#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "bl808_common.h"
#include "blai_core.h"
#include "blai_def_internal.h"
#include "blai_inst_obj_det_ops.h"
#include "blai_inst_postprocess.h"

int BL_entry_index(struct cpu_inst_layer_t* l, int location, int entry)
{
    int n = location / (l->w * l->h);
    int loc = location % (l->w * l->h);
    return  n * l->w * l->h * (4 + l->classes + 1) + entry * l->w * l->h + loc;
}

int lm_entry_index(struct cpu_inst_layer_t* l, int batch, int location, int entry)
{
    int n = location / (l->w * l->h);
    int loc = location % (l->w * l->h);
    return n * l->w * l->h * (14 + l->classes + 1) + entry * l->w * l->h + loc;
}

static inline float BL_leaky_activate(float x) { return (x > 0) ? x : .1f * x; }
static inline float BL_logistic_activate(float x) { return 1.f / (1.f + expf(-x)); }

void BL_scal_add_cpu(int N, float ALPHA, float BETA, float* X, int INCX)
{
    int i;
    for (i = 0; i < N; ++i)
        X[i * INCX] = X[i * INCX] * ALPHA + BETA;
}

void BL_activate_array(float* x, const int n, const ACTIVATION a)
{

    int i;
    if (a == LINEAR) {}
    else if (a == LEAKY) {
        for (i = 0; i < n; ++i) {
            x[i] = BL_leaky_activate(x[i]);
        }
    }
    else if (a == LOGISTIC) {
        for (i = 0; i < n; ++i) {
            x[i] = BL_logistic_activate(x[i]);
        }
    }
    else {
        for (i = 0; i < n; ++i) {
            x[i] = x[i];
        }
    }

}

int yolo_num_detections(struct cpu_inst_layer_t* l, float thresh)
{
    int i, n;
    int count = 0;
    for (i = 0; i < l->w * l->h; ++i) {
        for (n = 0; n < l->n; ++n) {
            int obj_index = BL_entry_index(l, n * l->w * l->h + i, 4);
            if (l->output[obj_index] > thresh) {
                ++count;
            }
        }
    }
    return count;
}

int num_detections(struct blai_net_info_t* net, float thresh)
{
    int i;
    int s = 0;
    for (i = 0; i < net->layer_cnt; ++i) {
        struct cpu_inst_layer_t* l = &net->layers[i];
        if (l->type == YOLO) {
            s += yolo_num_detections(l, thresh);
        }
    }
    return s;
}

detection* make_network_boxes(struct blai_net_info_t* net, float thresh, int* num)
{
    struct cpu_inst_layer_t* l = &net->layers[net->layer_cnt - 1];
    int i;
    int nboxes = num_detections(net, thresh);
    if (num) 
        *num = nboxes;
    if (nboxes == 0)
        return NULL;
    detection* dets = (detection*)BLAI_MALLOC(nboxes * sizeof(detection));
    for (i = 0; i < nboxes; ++i) {
        dets[i].prob = (float*)BLAI_MALLOC(l->classes * sizeof(float));
        // tx,ty,tw,th uncertainty
        /*
        dets[i].uc = (float*)xcalloc(4, sizeof(float)); // Gaussian_YOLOv3
        if (l->coords > 4) {
            dets[i].mask = (float*)xcalloc(l->coords - 4, sizeof(float));
        }
        */
    }
    return dets;
}

box get_yolo_box(float* x, int* biases, int n, int index, int i, int j, int lw, int lh, int w, int h, int stride)
{
    box b;
    b.x = (i + x[index + 0 * stride]) / lw;
    b.y = (j + x[index + 1 * stride]) / lh;
    b.w = exp(x[index + 2 * stride]) * biases[2 * n] / w;
    b.h = exp(x[index + 3 * stride]) * biases[2 * n + 1] / h;
    return b;
}

void correct_yolo_boxes(detection* dets, int n, int w, int h, int netw, int neth, int relative, int letter)
{
    int i;
    // network height (or width)
    int new_w = 0;
    // network height (or width)
    int new_h = 0;
    // Compute scale given image w,h vs network w,h
    // I think this "rotates" the image to match network to input image w/h ratio
    // new_h and new_w are really just network width and height
    if (letter) {
        if (((float)netw / w) < ((float)neth / h)) {
            new_w = netw;
            new_h = (h * netw) / w;
        }
        else {
            new_h = neth;
            new_w = (w * neth) / h;
        }
    }
    else {
        new_w = netw;
        new_h = neth;
    }
    // difference between network width and "rotated" width
    float deltaw = netw - new_w;
    // difference between network height and "rotated" height
    float deltah = neth - new_h;
    // ratio between rotated network width and network width
    float ratiow = (float)new_w / netw;
    // ratio between rotated network width and network width
    float ratioh = (float)new_h / neth;
    for (i = 0; i < n; ++i) {

        box b = dets[i].bbox;
        // x = ( x - (deltaw/2)/netw ) / ratiow;
        //   x - [(1/2 the difference of the network width and rotated width) / (network width)]
        b.x = (b.x - deltaw / 2. / netw) / ratiow;
        b.y = (b.y - deltah / 2. / neth) / ratioh;
        // scale to match rotation of incoming image
        b.w *= 1 / ratiow;
        b.h *= 1 / ratioh;

        // relative seems to always be == 1, I don't think we hit this condition, ever.
        if (!relative) {
            b.x *= w;
            b.w *= w;
            b.y *= h;
            b.h *= h;
        }

        dets[i].bbox = b;
    }
}

int get_yolo_detections(struct cpu_inst_layer_t* l, int w, int h, int netw, int neth, float thresh, int* map, int relative, detection* dets, int letter)
{
    int i, j, n;
    float* predictions = l->output;
    int count = 0;
    for (i = 0; i < l->w * l->h; ++i) {
        int row = i / l->w;
        int col = i % l->w;
        for (n = 0; n < l->n; ++n) {
            int obj_index = BL_entry_index(l, n * l->w * l->h + i, 4);
            float objectness = predictions[obj_index];
            if (objectness > thresh) {
                int box_index = BL_entry_index(l, n * l->w * l->h + i, 0);
                dets[count].bbox = get_yolo_box(predictions, l->biases, l->mask[n], box_index, col, row, l->w, l->h, netw, neth, l->w * l->h);
                dets[count].objectness = objectness;
                dets[count].classes = l->classes;
                for (j = 0; j < l->classes; ++j) {
                    int class_index = BL_entry_index(l, n * l->w * l->h + i, 4 + 1 + j);
                    float prob = objectness * predictions[class_index];
                    dets[count].prob[j] = (prob > thresh) ? prob : 0;
                }
                ++count;
            }
        }
    }
    correct_yolo_boxes(dets, count, w, h, netw, neth, relative, letter);
    return count;
}

void fill_network_boxes(struct blai_net_info_t* net, int w, int h, float thresh, float hier, int* map, int relative, detection* dets, int letter)
{
    int prev_classes = -1;
    int j;
    for (j = 0; j < net->layer_cnt; ++j) {
        struct cpu_inst_layer_t* l = &net->layers[j];
        if (l->type == YOLO) {
            int count = get_yolo_detections(l, w, h, net->w, net->h, thresh, map, relative, dets, letter);
            dets += count;
            if (prev_classes < 0) prev_classes = l->classes;
            else if (prev_classes != l->classes) {
                BL_LOGE(" Error: Different [yolo] layers have different number of classes = %d and %d - check your cfg-file! \n",
                    prev_classes, l->classes);
            }
        }    
    }
}


detection* get_network_boxes(struct blai_net_info_t* net, int w, int h, float thresh, float hier, int* map, int relative, int* num, int letter)
{
    detection* dets = make_network_boxes(net, thresh, num);
    if (dets)
        fill_network_boxes(net, w, h, thresh, hier, map, relative, dets, letter);
    return dets;
}

float overlap(float x1, float w1, float x2, float w2)
{
    float l1 = x1 - w1 / 2;
    float l2 = x2 - w2 / 2;
    float left = l1 > l2 ? l1 : l2;
    float r1 = x1 + w1 / 2;
    float r2 = x2 + w2 / 2;
    float right = r1 < r2 ? r1 : r2;
    return right - left;
}

float box_intersection(box a, box b)
{
    float w = overlap(a.x, a.w, b.x, b.w);
    float h = overlap(a.y, a.h, b.y, b.h);
    if (w < 0 || h < 0) return 0;
    float area = w * h;
    return area;
}

float box_union(box a, box b)
{
    float i = box_intersection(a, b);
    float u = a.w * a.h + b.w * b.h - i;
    return u;
}

float box_iou(box a, box b)
{
    //return box_intersection(a, b)/box_union(a, b);

    float I = box_intersection(a, b);
    float U = box_union(a, b);
    if (I == 0 || U == 0) {
        return 0;
    }
    return I / U;
}

int nms_comparator_v3(const void* pa, const void* pb)
{
    detection a = *(detection*)pa;
    detection b = *(detection*)pb;
    float diff = 0;
    if (b.sort_class >= 0) {
        diff = a.prob[b.sort_class] - b.prob[b.sort_class]; // there is already: prob = objectness*prob
    }
    else {
        diff = a.objectness - b.objectness;
    }
    if (diff < 0) return 1;
    else if (diff > 0) return -1;
    return 0;
}

void do_nms_sort(detection* dets, int total, int classes, float thresh)
{
    int i, j, k;
    k = total - 1;
    for (i = 0; i <= k; ++i) {
        if (dets[i].objectness == 0) {
            detection swap = dets[i];
            dets[i] = dets[k];
            dets[k] = swap;
            --k;
            --i;
        }
    }
    total = k + 1;

    for (k = 0; k < classes; ++k) {
        for (i = 0; i < total; ++i) {
            dets[i].sort_class = k;
        }
        qsort(dets, total, sizeof(detection), nms_comparator_v3);
        for (i = 0; i < total; ++i) {
            if (dets[i].prob[k] == 0) continue;
            box a = dets[i].bbox;
            for (j = i + 1; j < total; ++j) {
                box b = dets[j].bbox;
                if (box_iou(a, b) > thresh) {
                    dets[j].prob[k] = 0;
                }
            }
        }
    }
}

detection_with_class* get_actual_detections(detection* dets, int dets_num, float thresh, int* selected_detections_num, char** names)
{
    int selected_num = 0;
    detection_with_class* result_arr = (detection_with_class*)BLAI_MALLOC(dets_num * sizeof(detection_with_class));
    int i;
    for (i = 0; i < dets_num; ++i) {
        int best_class = -1;
        float best_class_prob = thresh;
        int j;
        for (j = 0; j < dets[i].classes; ++j) {
            int show = strncmp(names[j], "dont_show", 9);
            if (dets[i].prob[j] > best_class_prob && show) {
                best_class = j;
                best_class_prob = dets[i].prob[j];
            }
        }
        if (best_class >= 0) {
            result_arr[selected_num].det = dets[i];
            result_arr[selected_num].best_class = best_class;
            ++selected_num;
        }
    }
    if (selected_detections_num)
        *selected_detections_num = selected_num;
    return result_arr;
}

int compare_by_lefts(const void* a_ptr, const void* b_ptr) {
    const detection_with_class* a = (detection_with_class*)a_ptr;
    const detection_with_class* b = (detection_with_class*)b_ptr;
    const float delta = (a->det.bbox.x - a->det.bbox.w / 2) - (b->det.bbox.x - b->det.bbox.w / 2);
    return delta < 0 ? -1 : delta > 0 ? 1 : 0;
}

int lm_compare_by_lefts(const void* a_ptr, const void* b_ptr) {
    const lm_detection_with_class* a = (lm_detection_with_class*)a_ptr;
    const lm_detection_with_class* b = (lm_detection_with_class*)b_ptr;
    const float delta = (a->det.bbox.x - a->det.bbox.w / 2) - (b->det.bbox.x - b->det.bbox.w / 2);
    return delta < 0 ? -1 : delta > 0 ? 1 : 0;
}

void yolo_obj_det(struct blai_net_info_t *net, char** names, int image_width, int image_height, blai_inference_cb result_cb) {
    int nboxes = 0;
    float thresh = 0.24;
    float hier_thresh = 0.5;
    int ext_output = 1;
    float nms = .45;    // 0.4F
    int letterbox = 0;
    struct cpu_inst_layer_t* l = &net->layers[net->layer_cnt - 1];
    struct blai_result_t result;
    
    detection* dets = get_network_boxes(net, image_width, image_height, thresh, hier_thresh, 0, 1, &nboxes, letterbox);
    if (dets == NULL) {
        BL_LOGI("No object detected\r\n");
        return;
    }
        
    if (nms)
        do_nms_sort(dets, nboxes, l->classes, nms);

    int selected_detections_num;
    detection_with_class* selected_detections = get_actual_detections(dets, nboxes, thresh, &selected_detections_num, names);

    // text output
    qsort(selected_detections, selected_detections_num, sizeof(*selected_detections), compare_by_lefts);
    int i;
    for (i = 0; i < selected_detections_num; ++i) {
        const int best_class = selected_detections[i].best_class;
        BL_LOGI("%s: %.0f%%", names[best_class], selected_detections[i].det.prob[best_class] * 100);
        if (ext_output)
            BL_LOGI("\t(left_x: %4.0f   top_y: %4.0f   width: %4.0f   height: %4.0f)\r\n",
                round((selected_detections[i].det.bbox.x - selected_detections[i].det.bbox.w / 2) * image_width),
                round((selected_detections[i].det.bbox.y - selected_detections[i].det.bbox.h / 2) * image_height),
                round(selected_detections[i].det.bbox.w * image_width), round(selected_detections[i].det.bbox.h * image_height));
        else
            BL_LOGI("\r\n");
        int j;
        for (j = 0; j < l->classes; ++j) {
            if (selected_detections[i].det.prob[j] > thresh && j != best_class) {
                BL_LOGI("%s: %.0f%%", names[j], selected_detections[i].det.prob[j] * 100);

                if (ext_output)
                    BL_LOGI("\t(left_x: %4.0f   top_y: %4.0f   width: %4.0f   height: %4.0f)\r\n",
                        round((selected_detections[i].det.bbox.x - selected_detections[i].det.bbox.w / 2) * image_width),
                        round((selected_detections[i].det.bbox.y - selected_detections[i].det.bbox.h / 2) * image_height),
                        round(selected_detections[i].det.bbox.w * image_width), round(selected_detections[i].det.bbox.h * image_height));
                else
                    BL_LOGI("\r\n");
            }
        }
        result.r.objdet.rect.x = round((selected_detections[i].det.bbox.x - selected_detections[i].det.bbox.w / 2) * image_width);
        result.r.objdet.rect.y = round((selected_detections[i].det.bbox.y - selected_detections[i].det.bbox.h / 2) * image_height);
        result.r.objdet.rect.w = round(selected_detections[i].det.bbox.w * image_width);
        result.r.objdet.rect.h = round(selected_detections[i].det.bbox.h * image_height);
        result.r.objdet.best_class = best_class;
        result.r.objdet.prob = selected_detections[i].det.prob[best_class] * 100;
        result.app_type = net->app_type;
        result_cb(&result);
    }

    BLAI_FREE(selected_detections);
    for (i = 0; i < nboxes; i++)
        BLAI_FREE(dets[i].prob);
    BLAI_FREE(dets);
}
lm_box lm_get_yolo_box(float* x, int* biases, int n, int index, int i, int j, int lw, int lh, int w, int h, int stride)
{
    lm_box b;
    // ln - natural logarithm (base = e)
    // x` = t.x * lw - i;   // x = ln(x`/(1-x`))   // x - output of previous conv-layer
    // y` = t.y * lh - i;   // y = ln(y`/(1-y`))   // y - output of previous conv-layer
    // w = ln(t.w * net.w / anchors_w); // w - output of previous conv-layer
    // h = ln(t.h * net.h / anchors_h); // h - output of previous conv-layer

    float strid_w = w * 1. / lw;
    float strid_h = h * 1. / lh;

    b.x = (i + x[index + 0 * stride]) / lw;
    b.y = (j + x[index + 1 * stride]) / lh;
    b.w = exp(x[index + 2 * stride]) * biases[2 * n] / w;
    b.h = exp(x[index + 3 * stride]) * biases[2 * n + 1] / h;

    // b.lx1 = (i + x[index + 4*stride]  * biases[2*n]   / strid_w)  / lw;
    // b.ly1 = (j + x[index + 5*stride]  * biases[2*n+1] / strid_h)  / lh;
    // b.lx2 = (i + x[index + 6*stride]  * biases[2*n]   / strid_w)  / lw;
    // b.ly2 = (j + x[index + 7*stride]  * biases[2*n+1] / strid_h)  / lh;
    // b.lx3 = (i + x[index + 8*stride]  * biases[2*n]   / strid_w)  / lw;
    // b.ly3 = (j + x[index + 9*stride]  * biases[2*n+1] / strid_h)  / lh;
    // b.lx4 = (i + x[index + 10*stride] * biases[2*n]   / strid_w)  / lw;
    // b.ly4 = (j + x[index + 11*stride] * biases[2*n+1] / strid_h)  / lh;
    // b.lx5 = (i + x[index + 12*stride] * biases[2*n]   / strid_w)  / lw;
    // b.ly5 = (j + x[index + 13*stride] * biases[2*n+1] / strid_h)  / lh;

    b.lx1 = (i + x[index + 4 * stride]) / lw;
    b.ly1 = (j + x[index + 5 * stride]) / lh;
    b.lx2 = (i + x[index + 6 * stride]) / lw;
    b.ly2 = (j + x[index + 7 * stride]) / lh;
    b.lx3 = (i + x[index + 8 * stride]) / lw;
    b.ly3 = (j + x[index + 9 * stride]) / lh;
    b.lx4 = (i + x[index + 10 * stride]) / lw;
    b.ly4 = (j + x[index + 11 * stride]) / lh;
    b.lx5 = (i + x[index + 12 * stride]) / lw;
    b.ly5 = (j + x[index + 13 * stride]) / lh;


    return b;
}

void lm_correct_yolo_boxes(lm_detection* dets, int n, int w, int h, int netw, int neth, int relative, int letter)
{
    int i;
    // network height (or width)
    int new_w = 0;
    // network height (or width)
    int new_h = 0;
    // Compute scale given image w,h vs network w,h
    // I think this "rotates" the image to match network to input image w/h ratio
    // new_h and new_w are really just network width and height
    if (letter) {
        if (((float)netw / w) < ((float)neth / h)) {
            new_w = netw;
            new_h = (h * netw) / w;
        }
        else {
            new_h = neth;
            new_w = (w * neth) / h;
        }
    }
    else {
        new_w = netw;
        new_h = neth;
    }
    // difference between network width and "rotated" width
    float deltaw = netw - new_w;
    // difference between network height and "rotated" height
    float deltah = neth - new_h;
    // ratio between rotated network width and network width
    float ratiow = (float)new_w / netw;
    // ratio between rotated network width and network width
    float ratioh = (float)new_h / neth;
    for (i = 0; i < n; ++i) {

        lm_box b = dets[i].bbox;
        b.x = (b.x - deltaw / 2. / netw) / ratiow;
        b.y = (b.y - deltah / 2. / neth) / ratioh;
        // scale to match rotation of incoming image
        b.w *= 1 / ratiow;
        b.h *= 1 / ratioh;

        b.lx1 = (b.lx1 - deltaw / 2. / netw) / ratiow;
        b.ly1 = (b.ly1 - deltah / 2. / neth) / ratioh;
        b.lx2 = (b.lx2 - deltaw / 2. / netw) / ratiow;
        b.ly2 = (b.ly2 - deltah / 2. / neth) / ratioh;
        b.lx3 = (b.lx3 - deltaw / 2. / netw) / ratiow;
        b.ly3 = (b.ly3 - deltah / 2. / neth) / ratioh;
        b.lx4 = (b.lx4 - deltaw / 2. / netw) / ratiow;
        b.ly4 = (b.ly4 - deltah / 2. / neth) / ratioh;
        b.lx5 = (b.lx5 - deltaw / 2. / netw) / ratiow;
        b.ly5 = (b.ly5 - deltah / 2. / neth) / ratioh;

        // relative seems to always be == 1, I don't think we hit this condition, ever.
        if (!relative) {
            b.x *= w;
            b.w *= w;
            b.y *= h;
            b.h *= h;
            b.lx1 *= w;
            b.ly1 *= h;
            b.lx2 *= w;
            b.ly2 *= h;
            b.lx3 *= w;
            b.ly3 *= h;
            b.lx4 *= w;
            b.ly4 *= h;
            b.lx5 *= w;
            b.ly5 *= h;

        }

        dets[i].bbox = b;
    }
}

int lm_get_yolo_detections(struct cpu_inst_layer_t* l, int w, int h, int netw, int neth, float thresh, int* map, int relative, lm_detection* dets, int letter)
{
    int i, j, n;
    float* predictions = l->output;
    int count = 0;

    for (i = 0; i < l->w * l->h; ++i) {
        int row = i / l->w;
        int col = i % l->w;
        for (n = 0; n < l->n; ++n) {
            int obj_index = lm_entry_index(l, 0, n * l->w * l->h + i, 14);
            float objectness = predictions[obj_index];
            //if(objectness <= thresh) continue;    // incorrect behavior for Nan values

            if (objectness > thresh) {
                int box_index = lm_entry_index(l, 0, n * l->w * l->h + i, 0);
                dets[count].bbox = lm_get_yolo_box(predictions, l->biases, l->mask[n], box_index, col, row, l->w, l->h, netw, neth, l->w * l->h);
                dets[count].objectness = objectness;
                dets[count].classes = l->classes;
                
                for (j = 0; j < l->classes; ++j) {
                    int class_index = lm_entry_index(l, 0, n * l->w * l->h + i, 14 + 1 + j);
                    float prob = objectness * predictions[class_index];
                    dets[count].prob[j] = (prob > thresh) ? prob : 0;
                }
                ++count;
            }
        }
    }
    lm_correct_yolo_boxes(dets, count, w, h, netw, neth, relative, letter);
    return count;
}

void lm_fill_network_boxes(struct blai_net_info_t *net, int w, int h, float thresh, float hier, int* map, int relative, lm_detection* dets, int letter)
{
    int prev_classes = -1;
    int j;
    for (j = 0; j < net->layer_cnt; ++j) {
        struct cpu_inst_layer_t* l = &net->layers[j];
        if (l->type == YOLO) {

            int count = lm_get_yolo_detections(l, w, h, net->w, net->h, thresh, map, relative, dets, letter);
            dets += count;
            if (prev_classes < 0) prev_classes = l->classes;
            else if (prev_classes != l->classes) {
                BL_LOGE(" Error: Different [yolo] layers have different number of classes = %d and %d - check your cfg-file! \n",
                    prev_classes, l->classes);
            }
        }
    }
}

int lm_yolo_num_detections(struct cpu_inst_layer_t* l, float thresh)
{
    int i, n;
    int count = 0;
    for (i = 0; i < l->w * l->h; ++i) {
        for (n = 0; n < l->n; ++n) {
            int obj_index = lm_entry_index(l, 0, n * l->w * l->h + i, 14);
            if (l->output[obj_index] > thresh) {
                ++count;
            }
        }
    }
    return count;
}

int lm_num_detections(struct blai_net_info_t *net, float thresh)
{
    int i;
    int s = 0;
    for (i = 0; i < net->layer_cnt; ++i) {
        struct cpu_inst_layer_t* l= &net->layers[i];
        if (l->type == YOLO) 
            s += lm_yolo_num_detections(l, thresh);

    }
    return s;
}

lm_detection* lm_make_network_boxes(struct blai_net_info_t *net, float thresh, int* num)
{
    struct cpu_inst_layer_t* l = &net->layers[net->layer_cnt - 1];
    int i;
    int nboxes = lm_num_detections(net, thresh);
    if (num) 
        *num = nboxes;
    if (nboxes == 0)
        return NULL;

    lm_detection* dets = (lm_detection*)BLAI_MALLOC(nboxes * sizeof(lm_detection));
    for (i = 0; i < nboxes; i++) {
        dets[i].prob = (float*)BLAI_MALLOC(l->classes * sizeof(float));
        // tx,ty,tw,th uncertainty
        /*dets[i].uc = (float*)xcalloc(4, sizeof(float)); // Gaussian_YOLOv3
        if (l.coords > 4) {
            dets[i].mask = (float*)xcalloc(l.coords - 4, sizeof(float));
        }*/
    }
    return dets;
}

lm_detection* lm_get_network_boxes(struct blai_net_info_t* net, int w, int h, float thresh, float hier, int* map, int relative, int* num, int letter)
{
    lm_detection* dets = lm_make_network_boxes(net, thresh, num);
    if (dets)
        lm_fill_network_boxes(net, w, h, thresh, hier, map, relative, dets, letter);
    return dets;
}

float lm_box_intersection(lm_box a, lm_box b)
{
    float w = overlap(a.x, a.w, b.x, b.w);
    float h = overlap(a.y, a.h, b.y, b.h);
    if (w < 0 || h < 0) return 0;
    float area = w * h;
    return area;
}

float lm_box_union(lm_box a, lm_box b)
{
    float i = lm_box_intersection(a, b);
    float u = a.w * a.h + b.w * b.h - i;
    return u;
}

float lm_box_iou(lm_box a, lm_box b)
{
    //return box_intersection(a, b)/box_union(a, b);

    float I = lm_box_intersection(a, b);
    float U = lm_box_union(a, b);
    if (I == 0 || U == 0) {
        return 0;
    }
    return I / U;
}

int lm_nms_comparator_v3(const void* pa, const void* pb)
{
    lm_detection a = *(lm_detection*)pa;
    lm_detection b = *(lm_detection*)pb;
    float diff = 0;
    if (b.sort_class >= 0) {
        diff = a.prob[b.sort_class] - b.prob[b.sort_class]; // there is already: prob = objectness*prob
    }
    else {
        diff = a.objectness - b.objectness;
    }
    if (diff < 0) return 1;
    else if (diff > 0) return -1;
    return 0;
}

void lm_do_nms_sort(lm_detection* dets, int total, int classes, float thresh)
{

    int i, j, k;
    k = total - 1;
    for (i = 0; i <= k; ++i) {
        if (dets[i].objectness == 0) {
            lm_detection swap = dets[i];
            dets[i] = dets[k];
            dets[k] = swap;
            --k;
            --i;
        }
    }
    total = k + 1;

    for (k = 0; k < classes; ++k) {
        for (i = 0; i < total; ++i) {
            dets[i].sort_class = k;
        }
        qsort(dets, total, sizeof(lm_detection), lm_nms_comparator_v3);        
        for (i = 0; i < total; ++i) {
            if (dets[i].prob[k] == 0) continue;
            lm_box a = dets[i].bbox;
            for (j = i + 1; j < total; ++j) {
                lm_box b = dets[j].bbox;
                if (lm_box_iou(a, b) > thresh) {
                    dets[j].prob[k] = 0;
                }
            }
        }
    }
    
}

lm_detection_with_class* lm_get_actual_detections(lm_detection* dets, int dets_num, float thresh, int* selected_detections_num, char** names)
{
    int selected_num = 0;
    lm_detection_with_class* result_arr = (lm_detection_with_class*)BLAI_MALLOC(dets_num * sizeof(lm_detection_with_class));
    int i;
    for (i = 0; i < dets_num; ++i) {
        int best_class = -1;
        float best_class_prob = thresh;
        int j;
        for (j = 0; j < dets[i].classes; ++j) {
            int show = strncmp(names[j], "dont_show", 9);
            if (dets[i].prob[j] > best_class_prob && show) {
                best_class = j;
                best_class_prob = dets[i].prob[j];
            }
        }
        if (best_class >= 0) {
            result_arr[selected_num].det = dets[i];
            result_arr[selected_num].best_class = best_class;
            ++selected_num;
        }
    }
    if (selected_detections_num)
        *selected_detections_num = selected_num;
    return result_arr;
}

int compare_by_probs(const void* a_ptr, const void* b_ptr) {
    const lm_detection_with_class* a = (lm_detection_with_class*)a_ptr;
    const lm_detection_with_class* b = (lm_detection_with_class*)b_ptr;
    float delta = a->det.prob[a->best_class] - b->det.prob[b->best_class];
    return delta < 0 ? -1 : delta > 0 ? 1 : 0;
}

image BL_make_empty_image(int w, int h, int c)
{
    image out;
    out.data = 0;
    out.h = h;
    out.w = w;
    out.c = c;
    return out;
}

image BL_make_image(int w, int h, int c)
{
    image out = BL_make_empty_image(w, h, c);
    out.data = (float*)BLAI_MALLOC(h * w * c * sizeof(float));
    return out;
}

image BL_wrapimg(image im, int* image_size, lm_box best_bbox) {

    int lx1 = (best_bbox.lx1) * im.w;
    int ly1 = (best_bbox.ly1) * im.h;
    int lx2 = (best_bbox.lx2) * im.w;
    int ly2 = (best_bbox.ly2) * im.h;
    int lx3 = (best_bbox.lx3) * im.w;
    int ly3 = (best_bbox.ly3) * im.h;
    int lx4 = (best_bbox.lx4) * im.w;
    int ly4 = (best_bbox.ly4) * im.h;
    int lx5 = (best_bbox.lx5) * im.w;
    int ly5 = (best_bbox.ly5) * im.h;

    
    float v1[5][2] = {
        { 30.2946f, 51.6963f },
        { 65.5318f, 51.5014f },
        { 48.0252f, 71.7366f },
        { 33.5493f, 92.3655f },
        { 62.7299f, 92.2041f } };

    for (int i = 0; i < 5; i++) {
        v1[i][0] += (image_size[0] - 96.0) / 2;
        v1[i][1] += (image_size[1] - 112.0) / 2;
    }
    //cv::Mat src(5, 2, CV_32FC1, v1);
    image src = BL_make_image(2, 5, 1);
    memcpy(src.data, v1, 2 * 5 * sizeof(float));
    
    float v2[5][2] =
    { { lx1, ly1 },
      { lx2, ly2 },
      { lx3, ly3 },
      { lx4, ly4 },
      { lx5, ly5 } };

    //cv::Mat dst(5, 2, CV_32FC1, v2);
    image dst = BL_make_image(2, 5, 1);
    memcpy(dst.data, v2, 2 * 5 * sizeof(float));
    image m = similarTransform(dst, src);
    /*
    Mat imgAffine(image_size[0], image_size[1], CV_8UC3);
    Mat image_ori(im.h, im.w, CV_8UC3);
    Mat par = Mat(2, 3, CV_64FC1);
    for (int k = 0; k < im.c; ++k) {
        for (int i = 0; i < im.w * im.h; ++i) {
            image_ori.data[i * im.c + k] = (unsigned char)(255 * im.data[i + k * im.w * im.h]);
        }
    }
    
    par.at<double>(0, 0) = m.at<float>(0, 0);
    par.at<double>(0, 1) = m.at<float>(0, 1);
    par.at<double>(0, 2) = m.at<float>(0, 2);
    par.at<double>(1, 0) = m.at<float>(1, 0);
    par.at<double>(1, 1) = m.at<float>(1, 1);
    par.at<double>(1, 2) = m.at<float>(1, 2);

    warpAffine(image_ori, imgAffine, par, imgAffine.size(), INTER_LINEAR);
    */
    image wrap = BL_make_image(image_size[0], image_size[1], im.c);
    /*
    for (int k = 0; k < im.c; ++k) {
        for (int i = 0; i < image_size[0] * image_size[1]; ++i) {
            wrap.data[i + k * image_size[0] * image_size[1]] = imgAffine.data[i * im.c + k] / 255.0f;
        }
    }*/
    BLAI_FREE(src.data);
    BLAI_FREE(dst.data);
    BLAI_FREE(m.data);

    return wrap;
}

void yolo_face_landmark(struct blai_net_info_t* net, char** names, int image_width, int image_height, blai_inference_cb result_cb) {
    int nboxes = 0;

    float thresh = 0.24;
    float hier_thresh = 0.5;
    float dont_show = 1;
    int ext_output = 1;
    float nms = .45;    // 0.4F
    int letterbox = 0;
    float best_prob = 0;
    lm_box best_bbox = { 0 };
    struct blai_result_t result;

    image im = BL_make_image(image_width, image_height, 3);

    struct cpu_inst_layer_t* l = &net->layers[net->layer_cnt - 1];
    lm_detection* dets = lm_get_network_boxes(net, image_width, image_height, thresh, hier_thresh, 0, 1, &nboxes, letterbox);
    if (dets == NULL) {
        BL_LOGI("No object detected\r\n");
        BLAI_FREE(im.data);
        return;
    }

    if (nms) 
        lm_do_nms_sort(dets, nboxes, l->classes, nms);

    int selected_detections_num;
    lm_detection_with_class* selected_detections = lm_get_actual_detections(dets, nboxes, thresh, &selected_detections_num, names);

    // text output
    qsort(selected_detections, selected_detections_num, sizeof(*selected_detections), lm_compare_by_lefts);
    int i;
    for (i = 0; i < selected_detections_num; ++i) {
        const int best_class = selected_detections[i].best_class;
        BL_LOGI("%s: %.0f%%", names[best_class], selected_detections[i].det.prob[best_class] * 100);
        if (ext_output)
            BL_LOGI("\t(left_x: %4.0f   top_y: %4.0f   width: %4.0f   height: %4.0f)\n",
                round((selected_detections[i].det.bbox.x - selected_detections[i].det.bbox.w / 2) * image_width),
                round((selected_detections[i].det.bbox.y - selected_detections[i].det.bbox.h / 2) * image_height),
                round(selected_detections[i].det.bbox.w * image_width), round(selected_detections[i].det.bbox.h * image_height));
        else
            BL_LOGI("\n");

        int j;
        for (j = 0; j < l->classes; ++j) {
            if (selected_detections[i].det.prob[j] > thresh && j != best_class) {
                BL_LOGI("%s: %.0f%%", names[j], selected_detections[i].det.prob[j] * 100);

                if (ext_output)
                    BL_LOGI("\t(left_x: %4.0f   top_y: %4.0f   width: %4.0f   height: %4.0f)\n",
                        round((selected_detections[i].det.bbox.x - selected_detections[i].det.bbox.w / 2) * image_width),
                        round((selected_detections[i].det.bbox.y - selected_detections[i].det.bbox.h / 2) * image_height),
                        round(selected_detections[i].det.bbox.w * image_width), round(selected_detections[i].det.bbox.h * image_height));
                else
                    BL_LOGI("\n");
            }
        }
        result.r.landmark.rect.x = round((selected_detections[i].det.bbox.x - selected_detections[i].det.bbox.w / 2) * image_width);
        result.r.landmark.rect.y = round((selected_detections[i].det.bbox.y - selected_detections[i].det.bbox.h / 2) * image_height);
        result.r.landmark.rect.w = round(selected_detections[i].det.bbox.w * image_width);
        result.r.landmark.rect.h = round(selected_detections[i].det.bbox.h * image_height);
        result.r.landmark.best_class = best_class;
        result.r.landmark.prob = selected_detections[i].det.prob[best_class] * 100;
        result.app_type = net->app_type;

        if (selected_detections[i].det.prob[best_class] > best_prob) {
            best_prob = selected_detections[i].det.prob[best_class];
            best_bbox = selected_detections[i].det.bbox;
        }
    }

    qsort(selected_detections, selected_detections_num, sizeof(*selected_detections), compare_by_probs);
    for (i = 0; i < selected_detections_num; ++i) {
        int width = im.h * .006;
        if (width < 1)
            width = 1;

        int offset = selected_detections[i].best_class * 123457 % l->classes;    
        lm_box b = selected_detections[i].det.bbox;
        int left = (b.x - b.w / 2.) * im.w;
        int right = (b.x + b.w / 2.) * im.w;
        int top = (b.y - b.h / 2.) * im.h;
        int bot = (b.y + b.h / 2.) * im.h;

        int lx1 = (b.lx1) * im.w;
        int ly1 = (b.ly1) * im.h;
        int lx2 = (b.lx2) * im.w;
        int ly2 = (b.ly2) * im.h;
        int lx3 = (b.lx3) * im.w;
        int ly3 = (b.ly3) * im.h;
        int lx4 = (b.lx4) * im.w;
        int ly4 = (b.ly4) * im.h;
        int lx5 = (b.lx5) * im.w;
        int ly5 = (b.ly5) * im.h;
        BL_LOGI("left_eye:(%d,%d) right_eye:(%d,%d) nose:(%d,%d) left_mouth:(%d,%d) right_mouth:(%d,%d)\n", lx1, ly1, lx2, ly2, lx3, ly3, lx4, ly4, lx5, ly5);    
        result.r.landmark.lx1.x = lx1;
        result.r.landmark.lx1.y = ly1;
        result.r.landmark.lx1.pos = 0;

        result.r.landmark.lx2.x = lx2;
        result.r.landmark.lx2.y = ly2;
        result.r.landmark.lx2.pos = 1;

        result.r.landmark.lx3.x = lx3;
        result.r.landmark.lx3.y = ly3;
        result.r.landmark.lx3.pos = 2;

        result.r.landmark.lx4.x = lx4;
        result.r.landmark.lx4.y= ly4;
        result.r.landmark.lx4.pos = 3;

        result.r.landmark.lx5.x = lx5;
        result.r.landmark.lx5.y = ly5;
        result.r.landmark.lx5.pos = 4;
    }
    result_cb(&result);

    int crop_size[2] = { 128,128 };
    image wrap = BL_wrapimg(im, crop_size, best_bbox);
    
    BLAI_FREE(selected_detections);
    for (int i = 0; i < nboxes; i++)
        BLAI_FREE(dets[i].prob);
    BLAI_FREE(dets);

    BLAI_FREE(im.data);
    BLAI_FREE(wrap.data);

}


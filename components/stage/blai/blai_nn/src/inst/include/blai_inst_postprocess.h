#ifndef __BLAI_INST_POSTPROCESS_H__
#define __BLAI_INST_POSTPROCESS_H__

typedef struct {
    int w;
    int h;
    int c;
    float* data;
} image;

void image_classification(struct blai_net_info_t* net, char** imgnet_names, fixed_point_t* DATA_buf, blai_inference_cb result_cb, int num);
void KWS_classification(struct blai_net_info_t* net, char** imgnet_names, fixed_point_t* DATA_buf, blai_inference_cb result_cb, int num);
void get_output_data(struct blai_net_info_t* net, fixed_point_t* DATA_buf, int layer, int size);
void face_recongnition(struct blai_net_info_t* net, char** names, int names_len, const float** feature_list, int feature_len, fixed_point_t* DATA_buf, blai_inference_cb result_cb);
void yolo_obj_det(struct blai_net_info_t *net, char** names, int image_width, int image_height, blai_inference_cb result_cb);
void yolo_face_landmark(struct blai_net_info_t* net, char** names, int image_width, int image_height, blai_inference_cb result_cb);
void load_postprocess_classification(blai_model_hdl_t hdl, const char** classes_name, int classes_num);
void load_postprocess_face_recongnition(blai_model_hdl_t hdl, const char** names, int names_num, const float** features_list, int features_num);
image similarTransform(image src, image dst);
image BL_make_image(int w, int h, int c);
void retina_face(struct blai_net_info_t* net, char** imgnet_names, fixed_point_t* DATA_buf, int image_width, int image_height, blai_inference_cb result_cb);
void retina_person(struct blai_net_info_t* net, char** imgnet_names, fixed_point_t* DATA_buf, int image_width, int image_height, blai_inference_cb result_cb);
void retina(struct blai_net_info_t* net, char** imgnet_names, int class_num, fixed_point_t* DATA_buf, int image_width, int image_height, blai_inference_cb result_cb);
void face_recognition_evaluation(struct blai_net_info_t* net, char** face_IDs, fixed_point_t* DATA_buf, int image_width, int image_height, blai_inference_cb result_cb);

#endif /* __BLAI_INST_POSTPROCESS_H__ */


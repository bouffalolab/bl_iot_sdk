#ifndef __BL_CAM_H__
#define __BL_CAM_H__

#include <sensor.h>

int bl_cam_config_get(uint8_t *quality, uint16_t *width, uint16_t *height);
int bl_cam_config_update(uint8_t quality);
int bl_cam_init(int enable_mjpeg, const rt_camera_desc *desc);
int bl_cam_restart(int enable_mjpeg);
int bl_cam_enable_24MRef(void);
int bl_cam_frame_get(uint32_t *frames, uint8_t **ptr1, uint32_t *len1, uint8_t **ptr2, uint32_t *len2);
int bl_cam_frame_fifo_get(uint32_t *frames, uint8_t **ptr1, uint32_t *len1, uint8_t **ptr2, uint32_t *len2);
int bl_cam_frame_pop(void);
int bl_cam_frame_pop_old(void);
int bl_cam_frame_wait(void);
int bl_cam_yuv_frame_wait(void);
int bl_cam_yuv_frame_get(uint32_t *frames, uint8_t **ptr1, uint32_t *len1, uint8_t **ptr2, uint32_t *len2);
int bl_cam_yuv_frame_pop(void);
int bl_cam_mjpeg_encoder(uint32_t yuv_addr, uint32_t jpeg_addr, uint32_t *jpeg_size,  uint32_t width, uint32_t height, uint32_t quality);
#endif

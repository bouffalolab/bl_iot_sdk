#ifndef __SENSOR_H__
#define __SENSOR_H__
#include <bl_comm_sns.h>


typedef struct _sensor smart_sensor_t;

typedef enum {
    SENSOR_REG_ADDR_8BIT = 0,
    SENSOR_REG_ADDR_16BIT,
} sensor_reg_addr_bit_e;

typedef struct _sensor_property
{
    BAYER_PATTERN_E bayer_pattern;
} sensor_property_t;


typedef struct _sensor {
    /* Sensor ID */
    const char*         name;
    /* Sensor property */
    uint8_t             slv_addr;                   /* sensor I2C slave address */
    uint8_t             reg_addr_bit;               /* sensor register address bit*/
    uint32_t            pix_clk;                    /* sensor pixel clock */
    BL_Img_Size_T       total_win;                  /* sensor total window */
    BL_Img_Size_T       out_win;                    /* sensor output window */
    /* Sensor status */
    int                 enabled;                    /* sensor enable status */
    VIDEO_MODE_E        video_mode;
    FLIP_MIRROR_TYPE_E  flip_mirror_type;          /* flip mirror type */
    uint32_t             fps;                       /* fps * 100*/
    /* Sensor operations */
    int                 (*enable)(struct _sensor *sensor);
    int                 (*disable)(struct _sensor *sensor);
    int                 (*set_exposure)(struct _sensor *sensor, BL_EXPO_TIME expo_time);
    int                 (*set_gain)(struct _sensor *sensor, BL_GAIN_DB gain);
    int                 (*set_flipmirror)(struct _sensor *sensor, FLIP_MIRROR_TYPE_E type);
    int                 (*get_property)(struct _sensor *sensor, sensor_property_t *property);
    int                 (*set_fps)(struct _sensor *sensor, uint8_t *fps);
    /* Sensor quick mode */
    BAYER_PATTERN_E bayer_pattern;
} smart_sensor_t;

typedef struct _sensor_init_info {
    void (*get_probe_info)  (uint8_t *slv_addr, uint32_t *regs_sensor_id, uint16_t *sensor_id);
    int  (*init)            (smart_sensor_t *sensor);
} sensor_init_info_t;

typedef int (*SENSOR_PROBE_FUNC)(void);
typedef int (*SENSOR_INIT_FUNC)(smart_sensor_t *sensor);
typedef int (*SENSOR_SETFMT_FUNC)(smart_sensor_t *sensor);

typedef struct
{
	char *name;
	uint8_t addr;
    SENSOR_PROBE_FUNC probe;
    SENSOR_INIT_FUNC init;
    SENSOR_SETFMT_FUNC setFmt;
} BL_SENSOR_DESC_T;

typedef struct {
    int VTS;
    int fps;
} fps_info_t;

int yuvsensor_init(void);
int mipi_sensor_init(void);
int sensor_is_inited(void);
int sensor_is_enabled(void);
int sensor_enable(void);
int sensor_disable(void);
int sensor_reset(void);

void sensor_get_name(const char** name);


#define ATTR_SENSOR_DEVICE_TABLE __attribute__((section(".sensor_desc")))  __attribute__((used))


#endif /* __SENSOR_H__ */

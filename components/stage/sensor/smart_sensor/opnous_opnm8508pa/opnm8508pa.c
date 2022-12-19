#include <bl808.h>
#include <smart_sensor.h>
#include <sccb.h>

/* opnm8508pa sensor info */
#define SLAVE_ADDR                  0x3c
#define SLAVE_ADDR_DRIVER           0x70
#define SENSOR_ID_H                 0x4e
#define SENSOR_ID_L                 0x02


/* opnm8508pa registers */
#define REG_SENSOR_ID_H             0x02
#define REG_SENSOR_ID_L             0x03

typedef enum {
    FORMAT_INDEX_MIPI_2_LANE_328_744_10fps,
    FORMAT_INDEX_INVALID,
} FORMAT_INDEX;

static fps_info_t fps_tbl = {0};

static const sensor_format_t format_info[] = {
    {   /*  MIPI 2lane 328x744 10fps  */
        .total_width    = 328,
        .total_height   = 744,
        .pix_clk        = 32 * 1000 * 1000,
        .fps            = 30,
        .bayer_pattern = BAYER_PATTERN_BG,
    },
};

static const int opnm8508pa_mode[] = {\
    SPP_INPUT_MIPI_2LANE,
};


static const sensor_reg_16_8_t init_reglist_MIPI_2lane_328_744_10fps[] =
{
    {0x00, 0x02},
    {0x04, 0xCF},
    {0x05, 0x80},
    {0x00, 0x02},
    {0x0D, 0x08},
    {0x0E, 0x08},
    {0x0F, 0x04},
    {0x10, 0x01},
    {0x11, 0xE2},
    {0x12, 0x10},
    {0x13, 0xFA},
    {0x14, 0x01},
    {0x15, 0x40},
    {0x16, 0x0E},
    {0x17, 0x0F},
    {0x1E, 0x0E},
    {0x1F, 0x10},
    {0x20, 0x10},
    {0x21, 0xF8},
    {0x22, 0x0E},
    {0x23, 0x0E},
    {0x24, 0x10},
    {0x25, 0xFA},
    {0x28, 0x00},
    {0x29, 0x01},
    {0x2A, 0x00},
    {0x2B, 0x6E},
    {0x2D, 0x00},
    {0x2E, 0x4E},
    {0x2F, 0x20},
    {0x30, 0x00},
    {0x31, 0x0B},
    {0x32, 0x00},
    {0x33, 0x21},
    {0x34, 0x00},
    {0x35, 0x0B},
    {0x36, 0x00},
    {0x37, 0x0B},
    {0x38, 0x00},
    {0x39, 0x16},
    {0x3A, 0x00},
    {0x3B, 0x0B},
    {0x3C, 0x00},
    {0x3D, 0x21},
    {0x3E, 0x00},
    {0x3F, 0x0B},
    {0x41, 0x0E},
    {0x43, 0x19},
    {0x44, 0x81},
    {0x46, 0x44},
    // {0x4F, 0x06}, // clk alway in hs

    {0x5D, 0x30},
    {0x60, 0x00},
    {0x61, 0x21},
    {0x62, 0x00},
    {0x63, 0x31},
    {0x68, 0x00},
    {0x69, 0x21},
    {0x6A, 0x00},
    {0x6B, 0x4A},
    {0x6C, 0x00},
    {0x6D, 0x00},
    {0x6E, 0x00},
    {0x6F, 0x65},
    {0x70, 0x00},
    {0x71, 0x1F},
    {0x72, 0x01},
    {0x73, 0x3A},
    {0x74, 0x00},
    {0x75, 0x5A},
    {0x76, 0x15},
    {0x78, 0x0A},
    {0x79, 0x15},
    {0x7A, 0x08},
    {0x7B, 0x03},
    {0x7C, 0x01},
    {0x7D, 0x5F},
    {0x7E, 0x0A},
    {0x7F, 0x01},
    {0x80, 0x61},
    {0x81, 0x10},
    {0x82, 0x00},
    {0x83, 0x53},
    {0x84, 0x05},
    {0x85, 0x00},
    {0x86, 0x54},
    {0x8F, 0x00},
    {0x90, 0x56},
    {0x91, 0x00},
    {0x92, 0x1F},
    {0x93, 0x00},
    {0x94, 0x4A},
    {0x95, 0x00},
    {0x96, 0x1F},
    {0x97, 0x00},
    {0x98, 0x4A},
    {0x99, 0x00},
    {0x9A, 0x1F},
    {0x9B, 0x00},
    {0x9C, 0x4A},
    {0x9D, 0x00},
    {0x9E, 0x1F},
    {0x9F, 0x00},
    {0xA0, 0x4A},
    {0xA5, 0x80},
    {0xA2, 0x38},
    {0xA6, 0x6A},
    {0xA8, 0x3C},
    {0xB8, 0x0C},
    {0xA7, 0x95},
    {0xB0, 0x88},
    {0xB1, 0x60},
    {0xB4, 0x00},
    {0xAF, 0x0D},

    // 0xa5,0x45 for test mode
    // {0xa5, 0x80},
    // {0x45, 0x0a},

    // master mode
    {0x28, 0x07},
    {0x29, 0x80},
    {0xB7, 0x02},

    {REGLIST_END, 0x00},
};

static const sensor_reg_16_8_t init_reglist_MIPI_2lane_328_744_10fps_driver[] =
{
    {0xFF, 0x00},
    {0x20, 0xBA},
    {0x22, 0x3C},
    {0x23, 0xD9},
    {0x24, 0xDE},
    {0x31, 0x08},
    {0x32, 0x66},
    {0x33, 0x2D},
    {0x34, 0x47},
    {0x36, 0xC1},
    {0x37, 0x08},
    {0x38, 0x1B},
    {0x39, 0xC1},
    {0x3A, 0x08},
    {0x3B, 0x1B},
    {0x3F, 0x30},
    {0x40, 0x80},
    {0x43, 0xB4},
    {0x44, 0xFF},
    {0x45, 0x03},
    {0x46, 0xFF},
    {0x47, 0x00},
    {0x48, 0xA0},
    {0x4D, 0x90},

    {REGLIST_END, 0x00},
};

static int enable(smart_sensor_t *sensor)
{
    // start driver --> start sensor
    TickType_t xDelay = pdMS_TO_TICKS(1);

    // start driver
    SCCB_Write(SLAVE_ADDR_DRIVER, 0x48, 0xA0);
    SCCB_Write(SLAVE_ADDR_DRIVER, 0x23, 0xD9);
    // SCCB_Write(SLAVE_ADDR_DRIVER, 0x00, 0x01); //delay 1ms
    vTaskDelay(xDelay);
    SCCB_Write(SLAVE_ADDR_DRIVER, 0x29, 0xD3);
    SCCB_Write(SLAVE_ADDR_DRIVER, 0x4F, 0x4F);
    // SCCB_Write(SLAVE_ADDR_DRIVER, 0x00, 0x01); //delay 1ms
    vTaskDelay(xDelay);
    SCCB_Write(SLAVE_ADDR_DRIVER, 0x29, 0xD2);
    SCCB_Write(SLAVE_ADDR_DRIVER, 0x48, 0xAF);

    // start sensor
    SCCB_Write(sensor->slv_addr, 0x05,  0xFF);
    SCCB_Write(sensor->slv_addr, 0x06,  0x7F);

    return 0;
}

static int disable(smart_sensor_t *sensor)
{
    // stop sensor --> stop driver

    // stop sensor
    SCCB_Write(sensor->slv_addr, 0x05, 0x80);
    SCCB_Write(sensor->slv_addr, 0x06, 0x00);

    // stop driver
    SCCB_Write(SLAVE_ADDR_DRIVER, 0x48, 0xA0);
    SCCB_Write(SLAVE_ADDR_DRIVER, 0x4F, 0x4E);
    SCCB_Write(SLAVE_ADDR_DRIVER, 0x23, 0xD0);
    SCCB_Write(SLAVE_ADDR_DRIVER, 0x29, 0x00);
    return 0;
}

static int setFmt(smart_sensor_t *sensor)
{
    int i;
    FORMAT_INDEX format_index;
    const sensor_reg_16_8_t *init_reglist;
    const sensor_reg_16_8_t *init_reglist_driver;

    format_index = FORMAT_INDEX_MIPI_2_LANE_328_744_10fps;
    init_reglist = init_reglist_MIPI_2lane_328_744_10fps;
    init_reglist_driver = init_reglist_MIPI_2lane_328_744_10fps_driver;
    sensor->out_win.width  = 328;
    sensor->out_win.height = 744;

    sensor->pix_clk             = format_info[format_index].pix_clk;
    sensor->fps                 = format_info[format_index].fps;
    sensor->total_win.width     = format_info[format_index].total_width;
    sensor->total_win.height    = format_info[format_index].total_height;
    sensor->bayer_pattern       = format_info[format_index].bayer_pattern;

    /*
        上电顺序：
            Driver initial -->Sensor initial -->Start driver -->Start sensor
        下电时序与上电的相反
    */

    // init driver
    for (i = 0; init_reglist_driver[i].addr != REGLIST_END; i++) {
        SCCB_Write(SLAVE_ADDR_DRIVER, init_reglist_driver[i].addr, (uint8_t)init_reglist_driver[i].data);
    }

    // init sensor
    for (i = 0; init_reglist[i].addr != REGLIST_END; i++) {
        SCCB_Write(sensor->slv_addr, init_reglist[i].addr, (uint8_t)init_reglist[i].data);
    }

    // uint8_t rdata;
    // SCCB_Read(sensor->slv_addr, 0x4f, &rdata);
    // printf(" 0x4f value is  %x, %d\r\n", rdata, rdata);

    return 0;
}

static int probe(void)
{
    return sensor_probe_8bit(SLAVE_ADDR, REG_SENSOR_ID_H, REG_SENSOR_ID_L, SENSOR_ID_H, SENSOR_ID_L);
}

static int init(smart_sensor_t *sensor)
{
    /* Initialize sensor structure */
    SENSOR_INIT_COMMON(OPNM8508PA);

    return 0;
}

const BL_SENSOR_DESC_T sensor_desc_opnm8508pa ATTR_SENSOR_DEVICE_TABLE =
{
    "OPNM8508PA",
    SLAVE_ADDR,
    probe,
    init,
    setFmt,
};


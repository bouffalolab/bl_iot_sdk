#include <string.h>
#include <math.h>

#include <bl808.h>
#include <bl808_clkrst.h>
#include <bl_gpio.h>

#include <bl808_gpio.h>
#include <bl808_glb.h>

#include <sccb.h>
#include "smart_sensor.h"

extern BL_SENSOR_DESC_T _ld_bl_driver_sensor_start;
extern BL_SENSOR_DESC_T _ld_bl_driver_sensor_end;

static void sensor_pinmux_init(void)
{
    GLB_GPIO_Cfg_Type cfg;
    if (SPP_INPUT_MODE == SPP_INPUT_DVP) {
        uint8_t gpiopins[] = {GLB_GPIO_PIN_17, GLB_GPIO_PIN_16, GLB_GPIO_PIN_24,
                                GLB_GPIO_PIN_19, GLB_GPIO_PIN_18, GLB_GPIO_PIN_32, GLB_GPIO_PIN_31, GLB_GPIO_PIN_30, GLB_GPIO_PIN_29,
                                GLB_GPIO_PIN_28, GLB_GPIO_PIN_27, GLB_GPIO_PIN_26, GLB_GPIO_PIN_25};
        int i;

        cfg.gpioMode=GPIO_MODE_AF;
        cfg.pullType=GPIO_PULL_NONE;
        cfg.drive=0;
        cfg.smtCtrl=1;

        for(i=0;i<sizeof(gpiopins)/sizeof(gpiopins[0]);i++){
            cfg.gpioPin=gpiopins[i];
            cfg.gpioFun=GPIO_FUN_CAM;
            GLB_GPIO_Init(&cfg);
        }

        // REFCLK
        cfg.gpioPin=GLB_GPIO_PIN_33;
        cfg.gpioFun=GPIO_FUN_CLOCK_OUT;
        GLB_GPIO_Init(&cfg);

        cfg.gpioMode=GPIO_MODE_OUTPUT;
        cfg.pullType=GPIO_PULL_UP;
        // RESET
        if (DVP_8BIT_MODE == 1) {
            cfg.gpioPin=GLB_GPIO_PIN_18;
            cfg.gpioFun=GPIO_FUN_GPIO;
            GLB_GPIO_Init(&cfg);
            GLB_GPIO_Write(GLB_GPIO_PIN_18, 0);
            GLB_GPIO_Output_Enable(GLB_GPIO_PIN_18);
        } else {
            cfg.gpioPin=GLB_GPIO_PIN_20;
            cfg.gpioFun=GPIO_FUN_GPIO;
            GLB_GPIO_Init(&cfg);
            GLB_GPIO_Write(GLB_GPIO_PIN_20, 0);
            GLB_GPIO_Output_Enable(GLB_GPIO_PIN_20);
        }

        // PWDN
        cfg.gpioPin=GLB_GPIO_PIN_8;
        cfg.gpioFun=GPIO_FUN_GPIO;
        GLB_GPIO_Init(&cfg);
        GLB_GPIO_Write(GLB_GPIO_PIN_8, 0);
        GLB_GPIO_Output_Enable(GLB_GPIO_PIN_8);

        GLB_Set_ClkOutSel(1, 0); // select dvp_ref_clk pin as cam_ref_clk
        GLB_Set_Cam_Ref_CLK(1, 1, 3); // select cam_ref_clk as 96M / 4 = 24M
    }
    else {
        GLB_GPIO_Cfg_Type cfg;

        cfg.pullType = GPIO_PULL_NONE;
        cfg.drive = 0;
        cfg.smtCtrl = 1;

        if (BL808_BOARD_TYPE == BL_BOARD_808_EVB) {
            // reset
            cfg.gpioPin = GLB_GPIO_PIN_21;
            cfg.gpioFun = GPIO_FUN_GPIO;
            cfg.gpioMode = GPIO_MODE_OUTPUT;
            GLB_GPIO_Init(&cfg);
            GLB_GPIO_Write(GLB_GPIO_PIN_21, 0);
            GLB_GPIO_Output_Enable(GLB_GPIO_PIN_21);

            // pwdn
            cfg.gpioPin = GLB_GPIO_PIN_22;
            cfg.gpioFun = GPIO_FUN_GPIO;
            cfg.gpioMode = GPIO_MODE_OUTPUT;
            GLB_GPIO_Init(&cfg);
            GLB_GPIO_Write(GLB_GPIO_PIN_22, 0);
            GLB_GPIO_Output_Enable(GLB_GPIO_PIN_22);

            // mclk
            cfg.gpioPin = GLB_GPIO_PIN_23;
            cfg.gpioFun = GPIO_FUN_CLOCK_OUT;
            cfg.gpioMode = GPIO_MODE_OUTPUT;
            GLB_GPIO_Init(&cfg);

            GLB_Set_ClkOutSel(3, 0); // select dvp_ref_clk pin as cam_ref_clk
            GLB_Set_Cam_Ref_CLK(1, 1, 3); // select cam_ref_clk as 96M / 4 = 24M
        }
        else if (BL808_BOARD_TYPE == BL_BOARD_808_OPNM8508PA){
            cfg.gpioPin = GLB_GPIO_PIN_41;
            cfg.gpioFun = GPIO_FUN_GPIO;
            cfg.gpioMode = GPIO_MODE_OUTPUT;
            GLB_GPIO_Init(&cfg);
            GLB_GPIO_Write(GLB_GPIO_PIN_41, 0);
            GLB_GPIO_Output_Enable(GLB_GPIO_PIN_41);
        }
    }
}

static void yuv_sensor_input_reset(void)
{
    // RESET
    GLB_GPIO_Write(GLB_GPIO_PIN_18, 1);
    // PWDN
    GLB_GPIO_Write(GLB_GPIO_PIN_8, 0);
    BL808_Delay_US(50);
}

int yuvsensor_init(void)
{
    uint8_t slv_addr;
    BL_SENSOR_DESC_T *start, *end;

    start = &_ld_bl_driver_sensor_start;
    end = &_ld_bl_driver_sensor_end;
    sensor_pinmux_init();

    SCCB_Init();
    SPP_Sensor_Reset();
    yuv_sensor_input_reset();

    slv_addr = SCCB_Scan(0x1, 0x7f);
    BL_LOGI("slv_addr[0x%02x]\r\n", slv_addr);

    while (start < end) {
        BL_LOGI("try matching the sensor module [%s]\r\n", start->name);
        if(slv_addr == start->addr) {
            SCCB_Init();    /* TODO: will add i2c_abort in SCCB_Scan */
            if (0 == start->probe()){
                BL_LOGI("Initialize sensor module [%s]\r\n", start->name);
                if (start->init(NULL) < 0) {
                    return -1;
                }

#if PRINT_FAST_CAP_TIMING
                printf("SNS INIT %lu\r\n", xTaskGetTickCountFromISR());
#endif
                return 0;
            }
        }
        start++;
    }

    BL_LOGE("Sensor probe failed! Please check the sensor connection.\r\n");
    return -1;

}

static void sipeed_board_pinmux_init(GLB_GPIO_Type mclk, GLB_GPIO_Type pwdn, GLB_GPIO_Type reset)
{
    GLB_GPIO_Cfg_Type cfg;

    cfg.drive = 0;
    cfg.smtCtrl = 1;
    // REFCLK
    cfg.gpioPin=mclk;
    cfg.gpioFun=GPIO_FUN_CLOCK_OUT;
    GLB_GPIO_Init(&cfg);

    cfg.gpioMode=GPIO_MODE_OUTPUT;
    cfg.pullType=GPIO_PULL_UP;
    // PWDN
    cfg.gpioPin=pwdn;
    cfg.gpioFun=GPIO_FUN_GPIO;
    GLB_GPIO_Init(&cfg);
    GLB_GPIO_Write(pwdn, 1);
    GLB_GPIO_Output_Enable(pwdn);

    // RESET
    cfg.gpioPin=reset;
    cfg.gpioFun=GPIO_FUN_GPIO;
    GLB_GPIO_Init(&cfg);
    GLB_GPIO_Write(reset, 1);
    GLB_GPIO_Output_Enable(reset);

    GLB_Set_CAM_CLK(ENABLE, GLB_CAM_CLK_WIFIPLL_96M, 3); // select cam_ref_clk as 96M / 4 = 24M
}

int mipi_sensor_init(void)
{
    uint8_t slv_addr;
    BL_SENSOR_DESC_T *start, *end;

    start = &_ld_bl_driver_sensor_start;
    end = &_ld_bl_driver_sensor_end;
    sipeed_board_pinmux_init(GLB_GPIO_PIN_33, GLB_GPIO_PIN_40, GLB_GPIO_PIN_41);
    SCCB_Init_GPIO(GLB_GPIO_PIN_6, GLB_GPIO_PIN_7);

    slv_addr = SCCB_Scan(0x1, 0x7f);
    slv_addr = 0x3c;
    BL_LOGI("slv_addr[0x%02x]\r\n", slv_addr);

    while (start < end) {
        BL_LOGI("try matching the sensor module [%s]\r\n", start->name);
        if(slv_addr == start->addr) {
            if (0 == start->probe()){
                BL_LOGI("Initialize sensor module [%s]\r\n", start->name);
                if (start->init(NULL) < 0) {
                    return -1;
                }

                return 0;
            }
        }
        start++;
    }

    BL_LOGE("Sensor probe failed! Please check the sensor connection.\r\n");
    return -1;
}


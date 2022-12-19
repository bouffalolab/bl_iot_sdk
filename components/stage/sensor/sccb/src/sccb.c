#include "bl808_i2c.h"
#include "bl808_gpio.h"
#include "bl808_glb.h"
#include "bl808_glb_gpio.h"
#include "bl808_clock.h"
#include "sccb.h"
//#include <semphr.h>

#define I2C_ID I2C0_ID
#define USING_HW_I2C_SCCB


#ifdef USING_HW_I2C_SCCB
static I2C_CFG_Type i2cCfgStruct;

static void I2C_GPIO_Init(void)
{
    GLB_GPIO_Cfg_Type cfg;
    uint8_t gpio_pins[2];
    int i;

    if (SPP_INPUT_MODE == SPP_INPUT_DVP) {
        if (DVP_8BIT_MODE == 1) {
            gpio_pins[0] = GLB_GPIO_PIN_6;
            gpio_pins[1] = GLB_GPIO_PIN_7;
        } else {
            gpio_pins[0] = GLB_GPIO_PIN_22;
            gpio_pins[1] = GLB_GPIO_PIN_23;
        }
    } else { // mipi csi
        if (BL808_BOARD_TYPE == BL_BOARD_808_EVB) {
            gpio_pins[0] = GLB_GPIO_PIN_19;
            gpio_pins[1] = GLB_GPIO_PIN_20;
        }
        else if (BL808_BOARD_TYPE == BL_BOARD_808_OPNM8508PA){
            gpio_pins[0] = GLB_GPIO_PIN_21;
            gpio_pins[1] = GLB_GPIO_PIN_22;
        }

    }

    cfg.gpioMode=GPIO_MODE_AF;
    cfg.pullType=GPIO_PULL_UP;
    cfg.drive=0;
    cfg.smtCtrl=1;

#ifdef ENABLE_I2C1
    cfg.gpioFun=GPIO_FUN_I2C3;
#else
    cfg.gpioFun=GPIO_FUN_I2C2;
#endif
    for (i = 0; i < 2; i++) {
        cfg.gpioPin = gpio_pins[i];
        GLB_GPIO_Init(&cfg);
    }
}

static void GPIO_I2C_Init(GLB_GPIO_Type scl_pin, GLB_GPIO_Type sda_pin)
{
    GLB_GPIO_Cfg_Type cfg;
    uint8_t gpio_pins[2];
    int i;

    gpio_pins[0] = scl_pin;
    gpio_pins[1] = sda_pin;
 
    cfg.gpioMode=GPIO_MODE_AF;
    cfg.pullType=GPIO_PULL_UP;
    cfg.drive=0;
    cfg.smtCtrl=1;

#ifdef ENABLE_I2C1
    cfg.gpioFun=GPIO_FUN_I2C3;
#else
    cfg.gpioFun=GPIO_FUN_I2C2;
#endif
    for (i = 0; i < 2; i++) {
        cfg.gpioPin = gpio_pins[i];
        GLB_GPIO_Init(&cfg);
    }
}

static int I2C_BUS_Init(void)
{
    I2C_Disable(I2C_ID);
    I2C_SetDefaultConfig(&i2cCfgStruct);
    I2C_MasterInit(I2C_ID, &i2cCfgStruct);

    return 0;
}

int SCCB_Init(void)
{
    GLB_Set_I2C_CLK(ENABLE, GLB_I2C_CLK_XCLK, 0); // Set HW I2C Clock to 32M
    I2C_GPIO_Init();
    I2C_BUS_Init();

    return 0;
}

int SCCB_Init_GPIO(uint8_t scl, uint8_t sda)
{
    GLB_Set_I2C_CLK(ENABLE, GLB_I2C_CLK_XCLK, 0); // Set HW I2C Clock to 32M
    GPIO_I2C_Init((GLB_GPIO_Type)scl, (GLB_GPIO_Type)sda);
    I2C_BUS_Init();

    return 0;
}

static int SCCB_Probe(uint8_t slv_addr)
{
    I2C_Transfer_Cfg cfg;
    uint8_t dummy_data = 0;

    cfg.slaveAddr = slv_addr;
    cfg.subAddressSize = 0;
    cfg.subAddress = NULL;
    cfg.dataSize = 1;
    cfg.data = &dummy_data;
    if (SUCCESS == I2C_MasterSendBlocking(I2C_ID, &cfg)){
        return 0;
    } else {
        return -1;
    }
}

int SCCB_Scan(int first, int last)
{
    BL_LOGI("-------------------scan_i2c_bus--------------------\r\n");
    int i, j;
    int ret;
    uint8_t last_acked = 0;

    BL_LOGI("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\r\n");

    for (i = 0; i < 128; i += 16) {
        BL_LOGI("%02x: ", i);
        for(j = 0; j < 16; j++) {
            /* Skip unwanted addresses */
            if (i+j < first || i+j > last) {
                BL_LOGI("   ");
                continue;
            }

            ret = SCCB_Probe(i + j);
            if (ret < 0) {
                BL_LOGI("-- ");
            } else {
                BL_LOGI("%02x ", i+j);
                last_acked = i + j;
            }
        }
        BL_LOGI("\r\n");
    }

    if (0 == last_acked) {
        return 0;
    }

    return last_acked;
}

int SCCB_Read(uint8_t slave_addr, uint8_t reg_addr, uint8_t* rdata)
{
    I2C_Transfer_Cfg cfg;

    uint8_t temp = reg_addr;
    cfg.slaveAddr = slave_addr;
    cfg.subAddressSize = 1;
    cfg.subAddress = &temp;
    cfg.dataSize = 1;
    cfg.data = rdata;

    if(SUCCESS == I2C_MasterReceiveBlocking(I2C_ID, &cfg)) {
        return 0;
    } else {
        return -1;
    }
}

int SCCB_Read_Reg16(uint8_t slave_addr, uint16_t reg_addr, uint8_t* rdata)
{
    I2C_Transfer_Cfg cfg;

    uint8_t temp[2] = {reg_addr >> 8, reg_addr & 0xff};
    cfg.slaveAddr = slave_addr;
    cfg.subAddressSize = 2;
    cfg.subAddress = &temp[0];
    cfg.dataSize = 1;
    cfg.data = rdata;

    if(SUCCESS == I2C_MasterReceiveBlocking(I2C_ID, &cfg)) {
        return 0;
    } else {
        return -1;
    }
}

int SCCB_Write(uint8_t slave_addr, uint8_t reg_addr, uint8_t data)
{
    I2C_Transfer_Cfg cfg;

    cfg.slaveAddr = slave_addr;
    cfg.subAddressSize = 1;
    cfg.subAddress = &reg_addr;
    cfg.dataSize = 1;
    cfg.data = &data;

    if (SUCCESS == I2C_MasterSendBlocking(I2C_ID, &cfg)){
         return 0;
    } else {
        return -1;
    }
}

int SCCB_Write_Reg16(uint8_t slave_addr, uint16_t reg_addr, uint8_t data)
{
    I2C_Transfer_Cfg cfg;
    uint8_t temp[2] = {reg_addr >> 8, reg_addr & 0xff};

    cfg.slaveAddr = slave_addr;
    cfg.subAddressSize = 2;
    cfg.subAddress = &temp[0];
    cfg.dataSize = 1;
    cfg.data = &data;

    if (SUCCESS == I2C_MasterSendBlocking(I2C_ID, &cfg)){
         return 0;
    } else {
        return -1;
    }
}

#else // USING_HW_I2C_SCCB

/** @addtogroup  I2C_GPIO_SIM
 *  @{
 */

void ATTR_TCM_SECTION BL60X_Delay_US_MY(void)
{
    volatile uint32_t i=200;
    while(i--);
}

/** @defgroup  I2C_GPIO_SIM_Private_Macros
 *  @{
 */
#define SCL_H                   GLB_GPIO_Write(sclPin,1)
#define SCL_L                   GLB_GPIO_Write(sclPin,0)
#define SDA_H                   GLB_GPIO_Write(sdaPin,1)
#define SDA_L                   GLB_GPIO_Write(sdaPin,0)
#define SDA_read                GLB_GPIO_Read(sdaPin)
#define I2C_Delay_US(a)         BL60X_Delay_US_MY()

/*@} end of group I2C_GPIO_SIM_Private_Macros */

/** @defgroup  I2C_GPIO_SIM_Private_Types
 *  @{
 */

/*@} end of group I2C_GPIO_SIM_Private_Types */

/** @defgroup  I2C_GPIO_SIM_Private_Variables
 *  @{
 */
//static SemaphoreHandle_t i2c_mutex = NULL;
static GLB_GPIO_Type  sclPin = 20;
static GLB_GPIO_Type  sdaPin = 19;
static uint8_t sda_out=0;

/*@} end of group I2C_GPIO_SIM_Private_Variables */

/** @defgroup  I2C_GPIO_SIM_Global_Variables
 *  @{
 */

/*@} end of group I2C_GPIO_SIM_Global_Variables */

/** @defgroup  I2C_GPIO_SIM_Private_Fun_Declaration
 *  @{
 */

/*@} end of group I2C_GPIO_SIM_Private_Fun_Declaration */

/** @defgroup  I2C_GPIO_SIM_Private_Functions
 *  @{
 */

/*@} end of group I2C_GPIO_SIM_Private_Functions */

/** @defgroup  I2C_GPIO_SIM_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  I2C GPIO init function
 *
 * @param  sclGPIOPin: I2C SCL GPIO pin
 * @param  sdaGPIOPin: I2C SDA GPIO pin
 *
 * @return None
 *
*******************************************************************************/
void I2C_GPIO_Sim_Init(GLB_GPIO_Type sclGPIOPin,GLB_GPIO_Type  sdaGPIOPin)
{
    GLB_GPIO_Cfg_Type cfg;
    uint8_t gpiopins[2];
    uint8_t gpiofuns[2];
    int i;

    sclPin=sclGPIOPin;
    sdaPin=sdaGPIOPin;

    cfg.pullType=GPIO_PULL_UP;
    cfg.drive=1;
    cfg.smtCtrl=1;
    cfg.gpioMode=GPIO_MODE_OUTPUT;

    gpiopins[0]=sclPin;
    gpiopins[1]=sdaPin;
    gpiofuns[0]=11;
    gpiofuns[1]=11;

    for(i=0;i<sizeof(gpiopins)/sizeof(gpiopins[0]);i++){
        cfg.gpioPin=gpiopins[i];
        cfg.gpioFun=gpiofuns[i];
        GLB_GPIO_Init(&cfg);
    }
}

/****************************************************************************//**
 * @brief  I2C SDA out function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
static void I2C_SDA_OUT(void)
{
    GLB_GPIO_Cfg_Type cfg;

    if(sda_out==1){
        return;
    }
    cfg.pullType=GPIO_PULL_UP;
    cfg.drive=1;
    cfg.smtCtrl=1;
    cfg.gpioMode=GPIO_MODE_OUTPUT;
    cfg.gpioPin=sdaPin;
    cfg.gpioFun=11;

    GLB_GPIO_Init(&cfg);

    sda_out=1;
}

/****************************************************************************//**
 * @brief  I2C SDA in function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
static void I2C_SDA_IN(void)
{
    GLB_GPIO_Cfg_Type cfg;

    if(sda_out==0){
        return;
    }
    cfg.pullType=GPIO_PULL_UP;
    cfg.drive=1;
    cfg.smtCtrl=1;
    cfg.gpioMode=GPIO_MODE_INPUT;
    cfg.gpioPin=sdaPin;
    cfg.gpioFun=11;

    GLB_GPIO_Init(&cfg);

    sda_out=0;
}

/****************************************************************************//**
 * @brief  I2C start function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void I2C_Start(void)
{
    I2C_SDA_OUT();
    SDA_H;
    SCL_H;
    I2C_Delay_US(10);
    SDA_L;
    I2C_Delay_US(10);
    SCL_L;
}

/****************************************************************************//**
 * @brief  I2C stop function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void I2C_Stop(void)
{
    I2C_SDA_OUT();
    SCL_L;
    SDA_L;
    SCL_H;
    I2C_Delay_US(10);
    SDA_H;
    I2C_Delay_US(10);
}

/****************************************************************************//**
 * @brief  I2C ack function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
static void I2C_Ack(void)
{
    SCL_L;
    I2C_SDA_OUT();
    SDA_L;
    I2C_Delay_US(10);
    SCL_H;
    I2C_Delay_US(10);
    SCL_L;
}

/****************************************************************************//**
 * @brief  I2C no ack function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
static void I2C_NoAck(void)
{
    SCL_L;
    I2C_SDA_OUT();
    I2C_Delay_US(10);
    SDA_H;
    I2C_Delay_US(10);
    SCL_H;
    I2C_Delay_US(10);
    SCL_L;
}

/****************************************************************************//**
 * @brief  I2C get ack function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
uint8_t I2C_GetAck(void)
{
    uint8_t time = 0;

    I2C_SDA_IN();

    SDA_H;
    I2C_Delay_US(10);
    SCL_H;
    I2C_Delay_US(10);
    while(SDA_read){
        time++;
        if(time > 250){
            SCL_L;
            return 0;
        }
    }
    SCL_L;

    return 1;
}

/****************************************************************************//**
 * @brief  I2C send byte function
 *
 * @param  Data: send data
 *
 * @return None
 *
*******************************************************************************/
void I2C_SendByte(uint8_t Data)
{
    uint8_t cnt;

    I2C_SDA_OUT();

    for(cnt=0; cnt<8; cnt++){
        SCL_L;
        I2C_Delay_US(1);
        if(Data & 0x80){
            SDA_H;
        }
        else{
            SDA_L;
        }
        Data <<= 1;
        SCL_H;
        I2C_Delay_US(1);
    }
    SCL_L;

    I2C_Delay_US(1);
}

/****************************************************************************//**
 * @brief  I2C read byte function
 *
 * @param  ack: i2c ack byte
 *
 * @return None
 *
*******************************************************************************/
uint8_t I2C_ReadByte(uint8_t ack)
{
    uint8_t cnt;
    uint8_t data=0;

    I2C_SDA_IN();

    for(cnt=0; cnt<8; cnt++){
        SCL_L;
        I2C_Delay_US(1);

        SCL_H;
        data <<= 1;
        if(SDA_read){
            data |= 0x01;
        }
        I2C_Delay_US(1);
    }
    if(ack == 1){
        I2C_Ack();
    }
    else{
        I2C_NoAck();
    }

    return data;
}

/****************************************************************************//**
 * @brief  SCCB init function
 *
 * @param  sclGPIOPin: I2C SCL GPIO pin
 * @param  sdaGPIOPin: I2C SDA GPIO pin
 *
 * @return None
 *
*******************************************************************************/
GLB_GPIO_Type sclGPIOPin = GLB_GPIO_PIN_20;
GLB_GPIO_Type sdaGPIOPin = GLB_GPIO_PIN_19;

int SCCB_Init(void)
{
#if 0
    if (NULL == i2c_mutex) {
        i2c_mutex = xSemaphoreCreateMutex();
        if (NULL == i2c_mutex) {
            printf("create i2c_mutex fail\r\n");
            while(1);
        }
    }
#endif
    I2C_GPIO_Sim_Init(sclGPIOPin,sdaGPIOPin);
    return 0;
}

static int SCCB_Probe(uint8_t slv_addr)
{
    int ret = 0;
    //xSemaphoreTake(i2c_mutex, portMAX_DELAY);
    I2C_Start();

    I2C_SendByte((slv_addr<<1)|0);
    if(!I2C_GetAck()){
        I2C_Stop();
        ret = -1;
        goto exit;
    }

    I2C_Stop();

exit:
    //xSemaphoreGive(i2c_mutex);
    return ret;
}


int SCCB_Scan(int first, int last)
{
    printf("-------------------scan_i2c_bus--------------------\r\n");
    int i, j;
    int ret;
    uint8_t last_acked = 0;

    printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\r\n");

    for (i = 0; i < 128; i += 16) {
        printf("%02x: ", i);
        for(j = 0; j < 16; j++) {
            /* Skip unwanted addresses */
            if (i+j < first || i+j > last) {
                printf("   ");
                continue;
            }

            ret = SCCB_Probe(i + j);
            if (ret < 0) {
                printf("-- ");
            } else {
                printf("%02x ", i+j);
                last_acked = i + j;
            }
        }
        printf("\r\n");
    }

    if (0 == last_acked) {
        return 0;
    }

    return last_acked;
}

/****************************************************************************//**
 * @brief  SCCB write function
 *
 * @param  slave_addr: salve addr
 * @param  data: write data
 * @param  wrsize: write data len
 *
 * @return None
 *
*******************************************************************************/
int SCCB_Write(uint8_t slave_addr, uint8_t reg_addr, uint8_t data)
{
    int ret = 0;
    //xSemaphoreTake(i2c_mutex, portMAX_DELAY);
    I2C_Start();

    I2C_SendByte((slave_addr<<1)|0);
    if(!I2C_GetAck()){
        I2C_Stop();
        ret = -1;
        goto exit;
    }

    I2C_SendByte(reg_addr);

    if(!I2C_GetAck()){
        I2C_Stop();
        ret = -1;
        goto exit;
    }

    I2C_SendByte(data);

    if(!I2C_GetAck()){
        I2C_Stop();
        ret = -1;
        goto exit;
    }

    I2C_Stop();
exit:
    //xSemaphoreGive(i2c_mutex);
    return ret;
}

int SCCB_Write_Reg16(uint8_t slave_addr, uint16_t reg_addr, uint8_t data)
{
    int ret = 0;
    //xSemaphoreTake(i2c_mutex, portMAX_DELAY);
    I2C_Start();

    I2C_SendByte((slave_addr<<1)|0);
    if(!I2C_GetAck()){
        I2C_Stop();
        ret = -1;
        goto exit;
    }

    I2C_SendByte((reg_addr >> 8) & 0xff);

    if(!I2C_GetAck()){
        I2C_Stop();
        ret = -1;
        goto exit;
    }

    I2C_SendByte(reg_addr & 0xff);

    if(!I2C_GetAck()){
        I2C_Stop();
        ret = -1;
        goto exit;
    }

    I2C_SendByte(data);

    if(!I2C_GetAck()){
        I2C_Stop();
        ret = -1;
        goto exit;
    }

    I2C_Stop();

exit:
    //xSemaphoreGive(i2c_mutex);
    return ret;
}
/****************************************************************************//**
 * @brief  SCCB read function
 *
 * @param  slave_addr: salve addr
 * @param  data: read data
 * @param  rdsize: read data len
 *
 * @return None
 *
*******************************************************************************/
int SCCB_Read(uint8_t slave_addr, uint8_t reg_addr, uint8_t* rdata)
{
    int ret = 0;
    //xSemaphoreTake(i2c_mutex, portMAX_DELAY);

    I2C_Start();

    I2C_SendByte((slave_addr<<1)|0);
    if(!I2C_GetAck()){
        I2C_Stop();
        ret = -1;
        goto exit;
    }

    I2C_SendByte(reg_addr);

    if(!I2C_GetAck()){
        I2C_Stop();
        ret = -1;
        goto exit;
    }

    I2C_Stop();

    I2C_Start();

    I2C_SendByte((slave_addr<<1)|1);
    if(!I2C_GetAck()){
        I2C_Stop();
        ret = -1;
        goto exit;
    }

    *rdata=I2C_ReadByte(0);

    I2C_Stop();

exit:
    //xSemaphoreGive(i2c_mutex);
    return ret;
}

int SCCB_Read_Reg16(uint8_t slave_addr, uint16_t reg_addr, uint8_t* rdata)
{
    int ret = 0;
    //xSemaphoreTake(i2c_mutex, portMAX_DELAY);

    I2C_Start();

    I2C_SendByte((slave_addr<<1)|0);
    if(!I2C_GetAck()){
        I2C_Stop();
        ret = -1;
        goto exit;
    }

    I2C_SendByte((reg_addr >> 8) & 0xff);

    if(!I2C_GetAck()){
        I2C_Stop();
        ret = -1;
        goto exit;
    }

    I2C_SendByte(reg_addr & 0xff);

    if(!I2C_GetAck()){
        I2C_Stop();
        ret = -1;
        goto exit;
    }

    I2C_Stop();

    I2C_Start();

    I2C_SendByte((slave_addr<<1)|1);
    if(!I2C_GetAck()){
        I2C_Stop();
        ret = -1;
        goto exit;
    }

    *rdata = I2C_ReadByte(0);

    I2C_Stop();

exit:
    //xSemaphoreGive(i2c_mutex);
    return ret;
}
#endif // USING_HW_I2C_SCCB

uint8_t SCCB_Read_Dbg(uint8_t slv_addr, uint8_t reg_addr)
{
    uint8_t val;
    BL_LOGD("SCCB_Read_Dbg [0x%02X] 0x%04x ...\r\r\n", slv_addr, reg_addr);

    SCCB_Read(slv_addr, reg_addr, &val);

    return val;
}

uint8_t SCCB_Read_Reg16_Dbg(uint8_t slv_addr, uint16_t reg_addr)
{
    uint8_t val;
    BL_LOGD("SCCB_Read_Reg16_Dbg [0x%02X] 0x%04x ...\r\r\n", slv_addr, reg_addr);

    SCCB_Read_Reg16(slv_addr, reg_addr, &val);

    return val;
}


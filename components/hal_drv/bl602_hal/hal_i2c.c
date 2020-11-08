/*
 * Copyright (c) 2020 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <aos/yloop.h>
#include <looprt.h>
#include <loopset.h>
#include <loopset_i2c.h>

#include <bl602.h>
#include <bl_i2c.h>
#include <bl602_i2c.h>
#include <bl_irq.h>
#include <hal_i2c.h>
#include <blog.h>

i2c_msg_t *gpstmsg;
SemaphoreHandle_t i2c_hd_handle = NULL;
SemaphoreHandle_t i2c_msgs_handle = NULL;
SemaphoreHandle_t i2c_transfer_handle = NULL;
SemaphoreHandle_t i2c_loop_handle = NULL;
SemaphoreHandle_t i2c_insert_handle = NULL;

static void i2c_callback(i2c_msg_t *pstmsg)
{
    BaseType_t xHigherPriorityTaskWoken;
    I2C_Disable(pstmsg->i2cx);
    I2C_IntMask(pstmsg->i2cx, I2C_INT_ALL, MASK);
    i2c_clear_status(pstmsg->i2cx);
    if (pstmsg->block == I2C_M_NO_BLOCK) {
        i2c_async_trigger(pstmsg, POST_FLAG);
        if (pstmsg->direct == I2C_M_WRITE) {
            vPortFree(pstmsg->buf);
            vPortFree(pstmsg);
        }
    }
    xSemaphoreGiveFromISR(i2c_hd_handle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    if (pstmsg->block == I2C_M_NO_BLOCK) {
        xSemaphoreGiveFromISR(i2c_transfer_handle, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
    return;
}

static void i2c_transferbytes(i2c_msg_t *pstmsg)
{
    if ((pstmsg->direct == I2C_M_WRITE) && (pstmsg->event = EV_I2C_TXF_INT)) {
        if (pstmsg->idex < pstmsg->len) {
            do_write_data(pstmsg);
        } else if (pstmsg->idex == pstmsg->len) {
            I2C_IntMask(pstmsg->i2cx, I2C_TX_FIFO_READY_INT, MASK);
            return;
        } else {
        }
    } else if ((pstmsg->direct == I2C_M_READ) && (pstmsg->event = EV_I2C_RXF_INT)){
        if (pstmsg->idex < pstmsg->len) {
             do_read_data(pstmsg);
        } else {
            I2C_IntMask(pstmsg->i2cx, I2C_RX_FIFO_READY_INT, MASK);
            return;
        }
    } else {
    }

    return;
}

static void i2c_interrupt_entry(void *ctx)
{
    uint32_t tmpval;
    i2c_msg_t *pstmsg;

    pstmsg = *((i2c_msg_t **)ctx);

    tmpval = BL_RD_REG(I2C_BASE, I2C_INT_STS);
    if(BL_IS_REG_BIT_SET(tmpval,I2C_RXF_INT)){
        pstmsg->event = EV_I2C_RXF_INT;
    } else if(BL_IS_REG_BIT_SET(tmpval, I2C_END_INT)){
        pstmsg->event = EV_I2C_END_INT;
        i2c_callback(pstmsg);
        return;
    } else if(BL_IS_REG_BIT_SET(tmpval, I2C_NAK_INT)){
        pstmsg->event = EV_I2C_NAK_INT;
        i2c_callback(pstmsg);
        return;
    } else if(BL_IS_REG_BIT_SET(tmpval, I2C_TXF_INT)){
        pstmsg->event = EV_I2C_TXF_INT;
    } else if(BL_IS_REG_BIT_SET(tmpval, I2C_ARB_INT)){
        pstmsg->event = EV_I2C_ARB_INT;
        i2c_callback(pstmsg);
        return;
    } else if(BL_IS_REG_BIT_SET(tmpval,I2C_FER_INT)){
        pstmsg->event = EV_I2C_FER_INT;
        i2c_callback(pstmsg);
        return;
    } else {
        blog_error("other interrupt \r\n");
        pstmsg->event = EV_I2C_UNKNOW_INT;
        i2c_callback(pstmsg);
    }

    i2c_transferbytes(pstmsg);
    return;
}

int i2c_transfer_block(i2c_msg_t *pstmsg)
{
    xSemaphoreTake(i2c_transfer_handle, portMAX_DELAY);
    xSemaphoreTake(i2c_hd_handle, portMAX_DELAY);
    pstmsg->block = 0;
    gpstmsg = pstmsg;

    i2c_transfer_start(pstmsg);
    xSemaphoreTake(i2c_hd_handle, portMAX_DELAY);
    if (pstmsg->event == EV_I2C_END_INT) {
        blog_info("i2c transfer success \r\n");
    } else {
        blog_error("i2c transfer error, event = %d \r\n", pstmsg->event);
    }

    xSemaphoreGive(i2c_hd_handle);
    xSemaphoreGive(i2c_transfer_handle);

    return pstmsg->event;
}

int i2c_transfer_no_block(i2c_msg_t *pstmsg)
{
    uint8_t *pbuf;
    i2c_msg_t *psttmp;
    xSemaphoreTake(i2c_transfer_handle, portMAX_DELAY);
    xSemaphoreTake(i2c_hd_handle, portMAX_DELAY);
    gpstmsg = pstmsg;
    psttmp = pvPortMalloc(sizeof(i2c_msg_t));

    if (psttmp == NULL) {
        blog_error("malloc failed. \r\n");
        return -1;
    }
    memcpy(psttmp, pstmsg, (sizeof(i2c_msg_t)));
    if (pstmsg->direct == I2C_M_WRITE) {
        pbuf = pvPortMalloc(pstmsg->len);
        if (pbuf == NULL) {
            blog_error("buf alloc failed. len = %ld \r\n", pstmsg->len);
        }
        memcpy(pbuf , pstmsg->buf, pstmsg->len);
        psttmp->buf = pbuf;
    } else if (pstmsg->direct == I2C_M_READ) {
        psttmp->buf = pstmsg->buf;
    } else {
    }
    gpstmsg = psttmp;
    i2c_transfer_start(gpstmsg);
    return 0;
}

void i2c_msgs_process(i2c_msg_t *pstmsg)
{
    i2c_transfer_block(pstmsg);
    xSemaphoreGive(i2c_loop_handle);

    return;
}

void i2c_insert_msgs_process(i2c_msg_t *pstmsg)
{
    int i;
    int ret = 0;

    for (i = 0; i < pstmsg->ins_num; i++) {
        //need restart?
        ret = i2c_transfer_block(pstmsg + i);
        if (ret != 0) {
            blog_error("transfer error ret = %d \r\n", ret);
            break;
        }
    }
    xSemaphoreGive(i2c_loop_handle);
    xSemaphoreGive(i2c_insert_handle);

    return;
}

static void i2c_msg_space_func(i2c_msg_t *pstmsg, int i)//not support now
{
    if (i == 0) {
            /*start*/
    } else if (pstmsg[i - 1].direct != pstmsg[i].direct || pstmsg[i - 1].addr != pstmsg[i].addr) {
            /*restart*/
    } else {
    }
}

int i2c_transfer_msgs_block(i2c_msg_t *pstmsg, int num, int support_ins)
{
    int i;

    xSemaphoreTake(i2c_msgs_handle, portMAX_DELAY);
    if (support_ins == 0) {
        xSemaphoreTake(i2c_insert_handle, portMAX_DELAY);
    }
    for (i = 0; i < num; i++) {
        xSemaphoreTake(i2c_loop_handle, portMAX_DELAY);
        if (i > 0 && (pstmsg + i - 1)->event != 0) {
            blog_error("transfer error, num = %d event = %d \r\n", i - 1, (pstmsg + i - 1)->event);
            break;
        }
        i2c_msg_space_func(pstmsg, i);
        i2c_async_trigger(pstmsg + i, 0);
    }
    if ((pstmsg + i -1)->stop == 1) {
        /* stop, not support now */
    }
    xSemaphoreTake(i2c_loop_handle, portMAX_DELAY);
    xSemaphoreGive(i2c_loop_handle);
    if (support_ins == 0) {
        xSemaphoreGive(i2c_insert_handle);
    }
    xSemaphoreGive(i2c_msgs_handle);

    return (pstmsg + i - 1)->event;
}

int i2c_insert_transfer_msgs(i2c_msg_t *pstmsg, int num)
{
    xSemaphoreTake(i2c_insert_handle, portMAX_DELAY);
    xSemaphoreTake(i2c_loop_handle, portMAX_DELAY);
    pstmsg->ins_num = num;
    i2c_async_trigger(pstmsg, 1);
    xSemaphoreTake(i2c_loop_handle, portMAX_DELAY);
    xSemaphoreGive(i2c_loop_handle);
    xSemaphoreGive(i2c_insert_handle);

    return 0;
}

int i2c_transfer_onemsg_no_block(i2c_msg_t *pstmsg)
{
    i2c_transfer_no_block(pstmsg);
    return 0;
}

int hal_i2c_init(int i2cx, int freq)
{
    i2c_gpio_init(i2cx);
    i2c_set_freq(freq, i2cx);
    I2C_Disable(i2cx);
    bl_irq_enable(I2C_IRQn);
    I2C_IntMask(i2cx, I2C_INT_ALL, MASK);

    i2c_hd_handle = xSemaphoreCreateBinary();
    i2c_msgs_handle = xSemaphoreCreateMutex();
    i2c_transfer_handle = xSemaphoreCreateBinary();
    i2c_loop_handle = xSemaphoreCreateBinary();
    i2c_insert_handle = xSemaphoreCreateBinary();
    if (i2c_hd_handle == NULL || i2c_msgs_handle == NULL || i2c_transfer_handle == NULL || i2c_loop_handle == NULL || i2c_insert_handle == NULL) {
        blog_error("create sem failed \r\n");
        return -1;
    }

    xSemaphoreGive(i2c_hd_handle);
    xSemaphoreGive(i2c_msgs_handle);
    xSemaphoreGive(i2c_transfer_handle);
    xSemaphoreGive(i2c_loop_handle);
    xSemaphoreGive(i2c_insert_handle);
    bl_irq_register_with_ctx(I2C_IRQn, i2c_interrupt_entry, &gpstmsg);

    return 0;
}

int hal_i2c_read_block(int address, char *data, int length, int subaddr_len, int subaddr)
{
    i2c_msg_t msg;
    int ret = 0;

    msg.addr = address;
    msg.buf = (uint8_t *)data;
    msg.len = length;
    msg.direct = I2C_M_READ;
    msg.block = I2C_M_BLOCK;
    msg.idex = 0;
    msg.i2cx = 0;

    if (subaddr > 0) {
        msg.subflag = 1;
        msg.subaddr = subaddr;
        msg.sublen = subaddr_len;
    } else {
        msg.subflag = 0;
    }

    ret = i2c_transfer_msgs_block(&msg, 1, 0);

    return ret;
}

int hal_i2c_write_block(int address, const char *data, int length, int subaddr_len, int subaddr)
{
    i2c_msg_t msg;
    int ret = 0;

    msg.addr = address;
    msg.buf = (uint8_t *)data;
    msg.len = length;
    msg.direct = I2C_M_WRITE;
    msg.block = I2C_M_BLOCK;
    msg.idex = 0;
    msg.i2cx = 0;

    if (subaddr > 0) {
        msg.subflag = 1;
        msg.subaddr = subaddr;
        msg.sublen = subaddr_len;
    } else {
        msg.subflag = 0;
    }

    ret = i2c_transfer_msgs_block(&msg, 1, 0);

    return ret;
}

int hal_i2c_write_no_block(int address, const char *data, int length, int subaddr_len, int subaddr)
{
    i2c_msg_t msg;

    msg.addr = address;
    msg.buf = (uint8_t *)data;
    msg.len = length;
    msg.direct = I2C_M_WRITE;
    msg.block = I2C_M_NO_BLOCK;
    msg.idex = 0;
    msg.i2cx = 0;

    if (subaddr > 0) {
        msg.subflag = 1;
        msg.subaddr = subaddr;
        msg.sublen = subaddr_len;
    } else {
        msg.subflag = 0;
    }

    i2c_transfer_onemsg_no_block(&msg);

    return 0;
}

int hal_i2c_read_no_block(int address, const char *data, int length, int subaddr_len, int subaddr)
{
    i2c_msg_t msg;

    msg.addr = address;
    msg.buf = (uint8_t *)data;
    msg.len = length;
    msg.direct = I2C_M_READ;
    msg.block = I2C_M_NO_BLOCK;
    msg.idex = 0;
    msg.i2cx = 0;

    if (subaddr > 0) {
        msg.subflag = 1;
        msg.subaddr = subaddr;
        msg.sublen = subaddr_len;
    } else {
        msg.subflag = 0;
    }

    i2c_transfer_onemsg_no_block(&msg);

    return 0;
}

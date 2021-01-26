/*----------------------------------------------------------------------------
 * Copyright (c) <2018>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/


#ifndef __EC2X_OC_H
#define __EC2X_OC_H


///< THE BASIC FUNCTION FOR THE EC2X
///< RETURN:0 SUCCESS WHILE -1 FAILED
///< USE THIS FUCNTION TO GET THE TIME, THE FORMAT IS:
///< 2019/12/13/,10:17:31 GTM+8
int ec2x_get_time(char *timebuffer);
int ec2x_get_csq(int *csq);
int ec2x_get_rssi(int *rssi);
int ec2x_get_operator(char *buf);

///< register the ec2x oc mqtt function to the system
int oc_mqtt_imp_init(void);


///< iccid list
#define CN_ICCID_MAX_LEN  24
#define CN_ICCID_MAX_NUM  6
#define CN_ICCID_COPS_LEN 12
#define CN_EID_MAX_LEN    34
typedef struct
{
    int   type;
    int   status;
    char  id[CN_ICCID_MAX_LEN];
}iccid_t;

typedef struct
{
    int         num;
    iccid_t  iccid[CN_ICCID_MAX_NUM];
}iccid_tab_t;

typedef struct
{
    char id[CN_EID_MAX_LEN];
}eid_t;

#define CN_EC2X_VERSION_LEN_MAX    64
typedef struct
{
    char ver[CN_EC2X_VERSION_LEN_MAX];
}ec2x_ver_t;
int ec2x_geticcidtab(iccid_tab_t  *tab);
int ec2x_eniccid(iccid_t *iccid);
int ec2x_geteid(eid_t *eid);
int ec2x_getmqttversion(ec2x_ver_t *ver);
int ec2x_echoset(int mode);
int ec2x_hwsimset(int mode);
int ec2x_cpin(void);
int ec2x_cgatt(int *cgatt);
int ec2x_cgreg(int *n,int *status);

#endif /* __BOUDICA150_OC_H */

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


#ifndef __OC_COAP_AL_H
#define __OC_COAP_AL_H


#include <stddef.h>
#include <stdint.h>
//#include <coap_al.h>

/** @brief this is the message dealer module for the application*/
typedef int (*fn_oc_coap_msg_deal)(void *msg, int len);

typedef enum
{
    en_oc_boot_strap_mode_factory = 0,
    en_oc_boot_strap_mode_client_initialize,
    en_oc_boot_strap_mode_sequence,
}en_oc_boot_strap_mode_t;

typedef struct
{
    char *ep_id;                  ///< endpoint identifier, which could be recognized by the server
    char *address;                ///< server address,maybe domain name
    char *port;                   ///< server port
    char *psk_id;                 ///< server encode by psk, if not set NULL here
    char *psk;
    int   psk_len;
}oc_server_t;

/** @brief this is the agent configuration */
typedef struct
{
    en_oc_boot_strap_mode_t  boot_mode;       ///< bootmode,if boot client_initialize, then the bs must be set
    oc_server_t              boot_server;     ///< which will be used by the bootstrap, if not, set NULL here
    oc_server_t              app_server;      ///< if factory or smart boot, must be set here
    fn_oc_coap_msg_deal      rcv_func;        ///< receive function caller here
    void                    *usr_data;        ///< used for the user
}oc_config_param_t;

typedef enum
{
    en_oc_coap_err_ok          = 0,      ///< this means the status ok
    en_oc_coap_err_parafmt,              ///< this means the parameter err format
    en_oc_coap_err_network,              ///< this means the network wrong status
    en_oc_coap_err_conserver,            ///< this means the server refused the service for some reason(likely the id and pwd)
    en_oc_coap_err_noconfigured,         ///< this means we have not configure it yet,so could not connect
    en_oc_coap_err_configured,           ///< this means we has configured it, so could not reconfigure it
    en_oc_coap_err_noconected,           ///< this means the connection has not been built, so you could not send data
    en_oc_coap_err_gethubaddrtimeout,    ///< this means get the hub address timeout
    en_oc_coap_err_sysmem,               ///< this means the system memory is not enough
    en_oc_coap_err_system,               ///< this means that the system porting may have some problem,maybe not install yet
    en_oc_coap_err_last,
}en_oc_coap_err_code_t;
///////////////////////////COAP AGENT INTERFACE////////////////////////////////
typedef void* (*fn_oc_coap_config)(oc_config_param_t *param);                        ///< return the handle here
typedef int (*fn_oc_coap_deconfig)(void *handle);                                    ///< use the handle as the params
typedef int (*fn_oc_coap_report)(void *handle,char *msg,int len);                    ///< use the handle and report params
/**
 * @brief this data structure defines the coap agent implement
 */
typedef struct
{
    fn_oc_coap_config   config;   ///< this function used for the configuration
    fn_oc_coap_report   report;   ///< this function used for the report data to the cdp
    fn_oc_coap_deconfig deconfig; ///< this function used for the deconfig
}oc_coap_opt_t;

/**
 *@brief the coap agent should use this function to register the method for the application
 *
 *@param[in] opt, the operation method implement by the coap agent developer
 *@return 0 success while -1 failed
 */
int oc_coap_register(const char *name,const oc_coap_opt_t *opt);


//////////////////////////APPLICATION INTERFACE/////////////////////////////////

/**
 * @brief the application use this function to configure the coap agent
 * @param[in] param, refer to tag_oc_coap_config
 * @return oc coap handle else NULL failed
 */
void *oc_coap_config(oc_config_param_t *param);
/**
 * @brief the application use this function to send the message to the cdp
 * @param[in] hanlde:the coap handle returned by oc_coap_config
 * @param[in] report:the message to report
 *
 * @return 0 success while <0 failed
 */
int oc_coap_report(void *handle,char *msg,int len);

/**
 *@brief: the application use this function to deconfigure the coap agent
 *
 *@param[in] handle: returned by oc_coap_config
 *
 * return 0 success while <0 failed
 */

int oc_coap_deconfig(void *handle);

/**
 *@brief this is the oc coap  initialize function,must be called first
 *
 *@return 0 success while <0 failed
 */
int oc_coap_init();


#endif /* __OC_COAP_AL_H */

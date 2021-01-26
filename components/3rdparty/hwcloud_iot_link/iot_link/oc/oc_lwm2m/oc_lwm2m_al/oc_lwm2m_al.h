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

#ifndef LITEOS_LAB_IOT_LINK_OC_OC_LWM2M_OC_LWM2M_AL_OC_LWM2M_AL_H_
#define LITEOS_LAB_IOT_LINK_OC_OC_LWM2M_OC_LWM2M_AL_OC_LWM2M_AL_H_


#include <stddef.h>
#include <stdint.h>

typedef struct
{
    char *ep_id;                  ///< endpoint identifier, which could be recognized by the server
    char *address;                ///< server address,maybe domain name
    char *port;                   ///< server port
    char *psk_id;                 ///< server encode by psk, if not set NULL here
    char *psk;
    int   psk_len;
} oc_server_t;


typedef enum
{
    en_oc_boot_strap_mode_factory = 0,
    en_oc_boot_strap_mode_client_initialize,
    en_oc_boot_strap_mode_sequence,
} en_oc_boot_strap_mode_t;


typedef enum
{
    EN_OC_LWM2M_MSG_APPWRITE = 0,  ///< we have received the application command data
    EN_OC_LWM2M_MSG_APPDISCOVER,
    EN_OC_LWM2M_MSG_APPEXECUTE,
    EN_OC_LWM2M_MSG_SERVERREBS,    ///<we  have received the rebootstrap command from the platform
} en_oc_lwm2m_msg_t;

/** @brief this is the message dealer module for the application*/
typedef int (*fn_oc_lwm2m_msg_deal)(void *usr_data, en_oc_lwm2m_msg_t type, void *msg, int len);

/** @brief this is the agent configuration */
typedef struct
{
    en_oc_boot_strap_mode_t  boot_mode;       ///< bootmode,if boot client_initialize, then the bs must be set
    oc_server_t              boot_server;     ///< which will be used by the bootstrap, if not, set NULL here
    oc_server_t              app_server;      ///< if factory or smart boot, must be set here
    fn_oc_lwm2m_msg_deal     rcv_func;        ///< receive function caller here
    void                    *usr_data;        ///< used for the user
} oc_config_param_t;


typedef enum
{
    en_oc_lwm2m_err_ok          = 0,      ///< this means the status ok
    en_oc_lwm2m_err_parafmt,              ///< this means the parameter err format
    en_oc_lwm2m_err_network,              ///< this means the network wrong status
    en_oc_lwm2m_err_conserver,            ///< this means the server refused the service for some reason(likely the id and pwd)
    en_oc_lwm2m_err_noconfigured,         ///< this means we have not configure it yet,so could not connect
    en_oc_lwm2m_err_configured,           ///< this means we has configured it, so could not reconfigure it
    en_oc_lwm2m_err_noconected,           ///< this means the connection has not been built, so you could not send data
    en_oc_lwm2m_err_gethubaddrtimeout,    ///< this means get the hub address timeout
    en_oc_lwm2m_err_sysmem,               ///< this means the system memory is not enough
    en_oc_lwm2m_err_system,               ///< this means that the system porting may have some problem,maybe not install yet
    en_oc_lwm2m_err_last,
}en_oc_lwm2m_err_code_t;

///////////////////////////LWM2M AGENT INTERFACE////////////////////////////////
typedef int (*fn_oc_lwm2m_report)(char *buf, int len, int timeout);
typedef int (*fn_oc_lwm2m_config)(oc_config_param_t *param);
typedef int (*fn_oc_lwm2m_deconfig)(void);
/**
 * @brief this data structure defines the lwm2m agent implement
 */
typedef struct
{
    fn_oc_lwm2m_config   config;   ///< this function used for the configuration
    fn_oc_lwm2m_report   report;   ///< this function used for the report data to the cdp
    fn_oc_lwm2m_deconfig deconfig; ///< this function used for the deconfig
} oc_lwm2m_opt_t;


/**
 *@brief the lwm2m agent should use this function to register the method for the application
 *
 *@param[in] name, the operation method name
 *@param[in] opt, the operation method implement by the lwm2m agent developer
 *@return 0 success while <0 failed
 */
int oc_lwm2m_register(const char *name, const oc_lwm2m_opt_t *opt);

/**
 *@brief the lwm2m agent should use this function to unregister the method for the application
 *
 *@param[in] opt, the operation method implement by the lwm2m agent developer
 *@return 0 success while <0 failed
 */
int oc_lwm2m_unregister(const char *name);

//////////////////////////APPLICATION INTERFACE/////////////////////////////////
/**
 * @brief the application use this function to configure the lwm2m agent
 * @param[in] param, refer to oc_config_param_t
 * @return 0 success while others the error code described as en_oc_lwm2m_err_code_t
 */
int oc_lwm2m_config(oc_config_param_t *param);

/**
 * @brief the application use this function to send the message to the cdp
 * @param[in] buf the message to send
 * @param[in] len the message length
 * @param[in] timeout block time
 * @return 0 success while others the error code described as en_oc_lwm2m_err_code_t
 */
int oc_lwm2m_report(char *buf, int len, int timeout);

/**
 *@brief: the application use this function to deconfigure the lwm2m agent
 *
 * @return 0 success while others the error code described as en_oc_lwm2m_err_code_t
 */

int oc_lwm2m_deconfig(void);

/**
 *@brief this is the oc lwm2m agent initialize function,must be called first
 *
 *@return 0 success while <0 failed
 */
int oc_lwm2m_init();

/*
 * @brief this is the map for the errocode
 *
 * @param code: the error code
 *
 * @return: the string of the code
 *
 * */
const char *oc_lwm2m_errcode(en_oc_lwm2m_err_code_t code);

#endif /* LITEOS_LAB_IOT_LINK_OC_OC_LWM2M_OC_LWM2M_AL_OC_LWM2M_AL_H_ */

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


#include <stdlib.h>
#include <string.h>
#include <link_log.h>
#include <osal.h>
#include <dtls_al.h>
#include <ota_img.h>
#include <ota_flag.h>
#include <ota_https.h>

///< server key
static const char g_https_serverca[] =
" -----BEGIN CERTIFICATE-----\r\n"
"MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh\r\n"
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
"d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\r\n"
"QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT\r\n"
"MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\r\n"
"b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG\r\n"
"9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB\r\n"
"CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97\r\n"
"nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt\r\n"
"43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P\r\n"
"T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4\r\n"
"gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO\r\n"
"BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR\r\n"
"TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw\r\n"
"DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr\r\n"
"hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg\r\n"
"06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF\r\n"
"PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls\r\n"
"YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\r\n"
"CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\r\n"
"-----END CERTIFICATE-----\r\n";


///< build the http request
#define CN_OTA_HTTPS_REQ_FMT  "GET %s HTTP/1.1\r\nAuthorization: Bearer %s\r\nHost: %s:%s\r\n\r\n"
typedef struct
{
    const char *host;
    const char *port;
    const char *url_re;
}ota_https_netpara_t;
static int ota_https_buildreq(ota_https_para_t *cb,ota_https_netpara_t *netpara)
{
    int ret;
    ret = snprintf((char *)cb->cache,CONFIG_OCMQTT_HTTPS_CACHELEN,CN_OTA_HTTPS_REQ_FMT,netpara->url_re,\
                    cb->authorize,netpara->host,netpara->port);
    return ret;
}

///< https://121.36.42.100:8943/iodm/dev/v2.0/upgradefile/applications/qOrU58z7TMg2fao5xceWanjjQSAa/devices/5e12ea0a334dd4f337902dc3_iotlink005/packages/b2731c6b96178488a8862ace
#define CN_URL_HOST_INDEX "https://"
#define CN_URL_PORT_INDEX ":"
#define CN_URL_PORT_DEFAULT "443"
static ota_https_netpara_t *ota_https_getnetpara(ota_https_para_t *cb)
{
    ota_https_netpara_t *ret = NULL;
    const char *host_start;
    const char *host_end;
    const char *port_start;
    const char *port_end;
    const char *urlre_start;
    const char *urlre_end;
    char *tmp,*tmp_ret;
    int  len;

    tmp = (char *)cb->url;
    tmp_ret = strstr(tmp,CN_URL_HOST_INDEX);
    if(NULL == tmp_ret)
    {
        goto EXIT_HOST;
    }
    host_start = tmp_ret +strlen(CN_URL_HOST_INDEX);

    tmp = (char *)host_start;
    tmp_ret = strstr(tmp,CN_URL_PORT_INDEX);
    if(NULL == tmp_ret)
    {
        port_start = CN_URL_PORT_DEFAULT;
        port_end = port_start + strlen(CN_URL_PORT_DEFAULT) -1;

        tmp_ret = strstr(tmp,"/");
        if(NULL == tmp_ret)
        {
            goto EXIT_PORT;
        }
        host_end = tmp_ret-1;
        urlre_start = tmp_ret;
        urlre_end = cb->url + strlen(cb->url) -1;
    }
    else
    {
        host_end = tmp_ret-1;
        port_start = tmp_ret + 1;
        tmp = tmp_ret;

        tmp_ret = strstr(tmp,"/");
        if(NULL == tmp_ret)
        {
            goto EXIT_PORT;
        }
        port_end = tmp_ret -1;
        urlre_start = tmp_ret;
        urlre_end = cb->url + strlen(cb->url) -1;
    }
    len = sizeof(ota_https_netpara_t) + (host_end - host_start +1) + (port_end- port_start +1) + (urlre_end - urlre_start + 1);
    tmp = osal_malloc(len);
    if(NULL == tmp)
    {
        goto EXIT_MEM;
    }
    ret = (ota_https_netpara_t *)tmp;
    tmp += sizeof(ota_https_netpara_t);
    ///< initialize the member in the parameters
    len = host_end - host_start + 1;
    memcpy(tmp, host_start, len);
    tmp[len] = '\0';
    ret->host = tmp;
    tmp += len + 1;

    len = port_end - port_start + 1;
    memcpy(tmp, port_start, len);
    tmp[len] = '\0';
    ret->port = tmp;
    tmp += len + 1;

    len = urlre_end - urlre_start + 1;
    memcpy(tmp, urlre_start, len);
    tmp[len] = '\0';
    ret->url_re = tmp;

    return ret;

EXIT_MEM:
EXIT_PORT:
EXIT_HOST:
    return ret;
}

///< return the len write, try to send all the data in the timeout
static int loop_netwrite(void *handle,const uint8_t *buffer, int len,uint32_t timeout)
{
    int sndret;
    const uint8_t *data = buffer;
    while(len > 0)
    {
        sndret = dtls_al_write(handle,(uint8_t *)data,len,timeout);
        if(sndret > 0)
        {
            len -= sndret;
            data += sndret;
        }
        else if(sndret == 0)
        {
            break;
        }
    }
    return (len==0)?0:-1;
}

static int loop_netread(void *handle,uint8_t *buffer, int len,uint32_t timeout)
{
    int rcvret;
    const uint8_t *data = buffer;
    while(len > 0)
    {
        rcvret = dtls_al_read(handle,(uint8_t *)data,len,timeout);
        if(rcvret > 0)
        {
            len -= rcvret;
            data += rcvret;
        }
        else if(rcvret == 0)
        {
            break;
        }
    }

    return (len==0)?0:-1;
}

///< use the state machine to check the header
typedef enum
{
    EN_HEADER_STATUS_NORMAL = 0,
    EN_HEADER_STATUS_R,          ///< which means receive the \r
    EN_HEADER_STATUS_RN,         ///< which means receive the \r\n
    EN_HEADER_STATUS_RNR,        ///< which means receive the \r\n\r
    EN_HEADER_STATUS_RNRN,       ///< which means receive the \r\n\r\n
}en_header_status;

static int loop_dealheader(ota_https_para_t *cb,void *handle)
{
    int ret = -1;
    int offset = 0;
    char cur;
    en_header_status status = EN_HEADER_STATUS_NORMAL;
    while(status != EN_HEADER_STATUS_RNRN)
    {
        ret = loop_netread(handle,(uint8_t *) &cur, 1, CONFIG_OCMQTT_HTTPS_TIMEOUT);
        if(ret != 0)
        {
            break;
        }
        cb->cache[offset ++] = (uint8_t)cur;
        switch (status)
        {
            case EN_HEADER_STATUS_NORMAL:
                if(cur == '\r')
                {
                    status = EN_HEADER_STATUS_R;
                }
                break;
            case EN_HEADER_STATUS_R:
                if(cur == '\n')
                {
                    status = EN_HEADER_STATUS_RN;
                }
                else
                {
                    status = EN_HEADER_STATUS_NORMAL;
                }
                break;
            case EN_HEADER_STATUS_RN:
                if(cur == '\r')
                {
                    status = EN_HEADER_STATUS_RNR;
                }
                else
                {
                    status = EN_HEADER_STATUS_NORMAL;
                }
                break;
            case EN_HEADER_STATUS_RNR:
                if(cur == '\n')
                {
                    status = EN_HEADER_STATUS_RNRN;
                }
                else
                {
                    status = EN_HEADER_STATUS_NORMAL;
                }
                break;
            default:
                break;

        }

    }

    return ret;
}


///< return 0 success while -1 failed;
int ota_https_download(ota_https_para_t *param)
{
    int ret = -1;
    int len;
    void *handle = NULL;
    uint8_t *buf;
    ota_https_netpara_t  *netpara;
    dtls_al_para_t dtls_para;
    ota_flag_t     otaflag;
    ota_flag_t     otaflagclone;


    ///< first we will get the ota flag.
    en_ota_type_t  otatype= param->ota_type;
    if(0 != ota_flag_get(otatype, &otaflag))
    {
        goto EXIT_PARAM;
    }
    otaflag.info.img_download.file_size = param->file_size;
    otaflag.info.img_download.file_off = param->file_offset;
    strncpy((char *)otaflag.info.img_download.ver,param->version,CONFIG_OTA_VERSIONLEN);
    otaflag.info.curstatus = EN_OTA_STATUS_DOWNLOADING;

    netpara = ota_https_getnetpara(param);
    if(NULL == netpara)
    {
        goto EXIT_NETPARA;
    }

    (void) memset( &dtls_para,0, sizeof(dtls_para));
    dtls_para.security.type = EN_DTLS_AL_SECURITY_TYPE_CERT;
    dtls_para.istcp = 1;
    dtls_para.isclient = 1;
    dtls_para.security.u.cert.server_ca = (uint8_t *)g_https_serverca;
    dtls_para.security.u.cert.server_ca_len = sizeof(g_https_serverca);

    if(EN_DTLS_AL_ERR_OK != dtls_al_new(&dtls_para,&handle))
    {
        LINK_LOG_ERROR("TLS HANDLE BUILD ERR");
        goto EXIT_TLSHANDLE;
    }

    ret = dtls_al_connect( handle, netpara->host, netpara->port, CONFIG_OCMQTT_HTTPS_TIMEOUT);
    if (ret != EN_DTLS_AL_ERR_OK)
    {
        LINK_LOG_ERROR("TLS CONNECT ERR");
        goto EXIT_TLSCONNECT;
    }
    ///< send the request
    len = ota_https_buildreq(param,netpara);
    LINK_LOG_DEBUG("HTTPREQ:%d Bytes REQ:%s\r\n",len,param->cache);

    ret = loop_netwrite(handle, param->cache,len,CONFIG_OCMQTT_HTTPS_TIMEOUT);
    if(ret != 0)
    {
        LINK_LOG_ERROR("TLS REQUEST ERR");
        goto EXIT_REQSEND;
    }
    ///< WE SHOULD DEAL THE HTTP HEADER
    ret = loop_dealheader(param,handle);
    if(ret != 0)
    {
        LINK_LOG_ERROR("HTTP HEADER ERR");
        goto EXIT_HTTPHEADER;
    }

    ///< DO THE BODY RECEIVE
    ///< firs we will erase the download area
    ota_img_erase(otatype, EN_OTA_IMG_DOWNLOAD);

    LINK_LOG_DEBUG("HTTP BODY RECEIVE");
    buf = param->cache;
    len = (param->file_size - param->file_offset) > CONFIG_OCMQTT_HTTPS_CACHELEN?CONFIG_OCMQTT_HTTPS_CACHELEN:(param->file_size - param->file_offset);
    do{
        ret = loop_netread(handle, buf,len,CONFIG_OCMQTT_HTTPS_TIMEOUT);
        ///< deal the data
        if(ret == 0)
        {
            LINK_LOG_DEBUG("RCVING:total:%d hasrcved:%d curlen:%d \r\n",param->file_size, param->file_offset,len);
            ret = ota_img_write(otatype, EN_OTA_IMG_DOWNLOAD, otaflag.info.img_download.file_off, buf, len);
            if(0 != ret)
            {
                break;
            }
            param->file_offset += len;
            otaflag.info.img_download.file_off += len;
        }
        buf  = param->cache;
        len = (param->file_size - param->file_offset) > CONFIG_OCMQTT_HTTPS_CACHELEN?CONFIG_OCMQTT_HTTPS_CACHELEN:(param->file_size - param->file_offset);
    }while((ret == 0) && (param->file_size != param->file_offset));
    LINK_LOG_DEBUG("RCVFINISHED:total:%d hasrcved:%d\r\n",param->file_size, param->file_offset);
    if(param->file_size == param->file_offset)
    {
        otaflag.info.curstatus = EN_OTA_STATUS_DOWNLOADED;
        ret = 0;
    }
    (void)ota_img_flush(otatype, EN_OTA_IMG_DOWNLOAD);
    (void)ota_flag_save(otatype,&otaflag);

    ota_flag_get(otatype, &otaflagclone);
    if(0 != memcmp(&otaflag, &otaflagclone,sizeof(otaflag)))
    {
        LINK_LOG_ERROR("FLAG SAVE ERR");
    }
    else
    {
        LINK_LOG_DEBUG("FLAG SAVE OK");
    }

EXIT_HTTPHEADER:
EXIT_REQSEND:
EXIT_TLSCONNECT:
    dtls_al_destroy(handle);
EXIT_TLSHANDLE:
    osal_free(netpara);
EXIT_NETPARA:
EXIT_PARAM:
    return ret;
}






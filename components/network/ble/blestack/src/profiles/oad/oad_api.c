#include <stdbool.h>
#include <string.h>
#include <net/buf.h>
#include "oad_service.h"
#include "oad.h"
#include "oad_api.h"
#ifdef CONFIG_BT_SETTINGS
#include "settings.h"
#endif
#if defined(CFG_BOOT2_ENABLED)
#include "bl_boot2.h"
#endif
#include "bl_print.h"

static app_check_oad_cb app_check_cb = NULL;
struct oad_env_tag oad_env;
#define UPGRD_TIMEOUT	K_SECONDS(2)


static bool check_data_valid(struct oad_file_info *file_info)
{
    if(file_info->manu_code != oad_env.file_info.manu_code || file_info->file_ver != oad_env.upgrd_file_ver)
        return false;

    return true;
}

static void oad_notify_block_req(struct bt_conn *conn)
{
    struct net_buf_simple *buf = NET_BUF_SIMPLE(sizeof(struct oad_block_req_t) + OAD_OPCODE_SIZE);
    struct oad_block_req_t *block_req;

    net_buf_simple_init(buf, 0);
    *(buf->data) = OAD_CMD_IMAG_BLOCK_REQ;
    block_req = (struct oad_block_req_t *)(buf->data+1);
    buf->len = sizeof(struct oad_block_req_t) + OAD_OPCODE_SIZE;
    
    block_req->file_info.file_ver = oad_env.upgrd_file_ver;
    block_req->file_info.manu_code = oad_env.file_info.manu_code;
    block_req->file_offset = oad_env.upgrd_offset;

    bt_oad_notify(conn, buf->data, buf->len);
}

static void oad_notify_upgrd_end(struct bt_conn *conn, u8_t status)
{
    struct net_buf_simple *buf = NET_BUF_SIMPLE(sizeof(struct oad_upgrd_end_t) + OAD_OPCODE_SIZE);
    struct oad_upgrd_end_t *upgrd_end;

    #if defined(CFG_BOOT2_ENABLED)
    if(status == OAD_SUCC)
    {
       bl_print(PRINT_UART0, PRINT_MODULE_APP,"Submit upgrade work\r\n");
       k_delayed_work_submit(&oad_env.upgrd_work, UPGRD_TIMEOUT);
    }
    #endif
    
    net_buf_simple_init(buf, 0);
    *(buf->data) = OAD_CMD_IMAG_UPGRD_END;
    upgrd_end = (struct oad_upgrd_end_t *)(buf->data+1);
    buf->len = sizeof(struct oad_upgrd_end_t) + OAD_OPCODE_SIZE;
    upgrd_end->file_info.file_ver = oad_env.upgrd_file_ver;
    upgrd_end->file_info.manu_code = oad_env.file_info.manu_code;
    upgrd_end->status = status;

    bt_oad_notify(conn, buf->data, buf->len);
}

static void oad_notity_image_identity(struct bt_conn *conn)
{
    struct net_buf_simple *buf = NET_BUF_SIMPLE(sizeof(struct oad_image_identity_t));
    struct oad_image_identity_t *identity;

    net_buf_simple_init(buf, 0);
    *(buf->data) = OAD_CMD_IMAG_IDENTITY;
    identity = (void *)(buf->data+1);
    buf->len = sizeof(struct oad_image_identity_t)+ OAD_OPCODE_SIZE;

    identity->file_info.file_ver = oad_env.file_info.file_ver;
    identity->file_info.manu_code = oad_env.file_info.manu_code;
    identity->file_size = oad_env.cur_file_size;
    identity->crc32 = 0;

    bt_oad_notify(conn, buf->data, buf->len);
}

#if defined(CFG_BOOT2_ENABLED)
void ATTR_TCM_SECTION oad_systemReset(void)
{
  __DSB();                                                          /* Ensure all outstanding memory accesses included
                                                                       buffered write are completed before reset */
  SCB->AIRCR  = ((0x5FAUL << SCB_AIRCR_VECTKEY_Pos) |
                 SCB_AIRCR_SYSRESETREQ_Msk);
  __DSB();                                                          /* Ensure completion of memory access */

  for(;;)                                                           /* wait until reset */
  {
    __NOP();
  }
}

static void oad_upgrade(struct k_work *work)
{
    bl_print(PRINT_UART0, PRINT_MODULE_APP,"oad_upgrade\r\n");
    PtTable_Entry_Config ptEntry;
    oad_env.file_info.file_ver = oad_env.upgrd_file_ver;
    #ifdef CONFIG_BT_SETTINGS
    ef_set_env(NV_IMG_info, &oad_env.file_info);
    #endif

    if (0 == hal_boot2_get_active_entries(PT_ENTRY_FW_CPU0, &ptEntry))
    {
        //switch between index 0 and 1
        ptEntry.activeIndex = 1 - ptEntry.activeIndex;
        bl_print(PRINT_UART0, PRINT_MODULE_APP,"update ptable,active index is %d\r\n", ptEntry.activeIndex);
        hal_boot2_update_ptable(&ptEntry);
        XIP_SFlash_Exit_Cont_Read();    
        oad_systemReset();
    }
    else
    {
        bl_print(PRINT_UART0, PRINT_MODULE_APP,"fail to get pt entry%d\r\n");
    }
}

static u8_t oad_get_new_image_addr(void)
{
    PtTable_Entry_Config ptEntry;
    u8_t active_idx;
    
    if (0 == hal_boot2_get_active_entries(PT_ENTRY_FW_CPU0, &ptEntry))
    {  
        active_idx = 1 - ptEntry.activeIndex;
        oad_env.new_img_addr = ptEntry.Address[active_idx];
        bl_print(PRINT_UART0, PRINT_MODULE_APP,"oad_get_new_image_addr,addr is %d\r\n", oad_env.new_img_addr);
        return 0;
    }

    return -1;
}  
#endif //CFG_BOOT2_ENABLED

static u8_t oad_write_flash(u8_t *data, u16_t len)
{
    #if defined(CFG_BOOT2_ENABLED)
    if(!oad_env.new_img_addr)
    {   
        if(oad_get_new_image_addr()){
            bl_print(PRINT_UART0, PRINT_MODULE_APP,"New img address is null\r\n");
            return -1;
        }

        bl_print(PRINT_UART0, PRINT_MODULE_APP,"Upgrade file size is %d\r\n", oad_env.upgrd_file_size);
        XIP_SFlash_Erase_With_Lock(CPU_TYPE_NP, oad_env.new_img_addr, oad_env.upgrd_file_size);
    }

    bl_print(PRINT_UART0, PRINT_MODULE_APP,"Write flash to 0x%x\r\n",oad_env.new_img_addr + oad_env.upgrd_offset);
    XIP_SFlash_Write_With_Lock(CPU_TYPE_NP, oad_env.new_img_addr + oad_env.upgrd_offset, data, len);
    bl_print(PRINT_UART0, PRINT_MODULE_APP,"Write complete addr = 0x%x \r\n", oad_env.new_img_addr + oad_env.upgrd_offset);
    #endif
    return 0;  
}

static u8_t oad_image_data_handler(u8_t *data, u16_t len)
{
    oad_write_flash(data, len);
    oad_env.upgrd_offset += len;

    if(oad_env.upgrd_offset > oad_env.upgrd_file_size){
        return OAD_INVALID_IMAG;
    }else if(oad_env.upgrd_offset == oad_env.upgrd_file_size){
        return OAD_UPGRD_CMPLT;
    }else{
        return OAD_REQ_MORE_DATA;
    }  
}

static u8_t oad_image_block_resp_handler(struct bt_conn *conn, const u8_t *data, u16_t len)
{
    struct oad_block_rsp_t *block_rsp;
    u8_t *rsp_data;
    u8_t status = OAD_SUCC;

    switch(*data){
        case OAD_SUCC:
        {
            block_rsp = (struct oad_block_rsp_t *)data;
            if(!check_data_valid(&block_rsp->file_info)){
                status = OAD_INVALID_IMAG;
                break;
            }

            if(block_rsp->file_offset != oad_env.upgrd_offset){
                status = OAD_MALORMED_CMD;
                break;
            }
            rsp_data = data + OAD_BLK_RSP_DATA_OFFSET;
            status = oad_image_data_handler(rsp_data, block_rsp->data_size);
            if(status == OAD_UPGRD_CMPLT){
                oad_notify_upgrd_end(conn, OAD_SUCC);    
            }else if(status == OAD_REQ_MORE_DATA){
                oad_notify_block_req(conn);
            }else{
                oad_notify_upgrd_end(conn, status);   
            }
        }
        break;
        case OAD_ABORT:
        {
            XIP_SFlash_Erase_With_Lock(CPU_TYPE_NP, oad_env.new_img_addr, oad_env.upgrd_file_size);
        }
        break;
        
        default:
            status = OAD_MALORMED_CMD;

    }
    return status;
}

static void oad_image_identity_handler(struct bt_conn *conn, const u8_t *data, u16_t len)
{
    struct oad_image_identity_t *identity;
    
    identity = (struct oad_image_identity_t *)data;
    
    if(identity->file_info.manu_code == oad_env.file_info.manu_code &&
		(app_check_cb)(oad_env.file_info.file_ver, identity->file_info.file_ver)){
        oad_env.upgrd_file_ver = identity->file_info.file_ver;
        oad_env.upgrd_file_size = identity->file_size;
        oad_env.upgrd_offset = 0x00;
        oad_env.upgrd_crc32 = identity->crc32;
        
        oad_notify_block_req(conn);
    }else{
        oad_notity_image_identity(conn);
    }
}
  
static void oad_recv_callback(struct bt_conn *conn, const u8_t *data, u16_t len)
{    
    if(*data == OAD_CMD_IMAG_IDENTITY){
        oad_image_identity_handler(conn, data+1, len-1);
    }else{
        if(*data == OAD_CMD_IMAG_BLOCK_RESP)
            oad_image_block_resp_handler(conn, data+1, len-1); 
    }
}

void oad_server_enable(app_check_oad_cb cb)
{
    //todo: get current file info for oad_env.fileinfo
    app_check_cb = cb;
    oad_env.file_info.file_ver = LOCAL_FILE_VER;
    oad_env.file_info.manu_code = LOCAL_MANU_CODE;
    oad_env.new_img_addr = 0;
    bt_oad_service_enable();
    bt_oad_register_callback(oad_recv_callback);
    #if defined(CFG_BOOT2_ENABLED)
    k_delayed_work_init(&oad_env.upgrd_work, oad_upgrade);
    #endif
}

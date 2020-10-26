#ifndef __OAD_API_H__
#define __OAD_API_H__

#include <stdint.h>

typedef bool (*app_check_oad_cb)(uint32_t cur_file_ver, uint32_t new_file_ver);
void oad_server_enable(app_check_oad_cb cb);
#endif //__OAD_API_H__
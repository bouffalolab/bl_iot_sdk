#ifndef __JL_TC_H__
#define __JL_TC_H__

enum jl_tc_result {
    JL_TC_RESULT_SUCCESS,
};
typedef int jl_tc_result_t;

void jl_tc_memory();
void jl_tc_stdio();
void jl_tc_socket();
void jl_tc_extern();
void jl_tc_time();

void register_jl_tc_cmds();

#endif

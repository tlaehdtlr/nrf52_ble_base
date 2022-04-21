/*
    store error log
    print decoding
*/
#ifndef __BASE_DEBUG_H__
#define __BASE_DEBUG_H__
#include <stdint.h>
#include "app_error.h"

typedef struct error_log
{
    uint32_t        fault_id;
    uint32_t        pc;
    uint32_t        error_info;
    assert_info_t * p_assert_info;
    error_info_t  * p_error_info;
    ret_code_t      err_code;
    uint32_t        line_num;
    const uint8_t * p_file_name;
} error_log_t;

#define UNEXPECTED_ERROR_LOG    0

void v_debug_check_reset_reason(void);
void v_debug_store_log(void);
void v_debug_get_log(void);
void app_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info);
#endif
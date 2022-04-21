#include "base_debug.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf52833.h"
#include "nrf_delay.h"

/*
    reset cause
    nRF52833_PS_v1.3.pdf p73
*/
static uint32_t g_base_debug_reset_reas;
static const uint32_t k_base_debug_reset_pin_mask = 0x1;
static const uint32_t k_base_debug_dog_mask = 0x2;
static const uint32_t k_base_debug_soft_rest_mask = 0x4;
static const uint32_t k_base_debug_cpu_lockup_mask = 0x8;

void v_debug_check_reset_reason(void)
{
    g_base_debug_reset_reas = NRF_POWER->RESETREAS;
    // clear any enabled reset reasons
    NRF_POWER->RESETREAS = 0xffffffff;
    if (g_base_debug_reset_reas & k_base_debug_reset_pin_mask)
    {
        NRF_LOG_INFO("reset reason : reset pin");
    }
    else if (g_base_debug_reset_reas & k_base_debug_dog_mask)
    {
        NRF_LOG_INFO("reset reason : watchdog");
    }
    else if (g_base_debug_reset_reas & k_base_debug_soft_rest_mask)
    {
        NRF_LOG_INFO("reset reason : soft reset");
    }
    else if (g_base_debug_reset_reas & k_base_debug_cpu_lockup_mask)
    {
        NRF_LOG_INFO("reset reason : CPU lock-up");
    }
    else
    {
        NRF_LOG_INFO("reset reason : another reason %ld", g_base_debug_reset_reas);
    }
    v_debug_get_log();
}

/* end : reset cause */


/*  start : store log before reset  */
static volatile error_log_t err_log __attribute__((section(".non_init")));


void v_debug_store_log(void)
{
    /* unexpected error ... wdt reset */
    err_log.fault_id = UNEXPECTED_ERROR_LOG;
}


void v_debug_get_log(void)
{
    switch (err_log.fault_id)
    {
        case NRF_FAULT_ID_SDK_ASSERT:
        {
            NRF_LOG_INFO("[NRF_FAULT_ID_SDK_ASSERT] \r\n === %s , %u line ===", err_log.p_file_name , err_log.line_num);
        }
            break;

        case NRF_FAULT_ID_SDK_ERROR:
        {
            NRF_LOG_INFO("[NRF_FAULT_ID_SDK_ERROR] \r\n === %s , %u line ===", err_log.p_file_name , err_log.line_num);
        }
            break;
        default :
        {
            NRF_LOG_INFO("Not app error , unexpected reason");
        }
            break;
    }
}
/*  end : store log before reset  */


/* start : overwrite app_error_fault_handler */

void app_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info)
{
    __disable_irq();
    NRF_LOG_FINAL_FLUSH();

    err_log.fault_id   = id;
    err_log.pc         = pc;
    err_log.error_info = info;

    switch (id)
    {
        case NRF_FAULT_ID_SDK_ASSERT:
            err_log.p_assert_info = (assert_info_t*)info;
            err_log.line_num      = err_log.p_assert_info->line_num;
            err_log.p_file_name   = err_log.p_assert_info->p_file_name;
            break;

        case NRF_FAULT_ID_SDK_ERROR:
            err_log.p_error_info = (error_info_t*)info;
            err_log.err_code     = err_log.p_error_info->err_code;
            err_log.line_num     = err_log.p_error_info->line_num;
            err_log.p_file_name  = err_log.p_error_info->p_file_name;
            break;
    }

    UNUSED_VARIABLE(err_log);

    nrf_delay_ms(1000);
    NVIC_SystemReset();
    // while (0);
}

/* end : overwrite app_error_fault_handler */
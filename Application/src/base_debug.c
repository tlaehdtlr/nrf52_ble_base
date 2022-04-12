#include "base_debug.h"
#include <stdint.h>
#include "nrf_log.h"
#include "nrf52833.h"

/*
    reset cause
    nRF52833_PS_v1.3.pdf p73
*/
static uint32_t g_base_debug_reset_reas;
static const uint32_t k_base_debug_reset_pin_mask = 0x1;
static const uint32_t k_base_debug_dog_mask = 0x2;
static const uint32_t k_base_debug_soft_rest_mask = 0x4;
static const uint32_t k_base_debug_cpu_lockup_mask = 0x8;

void v_check_reset_reason(void)
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
}



/* reset cause */
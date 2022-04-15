#include "base_wdt.h"
#include <stdint.h>
#include "app_timer.h"
#include "app_error.h"
#include "nrf_drv_wdt.h"
#include "nrf_drv_clock.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"


nrf_drv_wdt_channel_id m_base_wdt_channel_id;
APP_TIMER_DEF(m_wdt_feed_timer_id);
const uint32_t wdt_feed_interval = APP_TIMER_TICKS(2000); //2s
volatile wdt_feed_state_t g_wdt_feed_state = WDT_FEED_STATE_FULL;


wdt_feed_state_t get_wdt_feed_state(void)
{
    return g_wdt_feed_state;
}

void v_base_wdt_stop_feed(void)
{
    uint32_t err_code;
    err_code = app_timer_stop(m_wdt_feed_timer_id);
    APP_ERROR_CHECK(err_code);
}

void v_base_wdt_feed(void)
{
    nrf_drv_wdt_channel_feed(m_base_wdt_channel_id);
    g_wdt_feed_state = WDT_FEED_STATE_FULL;
}


static void v_wdt_feed_timer_timeout_handler(void * p_context)
{
    UNUSED_PARAMETER(p_context);
    g_wdt_feed_state = WDT_FEED_STATE_HUNGRY;
}


static void wdt_event_handler(void)
{
    NRF_LOG_ERROR("wdt event handler ");
    //NOTE: The max amount of time we can spend in WDT interrupt is two cycles of 32768[Hz] clock - after that, reset occurs
}


void v_base_wdt_init(void)
{
    NRF_LOG_INFO("wdt init");
    uint32_t err_code = NRF_SUCCESS;

    /*
        if use NRF_DRV_WDT_DEAFULT_CONFIG and want to change time-out,
        change WDT_CONFIG_RELOAD_VALUE in config.h
    */
    nrf_drv_wdt_config_t config = NRF_DRV_WDT_DEAFULT_CONFIG;
    err_code = nrf_drv_wdt_init(&config, wdt_event_handler);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_wdt_channel_alloc(&m_base_wdt_channel_id);
    APP_ERROR_CHECK(err_code);
    nrf_drv_wdt_enable();

    /* timer for feeding */
    err_code = app_timer_create(&m_wdt_feed_timer_id, APP_TIMER_MODE_REPEATED, v_wdt_feed_timer_timeout_handler);
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_start(m_wdt_feed_timer_id, wdt_feed_interval, NULL);
    APP_ERROR_CHECK(err_code);
    return;
}
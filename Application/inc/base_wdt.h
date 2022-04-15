#ifndef __BASE_WDT_H__
#define __BASE_WDT_H__

typedef enum wdt_feed_state
{
    WDT_FEED_STATE_FULL,
    WDT_FEED_STATE_HUNGRY,
} wdt_feed_state_t;

wdt_feed_state_t get_wdt_feed_state(void);
void v_base_wdt_stop_feed(void);
void v_base_wdt_feed(void);
void v_base_wdt_init(void);

#endif
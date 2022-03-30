#ifnedf __CUSTOM_BOARD_H__
#define __CUSTOM_BOARD_H__

#include "nrf_gpio.h"

/*
    <0=> 0 (P0.0)    <1=> 1 (P0.1)    <2=> 2 (P0.2)    <3=> 3 (P0.3)    <4=> 4 (P0.4)    <5=> 5 (P0.5)    <6=> 6 (P0.6)    <7=> 7 (P0.7)    <8=> 8 (P0.8)    <9=> 9 (P0.9)    <10=> 10 (P0.10)
    <11=> 11 (P0.11)    <12=> 12 (P0.12)    <13=> 13 (P0.13)    <14=> 14 (P0.14)    <15=> 15 (P0.15)    <16=> 16 (P0.16)    <17=> 17 (P0.17)    <18=> 18 (P0.18)    <19=> 19 (P0.19)    <20=> 20 (P0.20)
    <21=> 21 (P0.21)    <22=> 22 (P0.22)    <23=> 23 (P0.23)    <24=> 24 (P0.24)    <25=> 25 (P0.25)    <26=> 26 (P0.26)    <27=> 27 (P0.27)    <28=> 28 (P0.28)    <29=> 29 (P0.29)    <30=> 30 (P0.30)
    <31=> 31 (P0.31)    <32=> 32 (P1.0)    <33=> 33 (P1.1)    <34=> 34 (P1.2)    <35=> 35 (P1.3)    <36=> 36 (P1.4)    <37=> 37 (P1.5)    <38=> 38 (P1.6)    <39=> 39 (P1.7)    <40=> 40 (P1.8)
    <41=> 41 (P1.9)    <42=> 42 (P1.10)    <43=> 43 (P1.11)    <44=> 44 (P1.12)    <45=> 45 (P1.13)    <46=> 46 (P1.14)    <47=> 47 (P1.15)
    <4294967295=> Not connected
*/

#define RX_PIN_NUMBER       8
#define TX_PIN_NUMBER       6
#define CTS_PIN_NUMBER      7
#define RTS_PIN_NUMBER      5
#define HWFC                true

#define LEDS_NUMBER         2
#define LED_1               13
#define LED_2               14
#define LEDS_LIST           { LED_1, LED_2 }
#define LEDS_ACTIVE_STATE   0

#define BUTTONS_NUMBER      2
#define BUTTON_1            11
#define BUTTON_2            12
#define BUTTONS_LIST        { BUTTON_1, BUTTON_2 }
#define BUTTONS_PULL        { NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_PULLUP}

#endif
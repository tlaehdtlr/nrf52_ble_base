#ifndef __BASE_BOOTLOADER_H__
#define __BASE_BOOTLOADER_H__

#include <stdint.h>
#include "nrf_dfu.h"
#ifdef __cplusplus
extern "C" {
#endif


ret_code_t base_bootloader_init(nrf_dfu_observer_t observer);

#ifdef __cplusplus
}
#endif

#endif // __BASE_BOOTLOADER_H__
/** @} */

#ifndef __BASE_GAP_H__
#define __BASE_GAP_H__

#include <stdbool.h>

void peer_manager_init(void);
void conn_params_init(void);
void advertising_start(bool erase_bonds);
void advertising_init(void);
void gap_params_init(void);

#endif
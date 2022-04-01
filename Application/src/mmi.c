#include "mmi.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "custom_board.h"
#include "nrf_cli.h"
#include "nrf_cli_uart.h"


NRF_CLI_UART_DEF(cli_uart, 0, 64, 16);
NRF_CLI_DEF(m_cli_uart, "base cli:~$ ", &cli_uart.transport, '\r', 4);


void cli_process(void)
{
    nrf_cli_process(&m_cli_uart);
}


void cli_start(void)
{
    ret_code_t ret;
    ret = nrf_cli_start(&m_cli_uart);
    APP_ERROR_CHECK(ret);
}


static void cli_init(void)
{
    ret_code_t ret;
    nrf_drv_uart_config_t uart_config = NRF_DRV_UART_DEFAULT_CONFIG;
    uart_config.pseltxd = MMI_UART_TX_PIN_NUMBER;
    uart_config.pselrxd = MMI_UART_RX_PIN_NUMBER;
    uart_config.hwfc    = NRF_UART_HWFC_DISABLED;
    ret = nrf_cli_init(&m_cli_uart, &uart_config, true, true, NRF_LOG_SEVERITY_INFO);
    APP_ERROR_CHECK(ret);
}


/**@brief Function for initializing the nrf log module.
 */
void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);
#if NRF_CLI_LOG_BACKEND
    cli_init();
#else
    NRF_LOG_DEFAULT_BACKENDS_INIT();
#endif
}

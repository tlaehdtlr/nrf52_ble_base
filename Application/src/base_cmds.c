#include "nrf_cli.h"
#include "nrf_log.h"
#include "base_wdt.h"
#include "base_debug.h"
#include "app_error.h"

#define UNKNOWN_PARAMETER     "unknown parameter: "

/* 0. help command start
    dongsik
    challenge
*/
static char* base_cmds_all[] =
{
    "1. dongsik",
    "2. challenge",
    "3. error",
};

static void base_cmds_help(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);
    UNUSED_VARIABLE(argc);
    UNUSED_VARIABLE(argv);
    for (int idx=0; idx < sizeof(base_cmds_all)/sizeof(char*); idx++)
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_VT100_COLOR_BLUE, "%s\n", base_cmds_all[idx]);
    }
}

NRF_CLI_CMD_REGISTER(help, NULL, "List of commands registered", base_cmds_help);

/* 0. help command end */


/* 1. dongsik command start
    - sleep
    - looks
        - good
        - bad
*/

static void base_cmds_good(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    UNUSED_VARIABLE(argc);
    UNUSED_VARIABLE(argv);
    nrf_cli_print(p_cli, "I agree ");
}

static void base_cmds_bad(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    UNUSED_VARIABLE(argc);
    UNUSED_VARIABLE(argv);
    nrf_cli_print(p_cli, "You too");
}

NRF_CLI_CREATE_STATIC_SUBCMD_SET(like)
{
    NRF_CLI_CMD(good, NULL, "!", base_cmds_good),
    NRF_CLI_CMD(bad, NULL, "?", base_cmds_bad),
    NRF_CLI_SUBCMD_SET_END
};

static void base_cmds_wake_up(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    UNUSED_VARIABLE(argc);
    UNUSED_VARIABLE(argv);
    nrf_cli_print(p_cli, "please let him wake up");
}

static void base_cmds_looks_like(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    if ((argc == 1) || nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "%s%s\n", UNKNOWN_PARAMETER, argv[1]);

}

NRF_CLI_CREATE_STATIC_SUBCMD_SET(verb)
{
    NRF_CLI_CMD(sleep, NULL, "is he sleeping really?", base_cmds_wake_up),
    NRF_CLI_CMD(looks, &like, "looks like ?", base_cmds_looks_like),
    NRF_CLI_SUBCMD_SET_END
};

static void base_cmds_dongsik(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);
    if (argc==1)
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    nrf_cli_error(p_cli, "%s:%s%s", argv[0], UNKNOWN_PARAMETER, argv[1]);
}

NRF_CLI_CMD_REGISTER(dongsik, &verb, "what is he doing", base_cmds_dongsik);
/* 1. dongsik command end*/


/* 2. challenge command start
    - patient
        - success
        - fail
 */

static void base_cmds_challenge(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);
    if (argc==1)
    {
        nrf_cli_print(p_cli, "challenge [arg1] [arg2] \r\n"\
                                "\t patient \r\n"\
                                "\t\t success \r\n" \
                                "\t\t fail \r\n");
        return;
    }
    else if (argc == 2)
    {
        ;
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "patient") == 0)
        {
            if (strcmp(argv[2], "success") == 0)
            {
                nrf_cli_print(p_cli, "Great !!");
                return ;
            }
            else if (strcmp(argv[2], "fail") == 0)
            {
                nrf_cli_print(p_cli, "Fighting !!");
                return ;
            }
        }
    }

    nrf_cli_error(p_cli, "please input correctly");
}

NRF_CLI_CMD_REGISTER(challenge, NULL, "", base_cmds_challenge);

/* 2. challenge command end */


/* 3. error command start
    - wdt
    - app
 */

static void base_cmds_error(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);
    if (argc == 2)
    {
        if (strcmp(argv[1], "wdt") == 0)
        {
            while(1);
            return ;
        }
        else if (strcmp(argv[1], "app") == 0)
        {
            APP_ERROR_CHECK(1);
            return ;
        }
    }
    else
    {
        nrf_cli_print(p_cli, "error [arg1] \r\n"\
                                "\t wdt \r\n"\
                                "\t app \r\n");
        return;
    }

    nrf_cli_error(p_cli, "please input correctly");
}

NRF_CLI_CMD_REGISTER(error, NULL, "", base_cmds_error);

/* 3. error command end */
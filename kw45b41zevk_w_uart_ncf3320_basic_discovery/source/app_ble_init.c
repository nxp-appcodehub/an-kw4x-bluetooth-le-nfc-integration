/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app.h"
#include "fwk_platform_ble.h"
#include "fwk_platform_ics.h" /* to get NbuInfo */
#include "assert.h"
#include "stdbool.h"

/* -------------------------------------------------------------------------- */
/*                              Private functions                             */
/* -------------------------------------------------------------------------- */

static void APP_RecoverLinkLayerFimrware(int reason)
{
    /* Customer shall add any code that could help for Software/Hardware recovery here */
    (void)reason;
    while (true)
    {
    }
}

static bool App_CheckNbuCompatibility(NbuInfo_t *nbu_info_p)
{
    /* Do whatever compatibility check with NBU version and return false for requesting recovery */
    (void)nbu_info_p;
    return true;
}

/* -------------------------------------------------------------------------- */
/*                              Public functions                              */
/* -------------------------------------------------------------------------- */

int APP_InitBle(void)
{
    int              status = 0;
    static NbuInfo_t nbu_info;

    /* Start link layer firmware and set up HCI link */
    status = PLATFORM_InitBle();
    if (status != 0)
    {
        /* Platform Ble can not start, start recovery */
        APP_RecoverLinkLayerFimrware(1);
        assert(0);
    }
    else
    {
        status = PLATFORM_GetNbuInfo(&nbu_info);
        if ((status < 0) || (App_CheckNbuCompatibility(&nbu_info) == false))
        {
            /* Link Layer version is not compatible, start recovery */
            APP_RecoverLinkLayerFimrware(2);
            assert(0);
        }
    }

    return status;
}
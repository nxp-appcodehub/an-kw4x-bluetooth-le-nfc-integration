/*! *********************************************************************************
 * \defgroup app
 * @{
 ********************************************************************************** */
/*
 * Copyright 2021 - 2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _APP_PREINCLUDE_H_
#define _APP_PREINCLUDE_H_

/*!
 *  Application specific configuration file only
 *  Board Specific Configuration shall be added to board.h file directly such as :
 *  - Number of button on the board,
 *  - Number of LEDs,
 *  - etc...
 */
/*! *********************************************************************************
 *     Board Configuration
 ********************************************************************************** */
/* Number of Button required by the application */
#define gAppButtonCnt_c                 2u

/* Number of LED required by the application */
#define gAppLedCnt_c                    2u

/*! Enable Debug Console (PRINTF) */
#define gDebugConsoleEnable_d           0

/*! *********************************************************************************
 *     App Configuration
 ********************************************************************************** */
/*! Maximum number of connections supported for this application */
#define gAppMaxConnections_c            8U

/*! Enable/disable use of bonding capability */
#define gAppUseBonding_d                0

/*! Enable/disable use of pairing procedure */
#define gAppUsePairing_d                0

/*! Enable/disable use of privacy */
#define gAppUsePrivacy_d                0

#define gPasskeyValue_c                 999999

#define gWuart_AutoStart_c              0

/*! *********************************************************************************
 *     Framework Configuration
 ********************************************************************************** */
/* enable NVM to be used as non volatile storage management by the host stack */
#define gAppUseNvm_d                    1

/*! Repeated Attempts - Mitigation for pairing attacks */
#define gRepeatedAttempts_d             0

/*! The minimum heap size needed:
    4 blocks of 32
    6 blocks of 80
    16 blocks of 288
    1 block of 312
    2 blocks of 400
*/
#define MinimalHeapSize_c               6328

/* Defines number of timers needed by the application */
#if gRepeatedAttempts_d
#define gTmrApplicationTimers_c         5U
#else
#define gTmrApplicationTimers_c         4U
#endif

/*! *********************************************************************************
 *     RTOS Configuration
 ********************************************************************************** */
#if defined(SDK_OS_FREE_RTOS)
/* Defines main task stack size */
#define gMainThreadStackSize_c          1800

/* Defines Host stack size */
#define gHost_TaskStackSize_c           2400
#endif

/*! *********************************************************************************
 *     BLE Stack Configuration
 ********************************************************************************** */
#define gMaxServicesCount_d             6
#define gMaxServiceCharCount_d          6

/* Enable Serial Manager interface */
#define gAppUseSerialManager_c          1

/*! *********************************************************************************
 *     BLE LL Configuration
 ***********************************************************************************/
/*  ble_ll_config.h file lists the parameters with their default values. User can override
 *    the parameter here by defining the parameter to a user defined value. */

#define gAppExtAdvEnable_d                   1
#define gLlScanPeriodicAdvertiserListSize_c (8U)
/* disable autonomous feature exchange */
#define gL1AutonomousFeatureExchange_d 0

/*
 * Specific configuration of LL pools by block size and number of blocks for this application.
 * Optimized using the MEM_OPTIMIZE_BUFFER_POOL feature in MemManager,
 * we find that the most optimized combination for LL buffers.
 *
 * If LlPoolsDetails_c is not defined, default LL buffer configuration in app_preinclude_common.h
 * will be applied.
 */

/* Include common configuration file and board configuration file */
#include "app_preinclude_common.h"
#endif /* _APP_PREINCLUDE_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

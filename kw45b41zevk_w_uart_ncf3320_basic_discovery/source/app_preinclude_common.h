/*! *********************************************************************************
 * \defgroup app
 * @{
 ********************************************************************************** */
/*!
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This file is the app configuration file which is pre included.
 *
 */
#ifndef _APP_PREINCLUDE_COMMON_H_
#define _APP_PREINCLUDE_COMMON_H_

/*!
 * Common configuration file for All wireless demo application
 * DO NOT EDIT
 * Application specific configuration shall be done in app_preinclude.h
 * Board specific configuration shall be done in board.h
 */

/* Number of bonded devices supported by the application. */
#ifndef gMaxBondedDevices_c
    /* Make sure that (gMaxBondedDevices_c * gBleBondDataSize_c) fits into the Flash area
     * reserved by the application for bond information. */
    #define gMaxBondedDevices_c         gAppMaxConnections_c
#endif /* gMaxBondedDevices_c */

#if defined(gAppUsePrivacy_d) && (gAppUsePrivacy_d == 0)
#ifndef gMaxResolvingListSize_c
    /* If privacy disabled, set to minimum size in order to save RAM */
    #define gMaxResolvingListSize_c     1
#endif /* gMaxResolvingListSize_c */
#else
#ifndef gMaxResolvingListSize_c
    /* LL supported maximum size */
    #define gMaxResolvingListSize_c     36
#endif /* gMaxResolvingListSize_c */
#endif

#if (gAppUseBonding_d) && (!gAppUsePairing_d)
    #error "Enable pairing to make use of bonding"
#endif

/* Enable/Disable database hash computation */
#if defined(gBLE51_d) && (gBLE51_d == 1U)
/* Default enabled for dynamic databases and disabled for static ones */
#if defined(gGattDbDynamic_d) && (gGattDbDynamic_d == 1U)
    #define gGattDbComputeHash_d        (1U)
#else
#ifndef gGattDbComputeHash_d
    #define gGattDbComputeHash_d        (0U)
#endif /* #ifndef gGattDbComputeHash_d */
#endif /* defined(gGattDbDynamic_d) && (gGattDbDynamic_d == 1U) */
#endif /* defined(gBLE51_d) && (gBLE51_d == 1U) */

#ifndef gGattUseUpdateDatabaseCopyProc_c
#define gGattUseUpdateDatabaseCopyProc_c FALSE
#endif

/* Enable/Disable application secure mode */
#ifndef gAppSecureMode_d
#define gAppSecureMode_d                 (0U)
#endif

#if (gAppSecureMode_d == 1U)
#define gSecLibSssUseEncryptedKeys_d     (1U)
#define gHostSecureMode_d                (1U)
#else
#define gHostSecureMode_d                (0U)
#endif

/*! Size of bond data structures for a bonded device  */
#define gBleBondIdentityHeaderSize_c     (56U)
/*! *********************************************************************************
 *   Auto Configuration
 ********************************************************************************** */
#if (defined(gAppLowpowerEnabled_d) && (gAppLowpowerEnabled_d==1))  \
     || (defined(gAppUseNvm_d) && (gAppUseNvm_d==1))
/* Enable FreeRtos Idle Hook for NVM saving in Idle and CM33 lowpower */
#define configUSE_IDLE_HOOK                     1
#endif


/*! *********************************************************************************
 *     Component Configuration
 ***********************************************************************************/

/* Sensors module is required for Battery measurement (BLE battery service profile) and temperature measurement */
#if !defined(gAppUseSensors_d)
#define gAppUseSensors_d               1
#endif

#if defined(gDebugConsoleEnable_d)
#define SERIAL_MANAGER_NON_BLOCKING_DUAL_MODE gDebugConsoleEnable_d
#endif

/* Enable Memory manager light heap extention for All BLE Applications
 *  Overide default configuration in fsl_component_mem_manager.c file.
 *  The memory Allocator will use all the available space in RAM for the Heap section.
 *  It requires specific symbol and placement in linker script
 *  For each Application, you can now set MinimalHeapSize_c to ensure minimal heap size is available
 *  at link time */
#ifndef gMemManagerLightExtendHeapAreaUsage
#define gMemManagerLightExtendHeapAreaUsage   1
#endif

/*! *********************************************************************************
 *   Host stack configuration
 ********************************************************************************** */

/* If the number of connection is not mentioned, set it to 1 as in ble_config.h. The MemManager
 * requires to know the number of connection for LL buffer sizing */
#ifndef gAppMaxConnections_c
#define gAppMaxConnections_c           (1U)
#endif

/*! Number of credit-based channels supported */
#ifndef gL2caMaxLeCbChannels_c
#define gL2caMaxLeCbChannels_c         (2U)
#endif

/* Simultaneous EA chained reports.
 * This value must be overwritten by applications that enable BLE 5.0 Observer features */
#ifndef gGapSimultaneousEAChainedReports_c
#define gGapSimultaneousEAChainedReports_c  (0U)
#endif

/* Defines number of timers needed by the protocol stack */
#define gTmrStackTimers_c (3U + (gAppMaxConnections_c * 2U) + gL2caMaxLeCbChannels_c + gGapSimultaneousEAChainedReports_c)

/*! *********************************************************************************
 *   NVM Module Configuration - gAppUseNvm_d shall be defined above as 1 or 0
 ********************************************************************************** */

#if gAppUseNvm_d
    /* configure NVM module */
    #define  gNvStorageIncluded_d                (1)
    #define  gNvFragmentation_Enabled_d          (1)
    #define  gNvUseFlexNVM_d                     (0)
    #if gNvUseFlexNVM_d
        #define  gUnmirroredFeatureSet_d         (0)
    #else
        #define  gUnmirroredFeatureSet_d         (1)
    #endif
    #if gNvFragmentation_Enabled_d
        /* Buffer size large enough to accommodate the maximum number of CCCDs for every device. */
        #define  gNvRecordsCopiedBufferSize_c    (gMaxBondedDevices_c * 16)
    #endif
#endif


 /*! *********************************************************************************
 *   Xcvr Configuration
 ********************************************************************************** */

/* Define the max tx power setting in dBm. Allowed values 0, 7 or 10 */
#if !defined(gAppMaxTxPowerDbm_c)
#define gAppMaxTxPowerDbm_c     0
#endif

 /*! *********************************************************************************
 *     RTOS Configuration
 ********************************************************************************** */
#if defined(SDK_OS_FREE_RTOS)

#ifndef gMainThreadStackSize_c
#define gMainThreadStackSize_c      2600
#endif

#ifndef gAppTaskWaitTimeout_ms_c
#define gAppTaskWaitTimeout_ms_c       osaWaitForever_c
#endif

/*! When FreeRTOS is used, enable by default the Tickless mode for low power */
#if defined(gAppLowpowerEnabled_d) && (gAppLowpowerEnabled_d>0)
#define configUSE_TICKLESS_IDLE          1
#undef  TM_ENABLE_TIME_STAMP
#define TM_ENABLE_TIME_STAMP             1
#endif

#endif /* SDK_OS_FREE_RTOS */

#endif /* _APP_PREINCLUDE_COMMON_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

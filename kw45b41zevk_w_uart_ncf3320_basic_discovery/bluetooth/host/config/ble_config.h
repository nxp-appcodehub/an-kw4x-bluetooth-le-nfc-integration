/*! *********************************************************************************
 * \addtogroup BLE
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
* Copyright 2016-2022 NXP
* All rights reserved.
*
* \file
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

/************************************************************************************
*************************************************************************************
* DO NOT MODIFY THIS FILE!
*************************************************************************************
************************************************************************************/

#ifndef BLE_CONFIG_H
#define BLE_CONFIG_H

/************************************************************************************
*************************************************************************************
* Public macros - Do not modify directly! Override in app_preinclude.h if needed.
*************************************************************************************
************************************************************************************/
/* Number of bonded devices supported by the application.
*  Make sure that (gMaxBondedDevices_c * gBleBondDataSize_c) fits into the Flash area
*  reserved by the application for bond information.
*  Also, adjust the value of gNvRecordsCopiedBufferSize_c to be greater or equal to
*  the number of elements of the largest NVM data set.
* (ex: gNvRecordsCopiedBufferSize_c >= (gMaxBondedDevices_c * gcGapMaximumSavedCccds_c)) */
#ifndef gMaxBondedDevices_c
#define gMaxBondedDevices_c             8
#endif

/*! Maximum number of entries in the controller resolving list. Adjust based on controller */
#ifndef gMaxResolvingListSize_c
#define gMaxResolvingListSize_c         8
#endif

/*! Maximum number of handles that can be registered for write notifications. */
#ifndef gMaxWriteNotificationHandles_c
#define gMaxWriteNotificationHandles_c        10
#endif

/*! Maximum number of handles that can be registered for read notifications. */
#ifndef gMaxReadNotificationHandles_c
#define gMaxReadNotificationHandles_c        10
#endif

/* Size of prepare write queue. Default value supports a 512-byte attribute transferred on maximum ATT_MTU. */
#ifndef gPrepareWriteQueueSize_c
#define gPrepareWriteQueueSize_c  (gAttMaxValueLength_c / (gAttMaxPrepWriteDataSize_d(gAttMaxMtu_c)) + 1U)
#endif

/* Preferred value for the maximum transmission number of payload octets to be
 * used for new connections.
 *
 * Range 0x001B - 0x00FB
 */
#ifndef gBleDefaultTxOctets_c
#define gBleDefaultTxOctets_c        0x00FB
#endif

/* Preferred value for the maximum packet transmission time to be
 * used for new connections.
 *
 * Range 0x0148 - 0x0848
 */
#ifndef gBleDefaultTxTime_c
#define gBleDefaultTxTime_c        	 0x0848
#endif

/* Timeout for Resolvable Private Address generation in Host
 *
 * Unit: 1 second
 * Range: 1 - 65535
 * Default: 900
 */
#ifndef gBleHostPrivacyTimeout_c
#define gBleHostPrivacyTimeout_c    900
#endif

/* Timeout for Resolvable Private Address generation in Controller
 * (Enhanced Privacy feature - BLE 4.2 only)
 *
 * Unit: 1 second
 * Range: 1 - 41400
 * Default: 900
 */
#ifndef gBleControllerPrivacyTimeout_c
#define gBleControllerPrivacyTimeout_c    900
#endif

/* Flag indicating whether OOB channel used in LE Secure Connections pairing has MITM protection (BLE 4.2 only).
 * Default: FALSE
 */
#ifndef gBleLeScOobHasMitmProtection_c
#define gBleLeScOobHasMitmProtection_c    (FALSE)
#endif

/*! Number of maximum connections supported at application level. Do not modify this
    directly. Redefine it in app_preinclude.h if the application supports multiple
    connections */
#ifndef gAppMaxConnections_c
#define gAppMaxConnections_c             (1U)
#endif

/* Maximum number of devices without bonding. */
#ifndef gMaxNonBondedDevices_c
#define gMaxNonBondedDevices_c             gAppMaxConnections_c
#endif

/*! Number of maximum enhanced ATT bearers supported at application level. Do not modify this
    directly. Redefine it according to application capabilities in app_preinclude.h */
#ifndef gAppEattMaxNoOfBearers_c
#if defined(gEATT_d) && (gEATT_d == TRUE)
#define gAppEattMaxNoOfBearers_c        (2U)
#else
#define gAppEattMaxNoOfBearers_c        (0U)
#endif
#endif

/*! This define is used to compute the sizes of arrays used by the EATT feature. Should be 0 if EATT
    is not supported at application level and equal to the maximum number of connections supported otherwise. */
#ifndef gBleAppMaxActiveConnectionsEatt_c
#if defined(gEATT_d) && (gEATT_d == TRUE)
#define gBleAppMaxActiveConnectionsEatt_c     gAppMaxConnections_c
#else
#define gBleAppMaxActiveConnectionsEatt_c     (0U)
#endif
#endif

#ifndef gAppEattDefaultMtu_c
#define gAppEattDefaultMtu_c            (64U)
#endif

/*! This define is used to compute the sizes of arrays used by the GATT caching feature. Should be 0 if GATT caching
    is not supported at application level and equal to the maximum number of bonded devices supported otherwise. */
#ifndef gcAppMaximumBondedDevicesGattCaching_c
#if defined(gGattCaching_d) && (gGattCaching_d == TRUE)
#define gcAppMaximumBondedDevicesGattCaching_c  gMaxBondedDevices_c
#else
#define gcAppMaximumBondedDevicesGattCaching_c  (0U)
#endif
#endif

/*! This define is used to compute the sizes of arrays used by the GATT caching feature. Should be 0 if GATT caching
    is not supported at application level and equal to the maximum number of connections supported otherwise. */
#ifndef gBleAppMaxActiveConnectionsGattCaching_c
#if defined(gGattCaching_d) && (gGattCaching_d == TRUE)
#define gBleAppMaxActiveConnectionsGattCaching_c     gAppMaxConnections_c
#else
#define gBleAppMaxActiveConnectionsGattCaching_c     (0U)
#endif
#endif

/*! Number of credit-based channels supported */
#ifndef gL2caMaxLeCbChannels_c
#define gL2caMaxLeCbChannels_c           (2U)
#endif

/*! Number of LE_PSM supported */
#ifndef gL2caMaxLePsmSupported_c
#define gL2caMaxLePsmSupported_c         (2U)
#endif

/*! Maximum number of pending L2CA packets.
    This queue is used by the L2CAP layer to buffer packets when the LE controller cannot accept ACL Data packets any more.
    Any new requests sent from the Host or application layer after this queue is full will generate a gBleOverflow_c event.
    Also, when the queue transitions to empty state, a gTxEntryAvailable_c generic event will be generated. */
#ifndef gMaxL2caQueueSize_c
#define gMaxL2caQueueSize_c              (3U)
#endif

#ifndef gMaxAdvReportQueueSize_c
#define gMaxAdvReportQueueSize_c         (30U)
#endif

/*! Simultaneous EA chained reports */
#ifndef gGapSimultaneousEAChainedReports_c
#define gGapSimultaneousEAChainedReports_c  (2U)
#endif

/*! Timeout in milliseconds for freeing the accumulated incomplete ext adv reports */
#ifndef gBleHostFreeEAReportTimeoutMs_c
#define gBleHostFreeEAReportTimeoutMs_c       (10000U)
#endif

/*! How to handle host privacy addresses for different advertising sets:
 * TRUE - use the same address for all advertising sets (same behavior as KW38 LL)
 * FALSE - use different address for each advertising set */
#ifndef gBleHostExtAdvUseSameRandomAddr_c
#define gBleHostExtAdvUseSameRandomAddr_c   (TRUE)
#endif

/*! How the Host handles LTK requests from LL for unbonded devices:
 * TRUE - deny LTK (default behavior)
 * FALSE - generate gConnEvtLongTermKeyRequest_c event to allow application to provide LTK */
#ifndef gBleHostAutoRejectLtkRequestForUnbondedDevices_c
#define gBleHostAutoRejectLtkRequestForUnbondedDevices_c   (TRUE)
#endif

/*! Maximum number of gapServiceSecurityRequirements_t structures that can be registered
    with Gap_RegisterDeviceSecurityRequirements() */
#ifndef gGapMaxServiceSpecificSecurityRequirements_c
#define gGapMaxServiceSpecificSecurityRequirements_c   (3U)
#endif

#ifndef gUseCSLibHook_c
#define gUseCSLibHook_c FALSE
#endif

/* The maximum number of BLE connection supported by platform */
#if defined(CPU_QN9080C)
    #define MAX_PLATFORM_SUPPORTED_CONNECTIONS     16

#elif (defined(CPU_MKW36A512VHT4) || defined(CPU_MKW36A512VFP4) || defined(CPU_MKW36A512VFT4) || \
       defined(CPU_MKW36Z512VHT4) || defined(CPU_MKW36Z512VFP4) || defined(CPU_MKW35A512VFP4) || \
       defined(CPU_MKW35A512VFT4) || defined(CPU_MKW35Z512VHT4) || defined(CPU_MKW34A512VFT4) || \
       defined(CPU_K32W032S1M2CAx_cm0plus) || defined(CPU_K32W032S1M2VPJ_cm0plus) || \
       defined(CPU_K32W032S1M2CAx_cm4) || defined(CPU_K32W032S1M2VPJ_cm4) || \
       defined(CPU_MKW38A512VFT4) || defined (CPU_MKW38Z512VFT4) || defined(CPU_MKW39A512VFT4) || \
       defined(CPU_MKW37A512VFT4) || defined(CPU_MKW37Z512VFT4) || \
       defined(CPU_K32W232H050VFTA) || defined(CPU_NHS52S04HN40) || \
       defined(CPU_MCXW345CHNA))

    #define MAX_PLATFORM_SUPPORTED_CONNECTIONS     8

#elif defined(KW45B41Z82_SERIES) || defined(KW45B41Z83_SERIES) || defined(K32W1480_SERIES) || defined(CPU_KW45B41Z83AFTA) || defined(CPU_K32W1480VFTA)
    #define MAX_PLATFORM_SUPPORTED_CONNECTIONS     24

#elif (defined(CPU_MKW41Z256VHT4) || defined(CPU_MKW41Z512CAT4) || defined(CPU_MKW41Z512VHT4) || \
       defined(CPU_MKW31Z256VHT4) || defined(CPU_MKW31Z512CAT4) || defined(CPU_MKW31Z512VHT4))
    #define MAX_PLATFORM_SUPPORTED_CONNECTIONS     2

#elif defined(CPU_MKW40Z160VHT4) || defined(CPU_MKW30Z160VHM4)
    #define MAX_PLATFORM_SUPPORTED_CONNECTIONS     1

#else
    #warning Undefined platform!
#endif

#if (gAppMaxConnections_c > MAX_PLATFORM_SUPPORTED_CONNECTIONS)
#error The number of connections configured by the application exceeds the number of connection supported by this platform.
#endif

#endif /* BLE_CONFIG_H */

/*! *********************************************************************************
* @}
********************************************************************************** */

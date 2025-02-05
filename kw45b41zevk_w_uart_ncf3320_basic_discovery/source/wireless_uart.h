/*! *********************************************************************************
 * \defgroup Wireless UART Application
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2021 NXP
* All rights reserved.
*
* \file
*
* This file is the interface file for the Wireless UART application
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef WIRELESS_UART_H
#define WIRELESS_UART_H
#include "gap_types.h"

/*************************************************************************************
**************************************************************************************
* Public macros
**************************************************************************************
*************************************************************************************/

/* Profile Parameters */
#define gScanningTime_c        10   /* 10 s*/

/* Enable/Disable Controller Adv/Scan/Connection Notifications */
#ifndef gUseControllerNotifications_c
#define gUseControllerNotifications_c 0
#endif

/* Receive Notifications in a callback registered in the Controller
   instead of Host GAP Generic callback */
#ifndef gUseControllerNotificationsCallback_c
#define gUseControllerNotificationsCallback_c 0
#endif

#if (defined(gAppButtonCnt_c) && (gAppButtonCnt_c == 1))
  /* switch press timer timeout */
  #ifndef gSwitchPressTimeout_c
  #define gSwitchPressTimeout_c    (1000UL)
  #endif
  /* switch press threshold (number of key presses to toggle the GAP role) */
  #ifndef gSwitchPressThreshold_c
  #define gSwitchPressThreshold_c    (2)
  #endif
#endif

#ifndef gWuart_CentralRole_c
#define gWuart_CentralRole_c 1
#endif

#ifndef gWuart_PeripheralRole_c
#define gWuart_PeripheralRole_c 1
#endif

#ifndef gWuart_AutoStart_c
#define gWuart_AutoStart_c 0
#endif

#ifndef gWuart_AutoStartGapRole_c
#define gWuart_AutoStartGapRole_c gGapCentral_c
#endif

#if gUseNfcLibrary_d
typedef struct nfcCardInfo_tag
{
	uint8_t technology;
	uint8_t uid[8];
}nfcCardInfo_t;

extern nfcCardInfo_t gNfcCardInfo;
#endif

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */
extern gapConnectionRequestParameters_t gConnReqParams;
extern gapScanningParameters_t          gScanParams;
extern gapAdvertisingData_t             gAppAdvertisingData;
extern gapScanResponseData_t            gAppScanRspData;
extern gapAdvertisingParameters_t       gAdvParams;

void BleApp_SendNfcCardInfo(void);
#define HexToAscii(hex) (uint8_t)( ((hex) & 0x0F) + ((((hex) & 0x0F) <= 9) ? '0' : ('A'-10)) )

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif


#endif /* _APP_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

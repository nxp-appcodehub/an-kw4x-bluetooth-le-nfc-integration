/*! *********************************************************************************
 * \addtogroup BLE
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2021 NXP
* All rights reserved.
*
* \file
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "ble_init.h"
#include "ble_host_task_config.h"

#if defined(gBoard_ExtPaSupport_d) && (gBoard_ExtPaSupport_d > 0)
#include "board_extPA.h"
#endif

#if !(defined(gUseHciTransportDownward_d) && gUseHciTransportDownward_d)
#include "ble_controller_task_config.h"
#endif /* gUseHciTransportDownward_d */

#if defined(KW45B41Z83_SERIES) || \
    defined(KW45B41Z82_SERIES) || \
    defined(K32W1480_SERIES)   || \
    defined(CPU_MCXW345CHNA) || defined(CPU_MCXW345CUKA)
#include "fwk_platform_ble.h"
#endif /* KW45B41Z83_SERIES */

#if defined(CPU_MCXW345CHNA) || defined(CPU_MCXW345CUKA)
#include "controller_api.h"
#endif

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/
#ifndef cMCU_SleepDuringBleEvents
    #define cMCU_SleepDuringBleEvents                      0
#endif /* cMCU_SleepDuringBleEvents */

#if defined(gUseHciTransportDownward_d) && gUseHciTransportDownward_d
#if defined(KW45B41Z83_SERIES) || \
    defined(KW45B41Z82_SERIES) || \
    defined(K32W1480_SERIES)   || \
    defined(CPU_MCXW345CHNA) || defined(CPU_MCXW345CUKA)
#define mHciSetMacAddrCommandLength_c       (8U)
#define gHciSetMacAddrCommand_c             0x0022U
#define HciCommand(opCodeGroup, opCodeCommand)\
    (((uint16_t)(opCodeGroup) & (uint16_t)0x3FU)<<(uint16_t)SHIFT10)|(uint16_t)((opCodeCommand) & 0x3FFU)
#define BT_USER_BD 254
#endif
#endif

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/
#if !defined(gUseHciTransportUpward_d) || (!gUseHciTransportUpward_d)
bool_t gHostInitResetController = gHostInitResetController_c;
#endif /* gUseHciTransportUpward_d */

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
#if !defined(gUseHciTransportDownward_d) || (!gUseHciTransportDownward_d)

#if  defined(K32W232H_SERIES)
void Controller_ParamInit(void);
#endif

#if defined(gXcvrDacTrimValueSorageAddr_d)
static uint32_t SaveXcvrDcocDacTrimToFlash(xcvr_DcocDacTrim_t *xcvrDacTrim);
static uint32_t RestoreXcvrDcocDacTrimFromFlash(xcvr_DcocDacTrim_t *xcvrDacTrim);
#endif /* gXcvrDacTrimValueSorageAddr_d */

#endif /* gUseHciTransportDownward_d */

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
#if defined(gPreserveXcvrDacTrimValue_d) && gPreserveXcvrDacTrimValue_d
/*
 * This variable must be preserved between CPU reset.
 * Place the XCVR DAC trim value in RAM retention region or in Flash.
 */
static xcvr_DcocDacTrim_t mXcvrDacTrim;
#endif /* gPreserveXcvrDacTrimValue_d */

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
*\fn           bleResult_t Ble_Initialize(gapGenericCallback_t gapGenericCallback)
*\brief        Performs full initialization of the BLE stack.
*
*\param  [in]  genericCallback    Callback used by the Host Stack to propagate GAP
*                                 generic events to the application.
*
*\return       bleResult_t        Result of the operation.
********************************************************************************** */
bleResult_t Ble_Initialize
(
    gapGenericCallback_t gapGenericCallback
)
{
#if defined(gUseHciTransportDownward_d) && gUseHciTransportDownward_d
    /* HCI Transport Init */
#if (defined(KW45B41Z83_SERIES) || \
    defined(KW45B41Z82_SERIES) || \
    defined(K32W1480_SERIES))
    if (gHciSuccess_c != Hcit_Init(Ble_HciRecvFromIsr))
    {
        return gHciTransportError_c;
    }        
#else        
    if (gHciSuccess_c != Hcit_Init(Ble_HciRecv))
    {
        return gHciTransportError_c;
    }
#endif
#if defined(KW45B41Z83_SERIES) || \
    defined(KW45B41Z82_SERIES) || \
    defined(K32W1480_SERIES)   || \
    defined(CPU_MCXW345CHNA) || defined(CPU_MCXW345CUKA)
    /*
     * Set BD Address in Controller. Must be done after HCI init
     * and before Host init.
     */
      Ble_SetBDAddr();
#endif /* KW45B41Z83_SERIES */

    /* Check for available memory storage */
    if (!Ble_CheckMemoryStorage())
    {
        return gBleOutOfMemory_c;
    }

    /* BLE Host Tasks Init */
    if (KOSA_StatusSuccess != Ble_HostTaskInit())
    {
        return gBleOsError_c;
    }

    /* BLE Host Stack Init */
    return Ble_HostInitialize(gapGenericCallback, Hcit_SendPacket);

#elif defined(gUseHciTransportUpward_d) && gUseHciTransportUpward_d

    if (KOSA_StatusSuccess != Controller_TaskInit())
    {
        return gBleOsError_c;
    }

    /* BLE Controller Init */
    if (KOSA_StatusSuccess != Controller_Init(Hcit_SendPacket))
    {
        return gBleOsError_c;
    }

#if defined(K32W232H_SERIES))
    /* Configures default TX power */
    Controller_ParamInit();
#endif /* K32W232H_SERIES */

    return Controller_SendPacketToController(Hci_SendPacketToController);

#else /* gUseHciTransportUpward_d */

    /* BLE Controller Init */
    if (KOSA_StatusSuccess != Controller_Init(Ble_HciRecv))
    {
        return gBleOsError_c;
    }

#if defined(K32W232H_SERIES)
    /* Configures default TX power */
    Controller_ParamInit();
#endif /* K32W232H_SERIES */

    /* Check for available memory storage */
    if (!Ble_CheckMemoryStorage())
    {
        return gBleOutOfMemory_c;
    }

    /* BLE Host Tasks Init */
    if (KOSA_StatusSuccess != Ble_HostTaskInit())
    {
        return gBleOsError_c;
    }

    /* BLE Host Stack Init */
    return Ble_HostInitialize(gapGenericCallback,
                (hciHostToControllerInterface_t) Controller_SendPacketToController);

#endif /* gUseHciTransportUpward_d */
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

#if defined(gXcvrDacTrimValueSorageAddr_d)
/*! *********************************************************************************
*\private
*\fn           uint32_t  SaveXcvrDcocDacTrimToFlash(xcvr_DcocDacTrim_t *xcvrDacTrim)
*\brief        Saves  XCVR DCOC DAC trim value to Flash.
*
*\param  [in]  xcvrDacTrim    XCVR DCOC DAC trim register value storage.
*
*\return       uint32_t       A flash status code.
********************************************************************************** */
static uint32_t  SaveXcvrDcocDacTrimToFlash(xcvr_DcocDacTrim_t *xcvrDacTrim)
{
    uint32_t status;

    if (FLib_MemCmpToVal((void const *)gXcvrDacTrimValueSorageAddr_d,
                         0xFF,
                         sizeof(xcvr_DcocDacTrim_t)))
    {
        status = NV_FlashProgramUnaligned(gXcvrDacTrimValueSorageAddr_d,
                                          sizeof(xcvr_DcocDacTrim_t),
                                          (uint8_t*)xcvrDacTrim);
    }
    else
    {
        status = 1;
    }

    return status;
}

/*! *********************************************************************************
*\private
*\fn           uint32_t RestoreXcvrDcocDacTrimFromFlash(
*                  xcvr_DcocDacTrim_t *xcvrDacTrim)
*\brief        Restores XCVR DCOC DAC trim value from Flash.
*
*\param  [in]  xcvrDacTrim    XCVR DCOC DAC trim register value storage.
*
*\retval       1              Invalid trim value stored in Flash.
*\retval       0              Valid trim value stored in Flash.
********************************************************************************** */
static uint32_t RestoreXcvrDcocDacTrimFromFlash(xcvr_DcocDacTrim_t *xcvrDacTrim)
{
    uint32_t status;

    if (FLib_MemCmpToVal((void const *)gXcvrDacTrimValueSorageAddr_d,
                         0xFF,
                         sizeof(xcvr_DcocDacTrim_t)))
    {
        status = 1;
    }
    else
    {
        status = 0;
        FLib_MemCpy(xcvrDacTrim,
                    (void const *)gXcvrDacTrimValueSorageAddr_d,
                    sizeof(xcvr_DcocDacTrim_t));
    }

    return status;
}
#endif /* gXcvrDacTrimValueSorageAddr_d */

#if defined(gUseHciTransportDownward_d) && gUseHciTransportDownward_d
#if defined(KW45B41Z83_SERIES) || \
    defined(KW45B41Z82_SERIES) || \
    defined(K32W1480_SERIES)   || \
    defined(CPU_MCXW345CHNA) || defined(CPU_MCXW345CUKA)
void Ble_SetBDAddr(void)
{
    uint8_t bleDeviceAddress[gcBleDeviceAddressSize_c] = {0};

    PLATFORM_GetBDAddr(bleDeviceAddress);

#if defined(CPU_MCXW345CHNA) || defined(CPU_MCXW345CUKA)
    /* Set BD address by API call */
    (void)Controller_SetDeviceAddress(bleDeviceAddress);
#else
    /* Set BD address by HCI message */
    uint8_t aHciPacket[mHciSetMacAddrCommandLength_c + gHciCommandPacketHeaderLength_c];
    uint16_t opcode = HciCommand(gHciVendorSpecificDebugCommands_c, gHciSetMacAddrCommand_c);

        /* Set HCI opcode */
    FLib_MemCpy((void*)aHciPacket, (const void*)&opcode, 2U);
    /* Set HCI parameter length */
    aHciPacket[2] = (uint8_t)mHciSetMacAddrCommandLength_c;
    /* Set command parameter ID */
    aHciPacket[3] = (uint8_t)BT_USER_BD;
    /* Set command parameter length */
    aHciPacket[4] = (uint8_t)6U;

    FLib_MemCpy((void*)&aHciPacket[gHciCommandPacketHeaderLength_c + 2U], (const void*)bleDeviceAddress, gcBleDeviceAddressSize_c);

    /* Send HCI command */
    (void)Hcit_SendPacket(gHciCommandPacket_c, aHciPacket, gHciCommandPacketHeaderLength_c + mHciSetMacAddrCommandLength_c);
#endif
}
#endif
#endif

/*! *********************************************************************************
* @}
********************************************************************************** */

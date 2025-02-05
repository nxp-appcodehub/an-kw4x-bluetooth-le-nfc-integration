/*! *********************************************************************************
* \addtogroup L2CA
* @{
********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* Copyright 2016-2017, 2021-2022 NXP
* All rights reserved.
*
* \file
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef L2CA_CB_INTERFACE_H
#define L2CA_CB_INTERFACE_H

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "ble_general.h"
#include "l2ca_types.h"

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/
/* Result values for LE Credit Based Connection Response */
typedef enum
{
    gSuccessful_c                               = 0x0000U,
    gLePsmNotSupported_c                        = 0x0002U,
    gNoResourcesAvailable_c                     = 0x0004U,
    gInsufficientAuthentication_c               = 0x0005U,
    gInsufficientAuthorization_c                = 0x0006U,
    gInsufficientEncryptionKeySize_c            = 0x0007U,
    gInsufficientEncryption_c                   = 0x0008U,
    gInvalidSourceCid_c                         = 0x0009U,
    gSourceCidAreadyAllocated_c                 = 0x000AU,
    gUnacceptableParameters_c                   = 0x000BU,
    gInvalidParameters_c                        = 0x000CU,
    gCommandRejected_c                          = 0x0100U,
    gResponseTimeout_c                          = 0xFFFEU
} l2caLeCbConnectionRequestResult_t;

typedef enum
{
    gL2ca_CancelConnection_c                    = 0x0000U,
    gL2ca_SendLeFlowControlCredit_c             = 0x0001U,
    gL2ca_DisconnectLePsm_c                     = 0x0002U,
    gL2ca_HandleSendLeCbData_c                  = 0x0003U,
    gL2ca_HandleRecvLeCbData_c                  = 0x0004U,
    gL2ca_HandleLeFlowControlCredit_c           = 0x0005U,
    gL2ca_EnhancedReconfigureReq_c              = 0x0006U,
    gL2ca_EnhancedCancelConnection_c            = 0x0007U
} l2caErrorSource_t;

typedef enum
{
    gReconfigurationSuccessful_c                = 0x0000U,
    gMtuReductionNotAllowed_c                   = 0x0001U,
    gMultipleChannelMpsReductionNotAllowed_c    = 0x0002U,
    gDestinationCidInvalid_c                    = 0x0003U,
    gUnacceptableReconfParameters_c             = 0x0004U,
    gReconfigurationTimeout_c                   = 0x0005U,
    gReconfReserved_c                           = 0xFFFFU
} l2capReconfigureResponse_t;

typedef enum
{
    gL2ca_ChannelStatusChannelIdle_c            = 0x0000U,
    gL2ca_ChannelStatusChannelBusy_c            = 0x0001U,
} l2caChannelStatus_t;

typedef struct l2caLeCbConnectionRequest_tag
{
    deviceId_t  deviceId;
    uint16_t    lePsm;
    uint16_t    peerMtu;
    uint16_t    peerMps;
    uint16_t    initialCredits;
} l2caLeCbConnectionRequest_t;

typedef struct l2caLeCbConnectionComplete_tag
{
    deviceId_t                          deviceId;
    uint16_t                            cId;
    uint16_t                            peerMtu;
    uint16_t                            peerMps;
    uint16_t                            initialCredits;
    l2caLeCbConnectionRequestResult_t   result;
} l2caLeCbConnectionComplete_t;

typedef struct l2caHandoverConnectionComplete_tag
{
    deviceId_t                          deviceId;
    uint16_t                            cId;
    uint16_t                            peerMtu;
    uint16_t                            peerMps;
    uint16_t                            credits;
} l2caHandoverConnectionComplete_t;

typedef struct l2caLeCbDisconnection_tag
{
    deviceId_t  deviceId;
    uint16_t    cId;
} l2caLeCbDisconnection_t;

typedef struct l2caLeCbNoPeerCredits_tag
{
    deviceId_t  deviceId;
    uint16_t    cId;
} l2caLeCbNoPeerCredits_t;

typedef struct l2caLeCbLocalCreditsNotification_tag
{
    deviceId_t  deviceId;
    uint16_t    cId;
    uint16_t    localCredits;
} l2caLeCbLocalCreditsNotification_t;

typedef struct l2caLeCbError_tag
{
    deviceId_t  deviceId;
    bleResult_t result;
    l2caErrorSource_t errorSource;
} l2caLeCbError_t;

typedef struct l2caLeCbChannelStatusNotification_tag
{
    deviceId_t              deviceId;
    uint16_t                cId;
    l2caChannelStatus_t     status;
} l2caLeCbChannelStatusNotification_t;

typedef struct l2caEnhancedConnectionRequest_tag
{
    deviceId_t  deviceId;
    uint16_t    lePsm;
    uint16_t    peerMtu;
    uint16_t    peerMps;
    uint16_t    initialCredits;
    uint8_t     noOfChannels;
    uint16_t    aCids[5];
} l2caEnhancedConnectionRequest_t;

typedef struct l2caEnhancedConnectionComplete_tag
{
    deviceId_t                        deviceId;
    uint16_t                          peerMtu;
    uint16_t                          peerMps;
    uint16_t                          initialCredits;
    l2caLeCbConnectionRequestResult_t result;
    uint8_t                           noOfChannels;
    uint16_t                          aCids[5];
} l2caEnhancedConnectionComplete_t;

typedef struct l2caEnhancedReconfigureRequest_tag
{
    deviceId_t                 deviceId;
    uint16_t                   newMtu;
    uint16_t                   newMps;
    l2capReconfigureResponse_t result;
    uint8_t                    noOfChannels;
    uint16_t                   aCids[5];
} l2caEnhancedReconfigureRequest_t;

typedef struct l2caEnhancedReconfigureResponse_tag
{
    deviceId_t                 deviceId;
    l2capReconfigureResponse_t result;
} l2caEnhancedReconfigureResponse_t;

typedef struct l2capControlMessage_tag
{
    l2capControlMessageType_t messageType;
    union
    {
        l2caLeCbConnectionRequest_t         connectionRequest;
        l2caLeCbConnectionComplete_t        connectionComplete;
        l2caLeCbDisconnection_t             disconnection;
        l2caLeCbNoPeerCredits_t             noPeerCredits;
        l2caLeCbLocalCreditsNotification_t  localCreditsNotification;
        l2caLeCbError_t                     error;
        l2caLeCbChannelStatusNotification_t channelStatusNotification;

#if defined(gBLE52_d) && (gBLE52_d == TRUE)
        l2caEnhancedConnectionRequest_t    enhancedConnRequest;
        l2caEnhancedConnectionComplete_t   enhancedConnComplete;
        l2caEnhancedReconfigureRequest_t   reconfigureRequest;
        l2caEnhancedReconfigureResponse_t  reconfigureResponse;
#endif /* gBLE52_d */

        l2caHandoverConnectionComplete_t   handoverConnectionComplete;
    } messageData;
} l2capControlMessage_t;

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Interface callback type definitions
*************************************************************************************
************************************************************************************/
typedef void(*l2caLeCbDataCallback_t)
                (deviceId_t deviceId,
                 uint16_t   channelId,
                 uint8_t* pPacket,
                 uint16_t packetLength);

typedef void(*l2caControlCallback_t)
                (l2capControlMessage_t* pMessage);

typedef l2caControlCallback_t l2caLeCbControlCallback_t;

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*
* L2CAP LE Credit Based Interface Primitives
*/

/*! *********************************************************************************
* \brief        Registers callbacks for credit based data and control events on
*               L2CAP.
*
* \param[in]    pCallback           Callback function for data plane messages.
* \param[in]    pCtrlCallback       Callback function for control plane messages.
*
* \return       bleResult_t         Result of the operation.
********************************************************************************** */
bleResult_t L2ca_RegisterLeCbCallbacks
(
    l2caLeCbDataCallback_t      pCallback,
    l2caLeCbControlCallback_t   pCtrlCallback
);

/*! *********************************************************************************
* \brief        Registers the LE_PSM from the L2CAP.
*
* \param[in]    lePsm               Bluetooth SIG or Vendor LE_PSM.
* \param[in]    lePsmMtu            MTU of the registered PSM.
*
* \return       bleResult_t         Result of the operation.
********************************************************************************** */
bleResult_t L2ca_RegisterLePsm
(
    uint16_t                    lePsm,
    uint16_t                    lePsmMtu
);

/*! *********************************************************************************
* \brief        Unregisters the LE_PSM from the L2CAP.
*
* \param[in]    lePsm               Bluetooth SIG or Vendor LE_PSM.
*
* \return       bleResult_t         Result of the operation.
*
* \pre          An LE_PSM must be registered a priori.
********************************************************************************** */
bleResult_t L2ca_DeregisterLePsm
(
    uint16_t    lePsm
);

/*! *********************************************************************************
* \brief        Initiates a connection with a peer device for a registered LE_PSM.
*
* \param[in]    lePsm               Bluetooth SIG or Vendor LE_PSM.
* \param[in]    deviceId            The DeviceID for which the command is intended.
* \param[in]    initialCredits      Initial credits.
*
* \return       bleResult_t         Result of the operation.
*
* \pre          An LE_PSM must be registered a priori.
********************************************************************************** */
bleResult_t L2ca_ConnectLePsm
(
    uint16_t    lePsm,
    deviceId_t  deviceId,
    uint16_t    initialCredits
);

/*! *********************************************************************************
* \brief        Disconnects a peer device for a registered LE_PSM.
*
* \param[in]    deviceId            The DeviceID for which the command is intended.
* \param[in]    channelId           The L2CAP Channel Id assigned on the initiator.
*
* \return       bleResult_t         Result of the operation.
*
* \pre          A connection must have already been created.
*
* \remarks      Once this command is issued, all incoming data in transit for this
*               device shall be discarded and any new additional outgoing data shall
*               be discarded.
********************************************************************************** */
bleResult_t L2ca_DisconnectLeCbChannel
(
    deviceId_t  deviceId,
    uint16_t    channelId
);

/*! *********************************************************************************
* \brief        Terminates an L2CAP channel.
*
* \param[in]    lePsm               Bluetooth SIG or Vendor LE_PSM.
* \param[in]    deviceId            The DeviceID for which the command is intended.
* \param[in]    refuseReason        Reason to refuse the channel creation.
*
* \return       bleResult_t         Result of the operation.
*
* \remarks      This interface can be used for a connection pending creation.
********************************************************************************** */
bleResult_t L2ca_CancelConnection
(
    uint16_t    lePsm,
    deviceId_t  deviceId,
    l2caLeCbConnectionRequestResult_t refuseReason
);

/*! *********************************************************************************
* \brief        Sends a data packet through a Credit-Based Channel.
*
* \param[in]    deviceId            The DeviceID for which the command is intended.
* \param[in]    channelId           The L2CAP Channel Id assigned on the initiator.
* \param[in]    pPacket             Data buffer to be transmitted.
* \param[in]    packetLength        Length of the data buffer.
*
* \return       bleResult_t         Result of the operation.
*
* \pre          An L2CAP Credit Based connection must be in place.
********************************************************************************** */
bleResult_t L2ca_SendLeCbData
(
    deviceId_t        deviceId,
    uint16_t          channelId,
    const uint8_t*    pPacket,
    uint16_t          packetLength
);

/*! *********************************************************************************
* \brief        Sends credits to a device when capable of receiving additional
*               LE-frames.
*
* \param[in]    deviceId            The DeviceID to which credits are given.
* \param[in]    channelId           The L2CAP Channel Id assigned on the initiator.
* \param[in]    credits             Number of credits to be given.
*
* \return       bleResult_t         Result of the operation.
*
* \pre          An L2CAP Credit Based connection must be in place.
********************************************************************************** */
bleResult_t L2ca_SendLeCredit
(
    deviceId_t  deviceId,
    uint16_t    channelId,
    uint16_t    credits
);

#if defined(gBLE52_d) && (gBLE52_d == TRUE)
/*! *********************************************************************************
* \brief        Initiates a connection with a peer device for a registered LE_PSM.
*               Enhanced mode: up to 5 channels can be opened.
*
* \param[in]    lePsm               Bluetooth SIG or Vendor LE_PSM.
* \param[in]    deviceId            The DeviceID for which the command is intended.
* \param[in]    initialCredits      Initial credits.
* \param[in]    noOfChannels        Number of channels to request for opening. Max 5.
* \param[in]    aCids               List of cids if an Enhanced Connection Request has
*                                   been previously received. NULL if not.
*
* \return       bleResult_t         Result of the operation.
*
* \pre          A LE_PSM must be registered a priori.
********************************************************************************** */
bleResult_t L2ca_EnhancedConnectLePsm
(
    uint16_t    lePsm,
    deviceId_t  deviceId,
    uint16_t    mtu,
    uint16_t    initialCredits,
    uint8_t     noOfChannels,
    uint16_t    *aCids
);

/*! *********************************************************************************
* \brief        Reconfigures up to 5 channels with new values for MTU and/or MPS.
*
* \param[in]    deviceId            The DeviceID for which the command is intended.
* \param[in]    newMtu              New MTU value to be configured.
* \param[in]    newMps              New MPS value to be configured.
* \param[in]    noOfChannels        Number of channels to reconfigure. Max 5.
* \param[in]    *aCids              The list of CIDs (endpoints on local device).
*
* \return       bleResult_t         Result of the operation.
********************************************************************************** */
bleResult_t L2ca_EnhancedChannelReconfigure
(
    deviceId_t  deviceId,
    uint16_t    newMtu,
    uint16_t    newMps,
    uint8_t     noOfChannels,
    uint16_t    *aCids
);

/*! *********************************************************************************
* \brief        Termination of pending L2CAP channels.
*
* \param[in]    lePsm            Bluetooth SIG or Vendor LE_PSM.
* \param[in]    deviceId         The DeviceID for which the command is intended.
* \param[in]    refuseReason     Reason to refuse the channel creation.
* \param[in]    noOfChannels     Number of channels to disconnect. Max 5.
* \param[in]    *aCids           The list of CIDs (endpoints on local device).
*
* \return       bleResult_t      Result of the operation.
*
* \remarks      This interface can be used for an enhanced connection pending
*               creation.
********************************************************************************** */
bleResult_t L2ca_EnhancedCancelConnection
(
    uint16_t    lePsm,
    deviceId_t  deviceId,
    l2caLeCbConnectionRequestResult_t refuseReason,
    uint8_t     noOfChannels,
    uint16_t    *aCids
);
#endif /* gBLE52_d */

#ifdef __cplusplus
}
#endif

#endif /* L2CA_CB_INTERFACE_H */

/*! *********************************************************************************
* @}
********************************************************************************** */

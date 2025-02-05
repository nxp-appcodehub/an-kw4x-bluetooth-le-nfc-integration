/*! *********************************************************************************
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* Copyright 2016-2020 NXP
* All rights reserved.
*
* \file
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */
#ifndef GATT_DECL_X_H
#define GATT_DECL_X_H

#define PRIMARY_SERVICE                     XDECL_PRIMARY_SERVICE
#define PRIMARY_SERVICE_UUID32              XDECL_PRIMARY_SERVICE_UUID32
#define PRIMARY_SERVICE_UUID128             XDECL_PRIMARY_SERVICE_UUID128
#define SECONDARY_SERVICE                   XDECL_SECONDARY_SERVICE
#define SECONDARY_SERVICE_UUID32            XDECL_SECONDARY_SERVICE_UUID32
#define SECONDARY_SERVICE_UUID128           XDECL_SECONDARY_SERVICE_UUID128
#define INCLUDE                             XDECL_INCLUDE
#define INCLUDE_CUSTOM                      XDECL_INCLUDE_CUSTOM
#define CHARACTERISTIC                      XDECL_CHARACTERISTIC
#define CHARACTERISTIC_UUID32               XDECL_CHARACTERISTIC_UUID32
#define CHARACTERISTIC_UUID128              XDECL_CHARACTERISTIC_UUID128
#define VALUE                               XDECL_VALUE
#define VALUE_UUID32                        XDECL_VALUE_UUID32
#define VALUE_UUID128                       XDECL_VALUE_UUID128
#define VALUE_VARLEN                        XDECL_VALUE_VARLEN
#define VALUE_UUID32_VARLEN                 XDECL_VALUE_UUID32_VARLEN
#define VALUE_UUID128_VARLEN                XDECL_VALUE_UUID128_VARLEN
#define CCCD                                XDECL_CCCD
#define DESCRIPTOR                          XDECL_DESCRIPTOR
#define DESCRIPTOR_UUID32                   XDECL_DESCRIPTOR_UUID32
#define DESCRIPTOR_UUID128                  XDECL_DESCRIPTOR_UUID128
#define CHARACTERISTIC_AGGREGATE            XDECL_CHARACTERISTIC_AGGREGATE

#include "gatt_db.h"

#undef PRIMARY_SERVICE
#undef PRIMARY_SERVICE_UUID32
#undef PRIMARY_SERVICE_UUID128
#undef SECONDARY_SERVICE
#undef SECONDARY_SERVICE_UUID32
#undef SECONDARY_SERVICE_UUID128
#undef INCLUDE
#undef INCLUDE_CUSTOM
#undef CHARACTERISTIC
#undef CHARACTERISTIC_UUID32
#undef CHARACTERISTIC_UUID128
#undef VALUE
#undef VALUE_UUID32
#undef VALUE_UUID128
#undef VALUE_VARLEN
#undef VALUE_UUID32_VARLEN
#undef VALUE_UUID128_VARLEN
#undef CCCD
#undef DESCRIPTOR
#undef DESCRIPTOR_UUID32
#undef DESCRIPTOR_UUID128
#undef CHARACTERISTIC_AGGREGATE

#endif /* GATT_DECL_X_H */

/*! *********************************************************************************
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* Copyright 2016-2020 NXP
* All rights reserved.
*
* \file
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef GATT_SIZE_X_H
#define GATT_SIZE_X_H

#define PRIMARY_SERVICE                         XSIZE_PRIMARY_SERVICE
#define PRIMARY_SERVICE_UUID32                  XSIZE_PRIMARY_SERVICE_UUID32
#define PRIMARY_SERVICE_UUID128                 XSIZE_PRIMARY_SERVICE_UUID128
#define SECONDARY_SERVICE                       XSIZE_SECONDARY_SERVICE
#define SECONDARY_SERVICE_UUID32                XSIZE_SECONDARY_SERVICE_UUID32
#define SECONDARY_SERVICE_UUID128               XSIZE_SECONDARY_SERVICE_UUID128
#define INCLUDE                                 XSIZE_INCLUDE
#define INCLUDE_CUSTOM                          XSIZE_INCLUDE_CUSTOM
#define CHARACTERISTIC                          XSIZE_CHARACTERISTIC
#define CHARACTERISTIC_UUID32                   XSIZE_CHARACTERISTIC_UUID32
#define CHARACTERISTIC_UUID128                  XSIZE_CHARACTERISTIC_UUID128
#define VALUE                                   XSIZE_VALUE
#define VALUE_UUID32                            XSIZE_VALUE_UUID32
#define VALUE_UUID128                           XSIZE_VALUE_UUID128
#define VALUE_VARLEN                            XSIZE_VALUE_VARLEN
#define VALUE_UUID32_VARLEN                     XSIZE_VALUE_UUID32_VARLEN
#define VALUE_UUID128_VARLEN                    XSIZE_VALUE_UUID128_VARLEN
#define CCCD                                    XSIZE_CCCD
#define DESCRIPTOR                              XSIZE_DESCRIPTOR
#define DESCRIPTOR_UUID32                       XSIZE_DESCRIPTOR
#define DESCRIPTOR_UUID128                      XSIZE_DESCRIPTOR
#define CHARACTERISTIC_AGGREGATE                XSIZE_CHARACTERISTIC_AGGREGATE

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

#endif /* GATT_SIZE_X_H */

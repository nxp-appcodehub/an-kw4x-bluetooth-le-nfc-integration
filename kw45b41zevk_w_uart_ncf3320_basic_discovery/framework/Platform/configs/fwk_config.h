/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FWK_FRAMEWORK_CONFIG_H_
#define _FWK_FRAMEWORK_CONFIG_H_

#if !defined(gPlatformUseHwParameter_d)
#define gPlatformUseHwParameter_d 1
#endif

/*! Lowpower Constraint setting for various resources
    The value shall map with the type defintion PWR_LowpowerMode_t in PWR_Interface.h
      0 : no LowPower, WFI only
      1 : Reserved
      2 : Deep Sleep
      3 : Power Down
      4 : Deep Power Down
    Note that if a Ble State is configured to Power Down mode, please make sure
       gLowpowerPowerDownEnable_d variable is set to 1 in Linker Script
    The PowerDown mode will allow lowest power consumption but the wakeup time is longer
       and the first 16K in SRAM is reserved to ROM code (this section will be corrupted on
       each power down wakeup so only temporary data could be stored there.)     */

#define gSecLibSssConstraint_c 2

/* Defines the calibration duration of the ADC, it will block the task during this time in milisec before trigger the
 * ADC on a channel*/
#define gSensorsAdcCalibrationDurationInMs_c 4U

#define gPlatformRamStartAddress_c (0x20000000U)
#define gPlatformRamEndAddress_c   (0x2001BFFFU)

#define gPlatformFlashStartAddress_c (FSL_FEATURE_FLASH_PFLASH_START_ADDRESS)
#define gPlatformFlashEndAddress_c   (FSL_FEATURE_FLASH_PFLASH_BLOCK_SIZE)

#endif /* _FWK_PLATFORM_H_ */

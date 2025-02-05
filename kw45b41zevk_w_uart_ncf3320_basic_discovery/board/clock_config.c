/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/
/*
 * How to setup clock using clock driver functions:
 *
 * 1. Call CLOCK_InitXXX() to configure corresponding SCG clock source.
 *    Note: The clock could not be set when it is being used as system clock.
 *    In default out of reset, the CPU is clocked from FIRC,
 *    so before setting FIRC, change to use another avaliable clock source.
 *
 * 2. Call CLOCK_SetXtal0Freq() to set XTAL0 frequency based on board settings.
 *
 * 3. Call CLOCK_SetXxxModeSysClkConfig() to set SCG mode for Xxx run mode.
 *    Wait until the system clock source is changed to target source.
 *
 */

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Clocks v8.0
processor: KW45B41Z83xxxA
package_id: KW45B41Z83AFTA
mcu_data: ksdk2_0
processor_version: 0.0.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

#include "fsl_ccm32k.h"
#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_CONFIG_SetScgOutSel
 * Description   : Set the SCG clock out select (CLKOUTSEL).
 * Param setting : The selected clock source.
 *
 *END**************************************************************************/
static void CLOCK_CONFIG_SetScgOutSel(clock_clkout_src_t setting)
{
     SCG0->CLKOUTCNFG = SCG_CLKOUTCNFG_CLKOUTSEL(setting);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPC_SetActiveModeCoreLDORegulator
 * Description   : Configs Core LDO VDD Regulator in Active mode.
 * Param setting : The selected LDO VDD regulator setting.
 *
 *END**************************************************************************/
static void SPC_SetActiveModeCoreLDORegulator(uint8_t setting)
{
    uint32_t reg;

    reg = SPC0->ACTIVE_CFG;
    reg &= ~SPC_ACTIVE_CFG_CORELDO_VDD_LVL_MASK;
    reg |= SPC_ACTIVE_CFG_CORELDO_VDD_LVL(setting);

    SPC0->ACTIVE_CFG = reg;

    while ((SPC0->SC & SPC_SC_BUSY_MASK) != 0UL)
    {
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_CONFIG_FircSafeConfig
 * Description   : This function is used to safely configure FIRC clock.
 *                 In default out of reset, the CPU is clocked from FIRC.
 *                 Before setting FIRC, change to use SIRC as system clock,
 *                 then configure FIRC.
 * Param fircConfig  : FIRC configuration.
 *
 *END**************************************************************************/
static void CLOCK_CONFIG_FircSafeConfig(const scg_firc_config_t *fircConfig)
{
    scg_sys_clk_config_t curConfig;
    scg_sys_clk_config_t sysClkSafeConfigSource = {
         .divSlow = (uint32_t)kSCG_SysClkDivBy4, /* Slow clock divider */
         .divCore = (uint32_t)kSCG_SysClkDivBy1, /* Core clock divider */
         .src = (uint32_t)kSCG_SysClkSrcSirc,    /* System clock source */
    };
    /* Change to use SIRC as system clock source to prepare to change FIRCCFG register */
    CLOCK_SetRunModeSysClkConfig(&sysClkSafeConfigSource);
    /* Wait for clock source switch finished */
    do
    {
        CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != sysClkSafeConfigSource.src);

    /* Init Firc */
    (void)CLOCK_InitFirc(fircConfig);
}

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/
void BOARD_InitBootClocks(void)
{
    BOARD_BootClockRUN();
}

/*******************************************************************************
 ********************** Configuration BOARD_BootClockRUN ***********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockRUN
called_from_default_init: true
outputs:
- {id: BUS_CLK.outFreq, value: 48 MHz}
- {id: CPU_CLK.outFreq, value: 48 MHz}
- {id: FIRC_REF_TRIM_CLK.outFreq, value: 1 MHz}
- {id: FRO192M_CLK.outFreq, value: 96 MHz}
- {id: FRO6M_CLK.outFreq, value: 6 MHz}
- {id: Platform_clock.outFreq, value: 48 MHz}
- {id: ROSC_CLK.outFreq, value: 32.768 kHz}
- {id: SCGCLKOUT_CLK.outFreq, value: 16 MHz}
- {id: SLOW_CLK.outFreq, value: 16 MHz}
- {id: SOSC_CLK.outFreq, value: 32 MHz}
- {id: System_clock.outFreq, value: 48 MHz}
settings:
- {id: CCM32K.CCM32K_32K_SEL.sel, value: CCM32K.OSC_32K}
- {id: CCM32K_FRO32K_CTRL_FRO_EN_CFG, value: Disabled}
- {id: CCM32K_OSC32K_CTRL_OSC_EN_CFG, value: Enabled}
- {id: SCG.DIVCORE.scale, value: '2', locked: true}
- {id: SCG.DIVSLOW.scale, value: '3', locked: true}
- {id: SCG.FIRC_TRIMDIV.scale, value: '32', locked: true}
- {id: SCG_FIRCCSR_TRIMEN_CFG, value: Enabled}
- {id: SCG_FIRCCSR_UPEN_CFG, value: Enabled}
- {id: SCG_SOSCCSR_SOSCEN_CFG, value: Enabled}
sources:
- {id: CCM32K.OSC_32K.outFreq, value: 32.768 kHz, enabled: true}
- {id: SOSC.SOSC.outFreq, value: 32 MHz, enabled: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for BOARD_BootClockRUN configuration
 ******************************************************************************/
static const scg_firc_trim_config_t FircTrimConfig_BOARD_BootClockRUN =
{
    .trimMode = kSCG_FircTrimUpdate,              /* FIRC trim is enabled and trim value update is enabled */
    .trimSrc = kSCG_FircTrimSrcSysOsc,            /* Trim source is System OSC */
    .trimDiv = 31U,                               /* Divided by 32 */
    .trimCoar = 0U,                               /* Trim value, see Reference Manual for more information */
    .trimFine = 0U,                               /* Trim value, see Reference Manual for more information */
};
const scg_sys_clk_config_t g_sysClkConfig_BOARD_BootClockRUN =
{
    .divSlow = (uint32_t)kSCG_SysClkDivBy3,       /* Slow Clock Divider: divided by 3 */
    .divBus = (uint32_t)kSCG_SysClkDivBy1,        /* Bus Clock Divider: divided by 1 */
    .divCore = (uint32_t)kSCG_SysClkDivBy2,       /* Core Clock Divider: divided by 2 */
    .src = (uint32_t)kSCG_SysClkSrcFirc,          /* Fast IRC is selected as System Clock Source */
};
const scg_sosc_config_t g_scgSysOscConfig_BOARD_BootClockRUN =
{
    .freq = 32000000U,                            /* System Oscillator frequency: 32000000Hz */
    .monitorMode = kSCG_SysOscMonitorDisable,     /* System OSC Clock Monitor is enabled */
    .enableMode = kSCG_SoscEnable,                /* System OSC Enable */
};
const scg_sirc_config_t g_scgSircConfig_BOARD_BootClockRUN =
{
    .enableMode = kSCG_SircDisableInSleep,        /* Slow IRC is disabled in sleep modes */
};
const scg_firc_config_t g_scgFircConfig_BOARD_BootClockRUN =
{
    .enableMode = kSCG_FircEnable,                /* Fast IRC is enabled */
    .range = kSCG_FircRange96M,                   /* 96 Mhz FIRC clock selected */
    .trimConfig = &FircTrimConfig_BOARD_BootClockRUN,
};
/*TODO: used in CCM32K_Set32kOscConfig , to be restored */
#if 0
static const ccm32k_osc_config_t g_ccm32kOscConfig_BOARD_BootClockRUN =
{
    .coarseAdjustment = kCCM32K_OscCoarseAdjustmentRange0,/* ESR_Range0 */
    .enableInternalCapBank = false,               /* Internal capacitance bank is not enabled */
    .xtalCap = kCCM32K_OscXtal0pFCap,             /* 0 pF */
    .extalCap = kCCM32K_OscExtal0pFCap,           /* 0 pF */
};
#endif
/*******************************************************************************
 * Code for BOARD_BootClockRUN configuration
 ******************************************************************************/
void BOARD_BootClockRUN(void)
{
    scg_sys_clk_config_t curConfig;

    /* Unlock FIRC, SIRC, ROSC and SOSC control status registers */
    CLOCK_UnlockFircControlStatusReg();
    CLOCK_UnlockSircControlStatusReg();
    CLOCK_UnlockRoscControlStatusReg();
    CLOCK_UnlockSysOscControlStatusReg();

    /* Monitor is disabe */
    CLOCK_SetRoscMonitorMode(kSCG_RoscMonitorDisable);

    CLOCK_SetXtal32Freq(BOARD_BOOTCLOCKRUN_ROSC_CLOCK);

    /* Regulate Core LDO to Mid Drive Voltage (1.0V) to make the Core run at maximum 48MHz */
    SPC_SetActiveModeCoreLDORegulator(1U);
    /* Init FIRC */
    CLOCK_CONFIG_FircSafeConfig(&g_scgFircConfig_BOARD_BootClockRUN);
    /* Set SCG to FIRC mode */
    CLOCK_SetRunModeSysClkConfig(&g_sysClkConfig_BOARD_BootClockRUN);
    /* Wait for clock source switch finished */
    do
    {
        CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != g_sysClkConfig_BOARD_BootClockRUN.src);
    /* Initializes SOSC according to board configuration */
    (void)CLOCK_InitSysOsc(&g_scgSysOscConfig_BOARD_BootClockRUN);
    /* Set the XTAL0 frequency based on board settings */
    CLOCK_SetXtal0Freq(g_scgSysOscConfig_BOARD_BootClockRUN.freq);
    /* Init SIRC */
    (void)CLOCK_InitSirc(&g_scgSircConfig_BOARD_BootClockRUN);
    /* Set SystemCoreClock variable */
    SystemCoreClock = BOARD_BOOTCLOCKRUN_CORE_CLOCK;
    /* Set SCG CLKOUT selection. */
    CLOCK_CONFIG_SetScgOutSel(kClockClkoutSelScgSlow);
}

/*******************************************************************************
 ********************* Configuration BOARD_BootClockHSRUN **********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockHSRUN
outputs:
- {id: BUS_CLK.outFreq, value: 96 MHz}
- {id: CPU_CLK.outFreq, value: 96 MHz}
- {id: FRO192M_CLK.outFreq, value: 96 MHz}
- {id: FRO6M_CLK.outFreq, value: 6 MHz}
- {id: Platform_clock.outFreq, value: 96 MHz}
- {id: ROSC_CLK.outFreq, value: 32.768 kHz}
- {id: SCGCLKOUT_CLK.outFreq, value: 24 MHz}
- {id: SLOW_CLK.outFreq, value: 24 MHz}
- {id: System_clock.outFreq, value: 96 MHz}
settings:
- {id: VDDCore, value: voltage_1v1}
- {id: CCM32K.CCM32K_32K_SEL.sel, value: CCM32K.OSC_32K}
- {id: CCM32K_OSC32K_CTRL_OSC_EN_CFG, value: Enabled}
- {id: SCG.DIVCORE.scale, value: '1', locked: true}
- {id: SCG.DIVSLOW.scale, value: '4', locked: true}
sources:
- {id: CCM32K.OSC_32K.outFreq, value: 32.768 kHz, enabled: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for BOARD_BootClockHSRUN configuration
 ******************************************************************************/
const scg_sys_clk_config_t g_sysClkConfig_BOARD_BootClockHSRUN =
{
    .divSlow = (uint32_t)kSCG_SysClkDivBy4,       /* Slow Clock Divider: divided by 4 */
    .divBus = (uint32_t)kSCG_SysClkDivBy1,        /* Bus Clock Divider: divided by 1 */
    .divCore = (uint32_t)kSCG_SysClkDivBy1,       /* Core Clock Divider: divided by 1 */
    .src = (uint32_t)kSCG_SysClkSrcFirc,          /* Fast IRC is selected as System Clock Source */
};
const scg_sosc_config_t g_scgSysOscConfig_BOARD_BootClockHSRUN =
{
    .freq = 0U,                                   /* System Oscillator frequency: 0Hz */
    .monitorMode = kSCG_SysOscMonitorDisable,     /* System OSC Clock Monitor is enabled */
    .enableMode = kSCG_SoscDisable,               /* System OSC disabled */
};
const scg_sirc_config_t g_scgSircConfig_BOARD_BootClockHSRUN =
{
    .enableMode = kSCG_SircDisableInSleep,        /* Slow IRC is disabled in sleep modes */
};
const scg_firc_config_t g_scgFircConfig_BOARD_BootClockHSRUN =
{
    .enableMode = kSCG_FircEnable,                /* Fast IRC is enabled */
    .range = kSCG_FircRange96M,                   /* 96 Mhz FIRC clock selected */
    .trimConfig = NULL,
};

/*******************************************************************************
 * Code for BOARD_BootClockHSRUN configuration
 ******************************************************************************/
void BOARD_BootClockHSRUN(void)
{
    scg_sys_clk_config_t curConfig;

    /* Unlock FIRC, SIRC, ROSC and SOSC control status registers */
    CLOCK_UnlockFircControlStatusReg();
    CLOCK_UnlockSircControlStatusReg();
    CLOCK_UnlockRoscControlStatusReg();
    CLOCK_UnlockSysOscControlStatusReg();

    /* Monitor is disabe */
    CLOCK_SetRoscMonitorMode(kSCG_RoscMonitorDisable);

    CLOCK_SetXtal32Freq(BOARD_BOOTCLOCKRUN_ROSC_CLOCK);

    /* Regulate Core LDO to Normal Voltage (1.1V) to make the Core run at maximum 96MHz */
    SPC_SetActiveModeCoreLDORegulator(2U);
    /* Init FIRC */
    CLOCK_CONFIG_FircSafeConfig(&g_scgFircConfig_BOARD_BootClockHSRUN);
    /* Set SCG to FIRC mode */
    CLOCK_SetRunModeSysClkConfig(&g_sysClkConfig_BOARD_BootClockHSRUN);
    /* Wait for clock source switch finished */
    do
    {
        CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != g_sysClkConfig_BOARD_BootClockHSRUN.src);
    /* Init SIRC */
    (void)CLOCK_InitSirc(&g_scgSircConfig_BOARD_BootClockHSRUN);
    /* Set SystemCoreClock variable */
    SystemCoreClock = BOARD_BOOTCLOCKHSRUN_CORE_CLOCK;
    /* Set SCG CLKOUT selection. */
    CLOCK_CONFIG_SetScgOutSel(kClockClkoutSelScgSlow);
}


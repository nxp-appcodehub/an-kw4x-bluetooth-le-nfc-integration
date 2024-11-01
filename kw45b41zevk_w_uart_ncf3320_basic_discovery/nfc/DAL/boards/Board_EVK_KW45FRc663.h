/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BOARD_EVK_KW45FRC663_H_
#define BOARD_EVK_KW45FRC663_H_


#define GPIO_PORT_A         0    /* Same macro for GPIOA/PORTA */
#define GPIO_PORT_B         1    /* Same macro for GPIOB/PORTB */
#define GPIO_PORT_C         2    /* Same macro for GPIOC/PORTC */
#define GPIO_PORT_D         3    /* Same macro for GPIOD/PORTD */
#define GPIO_PORT_E         4    /* Same macro for GPIOE/PORTE */

/******************************************************************
 * Board Pin/Gpio configurations
 ******************************************************************/
/*! @brief The handle of LED */
typedef void *irq_handle_t;

/*! @brief Definition of irq handle size as HAL_GPIO_HANDLE_SIZE  */
#define IRQ_HANDLE_SIZE (16U)

#define IRQ_HANDLE_ARRAY_DEFINE(name, count) \
    uint32_t name[count][((IRQ_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))]   
   
/* Pin configuration format : Its a 32 bit format where every byte represents a field as shown below.
 * | Byte3 | Byte2 | Byte1      | Byte0 |
 * |  --   |  --   | GPIO/PORT  | PIN   |
 * */
#define PHDRIVER_IRQ_GPIO_PORT_INSTANCE     2U
#define PHDRIVER_IRQ_GPIO_PIN               0U
#define PHDRIVER_IRQ_GPIO_PIN_DEFAULT_STATE 1U

#define PHDRIVER_PIN_RESET  ((GPIO_PORT_C << 8) | 1)
#define PHDRIVER_PIN_IRQ    ((GPIO_PORT_C << 8) | 0)

   
/* These pins are used for EMVCo Interoperability test status indication,
 * not for the generic Reader Library implementation.
 */
#define PHDRIVER_PIN_GLED      ((GPIO_PORT_A << 8) | 19)
#define PHDRIVER_PIN_RLED      ((GPIO_PORT_A << 8) | 21)
#define PHDRIVER_PIN_SUCCESS   ((GPIO_PORT_A << 8) | 20)
#define PHDRIVER_PIN_FAIL      ((GPIO_PORT_B << 8) | 0)

/******************************************************************
 * PIN Pull-Up/Pull-Down configurations.
 ******************************************************************/
#define PHDRIVER_PIN_RESET_PULL_CFG    PH_DRIVER_PULL_DOWN
#define PHDRIVER_PIN_IRQ_PULL_CFG      PH_DRIVER_PULL_UP
#define PHDRIVER_PIN_NSS_PULL_CFG      PH_DRIVER_PULL_UP

/******************************************************************
 * IRQ PIN NVIC settings
 ******************************************************************/
#define EINT_IRQn                 GPIOC_INT0_IRQn
#define EINT_PRIORITY             8
#if !gAppButtonCnt_c
#define CLIF_IRQHandler           GPIOC_INT0_IRQHandler
#endif
#define PIN_IRQ_TRIGGER_TYPE      PH_DRIVER_INTERRUPT_FALLINGEDGE

/*****************************************************************
 * Front End Reset logic level settings
 ****************************************************************/
#define PH_DRIVER_SET_HIGH            1          /**< Logic High. */
#define PH_DRIVER_SET_LOW             0          /**< Logic Low. */
#define RESET_POWERDOWN_LEVEL         PH_DRIVER_SET_HIGH
#define RESET_POWERUP_LEVEL           PH_DRIVER_SET_LOW


/*****************************************************************
 * SPI Configuration
 ****************************************************************/
#define PHDRIVER_KSDK_SPI_POLLING          /* Enable to perform SPI transfer using polling method. */
#define PHDRIVER_KSDK_SPI_MASTER           LPSPI0
#define PHDRIVER_KSDK_SPI_DATA_RATE        5000000U
#define PHDRIVER_KSDK_SPI_CLK_SRC          kCLOCK_Lpspi0
#define PHDRIVER_KSDK_SPI_IRQ              LPSPI0_IRQn

#define DSPI_IRQ_PRIORITY     7

#define ENABLE_PORT_SSP_1     kCLOCK_PortA
#define PORT_SSP_1            PORTA
#define FIRST_PINNUM_SSP      18

#define ENABLE_PORT_SSP_2     kCLOCK_PortA
#define PORT_SSP_2            PORTA
#define SECOND_PINNUM_SSP     19

#define ENABLE_PORT_SSP_3     kCLOCK_PortA
#define PORT_SSP_3            PORTA
#define THIRD_PINNUM_SSP      17

#define PHDRIVER_PIN_SSEL     ((GPIO_PORT_A << 8) | 16)

/*****************************************************************
 * Timer Configuration
 ****************************************************************/
#define PH_DRIVER_KSDK_PIT_TIMER          LPIT0
#define PH_DRIVER_KSDK_PIT_CLK            kCLOCK_ScgSircClk
#define PH_DRIVER_KSDK_TIMER_CHANNEL      kLPIT_Chnl_0    /**< PIT channel number 0 */
#define PH_DRIVER_KSDK_TIMER_NVIC         LPIT0_IRQn
#define PH_DRIVER_KSDK_TIMER_PRIORITY     8
#define PIT_DriverIRQHandler    LPIT0_IRQHandler

#endif /* BOARD_EVK_KW45FRC663_H_ */

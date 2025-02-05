/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_COMP_H_
#define _BOARD_COMP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "fsl_component_serial_manager.h"
#include "fsl_component_led.h"
#include "fsl_component_button.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*Mapping led pin to the correct device pins*/
#define BOARD_MONOCHROME_GPIO_PORT_INSTANCE     1U
#define BOARD_MONOCHROME_GPIO_PIN               0U
#define BOARD_MONOCHROME_GPIO_PIN_DEFAULT_STATE 0U

/*Mapping led pin to the correct device pins*/
#define BOARD_RGB_GREEN_GPIO_PORT_INSTANCE     0U
#define BOARD_RGB_GREEN_GPIO_PIN               19U
#define BOARD_RGB_GREEN_GPIO_PIN_DEFAULT_STATE 0U

/*Mapping led pin to the correct device pins*/
#define BOARD_RGB_BLUE_GPIO_PORT_INSTANCE     0U
#define BOARD_RGB_BLUE_GPIO_PIN               20U
#define BOARD_RGB_BLUE_GPIO_PIN_DEFAULT_STATE 0U

/*Mapping led pin to the correct device pins*/
#define BOARD_RGB_RED_GPIO_PORT_INSTANCE     0U
#define BOARD_RGB_RED_GPIO_PIN               21U
#define BOARD_RGB_RED_GPIO_PIN_DEFAULT_STATE 0U

/*Mapping button pin to the correct device pins*/
#define BOARD_BUTTON0_GPIO_PORT_INSTANCE     3U
#define BOARD_BUTTON0_GPIO_PIN               1U
#define BOARD_BUTTON0_GPIO_PIN_DEFAULT_STATE 1U

#define BOARD_BUTTON1_GPIO_PORT_INSTANCE     2U
#define BOARD_BUTTON1_GPIO_PIN               6U
#define BOARD_BUTTON1_GPIO_PIN_DEFAULT_STATE 1U

#if (defined(gAppLedCnt_c) && (gAppLedCnt_c > 0))
#if (defined(gAppLedCnt_c) && (gAppLedCnt_c == 1))
/* Even if the BSP supports 2 LEDs the Application may want one LED only but
 * that LED may RGB or monochrome */
#if defined(gAppRequireRgbLed_c) && (gAppRequireRgbLed_c > 0)
#define gBoardLedRgbHdl ((led_handle_t)g_ledHandle[0])
#else
#define gBoardLedMonochromeHdl ((led_handle_t)g_ledHandle[0])
#endif
#else
#define gBoardLedRgbHdl        ((led_handle_t)g_ledHandle[1])
#define gBoardLedMonochromeHdl ((led_handle_t)g_ledHandle[0])
#endif
#endif

#if (defined gBoardLedMonochromeHdl)
#define BOARD_MONOCHROME_LED_ACTUATE(__on__) LED_TurnOnOff(gBoardLedMonochromeHdl, __on__)
#define BOARD_MONOCHROME_LED_FLASH(_flash_config_) \
    LED_Flash(gBoardLedMonochromeHdl, (led_flash_config_t *)_flash_config_)
#else
#define BOARD_MONOCHROME_LED_ACTUATE(...)
#define BOARD_MONOCHROME_LED_FLASH(...)
#endif

#if (defined gBoardLedRgbHdl)
#define BOARD_RGB_LED_ACTUATE(__on__)       LED_TurnOnOff(gBoardLedRgbHdl, __on__)
#define BOARD_RGB_LED_SET_COLOR(__color__)  LED_SetColor(gBoardLedRgbHdl, __color__)
#define BOARD_RGB_LED_FLASH(_flash_config_) LED_Flash(gBoardLedRgbHdl, (led_flash_config_t *)_flash_config_)
#else
#define BOARD_RGB_LED_ACTUATE(...)
#define BOARD_RGB_LED_SET_COLOR(...)
#define BOARD_RGB_LED_FLASH(...)
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/* Serial Manager APIs */
void BOARD_InitSerialManager(serial_handle_t serialManagerHandle);

/* Second Serial Manager APIs - Debug Console can not be used as it uses the same UART*/
void BOARD_InitSerialManager2(serial_handle_t serialManagerHandle);

/* DeInit Serial Manager before going lowpower when wake domain is in DS  (device DS3 or lower)*/
void BOARD_UninitSerialManager(void);

/* Reinitialize the serial manager */
void BOARD_ReinitSerialManager(serial_handle_t serialManagerHandle);

/* DeInit Serial Manager before going lowpower when wake domain is in DS  (device DS3 or lower)*/
void BOARD_UninitSerialManager2(void);

/* Reinitialize the serial manager */
void BOARD_ReinitSerialManager2(serial_handle_t serialManagerHandle);

/*!
 * @brief Change the serial manager BaudRate
 *
 * This function is used to Change the serial manager BaudRate.
 *
 * @param serialManagerHandle The serial manager handle.
 * @param baudrate            The baud rate to be set.
 *
 * Note: Read writes handles shall be close before call this function.
 *  Read writes handles shall be open after call this function.
 *  Install Callback shall be called again after calling this function.
 *  @code
 *  ret = SerialManager_CloseWriteHandle((serial_write_handle_t)g_ispCliWriteHandle);
 *  assert(kStatus_SerialManager_Success == ret);
 *  ret = SerialManager_CloseReadHandle((serial_read_handle_t)s_ispCliReadHandle);
 *  assert(kStatus_SerialManager_Success == ret);
 *  BOARD_ChangeSerialManagerBaudRate(gAppSerMgrIf, cli_baudrate);
 *  ret = SerialManager_OpenWriteHandle((serial_handle_t)gAppSerMgrIf, (serial_write_handle_t)g_ispCliWriteHandle);
 *  assert(kStatus_SerialManager_Success == ret);
 *  ret = SerialManager_OpenReadHandle((serial_handle_t)gAppSerMgrIf, (serial_read_handle_t)s_ispCliReadHandle);
 *  assert(kStatus_SerialManager_Success == ret);
 *  ret = SerialManager_InstallRxCallback((serial_read_handle_t)s_ispCliReadHandle, cli_uart_rx_cb, NULL);
 *  assert(kStatus_SerialManager_Success == ret);
 *  @endcode
 */
void BOARD_ChangeSerialManagerBaudRate(serial_handle_t serialManagerHandle, uint32_t baudrate);

/*!
 * @brief Initialize monochrome LED
 *
 * This function is used to initialize monochrome LED.
 *
 * @param ledHandle The led handle .
 * Example below shows how to use this API to initialize PB1 LED.
 *  @code
 *   LED_HANDLE_ARRAY_DEFINE(g_ledHandle, gAppLedCnt_c);
 *   ledHandle = &g_ledHandle[ledHandleIndex];
 *   BOARD_InitMonochromeLed(ledHandle);
 *   LED_TurnOnOff(ledHandle, 1);
 *  @endcode
 */
void BOARD_InitMonochromeLed(led_handle_t ledHandle);

/*!
 * @brief Uninitialize monochrome LED .
 *
 * This function is used to uninitialize monochrome LED when going to low power mode
 * Turns off the LED and sets port as input
 *
 * @param ledHandle The led handle.
 */
void BOARD_UnInitMonochromeLed(led_handle_t ledHandle);

/*!
 * @brief Initialize RGB LED .
 *
 * This function is used to initialize RGB LED.
 *
 * @param ledHandleIndex The led handle index.ledHandleIndex must be less than gAppLedCnt_c.
 * Example below shows how to use this API to initialize PB1 LED.
 *  @code
 *   LED_HANDLE_ARRAY_DEFINE(g_ledHandle, gAppLedCnt_c);
 *   ledHandle = &g_ledHandle[ledHandleIndex];
 *   BOARD_InitRgbLed(ledHandle);
 *   LED_TurnOnOff(ledHandle, 1);
 *  @endcode
 */
void BOARD_InitRgbLed(led_handle_t ledHandle);

/*!
 * @brief Uninitialize RGB LED .
 *
 * This function is used to uninitialize RGB LED when going to low power mode
 * Turns off the LED and sets port as input
 *
 * @param ledHandle The led handle.
 */
void BOARD_UnInitRgbLed(led_handle_t ledHandle);

/*!
 * @brief Initialize button0 .
 *
 * This function is used to initialize button0.
 *
 * @param buttonHandleIndex The led handle index.buttonHandleIndex must be less than gAppButtonCnt_c.
 * Example below shows how to use this API to to initialize PA18 button.
 *  @code
 *   BUTTON_HANDLE_ARRAY_DEFINE(g_buttonHandle, gAppButtonCnt_c);
 *   BOARD_InitButton0(buttonHandleIndex);
 *   BUTTON_GetInput((button_handle_t)&g_buttonHandle[buttonHandleIndex] , &pinState);
 *  @endcode
 */
void BOARD_InitButton0(button_handle_t buttonHandle);

/*!
 * @brief Initialize button1 .
 *
 * This function is used to initialize button1.
 *
 * @param buttonHandleIndex The led handle index.buttonHandleIndex must be less than gAppButtonCnt_c.
 * Example below shows how to use this API to to initialize PA19 button.
 *  @code
 *   BUTTON_HANDLE_ARRAY_DEFINE(g_buttonHandle, gAppButtonCnt_c);
 *   BOARD_InitButton1(buttonHandleIndex);
 *   BUTTON_GetInput((button_handle_t)&g_buttonHandle[buttonHandleIndex] , &pinState);
 *  @endcode
 */
void BOARD_InitButton1(button_handle_t buttonHandle);

/*! @brief Reinitialize the button1
 *
 *  @param buttonHandle handle used for this button
 */
void BOARD_ReinitButton1(button_handle_t buttonHandle);

#endif /* _BOARD_COMP_H_ */

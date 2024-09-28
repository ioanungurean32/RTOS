/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file temphum15.h
 * @brief This file contains API for Temp&Hum 15 Click Driver.
 */

#ifndef TEMPHUM15_H
#define TEMPHUM15_H

#include "stdint.h"

#ifdef __cplusplus
extern "C"{
#endif


/*!
 * @addtogroup temphum15 Temp&Hum 15 Click Driver
 * @brief API for configuring and manipulating Temp&Hum 15 Click driver.
 * @{
 */

/**
 * @defgroup temphum15_cmd Temp&Hum 15 Registers List
 * @brief List of commands of Temp&Hum 15 Click driver.
 */

/**
 * @addtogroup temphum15_cmd
 * @{
 */

/**
 * @brief Temp&Hum 15 description register.
 * @details Specified commands for description of Temp&Hum 15 Click driver.
 */

#define TEMPHUM15_CMD_MEASURE_HIGH_PRECISION                     0xFD
#define TEMPHUM15_CMD_MEASURE_MEDIUM_PRECISION                   0xF6
#define TEMPHUM15_CMD_MEASURE_LOW_PRECISION                      0xE0
#define TEMPHUM15_CMD_READ_SERIAL                                0x89
#define TEMPHUM15_CMD_SOFT_RESET                                 0x94
#define TEMPHUM15_CMD_HEATER_HIGHEST_POW_HIGH_DUR                0x39
#define TEMPHUM15_CMD_HEATER_HIGHEST_POW_LOW_DUR                 0x32
#define TEMPHUM15_CMD_HEATER_MEDIUM_POW_HIGH_DUR                 0x2F
#define TEMPHUM15_CMD_HEATER_MEDIUM_POW_LOW_DUR                  0x24
#define TEMPHUM15_CMD_HEATER_LOWEST_POW_HIGH_DUR                 0x1E
#define TEMPHUM15_CMD_HEATER_LOWEST_POW_LOW_DUR                  0x15

/*! @} */ // temphum15_cmd

/**
 * @defgroup temphum15_set Temp&Hum 15 Registers Settings
 * @brief Settings for registers of Temp&Hum 15 Click driver.
 */

/**
 * @addtogroup temphum15_set
 * @{
 */

/**
 * @brief Temp&Hum 15 device address setting.
 * @details Specified setting for device slave address selection of
 * Temp&Hum 15 Click driver.
 */
#define TEMPHUM15_SET_DEV_ADDR                                   0x44 << 1

/*! @} */ // temphum15_set

/**
 * @addtogroup precision_mode
 * @{
 */

/**
 * @brief Temp&Hum 15 precision mode settings.
 * @details Specified setting for device precision mode selection of
 * Temp&Hum 15 Click driver.
 */

#define TEMPHUM15_MODE_HIGH_PRECISION                            0x00
#define TEMPHUM15_MODE_MEDIUM_PRECISION                          0x01
#define TEMPHUM15_MODE_LOW_PRECISION                             0x02

#define I2C_MASTER_ERROR  -1

/*! @} */ // precision_mode

/**
 * @addtogroup status
 * @{
 */

/**
 * @brief Temp&Hum 15 status return codes.
 * @details Return status codes for I2C data transmission of
 * Temp&Hum 15 Click driver.
 */

#define TEMPHUM15_SUCCESS                                         0
#define TEMPHUM15_ERROR                                          -1

/*! @} */ // status

/*!
 * @addtogroup temphum15 Temp&Hum 15 Click Driver
 * @brief API for configuring and manipulating Temp&Hum 15 Click driver.
 * @{
 */

/**
 * @brief Temp&Hum 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
uint8_t temphum15_init ( );

/**
 * @brief Temp&Hum 15 default configuration function.
 * @details This function executes a default configuration of Temp&Hum 15
 * click board.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
uint8_t temphum15_default_cfg ( );

/**
 * @brief Temp&Hum 15 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
uint8_t temphum15_generic_write ( uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Temp&Hum 15 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
uint8_t temphum15_generic_read ( uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Temp&Hum 15 get temperature and humidity function.
 * @details This function reads temperature and humidity with the
 * power consumption based on the precision mode selected.
 * @param[in] precision_mode : Precision mode setting.
 * @param[out] temp_val : Output temperature value.
 * @param[out] hum_val : Output humidity value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
uint8_t temphum15_get_temp_and_hum ( uint8_t precision_mode, float *temp_val, float *hum_val );

/**
 * @brief Temp&Hum 15 soft reset function.
 * @details This function sends soft reset command to the sensor.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
uint8_t temphum15_soft_reset ( );

/**
 * @brief Temp&Hum 15 read serial number function.
 * @details This function reads unique serial number of the sensor.
 * @param[out] serial_number : Output serial number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
uint8_t temphum15_read_serial ( uint32_t *serial_number );

#ifdef __cplusplus
}
#endif
#endif // TEMPHUM15_H

/*! @} */ // temphum15

// ------------------------------------------------------------------------ END

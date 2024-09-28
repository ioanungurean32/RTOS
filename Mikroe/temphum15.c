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
 * @file temphum15.c
 * @brief Temp&Hum 15 Click Driver.
 */

#include "temphum15.h"
#include "stm32f4xx_hal.h"
#include "../main.h"

#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif
#ifdef RTE_CMSIS_RTOS2                  // when RTE component CMSIS RTOS2 is used
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#endif

// ------------------------------------------------------------- PRIVATE MACROS

#define DEV_TEMPHUM15_RESOLUTION_MAX                                      65535
#define DEV_TEMPHUM15_MULTIPLIER_COEF_TEMP                                175
#define DEV_TEMPHUM15_ADDITION_COEF_TEMP                                  45
#define DEV_TEMPHUM15_MULTIPLIER_COEF_HUM                                 125
#define DEV_TEMPHUM15_ADDITION_COEF_HUM                                   6
#define DEV_TEMPHUM15_HUM_MAX_VALUE                                       100
#define DEV_TEMPHUM15_HUM_MIN_VALUE                                       0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

static void delay_low_repeatability ( void );

static void delay_med_repeatability ( void );

static void delay_high_repeatability ( void );

static void ( *delay_ptr_arr[ 3 ] )( void ) = {
    delay_high_repeatability,
    delay_med_repeatability,
    delay_low_repeatability
};

static void delay_soft_reset ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

I2C_HandleTypeDef hi2c3;


uint8_t temphum15_init ( ) {
	
	 GPIO_InitTypeDef GPIO_InitStruct = {0};
	 
	    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**I2C3 GPIO Configuration
    PC9     ------> I2C3_SDA
    PA8     ------> I2C3_SCL
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_I2C3_CLK_ENABLE();
	
	
	
	  hi2c3.Instance = I2C3;
		hi2c3.Init.ClockSpeed = 100000;
		hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
		hi2c3.Init.OwnAddress1 = 0;
		hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
		hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
		hi2c3.Init.OwnAddress2 = 0;
		hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
		hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
		if (HAL_I2C_Init(&hi2c3) != HAL_OK)
		{
			;//Error_Handler();
		}	

    return 0;//I2C_MASTER_SUCCESS;
}

uint8_t temphum15_default_cfg ( ) {
    // Click default configuration.
    return temphum15_soft_reset ( );
}

uint8_t temphum15_get_temp_and_hum ( uint8_t precision_mode, float *temp_val, float *hum_val ) {
    uint8_t status;
    uint16_t rx_word;
    uint8_t rx_buf[ 6 ];
    uint8_t cmd;
    uint8_t delay_sel;
    
    status = TEMPHUM15_SUCCESS;
    delay_sel = 0;
    
    switch ( precision_mode ) {
        case TEMPHUM15_MODE_MEDIUM_PRECISION: {
            cmd = TEMPHUM15_CMD_MEASURE_MEDIUM_PRECISION;
            delay_sel++;
            break;
        }
        case TEMPHUM15_MODE_LOW_PRECISION: {
            cmd = TEMPHUM15_CMD_MEASURE_LOW_PRECISION;
            delay_sel += 2;
            break;
        }
        default: {
            cmd = TEMPHUM15_CMD_MEASURE_HIGH_PRECISION;
        }
    }
    
   ///////////////////////// status |= i2c_master_write( &ctx->i2c, &cmd, 1 );
	 	status |=  HAL_I2C_Master_Transmit(&hi2c3, TEMPHUM15_SET_DEV_ADDR , &cmd, 1, HAL_MAX_DELAY);	
    
    if ( status != TEMPHUM15_SUCCESS ) {
        return status;
    }
    
    ( *delay_ptr_arr[ delay_sel ] )( );
    
    ///////////////////////status |= i2c_master_read( &ctx->i2c, rx_buf, 6 );
		 status |= HAL_I2C_Master_Receive(&hi2c3, TEMPHUM15_SET_DEV_ADDR , rx_buf, 6, HAL_MAX_DELAY);
    
    rx_word = rx_buf[ 0 ];
    rx_word <<= 8;
    rx_word |= rx_buf[ 1 ];
    
    *temp_val = ( float )rx_word / DEV_TEMPHUM15_RESOLUTION_MAX;
    *temp_val *= DEV_TEMPHUM15_MULTIPLIER_COEF_TEMP;
    *temp_val -= DEV_TEMPHUM15_ADDITION_COEF_TEMP;
    
    rx_word = rx_buf[ 3 ];
    rx_word <<= 8;
    rx_word |= rx_buf[ 4 ];
    
    *hum_val = ( float )rx_word / DEV_TEMPHUM15_RESOLUTION_MAX;
    *hum_val *= DEV_TEMPHUM15_MULTIPLIER_COEF_HUM;
    *hum_val -= DEV_TEMPHUM15_ADDITION_COEF_HUM;
    
    if ( *hum_val > DEV_TEMPHUM15_HUM_MAX_VALUE ) {
        *hum_val = DEV_TEMPHUM15_HUM_MAX_VALUE;
    }
    if ( *hum_val < DEV_TEMPHUM15_HUM_MIN_VALUE ) {
        *hum_val = DEV_TEMPHUM15_HUM_MIN_VALUE;
    }

    return status;
}

uint8_t temphum15_soft_reset ( ) {
    uint8_t status;
    uint8_t cmd;
    
    status = TEMPHUM15_SUCCESS;
    cmd = TEMPHUM15_CMD_SOFT_RESET;
    
    //////////////////////////////status |= i2c_master_write( &ctx->i2c, &cmd, 1 );
	 status |=  HAL_I2C_Master_Transmit(&hi2c3, TEMPHUM15_SET_DEV_ADDR , &cmd, 1, HAL_MAX_DELAY);	
    
    if ( status != TEMPHUM15_SUCCESS ) {
        return status;
    }
    
    delay_soft_reset( );
    
    return status;
}

uint8_t temphum15_read_serial ( uint32_t *serial_number ) {
    uint8_t status;
    uint8_t rx_buf[ 6 ];
    uint8_t cmd;
    
    status = TEMPHUM15_SUCCESS;
    cmd = TEMPHUM15_CMD_READ_SERIAL;
    
    /////////////////////////////////////////status |= i2c_master_write( &ctx->i2c, &cmd, 1 );
	  status |=  HAL_I2C_Master_Transmit(&hi2c3, TEMPHUM15_SET_DEV_ADDR , &cmd, 1, HAL_MAX_DELAY);	
    
    if ( status != TEMPHUM15_SUCCESS ) {
        return status;
    }
    
    delay_soft_reset( );
    
    ////////////////////////////////////////////////status |= i2c_master_read( &ctx->i2c, rx_buf, 6 );
     status |= HAL_I2C_Master_Receive(&hi2c3, TEMPHUM15_SET_DEV_ADDR, rx_buf, 6, HAL_MAX_DELAY);
		
    *serial_number = rx_buf[ 0 ];
    *serial_number <<= 8;
    *serial_number |= rx_buf[ 1 ];
    *serial_number <<= 8;
    *serial_number |= rx_buf[ 3 ];
    *serial_number <<= 8;
    *serial_number |= rx_buf[ 4 ];
    
    return status;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void delay_low_repeatability ( void ) {
    osDelay( 1 );
    osDelay( 1 );
    osDelay( 1 );
}

static void delay_med_repeatability ( void ) {
    osDelay( 5 );
    osDelay( 1 );
}

static void delay_high_repeatability ( void ) {
    osDelay( 10 );
}

static void delay_soft_reset ( void ) {
    osDelay( 1 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// ------------------------------------------------------------------------- END

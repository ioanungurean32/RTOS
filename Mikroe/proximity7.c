/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "proximity7.h"
#include "stm32f4xx_hal.h"
#include "../main.h"

#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif
#ifdef RTE_CMSIS_RTOS2                  // when RTE component CMSIS RTOS2 is used
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#endif
// ------------------------------------------------------------------ VARIABLES

proximity7_const_t g_const_data; 
I2C_HandleTypeDef hi2c1;

PROXIMITY7_RETVAL proximity7_init ( )
{
	 GPIO_InitTypeDef GPIO_InitStruct = {0};
	 
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB7     ------> I2C1_SDA
    PB8     ------> I2C1_SCL
    */
    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;// GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


    /* Peripheral clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
			 
		hi2c1.Instance = I2C1;
		hi2c1.Init.ClockSpeed = 100000;
		hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
		hi2c1.Init.OwnAddress1 = 0;
		hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
		hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
		hi2c1.Init.OwnAddress2 = 0;
		hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
		hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
		if (HAL_I2C_Init(&hi2c1) != HAL_OK)
		{
			;//Error_Handler();
		}
	
	  g_const_data.glass_attenuation = 0.49;
    g_const_data.const_b = 1.862;
    g_const_data.const_c = 0.746;
    g_const_data.const_d = 1.291;
    g_const_data.device_factor = 52.0;
		
		proximity7_default_cfg();
    
		
    return PROXIMITY7_OK;
}

void proximity7_default_cfg ()
{
    uint8_t write_buffer[ 1 ];

    write_buffer[ 0 ] = 0x00;
    proximity7_generic_write( PROXIMITY7_ENABLE | PROXIMITY7_REPEATED_BYTE, &write_buffer[ 0 ], 1 );

    osDelay (100U);  

    proximity7_set_als_integration_time( 400.0 );
    proximity7_set_proximity_integration_time( 2.73 );
    proximity7_set_wait_time( 2.73 );
    proximity7_set_proximity_pulse_count( 8 );

    write_buffer[ 0 ] = PROXIMITY7_LED_DRIVE_100mA |
                      PROXIMITY7_PROXIMITY_DIODE_CH1 |
                      PROXIMITY7_PROXIMITY_GAIN_1x |
                      PROXIMITY7_ALS_GAIN_8x;
    proximity7_generic_write( PROXIMITY7_GAIN_CONTROL | PROXIMITY7_REPEATED_BYTE, &write_buffer[ 0 ], 1 );

    write_buffer[ 0 ] = PROXIMITY7_WAIT_ENA |
                      PROXIMITY7_PROXIMITY_ENA |
                      PROXIMITY7_ALS_ENA |
                      PROXIMITY7_POWER_ON;
   proximity7_generic_write( PROXIMITY7_ENABLE | PROXIMITY7_REPEATED_BYTE, &write_buffer[ 0 ], 1 );
}
uint8_t tx_buf[ 256 ];

void proximity7_generic_write ( uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    
    uint8_t cnt, ret;
	
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
		
		ret = HAL_I2C_Master_Transmit(&hi2c1, PROXIMITY7_DEVICE_ADDRESS << 1, tx_buf, len + 1, HAL_MAX_DELAY);
		if ( ret != HAL_OK )
		{
			UART_WriteString("Eroare Scriere\n");
		}
    
   
}

void proximity7_generic_read ( uint8_t reg, uint8_t *data_buf, uint8_t len )
{  
		uint8_t ret;
	
		HAL_I2C_Master_Transmit(&hi2c1, PROXIMITY7_DEVICE_ADDRESS << 1, &reg, 1, HAL_MAX_DELAY);	
		
		ret = HAL_I2C_Master_Receive(&hi2c1, PROXIMITY7_DEVICE_ADDRESS << 1, data_buf, len, HAL_MAX_DELAY);
		if ( ret != HAL_OK )
		{
			UART_WriteString("Eroare citire\n");
		}
	
}

uint8_t proximity7_set_als_integration_time( float integration_time )
{
    uint8_t write_buffer[ 1 ];
    
    if ( integration_time >= 0.0 && integration_time <= 698.88 )
    {
        write_buffer[ 0 ] = ( uint8_t )( ( 256.0 - ( integration_time / 2.73 ) ) );

        proximity7_generic_write( PROXIMITY7_ALS_ADC_TIME | PROXIMITY7_REPEATED_BYTE, write_buffer, 1 );
        
        return 0;
    }
    else
    {
        return 1;
    }
}

uint8_t proximity7_set_proximity_integration_time( float integration_time )
{
    uint8_t write_buffer[ 1 ];

    if ( integration_time >= 0.0 && integration_time <= 698.88 )
    {
        write_buffer[ 0 ] = ( uint8_t )( ( 256.0 - ( integration_time / 2.73 ) ) );

        proximity7_generic_write( PROXIMITY7_PROXIMITY_ADC_TIME | PROXIMITY7_REPEATED_BYTE, write_buffer, 1 );

        return 0;
    }
    else
    {
        return 1;
    }
}

uint8_t proximity7_set_wait_time( float wait_time )
{
    uint8_t write_buffer[ 1 ];
    uint8_t wlong_bit[ 1 ];
    
    proximity7_generic_read( PROXIMITY7_CONFIGURATION | PROXIMITY7_REPEATED_BYTE, wlong_bit, 1 );
    wlong_bit[ 0 ] >>= 1;
    wlong_bit[ 0 ] &= 0x01;
    
    if ( wlong_bit[ 0 ] == 0 )
    {
        if ( ( wait_time >= 0.0 ) && ( wait_time <= 698.88 ) )
        {
            write_buffer[ 0 ] = ( uint8_t )( ( 256.0 - ( wait_time / 2.73 ) ) );
            proximity7_generic_write( PROXIMITY7_WAIT_TIME | PROXIMITY7_REPEATED_BYTE, write_buffer, 1 );

            return 0;
        }
        else
        {
            return 1;
        }
    }
    else if ( wlong_bit[ 0 ] == 1 )
    {
        if ( ( wait_time >= 32.76 ) && ( wait_time <= 8386.56 ) )
        {
            write_buffer[ 0 ] = ( uint8_t )( ( 256.0 - ( wait_time / 32.76 ) ) );
            proximity7_generic_write( PROXIMITY7_WAIT_TIME | PROXIMITY7_REPEATED_BYTE, write_buffer, 1 );

            return 0;
        }
        else
        {
            return 1;
        }
    }
		return 1;
}

void proximity7_set_low_alsCh0_threshold( uint16_t low_als_ch0_threshold )
{
    uint8_t write_buffer[ 2 ];

    write_buffer[ 0 ] = ( uint8_t )( low_als_ch0_threshold );
    write_buffer[ 1 ] = ( uint8_t )( low_als_ch0_threshold >> 8 );
    proximity7_generic_write( PROXIMITY7_LOW_ALS_INT_PIN_THRESHOLD_LOW | PROXIMITY7_AUTO_INCREMENT, write_buffer, 2 );
}

void proximity7_set_high_alsCh0_threshold( uint16_t high_als_ch0_threshold )
{
    uint8_t write_buffer[ 2 ];
    
    write_buffer[ 0 ] = ( uint8_t )( high_als_ch0_threshold );
    write_buffer[ 1 ] = ( uint8_t )( high_als_ch0_threshold >> 8 );
    proximity7_generic_write( PROXIMITY7_HIGH_ALS_INT_PIN_THRESHOLD_LOW | PROXIMITY7_AUTO_INCREMENT, write_buffer, 2 );
}

void proximity7_set_low_proximity_threshold( uint16_t low_proximity_threshold )
{
    uint8_t write_buffer[ 2 ];

    write_buffer[ 0 ] = ( uint8_t )( low_proximity_threshold );
    write_buffer[ 1 ] = ( uint8_t )( low_proximity_threshold >> 8 );
    proximity7_generic_write( PROXIMITY7_LOW_PROXIMITY_INT_PIN_THRESHOLD_LOW | PROXIMITY7_AUTO_INCREMENT, write_buffer, 2 );
}

void proximity7_set_high_proximity_threshold( uint16_t high_proximity_threshold )
{
    uint8_t write_buffer[ 2 ];

    write_buffer[ 0 ] = ( uint8_t )( high_proximity_threshold );
    write_buffer[ 1 ] = ( uint8_t )( high_proximity_threshold >> 8 );
    proximity7_generic_write( PROXIMITY7_HIGH_PROXIMITY_INT_PIN_THRESHOLD_LOW | PROXIMITY7_AUTO_INCREMENT, write_buffer, 2 );
}

void proximity7_set_int_persistance( uint16_t proximity_int_persistence, uint16_t als_int_persistence )
{
    uint8_t write_buffer[ 1 ];

    write_buffer[ 0 ] = proximity_int_persistence | als_int_persistence;
    proximity7_generic_write( PROXIMITY7_INT_PIN_PERSISTANCE_FILTERS | PROXIMITY7_REPEATED_BYTE, write_buffer, 1 );
}

void proximity7_set_proximity_pulse_count( uint8_t proximity_pulse_count )
{
    uint8_t write_buffer[ 1 ];

    write_buffer[ 0 ] = proximity_pulse_count;
    proximity7_generic_write( PROXIMITY7_PROXIMITY_PULSE_COUNT | PROXIMITY7_REPEATED_BYTE, write_buffer, 1 );
}

uint16_t proximity7_get_als_data_ch0( )
{
    uint8_t register_buffer[ 2 ];
    uint16_t als_data_ch0;
    
    proximity7_generic_read( PROXIMITY7_CH0_ADC_DATA_LOW | PROXIMITY7_AUTO_INCREMENT, register_buffer, 2 );
    
    als_data_ch0 = register_buffer[ 1 ];
    als_data_ch0 <<= 8;
    als_data_ch0 |= register_buffer[ 0 ];
    
    return als_data_ch0;
}

uint16_t proximity7_get_als_data_ch1( )
{
    uint8_t register_buffer[ 2 ];
    uint16_t als_data_ch1;

    proximity7_generic_read( PROXIMITY7_CH1_ADC_DATA_LOW | PROXIMITY7_AUTO_INCREMENT, register_buffer, 2 );

    als_data_ch1 = register_buffer[ 1 ];
    als_data_ch1 <<= 8;
    als_data_ch1 |= register_buffer[ 0 ];

    return als_data_ch1;
}

uint16_t proximity7_get_proximity_data( )
{
    uint8_t register_buffer[ 2 ];
    uint16_t proximity_data;

    proximity7_generic_read( PROXIMITY7_PROXIMITY_ADC_DATA_LOW | PROXIMITY7_AUTO_INCREMENT, register_buffer, 2 );

    proximity_data = register_buffer[ 1 ];
    proximity_data <<= 8;
    proximity_data |= register_buffer[ 0 ];

    return proximity_data;
}

uint8_t proximity7_set_proximity_offset(  uint8_t proximity_offset_sign,  uint8_t proximity_offset_magnitude )
{
    uint8_t write_buffer[ 1 ];

    if ( proximity_offset_magnitude < 128 )
    {
        write_buffer[ 0 ] = proximity_offset_sign | proximity_offset_magnitude;

        proximity7_generic_write(PROXIMITY7_PROXIMITY_OFFSET | PROXIMITY7_REPEATED_BYTE, write_buffer, 1 );
        
        return 0;
    }
    else
    {
        return 1;
    }
}

float proximity7_get_lux_level( )
{
    uint8_t register_buffer[ 4 ];
    uint16_t als_data_ch0;
    uint16_t als_data_ch1;

    float als_integration_time;
    float als_gain;
    float ir_adjusted_count1;
    float ir_adjusted_count2;
    float lux_per_count;
    float lux_level;

    proximity7_generic_read( PROXIMITY7_ALS_ADC_TIME | PROXIMITY7_REPEATED_BYTE, register_buffer, 1 );

    als_integration_time = ( 2.73 * ( 256 - register_buffer[ 0 ] ) );

    proximity7_generic_read( PROXIMITY7_GAIN_CONTROL | PROXIMITY7_REPEATED_BYTE, register_buffer, 1 );

    register_buffer[ 0 ] &= 0x03;

    if ( register_buffer[ 0 ] == 0 )
    {
        als_gain = 1.0;
    }
    else if ( register_buffer[ 0 ] == 1 )
    {
        als_gain = 8.0;
    }
    else if ( register_buffer[ 0 ] == 2 )
    {
        als_gain = 16.0;
    }
    else if ( register_buffer[ 0 ] == 3 )
    {
        als_gain = 120.0;
    }

    proximity7_generic_read( PROXIMITY7_CH0_ADC_DATA_LOW | PROXIMITY7_AUTO_INCREMENT, register_buffer, 4 );

    als_data_ch0 = register_buffer[ 1 ];
    als_data_ch0 <<= 8;
    als_data_ch0 |= register_buffer[ 0 ];
    
    als_data_ch1 = register_buffer[ 3 ];
    als_data_ch1 <<= 8;
    als_data_ch1 |= register_buffer[ 2 ];

    ir_adjusted_count1 = ( ( float )( als_data_ch0 ) - ( g_const_data.const_b * als_data_ch1 ) );
    ir_adjusted_count2 = ( (  g_const_data.const_c * als_data_ch0 ) - (  g_const_data.const_d * als_data_ch1 ) );
    lux_per_count      = (   g_const_data.glass_attenuation  *  g_const_data.device_factor / ( als_integration_time * als_gain ) );
    
    if ( ir_adjusted_count1 > ir_adjusted_count2 )
    {
        lux_level = ( ir_adjusted_count1 * lux_per_count );
    }
    else
    {
        lux_level = ( ir_adjusted_count2 * lux_per_count );
    }

    return lux_level;
}

void proximity7_set_constants( proximity7_const_t *set_const_data )
{
    g_const_data.glass_attenuation = set_const_data->glass_attenuation;
    g_const_data.const_b = set_const_data->const_b;
    g_const_data.const_c = set_const_data->const_c;
    g_const_data.const_d = set_const_data->const_d;
    g_const_data.device_factor = set_const_data->device_factor;
}

// ------------------------------------------------------------------------- END


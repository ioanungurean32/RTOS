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

#include "c7seg.h"
#include "stm32f4xx_hal.h"

#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif
#ifdef RTE_CMSIS_RTOS2                  // when RTE component CMSIS RTOS2 is used
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#endif

// ------------------------------------------------------------- PRIVATE MACROS 

#define C7SEG_DUMMY 0

#define C7SEG_EMPTY_DISPLAY 0

// ------------------------------------------------------------------ CONSTANTS

SPI_HandleTypeDef hspi3;

static const uint8_t C7SEG_CHAR_TABLE[ 51 ]=
{
    0x80, // '-'
    0x01, // '.'   Sevensegment bit order
    0x00, // '/'   (g)(f)(e)(d)(c)(a)(b)(dp)
    0x7E, // '0'
    0x0A, // '1'    _a_
    0xB6, // '2'  f|   |b
    0x9E, // '3'   |_g_|
    0xCA, // '4'  e|   |c
    0xDC, // '5'   |_d_|.dp
    0xFC, // '6'
    0x0E, // '7'
    0xFE, // '8'
    0xDE, // '9'
    0x00, // ':'
    0x00, // ';'
    0x00, // '<'
    0x00, // '='
    0x00, // '>'
    0x00, // '?'
    0x00, // '@'
    0xEE, // 'A'
    0xF8, // 'B'
    0x74, // 'C'
    0xBA, // 'D'
    0xF4, // 'E'
    0xE4, // 'F'
    0x7C, // 'G'
    0xEA, // 'H'
    0x0A, // 'I'
    0x3A, // 'J'
    0xE0, // 'K'
    0x70, // 'L'
    0x2C, // 'M'
    0xA8, // 'N'
    0x7E, // 'O'
    0xE6, // 'P'
    0xCE, // 'Q'
    0x64, // 'R'
    0xDC, // 'S'
    0xF0, // 'T'
    0x7A, // 'U'
    0x7B, // 'V'
    0xFB, // 'W'
    0xEA, // 'X'
    0xDA, // 'Y'
    0xB6, // 'Z'
    0x00, // '['
    0x00, // '/'
    0x00, // ']'
    0x00, // '^'
    0x10, // '_'
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

// Reset delay
static void dev_reset_delay ( void );

// Function that defines a digit from C7SEG_CHAR_TABLE
static uint8_t dev_get_digit (  uint8_t digit );

// Function that defines a character from C7SEG_CHAR_TABLE
static uint8_t dev_get_char ( char character );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

C7SEG_RETVAL c7seg_init ( )
{
		GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_SPI3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI3 GPIO Configuration
    PB3     ------> SPI3_SCK
    PB4     ------> SPI3_MISO
    PB5     ------> SPI3_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		
		hspi3.Instance = SPI3;
		hspi3.Init.Mode = SPI_MODE_MASTER;
		hspi3.Init.Direction = SPI_DIRECTION_2LINES;
		hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
		hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
		hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
		hspi3.Init.NSS = SPI_NSS_SOFT;
		hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
		hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
		hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
		hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
		hspi3.Init.CRCPolynomial = 10;
		if (HAL_SPI_Init(&hspi3) != HAL_OK)
		{
			;//Error_Handler();
		}
		
		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		
		/*Configure GPIO pin : PD6  PD7 */
		GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		
		/*Configure GPIO pin : PC8   */
		GPIO_InitStruct.Pin = GPIO_PIN_8;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);	
		
    return C7SEG_OK;
}

void c7seg_default_cfg ( )
{
    // Sets MR pin high
    
    c7seg_reset ( );
    
    // Turns display on
    
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);   
}


void c7seg_write_data ( uint8_t write_left, uint8_t write_right )
{
    uint8_t tx_buf[ 2 ];
    tx_buf[ 0 ] = write_right;
    tx_buf[ 1 ] = write_left;

	
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);		
		HAL_SPI_Transmit(&hspi3, &tx_buf[ 0 ], 2, 10 );	
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
}

void c7seg_reset ( )
{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);	
    dev_reset_delay( );	
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET);
}

void c7seg_display_mode ( uint8_t display_mode )
{
    if ( display_mode == C7SEG_DISPLAY_OFF )
    {       
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);				
    }
    
    if ( display_mode == C7SEG_DISPLAY_ON )
    {        
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
    }
}

void c7seg_write_data_number ( uint8_t left_number, uint8_t right_number )
{
    c7seg_write_data( dev_get_digit( left_number ), dev_get_digit( right_number ) );
}

void c7seg_write_data_character ( char left_char, char right_char )
{
    c7seg_write_data( dev_get_char( left_char ) , dev_get_char( right_char ) );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_reset_delay ( void )
{   
		osDelay (10U);     
}

static uint8_t dev_get_digit (  uint8_t digit )
{
    if ( ( digit >= 0 ) && ( digit <= 9 ) )
    {
        return C7SEG_CHAR_TABLE[ digit + 3 ];
    }
    else
    {
        return C7SEG_EMPTY_DISPLAY;
    }
}

static uint8_t dev_get_char ( char character )
{
    if ( ( character >= '-' ) && ( character <= '_' ) )
    {
        return C7SEG_CHAR_TABLE[ character - '-' ];
    }
    else
    {
        return C7SEG_EMPTY_DISPLAY;
    }
}

// ------------------------------------------------------------------------- END


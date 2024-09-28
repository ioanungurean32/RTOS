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
 * @file oledb.c
 * @brief OLED B Click Driver.
 */

#include "oledb.h"
#include <string.h>
#include "stm32f4xx_hal.h"

#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif
#ifdef RTE_CMSIS_RTOS2                  // when RTE component CMSIS RTOS2 is used
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#endif
// ------------------------------------------------------------- PRIVATE MACROS 

#define OLEDB_DUMMY 0

SPI_HandleTypeDef hspi2;


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS
// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS
static void oledb_spi_master_write( oledb_data_t *data_in, uint8_t data_len ) 
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);	
	HAL_SPI_Transmit(&hspi2, &data_in[ 0 ], data_len, 10 );
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);	
}


err_t oledb_init() 
{
	
	 GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
	
	/*Configure GPIO pins : PE10 */
	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	 
	/*Configure GPIO pin : PA1 */
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	  /*Configure GPIO pin : PB12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	
	
	/* Peripheral clock enable */
	__HAL_RCC_SPI2_CLK_ENABLE();

	/**SPI2 GPIO Configuration		
	PB13     ------> SPI2_SCK
	PB15     ------> SPI2_MOSI
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;

	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi2) != HAL_OK)
	{
		;//Error_Handler();
	}
	
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
	osDelay (100U);  
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);
		 
	
	oledb_default_cfg();
	
	return OLEDB_OK;
}

void oledb_send_cmd( oledb_data_t tx_cmd )
{
		uint8_t tx_buffer[ 1 ];	
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
		tx_buffer[ 0 ] = tx_cmd;		

		oledb_spi_master_write ( tx_buffer, 1 );
}

void oledb_send_data( oledb_data_t *tx_data, uint8_t data_len )
{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);	
	  oledb_spi_master_write( tx_data, data_len );
}

void oledb_default_cfg() 
{
		oledb_send_cmd( OLEDB_DISPLAYOFF );            //  0xAE Set OLED Display Off
		oledb_send_cmd( OLEDB_SETDISPLAYCLOCKDIV );    //  0xD5 Set Display Clock Divide Ratio/Oscillator Frequency
		oledb_send_cmd( 0x80 );
		oledb_send_cmd( OLEDB_SETMULTIPLEX );          //  0xA8 Set Multiplex Ratio
		oledb_send_cmd( OLEDB_DISPLAY_HEIGHT - 1 );
		oledb_send_cmd( OLEDB_SETDISPLAYOFFSET );      //  0xD3 Set Display Offset
		oledb_send_cmd( 0x00 );
		oledb_send_cmd( OLEDB_SETSTARTLINE );          //  0x40 Set Display Start Line
		oledb_send_cmd( OLEDB_CHARGEPUMP );            //  0x8D Set Charge Pump
		oledb_send_cmd( 0x14 );                        //  0x14 Enable Charge Pump
		oledb_send_cmd( OLEDB_COMSCANDEC );            //  0xC8 Set COM Output Scan Direction
		oledb_send_cmd( OLEDB_SETCOMPINS );            //  0xDA Set COM Pins Hardware Configuration
		oledb_send_cmd( 0x12 );
		oledb_send_cmd( OLEDB_SETCONTRAST );           //  0x81 Set Contrast Control
		oledb_send_cmd( 0xAF );
		oledb_send_cmd( OLEDB_SETPRECHARGE );          //  0xD9 Set Pre-Charge Period
		oledb_send_cmd( 0x25 );
		oledb_send_cmd( OLEDB_SETVCOMDETECT );         //  0xDB Set VCOMH Deselect Level
		oledb_send_cmd( 0x20 );
		oledb_send_cmd( OLEDB_DISPLAYALLON_RESUME );   //  0xA4 Set Entire Display On/Off
		oledb_send_cmd( OLEDB_NORMALDISPLAY );         //  0xA6 Set Normal/Inverse Display
		oledb_send_cmd( OLEDB_DISPLAYON );             //  0xAF Set OLED Display On
}

void oledb_set_page(oledb_data_t page_addr ) 
{
		oledb_send_cmd( OLEDB_PAGEADDR );
		oledb_send_cmd( page_addr );
		oledb_send_cmd( OLEDB_DISPLAY_ROWS - 1 );
}

void oledb_set_column(oledb_data_t col_addr ) 
{
		oledb_send_cmd( OLEDB_COLUMNADDR );
		oledb_send_cmd( col_addr );
		oledb_send_cmd( OLEDB_SSD1306_WIDTH - 1 );
}

void oledb_display_picture( oledb_resources_t *pic ) 
{
		uint8_t data_buf[ 8 ] = { 0 };
		uint8_t page_num = 0;
		uint8_t seg_num = 0;
		oledb_send_cmd( OLEDB_DISPLAYOFF );
		for ( page_num = 0; page_num < OLEDB_DISPLAY_ROWS; page_num++ ) 
		{
				oledb_set_column ( 0 );
				oledb_set_page ( page_num );
				for ( seg_num = 0; seg_num < OLEDB_DISPLAY_WIDTH; seg_num += 8 )
				{
						memcpy ( data_buf, &pic[ page_num * OLEDB_DISPLAY_WIDTH + seg_num ], 8 );
						oledb_send_data( data_buf, 8 );
				}
		}
		oledb_send_cmd( OLEDB_DISPLAYON );
}

void oledb_clear_display( )
{
		uint8_t data_buf[ 8 ] = { 0 };
		uint8_t page_num = 0;
		uint8_t seg_num = 0;
		oledb_send_cmd( OLEDB_DISPLAYOFF );
		for ( page_num = 0; page_num < OLEDB_DISPLAY_ROWS; page_num++ ) 
		{
				oledb_set_column ( 0 );
				oledb_set_page ( page_num );
				for ( seg_num = 0; seg_num < OLEDB_SSD1306_WIDTH; seg_num += 8 )
				{
						oledb_send_data( data_buf, 8 );
				}
		}
		oledb_send_cmd( OLEDB_DISPLAYON );
}

void oledb_write_char( uint8_t row, uint8_t position, uint8_t data_in )
{
		uint8_t font = OLEDB_FONT_6X8;
	
		if ( ( font > OLEDB_FONT_6X8 ) || ( row > ( OLEDB_DISPLAY_ROWS - 1 ) ) )
		{
				return;
		}
		uint8_t char_buf[ 6 ] = { 0 };
		uint8_t char_width = 0;
		if ( ( data_in < 32 ) || ( data_in > 127 ) ) 
		{
				data_in = ' ';
		}
		if ( OLEDB_FONT_5X7 == font )
		{
				char_width = 5;
				memcpy ( char_buf, &oledb_font_5x7[ ( data_in - 32 ) * char_width ], char_width );
		}
		else if ( OLEDB_FONT_6X8 == font )
		{
				char_width = 6;
				memcpy ( char_buf, &oledb_font_6x8[ ( data_in - 32 ) * char_width ], char_width );
		}
		if ( position > ( ( ( OLEDB_SSD1306_WIDTH + 1 ) / char_width ) - 1 ) )
		{
				return;
		}
		
		oledb_set_column ( OLEDB_DISPLAY_WIDTH - char_width - position * char_width );
		oledb_set_page ( row );
		oledb_send_data( char_buf, char_width );
}

void oledb_write_string( uint8_t row, uint8_t position, uint8_t *data_in )
{
		uint8_t font = OLEDB_FONT_6X8;
	  uint8_t data_len = strlen ( (const char *)data_in );
		uint8_t data_cnt = 0;
		
	  for ( data_cnt = 0; data_cnt < data_len; data_cnt++ )
		{
				oledb_write_char( row, position + data_len - 1 - data_cnt, data_in[ data_len - 1 - data_cnt ] );
		}
}

void oledb_set_contrast( oledb_data_t value ) 
{
		oledb_send_cmd( OLEDB_SETCONTRAST );    //  0x81 Set Contrast Control
		oledb_send_cmd( value );                //  Contrast Step 0 to 255
}

void oledb_scroll_right( oledb_data_t start_page_addr, oledb_data_t end_page_addr ) 
{
		oledb_send_cmd( OLEDB_RIGHT_HORIZONTAL_SCROLL );    //  0x26 Right Horizontal scroll
		oledb_send_cmd( 0x00 );                             //  Dummy byte
		oledb_send_cmd( start_page_addr );                  //  Define start page address
		oledb_send_cmd( 0x00 );                             //  Set time interval between each scroll
		oledb_send_cmd( end_page_addr );                    //  Define end page address
		oledb_send_cmd( 0x00 );                             //  Dummy byte
		oledb_send_cmd( 0xFF );                             //  Dummy byte
		oledb_send_cmd( OLEDB_ACTIVATE_SCROLL );            //  0x2F Activate scroll
}

void oledb_scroll_left( oledb_data_t start_page_addr, oledb_data_t end_page_addr ) 
{
		oledb_send_cmd( OLEDB_LEFT_HORIZONTAL_SCROLL );   //  0x27 Left Horizontal scroll
		oledb_send_cmd( 0x00 );                           //  Dummy byte
		oledb_send_cmd( start_page_addr );                //  Define start page address
		oledb_send_cmd( 0x00 );                           //  Set time interval between each scroll
		oledb_send_cmd( end_page_addr );                  //  Define end page address
		oledb_send_cmd( 0x00 );                           //  Dummy byte
		oledb_send_cmd( 0xFF );                           //  Dummy byte
		oledb_send_cmd( OLEDB_ACTIVATE_SCROLL );          //  0x2F Activate scroll
}

void oledb_scroll_diag_right( oledb_data_t start_page_addr, oledb_data_t end_page_addr ) 
{
		oledb_send_cmd( OLEDB_SET_VERTICAL_SCROLL_AREA );               //  0xA3 Set Vertical Scroll Area
		oledb_send_cmd( 0x00 );                                         //  Set No. of rows in top fixed area
		oledb_send_cmd( OLEDB_DISPLAY_HEIGHT );                         //  Set No. of rows in scroll area
		oledb_send_cmd( OLEDB_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL );   //  0x29 Vertical and Right Horizontal Scroll
		oledb_send_cmd( 0x00 );                                         //  Dummy byte
		oledb_send_cmd( start_page_addr );                              //  Define start page address
		oledb_send_cmd( 0x00 );                                         //  Set time interval between each scroll
		oledb_send_cmd( end_page_addr );                                //  Define end page address
		oledb_send_cmd( 0x01 );                                         //  Vertical scrolling offset
		oledb_send_cmd( OLEDB_ACTIVATE_SCROLL );                        //  0x2F Activate scroll
}

void oledb_scroll_diag_left( oledb_data_t start_page_addr, oledb_data_t end_page_addr ) 
{
		oledb_send_cmd( OLEDB_SET_VERTICAL_SCROLL_AREA );               //  0xA3 Set Vertical Scroll Area
		oledb_send_cmd( 0x00 );                                         //  Set No. of rows in top fixed area
		oledb_send_cmd( OLEDB_DISPLAY_HEIGHT );                         //  Set No. of rows in scroll area
		oledb_send_cmd( OLEDB_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL );    //  0x2A Vertical and Left Horizontal Scroll
		oledb_send_cmd( 0x00 );                                         //  Dummy byte
		oledb_send_cmd( start_page_addr );                              //  Define start page address
		oledb_send_cmd( 0x00 );                                         //  Set time interval between each scroll
		oledb_send_cmd( end_page_addr );                                //  Define end page address
		oledb_send_cmd( 0x01 );                                         //  Vertical scrolling offset
		oledb_send_cmd( OLEDB_ACTIVATE_SCROLL );                        //  0x2F Activate scroll
}

void oledb_stop_scroll( ) 
{
		oledb_send_cmd( 0x2E);   //  0x2E Deactivate scroll
}

// ------------------------------------------------------------------------ END

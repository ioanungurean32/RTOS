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
 * @file oledb.h
 * @brief This file contains API for OLED B Click Driver.
 */

#ifndef _OLEDB_H_
#define _OLEDB_H_

//#include "drv_digital_out.h"
//#include "drv_i2c_master.h"
//#include "drv_spi_master.h"
#include "oledb_resources.h"

// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup settings Display Settings
 * \{
 */
#define OLEDB_SSD1306_WIDTH                         128
#define OLEDB_DISPLAY_WIDTH                         96
#define OLEDB_DISPLAY_HEIGHT                        39
#define OLEDB_DISPLAY_ROWS                          5
#define OLEDB_FONT_5X7                              0
#define OLEDB_FONT_6X8                              1
#define OLEDB_DISPLAYOFF                            0xAE
#define OLEDB_SETDISPLAYCLOCKDIV                    0xD5
#define OLEDB_SETMULTIPLEX                          0xA8
#define OLEDB_SETDISPLAYOFFSET                      0xD3
#define OLEDB_SETSTARTLINE                          0x40
#define OLEDB_CHARGEPUMP                            0x8D
#define OLEDB_SETSEGMENTREMAP                       0xA1
#define OLEDB_SEGREMAP                              0xA0
#define OLEDB_COMSCANDEC                            0xC8
#define OLEDB_SETCOMPINS                            0xDA
#define OLEDB_SETCONTRAST                           0x81
#define OLEDB_SETPRECHARGE                          0xD9
#define OLEDB_SETVCOMDETECT                         0xDB
#define OLEDB_DISPLAYALLON_RESUME                   0xA4
#define OLEDB_NORMALDISPLAY                         0xA6
#define OLEDB_DISPLAYON                             0xAF
#define OLEDB_DISPLAYALLON                          0xA5
#define OLEDB_INVERTDISPLAY                         0xA7
#define OLEDB_SETLOWCOLUMN                          0x00
#define OLEDB_SETHIGHCOLUMN                         0x10
#define OLEDB_MEMORYMODE                            0x20
#define OLEDB_COLUMNADDR                            0x21
#define OLEDB_PAGEADDR                              0x22
#define OLEDB_COMSCANINC                            0xC0
#define OLEDB_EXTERNALVCC                           0x01
#define OLEDB_SWITCHCAPVCC                          0x02
#define OLEDB_ACTIVATE_SCROLL                       0x2F
#define OLEDB_DEACTIVATE_SCROLL                     0x2E
#define OLEDB_SET_VERTICAL_SCROLL_AREA              0xA3
#define OLEDB_RIGHT_HORIZONTAL_SCROLL               0x26
#define OLEDB_LEFT_HORIZONTAL_SCROLL                0x27
#define OLEDB_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL  0x29
#define OLEDB_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL   0x2A
/** \} */

/**
 * \defgroup data_mode Data Mode
 * \{
 */
#define OLEDB_COMMAND                               0x3C
#define OLEDB_DATA                                  0x3D
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define OLEDB_MASTER_I2C                            0
#define OLEDB_MASTER_SPI                            1
/** \} */

/**
 * \defgroup error Error
 * \{
 */

/**
 * \defgroup error_type Error Type
 * \{
 */
#define err_t  uint8_t
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define OLEDB_OK                                    0x00
#define OLEDB_INIT_ERROR                            0xFF
#define OLEDB_INVALID_DATA_MODE                     0xFE
#define OLEDB_INVALID_DRIVER_SELECTOR               0xFD
/** \} */

/** \} */ //  End error group

/** \} */ //  End macros group
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup types Types
 * \{
 */

typedef uint8_t  oledb_drv_select_t;

typedef uint8_t  oledb_data_t;

typedef const uint8_t  oledb_resources_t;


/**
 * @brief Communication type.
 */
typedef uint8_t  oledb_select_t;


/** \} */ //  End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS
/**
 * \defgroup public_function Public Function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Click Initialization function.
 *
 * @param[in] ctx  Click object.
 * @param[in] cfg  Click configuration structure.
 *
 * @returns 0x00 - Ok,
 *          0xFF - Init error,
 *          0xFD - Invalid driver selector.
 *
 * @details This function initializes all necessary peripherals and pins.
 */
err_t oledb_init();

/**
 * @brief Send cmd function.
 * @details This function sends commands to OLED B click.
 * @param[in] tx_cmd  Command to be sent.
 * @returns Nothing.
 */
void oledb_send_cmd( oledb_data_t tx_cmd );

/**
 * @brief Send data function.
 * @details This function sends data to OLED B click.
 * @param[in] tx_data  Data to be sent.
 * @param[in] data_len  Number of data bytes.
 * @returns Nothing.
 */
void oledb_send_data( oledb_data_t *tx_data, uint8_t data_len );

/**
 * @brief Click Default Configuration function.
 * @details This function configures OLED B click to default state.
 * 
 * @returns Nothing.
 */
void oledb_default_cfg();

/**
 * @brief Page Setting function.
 * @details This function sets page address for page addressing mode.
 * @param[in] page_addr  Page address.
 * 
 * @returns Nothing.
 */
void oledb_set_page( oledb_data_t page_addr );

/**
 * @brief Column Setting function.
 * @details This function sets column address for page addressing mode.
 * @param[in] col_addr  Column address.
 *
 * @returns Nothing.
 */
void oledb_set_column( oledb_data_t col_addr );

/**
 * @brief Display Picture function.
 * @details This function allows user to display picture for on the screen.
 * @param[in] pic  Resource code.
 *
 * @returns Nothing.
 */ 
void oledb_display_picture( oledb_resources_t *pic );

/**
 * @brief Clear Display function.
 * @details This function clears SSD1306 controller display.
 * 
 * @returns Nothing.
 */ 
void oledb_clear_display();

/**
 * @brief Write Char function.
 * @details This function writes a single character on the selected position in a 5x7 or 6x8 font size.
 * @param[in] row       Display row (0-4).
 * @param[in] position  Char position in a row (0-((128/char_width)-1)).
 * @param[in] data_in   Character to write (ASCII 32-127).
 * 
 * @returns Nothing.
 */ 
void oledb_write_char( uint8_t row, uint8_t position, uint8_t data_in );

/**
 * @brief Write String function.
 * @details This function writes a text string from the selected position in a 5x7 or 6x8 font size.
 * @param[in] row       Display row (0-4).
 * @param[in] position  Char position in a row (0-((128/char_width)-1)).
 * @param[in] data_in   Text string to write.
 * 
 * @returns Nothing.
 */ 
void oledb_write_string( uint8_t row, uint8_t position, uint8_t *data_in );

/**
 * @brief Contrast Setting function.
 * @details This function sets the display contrast level (0 to 255).
 * @param[in] value  Contrast value to be set.
 *
 * @returns Nothing.
 */
void oledb_set_contrast( oledb_data_t value );

/**
 * @brief Scroll Right function.
 * @details This function scrolls the display to the right.
 * @param[in] start_page_addr  Start page address.
 * @param[in] end_page_addr  End page address.
 * 
 * @returns Nothing.
 */
void oledb_scroll_right( oledb_data_t start_page_addr, oledb_data_t end_page_addr );

/**
 * @brief Scroll Left function.
 * @details This function scrolls the display to the left.
 * @param[in] start_page_addr  Start page address.
 * @param[in] end_page_addr  End page address.
 * 
 * @returns Nothing.
 */
void oledb_scroll_left( oledb_data_t start_page_addr, oledb_data_t end_page_addr );

/**
 * @brief Scroll Diagonally Right function.
 * @details This function scrolls the display diagonally to the right.
 * @param[in] start_page_addr  Start page address.
 * @param[in] end_page_addr  End page address.
 *
 * @returns Nothing.
 */
void oledb_scroll_diag_right( oledb_data_t start_page_addr, oledb_data_t end_page_addr );

/**
 * @brief Scroll Diagonally Left function.
 * @details This function scrolls the display diagonally to the left.
 * @param[in] start_page_addr  Start page address.
 * @param[in] end_page_addr  End page address.
 * 
 * @returns Nothing.
 */
void oledb_scroll_diag_left(oledb_data_t start_page_addr, oledb_data_t end_page_addr );

/**
 * @brief Stop Scrolling function.
 * @details This function allows user to stop the scrolling motion.
 * @param[in] ctx  Click object.
 *
 * @returns Nothing.
 */
void oledb_stop_scroll();

#ifdef __cplusplus
}
#endif
#endif // OLEDB_H

/*! @} */ // oledb

// ------------------------------------------------------------------------ END

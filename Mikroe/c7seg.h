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
 * \brief This file contains API for 7seg Click driver.
 *
 * \addtogroup c7seg 7seg Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C7SEG_H
#define C7SEG_H

#include "stdint.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C7SEG_RETVAL  uint8_t

#define C7SEG_OK            0x00
#define C7SEG_INIT_ERROR    0xFF
/** \} */

/**
 * \defgroup display mode Display Mode
 * \{
 */
#define C7SEG_DISPLAY_OFF   0
#define C7SEG_DISPLAY_ON    1
/** \} */

/** \} */ // End group macro 

// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */


/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Initialization function.

 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C7SEG_RETVAL c7seg_init ( );

/**
 * @brief Click Default Configuration function.
 *
 *
 * @description This function executes default configuration for c7seg click.
 * @note
 *  Click default configuration:
 * -------------------------------------------------
 * <pre>
 *    Sets MR pin high
 * </pre>
 * 
 * <pre>
 *    Display on
 * </pre>
 */
void c7seg_default_cfg ( );

/**
 * @brief Generic write data function.
 *
 * @param write_left    Left data to write.
 * @param write_right   Right data to write.
 * 
 * @description This function write left and right data on 7seg display.
 */
void c7seg_write_data ( uint8_t write_left, uint8_t write_right );

/**
 * @brief Click Reset function.
 *
 *
 * @description This function executes device reset for 7seg click.
 */
void c7seg_reset ( );

/**
 * @brief Display mode function.
 *
 * @param display_mode    State of display.
 *
 * @description This function sets display state for 7seg click.
 */
void c7seg_display_mode ( uint8_t display_mode );

/**
 * @breif Write number on 7seg diaplay.
 *
 * @param left_number       Left data to write.
 * @param right_number      Right data to write.
 *
 * @description This function writes left and right number on 7seg display.
 */
void c7seg_write_data_number ( uint8_t left_number, uint8_t right_number );

/**
 * @breif Write character on 7seg diaplay.
 *
 * @param left_char         Left character to write.
 * @param right_char        Right character to write.
 *
 * @description This function writes left and right character on 7seg display.
 */
void c7seg_write_data_character ( char left_char, char right_char );

#ifdef __cplusplus
}
#endif
#endif  // _C7SEG_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */

// ------------------------------------------------------------------------- END

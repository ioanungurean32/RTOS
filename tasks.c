/*------------------------------------------------------------------------------
 * Copyright (c) 2018 Arm Limited (or its affiliates). All
 * rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   1.Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   2.Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   3.Neither the name of Arm nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *------------------------------------------------------------------------------
 * Name:    
 * Purpose: 
 *----------------------------------------------------------------------------*/

#include "cmsis_os2.h"                  // ARM::CMSIS:RTOS:Keil RTX5
#include "Board_LED.h"                  // Board Support:LED
#include "Board_Buttons.h"              // Board Support:Buttons
#include "Mikroe\oledb.h"
#include "Mikroe\proximity7.h"
#include "Mikroe\temphum15.h"
#include "Mikroe\c7seg.h"
#include <string.h>
#include <stdio.h>
#include "main.h"

static osThreadId_t tid_Task1;         // Task id
static osThreadId_t tid_Task2;         // Task id
static osThreadId_t tid_Task3;         // Task id
static osThreadId_t tid_Task4;         // Task id
static osThreadId_t tid_Task5;         // Task id
static osThreadId_t tid_Task6;         // Task id
static osThreadId_t tid_Task7;         // Task id
static osThreadId_t tid_Task8;         // Task id

char BufferUART_Task6[128];
char BufferUART_Task7[128];

/*------------------------------------------------------------------------------
  Task 1 
 *----------------------------------------------------------------------------*/
void Task1 (void *argument) 
{
  
  while (1)
	{
	
      LED_On (0U);   															// Switch on
      osDelay (300U);                             // Delay 300 ms
      LED_Off (0U);              									// Switch off
      osDelay (300U);                             // Delay 300 ms
  }

}   
/*------------------------------------------------------------------------------
  Task 2 
 *----------------------------------------------------------------------------*/
void Task2 (void *argument) 
{
  
  while (1)
	{
	
      LED_On (1U);   															// Switch on
      osDelay (400U);                             // Delay 400 ms
      LED_Off (1U);              									// Switch off
      osDelay (400U);                             // Delay 400 ms
  }

}   
/*------------------------------------------------------------------------------
  Task 3 
 *----------------------------------------------------------------------------*/
void Task3 (void *argument) 
{
  
  while (1)
	{
	
      LED_On (2U);   															// Switch on
      osDelay (500U);                             // Delay 500 ms
      LED_Off (2U);              									// Switch off
      osDelay (500U);                             // Delay 500 ms
  }

}   
/*------------------------------------------------------------------------------
  Task 4 
 *----------------------------------------------------------------------------*/
void Task4 (void *argument) 
{
  
  while (1)
	{
	
      LED_On (3U);   															// Switch on
      osDelay (600U);                             // Delay 600 ms
      LED_Off (3U);              									// Switch off
      osDelay (600U);                             // Delay 600 ms
  }

}   
/*------------------------------------------------------------------------------
  Task 5  - afisate pe OLED
 *----------------------------------------------------------------------------*/
void Task5 (void *argument) 
{
	uint32_t  cnt = 0;
	
	char Buffer_afis[ 16 + 1];  // pe un rand se pot afisa maxim 16 charactere + 1 terminatorul de sir
	
  oledb_write_string( 0, 0, (uint8_t *)"SISTEME DE TIMP " );
  oledb_write_string( 1, 0, (uint8_t *)"      REAL      " );
  oledb_write_string( 2, 0, (uint8_t *)"   USV - 2024   " );
  oledb_write_string( 3, 0, (uint8_t *)"                " );
  oledb_write_string( 4, 0, (uint8_t *)"                " );

  while (1)
	{
			cnt ++ ;
		
			if(cnt % 2 == 0)
				oledb_send_cmd(  OLEDB_INVERTDISPLAY );
			else
				oledb_send_cmd(  OLEDB_NORMALDISPLAY );
		
			oledb_write_string( 4, 0, (uint8_t *)"TASK 5  ------- " );
      osDelay (500U);                             // Delay 500 ms
			oledb_write_string( 4, 0, (uint8_t *)"TASK 5  /////// " );
			osDelay (500U);                             // Delay 500 ms
		
			sprintf(Buffer_afis, " %d secunde", cnt);
			oledb_write_string( 3, 0, (uint8_t *)Buffer_afis );
		  
  }

}   

/*------------------------------------------------------------------------------
  Task 6  - proximity 7 click
 *----------------------------------------------------------------------------*/
void Task6 (void *argument) 
{
	uint8_t write_buffer[ 2 ];
  uint8_t read_buffer[ 1 ] ;
  float lux_level;
  uint16_t proximity;
  uint8_t als_valid;
  uint8_t proximity_valid;
  
  while (1)
	{
	
		proximity7_generic_read( PROXIMITY7_STATUS | PROXIMITY7_REPEATED_BYTE, &read_buffer[ 0 ], 1 );
    
    als_valid = read_buffer[ 0 ] & PROXIMITY7_ALS_VALID_MASK;
    proximity_valid = read_buffer[ 0 ] & PROXIMITY7_PROXIMITY_VALID_MASK;
    
    if ( ( als_valid != 0 ) && ( proximity_valid != 0 ) )
    {      

        lux_level = proximity7_get_lux_level( );
        sprintf( BufferUART_Task6, "< < <TASK 6> > > Lux level   : %f lx\r\n", lux_level );
				UART_WriteString(BufferUART_Task6);			
    
        proximity = proximity7_get_proximity_data( );
        sprintf( BufferUART_Task6, "< < <TASK 6> > > Proximity   : %d\r\n\n\n", proximity );
				UART_WriteString(BufferUART_Task6);

        write_buffer[ 0 ] = PROXIMITY7_SPECIAL_FUNCTION | PROXIMITY7_PROXIMITY_AND_ALS_INT_PIN_CLEAR;
        proximity7_generic_write( PROXIMITY7_SPECIAL_FUNCTION | PROXIMITY7_PROXIMITY_AND_ALS_INT_PIN_CLEAR, &write_buffer[ 0 ], 1 );
		}
      osDelay (1000U);                             // Delay 1000 ms
  }

}   


/*------------------------------------------------------------------------------
  Task 7 - Temp&Hum 15 click 
 *----------------------------------------------------------------------------*/
void Task7 (void *argument) 
{
	int8_t      status_data;
	float temperature;
  float humidity;

	
  osDelay( 100 );
  temphum15_default_cfg();
	
  while (1)
	{
		status_data = temphum15_get_temp_and_hum( TEMPHUM15_MODE_HIGH_PRECISION, &temperature, &humidity );
    if ( status_data == TEMPHUM15_SUCCESS ) 
		{       
				sprintf(BufferUART_Task7, "< < <TASK 7> > > Temperature : %.2f C\r\n", temperature);
        UART_WriteString( BufferUART_Task7 );
			
				sprintf(BufferUART_Task7, "< < <TASK 7> > > Humidity: %.2f %% RH\r\n\n\n", humidity );
        UART_WriteString( BufferUART_Task7);
    } else 
		{
        UART_WriteString( "< < <TASK 7> > > No data from Temp&Hum\r\n" );
    }
    osDelay( 2000 );  //delay 2s
     
  }

} 

/*------------------------------------------------------------------------------
  Task 8  --- 7 seg click
 *----------------------------------------------------------------------------*/
void Task8 (void *argument) 
{
	uint8_t counter;
	
  c7seg_default_cfg();
	osDelay (1000U);
  while (1)
	{	
      c7seg_display_mode( C7SEG_DISPLAY_ON );
			osDelay ( 1000 );
			
			for ( counter = 0; counter < 9; counter ++ )
			{
					c7seg_write_data_number( counter, counter + 1 );
					osDelay ( 1000 );
			}
			osDelay ( 1000 );

			for ( counter = 65; counter < 90; counter ++ )
			{
					c7seg_write_data_character( counter, counter + 1 );
					osDelay ( 1000 );
			}
			osDelay ( 1000 );

			c7seg_display_mode( C7SEG_DISPLAY_OFF );
			osDelay ( 1000 );
  }

}  

/*------------------------------------------------------------------------------
 * Application main thread
 *----------------------------------------------------------------------------*/
void app_main (void *argument) {

  LED_Initialize ();                    // Initialize LEDs
  Buttons_Initialize ();                // Initialize Buttons
	
	Init_UART2();
	
	oledb_init();													/*
					INITIALIZARE OLED B click -- functii cheie (vezi fisierul Mikroe\oledb.h): 
		
		oledb_clear_display()
	  oledb_set_contrast
		oledb_write_char
	  oledb_write_string
		
		oledb_send_cmd(  OLEDB_INVERTDISPLAY ); -- inverseaza afisare 
		oledb_send_cmd(  OLEDB_NORMALDISPLAY );  -- afisare normala
	
		https://www.mikroe.com/oled-b-click
		https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks/oledb
	
		Afisorul o resursa -- se recomanda folosirea lui dintr-un singur task sau controlul accesului
		cu un mutex sau un semafor binar daca se acceseaza resursa din mai multe taskuri.		
	*/
	
	proximity7_init();			/*
					
					INITIALIZARE Proximity 7 click -- functii cheie (vezi fisierul Mikroe\proximity7.h): 
		
		proximity7_generic_read
	  proximity7_get_lux_level
		proximity7_get_proximity_data
	
		https://www.mikroe.com/proximity-7-click
		https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks/proximity7
	
		Senzorul este o resursa -- se recomanda folosirea lui dintr-un singur task sau controlul accesului
		cu un mutex sau un semafor binar daca se acceseaza resursa din mai multe taskuri.		
	*/
	
	temphum15_init( );  /*
					
					INITIALIZARE Temp&Hum 15 click -- functii cheie (vezi fisierul Mikroe\temphum15.h): 
		
		temphum15_get_temp_and_hum
			
		https://www.mikroe.com/temphum-15-click
		https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks/temphum15
	
		Senzorul este o resursa -- se recomanda folosirea lui dintr-un singur task sau controlul accesului
		cu un mutex sau un semafor binar daca se acceseaza resursa din mai multe taskuri.		
	*/
	
	c7seg_init();  /*
					
					INITIALIZARE 7seg click -- functii cheie (vezi fisierul Mikroe\c7seg.h): 
		
		c7seg_write_data_number
		c7seg_write_data_character
		
		c7seg_display_mode( C7SEG_DISPLAY_ON );
		c7seg_display_mode( C7SEG_DISPLAY_OFF );		
	
		https://www.mikroe.com/7seg-click
		https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks/7seg
	
		Afisorul este o resursa -- se recomanda folosirea lui dintr-un singur task sau controlul accesului
		cu un mutex sau un semafor binar daca se acceseaza resursa din mai multe taskuri.		
	*/
	
	
  tid_Task1 = osThreadNew (Task1, NULL, NULL);  // Create  task 1
  if (tid_Task1 == NULL) { /* add error handling */ }
	
	tid_Task2 = osThreadNew (Task2, NULL, NULL);  // Create  task 2
  if (tid_Task2 == NULL) { /* add error handling */ }
	
	tid_Task3 = osThreadNew (Task3, NULL, NULL);  // Create  task 3
  if (tid_Task3 == NULL) { /* add error handling */ }
	
	tid_Task4 = osThreadNew (Task4, NULL, NULL);  // Create  task 4
  if (tid_Task4 == NULL) { /* add error handling */ }
	
	tid_Task5 = osThreadNew (Task5, NULL, NULL);  // Create  task 5
  if (tid_Task5 == NULL) { /* add error handling */ }
	
	tid_Task6 = osThreadNew (Task6, NULL, NULL);  // Create  task 6
  if (tid_Task6 == NULL) { /* add error handling */ }
	
	tid_Task7 = osThreadNew (Task7, NULL, NULL);  // Create task 7
  if (tid_Task7 == NULL) { /* add error handling */ }
	
	tid_Task8 = osThreadNew (Task8, NULL, NULL);  // Create task 8
  if (tid_Task8 == NULL) { /* add error handling */ }
	
	// acest task se termina dupa ce a creat task-urile aplicatiei
  osThreadExit();
}

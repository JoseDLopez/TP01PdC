/*=============================================================================
 * Copyright (c) 2020, José Daniel López <josedlopez11@gmail.com>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/05/13
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "TP01PdC.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/
#define UART_PC        UART_USB
#define UART_BLUETOOTH UART_232

#define BAUDRATE 9600

#define ONCOMMAND 66
#define OFFCOMMAND 65
/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/
bool_t hc05Test( int32_t uart );
void hc05PrintATCommands( int32_t uart );

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
   // ----- Setup -----------------------------------
   boardInit();

   uartConfig(UART_PC, BAUDRATE );
   uartConfig(UART_BLUETOOTH, BAUDRATE );

   uartWriteString(UART_PC, "UARTs configured.\r\n" );

   uint8_t data = 0;
   gpioWrite(LEDB,1);
   uartWriteString(UART_PC,"Bluetooth software started! \r\n");

   // ----- Repeat for ever -------------------------
   while( true ) {
      if(uartReadByte(UART_USB, &data)){
         uartWriteByte(UART_232, data);
      }
      if(uartReadByte(UART_232, &data)){
         if ( data == ONCOMMAND){
            gpioWrite(LED1,1);
            uartWriteString(UART_232, "LEDON");
         }

         if ( data == OFFCOMMAND){
            gpioWrite(LED1,0);
            uartWriteString(UART_232, "LEDOFF");
         }
         uartWriteByte(UART_USB, data);
      
      }
   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}

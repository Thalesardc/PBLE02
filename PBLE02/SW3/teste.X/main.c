#include "memoria.h"
#include "pwm.h"
#include "timer.h"
#include "adc.h"
#include "lcd.h"
#include "ssd.h"
#include "keypad.h"
#include "event.h"
#include "var.h"
#include "stateMachine.h"
#include "output.h"
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/system.h"

void main (void) {

    SYSTEM_Initialize();
    //init das bibliotecas
    //lcdInit();
   // timerInit();
    varInit();
    eventInit();
    smInit();
    outputInit();
  //  pwmInit();    
    
    for (;;) {
//        if(UART1_Read() == 'd')
//        {
//                UART1_Write(1 + '0');
//        }
        //timerReset(getTime());
        smLoop();
        //lcdCommand(0x80);
        //lcdData(UART1_Read());
        
        


        //m·quina de estados*/

        


        //timerWait();

        

    }
}
#include <stddef.h>
#include "keypad.h"
#include "event.h"
#include "mcc_generated_files/uart1.h"
#include "var.h"

static unsigned int key_ant;
char valorlido;
char aux[9];
int i = 0;

void eventInit(void) {
    key_ant = 0;
}

unsigned int eventRead(void) {
    int key;
    int ev = EV_NOEVENT;
    static int ev_ant;

   valorlido = UART1_Read();
    
    if (valorlido != 0)
    {
        //UART1_Write(valorlido);
        if ((valorlido == 'D') || (valorlido == 'd'))
        {
            ev = EV_RIGHT;
        }
        else if ((valorlido == 'A') || (valorlido =='a'))
        {
            ev = EV_LEFT;
        }
        else if ((valorlido == 'E') || (valorlido == 'e'))
        {
            ev = EV_ENTER;
        }
        else if ((valorlido == 'W') || (valorlido == 'w'))
        {   
            ev = EV_UP;
            
        }
        else if ((valorlido == 'S') || (valorlido == 's'))
        {
            ev = EV_DOWN;
        }
        else{
          aux[i] = valorlido;
          UART1_Write(i + 48);
          i++;
          if(aux[0] == '#'){
           if((aux[1] == 'T') && (aux[2] == '1') && (aux[3] == 'H')){
               setAlarmLevel1HIGH(((aux[4] - 48)%10)*1000 + ((aux[5] - 48)%10)*100 + ((aux[6] - 48)%10)*10 + ((aux[7] - 48))%10); 
           }
           else if ((aux[1] == 'T') && (aux[2] == '1') && (aux[3] == 'L')){
               setAlarmLevel1LOW(((aux[4] - 48)%10)*1000 + ((aux[5] - 48)%10)*100 + ((aux[6] - 48)%10)*10 + ((aux[7] - 48))%10);
          }
           else if ((aux[1] == 'T') && (aux[2] == '2') && (aux[3] == 'H')){
               setAlarmLevel2HIGH(((aux[4] - 48)%10)*1000 + ((aux[5] - 48)%10)*100 + ((aux[6] - 48)%10)*10 + ((aux[7] - 48))%10);
          }
           else if ((aux[1] == 'T') && (aux[2] == '2') && (aux[3] == 'L')){
               setAlarmLevel2LOW(((aux[4] - 48)%10)*1000 + ((aux[5] - 48)%10)*100 + ((aux[6] - 48)%10)*10 + ((aux[7] - 48))%10);
          }
           else if ((aux[1] == 'Y')){
               setTime(((aux[2] - 48)%10)*1000 + ((aux[3] - 48)%10)*100 + ((aux[4] - 48)%10)*10 + ((aux[5] - 48))%10);
          }
           else if ((aux[1] == 'P') && (aux[2] == 'T')){
               setLanguage(0);
          }
           else if ((aux[1] == 'I') && (aux[2] == 'N')){
               setLanguage(1);
           }
          if (valorlido == '.'){
              i = 0;
          }
          }
        }    
        return ev;
    }
    
    
    
    
    key = kpRead();
    if (key > 400 && key < 570) // botao 1
    {
        ev = EV_RIGHT;

    } else if (key > 570 && key < 660) // botao 2
    {
        ev = EV_ENTER;
    } else if (key > 660 && key < 740) // botao 3
    {
        ev = EV_LEFT;
    } else if (key > 740 && key < 890) // botao 4
    {
        ev = EV_UP;
    } else if (key > 890 && key < 980) // botao 5
    {
        ev = EV_DOWN;
    }

    
    if (ev != ev_ant) {
        ev_ant = ev;
        return ev;
    }else{
        ev_ant = ev;
        return EV_NOEVENT;
    }
    
}

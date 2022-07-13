#include "var.h"
#include "stateMachine.h"
#include "event.h"
#include "output.h"
#include "lcd.h"
#include "keypad.h"
#include "adc.h"
#include "pwm.h"

void smInit(void) {
    setState(STATE_TEMPO);
}

void smLoop(void) {
    unsigned char evento;

    //m�quina de estados
    evento = eventRead();

    switch (getState()) {
        case STATE_ALARME_MENU:  
            //s� mostra na tela os valores P1 e P2 para facilitar
            //execu��o de atividade
            

            //gest�o da maquina de estado
            if (evento == EV_ENTER) {
                setState(STATE_ALARME1);
            }
            
            break;
        case STATE_ALARME1://execu��o de atividade
            if (evento == EV_RIGHT) {
                setAlarmLevel1LOW(getAlarmLevel1LOW() + 1);
            }
            if (evento == EV_LEFT) {
                setAlarmLevel1LOW(getAlarmLevel1LOW() - 1);
            }
            if (evento == EV_UP) {
                setAlarmLevel1HIGH(getAlarmLevel1HIGH() + 1);
            }
            if (evento == EV_DOWN) {
                setAlarmLevel1HIGH(getAlarmLevel1HIGH() - 1);
            }

            //gest�o da maquina de estado
            if (evento == EV_ENTER) {
                setState(STATE_ALARME2);
            }
            break;
            case STATE_ALARME2://execu��o de atividade
            if (evento == EV_RIGHT) {
                setAlarmLevel2LOW(getAlarmLevel2LOW() + 1);
            }
            if (evento == EV_LEFT) {
                setAlarmLevel2LOW(getAlarmLevel2LOW() - 1);
            }
            if (evento == EV_UP) {
                setAlarmLevel2HIGH(getAlarmLevel2HIGH() + 1);
            }
            if (evento == EV_DOWN) {
                setAlarmLevel2HIGH(getAlarmLevel2HIGH() - 1);
            }

            //gest�o da maquina de estado
            if (evento == EV_ENTER) {
                setState(STATE_TEMPO);
            }
            break;
        case STATE_TEMPO:

            //execu��o de atividade
            if (evento == EV_RIGHT) {
                setTime(getTime() + 1);
            }
            if (evento == EV_LEFT) {
                setTime(getTime() - 1);
            }

            //gest�o da maquina de estado
            if (evento == EV_ENTER) {
                setState(STATE_IDIOMA);
            }
            break;

        case STATE_IDIOMA:

            //execu��o de atividade
            if (evento == EV_RIGHT) {
                setLanguage(getLanguage() + 1);
            }
            if (evento == EV_LEFT) {
                setLanguage(getLanguage() - 1);
            }

            //gest�o da maquina de estado
            if (evento == EV_ENTER) {
                setState(STATE_ALARME_MENU);
            }
            break;
//        case STATE_HORA:
//            //execu��o de atividade
//            if (evento == EV_RIGHT) {
//                setState(STATE_ALARME);
//            }
//            if (evento == EV_LEFT) {
//                setState(STATE_ALARME);
//            }
//
//            //gest�o da maquina de estado
//            if (evento == EV_ENTER) {
//                setState(STATE_ALARME);
//            }
//            break;



    }
    teste1(); //chama a verificao de ativacao do alarme




    outputPrint(getState(), getLanguage());
}
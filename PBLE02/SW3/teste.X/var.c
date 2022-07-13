#include "var.h"
#include "adc.h"
#include "pwm.h"
#include "mcc_generated_files/pin_manager.h"
#include "memoria.h"

//variáveis a serem armazenadas
static char state;
//static char language;
static int time;
static int alarmLevel1HIGH;
static int alarmLevel1LOW;
static int alarmLevel2HIGH;
static int alarmLevel2LOW;
//TRISC = 0x00;

void varInit(void) {
    state = 0;
    time = 1000;
    alarmLevel1HIGH = 200;
    alarmLevel1LOW = 100;
    alarmLevel2HIGH = 200;
    alarmLevel2LOW = 100;
    //MEMwrite(0, 1, 200);
    //MEMwrite(0, 2, 200);
    
}

char getState(void) {
    return state;
//    return MEMread(0, 5);
}

void setState(char newState) {
    state = newState;
//    MEMwrite(0, 5, newState);
}

int getTime(void) {
//    return time;
    return MEMread(0, 6);
}

void setTime(int newTime) {
//    time = newTime;
    MEMwrite(0, 6, newTime);
}

int getAlarmLevel1HIGH(void) {
    //return alarmLevel1HIGH;
    return MEMread(0, 1);
}

int getAlarmLevel1LOW(void) {
    //return alarmLevel1LOW;
    return MEMread(0, 2);
}
int getAlarmLevel2HIGH(void) {
    //return alarmLevel1HIGH;
    return MEMread(0, 11);
}

int getAlarmLevel2LOW(void) {
    //return alarmLevel1LOW;
    return MEMread(0, 10);
}

void setAlarmLevel1HIGH(int newAlarmLevel1HIGH) {
    //alarmLevel1HIGH = newAlarmLevel1HIGH;
    if(newAlarmLevel1HIGH > 254){
        newAlarmLevel1HIGH = 254;
    }
    MEMwrite(0, 1, newAlarmLevel1HIGH);
}

void setAlarmLevel1LOW(int newAlarmLevel1LOW) {
   // alarmLevel1LOW = newAlarmLevel1LOW;
    if(newAlarmLevel1LOW < 1){
        newAlarmLevel1LOW = 1;
    }
    MEMwrite(0, 2, newAlarmLevel1LOW);
}

void setAlarmLevel2HIGH(int newAlarmLevel2HIGH) {
    //alarmLevel1HIGH = newAlarmLevel1HIGH;
    if(newAlarmLevel2HIGH > 254){
        newAlarmLevel2HIGH = 254;
    }
    MEMwrite(0, 11, newAlarmLevel2HIGH);
}

void setAlarmLevel2LOW(int newAlarmLevel2LOW) {
   // alarmLevel1LOW = newAlarmLevel1LOW;
    if(newAlarmLevel2LOW < 1){
        newAlarmLevel2LOW = 1;
    }
    MEMwrite(0, 10, newAlarmLevel2LOW);
}
//pmwInit();
//teste1 faz a verificaçao pra ver se a flag do alarme ta dentro de P1 e P2, se tiver liga vento, se não tiver, desliga

void teste1(void) {

    if (adcRead1() >= getAlarmLevel1HIGH()) {
        LED1_SetHigh();
    } else {
        LED1_SetLow();
    }

    if (adcRead1() <= getAlarmLevel1LOW()) {
        LED2_SetHigh();
    } else {
        LED2_SetLow();
    }

    if (adcRead2() >= getAlarmLevel2HIGH()) {
        LED3_SetHigh();
    } else {
        LED3_SetLow();
    }

    if (adcRead2() <= getAlarmLevel2LOW()) {
        LED4_SetHigh();
    } else {
        LED4_SetLow();
    }

}

char getLanguage(void) {

    //return language;
    return MEMread(0, 3);
}

void setLanguage(char newLanguage) {
    //só tem 4 linguas
    //usando resto pra evitar colocar valor errado
    if (newLanguage < 0) {
        MEMwrite(0, 3, 3);
        //language = 3;
    } else {
        MEMwrite(0, 3, newLanguage%4);
        //language = newLanguage % 4;
    }
    
}

int retornaHora(void) {
    int z = 0;

    // z = rtcGetHours();

    return z;
}
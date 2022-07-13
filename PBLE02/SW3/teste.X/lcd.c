#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/system.h"
#include "lcd.h"

//funções de bit
#define BitSet(arg,bit) ((arg) |= (1<<bit))
#define BitClr(arg,bit) ((arg) &= ~(1<<bit)) 
#define BitFlp(arg,bit) ((arg) ^= (1<<bit)) 
#define BitTst(arg,bit) ((arg) & (1<<bit)) 

void delayMS(unsigned char ms) {
    volatile unsigned int i;
    for (; ms > 0; ms--)
    {
        for (i = 0; i < 30; i++);
    }
}

void pulseEnablePin() {
    E_SetHigh();
    E_SetLow();
}

void pushNibble(int value, int rs) {
    if (BitTst(value, 4)) D4_SetHigh();
    else D4_SetLow();
    if (BitTst(value, 5)) D5_SetHigh();
    else D5_SetLow();
    if (BitTst(value, 6)) D6_SetHigh();
    else D6_SetLow();
    if (BitTst(value, 7)) D7_SetHigh();
    else D7_SetLow();
    if (rs) RS_SetHigh();
    else RS_SetLow();
    pulseEnablePin();
}

void pushByte(int value, int rs) {
    int val_lower = (value << 4) &0xf0;
    int val_upper = value & 0xF0;
    pushNibble(val_upper, rs);
    pushNibble(val_lower, rs);
}

void lcdChar(int value) {
    //let pushByte worry about the intricacies of Enable, nibble order.
    pushByte(value, 1);
    delayMS(1);
}

void lcdCommand(int value) {
    pushByte(value, 0);
    delayMS(1);
}

void lcdCommand4bits(int nibble) {
    pushNibble(nibble << 4, 0);
}

void lcdInit() {
    E_SetDigitalOutput();
    RS_SetDigitalOutput();
    D4_SetDigitalOutput();
    D5_SetDigitalOutput();
    D6_SetDigitalOutput();
    D7_SetDigitalOutput();
    LCD_LED_SetHigh(); //acende luz de fundo do LCD

    delayMS(15); //15ms

    //The first 4 nibbles and timings are not in my DEM16217 SYH datasheet, but apparently are HD44780 standard...
    lcdCommand4bits(0x03);
    delayMS(1);
    lcdCommand4bits(0x03);
    delayMS(1); //100us
    lcdCommand4bits(0x03);
    delayMS(5);

    // needed by the LCDs controller
    //this being 2 sets up 4-bit mode.
    lcdCommand4bits(0x02);
    delayMS(1);

    //configura o display
    lcdCommand(0x28); //8bits, 2 linhas, 5x8
    lcdCommand(0x06); //modo incremental
    lcdCommand(0x0c); //display e cursor on, com blink
    lcdCommand(0x03); //zera tudo
    lcdCommand(0x80); //posição inicial
    lcdCommand(0x01); //limpar display
}

void lcdString(char msg[]) {
    unsigned char i = 0; //fancy int.  avoids compiler warning when comparing i with strlen()'s uint8_t
    while (msg[i]) {
        lcdChar(msg[i]);
        i++;
    }
}

void lcdData(unsigned char value){
    pushByte(value,1);
    delayMS(2);
}

//imprime o nível de alarme

void lcdIntLevel(int val) {
    lcdData((val / 1000) % 10 + 48);
    lcdData((val / 100) % 10 + 48);
    lcdData((val / 10) % 10 + 48);
    lcdData((val / 1) % 10 + 48);
}

//imprime o tempo, usado no submenu de ultimo alarme

void lcdIntTime(int val) {
    lcdData(((val / 1000) % 10) + 48); //horas
    lcdData(((val / 100) % 10) + 48);
    lcdData(':');
    lcdData(((val / 10) % 10) + 48); //minutos
    lcdData(((val / 1) % 10) + 48);
}
void lcdIntDate(int val) {
    lcdData(((val / 1000) % 10) + 48); //mês
    lcdData(((val / 100) % 10) + 48);
    lcdData('/');
    lcdData(((val / 10) % 10) + 48); //dia
    lcdData(((val / 1) % 10) + 48);
}

//imprime os segundos, usado no submenu de tempo de alarme

void lcdIntTimeSeconds(int val) {
    lcdData(((val / 1) % 10) + 48);
}
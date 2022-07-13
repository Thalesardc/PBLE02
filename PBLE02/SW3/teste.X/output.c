#include "output.h"
#include "lcd.h"
#include "stateMachine.h"
#include "var.h"
#include "adc.h"


#define NUM_IDIOMAS 4

//msgs com 16 caracteres
//1 msg por estado (apenas linha de cima)
static char * msgs[STATE_FIM][NUM_IDIOMAS] = {
    {"Valor do alarme   ", "Alarm value      ","Flaggenwert     ","Valeur du signal"},
    {"Alterar alarme 1 ", "Change alarm 1    ","Alarm andern 1    ","Changer D alarme 1"},
    {"Alterar alarme 2  ", "Change alarm 2    ","Alarm andern 2   ","Changer D alarme 2"},
    {"Alterar tempo   ", "Change time     ","Zeit andern     ","Changer le temp "},
    {"Alterar idioma  ", "Change language ","Sprache andern  ","Changer la langu"},
};

void outputInit(void) {
    lcdInit();
}

void outputPrint(int numTela, int idioma) {

    if (numTela == STATE_TEMPO) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        lcdIntLevel(getTime());
        lcdString("           ");//para apagar os textos depois do numero
    }
    if (numTela == STATE_ALARME1) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        lcdIntLevel(getAlarmLevel1LOW());
        lcdString("   ");//para apagar os textos depois do numero
        lcdIntLevel(getAlarmLevel1HIGH());
        lcdString("     ");
    }
    if (numTela == STATE_ALARME2) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        lcdIntLevel(getAlarmLevel2LOW());
        lcdString("   ");//para apagar os textos depois do numero
        lcdIntLevel(getAlarmLevel2HIGH());
        lcdString("     ");
    }
    if (numTela == STATE_ALARME_MENU) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        //lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        
        lcdString("A1 ");
        lcdIntLevel (adcRead1());
        lcdString(" A2 ");
        lcdIntLevel(adcRead2());
        lcdString("           ");//para apagar os textos depois do numero
    }
    if (numTela == STATE_IDIOMA) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        //serial_write())
        lcdCommand(0xC0);
        if (getLanguage() == 0) {
            lcdString("Portugues       ");
        }
        if (getLanguage() == 1) {
            lcdString("English         ");
        }
        if (getLanguage() == 2) {
            lcdString("Deutsche        ");
        }
        if (getLanguage() == 3) {
            lcdString("Francais        ");
        }
       

    }
    
    
}
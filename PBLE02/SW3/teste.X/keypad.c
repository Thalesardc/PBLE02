// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2014
// -----------------------------------------------------------------------
//   Arquivo: keypad.c
//            Biblioteca de operação de um teclado matricial
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licença: GNU GPL 2
// -----------------------------------------------------------------------
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; version 2 of the License.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// -----------------------------------------------------------------------

#include "keypad.h"
#include "mcc_generated_files/adc1.h"

//static unsigned char valor = 0x00;

unsigned int kpRead(void) {
    int conversion;
    ADC1_Initialize();
    ADC1_ChannelSelect(TECLADO);
    ADC1_Start();
    //Provide Delay
    for(int i=0;i <1000;i++)
    {
    }
    ADC1_Stop();
    while(!ADC1_IsConversionComplete())
    {
        ADC1_Tasks();   
    }
    conversion = ADC1_ConversionResultGet(); // Pega Analógico convertido para Digital
    return conversion;
}

//void kpDebounce(void) {
//    unsigned char i, j;
//    static unsigned char tempo;
//    static unsigned char valorNovo = 0x0000;
//    static unsigned char valorAntigo = 0x0000;
//
//    for (i = 0; i < 4; i++) {
//        TRISB = ~((unsigned char)1<<i);
//        PORTB = ~((unsigned char)1<<i);
//
//        //realiza o teste para cada bit e atualiza a variável
//        for (j = 0; j < 2; j++) {
//            if (!BitTst(PORTB, j + 4)) {
//                BitSet(valorNovo, (i * 2) + j);
//            } else {
//                BitClr(valorNovo, (i * 2) + j);
//            }
//        }
//    }
//    if (valorAntigo == valorNovo) {
//        tempo--;
//    } else {
//        tempo = 10;
//        valorAntigo = valorNovo;
//    }
//    if (tempo == 0) {
//        valor = valorAntigo;
//    }
//}
//

#include "mcc_generated_files/adc1.h"

int adcRead1(void)
{
//  int conversion;
  ADC1_Initialize();
  ADC1_ChannelSelect(ANA15);
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
  //return ADC1_ConversionResultGet(); 
  return 50;
}

int adcRead2(void) {
    
  ADC1_Initialize();
  ADC1_ChannelSelect(ANA1);
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
  //return ADC1_ConversionResultGet();
  return 50;
}


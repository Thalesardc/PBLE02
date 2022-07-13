/* 
 * File:   alarme.h
 * Author: Avell
 *
 * Created on 14 de Junho de 2017, 16:10
 */

#ifndef VAR_H
#define	VAR_H

void varInit(void);

char getState(void);
void setState(char newState);
int getTime(void);
void setTime(int newTime);
int getAlarmLevel1LOW(void);
int getAlarmLevel1HIGH(void);
int getAlarmLevel2LOW(void);
int getAlarmLevel2HIGH(void);
void setAlarmLevel1HIGH(int newAlarmLevel1HIGH);
void setAlarmLevel1LOW(int newAlarmLevel1LOW);
void setAlarmLevel2HIGH(int newAlarmLevel2HIGH);
void setAlarmLevel2LOW(int newAlarmLevel2LOW);
char getLanguage(void);
void setLanguage(char newLanguage);
int  retornaHora(void);
void teste1 (void);
#endif	/* VAR_H */

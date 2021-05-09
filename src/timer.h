/*
 * Timer.h
 *
 * Created: 5/5/2021 16:47:53
 *  Author: Julián
 */

#ifndef TIMER_H_
#define TIMER_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

/*
	flag -	Posición de memoria donde se avisará que se estableció el Flag TOV0
*/
void Timer_Init_Timer0(int *flag);

/*
	flag -	Posición de memoria donde se va a escribir un 1 cuando transcurra 1s
*/
void Timer_Init_Timer2(int *flag);

/**
	ms -	Cantidad de ms que se desea que sea el retardo
*/
void Timer_Set_Delay(int ms);

#endif /* TIMER_H_ */
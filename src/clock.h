/*
 * Clock.h
 *
 * Created: 7/5/2021 20:04:24
 *  Author: Julián
 */

#ifndef CLOCK_H_
#define CLOCK_H_

/*
	hours - Valor de la hora a establecer
*/
void Clock_Set_Hours(short int hours);

/*
	minutes - Valor de los minutos a establecer
*/
void Clock_Set_Minutes(short int minutes);

/*
	seconds - Valor de la seconds a establecer
*/
void Clock_Set_Seconds(short int seconds);

/*
	Devuelve la hora actual
*/
short int Clock_Get_Hours();

/*
	Devuelve los minutos actuales
*/
short int Clock_Get_Minutes();

/*
	Devuelve los segundos actuales
*/
short int Clock_Get_Seconds();

/*
	Indica al Clock que se tiene que incrementar en 1s
*/
void Clock_Tick();

#endif /* CLOCK_H_ */
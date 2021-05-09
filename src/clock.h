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
void Clock_Set_Hours();

/*
	minutes - Valor de los minutos a establecer
*/
void Clock_Set_Minutes();

/*
	seconds - Valor de la seconds a establecer
*/
void Clock_Set_Seconds();

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

/*
    Devuelve si se termino de ingresar la hora o no
*/
char Clock_End();

/*
    Limpia todas las variables internas devolviendo al reloj a un estado por defecto
*/
void Clock_Clean();

/*
    Almacena temporalmente el dígito que se envía
*/
void Clock_SendDigit(short int digit);

#endif /* CLOCK_H_ */
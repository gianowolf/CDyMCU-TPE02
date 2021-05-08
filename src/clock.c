/*
 * Clock.c
 *
 * Created: 7/5/2021 20:04:11
 *  Author: Julián
 */

static short int _hours = 0;
static short int _minutes = 0;
static short int _seconds = 0;
/*
	hours - Valor de la hora a establecer
*/
void Clock_Set_Hour(short int hours)
{
    _hours = hours;
}

/*
	minutes - Valor de los minutos a establecer
*/
void Clock_Set_Minutes(short int minutes)
{
    _minutes = minutes;
}

/*
	seconds - Valor de la seconds a establecer
*/
void Clock_Set_Seconds(short int seconds)
{
    _seconds = seconds;
}

/*
	Devuelve la hora actual
*/
short int Clock_Get_Hours()
{
    return _hours;
}

/*
	Devuelve los minutos actuales
*/
short int Clock_Get_Minutes()
{
    return _minutes;
}

/*
	Devuelve los segundos actuales
*/
short int Clock_Get_Seconds()
{
    return _seconds;
}

/*
	Indica al Clock que se tiene que incrementar en 1s
*/
void Clock_Tick()
{
    short int secondOverflow = (_seconds == 59);
    short int minuteOverflow = (_minutes == 59);

    _seconds = (_seconds + 1) % 60;
    _minutes = (_minutes + secondOverflow) % 60;
    _hours = (_hours + minuteOverflow) % 24;
}
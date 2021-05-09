/*
 * Clock.c
 *
 * Created: 7/5/2021 20:04:11
 *  Author: Julián
 */

static short int hours = 0;
static short int minutes = 0;
static short int seconds = 0;

static char tempValue[] = {0, 0}; // valor que se va almacenando cuando se quiere cambiar la hora
static char index = 0;            // posición en tempValue donde se está escribiendo

/*
	Guarda la hora con lo que se cargó hasta el momento
*/
void Clock_Set_Hour()
{
    hours = tempValue[0] * 10 + tempValue[1];
}

/*
	Guarda los minutos con lo que se cargó hasta el momento
*/
void Clock_Set_Minutes(short int minutes)
{
    minutes = tempValue[0] * 10 + tempValue[1];
}

/*
	Guarda los segundos con lo que se cargó hasta el momento
*/
void Clock_Set_Seconds(short int seconds)
{
    seconds = tempValue[0] * 10 + tempValue[1];
}

/*
	Devuelve la hora actual
*/
short int Clock_Get_Hours()
{
    return hours;
}

/*
	Devuelve los minutos actuales
*/
short int Clock_Get_Minutes()
{
    return minutes;
}

/*
	Devuelve los segundos actuales
*/
short int Clock_Get_Seconds()
{
    return seconds;
}

/*
	Indica al Clock que se tiene que incrementar en 1s
*/
void Clock_Tick()
{
    short int secondOverflow = (seconds == 59);
    short int minuteOverflow = (minutes == 59);

    seconds = (seconds + 1) % 60;
    minutes = (minutes + secondOverflow) % 60;
    hours = (hours + minuteOverflow) % 24;
}

/*
    Devuelve si se termino de ingresar la hora o no
*/
char Clock_End()
{
    return index == 2;
}

/*
    Limpia todas las variables internas devolviendo al reloj a un estado por defecto
*/
void Clock_Clean()
{
    tempValue[0] = 0;
    tempValue[1] = 0;
    index = 0;
}

/*
    Almacena temporalmente el dígito que se envía
*/
void Clock_SendDigit(short int digit)
{
    tempValue[index++] = digit;
}
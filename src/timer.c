/*
 * Timer.c
 *
 * Created: 5/5/2021 16:47:31
 *  Author: Julián
 */

#include "Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define SET(port, bit) port |= (1 << bit)
#define CLR(port, bit) port &= ~(1 << bit)
#define TOGGLE(port, bit) port ^= (1 << bit)

#define IS_SET(port, bit) port &(1 << bit)
#define IS_CLR(port, bit) ~(port & (1 << bit))

static int *timer_flag;            // posición de memoria donde se indica que se levantó el Flag de desbordamiento
static int *timer2_flag;           // posición de memoria donde se indica que se levantó el Flag de comparación del registro A para el Timer2
static unsigned short count = 0;   // capaz de contar hasta 65,536s
static unsigned short trigger = 0; // pasado este umbral se activa el timer_flag
static short int initial = 0;      // valor a colocar en el TCNT0 para que produzca una interrupción cada 1ms

void Init_Timer0()
{
    /* Establezco el Timer0 en Modo Normal */
    CLR(TCCR0A, WGM00);
    CLR(TCCR0A, WGM01);
    CLR(TCCR0B, WGM02);

    /* El valor inicial del contador es 0 */
    TCNT0 = 0x00;

    /* Habilito la interrupción por desbordamiento del Timer0 */
    SET(SREG, 7); // Habilitador global de interrupciones
    SET(TIMSK0, TOIE0);

    /* Calculo el valor initial */
    initial = 256 - (1e-3) * F_CPU / 64;
}

void Init_Timer2(int *flag)
{
    // a. Disable the Timer/Counter2 interrupts by clearing OCIE2x and TOIE2.
    CLR(TIMSK2, OCIE2A);
    CLR(TIMSK2, TOIE2);

    // b. Select clock source by setting AS2 as appropriate.
    /* Elijo como fuente de reloj, el oscilador de 32768Hz */
    SET(ASSR, AS2);

    // c. Write new values to TCNT2, OCR2x, and TCCR2x.

    /* El valor inicial del contador es 0 */
    TCNT2 = 0x00;

    /* Valor de comparación para producir una interrupción cada 1s */
    OCR2A = 32;

    /* Elijo el pre-escalador 1:1024 */
    SET(TCCR2B, CS20);
    SET(TCCR2B, CS21);
    SET(TCCR2B, CS22);

    /* Establezco el Timer2 en Modo CTC */
    CLR(TCCR2A, WGM20);
    SET(TCCR2A, WGM21);
    CLR(TCCR2B, WGM22);

    // d. To switch to asynchronous operation: Wait for TCN2xUB, OCR2xUB, and TCR2xUB.
    //while (IS_CLR(ASSR,TCN2UB) && IS_CLR(ASSR,OCR2AUB) && IS_CLR(ASSR,TCR2AUB));

    // e. Clear the Timer/Counter2 Interrupt Flags.
    CLR(TIFR2, TOV2);
    CLR(TIFR2, OCF2A);
    CLR(TIFR2, OCF2B);

    // f. Enable interrupts, if needed

    /* Habilito la interrupción por Comparación del Timer2 */
    SET(SREG, 7); // Habilitador global de interrupciones
    SET(TIMSK2, OCIE2A);

    /* Almaceno la dirección donde voy a indicar el flag de 1s */
    timer2_flag = flag;
}

void Enable_Timer()
{
    /* Elijo el prescalador 1:64, entrada = 3 */
    SET(TCCR0B, CS00);
    SET(TCCR0B, CS01);
    CLR(TCCR0B, CS02);
}

void Disable_Timer()
{
    /* Elijo el prescalador 0, entrada = 0 */
    CLR(TCCR0B, CS00);
    CLR(TCCR0B, CS01);
    CLR(TCCR0B, CS02);
}

void Set_Delay(int ms, int *flag)
{
    timer_flag = flag;
    TCNT0 = initial; // valor para que el timer cuente 1ms
    count = 0;
    trigger = ms;
    Enable_Timer();
}

/* Rutina de interrupción cuando hay desbordamiento en el Timer0 */
ISR(TIMER0_OVF_vect)
{
    if (count++ == trigger)
    {
        *timer_flag = 1; // Indico que transcurrió el tiempo de demora

        Disable_Timer();
        CLR(TIFR0, TOV0); // Limpio el Flag de Overflow porque hay que hacerlo manualmente
    }
    TCNT0 = initial;
}

/* Rutina de interrupción cuando hay una comparación del registro TCNT2 con OCR2A */
ISR(TIMER2_COMPA_vect)
{
    *timer2_flag = 1;
}
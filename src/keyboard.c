/*
 * Keypad.c
 *
 * Created: 7/5/2021 23:00:21
 *  Author: Julián
 */

#include "Keypad.h"
#include <avr/io.h>

static unsigned char prev = 1;
static unsigned char deb = 0;

void Keypad_Init()
{
    DDROUT = 0x0F;
    DDRIN = 0x0F;
}

unsigned char Keypad_Scan(unsigned char *key)
{
    unsigned char secuencia[] = {0xFD, 0xFB, 0xF7, 0xFE};
    unsigned char i, renglon, dato;

    /* Itero por cada fila del Keypad */
    for (renglon = 0, i = 0; i < 4; i++)
    {
        PORTOUT = secuencia[i]; // Ubica la salida

        dato = PININ & 0x0F; // Lee la entrada
        deb = dato;
        //if(dato!=0x00) { asm("break"); }
        if (dato != 0x00 && prev == 1)
        { // Si se presionó una tecla, lectura de esta forma para evitar rebotes
            switch (dato)
            { // Revisa las columnas
            case 0x0E:
                *key = renglon;
                break;
            case 0x0D:
                *key = renglon + 1;
                break;
            case 0x0B:
                *key = renglon + 2;
                break;
            case 0x07:
                *key = renglon + 3;
                break;
            case 0x00:
                return 0;
                break;
            case 0x01:
                *key = renglon;
                break;
            case 0x02:
                *key = renglon + 1;
                break;
            case 0x03:
                break;
            case 0x04:
                *key = renglon + 2;
                break;
            case 0x05:
                break;
            case 0x06:
                break;
            case 0x08:
                *key = renglon + 3;
                break;
            case 0x09:
                break;
            case 0x0A:
                break;
            case 0x0C:
                break;
            case 0x0F:
                break;
            }
            prev = (dato == 0x00);
            return 1;
        }
        prev = (dato == 0x00);
        renglon += 4; // Revisa el siguiente renglón
    }
    return 0;
}
/*
 * Keypad.h
 *
 * Created: 7/5/2021 23:00:34
 *  Author: Julián
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define DDROUT DDRB
#define PORTOUT PORTB
#define DDRIN DDRC
#define PININ PINC

/*
	Lee las entradas del Teclado, si se presionó una tecla, en el 
	flanco de bajada retorna 1, y devuelve en key la tecla presionada
*/
unsigned char Keypad_Scan(unsigned char *key);

/*
	Inicializa el Keypad configurando los puertos
*/
void Keypad_Init();

#endif /* KEYPAD_H_ */
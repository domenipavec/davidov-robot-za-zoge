#ifndef ROBOT_H
#define ROBOT_H

#include "avr-cpp-lib/bitop.h"
#include "avr-cpp-lib/lcds.h"

#include <stdint.h>
#define F_CPU 8000000UL  // 8 MHz
    
#include <avr/io.h>
#include <avr/pgmspace.h>

void uartCommand(uint8_t c);

#define MOTOR_0_NAPREJ (BIT(1))
#define MOTOR_0_NAZAJ (BIT(2))
#define MOTOR_0_STOP (0)
#define MOTOR_0_BREMZA (BIT(1) | BIT(2))
#define MOTOR_1_NAPREJ (BIT(3))
#define MOTOR_1_NAZAJ (BIT(4))
#define MOTOR_1_STOP (0)
#define MOTOR_1_BREMZA (BIT(3) | BIT(4))
#define MOTOR_0_RAZDALJA (BIT(5))
#define MOTOR_1_RAZDALJA (BIT(6))
void motorPremik(uint8_t c, uint16_t v = 0);

#define MOTOR_0_HITROST (BIT(1))
#define MOTOR_1_HITROST (BIT(2))
#define MOTOR_0_MOC (BIT(3))
#define MOTOR_1_MOC (BIT(4))
void motorNastavi(uint8_t c, uint16_t v);

void pripravi();

void osvetliZaslon(uint8_t i);
void ugasniZaslon();

void pisk(uint16_t f);
void stopPisk();

void pavza(uint16_t i);

#define MOTOR_SE_PREMIKA (BITSET(PIND, PD2))
#define GUMB0 (BITCLEAR(PINC, PC3))
#define GUMB1 (BITCLEAR(PINC, PC4))
#define GUMB2 (BITCLEAR(PINC, PC5))
#define GUMB3 (BITCLEAR(PINC, PC6))
#define GUMB4 (BITCLEAR(PINC, PC7))

inline void luc0prizgi() {
	SETBIT(PORTB, PB4);
}
inline void luc0ugasni() {
	CLEARBIT(PORTB, PB4);
}
inline void luc1prizgi() {
	SETBIT(PORTB, PB3);
}
inline void luc1ugasni() {
	CLEARBIT(PORTB, PB3);
}
inline void luc2prizgi() {
	SETBIT(PORTB, PB2);
}
inline void luc2ugasni() {
	CLEARBIT(PORTB, PB2);
}
inline void luc3prizgi() {
	SETBIT(PORTB, PB1);
}
inline void luc3ugasni() {
	CLEARBIT(PORTB, PB1);
}
inline void luc4prizgi() {
	SETBIT(PORTB, PB0);
}
inline void luc4ugasni() {
	CLEARBIT(PORTB, PB0);
}

extern avr_cpp_lib::LCDS lcd;

#define LCD_LOKACIJA(x,y) lcd.gotoXY((x),(y))
#define LCD_TEKST(x) lcd.writeFlash(PSTR(x))
#define LCD_DOMOV() lcd.command(avr_cpp_lib::LCDS::HOME)
#define LCD_STEVILKA(x,y) lcd.write((x), (y))
#define LCD_POCISTI() lcd.command(avr_cpp_lib::LCDS::CLEAR)
#define LCD_KAZALEC_PRIZGI() lcd.command(avr_cpp_lib::LCDS::CURSOR_ON)
#define LCD_KAZALEC_UTRIPANJE() lcd.command(avr_cpp_lib::LCDS::CURSOR_ON_BLINK)
#define LCD_KAZALEC_UGASNI() lcd.command(avr_cpp_lib::LCDS::CURSOR_OFF)
#define LCD_KAZALEC_DESNO() lcd.command(avr_cpp_lib::LCDS::CURSOR_RIGHT)
#define LCD_KAZALEC_LEVO() lcd.command(avr_cpp_lib::LCDS::CURSOR_LEFT)
#define LCD_UGASNI() lcd.command(avr_cpp_lib::LCDS::DISPLAY_OFF)
#define LCD_PRIZGI() lcd.command(avr_cpp_lib::LCDS::DISPLAY_ON)
#define LCD_PREMAKNI_DESNO() lcd.command(avr_cpp_lib::LCDS::DISPLAY_RIGHT)
#define LCD_PREMAKNI_LEVO() lcd.command(avr_cpp_lib::LCDS::DISPLAY_LEFT)

#endif

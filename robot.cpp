#include "robot.h"
#include <util/delay.h>

void uartCommand(uint8_t c) {
	for (int8_t i = 8; i > 0; i--) {
		if (BITSET(c, i-1)) {
			SETBIT(PORTB, PB6);
		} else {
			CLEARBIT(PORTB, PB6);
		}
		__builtin_avr_delay_cycles(120);
		SETBIT(PORTB, PB7);
		__builtin_avr_delay_cycles(120);
		CLEARBIT(PORTB, PB7);
		__builtin_avr_delay_cycles(120);
	}
}

void pripravi() {
	pavza(2000);
	
	// za komunikacijo
	SETBIT(DDRB, PB6);
	SETBIT(DDRB, PB7);

	// za pwm
	SETBIT(DDRD, PD4);
	SETBIT(DDRD, PD5);

	// nastavitev pwm timer-ja
	TCCR1A = BIT(WGM11);
	TCCR1B = BIT(WGM12) | BIT(WGM13) | BIT(CS10);

	// gumbi
	SETBITS(PORTC, BIT(PC3) | BIT(PC4) | BIT(PC5) | BIT(PC6) | BIT(PC7));
}

volatile uint8_t DI_LCD_INTENSITY = 0xff;
volatile uint16_t DI_ICR1 = 0xff;

void updateFrequency() {
	uint32_t temp = DI_LCD_INTENSITY;
	temp *= DI_ICR1;
	temp /= 0xff;
	ICR1 = DI_ICR1;
	OCR1A = temp;
	OCR1B = ICR1/2;
}

void osvetliZaslon(uint8_t i) {
	DI_LCD_INTENSITY = i;
	updateFrequency();
	SETBIT(TCCR1A, COM1A1);
}

void ugasniZaslon() {
	CLEARBIT(TCCR1A, COM1A1);
}

void pisk(uint16_t f) {
	uint32_t temp = F_CPU;
	temp /= f;
	DI_ICR1 = temp;
	updateFrequency();
	SETBIT(TCCR1A, COM1B1);
}

void stopPisk() {
	CLEARBIT(TCCR1A, COM1B1);
}

void motorPremik(uint8_t c, uint16_t v) {
	uartCommand(BIT(0) | c | BIT(7));
	uartCommand(v >> 8);
	uartCommand(v & 0xff);
}

void motorNastavi(uint8_t c, uint16_t v) {
	uartCommand(c | BIT(7));
	uartCommand(v >> 8);
	uartCommand(v & 0xff);
}

void pavza(uint16_t i) {
	for (; i > 0; i--) {
		_delay_ms(1);
	}
}


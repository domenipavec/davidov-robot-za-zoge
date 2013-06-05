#include "robot.h"
#include <util/delay.h>

void uartCommand(uint8_t c) {
	for (int8_t i = 8; i > 0; i--) {
		if (BITSET(c, i-1)) {
			SETBIT(PORTB, PB6);
		} else {
			CLEARBIT(PORTB, PB6);
		}
		_delay_ms(1);
		SETBIT(PORTB, PB7);
		_delay_ms(1);
		CLEARBIT(PORTB, PB7);
		_delay_ms(1);
	}
}

void motorPripravi() {
	SETBIT(DDRB, PB7);
	SETBIT(DDRB, PB6);
}

void motor0naprej(uint16_t d) {
	uartCommand(13);
	uartCommand(d >> 8);
	uartCommand(d & 0xff);
}

void motor0nazaj(uint16_t d) {
	uartCommand(15);
	uartCommand(d >> 8);
	uartCommand(d & 0xff);
}

void motor0bremza() {
	uartCommand(5);
	uartCommand(0);
	uartCommand(0);
}

void motor0stop() {
	uartCommand(7);
	uartCommand(0);
	uartCommand(0);
}

void motor0hitrost(uint16_t h) {
	uartCommand(9);
	uartCommand(h >> 8);
	uartCommand(h & 0xff);
}

void motor0moc(uint16_t m) {
	uartCommand(11);
	uartCommand(m >> 8);
	uartCommand(m & 0xff);
}

void motor1naprej(uint16_t d) {
	uartCommand(14);
	uartCommand(d >> 8);
	uartCommand(d & 0xff);
}

void motor1nazaj(uint16_t d) {
	uartCommand(16);
	uartCommand(d >> 8);
	uartCommand(d & 0xff);
}

void motor1bremza() {
	uartCommand(6);
	uartCommand(0);
	uartCommand(0);
}

void motor1stop() {
	uartCommand(8);
	uartCommand(0);
	uartCommand(0);
}

void motor1hitrost(uint16_t h) {
	uartCommand(10);
	uartCommand(h >> 8);
	uartCommand(h & 0xff);
}

void motor1moc(uint16_t m) {
	uartCommand(12);
	uartCommand(m >> 8);
	uartCommand(m & 0xff);
}

void pavza(uint16_t i) {
	for (; i > 0; i--) {
		_delay_ms(1);
	}
}

void pocakajMotor() {
	while(BITSET(PIND, PD2));
}

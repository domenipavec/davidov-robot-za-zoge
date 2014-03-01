#include "robot.h"
#include <util/delay.h>
#include <avr/interrupt.h>

avr_cpp_lib::LCDS lcd(avr_cpp_lib::OutputPin(&DDRD, &PORTD, PD3),
                      avr_cpp_lib::OutputPin(&DDRD, &PORTD, PD6),
                      avr_cpp_lib::OutputPin(&DDRD, &PORTD, PD7),
                      avr_cpp_lib::OutputPin(&DDRC, &PORTC, PC0),
                      avr_cpp_lib::OutputPin(&DDRC, &PORTC, PC1),
                      avr_cpp_lib::OutputPin(&DDRC, &PORTC, PC2));

void uartCommand(uint8_t c) {
	for (int8_t i = 8; i > 0; i--) {
		if (BITSET(c, i-1)) {
			SETBIT(PORTB, PB6);
		} else {
			CLEARBIT(PORTB, PB6);
		}
		__builtin_avr_delay_cycles(240);
		SETBIT(PORTB, PB7);
		__builtin_avr_delay_cycles(240);
		CLEARBIT(PORTB, PB7);
		__builtin_avr_delay_cycles(240);
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
	
	// nastavitev timer-ja za servo
	// ctc mode, clk/64
	TCCR0 = BIT(CS01) | BIT(CS00);
	// pwm value
	OCR0 = 128;
	// both interrupts on
	SETBIT(TIMSK, OCIE0);
	SETBIT(TIMSK, TOIE0);

	// gumbi
	SETBITS(PORTC, BIT(PC3) | BIT(PC4) | BIT(PC5) | BIT(PC6) | BIT(PC7));

	// lucke
	SETBITS(DDRB, BIT(PB0) | BIT(PB1) | BIT(PB2) | BIT(PB3) | BIT(PB4));
	
	// adc
	ADMUX = 0b01100000;
	ADCSRA = 0b10010110;
	
	// vklopi interrupte
	sei();
	
	pisk(1000);
	pavza(100);
	stopPisk();
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

uint8_t preberiADC(uint8_t adc) {
	// adc
	adc = (ADMUX & 0b11100000) | (adc & 0b00000111);
	ADMUX = adc;
	SETBIT(ADCSRA, ADSC);
	while (BITCLEAR(ADCSRA, ADIF));
	SETBIT(ADCSRA, ADIF);
	return ADCH;
}

static volatile uint8_t timer0Count = 10;
static volatile uint8_t servoSetRound = 10;
static volatile uint8_t servoPort = 0;

ISR(TIMER0_COMP_vect) {
	if (timer0Count == servoSetRound) {
		CLEARBITS(PORTA, servoPort);
	}
}

ISR(TIMER0_OVF_vect) {
	timer0Count--;
	if (timer0Count == 0) {
		timer0Count = 10;
		SETBITS(PORTA, servoPort);
	}
}

void nastaviServo(const uint8_t port) {
	CLEARBITS(DDRA, servoPort);
	CLEARBITS(PORTA, servoPort);
	servoPort = BIT(port);
	SETBITS(DDRA, servoPort);
}

void lokacijaServo(uint8_t l) {
	if (l > 240) {
		l = 240;
	}
	if (l < 189) {
		OCR0 = l+67;
		servoSetRound = 10;
	} else {
		OCR0 = l - 189;
		servoSetRound = 9;
	}
}

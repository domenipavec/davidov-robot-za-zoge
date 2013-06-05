#include "bitop.h"
#include <stdint.h>
#define F_CPU 8000000UL  // 8 MHz
    
#include <avr/io.h>

void uartCommand(uint8_t c);

void motor0naprej(uint16_t d);
void motor0nazaj(uint16_t d);
void motor0bremza();
void motor0stop();
void motor0hitrost(uint16_t h);
void motor0moc(uint16_t m);

void pavza(uint16_t i);
void pocakajMotor();
void motor1naprej(uint16_t d);
void motor1nazaj(uint16_t d);
void motor1bremza();
void motor1stop();
void motor1hitrost(uint16_t h);
void motor1moc(uint16_t m);

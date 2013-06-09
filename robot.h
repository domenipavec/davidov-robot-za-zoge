#include "bitop.h"
#include <stdint.h>
#define F_CPU 8000000UL  // 8 MHz
    
#include <avr/io.h>

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

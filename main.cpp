#include "robot.h"

const uint8_t MEJA = 100;

uint8_t postaja = 0;
uint8_t nacin = 0;

int main() {
	pripravi();

	nastaviServo(ADC0);

	lokacijaServo(0);

	//osvetliZaslon(255);

	motorNastavi(MOTOR_0_MOC | MOTOR_1_MOC, 500);
	motorPremik(MOTOR_0_NAZAJ | MOTOR_1_NAPREJ);
    
    luc0prizgi();
    luc2prizgi();
    
    uint16_t utripanje = 0;

	for(;;) {
		uint8_t leviSenzor = preberiADC(ADC7);
		uint8_t desniSenzor = preberiADC(ADC6);
		
		if (leviSenzor > MEJA) {
			if (desniSenzor > MEJA) {
				if (nacin != 0) {
					motorPremik(MOTOR_0_NAZAJ | MOTOR_1_NAPREJ);
					pavza(10);
					nacin = 0;
				}
			} else {
				if (nacin != 1) {
					motorPremik(MOTOR_0_STOP | MOTOR_1_NAPREJ);
					pavza(10);
					nacin = 1;
				}
			}
		} else {
			if (desniSenzor > MEJA) {
				if (nacin != 2) {
					motorPremik(MOTOR_0_NAZAJ | MOTOR_1_STOP);
					pavza(10);
					nacin = 2;
				}
			} else {
				motorPremik(MOTOR_0_STOP | MOTOR_1_STOP);
				if (postaja == 0) {
					pavza(5000);
					postaja = 1;
				} else if (postaja == 1) {
					pavza(1000);
					lokacijaServo(130);
					pavza(1000);
					lokacijaServo(0);
					pavza(1000);
					postaja = 0;
				}
				motorPremik(MOTOR_0_NAZAJ | MOTOR_1_NAPREJ);
				nacin = 0;
				pavza(200);
			}
		}
		
		pavza(1);
        
        if (GUMB2) {
            pisk(1000);
            if (postaja == 1) {
                postaja = 0;
            } else {
                postaja = 1;
            }
            pavza(10);
            while (GUMB2);
            stopPisk();
        }
        
        utripanje++;
        if (utripanje == 400) {
            luc1prizgi();
            luc2ugasni();
        }
        if (utripanje == 800) {
            utripanje = 0;
            luc1ugasni();
            luc2prizgi();
        }
		
		//LCD_DOMOV();
		//LCD_STEVILKA(leviSenzor, 3);
		//LCD_TEKST("  ");
		//LCD_STEVILKA(desniSenzor, 3);
		//pavza(250);
	}
}

#include <MKL25Z4.h>                    // Device header
#include <stdio.h>
#include <math.h>
#define DEFAULT_SYSTEM_CLOCK 20971520u  // System clock rate 
#define servo_mod 3268
#define motor_mod 167

void PWM_init(void);
int Cnv_calculator(float duty, int mod);
void Servo_drive(int servo_no, int angle);
void Pwm_servo(int servo_no, int duty);
void Delay(volatile unsigned int time_del);
void ADC0_init(void);
int ADC_getresults(int QQQ);

void STANDING(void);
void MOVING_FORWARD(void);
void TURNING_RIGHT(void);
void TURNING_LEFT(void);
void SLEEP(void);

const static int SERVOLIST[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179}; 
	 

int main(void){

int adcres1,adcres2,adcres3,adcres4,yon1,yon2;
PWM_init();
ADC0_init();	
STANDING();

while(1) {
adcres1=ADC_getresults(0);
adcres2=ADC_getresults(3);
yon1=round(adcres1/22.755555);
yon2=round(adcres1/22.755555);

if (adcres1 >= 3750){	SLEEP();}
else if (adcres1 <= 0400){	MOVING_FORWARD();}
else if (adcres2 >= 3750){	TURNING_RIGHT();}
else if (adcres2 <= 0400){	TURNING_LEFT();}
		
}

//	Delay(3000000);
	
//	Servo_drive(01, 60);
//	Servo_drive(01, 110);
//	Servo_drive(01, 90);

//	Delay(3000000);
//	
//// STANDING();
//	
//	TURNING_RIGHT();
	
//	Servo_drive(01, 140);
//	Servo_drive(02, 90);
//	Servo_drive(03, 140);
//	Servo_drive(11, 40);
//	Servo_drive(12, 90);
//	Servo_drive(13, 40);
//	Servo_drive(21, 140);
//	Servo_drive(22, 90);
//	Servo_drive(23, 140);
//	Servo_drive(31, 40);
//	Servo_drive(32, 90);
//	Servo_drive(33, 40);
while(1){	
	
}	
}

void PWM_init(void){

	SIM->SCGC5 |= 0x2000 | 0x800 | 0x1000 | 0x0200 ;  // Enable clock to Port A, E, D, and C

//  PORTA->PCR[03] = 0x0300;                          // Configuring PTA-03 Mux (TPM0-CH0)
//  PORTA->PCR[01] = 0x0300;                          // Configuring PTA-01 Mux (TPM0-CH0)	
//  PORTC->PCR[01] = 0x0400;                          // Configuring PTC-01 Mux (TPM0-CH0)	
//  PORTD->PCR[00] = 0x0400;                          // Configuring PTD-00 Mux (TPM0-CH0)
//	
//  PORTE->PCR[25] = 0x0300;                          // Configuring PTE-25 Mux (TPM0-CH1)
//  PORTA->PCR[04] = 0x0300;                          // Configuring PTA-04 Mux (TPM0-CH1)	
//  PORTC->PCR[02] = 0x0400;                          // Configuring PTC-02 Mux (TPM0-CH1)	
//  PORTD->PCR[01] = 0x0400;                          // Configuring PTD-01 Mux (TPM0-CH1)

//	PORTE->PCR[29] = 0x0300;                          // Configuring PTE-29 Mux (TPM0-CH2)
//  PORTA->PCR[05] = 0x0300;                          // Configuring PTA-05 Mux (TPM0-CH2)	
//  PORTC->PCR[03] = 0x0400;                          // Configuring PTC-03 Mux (TPM0-CH2)	
//  PORTD->PCR[02] = 0x0400;                          // Configuring PTD-02 Mux (TPM0-CH2)

	
	SIM->SCGC6 |= 0x01000000;                         // Enable clock to TPM0
	SIM->SOPT2 |= 0x01000000;                         // Clock source selection
	TPM0->SC = 0;                                     // Disable timer

	TPM0->CONTROLS[0].CnSC = 0x20 | 0x08;             // Center-aligned, non inverted
	TPM0->CONTROLS[1].CnSC = 0x20 | 0x08;             // Center-aligned, non inverted
	TPM0->CONTROLS[2].CnSC = 0x20 | 0x08;							// Center-aligned, non inverted
	TPM0->CONTROLS[3].CnSC = 0x20 | 0x08;							// Center-aligned, non inverted
	TPM0->CONTROLS[4].CnSC = 0x20 | 0x08;							// Center-aligned, non inverted
	
	
                                                      // Initialize the servos
//	Servo_drive(1, 2);                                // Bottom
//	Servo_drive(2, 0);                                // Knee
//	Servo_drive(3, 0);                                // Ankle
//	Servo_drive(4, 0);                                // Claw

}
  
void Pwm_servo(int servo_no, int cnv){
	TPM0->MOD = 0x0CCC;                             // Write the MOD value 1638 to TPM0
	
	if(servo_no== 01 ){TPM0->CONTROLS[4].CnV = cnv;}
	if(servo_no== 02 || 03 ){TPM0->CONTROLS[0].CnV = cnv;}      // Writes the CnV values to the channels
	if(servo_no== 11 || 12 || 13 ){TPM0->CONTROLS[1].CnV = cnv;}
	if(servo_no== 21 || 22 || 23 ){TPM0->CONTROLS[2].CnV = cnv;}
	if(servo_no== 31 || 32 || 33 ){TPM0->CONTROLS[3].CnV = cnv;}
	
	TPM0->SC = 0xF;                                    // Start the timer
}    
	
int Cnv_calculator(float duty, int mod){
	int cnv;
	cnv = (duty*(mod))/100.0;                         // Calculate the CnV given the duty cycle and MOD
	return cnv;
}

void Servo_drive(int servo_no, int data){
	float duty = 0.0;
	int cnv = 0, angle;
		switch(servo_no){
			
			case 01:
					PORTC->PCR[8] = 0x0300;
					angle = SERVOLIST[data]; 									// Get the angle from the lookup table
//					PORTE->PCR[31] = 0x0000;
					break;
			
			case 02:                                 
					PORTC->PCR[01] = 0x0400;
					angle = SERVOLIST[data]; 									// Get the angle from the lookup table
//					PORTA->PCR[01] = 0x0000;
					break;

			case 03:                                 
					PORTD->PCR[00] = 0x0400;
					angle = SERVOLIST[data]; 									// Get the angle from the lookup table
//					PORTC->PCR[01] = 0x0000;
					break;

			case 11:                                 
					PORTA->PCR[04] = 0x0300;
					angle = SERVOLIST[data]; 									// Get the angle from the lookup table
//					PORTD->PCR[00] = 0x0000;
					break;

			case 12:                                  
					PORTC->PCR[02] = 0x0400;
					angle = SERVOLIST[data]; 									// Get the angle from the lookup table
//					PORTE->PCR[25] = 0x0000;
					break;

			case 13:                                  
					PORTD->PCR[01] = 0x0400;
					angle = SERVOLIST[data]; 									// Get the angle from the lookup table
//					PORTA->PCR[04] = 0x0000;
					break;
			
			case 21:                                  
					PORTA->PCR[05] = 0x0300;
					angle = SERVOLIST[data]; 									// Get the angle from the lookup table
//					PORTC->PCR[02] = 0x0000;
					break;

			case 22:                                  
					PORTC->PCR[03] = 0x0400;
					angle = SERVOLIST[data]; 									// Get the angle from the lookup table
//					PORTD->PCR[01] = 0x0000;
					break;

			case 23:                                  
					PORTD->PCR[02] = 0x0400;
					angle = SERVOLIST[data]; 									// Get the angle from the lookup table
//					PORTE->PCR[29] = 0x0000;
					break;

			case 31:                                  
					PORTE->PCR[30] = 0x0300;
					angle = SERVOLIST[data]; 									// Get the angle from the lookup table
//					PORTA->PCR[05] = 0x0000;
					break;
			
			case 32:                                  
					PORTC->PCR[04] = 0x0400;
					angle = SERVOLIST[data]; 									// Get the angle from the lookup table
//					PORTD->PCR[02] = 0x0000;
					break;

			case 33:                                  
					PORTD->PCR[03] = 0x0400;
					angle = SERVOLIST[data]; 									// Get the angle from the lookup table
//					PORTD->PCR[02] = 0x0000;
					break;
		} 
	duty = (10.0*angle / 180 ) + 2.5 ;                     // Normalize angle to duty cycle
	cnv = Cnv_calculator(duty, servo_mod);             // Maps duty to CnV
	Pwm_servo(servo_no,cnv);                           // Sends the PWM signal to servos

		Delay(500000);

		PORTC->PCR[8] = 0x0000;
		PORTC->PCR[01] = 0x0000;
		PORTD->PCR[00] = 0x0000;
		PORTA->PCR[04] = 0x0000;
		PORTC->PCR[02] = 0x0000;
		PORTD->PCR[01] = 0x0000;
		PORTA->PCR[05] = 0x0000;
		PORTC->PCR[03] = 0x0000;
		PORTD->PCR[02] = 0x0000;
		PORTE->PCR[30] = 0x0000;
		PORTC->PCR[04] = 0x0000;
		PORTD->PCR[03] = 0x0000;
}

void STANDING(void){

Delay(2000000);
	
	Servo_drive(01, 90);
	Servo_drive(02, 90);
	Servo_drive(03, 90);
	
	Servo_drive(11, 90);
	Servo_drive(12, 90);
	Servo_drive(13, 90);
	
	Servo_drive(21, 90);
	Servo_drive(22, 90);
	Servo_drive(23, 90);
	
	Servo_drive(31, 90);
	Servo_drive(32, 90);
	Servo_drive(33, 90);
}
void ADC0_init(void)
{
SIM->SCGC5 |= 0x2000; /* clock to PORTE */
SIM->SCGC5 |= 0x400;  /* clock to PORTE */
PORTE->PCR[20] = 0;   /* PTE20 analog input */
PORTE->PCR[22] = 0;
PORTB->PCR[1] = 0;
PORTB->PCR[0] = 0;
SIM->SCGC6 |= 0x8000000; /* clock to ADC0 */
ADC0->SC2 &= ~0x40; /* software trigger */
/* clock div by 4, long sample time, single ended 12 bit, bus clock */
ADC0->CFG1 = 0x40 | 0x10 | 0x04 | 0x00;
}

void MOVING_FORWARD(void) {
	Servo_drive(13, 40);
	Servo_drive(11, 40);
	Servo_drive(12, 90);
	Servo_drive(11, 90);
	Servo_drive(12, 90);
	Servo_drive(13, 90);
	
	Servo_drive(33, 40);
	Servo_drive(31, 140);
	Servo_drive(32, 90);
	Servo_drive(31, 90);
	Servo_drive(32, 90);
	Servo_drive(33, 90);
	
	Servo_drive(03, 140);
	Servo_drive(01, 40);
	Servo_drive(02, 90);
	Servo_drive(01, 90);
	Servo_drive(02, 90);
	Servo_drive(03, 90);
	
	Servo_drive(23, 140);
	Servo_drive(21, 140);
	Servo_drive(22, 90);
	Servo_drive(21, 90);
	Servo_drive(22, 90);
	Servo_drive(23, 90);
	
////////////////////////////	
}
void TURNING_RIGHT(void) {
		
	
	Servo_drive(13, 45);
	Servo_drive(11, 45);
	Servo_drive(13, 90);
	
	Servo_drive(33, 45);
	Servo_drive(31, 45);
	Servo_drive(33, 90);
	
	Servo_drive(03, 135);
	Servo_drive(01, 45);
	Servo_drive(03, 90);
	
	Servo_drive(23, 135);
	Servo_drive(21, 45);
	Servo_drive(23, 90);	
	
	Servo_drive(11, 90);
	Servo_drive(31, 90);
	Servo_drive(01, 90);
	Servo_drive(21, 90);	
}
void TURNING_LEFT(void){


	Servo_drive(23, 135);
	Servo_drive(21, 135);
	Servo_drive(23, 90);	

	Servo_drive(03, 135);
	Servo_drive(01, 135);
	Servo_drive(03, 90);

	Servo_drive(33, 45);
	Servo_drive(31, 135);
	Servo_drive(33, 90);
	
	Servo_drive(13, 45);
	Servo_drive(11, 135);
	Servo_drive(13, 90);

	Servo_drive(11, 90);
	Servo_drive(31, 90);
	Servo_drive(01, 90);
	Servo_drive(21, 90);	
	
	
}

void SLEEP(void) {
		
	
	Servo_drive(01, 135);
	Servo_drive(11, 45);
	Servo_drive(21, 135);
	Servo_drive(31, 45);
	
	Servo_drive(02, 90);
	Servo_drive(12, 90);
	Servo_drive(22, 90);
	Servo_drive(32, 90);
	
	Servo_drive(03, 150);
	Servo_drive(13, 35);
	Servo_drive(23, 150);
	Servo_drive(33, 35);	

}


int ADC_getresults(int QQQ){
	int result=0;
	ADC0->SC1[0] = QQQ; /* start conversion on channel 0 */
	while(!(ADC0->SC1[0] & 0x80)) { } /* wait for conversion complete */
	result = ADC0->R[0]; /* read conversion result and clear COCO flag */
	return result;
}

void Delay(volatile unsigned int time_del) {
  while (time_del--) 
		{
  }
}

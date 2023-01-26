#include "msp.h"
 int colour = 0;

void TA0_N_IRQHandler(void) {
	
	//clear interrupt flag
	TA0CTL &= (uint16_t)(~BIT0);
	
	// Toggle LED
	P1OUT ^=(uint8_t)(1<<0);
}

void TA1_N_IRQHandler(void) {
	
	//clear interrupt flag
	TA1CTL &= (uint16_t)(~BIT0);
	
	// Change colour
	P2OUT = colour;
	colour = (colour + 1)% 8;
}

void TA1_0_IRQHandler(void) {
	
	//clear interrupt flag
	TA1CCTL0 &= (uint16_t)(~BIT0);
	
	// Change colour
	P2OUT = colour;
	colour = (colour + 1)% 8;
}

int main()
{
	//Disable watchdog timer
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
	
	//Configure pins as GPIO
	P1SEL0 &= (uint8_t) ~(1<<0);
	P1SEL1 &= (uint8_t) ~(1<<0);
	
	P2SEL0 &= (uint8_t) (~((1<<2) | (1<<1) | (1<<0)));
	P2SEL1 &= (uint8_t) (~((1<<2) | (1<<1) | (1<<0)));
	
	// Configure LED pins as output
	P1DIR |=(uint8_t)(1<<0);
	P2DIR |=(uint8_t)(((1<<2) | (1<<1) | (1<<0)));
	
	//Configure default state of LED
	P1OUT &=~(uint8_t)(1<<0);
	P2OUT &=~(uint8_t)(((1<<2) | (1<<1) | (1<<0)));
	
	// Configure TimerA0
	TA0CTL &= (uint16_t) (~(BIT5 | BIT4));	//stop timer
	TA0CTL &= (uint16_t) (~BIT0);	//clear interrupt flag
	TA0CCR0 = (uint16_t) (32767);	
	TA0CTL |= (uint16_t) (BIT1);	//interrupt enabled
	TA0CTL |= (uint16_t) (BIT4);	//up mode (count to CCR0)
	TA0CTL &= (uint16_t) (~(BIT9));
	TA0CTL |= (uint16_t) (BIT8);
	TA0R = (uint16_t) (32767);	
	
	// Configure TimerA1
	TA1CTL &= (uint16_t) (~(BIT5 | BIT4));	//stop timer
	TA1CTL &= (uint16_t) (~BIT0);	//clear interrupt flag
	TA1CCR0 = (uint16_t) (16383);	
	TA1CTL |= (uint16_t) (BIT1);	//interrupt enabled
	TA1CTL |= (uint16_t) ((BIT5) | (BIT4));	//up down mode
	TA1CTL &= (uint16_t) (~(BIT9));
	TA1CTL |= (uint16_t) (BIT8);
	TA1CCTL0 |= (uint16_t) (BIT4);
	TA1R = (uint16_t) (13108);	
	
	//Configure NVIC
	NVIC_SetPriority(TA0_N_IRQn, 2);
	NVIC_SetPriority(TA1_N_IRQn, 2);
	NVIC_SetPriority(TA1_0_IRQn, 2);
	NVIC_EnableIRQ(TA0_0_IRQn);
	NVIC_EnableIRQ(TA0_N_IRQn);
	NVIC_EnableIRQ(TA1_N_IRQn);
	
	// Globally enable interrupts in CPU
	__ASM("CPSIE I");
	
	while(1){}
	return 0;
}
	
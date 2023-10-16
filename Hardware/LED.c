#include "stm32f10x.h"                  // Device header
void LED_init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIOses;
	GPIOses.GPIO_Mode= GPIO_Mode_Out_PP;
	GPIOses.GPIO_Pin=GPIO_Pin_1 | GPIO_Pin_2;
	GPIOses.GPIO_Speed=GPIO_Speed_50MHz;  
	
	GPIO_Init(GPIOA,&GPIOses);
	
	GPIO_WriteBit(GPIOA,GPIO_Pin_1 | GPIO_Pin_2,(BitAction)1);
}

void LED1_ON(void){
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)0);
}

void LED1_OFF(void){
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,(BitAction)1);
}

void LED2_ON(void){
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)0);
}

void LED2_OFF(void){
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,(BitAction)1);
}

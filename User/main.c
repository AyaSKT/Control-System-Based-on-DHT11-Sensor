#include "stm32f10x.h"                  // Device header
#include "Delay.h"                      // Delay header
#include "Key.h"
#include "dht11.h"
#include "OLED.h"

extern unsigned int rec_data[4];
//A11 FAN
//B7 pump
void FAN_SWITCH(int a){
	if(a)GPIO_WriteBit(GPIOA,GPIO_Pin_6,(BitAction)1);
	else GPIO_WriteBit(GPIOA,GPIO_Pin_6,(BitAction)0);
}	
void PUMP_SWITCH(int a){
	if(a)GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)1);
	else GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)0);
}
int main(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIOses;

	
	GPIOses.GPIO_Mode= GPIO_Mode_Out_PP;
	GPIOses.GPIO_Pin=GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_4;
	GPIOses.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOses);
	
	GPIO_WriteBit(GPIOA,GPIO_Pin_7 | GPIO_Pin_6,(BitAction)0);//fan
	GPIO_WriteBit(GPIOA,GPIO_Pin_5 | GPIO_Pin_4,(BitAction)0);
	
	
	char fan_on[]="FAN ON";
	char off[]="OFF";
	char device_on[]="PUMP ON";
	OLED_Init(); 
	
	while(1){
		OLED_Clear();
		
		FAN_SWITCH(0);
		PUMP_SWITCH(0);
		DHT11_REC_Data();
		
		OLED_ShowString(1,1,"DHT11 sensor:");
		OLED_ShowString(2,1,"H:");
		OLED_ShowNum(2,3,rec_data[0],2);
		OLED_ShowString(2,5,"%");
		OLED_ShowString(3,1,"T:");
		OLED_ShowNum(3,3,rec_data[2],2);		
		OLED_ShowString(3,5, "^C");
		OLED_ShowString(4,1,"MODE:");
		
		if(rec_data[0]<=50	){
			OLED_ShowString(4,6,device_on);
			PUMP_SWITCH(1);
			
		}else if(rec_data[0]>=80){
			OLED_ShowString(4,6,fan_on);
			FAN_SWITCH(1);
		}else{
			OLED_ShowString(4,6,off);
			FAN_SWITCH(0);
			PUMP_SWITCH(0);
		}
		
		Delay_s(1);
	}
	
	
}

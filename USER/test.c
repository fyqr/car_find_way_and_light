#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "lcd.h"
#include "usmart.h"		
#include "hc05.h" 	 
#include "usart3.h" 	
#include "key.h" 	 
#include "string.h"	 
#include "motor.h"
#include "adc.h"
//ALIENTEK̽����STM32F407��������չʵ��1
//ATK-HC05��������ģ��ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 
 
extern u32 global_time_cnt;
extern u8 USART3_RX_BYTE;

	int ii=0;
	u8 last_state = 0xff;
	u8 la2_state = 0xff;
	u8 out = 0;
	u8 fudu =30;
	u8 fudu2 =0;
	u16 you;
	u16 zuo;
	u8 state=0;	
	
	

	void xunguang()
	{
		adc4=Get_Adc_Average(4,20);//adc4���ұߵĴ�����
		adc5=Get_Adc_Average(5,20);//adc5����ߵĴ�����
		
		
		if(adc4<=0x400||adc5<=0x400)
		{
      car_stop();
      continue;
		}
		else if(adc4>=0xdd0 && adc5>=0xdd0)
		{
			car_right();
		}
		else if(adc4>adc5&&adc4-adc5<0x08f||adc5>adc4&&adc5-adc4<0x8f)
		{
			 car_forward();
			delay_ms(100);
		}
		
      else if(adc4<adc5)//�ұ���,��߰�
		{
        car_right();
		}
      else     //��������ұ߰�
		{ 
        car_left();
			
			
		}
	}

	
	
 void xunji()
 {
		switch(KEY1<<2 | KEY0<<1 | KEY2)
		{
			case 5: car_forward(); last_state = 5; break;//101
			case 4: car_right_s(200); last_state = 4; break;//100
			case 6: car_right_s(150); last_state = 6; break;//110
			case 1: car_left_s(200); last_state = 1; break;//001
			case 3: car_left_s(150); last_state = 3; break;//011
			case 7: {
				out++;
				switch(last_state){
					case 4: 
					case 6: if(out>outfudu)
									{
										car_right_back();
										chixu++;
										if(chixu>chixufudu)
										{
											out=0;
											chixu=0;
										}
									}
									else car_right_s(250);break; 
					case 1:
					case 3: if(out>outfudu)
									{
										car_left_back();chixu++;
										if(chixu>chixufudu)
										{
											out=0;
											chixu=0;
										}
									}
									else car_left_s(250);break;
					default: break;
						
				}
			}
//			case 0: car_stop(); break;
			default: break;
		}
	}

u8 KEY_State(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up)//&&(WK_UP==1)
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(WK_UP==1)return 1;
	}else if(WK_UP==0)key_up=1; 	    
 	return 0;// �ް�������
}
	
int main(void)
{	 


	Stm32_Clock_Init(336,8,2,7);//����ʱ��,168Mhz 
	delay_init(168);			//��ʱ��ʼ��  
	uart_init(84,115200);		//��ʼ�����ڲ�����Ϊ115200 
	usmart_dev.init(84); 		//��ʼ��USMART		
	KEY_Init();					//��ʼ������
	LCD_Init();		 			//��ʼ��LCD
	usmart_dev.init(72); 		//��ʼ��USMART 	  
	POINT_COLOR=RED;
	delay_ms(1000);			//�ȴ�����ģ���ϵ��ȶ�
	
	
	
	if(HC05_Init()) 		//��ʼ��ATK-HC05ģ��  
	{
		LCD_ShowString(30,90,200,16,16,"ATK-HC05 Error!"); 
		delay_ms(500);
		LCD_ShowString(30,90,200,16,16,"Please Check!!!"); 
		delay_ms(100);
	}
	
	POINT_COLOR=BLUE;
	delay_ms(100);
	pwm_init();
	delay_ms(100);
	
	//TODO����
	//WK_UP==1;
//	while(1)
//	{
//		if(WK_UP==0)car_right();����
//	}
	


	
	while(1)
	{
/*		fudu2++;
			if(fudu2>1000)
			{
				if(KEY_State(1)==0)state=1-state;
				fudu2=0;
			}
*/
			if(WK_UP==0)state=1-state;
			while(WK_UP==0);
			if(state==0)xunji();
			else xunguang();
	}

	while(1) 
	{				
		switch(USART3_RX_BYTE)
		{
			//up, forward
			case 'w': car_forward(); break;
			//down, backward
			case 's': car_backward(); break;
			//left, turn left
			case 'a': car_left(); break;
			//right, turn right
			case 'd': car_right(); break;
			//default mode
			case 't': car_stop(); break;
			default: break;
		}
	}											    
}

















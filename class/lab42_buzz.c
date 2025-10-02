//
// GPIO_7seg_keypad : 3x3 keypad inpt and display on 7-segment LEDs
//
#include <stdio.h>
#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "Seven_Segment.h"
#include "Scankey.h"

int flag=0;
//buzz
void Buzz_Do(int number)
{
	int i;
	for (i=0; i<number; i++) {
      PB11=0; // PB11 = 0 to turn on Buzzer
	  CLK_SysTickDelay(100000);	 // Delay 
	  PB11=1; // PB11 = 1 to turn off Buzzer	
	  CLK_SysTickDelay(100000);	 // Delay 
	}
}

void Buzz_Re(int number)
{
	int i;
	for (i=0; i<number; i++) {
      PB11=0; // PB11 = 0 to turn on Buzzer
	  CLK_SysTickDelay(100000);	 // Delay 
	  PB11=1; // PB11 = 1 to turn off Buzzer	
	  CLK_SysTickDelay(100000);	 // Delay 
	}
}

void Buzz_Mi(int number)
{
	int i;
	for (i=0; i<number; i++) {
      PB11=0; // PB11 = 0 to turn on Buzzer
	  CLK_SysTickDelay(100000);	 // Delay 
	  PB11=1; // PB11 = 1 to turn off Buzzer	
	  CLK_SysTickDelay(100000);	 // Delay 
	}
}
void clean_7seg(void){
    CloseSevenSegment();
    value[0] = value[1] = value[2] = 0;
}

void shift_right(int value[3]) {
	//int keyin = value[0];
	value[0] = value[1];
	value[1] = value[2];
	//value[2] = temp;

    show_7seg_right(int value[2],int value[1],int value[0]);
}




void show_7seg_right(int PC6_v, int PC5_v, int PC4_v){
    CloseSevenSegment();
		if(PC6_v != 0)
			ShowSevenSegment(2,PC6_v);//value
		CLK_SysTickDelay(5000);
	
	
		CloseSevenSegment();
		if(PC5_v != 0)
			ShowSevenSegment(1,PC5_v);//value
		CLK_SysTickDelay(5000);
	
	
		CloseSevenSegment();
		if(PC4_v != 0)
			ShowSevenSegment(0,PC4_v);//value
		CLK_SysTickDelay(5000);
}

void shift_left(int value[4], uint16_t keyin) {
	value[3] = value[2];
	value[2] = value[1];
	value[1] = value[0];
	value[0] = keyin;
}
//==========================

int main(void)
{
	uint16_t keyin;
	int value[4] = {0, 0, 0, 0};
	
	
	SYS_Init();
	OpenSevenSegment();
	OpenKeyPad();
	
	//show_7seg(1,1,1,1);
	
	while (1) {
		keyin = ScanKey();
		if (keyin != 0) {
			if (keyin != 5 && flag != 5) {
				
				// main
				if (keyin < 4) shift_left(value, keyin);
				if (keyin == 6) clean_7seg();
				if (keyin == 7) shift_right(value);
				//if (keyin == 9) shift_left2(value, keyin);
			}
		    else {
                flag = 5;
                if (flag == 1) flag = 0;
            }
		}
		
		
		
		show_7seg(value[3],value[2],value[1],value[0]);
    }
}




/*

// display an integer on four 7-segment LEDs
void show_7seg(int PC7_v, int PC6_v, int PC5_v, int PC4_v)
{
		
	
		
		CloseSevenSegment();
		if(PC7_v != 0)
			ShowSevenSegment(3,PC7_v);//value
		CLK_SysTickDelay(5000);
	
	
  
		CloseSevenSegment();
		if(PC6_v != 0)
			ShowSevenSegment(2,PC6_v);//value
		CLK_SysTickDelay(5000);
	
	
		CloseSevenSegment();
		if(PC5_v != 0)
			ShowSevenSegment(1,PC5_v);//value
		CLK_SysTickDelay(5000);
	
	
		CloseSevenSegment();
		if(PC4_v != 0)
			ShowSevenSegment(0,PC4_v);//value
		CLK_SysTickDelay(5000);
	
}

void shift_left(int value[4], uint16_t keyin) {
	value[3] = value[2];
	value[2] = value[1];
	value[1] = value[0];
	value[0] = keyin;
}
void shift_left1(int value[4], uint16_t keyin) {
	int temp = value[3];
	value[3] = value[2];
	value[2] = value[1];
	value[1] = value[0];
	value[0] = temp;
}
void shift_left2(int value[4], uint16_t keyin) {
	int temp = value[0];
	value[0] = value[1];
	value[1] = value[2];
	value[2] = value[3];
	value[3] = temp;
}
void shift_remove(int value[4], uint16_t keyin) {
	value[0] = value[1] = value[1] = value[2] = 0;//�M��
	//CloseSevenSegment();
}

	



int main(void)
{
	uint16_t keyin;
	int value[4] = {0, 0, 0, 0};
	int flag=0;
	
	SYS_Init();
	OpenSevenSegment();
	OpenKeyPad();
	
	//show_7seg(1,1,1,1);
	
	while (1) {
		keyin = ScanKey();
	/*	
		switch (keyin){
			case 0:
				if (flag== 1)
					flag = 0;
				break;
			case 7:
				if (flag== 0) {
					shift_left1(value, keyin);
					flag = 1;
				}
				break;
			case 8:
				value[0] = value[1] = value[1] = value[2] = 0;
				break;
			case 9:
				shift_left2(value, keyin);
				break;
			default:
				if(keyin<7){
					if (flag== 0) {
					shift_left(value, keyin);
					flag = 1;
					}
					break;
					
				}
			}
		****
		
		if (keyin != 0) {
			if (flag == 0) {
				
				// main
				if (keyin < 7) shift_left(value, keyin);
				if (keyin == 7) shift_left1(value, keyin);
				if (keyin == 8) value[0] = value[1] = value[1] = value[2] = 0;
				if (keyin == 9) shift_left2(value, keyin);
				
				
				flag = 1;
			}
		} else {
			if (flag == 1) flag = 0;
		}
		
		
		
		show_7seg(value[3],value[2],value[1],value[0]);
    }
}
*/

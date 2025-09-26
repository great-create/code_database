//lab32
// LCD_led_lcd_keypad
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "LCD.h"
#include "Seven_Segment.h"
#include "Scankey.h"

int password_dis = 0;
int count_input = 0;//input :4 bits
int rand_array[4];
int input_array[4];

void show_7seg(int PC7_v, int PC6_v, int PC5_v, int PC4_v)
{
	ShowSevenSegment(3,PC7_v);	
	ShowSevenSegment(2,PC6_v);
	ShowSevenSegment(1,PC5_v);
	ShowSevenSegment(0,PC4_v);	
}
void showled(void){
    int i;
    for(i=0;i<2;i++){
			PC12 =0; PC13 =0; PC14 =0; PC15 =0; // turn off LED
			CLK_SysTickDelay(300000);	 // 0.3Delay 	
		
			PC12 =1; PC13 =1;PC14 =1; PC15 =1; // turn on LED
			CLK_SysTickDelay(300000);	 // 0.3Delay 
		}
    PC12 =0; PC13 =0; PC14 =0; PC15 =0; // turn off LED
}

void showled_delay(void){
    int i;
    PC12 =0; // turn off LED
	CLK_SysTickDelay(300000);	 // 0.3Delay
	PC12 =1; // turn on LED
	PC13 =0; // turn off LED
	CLK_SysTickDelay(300000);	 // 0.3Delay
	PC13 =1; // turn on LED
	PC14 =0; // turn off LED
	CLK_SysTickDelay(300000);	 // 0.3Delay
	PC14 =1; // turn on LED
	PC15 =0; // turn off LED
	CLK_SysTickDelay(300000);	 // 0.3Delay
	PC15 =1; // turn on LED
    PC12 =0; PC13 =0; PC14 =0; PC15 =0; // turn off LED
}

void clear_input(void){
    clear_LCD();
    for(int i = 0; i < 4; i++) {
        input_array[i] = 0;
    }
}

void check_inputarray_randarray(int password_dis){
    int i;
    int match = 1;//set true
    int input_num = 0;//是否input

    for (i = 0; i < 4; i++) {
        if (input_array[i] != 0) {
            input_num = 1;
            break;
        }
    }

    if(input_num == 0) printS(10*8,password_dis,"NULL");

    
    for (i = 0; i < 4; i++) {//CHECK
        if (input_array[i] != rand_array[i]) {
            match = 0;
            break;
        }
    }

    if(match){
        printS(10*8,password_dis,"PASS");
        showled_delay();
    }
    else{
        printS(10*8,password_dis,"ERROR");
        showled();
    }

}

int main(void)
{
	char Text[16] = "keypad:         ";
	uint16_t keyin;
    int value[4] = {0, 0, 0, 0};
	int i,flag=0;
    

	SYS_Init();
	  
	init_LCD();
	clear_LCD();
	
    GPIO_SetMode(PC, (BIT12|BIT13|BIT14|BIT15), GPIO_MODE_OUTPUT);
	OpenSevenSegment();
	OpenKeyPad();	              // initialize 3x3 keypad
	print_Line(0,"LCD_Keypad"); // print title
	 
	while(1)
	{
	    keyin = ScanKey();
        
        
		if (keyin != 0) {
			if (flag == 0) {
                if(keyin<7 && count_input < 4){
                    input_array[count_input] = keyin;
                    printC(i*8,password_dis,input_array[i]);
                    count_input++;
                }
                
                for (int i = 0; i < 4; i++) {
                    input_array[i] = keyin;
                    printC(i*8,password_dis,input_array[i]);
                }
				if (keyin == 7) {
                    CloseSevenSegment();
                    //srand(time(NULL));
                    srand(TIMER2->TDR); // 設定時間為亂數種子
                    for (int i = 0; i < 4; i++) {
                        rand_array[i] = rand() % 6 + 1;
                    }
                    show_7seg(rand_array[0], rand_array[1], rand_array[2], rand_array[3]);
                }
				if (keyin == 8) {
                    clear_input();
                    password_dis = 0;
                    count_input = 0;
                }
				if (keyin == 9){
                    check_inputarray_randarray(password_dis);
                    password_dis += 16;
                }
				
				flag = 1;
			}
		} else {
			if (flag == 1) flag = 0;
		}


		//sprintf(Text+8,"%d", keyin); // print scankey input to string			  
		//print_Line(1, Text);         // display string on LCD
		//CLK_SysTickDelay(5000); 	   // delay 																	 
	    
    }

}





//====================
//LED
/*
#include <stdio.h>
#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"


void showled(void){
    for(i=0;i<2;i++){
			PC12 =0; PC13 =0; PC14 =0; PC15 =0; // turn off LED
			CLK_SysTickDelay(300000);	 // 0.3Delay 	
		
			PC12 =1; PC13 =1;PC14 =1; PC15 =1; // turn on LED
			CLK_SysTickDelay(300000);	 // 0.3Delay 
		}

]


int main(void)
{
	int i;
    SYS_Init(); 
    GPIO_SetMode(PC, (BIT12|BIT13|BIT14|BIT15), GPIO_MODE_OUTPUT);
	
    while(1) {
        
    }

}
*/

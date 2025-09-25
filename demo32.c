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

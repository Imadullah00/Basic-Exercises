#include<stdio.h>
#include<stdint.h>

  uint32_t* pRCC_AHB1ENR = (uint32_t*) (0x40021000+0x34);

  uint32_t* pGPIOA_MODER = (uint32_t*)  0x50000000;
  uint32_t* pGPIOA_OUTREG = (uint32_t*) 0x50000014;

  uint32_t* pGPIOB_MODER = (uint32_t*) 0x50000400;
  uint32_t* GPIOB_INREG = (uint32_t*) 0x50000410;

void initialize(void);
void mode0(void);
void mode1(void);
void mode2(void);
void mode3(void);
void mode4(void);
void mode5(void);

int main(void)
{
  printf("test\n");

initialize();

volatile uint8_t choice;
volatile uint8_t choice_2; 
volatile uint8_t choice_3; 

while(1)
{
  choice =  *GPIOB_INREG & 0x00000008;
  choice_2 = *GPIOB_INREG & 0x00000001;
  choice_3 = *GPIOB_INREG & 0x00000002;

printf("choice: %d, choice_2: %d, choice_3: %d\n", choice, choice_2, choice_3);

if(choice == 0 && choice_2 == 0 && choice_3 == 0)
{
   mode0();
}

if(choice == 0 && choice_2 == 0 && choice_3 !=0)
{
      mode1();
}

if(choice == 0 && choice_2 != 0 && choice_3 == 0)
{
      mode2();  
}

if(choice == 0 && choice_2 != 0 && choice_3 != 0)
{
      mode3();  
}

if(choice != 0 && choice_2 == 0 && choice_3 == 0)
{ 
      mode4();
}

if(choice != 0 && choice_2 == 0 && choice_3 != 0)
{
      mode5();
}

if(choice != 0 && choice_2 != 0 && choice_3 == 0)
{
      mode4();
      mode3();
}

if(choice != 0 && choice_2 != 0 && choice_3 != 0)
{
      mode4();
      mode5();
}
}
}

void initialize(void)
{
  *pRCC_AHB1ENR = *pRCC_AHB1ENR | 0x00000003;

  *pGPIOA_MODER = *pGPIOA_MODER & 0xFFFC033F;
  *pGPIOA_MODER = *pGPIOA_MODER | 0x00015440;

  *pGPIOB_MODER = *pGPIOB_MODER & 0xFFFFFF30;
}

void mode0(void)    //ON
{
  *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x000001E8;
}

void mode1(void)    //BLINKING
{
  *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x000001E8;
  for(uint32_t i = 0; i<300000; i++) asm("NOP");   //DELAY
  *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFE17;
  for(uint32_t i = 0; i<300000; i++) asm("NOP");   //DELAY
}

void mode2()       //HEARTBEAT
{
  *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x000001E8;
  for(uint32_t i = 0; i<35000; i++) asm("NOP");   //DELAY
  *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFE17;
  for(uint32_t i = 0; i<900000; i++) asm("NOP");   //DELAY
}

void mode3(void)  //CHASE BLINK
{
    /*blinking LED1*/
    *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000020;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY
    *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFFDF;
    for(uint32_t i = 0; i<300000; i++) asm("NOP");   //DELAY

        /*blinking LED2*/
    *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000008;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY
    *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFFF0;
    for(uint32_t i = 0; i<300000; i++) asm("NOP");   //DELAY

     /*blinking LED3*/
    *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000040;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY
    *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFFBF;
    for(uint32_t i = 0; i<300000; i++) asm("NOP");   //DELAY

     /*blinking LED4*/
    *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000080;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY
    *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFF7F;
    for(uint32_t i = 0; i<300000; i++) asm("NOP");   //DELAY

    /*blinking LED5*/
    *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000100;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY
    *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFEFF;
    for(uint32_t i = 0; i<300000; i++) asm("NOP");   //DELAY

     /*blinking LED4*/
    *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000080;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY
    *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFF7F;
    for(uint32_t i = 0; i<300000; i++) asm("NOP");   //DELAY

      /*blinking LED3*/
    *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000040;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY
    *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFFBF;
    for(uint32_t i = 0; i<300000; i++) asm("NOP");   //DELAY

     /*blinking LED2*/
    *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000008;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY
    *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFFF0;
    for(uint32_t i = 0; i<300000; i++) asm("NOP");   //DELAY
  
}

void mode4() // CHASE
{
    /* LED1 ON*/
    *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000020;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY
   
    /*LED2 ON*/
    *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000008;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY
   
    /* LED3 ON*/
    *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000040;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY
  
    /* LED4 ON*/
    *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000080;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY
   
    /* LED5 ON*/
    *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000100;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY
  
    /*LED5 OFF*/
   *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFEFF;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY

    /*LED4 OFF*/
    *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFF7F;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY

    /*LED3 OFF*/
    *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFFBF;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY

    /*LED2 OFF*/
    *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFFF0;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY

    /*LED1 OFF*/
    *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFFDF;
    for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY

    //printf("test2\n");
}

void mode5()  // MERGE CENTRE
{
  /*turn on LED1 & LED5*/
  *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000020;
  *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000100;
  for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY

  /*turn on LED2 & LED4*/
  *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000008;
  *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000080;
  for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY 

 /*turn on LED3*/
  *pGPIOA_OUTREG = *pGPIOA_OUTREG | 0x00000040;
  for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY

  /*turn off LED3*/
  *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFFBF;
  for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY 

  /*turn off LED2 & LED4*/
  *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFFF0;
  *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFF7F;
  for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY 

  /*turn off LED1 & LED5*/
  *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFFDF;
  *pGPIOA_OUTREG = *pGPIOA_OUTREG & 0xFFFFFEFF;
  for(uint32_t i = 0; i<200000; i++) asm("NOP");   //DELAY 
}

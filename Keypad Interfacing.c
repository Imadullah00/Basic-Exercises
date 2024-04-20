#include<stdint.h>
#include<stdio.h>

//port A pin 0,1,2,3-----> O/P	(ROWS)
//port A pin 12,13,14,15--->I/P   (COLUMNS)

void delay()
{
  for(volatile uint16_t i = 0; i<65533; i++) asm("NOP");
}
int main()
{
  printf("check1\n");
volatile uint32_t* ptr_RCC = (uint32_t*)(0x40021034) ; //clock
volatile uint32_t* ptr_GPIOA_reg =  (uint32_t*) 0x50000000;  //gpioA reg
volatile uint32_t* ptr_GPIOA_MODEREG =  (uint32_t*) (0x50000000);// gpioA modereg
volatile uint32_t* ptr_GPIOA_INREG =  (uint32_t*)(0x50000010); // gpioA input reg
volatile uint32_t* ptr_GPIOA_outreg =  (uint32_t*)(0x50000014);// gpioA output reg
volatile uint32_t* ptr_GPIOA_RESIREG =  (uint32_t*)(0x5000000C); // gpioA pullup/down resistors reg

*ptr_RCC = *ptr_RCC | 0x00000001;

*ptr_GPIOA_MODEREG = *ptr_GPIOA_MODEREG & 0xFFFFFF00;
*ptr_GPIOA_MODEREG = *ptr_GPIOA_MODEREG | 0x00000055; //pin 0-3 as o/p
*ptr_GPIOA_MODEREG = *ptr_GPIOA_MODEREG & 0x00FFFFFF;// pin 12-15 as i/p

*ptr_GPIOA_RESIREG = *ptr_GPIOA_RESIREG & 0x00FFFFFF; //resetting all
*ptr_GPIOA_RESIREG = *ptr_GPIOA_RESIREG | 0x55000000;// configuring pullups for pin 12-15

*ptr_GPIOA_outreg = *ptr_GPIOA_outreg  | 0x0000000F; //setting pin 0-3
*ptr_GPIOA_outreg = *ptr_GPIOA_outreg  & 0xFFFFFFFE; //making R1(pin0) LOW

 printf("check2\n");
while(1)
{
 *ptr_GPIOA_outreg = *ptr_GPIOA_outreg  | 0x0000000F; //setting pin 0-3
 *ptr_GPIOA_outreg = *ptr_GPIOA_outreg  & 0xFFFFFFFE; //making R1(pin0) LOW

  if(!(*ptr_GPIOA_INREG & 0x1000))  ////TESTING if C1 LOW
  {
  delay();
  printf("key pressed is 1\n");
  }

   if(!(*ptr_GPIOA_INREG & 0x2000))
  {
    delay();
    printf("key pressed is 2\n");
  }

   if(!(*ptr_GPIOA_INREG & 0x4000))
  {
    delay();
    printf("key pressed is 3\n");
  }

  if(!(*ptr_GPIOA_INREG & 0x8000))
  {
    delay();
    printf("key pressed is A\n");
  }

 *ptr_GPIOA_outreg = *ptr_GPIOA_outreg  | 0x0000000F; //setting pin 0-3
 *ptr_GPIOA_outreg = *ptr_GPIOA_outreg  & 0xFFFFFFFD; //making R2(pin1) LOW

 if(!(*ptr_GPIOA_INREG & 0x00001000))   ////TESTING if C1 LOW
  {
    delay();
    printf("key pressed is 4 \n");
  }

  if(!(*ptr_GPIOA_INREG & 0x00002000))
  {
    delay();
    printf("key pressed is 5 \n");
  }
    
    if(!(*ptr_GPIOA_INREG & 0x00004000))
  {
    delay();
    printf("key pressed is 6 \n");
  }

   if(!(*ptr_GPIOA_INREG & 0x00008000))
  {
    delay();
    printf("key pressed is B \n");
  }

  *ptr_GPIOA_outreg = *ptr_GPIOA_outreg  | 0x0000000F; //setting pin 0-3
 *ptr_GPIOA_outreg = *ptr_GPIOA_outreg  & 0xFFFFFFFB; //making R3(pin2) LOW

 if(!(*ptr_GPIOA_INREG & 0x00001000))   //TESTING if C1 LOW
  {
    delay();
    printf("key pressed is 7 \n");
  }

  if(!(*ptr_GPIOA_INREG & 0x00002000))
  {
    delay();
    printf("key pressed is 8 \n");
  }
    
    if(!(*ptr_GPIOA_INREG & 0x00004000))
  {
    delay();
    printf("key pressed is 9 \n");
  }

   if(!(*ptr_GPIOA_INREG & 0x00008000))
  {
    delay();
    printf("key pressed is C \n");
  }

  *ptr_GPIOA_outreg = *ptr_GPIOA_outreg  | 0x0000000F; //setting pin 0-3
 *ptr_GPIOA_outreg = *ptr_GPIOA_outreg  & 0xFFFFFFF7; //making R3(pin2) LOW
 if(!(*ptr_GPIOA_INREG & 0x00001000))  //TESTING if C1 LOW
  {
    delay();
    printf("key pressed is * \n");
  }

  if(!(*ptr_GPIOA_INREG & 0x00002000))
  {
    delay();
    printf("key pressed is 0 \n");
  }
    
    if(!(*ptr_GPIOA_INREG & 0x00004000))
  {
    delay();
    printf("key pressed is # \n");
  }

   if(!(*ptr_GPIOA_INREG & 0x00008000))
  {
    delay();
    printf("key pressed is D \n");
  }
}
}//main ends

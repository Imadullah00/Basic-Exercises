#include <stdio.h>
#include <stdint.h>

int main()
{
  volatile uint32_t* ptrrcc = (uint32_t*) 0x40021034;  //RCC address + offset of 0x34
  //*ptrrcc = *ptrrcc | 0x00000001;    //enabling GPIOA clock
  *ptrrcc = *ptrrcc | 0x00000003; // enabling GPIOA, GPIOB clock

  volatile uint32_t* ptrmodereg = (uint32_t*) 0x50000000;  //address of GPIOA MODER
  *ptrmodereg = *ptrmodereg & 0xFFFFF3FF;  //RESET BOTH BITS  //bits 10 and 11
  *ptrmodereg = *ptrmodereg  | 0x00000400; //SET 1 BIT  // TO CONFIGURE IN O/P MODE (01)
  uint32_t* ptroutputreg = (uint32_t*) 0x50000014;  //OUTPUT REG ADDRESS


  volatile uint32_t* ptrmoderegB = (uint32_t*) 0x50000400;  //address of GPIOC MODER
  *ptrmoderegB = *ptrmoderegB  & 0xFFFFFFFC;
  volatile uint8_t* ptrinputregB = (uint8_t*) 0x50000410;  //INPUT REG ADDRESS
  // *ptroutputreg = *ptroutputreg | 0x00000020;   //SETTING PA5 TO LIGHT LED

  while (1)
  {

    volatile uint8_t data = *ptrinputregB & 0x01;

    if (data)
    {
      printf("on\n");
      *ptroutputreg = *ptroutputreg | 0x00000020;   //SETTING PA5 TO LIGHT LED
    }

    else
    {
      *ptroutputreg = *ptroutputreg & 0xFFFFFFDF;
      printf(" off\n");
      //RESETTING PA5 TO TURN OFF LED
    }
    //for(uint32_t i = 0; i<300000; i++) asm("NOP");   //DELAY
    //for(uint32_t i = 0; i<300000; i++)  asm("NOP");   //DELAY

  }
  return 0;

}

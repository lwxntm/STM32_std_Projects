
#include "main.h"

#include "Delay.h"
#include "OLED.h"

int main()
{
    OLED_Init();
    char a='A';
    OLED_ShowString(2,1,"Hello, world");

    while(1)
    {
        Delay_ms(100);
        OLED_ShowNum(1,1,a,8);
        a++;
      //  if(OnBoard_Key_GetState())
       //     OnBoard_LED_Toggle();
    }
}

#if 0
//下面是寄存器版本的blink
int main()
{
    RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;
    GPIOC->MODER &=~(0x03<<26);
    GPIOC->MODER |=(0x01<<26);
    GPIOC->OTYPER&=~(0x01<<13);
    GPIOC->OTYPER|= 0x00<<13;
    GPIOC->OSPEEDR&= ~(0x03<<26);
    GPIOC->OSPEEDR|= 0x00<<26;
    GPIOC->PUPDR &=~(0x03<<26);   //上下拉复位
    GPIOC->PUPDR |=0x00<<26;   //不上拉 不下拉
    while(1)
    {
        GPIOC->BSRRL=1<<13;  //置位
        GPIOC->BSRRH=1<<13;  //复位
    }
}
#endif

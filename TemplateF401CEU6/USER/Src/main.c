
#include "main.h"

#include "Delay.h"

#define WS2812_H GPIOB->BSRRL = GPIO_Pin_2;i=10;while(i--);GPIOB->BSRRH = GPIO_Pin_2;i=2;while(i--)
#define WS2812_L GPIOB->BSRRL = GPIO_Pin_2;i=2;while(i--);GPIOB->BSRRH = GPIO_Pin_2;i=10;while(i--)

void WS2812_SetRGBColor(uint8_t r, uint8_t g, uint8_t b) {
    uint8_t i, j;

    for (j = 0; j < 8; j++) {
        if (g & (0x80 >> j)) {
            WS2812_H;
        } else {
            WS2812_L;
        }
    }
    for (j = 0; j < 8; j++) {
        if (r & (0x80 >> j)) {
            WS2812_H;
        } else {
            WS2812_L;
        }
    }

    for (j = 0; j < 8; j++) {
        if (b & (0x80 >> j)) {
            WS2812_H;
        } else {
            WS2812_L;
        }
    }
}

int main() {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_2);
    while (1) {
        WS2812_SetRGBColor(0, 1, 2);
        WS2812_SetRGBColor(0, 2, 1);
        WS2812_SetRGBColor(1, 0, 2);
        WS2812_SetRGBColor(1, 2, 0);
        WS2812_SetRGBColor(2, 0, 1);
        WS2812_SetRGBColor(2, 1, 0);
        WS2812_SetRGBColor(0, 1, 2);
        WS2812_SetRGBColor(0, 2, 1);
        Delay_ms(100);





        WS2812_SetRGBColor(0, 2, 1);
        WS2812_SetRGBColor(1, 0, 2);
        WS2812_SetRGBColor(1, 2, 0);
        WS2812_SetRGBColor(2, 0, 1);
        WS2812_SetRGBColor(2, 1, 0);
        WS2812_SetRGBColor(0, 1, 2);
        WS2812_SetRGBColor(0, 2, 1);WS2812_SetRGBColor(0, 1, 2);
        Delay_ms(100);





        WS2812_SetRGBColor(1, 0, 2);
        WS2812_SetRGBColor(1, 2, 0);
        WS2812_SetRGBColor(2, 0, 1);
        WS2812_SetRGBColor(2, 1, 0);
        WS2812_SetRGBColor(0, 1, 2);
        WS2812_SetRGBColor(0, 2, 1); WS2812_SetRGBColor(0, 1, 2);
        WS2812_SetRGBColor(0, 2, 1);
        Delay_ms(100);
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

//
// Created by xiaotian on 2021/12/14.
//

#ifndef TEMPLATEF401CEU6_WS2812_H
#define TEMPLATEF401CEU6_WS2812_H

#include "stm32f4xx.h"

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

#endif //TEMPLATEF401CEU6_WS2812_H

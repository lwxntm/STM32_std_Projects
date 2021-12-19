//
// Created by xiaotian on 2021/12/14.
//

#ifndef TEMPLATEF401CEU6_ST7789_H
#define TEMPLATEF401CEU6_ST7789_H

#define  SCL_GPIO_Port GPIOB
#define  SCL_GPIO_Pin GPIO_Pin_12
#define  SDA_GPIO_Port GPIOB
#define  SDA_GPIO_Pin GPIO_Pin_13
#define  RS_GPIO_Port GPIOB
#define  RS_GPIO_Pin GPIO_Pin_15
#define  RES_GPIO_Port GPIOB
#define  RES_GPIO_Pin GPIO_Pin_14
#define  BL_GPIO_Port GPIOA
#define  BL_GPIO_Pin GPIO_Pin_8


void lcd_initial();
void Font_Test();
#endif //TEMPLATEF401CEU6_ST7789_H

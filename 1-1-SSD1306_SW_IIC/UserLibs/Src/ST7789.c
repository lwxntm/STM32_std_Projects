//
// Created by xiaotian on 2021/12/14.
//

#include "stm32f4xx.h"

//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：STC51
//1.3寸TFT_ST7735液晶驱动
//********************************************************************************
#include "Delay.h"
#include<string.h>
#include<ST7789_Font.h>
#include "ST7789.h"
#include <stdio.h>


#define uchar unsigned char
#define uint unsigned int


//测试硬件平台：STC12C5A60S2/STC12LE5A60S2
//主频：12MHZ
//单片机IO推挽输出设置定义
#define USE_LANDSCAPE//测试程序横竖屏切换，横屏请开启此宏，竖屏请屏蔽
#define MCU_STC12//如果您使用的单片机不是STC12系列(如STC89C52)请屏蔽此宏定义
/*
//---------------------------液晶屏接线说明-------------------------------------//
//接线前请参考液晶屏说明书第10页引脚定义
sbit bl        =P1^4;//接模块BL引脚，背光可以采用IO控制或者PWM控制，也可以直接接到高电平常亮
sbit scl       =P1^5;//接模块CLK引脚,接裸屏Pin9_SCL
sbit sda       =P1^3;//接模块DIN/MOSI引脚，接裸屏Pin8_SDA
sbit rs        =P3^4;//接模块D/C引脚，接裸屏Pin7_A0
sbit cs        =P1^7;//接模块CE引脚，接裸屏Pin12_CS
sbit reset     =P3^5;//接模块RST引脚，接裸屏Pin6_RES
//---------------------------End of液晶屏接线---------------------------------//
*/


//定义常用颜色
#define RED        0xf800
#define GREEN        0x07e0
#define BLUE        0x001f
#define WHITE        0xffff
#define BLACK        0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D
#define GRAY1   0x8410
#define GRAY2   0x4208


void Contrast_Adjust();

typFNT_GBK16 hz16[];

void Output_Pixel(uint x, uint y);


void delay_ms(volatile uint time) {
    Delay_ms(time);
}


//向SPI总线传输一个8位数据
void SPI_WriteData(uint8_t Data) {
    unsigned char i = 0;
    for (i = 8; i > 0; i--) {
        if (Data & 0x80)
            GPIO_SetBits(SDA_GPIO_Port, SDA_GPIO_Pin);//输出数据
        else GPIO_ResetBits(SDA_GPIO_Port, SDA_GPIO_Pin);
        GPIO_ResetBits(SCL_GPIO_Port, SCL_GPIO_Pin);
        delay_ms(1);
        GPIO_SetBits(SCL_GPIO_Port, SCL_GPIO_Pin);delay_ms(1);
        Data = (Data<<1);
    }
}

//向液晶屏写一个8位指令
void Lcd_WriteIndex(uchar Data) {

   // cs = 0;
    GPIO_ResetBits(RS_GPIO_Port, RS_GPIO_Pin);
    SPI_WriteData(Data);
   // cs = 1;
}

//向液晶屏写一个8位数据
void Lcd_WriteData(uchar Data) {
    unsigned char i = 0;
   // cs = 0;
    GPIO_SetBits(RS_GPIO_Port, RS_GPIO_Pin);
    SPI_WriteData(Data);
  //  cs = 1;
}

//向液晶屏写一个16位数据
void LCD_WriteData_16Bit(unsigned int Data) {
    unsigned char i = 0;
  //  cs = 0;
    GPIO_SetBits(RS_GPIO_Port, RS_GPIO_Pin);
    SPI_WriteData(Data >> 8);    //写入高8位数据
    SPI_WriteData(Data);            //写入低8位数据
  //  cs = 1;

}

void Reset() {
    GPIO_ResetBits(RES_GPIO_Port, RES_GPIO_Pin);
    delay_ms(100);
    GPIO_SetBits(RES_GPIO_Port, RES_GPIO_Pin);
    delay_ms(100);
}

//////////////////////////////////////////////////////////////////////////////////////////////
//液晶屏初始化 for S6D02A1
void lcd_initial() {
    Reset();//Reset before LCD Init.
//	Lcd_WriteIndex(0x11);//Sleep exit
    delay_ms(120);
    Lcd_WriteIndex(0x36);
    Lcd_WriteData(0x00);

    Lcd_WriteIndex(0x3A);
    Lcd_WriteData(0x05);

    Lcd_WriteIndex(0xB2);
    Lcd_WriteData(0x0C);
    Lcd_WriteData(0x0C);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x33);
    Lcd_WriteData(0x33);

    Lcd_WriteIndex(0xB7);
    Lcd_WriteData(0x35);

    Lcd_WriteIndex(0xBB);
    Lcd_WriteData(0x19);

    Lcd_WriteIndex(0xC0);
    Lcd_WriteData(0x2C);

    Lcd_WriteIndex(0xC2);
    Lcd_WriteData(0x01);

    Lcd_WriteIndex(0xC3);
    Lcd_WriteData(0x12);

    Lcd_WriteIndex(0xC4);
    Lcd_WriteData(0x20);

    Lcd_WriteIndex(0xC6);
    Lcd_WriteData(0x0F);

    Lcd_WriteIndex(0xD0);
    Lcd_WriteData(0xA4);
    Lcd_WriteData(0xA1);

    Lcd_WriteIndex(0xE0);
    Lcd_WriteData(0xD0);
    Lcd_WriteData(0x04);
    Lcd_WriteData(0x0D);
    Lcd_WriteData(0x11);
    Lcd_WriteData(0x13);
    Lcd_WriteData(0x2B);
    Lcd_WriteData(0x3F);
    Lcd_WriteData(0x54);
    Lcd_WriteData(0x4C);
    Lcd_WriteData(0x18);
    Lcd_WriteData(0x0D);
    Lcd_WriteData(0x0B);
    Lcd_WriteData(0x1F);
    Lcd_WriteData(0x23);

    Lcd_WriteIndex(0xE1);
    Lcd_WriteData(0xD0);
    Lcd_WriteData(0x04);
    Lcd_WriteData(0x0C);
    Lcd_WriteData(0x11);
    Lcd_WriteData(0x13);
    Lcd_WriteData(0x2C);
    Lcd_WriteData(0x3F);
    Lcd_WriteData(0x44);
    Lcd_WriteData(0x51);
    Lcd_WriteData(0x2F);
    Lcd_WriteData(0x1F);
    Lcd_WriteData(0x1F);
    Lcd_WriteData(0x20);
    Lcd_WriteData(0x23);

    Lcd_WriteIndex(0x21);

    Lcd_WriteIndex(0x11);


    Lcd_WriteIndex(0x29);


}


/*************************************************
函数名：LCD_Set_Region
功能：设置lcd显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
void Lcd_SetRegion(unsigned int x_start, unsigned int y_start, unsigned int x_end, unsigned int y_end) {

    Lcd_WriteIndex(0x2a);
    Lcd_WriteData(0x00);
    Lcd_WriteData(x_start);
    Lcd_WriteData(0x00);
    Lcd_WriteData(x_end);

    Lcd_WriteIndex(0x2b);
    Lcd_WriteData(0x00);
    Lcd_WriteData(y_start);
    Lcd_WriteData(0x00);
    Lcd_WriteData(y_end);
    Lcd_WriteIndex(0x2c);
}


void PutPixel(uint x_start, uint y_start, uint color) {
    Lcd_SetRegion(x_start, y_start, x_start + 1, y_start + 1);
    LCD_WriteData_16Bit(color);

}


void dsp_single_colour(int color) {
    uchar i, j;
    Lcd_SetRegion(0, 0, 240 - 1, 240 - 1);
    for (i = 0; i < 240; i++)
        for (j = 0; j < 240; j++)
            LCD_WriteData_16Bit(color);
}

//采用设置窗口方法填充字库数据，相比Gui_DrawFont_GBK16更快速
void Fast_DrawFont_GBK16(uint x, uint y, uint fc, uint bc, uchar *s) {
    unsigned char i, j;
    unsigned short k;
    uint HZnum;
    HZnum = sizeof(hz16) / sizeof(typFNT_GBK16);
    while (*s) {
        if ((*s) >= 128) {
            for (k = 0; k < HZnum; k++) {
                if ((hz16[k].Index[0] == *(s)) && (hz16[k].Index[1] == *(s + 1))) {
                    Lcd_SetRegion(x, y, x + 16 - 1, y + 16 - 1);
                    for (i = 0; i < 16 * 2; i++) {
                        for (j = 0; j < 8; j++) {
                            if (hz16[k].Msk[i] & (0x80 >> j)) LCD_WriteData_16Bit(fc);
                            else {
                                if (fc != bc) LCD_WriteData_16Bit(bc);
                            }
                        }
                    }


                }
            }
            s += 2;
            x += 16;
        } else
            s += 1;

    }
}
/*
//此方法描绘汉字较慢
void Gui_DrawFont_GBK16(uint x, uint y, uint fc, uint bc, uchar *s) {
    unsigned char i, j;
    unsigned short k, x0;
    x0 = x;

    while (*s) {
        if ((*s) >= 128) {
            for (k = 0; k < hz16_num; k++) {
                if ((hz16[k].Index[0] == *(s)) && (hz16[k].Index[1] == *(s + 1))) {
                    for (i = 0; i < 16; i++) {
                        for (j = 0; j < 8; j++) {
                            if (hz16[k].Msk[i * 2] & (0x80 >> j)) PutPixel(x + j, y + i, fc);
                            else {
                                if (fc != bc) PutPixel(x + j, y + i, bc);
                            }
                        }
                        for (j = 0; j < 8; j++) {
                            if (hz16[k].Msk[i * 2 + 1] & (0x80 >> j)) PutPixel(x + j + 8, y + i, fc);
                            else {
                                if (fc != bc) PutPixel(x + j + 8, y + i, bc);
                            }
                        }
                    }
                }
            }
            s += 2;
            x += 16;
        } else
            s += 1;

    }
}
*/
void Font_Test(void) {
    //中文显示测试全动电子欢迎您因为专业所以注
    dsp_single_colour(WHITE);
    Fast_DrawFont_GBK16(8, 10, BLUE, YELLOW, "中文测试");
    Fast_DrawFont_GBK16(16, 50, BLUE, WHITE, "欢迎您");
    Fast_DrawFont_GBK16(8, 70, WHITE, BLUE, "因为专注");
    Fast_DrawFont_GBK16(8, 90, WHITE, BLUE, "所以专业");
    Fast_DrawFont_GBK16(16, 150, BLUE, WHITE, "欢迎您");
    Fast_DrawFont_GBK16(16, 190, BLUE, WHITE, "欢迎您");
    delay_ms(1800);
}







//
// Created by xiaotian on 2021/12/14.
//

#include "stm32f4xx.h"

//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ����STC51
//1.3��TFT_ST7735Һ������
//********************************************************************************
#include "Delay.h"
#include<string.h>
#include<ST7789_Font.h>
#include "ST7789.h"
#include <stdio.h>


#define uchar unsigned char
#define uint unsigned int


//����Ӳ��ƽ̨��STC12C5A60S2/STC12LE5A60S2
//��Ƶ��12MHZ
//��Ƭ��IO����������ö���
#define USE_LANDSCAPE//���Գ���������л��������뿪���˺꣬����������
#define MCU_STC12//�����ʹ�õĵ�Ƭ������STC12ϵ��(��STC89C52)�����δ˺궨��
/*
//---------------------------Һ��������˵��-------------------------------------//
//����ǰ��ο�Һ����˵�����10ҳ���Ŷ���
sbit bl        =P1^4;//��ģ��BL���ţ�������Բ���IO���ƻ���PWM���ƣ�Ҳ����ֱ�ӽӵ��ߵ�ƽ����
sbit scl       =P1^5;//��ģ��CLK����,������Pin9_SCL
sbit sda       =P1^3;//��ģ��DIN/MOSI���ţ�������Pin8_SDA
sbit rs        =P3^4;//��ģ��D/C���ţ�������Pin7_A0
sbit cs        =P1^7;//��ģ��CE���ţ�������Pin12_CS
sbit reset     =P3^5;//��ģ��RST���ţ�������Pin6_RES
//---------------------------End ofҺ��������---------------------------------//
*/


//���峣����ɫ
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


//��SPI���ߴ���һ��8λ����
void SPI_WriteData(uint8_t Data) {
    unsigned char i = 0;
    for (i = 8; i > 0; i--) {
        if (Data & 0x80)
            GPIO_SetBits(SDA_GPIO_Port, SDA_GPIO_Pin);//�������
        else GPIO_ResetBits(SDA_GPIO_Port, SDA_GPIO_Pin);
        GPIO_ResetBits(SCL_GPIO_Port, SCL_GPIO_Pin);
        delay_ms(1);
        GPIO_SetBits(SCL_GPIO_Port, SCL_GPIO_Pin);delay_ms(1);
        Data = (Data<<1);
    }
}

//��Һ����дһ��8λָ��
void Lcd_WriteIndex(uchar Data) {

   // cs = 0;
    GPIO_ResetBits(RS_GPIO_Port, RS_GPIO_Pin);
    SPI_WriteData(Data);
   // cs = 1;
}

//��Һ����дһ��8λ����
void Lcd_WriteData(uchar Data) {
    unsigned char i = 0;
   // cs = 0;
    GPIO_SetBits(RS_GPIO_Port, RS_GPIO_Pin);
    SPI_WriteData(Data);
  //  cs = 1;
}

//��Һ����дһ��16λ����
void LCD_WriteData_16Bit(unsigned int Data) {
    unsigned char i = 0;
  //  cs = 0;
    GPIO_SetBits(RS_GPIO_Port, RS_GPIO_Pin);
    SPI_WriteData(Data >> 8);    //д���8λ����
    SPI_WriteData(Data);            //д���8λ����
  //  cs = 1;

}

void Reset() {
    GPIO_ResetBits(RES_GPIO_Port, RES_GPIO_Pin);
    delay_ms(100);
    GPIO_SetBits(RES_GPIO_Port, RES_GPIO_Pin);
    delay_ms(100);
}

//////////////////////////////////////////////////////////////////////////////////////////////
//Һ������ʼ�� for S6D02A1
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
��������LCD_Set_Region
���ܣ�����lcd��ʾ�����ڴ�����д�������Զ�����
��ڲ�����xy�����յ�
����ֵ����
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

//�������ô��ڷ�������ֿ����ݣ����Gui_DrawFont_GBK16������
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
//�˷�����溺�ֽ���
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
    //������ʾ����ȫ�����ӻ�ӭ����Ϊרҵ����ע
    dsp_single_colour(WHITE);
    Fast_DrawFont_GBK16(8, 10, BLUE, YELLOW, "���Ĳ���");
    Fast_DrawFont_GBK16(16, 50, BLUE, WHITE, "��ӭ��");
    Fast_DrawFont_GBK16(8, 70, WHITE, BLUE, "��Ϊרע");
    Fast_DrawFont_GBK16(8, 90, WHITE, BLUE, "����רҵ");
    Fast_DrawFont_GBK16(16, 150, BLUE, WHITE, "��ӭ��");
    Fast_DrawFont_GBK16(16, 190, BLUE, WHITE, "��ӭ��");
    delay_ms(1800);
}







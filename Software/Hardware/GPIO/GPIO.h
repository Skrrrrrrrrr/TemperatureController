#ifndef __GPIO_H
#define __GPIO_H

#include "config.h"

extern u8 psw2_st;

void IO_init();

extern void GPIO_init_pin(int pin, int mode); //��ʼ������IO���ź���
/*
ȡֵ��pin:Ҫ��ʼ��������   ����11 Ϊ P1^1
ȡֵ��mode:Ҫ��ʼ��ģʽ    ����0 Ϊ ׼˫��   5mAС����������ѡ��
															 1 Ϊ ǿ����   20mA����������ѡ��
															 2 Ϊ ����̬   ��ֹ��������������A/Dת��ѡ��
															 3 Ϊ ��©     ȡ���ڲ����������裬ѡ��
*/
extern bit Get_IO(int IO); //��ȡ����IO״̬

extern void Out_IO(unsigned char IO, bit status); //����IO���

#endif
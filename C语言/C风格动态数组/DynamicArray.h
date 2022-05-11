#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct DYNAMICARRAY
{
	int* pAddr;//��ŵ�ǰ���ݵĵ�ַ
	int size;//��ǰ�ж���Ԫ��
	int capacity;//��������������������ɶ���Ԫ��
}Dynamic_Array;

//��ʼ��
Dynamic_Array* Array_Init();
//����
void Push_Back_Array(Dynamic_Array*arr,int value);
//����λ��ɾ��
void Remove_Array(Dynamic_Array* arr, int pos);
//����ֵɾ��
void RemoveByValue_Array(Dynamic_Array*arr,int value);
//����
int Find_Array(Dynamic_Array* arr, int value);
//��ӡ
void Print_Array(Dynamic_Array* arr);
//�ͷŶ�̬������ڴ�
void FreeSpace_Array(Dynamic_Array* arr);
//�������
void Clear_Array(Dynamic_Array* arr);
//��ȡ��̬���������
int Cappcity_Array(Dynamic_Array* arr);
//��ö�̬���鵱ǰԪ�ظ���
int Size_Array(Dynamic_Array* arr);
//����λ�û�ȡĳ��λ��Ԫ��
int At_Array(Dynamic_Array* arr, int poa);

#endif 
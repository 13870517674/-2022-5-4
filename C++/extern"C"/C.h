#pragma once;       //��ֹͷ�ļ��ظ�������Windowsƽ̨ר��
#ifdef __cplusplus //ʹ��Ԥ������ж��Ƿ�Ϊcpp�ļ�
extern "C" {
    void display();
}
#endif
#ifndef __cplusplus
void display();
#endif
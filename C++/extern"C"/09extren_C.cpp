#include<iostream>
#include<thread>
#include"C.h"
//������ϴ��룬h�ļ�û��дextern"C"��ô����ʹ���������ַ�ʽ
extern"C" {
#include"C.h"
}
int main() {
    std::thread threads(display);
    threads.join();
}
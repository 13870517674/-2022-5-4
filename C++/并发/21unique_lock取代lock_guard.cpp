#include<iostream>
#include<thread>
#include<mutex>

//1:unique_lockȡ��lock_guard
//unique_lock�Ǹ���ģ�壬�����У�һ��lock_guard���Ƽ�ʹ�ã���lock_guardȡ����mutex��lock��nulcok();
//unique_lock��lock_guard���ܶࣻЧ���ϲ�һ�㣬�ڴ��һ��

int v = 1;

void critical_section(int change_v)noexcept {
    static std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    // ִ�о�������
    v = change_v;
    std::cout << v << std::endl;
    // ���������ͷ�
    lock.unlock();

    // �ڴ��ڼ䣬�κ��˶��������� v �ĳ���Ȩ

    // ��ʼ��һ�龺���������ٴμ���
    lock.lock();
    v += 1;
    std::cout << v << std::endl;
}

int main() {
    std::jthread t1(critical_section, 2), t2(critical_section, 3);//ֻ�����ֿ���2334����3423������Ҫ���������߳�˭�ȿ���
    return 0;
}
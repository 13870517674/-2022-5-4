#include<iostream>
#include<thread>
int main(){
	std::thread a([]() {});
	std::cout << a.get_id() << std::endl;
	a.detach();
	//thread�������������̲߳��ܻ�ȡ��id�����û�У���᷵��һ��std::thread::id����������Ĭ�Ϲ��췽ʽ���ɣ���ʾ���̲߳����ڡ�

	//��ε�ǰ�̵߳�ID����ͨ������std::this_thread::get_id()���,����
	std::cout << std::this_thread::get_id() << std::endl;
	std::thread b([]() {std::cout << std::this_thread::get_id() << std::endl; });
	b.join();
}
#include<iostream>
#include<thread>

void do_something(unsigned) {}
struct func {
	int& i;
	func(int& i_) :i(i_) {}
	void operator()() {
		for (unsigned j = 0; j < 1000000; ++j) {
			do_something(i);
		}
	}
};

void oops() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread my_thread(my_func);
	/*detach()�����߳��ں�̨�����������У����߳��޷���ȡ�����̵߳Ŀ���Ȩ����ʹ���߳̽��������߳�δִ��Ҳ��������������߳̽���ʱ��������ʱ�⸺�����������߳���ص���Դ��*/
	my_thread.detach();
}

int main() {
	oops();
	//���߳̿����������У����̵߳ĺ�������,Ȼ��ͻ�����,�����п��ܵ�����������
}
//��18���������
//��19���ϰ벿��̸�������
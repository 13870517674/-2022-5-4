#include<iostream>
#include<thread>
#include<Windows.h>

void do_something(unsigned) { std::cout << 1 << ' '; }
struct func {
	int& i;
	func(int& i_) :i(i_) {}
	void operator()() {
		for (unsigned j = 0; j < 10; ++j) {
			do_something(i);
		}
	}
};
class scoped_thread {
	std::thread t;
public:
	explicit scoped_thread(std::thread t_) :t(std::move(t_)) {
		if (!t.joinable())
			throw std::logic_error("NO thread");//���쳣��������̲߳��ܱ���ϣ�Ҳ����join����death��ʱ����׳��쳣
												//ʹ��std::logic_error��ʵ����ͨ��ûɶ���𣬵��Ǻù���һЩ����������׼
	}
	~scoped_thread() {
		//join �ȴ��߳̽��� ���û�����Ϳ���join����ֱ������,ִ��̫���ˣ�������Ϊ��Ҫjoin�Ż��ӡ����ʵ����Ҫ�����Ǽ�һ��Sleep�Ϳ�������
		//���߳���һ��ѭ���������������̫���ˣ��������ʱ�����̺߳�����û�����꣬����Ҫ��join��ס����ִ����
		Sleep(1000);
		t.join();
	}
	//scoped_thread(std::thread const&) = delete;
	scoped_thread operator=(scoped_thread const&) = delete;
};
void f() {
	int some_local_state = 0;
	scoped_thread t{ std::thread(func(some_local_state)) };
}
int main() {
	f();
}
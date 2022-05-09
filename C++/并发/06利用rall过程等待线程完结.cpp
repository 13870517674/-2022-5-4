#include<iostream>
#include<thread>
class thread_guard {
	std::thread& t;
public:
	explicit thread_guard(std::thread& t_) :t(t_) {}
	~thread_guard() {
		/* joinabe��Ա������������c++�ٷ��ĵ����Ƿ����߳��Ƿ��ǿɽ�ϵġ�. �ɽ�ϵ���˼���ǣ�һ���߳��Ƿ��ܹ���ִ��Join������detch������
		��Ϊ��ͬ���̲߳��ܱ�join���Σ�Ҳ����join���ٽ���detach��ͬ��Ҳ�����Ա�detach���Σ�����joinable���������ж��Ƿ��ܽ��пɽ�ϡ�*/
		if (t.joinable()) {
			t.join();
		}
	}
	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;
};
void do_something() {}
struct func {
	int& i;
	func(int& i_) :i(i_) {}
	void operator()() {
		for (unsigned j = 0; j < 1000000; ++j) {
			do_something();
		}
	}
};
void f() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);
	do_something();
}
int main() {
	f();
}
//20���°벿�ֵ�21ҳ
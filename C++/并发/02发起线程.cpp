#include<iostream>
#include<thread>
void do_some_work(){}
class background_task {
public:
	void operator()()const {
		do_some_work();
	}
};
int main() {
	background_task f;
	std::thread my_thread(f);
	my_thread.join();
}
//��������lambda���ʽ������ָ��ȶ����ԣ�������ʹ�ú�������
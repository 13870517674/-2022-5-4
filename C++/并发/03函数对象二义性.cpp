#include<iostream>
#include<thread>
class background_task {
public:
	void operator()()const {}
};

int main() {
	//std::thread my_thread(background_task());//�����Ƿ����µ��̣߳�����һ�������������󣬵��ǻᱻ����Ϊ��������
	
	//�����ʽ���ټ�һ��С���ţ�����ʹ�����﷨��ʼ���б����С���ŵķ�ʽ,����ѡһ�־��У��Ƽ�ʹ�ó�ʼ���б�����lambda���ʽ
	
	//std::thread my_thread{ background_task() };
	std::thread my_thread((background_task()));
	my_thread.join();

	//lambda��д����ûɶ������������ֱ��д��
	std::thread my_thread2([] {});
	my_thread2.join();

}
//�ڵ�17��Դ�����ϸ�Ľ���
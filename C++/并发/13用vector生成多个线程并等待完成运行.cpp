#include<thread>
#include<iostream>
#include<vector>
#include<mutex>

std::mutex p;

void do_word(int &id) {
	{
		std::lock_guard<std::mutex>a(p);//����
		std::cout << ++id << '\n';
	}
}
void f() {
	int a = 1;
	std::vector<std::thread>threads;
	for (unsigned i = 0; i < 20; ++i) {
		threads.emplace_back(do_word, std::ref(a));//�������̣߳��˳�Ա������C++14���
	}
	for (auto& entry : threads)
		entry.join();
}
int main() {
	f();
}
//��Ϊ�߳�֮��������ٶȲ�һ�������Խ��һ�㶼��һ��,��Դ���ᣬ��thread���󴴽��õ�ʱ�����߳̿�ʼ����
//4��27���Ǹ�����������һЩ�Ľ������뻥�⣬��ס�ˣ������̲߳�������
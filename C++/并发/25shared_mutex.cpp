#include<iostream>
#include<thread>
#include<shared_mutex>
using namespace std;
/*C++14�ṩ��shared_mutex���������-д�����⣬Ҳ���Ƕ�д��������ͨ����һ������д��ͬʱֻ����һ��д�߻������ߣ�������ͬʱ���ж�������д�ߣ���д��������һ�����ͨ��Ҫ�á�

shared_mutexͨ��lock_shared��unlock_shared��shared_lock���ж��ߵ������������ͨ��lock��unlock��unique_lock����д�ߵ������������*/
shared_mutex g_mutex;
std::string g_str;

void readLoop()
{
	while (true) {
		this_thread::sleep_for(chrono::milliseconds(100));
		g_mutex.lock_shared();
		cout << g_str;
		g_mutex.unlock_shared();
	}
}

void writeLoop()
{
	int number = 0;
	while (true) {
		this_thread::sleep_for(chrono::milliseconds(100));
		g_mutex.lock();
		g_str = to_string(number++) + "\n";
		g_mutex.unlock();
	}
}

int main()
{
	thread(writeLoop).detach();
	thread(writeLoop).detach();
	thread(readLoop).detach();
	thread(readLoop).detach();
	system("pause");
}
//Ҳ����ʹ��unique_lcok���ʹ�ã�������mutex
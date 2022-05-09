#include<iostream>
#include<mutex>
#include<thread>

//std::lock()����ģ�壺���ڴ�������������ʱ��ų���
//������ͬʱ��סһ�������������ϵĻ��������������������˲��ޣ�1�����У���
//��������������Ϊ�ٶ���߳��� ��Ϊ����˳�����⵼�µ������ķ������⣻
//std::lock();�������������һ��û����ס��������������ţ������л���������ס�������������ߣ����أ�
//Ҫ����������������ס��Ҫ��������������û��ס�����ֻ����һ������һ��û���ɹ��������������Ѿ���ס�Ľ���

using namespace std;
int g_i = 0;
std::mutex g_i_mutex;
std::mutex g_j_mutex;

void safe_increment()
{
	/*ͬʱ������*/
	std::lock(g_i_mutex, g_j_mutex);
	for (int i = 0; i < 100; i++)
	{
		++g_i;
	}
	/*��Ҫ�ֶ�����*/
	std::cout << std::this_thread::get_id() << ": " << g_i << '\n';
	g_i_mutex.unlock();
	g_j_mutex.unlock();
}

int main()
{
	std::cout << "main: " << g_i << '\n';
	std::thread t1(safe_increment);
	std::thread t2(safe_increment);
	t1.join();
	t2.join();
	std::cout << "main: " << g_i << '\n';
	return 0;
}
//�ܽ�:std::lock������һ���������������������ʹ�ã�����һ��һ������
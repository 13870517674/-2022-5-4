#include<iostream>
#include<thread>
#include<mutex>
#include <atomic>
//int g_mycout = 0;	//����һ��ȫ�ֱ���
std::atomic<int>g_mycout = 0;	//���Ƿ�װ��һ������Ϊint�Ķ���ֵ�������ǿ��������һ��int���ͱ���һ�����������g_mycout
//std::mutex g_my_mutex;
void mythread()
{
	for (int i = 0; i < 1000000; i++)
	{
		//g_my_mutex.lock();
		//g_mycout++;
		//g_my_mutex.unlock();

		g_mycout++;//��Ӧ�Ĳ�����һ��ԭ�Ӳ��������ᱻ��ϣ�
		g_mycout += 1;//֧��
		//g_mycout = g_mycout + 1;	//�������,����ԭ�Ӳ���
	}
}

std::atomic<bool>g_ifod = false;	//�̱߳���˳���������ԭ�Ӳ�������ֹ����д����

void mythread2()
{
	std::chrono::milliseconds dura(1000);	//һ����
	while (g_ifod == false)
	{
		//ϵͳûҪ���߳��˳������Ա��߳̿��Ը��Լ�������
		std::cout << "thread id= " << std::this_thread::get_id() << "������..." << std::endl;
		std::this_thread::sleep_for(dura);
	}
	std::cout << "thread id= " << std::this_thread::get_id() << "���н���...." << std::endl;
}

int main() {
/*����std::atomicԭ�Ӳ���

3.1 ԭ�Ӳ�����������������
�����������̱߳���� ���ڱ����������ݣ�����ס�� �����������ݣ� ������

�������̣߳���һ���������в�����һ���̶߳����������ֵ��һ���߳������������дֵ��

��ʹ��һ���򵥱����Ķ�ȡ��д�����������ͬʱд�������������Ҳ�п��ܻᵼ�¶�дֵ���ң�һ��C���ᱻ���3��4����������ִ�У�������Ȼ�п��ܻ��ң�*/

	std::thread mytobj1(mythread);
	std::thread mytobj2(mythread);
	mytobj1.join();
	mytobj2.join();
	std::cout << g_mycout << std::endl;	//�������Ԥ��,�������ɽ��

	//��ҿ��԰�ԭ�Ӳ�������һ�ֲ���Ҫ�õ��������������������Ķ��̲߳�����̷�ʽ
	//����Ҳ��������ԭ�Ӳ������ڶ��߳��в��ᱻ��ϵĳ���ִ��Ƭ�Σ�ԭ�Ӳ����Ȼ�����Ч���ϸ�ʤһ��
	//�������ļ���һ�������һ������Σ����д��룩����ԭ�Ӳ�������ԣ���һ�㶼��һ��������������һ�������

	//ԭ�Ӳ�����һ�㶼��ָ�����ɷָ�Ĳ�������Ҳ����˵���ֲ���Ҫô�����״̬��Ҫô��û��ɵģ������ܳ��ְ����״̬
	//std::atomic������ԭ�Ӳ�����std::atomic�Ǹ���ģ�壬��ʵstd::atomic
	std::thread mytobj1(mythread2);
	std::thread mytobj2(mythread2);
	std::chrono::milliseconds dura(5000);	//������
	std::this_thread::sleep_for(dura);
	g_ifod = true;	//��ԭ�Ӷ����д���������߳��������н�����
	mytobj1.join();
	mytobj2.join();
	std::cout << "����ִ����ϣ��˳�" << std::endl;
}
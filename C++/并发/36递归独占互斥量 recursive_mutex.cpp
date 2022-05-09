#include<iostream>
#include<thread>
#include<mutex>

std::recursive_mutex mymutex;
void test() {
	std::lock_guard<std::recursive_mutex>myguard(mymutex);
	mymutex.lock();
	std::cout << "1" << std::endl;
	mymutex.unlock();
	mymutex.lock();
	mymutex.unlock();
}
int main()
{
/*�ġ��ݹ��ռ������ std::recursive_mutex
std::mutex ��ռʽ������

std::recursive_mutex��������ͬһ���߳���ͬһ����������α� lock() �������ǵݹ�����Ĵ����������Ƶģ�̫����ܻᱨ�쳣����Ч��Ҫ��mutex�͡�

������������ recursive_mutex Ҫ���Ǵ����Ƿ����Ż��ռ䣬����ܵ���һ�� lock()�Ͳ�Ҫ���ö�Ρ�*/
	std::thread a(test), a2(test);
	a.join();
	a2.join();
}
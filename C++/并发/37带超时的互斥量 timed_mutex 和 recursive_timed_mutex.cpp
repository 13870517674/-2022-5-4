#include<mutex>
#include<iostream>
#include<thread>

std::timed_mutex my_mymutex;
void test() {
	std::chrono::milliseconds timeout(1);
	if (my_mymutex.try_lock_for(timeout)) {/*���������⡣����ֱ������ָ���� timeout_duration ��õ�����ȡ���ں����ȵ������ɹ������ʱ���� true �� ���򷵻� false ��*/
		//......�õ�������ture
		std::cout << "1�������õ�����" << std::endl;
		std::this_thread::sleep_for(std::chrono::microseconds(10));
		my_mymutex.unlock();
	}
	else
	{
		std::cout << "û���õ���" << std::endl;
		std::chrono::milliseconds sleeptime(100);
		std::this_thread::sleep_for(sleeptime);
	}
}
/*    try_lock_until()��
������һ��δ����ʱ��㣬�����δ����ʱ��û����ʱ���ڣ�����õ�����ͷ�����̾������������ʱ�䵽��û�õ���������Ҳ������������*/
void test2() {
	std::chrono::milliseconds timeout(1);
	if (my_mymutex.try_lock_until(std::chrono::steady_clock::now() + timeout)) {
		//......�õ�������ture
		std::cout << "1�������õ�����" << std::endl;
		std::this_thread::sleep_for(std::chrono::microseconds(10));
		my_mymutex.unlock();
	}
	else
	{
		std::cout << "û���õ���" << std::endl;
		std::chrono::milliseconds sleeptime(100);
		std::this_thread::sleep_for(sleeptime);
	}
}
int main() {
/*std::recursive_timed_mutex���Ǵ���ʱ�ĵݹ��ռ������

5.1 std::timed_mutex���Ǵ���ʱ�Ķ�ռ������

	try_lock_for()��

�ȴ�һ��ʱ�䣬����õ����������߳�ʱ��δ�õ������ͼ���ִ�У���ѡ��ִ�У����£�*/
	std::thread a(test), a2(test), a3(test),a4(test);
	a.join();
	a2.join();
	a3.join();
	a4.join();

	/*    try_lock_until()��

������һ��δ����ʱ��㣬�����δ����ʱ��û����ʱ���ڣ�����õ�����ͷ�����̾������������ʱ�䵽��û�õ���������Ҳ������������*/


}
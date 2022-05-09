#include<iostream>
#include<mutex>
#include<thread>

//std::lock_guard��std::adopt_lock����
//std::adopt_lock�Ǹ��ṹ�������һ��������ã����þ��Ǳ�ʾ����������Ѿ�lock()��
//����Ҫ��std::lock_guard<std::mutext>���캯�������mutex�����ٴν���lock()��
//����Ѿ�lock��������ͨstd::lock_guard<std::mutext>û��adopt_lock�����ͻᱨ��

std::mutex test5_mutex;//����5����
void test5() {
	test5_mutex.lock();		//�����ǳ�Ա������lock��Ҳ������19��std::lock()
	std::lock_guard<std::mutex> lg(test5_mutex, std::adopt_lock);
	std::cout << "hello test5" <<std:: endl;
}
void test5(int) {//����
	std::lock_guard<std::mutex>a(test5_mutex);
	std::cout << "hello test5(int)" << std::endl;
}

int main() {
	std::thread t1([] { test5(); });//���õ�һ��test5����
	std::thread t2([] { test5(2); });//���õڶ���test5����

	t1.join();
	t2.join();
	return 0;
}
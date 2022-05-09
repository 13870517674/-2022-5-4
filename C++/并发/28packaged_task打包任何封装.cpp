#include<iostream>
#include<thread>
#include<mutex>
#include<future>
#include<vector>

int mythread(int i) {	//�߳���ں���
	std::cout << i << std::endl;
	std::cout << "mythread() start " << "threadid=" << std::this_thread::get_id() << std::endl;//��ӡ���߳�id
	std::chrono::milliseconds dura(1000);//��ʱһ��
	std::this_thread::sleep_for(dura);
	std::cout << "mythread() end " << "threadid=" << std::this_thread::get_id() << std::endl;
	return 5;
}
void test() {		//ֱ�ӵ���,���ڵ��̺߳����߳���ͬһ���߳�
	std::packaged_task<int(int)>mypt(mythread);
	mypt(100);
	std::future<int>result = mypt.get_future();
	std::cout << result.get() << std::endl;
}
int main() {
/*����std::pakcaged_task��������񣬰������װ������
��ģ�壬����ģ������Ǹ��ֿɵ��ö���ͨ��packaged_task�Ѹ��ֿɵ��ö����װ���������㽫����Ϊ�߳���ں��������á�*/
//packaged_task��װ�����Ŀɵ��ã����Դ�����Ƕ�������pakcaged_task����Ҳ��һ���ɵ��ö���
	test();
	std::cout << "main " << "threadid =" << std::this_thread::get_id() << std::endl;
	std::packaged_task<int(int)>mypt(mythread);	//���ǰѺ���mythreadͨ��packaged_task��װ����
	std::thread t1(std::ref(mypt), 1);
	t1.join();	//�ȴ��߳�ִ�����
	std::future<int>result = mypt.get_future();	//std::future����������߳���ں����ķ��ؽ��������result����mythread�̵߳ķ���ֵ
	std::cout << result.get() << std::endl;
	//ʹ��lambda���ʽ
	std::packaged_task<int(int)>mypt2([](int i) {
		std::cout << i << std::endl;
		std::cout << "mythread() start " << "threadid=" << std::this_thread::get_id() << std::endl;//��ӡ���߳�id
		std::chrono::milliseconds dura(1000);//��ʱһ��
		std::this_thread::sleep_for(dura);
		std::cout << "mythread() end " << "threadid=" << std::this_thread::get_id() << std::endl;
		return 50;
		});
	std::thread t2(std::ref(mypt2), 1);
	t2.join();	//�ȴ��߳�ִ�����
	std::future<int>result2 = mypt2.get_future();	
	std::cout << result2.get() << std::endl;

	//�ŵ�����
	std::packaged_task<int(int)>mypt3(mythread);	//���ǰѺ���mythreadͨ��packaged_task��װ����
	std::vector<std::packaged_task<int(int)>>mytasks;
	mytasks.push_back(std::move(mypt3));		//����	�����ƶ����壬���ȥ��mypt��Ϊ��

	std::packaged_task<int(int)>mypt_;
	auto iter = mytasks.begin();
	mypt_ = std::move(*iter);	//�ƶ�����
	mytasks.erase(iter);	//ɾ����һ��Ԫ�أ��������Ѿ�ʧЧ�����Ժ�����벻����ʹ��
	mypt_(123);
	std::future<int>result_ = mypt_.get_future();
	std::cout << result_.get() << std::endl;
}
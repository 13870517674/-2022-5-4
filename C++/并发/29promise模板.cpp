#include<iostream>
#include<thread>
#include<mutex>
#include<future>
#include<vector>
#include<algorithm>
/*std::promise����ģ��
�����ܹ���ĳ���߳��и�����ֵ��Ȼ�����ǿ����������߳��У������ֵȡ����*/
void mythread(std::promise<int>& tmp, int clac) {
	std::cout << "mythread() start" << "threadid = " << std::this_thread::get_id() << std::endl;
	std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);
	std::cout << "mythread() end" << "threadid = " << std::this_thread::get_id() << std::endl;
	int result = clac;
	tmp.set_value(result); //������浽��tmp���������
}

std::vector<std::packaged_task<int(int)>> task_vec;

int main() {
	std::promise<int> myprom;					//����һ��promise���󣬱����ֵ������Ϊint
	std::thread t1(mythread, std::ref(myprom), 180);
	t1.join(); //�������߳��Ѿ�ִ������
	std::future<int> fu1 = myprom.get_future(); //promise��future�󶨣����ڻ�ȡ�̷߳���ֵ
	auto result = fu1.get();
	std::cout << "result = " << result << std::endl;
}
#include <thread>
#include <iostream>
#include <future>

int mythread() {
	std::cout << "mythread() start" << "threadid = " << std::this_thread::get_id() << std::endl;
	std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);
	std::cout << "mythread() end" << "threadid = " << std::this_thread::get_id() << std::endl;
	return 5;
}

int main() {
	std::cout << "main" << "threadid = " << std::this_thread::get_id() << std::endl;
	std::packaged_task<int()> mypt(mythread);
	std::thread t1(std::ref(mypt));
	std::future<int> result = mypt.get_future();	//std::future��Ҳ�İ���ˣ���������ﺬ���߳���ں���

	bool ifcanget = result.valid(); //�ж�future�е�ֵ�ǲ���һ����Чֵ
	std::shared_future<int> result_s(result.share()); //ִ����Ϻ�result_s����ֵ����result�����,�ƶ�����
	ifcanget = result.valid();
	//std::shared_future<int> result_s(std::move(result));
	//ͨ��get_future����ֱֵ�ӹ���һ��shared_future����
	//std::shared_future<int> result_s(mypt.get_future());
	t1.join();

	auto myresult1 = result_s.get();
	auto myresult2 = result_s.get();

	std::cout << "good luck" << std::endl;
	return 0;
}
#include<iostream>
#include<thread>

void update_data_for_widget(int w, int& data) {}
void oops_again(int w) {
	int data;
	//std::thread t(update_data_for_widget, w, data);	//����ʽ����ֵ����
	std::thread t(update_data_for_widget, w, std::ref(data));
	//24ҳ�°벿��
	t.join();
}
class X {
public:
	inline void do_lengthy_work() { std::cout << "class\n"; };
};
void test() {
	X my_x;
	//������std::bind��������������:��Ҫ��ĳ����ĳ�Ա�����趨Ϊ�̺߳�����������Ӧ�ô���һ������ָ�룬ָ��ó�Ա���������⣬���ǻ�Ҫ�������ʵĶ���ָ�룬��Ϊ�ú����ĵ�һ��������
	std::thread t(&X::do_lengthy_work, &my_x);
	//25ҳ�ϰ벿��
	t.join();
}
int main() {
	oops_again(1);
	test();
}
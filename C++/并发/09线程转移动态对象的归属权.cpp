#include<iostream>
#include<thread>
#include<memory>
class V {
public:
	int a;
};

void T(std::unique_ptr<V>p) { }

void test() {
	std::unique_ptr<V>p(new V);
	p->a=42;
	std::thread t(T, std::move(p));//��ʵ����ͨ�Ĵ���ûʲô���𣬾��Ǳ�����ƶ����������ָ��
	t.join();
}

int main() {
	test();
}
//25ҳ�°벿��
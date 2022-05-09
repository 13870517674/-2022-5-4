#include<iostream>
#include<thread>
#include<vector>
#include<mutex>

std::mutex I;

void f(int& i) {
	I.lock();
	std::cout << i++ << std::endl;
	I.unlock();
}
void g(int& i) {
	std::lock_guard<std::mutex>a(I);
	std::cout << i++ << std::endl;
}
int main() {
	int n = 1;
	std::vector<std::jthread>a;
	for (int i = 0; i < 10; i++) {
		//a.emplace_back(f, std::ref(n));		//����lock�汾��
		a.emplace_back(g, std::ref(n));
	}
	/*for (auto& i : a) {				//��Ϊʹ����C++20��jthread�����Բ���Ҫjoin��
		i.join();
	}*/
}
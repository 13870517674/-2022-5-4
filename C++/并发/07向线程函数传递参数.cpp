#include<iostream>
#include<thread>
void f(int i, std::string const& s) {}
void oops(int some_param) {
	char buffer[1024];
	sprintf(buffer, "%i", some_param);//��ʮ��������ת��Ϊ�ַ���
	//std::thread t(f, 3, buffer);	//����ʽ�п�������δ������Ϊ���ڵ�23���24������ϸ����
	std::thread t(f, 3, std::string(buffer));//�ֶ�ת��Ϊstring��������thread���캯����ʽת��
	t.detach();
}
int main() {
	oops(6);
}
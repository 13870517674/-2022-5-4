#include<iostream>
#include<thread>

void some_function(){}
void some_other_function(){}

void test1() {
	std::thread t1(some_function);

	std::thread t2 = std::move(t1);
	t1 = std::thread(some_other_function);


	std::thread t3;
	t3 = std::move(t2);
	//t1����,��Ϊt1�Ѿ���������ʼ�߳�
	t1 = std::move(t3);
	
	/*û��join����detach��std::thread�������joinable��
	joinable�Ķ����ڸ�ֵ��ʱ��ͻ�terminate
	����std::move��ʱ��ҵ��ģ��Ǹ�ֵ��ʱ��ҵ��ģ�Ҳ�������һ��*/

	//���std::thread::operator=���й����������н��̣���joinable==true�����������std::terminate()
	//����ֵother��״̬����*this������otherΪĬ�Ϲ����״̬
}
int main() {
	test1();
}
//27���ϰ벿�ֽ����ˣ�ͬʱ�鿴�ο��ĵ�
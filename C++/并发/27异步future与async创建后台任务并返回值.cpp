#include<iostream>
#include<thread>
#include<mutex>
#include<list>
#include<map>
#include<future>

int mythread() {	//�߳���ں���
	std::cout << "mythread() start" << "threadid=" << std::this_thread::get_id() << std::endl;//��ӡ���߳�id
	std::chrono::milliseconds dura(1000);//��һ��һ���ʱ��
	std::this_thread::sleep_for(dura);
	std::cout << "mythread()end" << "threadid=" << std::this_thread::get_id() << std::endl;
	return 5;
}

class A {
public:
	int mythread(int a) {	
		std::cout << a << std::endl;
		std::cout << "mythread() start" << "threadid=" << std::this_thread::get_id() << std::endl;//��ӡ���߳�id
		std::chrono::milliseconds dura(1000);//��һ�������ʱ��
		std::this_thread::sleep_for(dura);
		std::cout << "mythread()end" << "threadid=" << std::this_thread::get_id() << std::endl;
		return 5;
	}
};
void test() {		//���Ա�������ΰ汾
	A a;
	int i = 10;
	//����ͨ����std::async()����һ���������ò���������std::lunnch����(ö������),���ﵽһЩ�����Ŀ��
	//std::lanuch::deferred:��ʾ�߳���ں������ӳٵ�std::future��wait()����get()��������ʱ��ִ��
	//�����wait()����get()û�б����ã���ô����̸߳������ᴴ��
	//std::lauch:�ӳٵ��ã�����û�д����µ��̣߳��������߳��е��õ��߳���ں�����
	//std::lauch::async���ڵ���async������ʱ��ʼ�����̣߳�
	//async()����Ĭ����std::lauch::async������ֻ��Ҫע�⣺std::lanuch::deferred

	//std::future<int>result = std::async(std::launch::deferred, &A::mythread, &a, i);
	std::future<int>result = std::async(std::launch::async, &A::mythread, &a, i);
	//std::future<int>result = std::async(&A::mythread, &a, i);		//Ĭ�Ϸ�ʽ���������û����

	std::cout << result.get() << std::endl;	//��������ȴ�mythreadִ����ϣ��õ����
}
int main() {
//һ��std::async,future������̨���񲢷���ֵ
//ϣ���̷߳���һ�������
//std::async�Ǹ�����ģ�壬��������һ���첽������������һ���첽����֮��������һ��std::future����std::future�Ǹ���ģ��

/*ʲô�С�����һ���첽���񡱣������Զ�����һ���̣߳�����ʼ ִ�ж�Ӧ���߳���ں�����������һ��std::future�������std::future������
�ͺ����߳���ں��������صĽ�������ǿ���ͨ������future����ĳ�Ա����get()����ȡ�����

��future����������˼��Ҳ���˳ƺ�std::future�ṩ��һ�ַ����첽��������Ļ��ƣ�����˵�����������û�취�����õ��������ڲ��õĽ�����
����߳�ִ����ϵ�ʱ������ܹ��õ�����ˣ����ԣ������ô��⣺future�б�����һ��ֵ�����ֵ���ڽ�����ĳ��ʱ���ܹ��õ���

std::future�����get()��Ա������ȴ��߳�ִ�н��������ؽ�����ò���������ͻ�һֱ�ȴ����о��е���join()�����ǣ����ǿ��Ի�ȡ����ġ�

std::future�����wait()��Ա���������ڵȴ��̷߳��أ����������ؽ�������Ч���� std::thread ��join()����*/

	//���г���ͨ��std::future�����get()��Ա�����ȴ��߳�ִ�н��������ؽ��
	//���get()������ţ�����õ������ķ���ֵ �Ĳ����ݣ����õ�ֵ��������ȴ���ֵ
	
	std::cout << "main " << "threadid=" << std::this_thread::get_id() << std::endl;
	std::future<int>result = std::async(mythread);		//����һ���̲߳���ʼִ��,�󶨹�ϵ�����̲�����������
	std::cout << "continue......!" << std::endl;
	int def;
	def = 0;
	std::cout << result.get() << std::endl;	//��������ȴ�mythreadִ����ϣ��õ����
	//std::cout << result.get() << std::endl;	//get()ֻ�ܵ���һ�Σ����ܵ��ö��
	//result.wait();	//�ȴ��̷߳��أ��������ؽ��
	std::cout << "I Love China!" << std::endl;
	test();
	return 0;
}
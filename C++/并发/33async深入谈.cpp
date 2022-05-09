#include<iostream>
#include<thread>
#include<future>
#include<atomic>
using namespace std::literals;

int mythread()
{
	std::cout << "mythread() start " << "threadid=" << std::this_thread::get_id() << std::endl;
	return 1;
}

int main() {
	////std::async����������async��������һ���첽����
	//std::cout << "main start" << "threadid = " << std::this_thread::get_id() << std::endl;
	//std::future<int>result = std::async(std::launch::deferred,mythread);//�ӳٵ��ã����Ҳ��ᴴ�����̣߳��ӳٵ�get()����wait()��ִ�У���֮��ִ��
	////std::future<int>result = std::async(mythread);
	//std::cout << result.get() << std::endl;

	//std::launch::deferred���ӳٵ��á�,�Լ�std::launch::async��ǿ�ƴ���һ���̡߳�
	//std::thread()���ϵͳ��Դ���ţ���ô���ܴ����߳̾ͻ�ʧ�ܣ���ôִ��std::thread()ʱ����������ܱ���
	//std::async()����һ�㲻�д����̣߳�����async�ܹ������̣߳�������һ���������һ���첽����
	//std::async��std::thread�����ԵĲ�ͬ������async��ʱ�򲢲��������߳�
	//std::launch::deferred���ӳٵ��á����Ҳ��ᴴ�����̣߳��ӳٵ�get()����wait()��ִ�У���֮��ִ��
	//std::launch::async��ǿ��������������߳���ִ�У���ζ�ţ�ϵͳ���봴�����߳�
	//std::launch::async | std::launch::deferred
	//������� | ��ζ�ŵ���async����Ϊ������ �������̲߳�����ִ�� ���� ��û�д������̲߳��ӳٵ���
			//���߾���һ��ϵͳ����һЩ�������

	//�ھŽڿν����ˣ���ʵĬ��ֵӦ����std::launch::async | std::launch::deferred��������Ч����ȫһ��
	//���仰˵ϵͳ���Զ��������첽���������̣߳�����ͬ�������������̣߳�����

	///���о�������˼��ϵͳ��ξ����첽���������̣߳�����ͬ�������������̣߳�
	//std::async��std::thread������
	//std::thread�����̣߳����ϵͳ��Դ���ţ������߳�ʧ�ܣ���ô��������ͻᱨ�쳣����
	//int mythread(){return 1;}
	//std::thread mytobj(mythread);
	//mytobj.join
	//std::thread�����̵߳ķ�ʽ������̷߳���ֵ�������õ����ֵҲ�����ף�
	//std::async�����첽���񡣿��ܴ���Ҳ���ܲ������̡߳�����async���÷����������õ��̵߳ķ���ֵ
	//����ϵͳ��Դ���ƣ�
	//��1�������std::thread�������߳�̫�࣬����ܴ���ʧ�ܣ�ϵͳ�����쳣������
	//��2�������std::async��һ��Ͳ��ᱨ�쳣����Ϊ�����ϵͳ��Դ���ŵ����޷��������̵߳�ʱ�����ֲ��Ӷ�������ĵ��� �Ͳ��ᴴ�����̡߳����Ǻ���˭������result.get()��
				//��ô����첽��������������߳���
	//�����ǿ��std::asyncһ��Ҫ�������̣߳���ô�ͱ���ʹ�ã�std::launch::async�����ܵĴ��۾���ϵͳ��Դ����ʱ��������
	//��3�����飺һ��������߳��������˳���100-200��ʱ��Ƭ��

	//���Ӷ��������std::async���ã���ϵͳ�����Ƿ񴴽����߳�
	/*std::future<int> result = std::async(mythread);
	���⽹���������д�������񵽵���û�б��Ƴ�ִ�С�

	ͨ��wait_for����״̬���жϣ�*/
	std::cout << "main " << "threadid=" << std::this_thread::get_id() << std::endl;
	std::future<int>result = std::async(mythread);
	std::cout << "continue......!" << std::endl;
	//ö������
	std::future_status status = result.wait_for(0s);	
	if (status == std::future_status::timeout)
	{
		//�̻߳�ûִ����
		std::cout << "��ʱ���̻߳�û��ִ�����" << std::endl;
		std::cout << result.get() << std::endl;
	}
	else if (status == std::future_status::ready)
	{
		//��ʾ�̳߳ɹ�����
		std::cout << "�̳߳ɹ�ִ����ϣ�����" << std::endl;
		std::cout << result.get() << std::endl;
	}
	else if (status == std::future_status::deferred)//�ӳ�
	{
		//�̱߳��ӳ�ִ�У���������std::launch::deferred
		std::cout << "�̱߳��ӳ�ִ��" << std::endl;
		std::cout << result.get() << std::endl;
	}

}
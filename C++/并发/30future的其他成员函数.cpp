#include<iostream>
#include<thread>
#include<mutex>
#include<future>
int mythread() {	
	std::cout << "mythread() start " << "threadid=" << std::this_thread::get_id() << std::endl;
	std::chrono::milliseconds dura(2000);
	std::this_thread::sleep_for(dura);
	std::cout << "mythread() end " << "threadid=" << std::this_thread::get_id() << std::endl;
	return 5;
}
int main() {
/*һ��std::future �ĳ�Ա����
1��std::future_status status = result.wait_for(std::chrono::seconds(����));
��ס��ǰ���̣��ȴ�std::async()���첽��������һ��ʱ�䣬Ȼ�󷵻���״̬std::future_status�����std::async()�Ĳ�����std::launch::deferred���ӳ�ִ�У����򲻻Ῠס�����̡�
���� ���� wait_for�ķ���ֵ
future_status::deferred ����״̬���еĺ��������ӳ����У������������ʽ����ʱ����
future_status::ready ����״̬����
future_status::timeout ����״̬�ھ���ָ���ĵȴ�ʱ������δ����
*/
	std::cout << "main " << "threadid=" << std::this_thread::get_id() << std::endl;
	//std::future<int>result = std::async(std::launch::deferred, mythread);
	std::future<int>result = std::async(mythread);
	std::cout << "continue......!" << std::endl;
	//ö������
	std::future_status status = result.wait_for(std::chrono::seconds(3));	//�ȴ�һ����,wait_for��Ա�����ķ���ֵ������
	if (status == std::future_status::timeout)//��ʱ������ȴ���һ���ӣ�ϣ���㷵�أ���û�з��أ���ôstatus==timeout
	{
		//�̻߳�ûִ����
		std::cout << "��ʱ���̻߳�û��ִ�����" << std::endl;
	}
	else if (status == std::future_status::ready)
	{
		//��ʾ�̳߳ɹ�����
		std::cout << "�̳߳ɹ�ִ����ϣ�����" << std::endl;
		std::cout << result.get() << std::endl;
	}
	else if (status == std::future_status::deferred)//�ӳ�
	{
		//���async��һ������������Ϊstd::launch::deferred����������
		std::cout << "�̱߳��ӳ�ִ��" << std::endl;
		std::cout << result.get() << std::endl;		
	}

	//getֻ�ܵ���һ�Σ���Ϊ����һ���ƶ�����,����ٴε��þͻ������쳣������������Ļ���������status == std::future_status::ready��һ�ε���get()��Ȼ���ظ�����get�����쳣
	return 0;
}
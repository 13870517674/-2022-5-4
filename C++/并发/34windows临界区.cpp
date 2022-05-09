#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <Windows.h>

#define __WINDOWSJQ_

using namespace std;

class A
{
public:
	// ���յ�����Ϣ�������
	void inMsgRecvQueue()
	{
		for (size_t i = 0; i < 1000; ++i)
		{
			cout << "�յ���Ϣ����������� " << i << endl;

#ifdef  __WINDOWSJQ_
			EnterCriticalSection(&my_winsec);	//	�����ٽ���
			//EnterCriticalSection(&my_winsec);	//	�����ٴν����ٽ���,���򲻻����
			msgRecvQueue.push_back(i);
			LeaveCriticalSection(&my_winsec);	//	�뿪�ٽ���
			//LeaveCriticalSection(&my_winsec);	//	����������Σ������뿪���β��ᱨ��
#elif
			my_mutex.lock();
			msgRecvQueue.push_back(i);
			my_mutex.unlock();
#endif //  __WINDOWSJQ_
		}

		cout << "��Ϣ��ӽ���" << endl;
	}

	// �Ӷ�����ȡ����Ϣ
	void outMsgRecvQueue()
	{
		for (size_t i = 0; i < 1000; ++i)
		{
#ifdef  __WINDOWSJQ_
			EnterCriticalSection(&my_winsec);	//	�����ٽ���
			if (!msgRecvQueue.empty())
			{
				// ���в�Ϊ��
				int num = msgRecvQueue.front();
				cout << "����Ϣ������ȡ�� " << num << endl;
				msgRecvQueue.pop_front();
			}
			else
			{
				// ��Ϣ����Ϊ��
				cout << "��Ϣ����Ϊ�� " << endl;
			}
			LeaveCriticalSection(&my_winsec);	//	�뿪�ٽ���
#elif
			my_mutex.lock();
			if (!msgRecvQueue.empty())
			{
				// ���в�Ϊ��
				int num = msgRecvQueue.front();
				cout << "����Ϣ������ȡ�� " << num << endl;
				msgRecvQueue.pop_front();
				my_mutex.unlock();
			}
			else
			{
				// ��Ϣ����Ϊ��
				cout << "��Ϣ����Ϊ�� " << endl;
				my_mutex.unlock();
			}
#endif //  __WINDOWSJQ_
		}

		cout << "��Ϣ���ӽ���" << endl;
	}

	A()
	{
#ifdef __WINDOWSJQ_
		InitializeCriticalSection(&my_winsec);	//	���ٽ���֮ǰҪ��ʼ��
#endif // __WINDOWSJQ_

	}

private:
	list<int> msgRecvQueue;
	mutex my_mutex;

#ifdef __WINDOWSJQ_
	CRITICAL_SECTION my_winsec;	//	windows�е��ٽ������ǳ�����C++11�е�mutex
#endif // __WINDOWSJQ_

};

int main()
{
	A myobj;
	thread	myInMsgObj(&A::inMsgRecvQueue, &myobj);
	thread	myOutMsgObj(&A::outMsgRecvQueue, &myobj);
	myInMsgObj.join();
	myOutMsgObj.join();

	getchar();
	return 0;
}

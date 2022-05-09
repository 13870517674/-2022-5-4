#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
/*����
    ��֤ĳ����������ִֻ��һ��
    ����һ��flag���ڲ�ͨ����flag�ĸı������ƴ���ֻ����һ��

ע��
    ����ֻ����һ�ε�ǰ����ͬһ��flag�� ��ͬflagû�취�ﵽ���Ƶ�Ŀ��
    ����Ѿ����߳�ִ�й��ˣ����������̲߳�����ִ��
    ������߳�����ִ�У����������̻߳������ȴ�   
    �������ִ�е��߳��׳��쳣������ִ����ɣ������̻߳�����ִ��
*/

std::once_flag flag;

void Test(int &i) {
    std::call_once(flag, [&]()mutable {
        cout << i << endl;
        ++i;
        this_thread::sleep_for(chrono::milliseconds(100));//��������
        });
    cout << "exec end!!!" << endl; //ÿ���̶߳��������ȴ�call_once�ĺ���ִ�����
}

int main()
{
    int n = 1;
    vector<jthread> v(100);
    for (uint32_t i = 0; i < 10; i++) {
        v[i] = jthread(Test, std::ref(n));
    }
}
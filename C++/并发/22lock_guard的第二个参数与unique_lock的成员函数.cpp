#include<iostream>
#include<thread>
#include<mutex>
std::mutex myMutex1;
void G(int&i) { std::cout << i++ << std::endl; }
//lock_guard���Դ��ڶ���������
/*.1 std::adopt_lock��

    ��ʾ����������Ѿ���lock()��������Ҫ�ڹ��캯����lock����������ˡ�
    ǰ�᣺������ǰlock,����ᱨ�쳣
    ֮ǰ��lock_guard��Ҳ�������������*/
void test01() {
    int i = 0;          //�����iд��ȫ����ô�ͺû��ӡ��19����Ҫ�Ǵ˺�������һ���߳����е�ʱ������
    static std::mutex my_mutex;
    my_mutex.lock();    //Ҫ��lock()���������std::adopt_lock����
    std::unique_lock<std::mutex>A{ my_mutex,std::adopt_lock };
    for (int n = 0; n < 10; n++)G(i);
    std::chrono::milliseconds dura(100);//1��=1000����
    std::this_thread::sleep_for(dura);//��Ϣһ����ʱ��
    A.unlock(); //��д�ɲ�д����Ҫ�Ǳ�ʾ��������
}

/*2.2 std::try_to_lock��

    ������mutex��lock()ȥ�������mutex�������û�������ɹ������������أ��������������
    ʹ��try_to_lock��ԭ���Ƿ�ֹ�������߳�����mutex̫��ʱ�䣬���±��߳�һֱ������lock����ط�
    ǰ�᣺������ǰlock();  
    owns_locks()�����ж��Ƿ��õ��������õ�����true
    ���ǿ���ʹ��try_to_lock���̳߳��Ի�ȡ�������û�������ɹ����������������������ȥִ���������롣*/

void InMsg()noexcept
{
    auto id = std::this_thread::get_id();
    for (int i = 0; i < 10; i++) {
        std::unique_lock<std::mutex> guard(myMutex1, std::try_to_lock);
        if (guard.owns_lock())  //�ж��Ƿ��õ���
        {
            //std::chrono::microseconds time(100);
            //std::this_thread::sleep_for(time);
            std::cout << id << "push\n";
        }
        else
        {
            
            std::cout << id << "wait\n";
        }
    }
}

/*2.3 std::defer_lock��
    ���û�еڶ��������Ͷ�mutex���м���������defer_lock��ʼ����һ��û�м�����mutex
    ������������Ŀ�����Ժ���Ե���unique_lock��һЩ����
    ǰ�᣺������ǰlock*/
void test03() {                     //��Ա����lock()������unlock()����
    std::unique_lock<std::mutex>sbguard1(myMutex1,std::defer_lock);//û�м�����myMutex1
    sbguard1.lock();     
    for (int i = 0; i < 10; i++)
        std::cout << i << std::endl;
    sbguard1.unlock();//ֻ��ʾ��һ�£�û��Ҫһ������д
}
void test03_() {
    std::unique_lock<std::mutex>sbguard1(myMutex1);//ȥ����Щһ�����ԣ�ֻ�������Ը������
    for (int i = 0; i < 10; i++)
        std::cout << i << std::endl;
}

//try_lock()��Ա��������std::try_to_lock�е�����
void test04() {
    std::unique_lock<std::mutex>sbguard1(myMutex1,std::defer_lock);
    if (sbguard1.try_lock() == true)//����true��ʾ�õ�����          try_lock()Ҫ��std::defer_lock���ʹ��
    {
        //��������
        printf("�õ���\n");
    }
    else
    {
        printf("û�õ���\n");
        //û�õ�������Ĵ���
    }
}

//release()��Ա�������������������mutex����ָ�룬���ͷ�����Ȩ��Ҳ����˵�����unique_lock��mutex�����й�ϵ
void test05() {
    std::unique_lock<std::mutex>abguard1(myMutex1);
    std::mutex *ptx=abguard1.release();//�������������Լ��������myMutex1
    //ptx->lock();
    for (int i = 0; i < 10; i++)
        std::cout << i << std::endl;
    ptx->unlock();
}


//�ģ�unique_lock����Ȩ�Ĵ���mutex��
//std::unique_lock<std::mutex>sbguard1(myMutex1):  ����Ȩ����
//sbguard1ӵ��myMutex1������Ȩ
//subguard1���԰��Լ���mutex��myMutex1)������Ȩת�Ƹ�������unique_lock����
//���ԣ�unique_lock�������mutex������Ȩ���� ����ת�ƣ����ǲ��ܸ���
void test06() {
    std::unique_lock<std::mutex>abguard1(myMutex1);
    //std::unique_lock<std::mutex>abguard2(abguard1); //��������Ȩ������
    std::unique_lock<std::mutex>sbguard3(std::move(abguard1));//�ƶ����壬�൱��sbguard3��myMutex����һ��
                                                              //����sbguard1ָ���,sbguard3ָ��myMutex1
}

std::unique_lock<std::mutex>rtn_unique_lock()
{
    std::unique_lock<std::mutex>tmpguard(myMutex1);
    return tmpguard; //�Ӻ�������һ���ֲ���unique_lock�����ǿ��Եġ�
                     //�������־ֲ�����tmpguard�ᵼ��ϵͳ������ʱunique_lock���󣬲�����unique_lcok���ƶ����캯��
}

void test07() {
    std::unique_lock<std::mutex>sbguard = rtn_unique_lock();//�ڶ�������Ȩת�Ƶķ�ʽ
}

int main() {
    //std::jthread a(test01), a2(test01);
    
    //std::jthread b(InMsg),b2(InMsg);
    
    //std::jthread c(test03), c2(test03),c3(test03);

    //std::jthread d(test04), d2(test04);

    //std::jthread e(test05), e2(test05);

	return 0;
}
#include<iostream>
#include<Windows.h>
class CWinLock {
public:
    CWinLock(CRITICAL_SECTION* pCritmp)
    {
        my_winsec = pCritmp;
        EnterCriticalSection(my_winsec);
    }
    ~CWinLock()
    {
        LeaveCriticalSection(my_winsec);
    }
private:
    CRITICAL_SECTION* my_winsec;
};
//Windows�汾�������߼�������������ָ�����std::lock_guard�������ԭ��
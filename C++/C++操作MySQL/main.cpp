#include "MySQL.h"

int main()
{
	DataBase* d1 = new DataBase;
	//����
	d1->Connect("localhost", "root", "123456", "itcast", 0);
	printf("\n");
	//��ѯ��
	d1->Query("emp");
	printf("\n");
	//�������
	//d1->Implement("insert into emp(id,workno,name,gender,age,idcard,workaddress,entrydate) values(7,'0007','�����', '��', 20, '1235647895455','����','2005-11-08')");
	printf("\n");
	//��ѯ��
	d1->Query("emp");
	printf("\n");
	return 0;
}

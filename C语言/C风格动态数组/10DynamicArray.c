#include"DynamicArray.h"
//��ʼ��
Dynamic_Array* Array_Init(){
	//�����ڴ�
	Dynamic_Array* myArray = (Dynamic_Array*)malloc(sizeof(Dynamic_Array));
	//��ʼ��
	myArray->size = 0;
	myArray->capacity = 20;
	myArray->pAddr = malloc(sizeof(int) * myArray->capacity);
	return myArray;
}
//����
void Push_Back_Array(Dynamic_Array* arr, int value){
	if (arr == NULL) {
		return;
	}
	//�жϿռ��Ƿ��㹻
	if (arr->size==arr->capacity) {
		//��һ������һ�������ڴ�ռ� �¿ռ��Ǿɿռ������
		int* newSpace = malloc(sizeof(int) * arr->capacity * 2);
		//�ڶ��� �������ݵ��µĿռ�,Ҳ���ǰ�pAddr������newSpace
		memcpy(newSpace,arr->pAddr, arr->capacity * sizeof(int));
		//������ �ͷžɿռ���ڴ�
		free(arr->pAddr);
		//��������
		arr->capacity = arr->capacity * 2;
		arr->pAddr = newSpace;
	}
	arr->pAddr[arr->size] = value;
	arr->size++;
}
//����λ��ɾ��
void Remove_Array(Dynamic_Array* arr, int pos){
	if (arr == NULL) {
		return;
	//�ж�λ���Ƿ���Ч
	}
	if (pos < 0 || pos >= arr->size) {
		return;
	}
	//ɾ��Ԫ��
	for (int i = pos; i < arr->size-1; i++) {
		arr->pAddr[i] = arr->pAddr[i + 1];
	}
	arr->size--;
}
//����ֵɾ��
void RemoveByValue_Array(Dynamic_Array* arr, int value){
	if (arr == NULL) {
		return;
	}
	//�ҵ�ֵ��λ��
	int pos = Find_Array(arr, value);
	//ɾ��
	Remove_Array(arr, pos);
}
//����
int Find_Array(Dynamic_Array* arr, int value){
	if (arr == NULL) {
		return-1;
	}
	int pos = -1;
	for (int i = 0; i < arr->size; i++) {
		if (arr->pAddr[i] == value) {
			pos = i;
			break;
		}
	}
	return pos;
}
//��ӡ
void Print_Array(Dynamic_Array* arr){
	if (arr == NULL) {
		return;
	}
	for (int i = 0; i < arr->size; i++) {
		printf("%d", arr->pAddr[i]);
	}
	printf("\n");
}
//�ͷŶ�̬������ڴ�
void FreeSpace_Array(Dynamic_Array* arr){
	if (arr == NULL) {
		return;
	}
	if (arr->pAddr != NULL) {
		free(arr->pAddr);
		arr->pAddr = NULL;
	}
	//free(arr);
	//arr = NULL;
}
//�������
void Clear_Array(Dynamic_Array* arr) {
	if (arr == NULL) {
		return;
	}
	arr->size = 0;
}
//��ȡ��̬���������
int Cappcity_Array(Dynamic_Array* arr) {
	if (arr == NULL) {
		return-1;
	}
	return arr->capacity;
}
//��ö�̬���鵱ǰԪ�ظ���
int Size_Array(Dynamic_Array* arr) {
	if (arr == NULL) {
		return-1;
	}
	return arr->size;
}
//����λ�û�ȡĳ��λ��Ԫ��
int At_Array(Dynamic_Array* arr, int poa) {
	return arr->pAddr[poa];
}
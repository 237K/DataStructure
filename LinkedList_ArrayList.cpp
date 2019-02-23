//
//	OS Windows
//	2019.02.23
//
//	[자료구조]
//
//		<1. Linked List>
//			1) 배열 기반 리스트
//
#include <iostream>
#include <cstdio>
using namespace std;

const static int LIST_LEN = 100;

template <typename T>
class List
{
private:
	T arr[LIST_LEN];
	int NumOfData;
	int CurPosition;
public:
	void ListInit(List *plist);
	void ListInsert(List* plist, T data);
	int ListFirst(List* plist, T* pdata);
	int ListNext(List* plist, T* pdata);
	T ListRemove(List* plist);
	int ListCount(List* plist);
};

template <typename T>
void List<T>::ListInit(List *plist)
{
	(plist->NumOfData) = 0;
	(plist->CurPosition) = -1;
}

template <typename T>
void List<T>::ListInsert(List* plist, T data)
{
	if (plist->NumOfData >= LIST_LEN)
	{
		puts("더 이상 저장할 수 없습니다.\n");
		return;
	}
	(plist->arr[plist->NumOfData]) = data;
	(plist->NumOfData++);
}

template <typename T>
int List<T>::ListFirst(List* plist, T* pdata)
{
	if (plist->NumOfData == 0)
		return 0;
	
	(plist->CurPosition) = 0;
	*pdata = plist->arr[0];
	return 1;
}

template <typename T>
int List<T>::ListNext(List *plist, T* pdata)
{
	if (plist->CurPosition >= (plist->NumOfData) - 1)
		return 0;

	(plist->CurPosition)++;
	*pdata = plist->arr[plist->CurPosition];
	return 1;
}

template <typename T>
T List<T>::ListRemove(List* plist)
{
	int temp_pos = plist->CurPosition;
	int num = plist->NumOfData;
	T temp_data = plist->arr[temp_pos];
	for (int i = temp_pos; i < num; ++i)
		plist->arr[i] = plist->arr[i + 1];

	(plist->CurPosition)--;
	(plist->NumOfData)--;
	return temp_data;
}

template <typename T>
int List<T>::ListCount(List* plist)
{
	return plist->NumOfData;
}

int main(int argc, char** argv)
{
	List<int> list;

	list.ListInit(&list);
	list.ListInsert(&list, 11);
	list.ListInsert(&list, 22);
	list.ListInsert(&list, 33);

	printf("Number Of Data : %d\n", list.ListCount(&list));

	int data;
	if (list.ListFirst(&list, &data))
	{
		printf("%d ", data);

		while (list.ListNext(&list, &data))
			printf("%d ", data);
	}
	printf("\n\n");

	printf("22찾아서 삭제\n\n");
	if (list.ListFirst(&list, &data))
	{
		if (data == 22)
			list.ListRemove(&list);
		while (list.ListNext(&list, &data))
		{
			if (data == 22)
				list.ListRemove(&list);
		}
	}

	printf("Number Of Data : %d\n", list.ListCount(&list));
	if (list.ListFirst(&list, &data))
	{
		printf("%d ", data);

		while (list.ListNext(&list, &data))
			printf("%d ", data);
	}
	printf("\n\n");

	return 0;
}
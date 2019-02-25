//
//	OS Windows
//	2019.02.23
//
//	[�ڷᱸ��]
//		<1. Linked List>
//			1) �迭 ��� ����Ʈ
//			2) Linked List�� �⺻ ����. ��ü �帧�� ���� ����
//			3) Linked List ADT ����
//				a) void Init(List* plist)
//				b) void Insert(List* plist, T data)
//				c) int First(List* plist, T* pdata)		����Ʈ ù ��° �����͸� pdata�� ����Ű�� �޸𸮿� ����. ���� ���� �� TRUE(1), ���� �� FALSE(0) ��ȯ
//				d) int Next(List* plist, T* pdata)
//				e) T Remove(List* plist)
//				f) int Count(List* plist)
//				g) void SetSortRule(List* plist, int (*comp)(T d1, T d2))	//������ ������ �Ǵ� �Լ� ���
//

#include <cstdio>
using namespace std;

template <typename T>
class Node
{
public:
	T data;
	Node *next;
};

template <typename T>
class LinkedList
{
public:
	Node<T> *head;
	Node<T> *cur;
	Node<T> *before;
	int NumOfdata;
	int (*comp)(T d1, T d2);
public:
	void Init(LinkedList* plist);
	void Insert(LinkedList* plist, T data);
	void HeadInsert(LinkedList* plist, T data);
	void SortInsert(LinkedList* plist, T data);
	int First(LinkedList* plist, T* data);
	int Next(LinkedList* plist, T* data);
	T Remove(LinkedList* plist);
	int Count(LinkedList* plist);
	void SetSortRule(LinkedList* plist, int (*comp)(T d1, T d2));
};

template <typename T>
void LinkedList<T>::Init(LinkedList* plist)
{
	plist->head = new Node<T>;				//dummy ��� ����
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->NumOfdata = 0;
}

template <typename T>
void LinkedList<T>::Insert(LinkedList* plist, T data)
{
	if (plist->comp == NULL)
		HeadInsert(plist, data);		//Head�� �����ϴ� �Լ�
	else
		SortInsert(plist, data);		//���ı����� ������� �����ϴ� �Լ�
}

template <typename T>
void LinkedList<T>::HeadInsert(LinkedList* plist, T data)
{
	Node<T> *newNode = new Node<T>;					//���ο� ��带 �����
	newNode->data = data;						//�� ��忡 �����͸� �ְ�
	newNode->next = plist->head->next;			//���ο� ����� next���� ���� head�� next�� ����Ű�� �ִ� ��带 ����Ű���� �ϰ�
	plist->head->next = newNode;				//head����� next(���̳��)�� ���ο� ��带 ����Ű���� �ϰ�
	(plist->NumOfdata)++;						//������ ���� ����
}

template <typename T>
void LinkedList<T>::SortInsert(LinkedList* plist, T data)
{
	Node<T> *newNode = new Node<T>;
	Node<T> *pred = plist->head;
	newNode->data = data;

	while (pred->next != NULL && plist->comp(data, pred->next->data) != 0)
	{
		pred = pred->next;
	}

	newNode->next = pred->next;
	pred->next = newNode;

	(plist->NumOfdata)++;
}

template <typename T>
int LinkedList<T>::First(LinkedList* plist, T* pdata)
{
	if (plist->head->next == NULL)				//���̳�尡 ����Ű�°� NULL�̸� 
		return 0;								//��ȯ�� ������ ����

	plist->before = plist->head;				//before��尡 ���̳�带 ����Ű�� �ϰ�
	plist->cur = plist->head->next;				//cur��尡 ���̳�尡 ����Ű�� ���(ù ��° ���)�� ����Ű���� ��

	*pdata = plist->cur->data;					//ù ��° ����� ������ ����
	return 1;
}

template <typename T>
int LinkedList<T>::Next(LinkedList* plist, T* pdata)
{
	if (plist->cur->next == NULL)
		return 0;

	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*pdata = plist->cur->data;
	return 1;
}

template <typename T>
T LinkedList<T>::Remove(LinkedList* plist)
{
	Node<T> *tempNode = plist->cur;				//�ӽó�忡 cur��� ����
	T tempData = tempNode->data;				//�ӽú����� cur��� ������ ����

	plist->before->next = plist->cur->next;		//cur����� next�� before����� next�� ����Ű�� ��带 ����Ű���� ��
	plist->cur = plist->before;					//cur��尡 before��尡 ����Ű�� ��带 ����Ű���� ��

	delete tempNode;							//����
	(plist->NumOfdata)--;						//������ ���� ���̳ʽ�
	return tempData;							//������ ������ ��ȯ
}

template <typename T>
int LinkedList<T>::Count(LinkedList* plist)
{
	return plist->NumOfdata;
}

template <typename T>
void LinkedList<T>::SetSortRule(LinkedList* plist, int(*comp)(T d1, T d2))
{
	plist->comp = comp;
}

int Predicate(int d1, int d2)
{
	if (d1 < d2)
		return 0;
	else
		return 1;        
}

int main(void)
{
	LinkedList<int> LL;
	int data;
	LL.Init(&LL);
	LL.SetSortRule(&LL, Predicate);
	LL.Insert(&LL, 11);
	LL.Insert(&LL, 22);
	LL.Insert(&LL, 11);
	LL.Insert(&LL, 22);
	LL.Insert(&LL, 33);

	printf("Count : %d\n", LL.Count(&LL));
	if (LL.First(&LL, &data))
	{
		printf("%d ", data);
		while (LL.Next(&LL, &data))
		{
			printf("%d ", data);
		}
	}
	printf("\n\n");

	if (LL.First(&LL, &data))
	{
		if (data == 22)
			LL.Remove(&LL);
		while (LL.Next(&LL, &data))
		{
			if (data == 22)
				LL.Remove(&LL);
		}
	}

	printf("Count : %d\n", LL.Count(&LL));
	if (LL.First(&LL, &data))
	{
		printf("%d ", data);
		while (LL.Next(&LL, &data))
		{
			printf("%d ", data);
		}
	}
	printf("\n\n");

	return 0;
}
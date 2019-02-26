//
//	OS Windows
//	2019.02.24
//
//	[�ڷᱸ��]
//		<1. Linked List>
//		<2. Circular Linked List>
//			1) ������ ����Ű�� �����ͺ��� : tail, �Ӹ��� ����Ű�� �����ͺ��� : tail->next
//			2) �������Ḯ��Ʈ ADT ����
//				a) void Init()
//				b) void InsertFront(T data)
//				c) void InsertBack(T data)
//				d) int First(T* pdata)
//				e) int Next(T* pdata)
//				f) T Remove()
//				g) int Count()

#include <iostream>
using namespace std;

template <typename T>
class Node
{
private:
	T data;
	Node* next;
};

template <typename T>
class CLL
{
private:
	Node<T>* tail;
	Node<T>* cur;
	Node<T>* before;
	int numOfdata;
public:
	void Init();
	void InsertBack(T data);
	void InsertFront(T data);
	int First(T* data);
	int Next(T* data);
	T Remove();
	int Count();
};

template <typename T>
void CLL<T>::Init()
{
	tail = NULL;
	cur = NULL;
	before = NULL;
	numOfdata = 0;
}

template <typename T>
void CLL<T>::InsertFront(T data)
{
	Node<T>* newNode = new Node<T>*;
	newNode->data = data;
	if (tail == NULL)
	{
		tail = newNode;
		newNode->next = newNode;
	}
	else
	{
		newNode->next = tail->next;
		tail->next = newNode;
	}
	numOfdata++;
}

template <typename T>
void CLL<T>::InsertBack(T data)
{
	Node<T>* newNode = new Node<T>*;
	newNode->data = data;
	if (tail == NULL)
	{
		tail = newNode;
		newNode->next = newNode;
	}
	else
	{
		newNode->next = tail->next;
		tail->next = newNode;
		tail = newNode;
	}
	numOfdata++;
}


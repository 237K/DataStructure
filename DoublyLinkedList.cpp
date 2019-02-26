//
//	OS Windows
//	2019.02.26
//
//	[자료구조]
//		<1. Linked List>
//		<2. Circular Linked List>
//		<3. Doubly Linked List>
//			1) 더미노드가 없는 양방향 연결 리스트 ADT 정의
//				a) void Init()
//				b) void Insert(T data)
//				c) int First(T* pdata)
//				d) int Next(T* pdata)
//				e) int Previous(T* pdata)
//				f) int Count()
//

#include <cstdio>
#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
	T data;
	Node<T>* next;
	Node<T>* prev;
};

template <typename T>
class DLL
{
private:
	Node<T>* head;
	Node<T>* cur;
	int numOfdata;
public:
	void Init();
	void Insert(T data);
	int First(T* pdata);
	int Next(T* pdata);
	int Previous(T* pdata);
	int Count();
};

template <typename T>
void DLL<T>::Init()
{
	head = NULL;
	numOfdata = 0;
}

template <typename T>
void DLL<T>::Insert(T data)
{
	Node<T> *newNode = new Node<T>;
	newNode->data = data;
	if (head == NULL)
	{
		head = newNode;
		newNode->next = NULL;
		newNode->prev = NULL;
	}
	else
	{
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
		newNode->prev = NULL;
	}
	numOfdata++;
}

template <typename T>
int DLL<T>::First(T* pdata)
{
	if (head == NULL)
		return 0;
	else
	{
		cur = head;
		*pdata = cur->data;
		return 1;
	}
}

template <typename T>
int DLL<T>::Next(T* pdata)
{
	if (cur->next == NULL)
		return 0;
	else
	{
		cur = cur->next;
		*pdata = cur->data;
		return 1;
	}
}

template <typename T>
int DLL<T>::Previous(T* pdata)
{
	if (cur->prev == NULL)
		return 0;
	else
	{
		cur = cur->prev;
		*pdata = cur->data;
		return 1;
	}
}

template <typename T>
int DLL<T>::Count()
{
	return numOfdata;
}

int main(void)
{
	DLL<int> dll;
	int data;
	dll.Init();

	for (int i = 1; i <= 8; ++i)
		dll.Insert(i);

	if (dll.First(&data))
	{
		cout<<data<<' ';
		while (dll.Next(&data))
		{
			cout << data << ' ';
		}

		while (dll.Previous(&data))
		{
			cout << data << ' ';
		}
	}
	cout << endl << endl;
	return 0;
}
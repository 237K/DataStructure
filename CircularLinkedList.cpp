//
//	OS Windows
//	2019.02.24
//
//	[자료구조]
//		<1. Linked List>
//		<2. Circular Linked List>
//			1) 꼬리를 가리키는 포인터변수 : tail, 머리를 가리키는 포인터변수 : tail->next
//			2) 원형연결리스트 ADT 정의
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
public:
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
	int First(T* pdata);
	int Next(T* pdata);
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
	Node<T>* newNode = new Node<T>;
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
	Node<T>* newNode = new Node<T>;
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

template <typename T>
int CLL<T>::First(T* pdata)
{
	if (tail == NULL)
		return 0;
	else
	{
		cur = tail->next;
		before = tail;
		*pdata = cur->data;
		return 1;
	}
}

template <typename T>
int CLL<T>::Next(T* pdata)
{
	if (tail == NULL)
		return 0;
	else
	{
		before = cur;
		cur = cur->next;
		*pdata = cur->data;
		return 1;
	}
}

template <typename T>
T CLL<T>::Remove()
{
	Node<T>* tempNode = cur;
	T tempData = cur->data;

	if (tempNode == tail)
	{
		if (tail == tail->next)
		{
			tail = NULL;
		}
		else
		{
			tail = before;
		}
	}

	before->next = cur->next;
	cur = before;

	delete tempNode;
	numOfdata--;

	return tempData;
}

template <typename T>
int CLL<T>::Count()
{
	return numOfdata;
}

int main(void)
{
	CLL<int> cll;
	int data, i, nodeNum;
	cll.Init();

	cll.InsertBack(3);
	cll.InsertBack(4);
	cll.InsertBack(5);

	cll.InsertFront(2);
	cll.InsertFront(1);

	cout << "원형연결리스트이므로 무한 반복 출력할 수 있음. 3번 연속 출력" << endl;
	if (cll.First(&data))
	{
		cout << data << ' ';
		for (i = 0; i < cll.Count() * 3-1; ++i)
		{
			if (cll.Next(&data))
				cout << data << ' ';
		}
		cout << endl;
	}
	cout << endl<<endl;
	cout << "=========2의 배수 삭제=========" << endl;
	nodeNum = cll.Count();

	if (nodeNum != 0)
	{
		if (cll.First(&data))
		{
			if (data % 2 == 0)
				cll.Remove();
		}
		for (i = 0; i < nodeNum; ++i)
		{
			if (cll.Next(&data))
			{
				if (data % 2 == 0)
					cll.Remove();
			}
		}
	}

	if (cll.First(&data))
	{
		cout << data << ' ';
		for (i = 0; i < cll.Count()-1; ++i)
		{
			if (cll.Next(&data))
				cout << data << ' ';
		}
		cout << endl;
	}

	return 0;
}
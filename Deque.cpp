//
//	OS Windows
//	2019.03.01
//
//	[자료구조]
//		<1. Linked List>
//		<2. Circular Linked List>
//		<3. Doubly Linked List>
//		<4. Stack>
//		<5. Queue>
//		<6. Deque>
//			1) 'Double-ended queue' 앞뒤로 넣고 뺄 수 있음. 따라서 양방향 연결 리스트로 구현하기에 적합함
//			2) ADT 정의
//				a) void Init()
//				b) bool Empty()
//				c) void DQPushFront(T data)
//				d) void DQPushBack(T data)
//				e) T DQPopFront()
//				f) T DQPopBack()
//				g) T DQFront()
//				h) T DQBack()
//			

#include <iostream>
#include <cstdio>
using namespace std;

template <typename T>
class Node
{
public:
	T data;
	Node<T> *next;
	Node<T> *back;
};

template <typename T>
class Deque
{
private:
	Node<T> *head;
	Node<T> *tail;
public:
	void Init();
	bool Empty();
	void DQPushFront(T data);
	void DQPushBack(T data);
	T DQPopFront();
	T DQPopBack();
	T DQFront();
	T DQBack();
};
template <typename T>
void Deque<T>::Init()
{
	head = new Node<T>;		//더미생성
	tail = new Node<T>;		//더미생성
	head->next = tail;
	tail->back = head;
}
template <typename T>
bool Deque<T>::Empty()
{
	if (head->next == tail)
		return true;
	else
		return false;
}
template <typename T>
void Deque<T>::DQPushFront(T data)
{
	Node<T> *newNode = new Node<T>;
	newNode->data = data;
	head->next->back = newNode;
	newNode->next = head->next;
	head->next = newNode;
	newNode->back = head;
}

template <typename T>
void Deque<T>::DQPushBack(T data)
{
	Node<T> *newNode = new Node<T>;
	newNode->data = data;
	newNode->back = tail->back;
	tail->back->next = newNode;
	newNode->next = tail;
	tail->back = newNode;
}

template <typename T>
T Deque<T>::DQPopFront()
{
	if (head->next == tail)
	{
		cout << "Queue Memory Error" << endl;
		exit(-1);
	}
	else
	{
		Node<T> *tempNode = head->next;
		T tempData = tempNode->data;
		head->next->next->back = head;
		head->next = head->next->next;
		delete tempNode;
		return tempData;
	}
}

template <typename T>
T Deque<T>::DQPopBack()
{
	if (tail->back == head)
	{
		cout << "Queue Memory Error" << endl;
		exit(-1);
	}
	else
	{
		Node<T> *tempNode = tail->back;
		T tempData = tempNode->data;
		tail->back->back->next = tail;
		tail->back = tail->back->back;
		delete tempNode;
		return tempData;
	}
}

template <typename T>
T Deque<T>::DQFront()
{
	return head->next->data;
}

template <typename T>
T Deque<T>::DQBack()
{
	return tail->back->data;
}

int main(void)
{
	Deque<int> DQ;
	DQ.Init();

	for (int i = 1; i < 6; ++i)
		DQ.DQPushFront(i);

	for (int i = 100; i > 94; --i)
		DQ.DQPushBack(i);

	while (!DQ.Empty())
		cout << DQ.DQPopFront() << ' ';
	cout << endl << endl;

	for (int i = 1; i < 6; ++i)
		DQ.DQPushFront(i);

	for (int i = 100; i > 94; --i)
		DQ.DQPushBack(i);

	while (!DQ.Empty())
		cout << DQ.DQPopBack() << ' ';
	cout << endl << endl;
	return 0;
}
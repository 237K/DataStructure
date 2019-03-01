//
//	OS Windows
//	2019.02.28
//
//	[자료구조]
//		<1. Linked List>
//		<2. Circular Linked List>
//		<3. Doubly Linked List>
//		<4. Stack>
//		<5. Queue>
//			1) ADT 정의
//				a) void QInit()
//				b) bool Empty()
//				c) void enqueue(T data)
//				d) T dequeue()
//				e) T QFront()
//			2) (*Circular queue) 배열 기반 큐 구현
//				a) 제일 앞을 가리키는 F, 제일 뒤를 가리키는 R이 필요
//				b) enqueue 시 R을 한 칸 이동시키고, 그 자리에 데이터 저장
//				c) dequeue 시 F를 한 칸 이동시키고, 그 자리의 데이터 반환 및 삭제
//				d) R이 배열의 끝에 위치한 경우 배열의 처음으로 이동시킴
//				e) 배열에 데이터를 꽉 채울 경우, 가득찬 경우와 비어있는 경우 모두 F가 R보다 한 칸 앞서므로 구분할 수 없음
//				f) 때문에 F 자리에 데이터를 비워둠으로써 배열이 가득찬 경우에는 F가 R보다 한 칸 앞서고, 비어있는 경우에는 F랑 R이 같은 곳을 가리킴
//		  → 3) 연결리스트 기반 큐 구현

#include <cstdio>
#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
	T data;
	Node<T> *next;
};

template <typename T>
class Queue
{
private:
	Node<T>* first;
	Node<T>* rear;
public:
	void QInit();
	bool Empty();
	void enqueue(T data);
	T dequeue();
	T QFront();
	T QBack();
};

template <typename T>
void Queue<T>::QInit()
{
	first = NULL;
	rear = NULL;
}

template <typename T>
bool Queue<T>::Empty()
{
	if (first == NULL)
		return true;
	else
		return false;
}

template <typename T>
void Queue<T>::enqueue(T data)
{
	Node<T> *newNode = new Node<T>;
	newNode->next = NULL;
	newNode->data = data;
	if (first == NULL)
	{
		first = newNode;
		rear = newNode;
	}
	else
	{
		rear->next = newNode;
		rear = newNode;
	}
}

template <typename T>
T Queue<T>::dequeue()
{
	if (first == NULL)
	{
		cout << "Empty!" << endl;
		exit(-1);
	}
	else
	{
		Node<T> *tempNode = first;
		T tempData = first->data;
		first = first->next;			//if(first->next == NULL)일 경우 first에 NULL이 저장되므로 OK.
		delete tempNode;
		return tempData;
	}
}

template <typename T>
T Queue<T>::QFront()
{
	if (first == NULL)
	{
		cout << "Empty!" << endl;
		exit(-1);
	}
	else
	{
		return first->data;
	}
}

template <typename T>
T Queue<T>::QBack()
{
	if (first == NULL)
	{
		cout << "Empty!" << endl;
		exit(-1);
	}
	else
	{
		return rear->data;
	}
}

int main(void)
{
	Queue<int> Q;
	Q.QInit();

	for (int i = 1; i < 6; ++i)
		Q.enqueue(i);

	cout << "Front : " << Q.QFront() << endl;
	cout << "Back : " << Q.QBack() << endl<<endl;

	while (!Q.Empty())
		cout << Q.dequeue() << ' ';

	cout << endl << endl;
	return 0;
}
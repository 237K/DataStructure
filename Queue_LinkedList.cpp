//
//	OS Windows
//	2019.02.28
//
//	[�ڷᱸ��]
//		<1. Linked List>
//		<2. Circular Linked List>
//		<3. Doubly Linked List>
//		<4. Stack>
//		<5. Queue>
//			1) ADT ����
//				a) void QInit()
//				b) bool Empty()
//				c) void enqueue(T data)
//				d) T dequeue()
//				e) T QFront()
//			2) (*Circular queue) �迭 ��� ť ����
//				a) ���� ���� ����Ű�� F, ���� �ڸ� ����Ű�� R�� �ʿ�
//				b) enqueue �� R�� �� ĭ �̵���Ű��, �� �ڸ��� ������ ����
//				c) dequeue �� F�� �� ĭ �̵���Ű��, �� �ڸ��� ������ ��ȯ �� ����
//				d) R�� �迭�� ���� ��ġ�� ��� �迭�� ó������ �̵���Ŵ
//				e) �迭�� �����͸� �� ä�� ���, ������ ���� ����ִ� ��� ��� F�� R���� �� ĭ �ռ��Ƿ� ������ �� ����
//				f) ������ F �ڸ��� �����͸� ��������ν� �迭�� ������ ��쿡�� F�� R���� �� ĭ �ռ���, ����ִ� ��쿡�� F�� R�� ���� ���� ����Ŵ
//		  �� 3) ���Ḯ��Ʈ ��� ť ����

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
		first = first->next;			//if(first->next == NULL)�� ��� first�� NULL�� ����ǹǷ� OK.
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
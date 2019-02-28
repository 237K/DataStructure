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
//

#include <cstdio>
#include <iostream>
using namespace std;

const static int QLEN = 100;

template <typename T>
class Queue
{
private:
	int front;
	int rear;
	T QArray[QLEN];
public:
	void QInit();
	bool Empty();
	void enqueue(T data);
	T dequeue();
	T QFront();
	int NextIdx(int _idx);
};

template <typename T>
int Queue<T>::NextIdx(int _idx)
{
	if (_idx == QLEN - 1)			//R�� �迭 �������� ����Ű�� ������,
		return 0;					//�迭�� ó������ ���ư�
	else
	{
		return _idx + 1;
	}
}
template <typename T>
void Queue<T>::QInit()
{
	front = 0;
	rear = 0;
}

template <typename T>
bool Queue<T>::Empty()
{
	if (front == rear)
		return true;
	else
		return false;
}

template <typename T>
void Queue<T>::enqueue(T data)
{
	if (NextIdx(rear) == front)
	{
		cout << "(Error) Full!" << endl;
		return;
	}
	else
	{
		cout << "front : " << front << endl;
		cout << "rear : " << rear << endl;
		rear = NextIdx(rear);
		QArray[rear] = data;
	}
}

template <typename T>
T Queue<T>::dequeue()
{
	if (front == rear)
	{
		cout << "(Error) Empty!" << endl;
		exit(-1);
	}
	else
	{
		cout << "front : " << front << endl;
		cout << "rear : " << rear << endl;
		front = NextIdx(front);
		return QArray[front];
	}
}

template <typename T>
T Queue<T>::QFront()
{
	if (front == rear)
	{
		cout << "(Error) Empty!" << endl;
		exit(-1);
	}
	else
	{
		return QArray[NextIdx(front)];
	}
}

int main(void)
{
	Queue<int> Q;
	Q.QInit();

	for (int i = 1; i < 6; ++i)
		Q.enqueue(i);

	while (!Q.Empty())
		cout << Q.dequeue() << endl;
	
	cout << endl << endl;
	return 0;
}
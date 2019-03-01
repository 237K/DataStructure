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
//			2) (*Circular queue) �迭 ��� ť ����
//			3) ���Ḯ��Ʈ ��� ť ����
//		  �� 4) ť�� Ȱ���� �ùķ��̼�
//				a) �մԵ��� ���� ������ ������� ��. ������ �����ο��� �󸶳� �Ǿ�� ���� ȿ������ �� �ùķ��̼� �غ��� �Ǵ��ϰ��� ��
//				b) ���ɽð� 1�ð� ���� ���� 15�ʴ� 1�� �� �ֹ���
//				c) ġ����� 12�� / �Ұ����� 15�� / ������� 24��
//				d) ��� ���� �������� �޴��� ������
//				e) �ܹ��Ÿ� ����� ����� 1��. �ֹ��� �޴��� ���� ���� ���� ���ǿ��� ���� �����
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <time.h>
using namespace std;

const static int QLEN = 100;				//Q�� ũ�Ⱑ ������ �ִ� ���밡�� �ο�

const static int ORDER_TERM = 15;

enum BURGER { CHEESE = 0, BULGOGI = 1, DOUBLE = 2 };

const static int CHEESE_TERM = 12;
const static int BULGOGI_TERM = 15;
const static int DOUBLE_TERM = 24;

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
		cout << "Waiting room is Full!" << endl;
		return;
	}
	else
	{
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

	int make_process = 0;
	int cheese_order = 0;
	int bulgogi_order = 0;
	int double_order = 0;
	int second = 0;

	srand(time(NULL));

	for (second = 0; second < 3600; ++second)
	{
		if (second % ORDER_TERM == 0)			//15�ʿ� �� �� �� �ֹ� �޴µ�
		{
			switch (BURGER(rand() % 3))			//���� ������ ����
			{
			case CHEESE:					
				Q.enqueue(CHEESE_TERM);			//Q�� �� ���� ����� �ð��� ����
				cheese_order++;
				break;
			case BULGOGI:
				Q.enqueue(BULGOGI_TERM);
				bulgogi_order++;
				break;
			case DOUBLE:
				Q.enqueue(DOUBLE_TERM);
				double_order++;
				break;
			}
		}

		if (make_process <= 0 && !Q.Empty())	//���� ����� �ִ°� ����, �ֹ��� �׿� ������
		{
			make_process = Q.dequeue();			//���� ���� �ֹ��� ������ ����� ������. �ֹ��� ���� ���ǿ��� ���ͼ� ��ٸ�
		}
		make_process--;							//1�ʰ� ������ ���� ���۵� 1�ʸ�ŭ �����
	}

	cout << "[Simulation]" << endl;
	cout << "Waiting room size : " << QLEN << endl;
	cout << "  1. Cheese burger : " << cheese_order << endl;
	cout << "  2. Bulgogi burger : " << bulgogi_order << endl;
	cout << "  3. Double burger : " << double_order << endl<<endl;

	return 0;
}
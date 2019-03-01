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
//			2) (*Circular queue) 배열 기반 큐 구현
//			3) 연결리스트 기반 큐 구현
//		  → 4) 큐를 활용한 시뮬레이션
//				a) 손님들을 위한 대기실을 만들고자 함. 대기실의 수용인원이 얼마나 되어야 가장 효과적일 지 시뮬레이션 해보고 판단하고자 함
//				b) 점심시간 1시간 동안 고객이 15초당 1명 씩 주문함
//				c) 치즈버거 12초 / 불고기버거 15초 / 더블버거 24초
//				d) 모든 고객은 무작위로 메뉴를 선택함
//				e) 햄버거를 만드는 사람은 1명. 주문한 메뉴를 받을 다음 고객은 대기실에서 나와 대기함
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <time.h>
using namespace std;

const static int QLEN = 100;				//Q의 크기가 대기실의 최대 수용가능 인원

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
	if (_idx == QLEN - 1)			//R이 배열 마지막을 가리키고 있으면,
		return 0;					//배열의 처음으로 돌아감
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
		if (second % ORDER_TERM == 0)			//15초에 한 번 씩 주문 받는데
		{
			switch (BURGER(rand() % 3))			//버거 종류에 따라
			{
			case CHEESE:					
				Q.enqueue(CHEESE_TERM);			//Q에 각 버거 만드는 시간을 넣음
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

		if (make_process <= 0 && !Q.Empty())	//지금 만들고 있는게 없고, 주문이 쌓여 있으면
		{
			make_process = Q.dequeue();			//먼저 들어온 주문을 꺼내서 만들기 시작함. 주문한 고객은 대기실에서 나와서 기다림
		}
		make_process--;							//1초가 지나면 버거 제작도 1초만큼 진행됨
	}

	cout << "[Simulation]" << endl;
	cout << "Waiting room size : " << QLEN << endl;
	cout << "  1. Cheese burger : " << cheese_order << endl;
	cout << "  2. Bulgogi burger : " << bulgogi_order << endl;
	cout << "  3. Double burger : " << double_order << endl<<endl;

	return 0;
}
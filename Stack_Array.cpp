//
//	OS Windows
//	2019.02.27
//
//	[자료구조]
//		<1. Linked List>
//		<2. Circular Linked List>
//		<3. Doubly Linked List>
//		<4. Stack>
//			1) ADT 정의
//				a) void Init()
//				b) bool Empty()
//				c) void Push(T data)	매개변수 data로 전달된 값을 저장
//				d) T Pop()				데이터가 하나 이상 존재함이 보장되어야 함. 마지막에 저장된 요소 삭제 및 반환
//				e) T Top()				데이터가 하나 이상 존재함이 보장되어야 함. 마지막에 저장된 요소 반환
//			2) 배열 기반 스택 구현
//

#include <cstdio>
#include <iostream>
using namespace std;

const static int STACK_LEN = 100;

template <typename T>
class Stack
{
private:
	int topIdx;
	T StackArray[STACK_LEN];
public:
	void Init();
	bool Empty();
	void Push(T data);
	T Pop();
	T Top();
};

template <typename T>
void Stack<T>::Init()
{
	topIdx = -1;
}

template <typename T>
bool Stack<T>::Empty()
{
	if (topIdx == -1)
		return true;
	else
		return false;
}

template <typename T>
void Stack<T>::Push(T data)
{
	topIdx++;
	StackArray[topIdx] = data;
}

template <typename T>
T Stack<T>::Pop()
{
	if (Empty())
	{
		cout << "Stack Memory Error" << endl;
		exit(-1);
	}
	else
	{
		T temp = StackArray[topIdx];
		topIdx--;
		return temp;
	}
}

template <typename T>
T Stack<T>::Top()
{
	if (Empty())
	{
		cout << "Stack Memory Error" << endl;
		exit(-1);
	}
	else
		return StackArray[topIdx];
}

int main(void)
{
	Stack<int> stack;
	stack.Init();

	for (int i = 1; i <= 5; ++i)
		stack.Push(i);

	while (!stack.Empty())
		cout << stack.Pop() << endl;

	return 0;
}
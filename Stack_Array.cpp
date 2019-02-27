//
//	OS Windows
//	2019.02.27
//
//	[�ڷᱸ��]
//		<1. Linked List>
//		<2. Circular Linked List>
//		<3. Doubly Linked List>
//		<4. Stack>
//			1) ADT ����
//				a) void Init()
//				b) bool Empty()
//				c) void Push(T data)	�Ű����� data�� ���޵� ���� ����
//				d) T Pop()				�����Ͱ� �ϳ� �̻� �������� ����Ǿ�� ��. �������� ����� ��� ���� �� ��ȯ
//				e) T Top()				�����Ͱ� �ϳ� �̻� �������� ����Ǿ�� ��. �������� ����� ��� ��ȯ
//			2) �迭 ��� ���� ����
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
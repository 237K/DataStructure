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
//		  → 3) 연결리스트 기반 스택 구현
//				- head쪽에 새로운 노드를 삽입하는 형태의 연결리스트는 stack과 흡사함
//				────────		────────		────────		────────
//			   │  head  │	→  │  Node  │	→  │  Node  │	→  │  Node  │
//				────────		────────		────────		────────
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
};

template <typename T>
class Stack
{
private:
	Node<T>* head;
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
	head = NULL;
}

template <typename T>
bool Stack<T>::Empty()
{
	if (head == NULL)
		return true;
	else
		return false;
}

template <typename T>
void Stack<T>::Push(T data)
{
	Node<T>* newNode = new Node<T>;
	newNode->data = data;

	newNode->next = head;
	head = newNode;
}

template <typename T>
T Stack<T>::Pop()
{
	if (head == NULL)
	{
		cout << "Stack Memory Error" << endl;
		exit(-1);
	}
	else
	{
		Node<T>* tempNode = head;
		T tempData = head->data;
		head = head->next;
		delete tempNode;
		return tempData;
	}
}

template <typename T>
T Stack<T>::Top()
{
	if (head == NULL)
	{
		cout << "Stack Memory Error" << endl;
		exit(-1);
	}
	else
	{
		return head->data;
	}
}

int main(void)
{
	Stack<int> stack;
	stack.Init();

	for (int i = 1; i <= 5; ++i)
		stack.Push(i);

	while (!stack.Empty())
		cout << stack.Pop() << ' ';
	cout << endl << endl;
	return 0;
}
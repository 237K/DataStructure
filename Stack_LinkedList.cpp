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
//		  �� 3) ���Ḯ��Ʈ ��� ���� ����
//				- head�ʿ� ���ο� ��带 �����ϴ� ������ ���Ḯ��Ʈ�� stack�� �����
//				����������������		����������������		����������������		����������������
//			   ��  head  ��	��  ��  Node  ��	��  ��  Node  ��	��  ��  Node  ��
//				����������������		����������������		����������������		����������������
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
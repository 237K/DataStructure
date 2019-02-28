//
//	OS Windows
//	2019.02.27
//
//	[���� ����ǥ����� ����ǥ������� ��ȯ]
//		1. �Ұ�ȣ ������� �ʰ�
//			1) ���ڸ� �׳� �ű�
//			2) �����ڸ� ���ÿ� �ű�µ�, ���ÿ����� �켱������ ���� �����ڰ� ���� �ڸ����� ���ϵ��� ��
//				- ������ ��������� �׳� �ְ�
//				- ������ ������� ������ ���� ���ÿ� �ִ� �����ڶ� �켱���� ���ؼ� �켱������ ������ ���ÿ� �ְ�, ������ ���� ���ÿ� �ִ� �����ڸ� ���� ���� �ڷ� �ű�
//				- *�켱������ ������ ������(+�� -)�� ���, ���� ���� ������ �켱������ ���� ������ �Ǵ�
//			3) ���ڸ� �� �ű�� ���ÿ� �����ִ� �����ڸ� ���� �ű�
//		2. �Ұ�ȣ ����ϰ�
//			1) ( �� �ٸ� �����ڿ� ���������� ���ÿ� �ű��, )�� ���� �� ���� ���ÿ� ��ġ�ؾ� ��
//			2) ������ ( �� �켱������ �ٸ� �����ڵ麸�� ���� ������ �Ǵ��ؾ� ��
//			3) ) �� ������ �ű����� �ʰ�, ���ÿ��� ( �� ���� �� ���� ���ÿ� �ִ� �����ڸ� �ű�
//

#include <cstdio>
#include <iostream>
#include <string>
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

bool isOperator(const char& ch)
{
	if (ch == '*' || ch == '/' || ch == '+' || ch == '-')
		return true;
	else
		return false;
}

int Priority(const char& ch)
{
	switch (ch)
	{
	case '*':
	case '/':
		return 3;
		break;
	case '+':
	case '-':
		return 2;
		break;
	case '(':
		return 1;
		break;
	default:
		return -1;
		break;
	}
}

static string PostFix;

void ConvertToPostFix(const string& in)
{
	Stack<char> stack;
	int Length = in.length();
	stack.Init();
	PostFix.clear();

	for (int i = 0; i < Length; ++i)
	{
		if (in[i] >= '0' && in[i] <= '9')
			PostFix.push_back(in[i]);

		else if (isOperator(in[i]))
		{
			if (stack.Empty())
				stack.Push(in[i]);
			else
			{
				while (Priority(stack.Top()) >= Priority(in[i]))
				{
					char moveOP = stack.Pop();
					PostFix.push_back(moveOP);
				}
				stack.Push(in[i]);
			}
		}
		else if (in[i] == '(')
		{
			stack.Push(in[i]);
		}
		else if (in[i] == ')')
		{
			while (stack.Top() != '(')
			{
				char moveOP = stack.Pop();
				PostFix.push_back(moveOP);
			}
			stack.Pop();
		}
	}
	while (!stack.Empty())
	{
		char moveOP = stack.Pop();
		PostFix.push_back(moveOP);
	}
}

int main(void)
{
	string str1 = "1+2*3";
	string str2 = "(1+2)*3";
	string str3 = "((1-2)+3)*(5-2)";
	string str4 = "(1*2+3)/4";
	string str5 = "(1+2*3)/4";

	ConvertToPostFix(str1);
	cout << "InFix : " << str1 << endl;
	cout << "PostFix : " << PostFix << endl << endl;

	ConvertToPostFix(str2);
	cout << "InFix : " << str2 << endl;
	cout << "PostFix : " << PostFix << endl << endl;

	ConvertToPostFix(str3);
	cout << "InFix : " << str3 << endl;
	cout << "PostFix : " << PostFix << endl << endl;

	ConvertToPostFix(str4);
	cout << "InFix : " << str4 << endl;
	cout << "PostFix : " << PostFix << endl << endl;

	ConvertToPostFix(str5);
	cout << "InFix : " << str5 << endl;
	cout << "PostFix : " << PostFix << endl << endl;

	return 0;
}
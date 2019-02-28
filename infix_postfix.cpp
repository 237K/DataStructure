//
//	OS Windows
//	2019.02.27
//
//	[수식 중위표기법을 후위표기법으로 변환]
//		1. 소괄호 고려하지 않고
//			1) 숫자면 그냥 옮김
//			2) 연산자면 스택에 옮기는데, 스택에서는 우선순위가 낮은 연산자가 먼저 자리잡지 못하도록 함
//				- 스택이 비어있으면 그냥 넣고
//				- 스택이 비어있지 않으면 현재 스택에 있는 연산자랑 우선순위 비교해서 우선순위가 높으면 스택에 넣고, 낮으면 지금 스택에 있는 연산자를 빼서 숫자 뒤로 옮김
//				- *우선순위가 동일한 연산자(+와 -)일 경우, 먼저 들어온 연산자 우선순위가 높은 것으로 판단
//			3) 숫자를 다 옮기면 스택에 남아있는 연산자를 빼서 옮김
//		2. 소괄호 고려하고
//			1) ( 는 다른 연산자와 마찬가지로 스택에 옮기며, )를 만날 때 까지 스택에 위치해야 함
//			2) 때문에 ( 의 우선순위는 다른 연산자들보다 낮은 것으로 판단해야 함
//			3) ) 를 만나면 옮기지는 않고, 스택에서 ( 를 만날 때 까지 스택에 있는 연산자를 옮김
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
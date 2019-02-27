//
//	OS Windows
//	2019.02.26
//
//	[�ڷᱸ��]
//		<1. Linked List>
//		<2. Circular Linked List>
//		<3. Doubly Linked List>
//			1) ���̳�尡 ���� ����� ���� ����Ʈ ADT ����
//			2) ���̳�尡 ���Ե� ����� ���� ����Ʈ ADT ����
//				������������������														 ������������������
//			   ��  head   ��														��  tail   ��
//				������������������														 ������������������
//				    ��																 ��
//				������������������		����������������		����������������		����������������		 ������������������
//			   ��/�� Dummy ��	��  ��  Node  ��	��  ��  Node  ��	��  ��  Node  ��	��   �� Dummy ��/��
//				������������������		����������������		����������������		����������������		 ������������������
//				*��, �ڿ� ���̳�尡 �ְ�, head�� tail�� ���� �հ� �ڸ� ����Ŵ
//
//				a) void Init()
//				b) void InsertBack(T data)
//				c) int First(T* pdata)
//				d) int Next(T* pdata)
//				e) T Remove()
//				f) int Count()
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
	Node<T>* prev;
};

template <typename T>
class DLL
{
private:
	Node<T>* head;
	Node<T>* tail;
	Node<T>* cur;
	int numOfdata;
public:
	void Init();
	void InsertBack(T data);
	int First(T* pdata);
	int Next(T* pdata);
	T Remove();
	int Count();
};

template <typename T>
void DLL<T>::Init()				//����� ���� ����Ʈ �ʱ�ȭ
{
	head = new Node<T>;			//���̳�� ����. head�� ���̳�� ����Ű���� ��
	head->next = tail;			//���̳��� tail�� ����Ŵ
	head->prev = NULL;			
	tail = new Node<T>;			//���̳�� ����. tail�� ���̳�带 ����Ű���� ��
	tail->prev = head;			//���̳��� head�� ����Ŵ
	tail->next = NULL;
	numOfdata = 0;
}

template <typename T>
void DLL<T>::InsertBack(T data)			//�ڿ� �����ϴ� �Լ�	(**�յڿ� ���̳�尡 �־ NULL�˻��� �ʿ䵵 ���� ��� ��쿡 �����ϰ� ������ �� ����)
{
	Node<T> *newNode = new Node<T>;		//�� ��带 �����
	newNode->data = data;				//���ڷ� �޾ƿ� ������ �����ϰ�
	newNode->prev = tail->prev;			//�� ��� ���� ����
	tail->prev->next = newNode;			//�� ��� ���� ����
	newNode->next = tail;				//�� ��� ������ ����
	tail->prev = newNode;				//�� ��� ������ ����
	numOfdata++;
}

template <typename T>
int DLL<T>::First(T* pdata)
{
	if (head->next == tail)
		return 0;
	else
	{
		cur = head->next;
		*pdata = cur->data;
		return 1;
	}
}

template <typename T>
int DLL<T>::Next(T* pdata)
{
	if (cur->next == tail)
		return 0;
	else
	{
		cur = cur->next;
		*pdata = cur->data;
		return 1;
	}
}

template <typename T>
T DLL<T>::Remove()						//���� �Լ�
{
	Node<T>* tempNode = cur;			//�ӽ÷� �����صΰ�
	T tempData = tempNode->data;
	cur->prev->next = cur->next;		//������ ����� ���� ���� �߶� ���̰�
	cur->next->prev = cur->prev;		//������ ����� ������ ���� �߶� ���̰�
	cur = cur->prev;					//cur ��ġ �̵��� ��
	delete tempNode;					//����
	return tempData;
}

template <typename T>
int DLL<T>::Count()
{
	return numOfdata;
}

int main(void)
{
	DLL<int> dll;
	int data;
	dll.Init();

	for (int i = 1; i <= 8; ++i)
		dll.InsertBack(i);

	if (dll.First(&data))
	{
		cout << data << ' ';
		while (dll.Next(&data))
		{
			cout << data << ' ';
		}
	}
	cout << endl << endl;
	cout << "======2�� ��� ����======" << endl;

	if (dll.First(&data))
	{
		if (data % 2 == 0)
			dll.Remove();
		while (dll.Next(&data))
		{
			if (data % 2 == 0)
				dll.Remove();
		}
	}

	if (dll.First(&data))
	{
		cout << data << ' ';
		while (dll.Next(&data))
		{
			cout << data << ' ';
		}
	}
	cout << endl << endl;
	return 0;
}
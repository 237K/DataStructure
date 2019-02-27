//
//	OS Windows
//	2019.02.26
//
//	[자료구조]
//		<1. Linked List>
//		<2. Circular Linked List>
//		<3. Doubly Linked List>
//			1) 더미노드가 없는 양방향 연결 리스트 ADT 정의
//			2) 더미노드가 포함된 양방향 연결 리스트 ADT 정의
//				─────────														 ─────────
//			   │  head   │														│  tail   │
//				─────────														 ─────────
//				    ↓																 ↓
//				─────────		────────		────────		────────		 ─────────
//			   │/│ Dummy │	↔  │  Node  │	↔  │  Node  │	↔  │  Node  │	↔   │ Dummy │/│
//				─────────		────────		────────		────────		 ─────────
//				*앞, 뒤에 더미노드가 있고, head와 tail이 각각 앞과 뒤를 가리킴
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
void DLL<T>::Init()				//양방향 연결 리스트 초기화
{
	head = new Node<T>;			//더미노드 생성. head가 더미노드 가리키도록 함
	head->next = tail;			//더미노드는 tail을 가리킴
	head->prev = NULL;			
	tail = new Node<T>;			//더미노드 생성. tail이 더미노드를 가리키도록 함
	tail->prev = head;			//더미노드는 head를 가리킴
	tail->next = NULL;
	numOfdata = 0;
}

template <typename T>
void DLL<T>::InsertBack(T data)			//뒤에 삽입하는 함수	(**앞뒤에 더미노드가 있어서 NULL검사할 필요도 없고 모든 경우에 동일하게 적용할 수 있음)
{
	Node<T> *newNode = new Node<T>;		//새 노드를 만들고
	newNode->data = data;				//인자로 받아온 데이터 저장하고
	newNode->prev = tail->prev;			//새 노드 왼쪽 연결
	tail->prev->next = newNode;			//새 노드 왼쪽 연결
	newNode->next = tail;				//새 노드 오른쪽 연결
	tail->prev = newNode;				//새 노드 오른쪽 연결
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
T DLL<T>::Remove()						//제거 함수
{
	Node<T>* tempNode = cur;			//임시로 저장해두고
	T tempData = tempNode->data;
	cur->prev->next = cur->next;		//제거할 노드의 왼쪽 연결 잘라서 붙이고
	cur->next->prev = cur->prev;		//제거할 노드의 오른쪽 연결 잘라서 붙이고
	cur = cur->prev;					//cur 위치 이동한 후
	delete tempNode;					//삭제
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
	cout << "======2의 배수 삭제======" << endl;

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
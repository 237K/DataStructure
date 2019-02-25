//
//	OS Windows
//	2019.02.23
//
//	[자료구조]
//		<1. Linked List>
//			1) 배열 기반 리스트
//			2) Linked List의 기본 개념. 전체 흐름에 대한 개요
//			3) Linked List ADT 정의
//				a) void Init(List* plist)
//				b) void Insert(List* plist, T data)
//				c) int First(List* plist, T* pdata)		리스트 첫 번째 데이터를 pdata가 가리키는 메모리에 저장. 참조 성공 시 TRUE(1), 실패 시 FALSE(0) 반환
//				d) int Next(List* plist, T* pdata)
//				e) T Remove(List* plist)
//				f) int Count(List* plist)
//				g) void SetSortRule(List* plist, int (*comp)(T d1, T d2))	//정렬의 기준이 되는 함수 등록
//

#include <cstdio>
using namespace std;

template <typename T>
class Node
{
public:
	T data;
	Node *next;
};

template <typename T>
class LinkedList
{
public:
	Node<T> *head;
	Node<T> *cur;
	Node<T> *before;
	int NumOfdata;
	int (*comp)(T d1, T d2);
public:
	void Init(LinkedList* plist);
	void Insert(LinkedList* plist, T data);
	void HeadInsert(LinkedList* plist, T data);
	void SortInsert(LinkedList* plist, T data);
	int First(LinkedList* plist, T* data);
	int Next(LinkedList* plist, T* data);
	T Remove(LinkedList* plist);
	int Count(LinkedList* plist);
	void SetSortRule(LinkedList* plist, int (*comp)(T d1, T d2));
};

template <typename T>
void LinkedList<T>::Init(LinkedList* plist)
{
	plist->head = new Node<T>;				//dummy 노드 생성
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->NumOfdata = 0;
}

template <typename T>
void LinkedList<T>::Insert(LinkedList* plist, T data)
{
	if (plist->comp == NULL)
		HeadInsert(plist, data);		//Head에 삽입하는 함수
	else
		SortInsert(plist, data);		//정렬기준을 기반으로 삽입하는 함수
}

template <typename T>
void LinkedList<T>::HeadInsert(LinkedList* plist, T data)
{
	Node<T> *newNode = new Node<T>;					//새로운 노드를 만들고
	newNode->data = data;						//새 노드에 데이터를 넣고
	newNode->next = plist->head->next;			//새로운 노드의 next노드는 현재 head의 next가 가리키고 있는 노드를 가리키도록 하고
	plist->head->next = newNode;				//head노드의 next(더미노드)가 새로운 노드를 가리키도록 하고
	(plist->NumOfdata)++;						//데이터 개수 증가
}

template <typename T>
void LinkedList<T>::SortInsert(LinkedList* plist, T data)
{
	Node<T> *newNode = new Node<T>;
	Node<T> *pred = plist->head;
	newNode->data = data;

	while (pred->next != NULL && plist->comp(data, pred->next->data) != 0)
	{
		pred = pred->next;
	}

	newNode->next = pred->next;
	pred->next = newNode;

	(plist->NumOfdata)++;
}

template <typename T>
int LinkedList<T>::First(LinkedList* plist, T* pdata)
{
	if (plist->head->next == NULL)				//더미노드가 가리키는게 NULL이면 
		return 0;								//반환할 데이터 없음

	plist->before = plist->head;				//before노드가 더미노드를 가리키게 하고
	plist->cur = plist->head->next;				//cur노드가 더미노드가 가리키는 노드(첫 번째 노드)를 가리키도록 함

	*pdata = plist->cur->data;					//첫 번째 노드의 데이터 전달
	return 1;
}

template <typename T>
int LinkedList<T>::Next(LinkedList* plist, T* pdata)
{
	if (plist->cur->next == NULL)
		return 0;

	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*pdata = plist->cur->data;
	return 1;
}

template <typename T>
T LinkedList<T>::Remove(LinkedList* plist)
{
	Node<T> *tempNode = plist->cur;				//임시노드에 cur노드 보관
	T tempData = tempNode->data;				//임시변수에 cur노드 데이터 보관

	plist->before->next = plist->cur->next;		//cur노드의 next가 before노드의 next가 가리키는 노드를 가리키도록 함
	plist->cur = plist->before;					//cur노드가 before노드가 가리키는 노드를 가리키도록 함

	delete tempNode;							//삭제
	(plist->NumOfdata)--;						//데이터 개수 마이너스
	return tempData;							//삭제한 데이터 반환
}

template <typename T>
int LinkedList<T>::Count(LinkedList* plist)
{
	return plist->NumOfdata;
}

template <typename T>
void LinkedList<T>::SetSortRule(LinkedList* plist, int(*comp)(T d1, T d2))
{
	plist->comp = comp;
}

int Predicate(int d1, int d2)
{
	if (d1 < d2)
		return 0;
	else
		return 1;        
}

int main(void)
{
	LinkedList<int> LL;
	int data;
	LL.Init(&LL);
	LL.SetSortRule(&LL, Predicate);
	LL.Insert(&LL, 11);
	LL.Insert(&LL, 22);
	LL.Insert(&LL, 11);
	LL.Insert(&LL, 22);
	LL.Insert(&LL, 33);

	printf("Count : %d\n", LL.Count(&LL));
	if (LL.First(&LL, &data))
	{
		printf("%d ", data);
		while (LL.Next(&LL, &data))
		{
			printf("%d ", data);
		}
	}
	printf("\n\n");

	if (LL.First(&LL, &data))
	{
		if (data == 22)
			LL.Remove(&LL);
		while (LL.Next(&LL, &data))
		{
			if (data == 22)
				LL.Remove(&LL);
		}
	}

	printf("Count : %d\n", LL.Count(&LL));
	if (LL.First(&LL, &data))
	{
		printf("%d ", data);
		while (LL.Next(&LL, &data))
		{
			printf("%d ", data);
		}
	}
	printf("\n\n");

	return 0;
}
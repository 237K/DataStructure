//
//	OS Windows
//	2019.03.11
//
//	[자료구조]
//		<1. Linked List>
//		<2. Circular Linked List>
//		<3. Doubly Linked List>
//		<4. Stack>
//		<5. Queue>
//		<6. Deque>
//		<7. Binary Tree>
//		<8. Heap>
//			1) 완전이진트리 구조
//			2) 모든 경우에 부모노드의 우선순위 >= 자식노드의 우선순위 를 만족함. 루트노드의 우선순위가 가장 높음
//			3) 루트노드로 올라갈수록 저장된 값이 커지는 완전 이진 트리 = 최대힙(max heap), 반대를 최소힙(min heap) 이라고 함
//			4) 힙에서는 데이터를 삽입하거나 삭제할 때 트리의 높이에 해당하는 수만큼만 비교연산을 진행하면 됨. 
//			5) 힙 기반 데이터 저장/삭제의 시간복잡도 = O(log2n)
//			6) 새로운 노드를 추가한 이후에도 완전이진트리를 유지해야 하므로 연결리스트보다는 배열을 사용하는 것이 좋음
//			7) 왼쪽 자식노드의 인덱스 = 부모노드의 인덱스 * 2
//			8) 오른쪽 자식노드의 인덱스 = 부모노드의 인덱스 * 2 + 1
//			9) 부모노도의 인덱스 = 자식노드의 인덱스 / 2
//		    10) 우선순위 결정을 위한 함수포인터 변수를 추가함
//		<9. Binary Search Tree>
//		<10. AVL Tree>
//		<11. Hash Table>
//			1) 모든 데이터는 key를 가진다. 모든 key는 중복되지 않는다.
//			2) 배열 기반 테이블
//				- key를 인덱스값으로 사용하려면 매우 큰 배열이 필요하므로 적합하지 않음
//			3) 해시 함수 추가
//				- 좋은 해시 함수는 해시값이 특정 영역에 몰리지 않고 고르게 퍼져서 충돌 확률이 낮은 함수
//				- 키의 일부분을 참조하여 해시값을 만들지 않고 키 전체를 참조하여 해시값을 만들어야 함
//					a) 자릿수 선택
//					b) 자릿수 폴딩
//			4) 충돌(Collision) 문제 해결
//				a) 선형 조사법(Linear Probing)
//					- 옆자리가 비었는지 확인하고 비었으면 그 자리에 저장
//					- 클러스터 현상(특정 영역에 데이터가 집중적으로 몰리는 현상) 발생 가능성 높음
//				b) 이차 조사법(Quadratic Probing)
//					- 옆자리가 아니라 n제곱 칸 옆의 슬롯을 검사
//			 ***c) 이중 해시(Double Hash)
//					- 1차 해시 함수 : 키를 근거로 저장위치를 결정하기 위한 함수
//						- 일반적으로 h1(k) = k % 10;
//					- 2차 해시 함수 : 충돌 발생 시 어디를 확인할 지 결정하기 위한 함수
//						- 일반적으로 h2(k) = 1 + (k % c)
//							- c는 소수를 사용하는 것이 클러스터 현상 발생 확률을 줄일 수 있음
//				d) 체이닝(Chaining)
//					- 충돌이 발생하더라도 그 자리에 삽입. 연결리스트 이용
//						a) 슬롯이 연결리스트의 노드 역할을 하게 하는 방법
//						b) 연결리스트의 노드와 슬롯을 구분하는 방법
//

#include <iostream>
#include <string>
using namespace std;

const static int TABLE_SIZE = 100;
typedef int HashFunc(int k);

#include <cstdio>
#include <iostream>
using namespace std;

///////////////////////////양방향 연결리스트/////////////////////////////////////////////////////
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
	void DLLInit();
	void DLLInsert(T data);
	int DLLFirst(T* pdata);
	int DLLNext(T* pdata);
	T DLLRemove();
	int DLLCount();
};

template <typename T>
void DLL<T>::DLLInit()				//양방향 연결 리스트 초기화
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
void DLL<T>::DLLInsert(T data)			//뒤에 삽입하는 함수	(**앞뒤에 더미노드가 있어서 NULL검사할 필요도 없고 모든 경우에 동일하게 적용할 수 있음)
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
int DLL<T>::DLLFirst(T* pdata)
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
int DLL<T>::DLLNext(T* pdata)
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
T DLL<T>::DLLRemove()						//제거 함수
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
int DLL<T>::DLLCount()
{
	return numOfdata;
}
///////////////////////////양방향 연결리스트/////////////////////////////////////////////////////

typedef struct _person
{
	int ssn;
	string name;
	string add;
	_person* operator= (const _person& p)
	{
		ssn = p.ssn;
		name = p.name;
		add = p.add;
		return this;
	}
} Person;

static int GetSSN(Person *p)
{
	return p->ssn;
}

static void ShowPersonInfo(Person *p)
{
	cout << "이름 : " << p->name << endl;
	cout << "주민등록번호 : " << p->ssn << endl;
	cout << "주소 : " << p->add << endl << endl;
}

static Person* MakePersonData(int ssn, string name, string add)
{
	Person *p = new Person();
	p->ssn = ssn;
	p->name = name;
	p->add = add;
	return p;
}


typedef int Key;
typedef Person* Value;

typedef struct _slot
{
	Key key;
	Value value;
} Slot;


typedef struct _table
{
	DLL<Slot> table[TABLE_SIZE];
	HashFunc *HF;
} Table;

static void TableInit(Table *t, HashFunc *f)
{
	t->HF = f;
	
	for (int i = 0; i < TABLE_SIZE; ++i)
	{
		(t->table[i]).DLLInit();
	}
}

static Value TableSearch(Table *t, Key k)
{
	int hv = t->HF(k);
	Slot ss;
	if ((t->table[hv]).DLLFirst(&ss))
	{
		if (ss.key == k)
		{
			return ss.value;
		}
		else
		{
			while ((t->table[hv]).DLLNext(&ss))
			{
				if (ss.key == k)
				{
					return ss.value;
				}
			}
		}
	}
	return NULL;
}

static void TableInsert(Table *t, Key k, Value v)
{
	int hv = t->HF(k);
	Slot ns = { k, v };
	if (TableSearch(t, k) != NULL)
	{
		cout << "키 중복!" << endl;
		return;
	}
	else
		(t->table[hv]).DLLInsert(ns);
}

static Value TableDelete(Table *t, Key k)
{
	int hv = t->HF(k);
	Slot cs;

	if ((t->table[hv]).DLLFirst(&cs))
	{
		if (cs.key == k)
		{
			t->table[hv].DLLRemove();
			return cs.value;
		}
		else
		{
			while (t->table[hv].DLLNext(&cs))
			{
				if (cs.key == k)
				{
					t->table[hv].DLLRemove();
					return cs.value;
				}
			}
		}
	}
	return NULL;
}


int MyHashFunc(int k)
{
	return k % 100;
}

int main(void)
{
	return 0;
}
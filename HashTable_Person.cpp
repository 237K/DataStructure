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
//

#include <iostream>
#include <string>
using namespace std;

const static int TABLE_SIZE = 100;
typedef int HashFunc(int k);

enum SlotStatus {EMPTY, DELETED, INUSE};

typedef struct _person
{
	int ssn;
	string name;
	string add;
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
	enum SlotStatus status;
} Slot;


typedef struct _table
{
	Slot table[TABLE_SIZE];
	HashFunc *HF;
} Table;

static void Init(Table *t, HashFunc *f)
{
	for (int i = 0; i < TABLE_SIZE; ++i)
		(t->table[i]).status = EMPTY;

	t->HF = f;
}

static void Insert(Table *t, Key k, Value v)
{
	int hv = t->HF(k);
	(t->table[hv]).value = v;
	(t->table[hv]).key = k;
	(t->table[hv]).status = INUSE;
}

static Value Delete(Table *t, Key k)
{
	int hv = t->HF(k);

	if ((t->table[hv]).status != INUSE)
		return NULL;
	else
	{
		(t->table[hv]).status = DELETED;
		return (t->table[hv]).value;
	}
}

static Value Search(Table *t, Key k)
{
	int hv = t->HF(k);
	if ((t->table[hv]).status != INUSE)
		return NULL;
	else
		return (t->table[hv]).value;
}

int MyHashFunc(int k)
{
	return k % 100;
}

int main(void)
{
	Table T;
	Init(&T, MyHashFunc);

	Person *p1;
	Person *p2;
	Person *p3;

	p1 = MakePersonData(20120003, "LEE", "Seoul");
	Insert(&T, GetSSN(p1), p1);
	p1 = MakePersonData(20092455, "HYEONG", "Seoul");
	Insert(&T, GetSSN(p1), p1);
	p1 = MakePersonData(20140712, "KIM", "Pusan");
	Insert(&T, GetSSN(p1), p1);

	p2 = Search(&T, 20092455);
	ShowPersonInfo(p2);
	p2 = Search(&T, 20120003);
	ShowPersonInfo(p2);
	p2 = Search(&T, 20140712);
	ShowPersonInfo(p2);

	p3 = Delete(&T, 20140712);
	p3 = Delete(&T, 20120003);
	p3 = Delete(&T, 20092455);

	return 0;
}
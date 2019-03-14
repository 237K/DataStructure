//
//	OS Windows
//	2019.03.11
//
//	[�ڷᱸ��]
//		<1. Linked List>
//		<2. Circular Linked List>
//		<3. Doubly Linked List>
//		<4. Stack>
//		<5. Queue>
//		<6. Deque>
//		<7. Binary Tree>
//		<8. Heap>
//			1) ��������Ʈ�� ����
//			2) ��� ��쿡 �θ����� �켱���� >= �ڽĳ���� �켱���� �� ������. ��Ʈ����� �켱������ ���� ����
//			3) ��Ʈ���� �ö󰥼��� ����� ���� Ŀ���� ���� ���� Ʈ�� = �ִ���(max heap), �ݴ븦 �ּ���(min heap) �̶�� ��
//			4) �������� �����͸� �����ϰų� ������ �� Ʈ���� ���̿� �ش��ϴ� ����ŭ�� �񱳿����� �����ϸ� ��. 
//			5) �� ��� ������ ����/������ �ð����⵵ = O(log2n)
//			6) ���ο� ��带 �߰��� ���Ŀ��� ��������Ʈ���� �����ؾ� �ϹǷ� ���Ḯ��Ʈ���ٴ� �迭�� ����ϴ� ���� ����
//			7) ���� �ڽĳ���� �ε��� = �θ����� �ε��� * 2
//			8) ������ �ڽĳ���� �ε��� = �θ����� �ε��� * 2 + 1
//			9) �θ�뵵�� �ε��� = �ڽĳ���� �ε��� / 2
//		    10) �켱���� ������ ���� �Լ������� ������ �߰���
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
	cout << "�̸� : " << p->name << endl;
	cout << "�ֹε�Ϲ�ȣ : " << p->ssn << endl;
	cout << "�ּ� : " << p->add << endl << endl;
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
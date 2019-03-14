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
//			1) ��� �����ʹ� key�� ������. ��� key�� �ߺ����� �ʴ´�.
//			2) �迭 ��� ���̺�
//				- key�� �ε��������� ����Ϸ��� �ſ� ū �迭�� �ʿ��ϹǷ� �������� ����
//			3) �ؽ� �Լ� �߰�
//				- ���� �ؽ� �Լ��� �ؽð��� Ư�� ������ ������ �ʰ� ���� ������ �浹 Ȯ���� ���� �Լ�
//				- Ű�� �Ϻκ��� �����Ͽ� �ؽð��� ������ �ʰ� Ű ��ü�� �����Ͽ� �ؽð��� ������ ��
//					a) �ڸ��� ����
//					b) �ڸ��� ����
//			4) �浹(Collision) ���� �ذ�
//				a) ���� �����(Linear Probing)
//					- ���ڸ��� ������� Ȯ���ϰ� ������� �� �ڸ��� ����
//					- Ŭ������ ����(Ư�� ������ �����Ͱ� ���������� ������ ����) �߻� ���ɼ� ����
//				b) ���� �����(Quadratic Probing)
//					- ���ڸ��� �ƴ϶� n���� ĭ ���� ������ �˻�
//			 ***c) ���� �ؽ�(Double Hash)
//					- 1�� �ؽ� �Լ� : Ű�� �ٰŷ� ������ġ�� �����ϱ� ���� �Լ�
//						- �Ϲ������� h1(k) = k % 10;
//					- 2�� �ؽ� �Լ� : �浹 �߻� �� ��� Ȯ���� �� �����ϱ� ���� �Լ�
//						- �Ϲ������� h2(k) = 1 + (k % c)
//							- c�� �Ҽ��� ����ϴ� ���� Ŭ������ ���� �߻� Ȯ���� ���� �� ����
//				d) ü�̴�(Chaining)
//					- �浹�� �߻��ϴ��� �� �ڸ��� ����. ���Ḯ��Ʈ �̿�
//						a) ������ ���Ḯ��Ʈ�� ��� ������ �ϰ� �ϴ� ���
//						b) ���Ḯ��Ʈ�� ���� ������ �����ϴ� ���
//

#include <iostream>
#include <string>
using namespace std;

const static int TABLE_SIZE = 100;
typedef int HashFunc(int k);

#include <cstdio>
#include <iostream>
using namespace std;

///////////////////////////����� ���Ḯ��Ʈ/////////////////////////////////////////////////////
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
void DLL<T>::DLLInit()				//����� ���� ����Ʈ �ʱ�ȭ
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
void DLL<T>::DLLInsert(T data)			//�ڿ� �����ϴ� �Լ�	(**�յڿ� ���̳�尡 �־ NULL�˻��� �ʿ䵵 ���� ��� ��쿡 �����ϰ� ������ �� ����)
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
T DLL<T>::DLLRemove()						//���� �Լ�
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
int DLL<T>::DLLCount()
{
	return numOfdata;
}
///////////////////////////����� ���Ḯ��Ʈ/////////////////////////////////////////////////////

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
		cout << "Ű �ߺ�!" << endl;
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
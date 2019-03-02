//
//	OS Windows
//	2019.03.02
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
//		  �� 10) �켱���� ������ ���� �Լ������� ������ �߰���
//

#include <iostream>
#include <vector>
using namespace std;
const static int MAX = 100;
typedef int PriorityComp(int d1, int d2);		//d1�� �켱������ ������ 0���� ū �� ��ȯ
												//d2�� �켱������ ������ 0���� ���� �� ��ȯ
class Heap										//�켱������ ������ 0 ��ȯ
{
private:
	vector<int> heapVector;
	int numOfdata;
	PriorityComp *comp;							
public:
	void Init(PriorityComp pc);
	bool Empty();
	void Insert(int data);
	int Delete();
	void Print() const;

	int GetParentIdx(int idx);					//�θ��� �ε��� ��ȯ
	int GetLeftChildIdx(int idx);				//���� �ڽĳ�� �ε��� ��ȯ
	int GetRightChildIdx(int idx);				//������ �ڽĳ�� �ε��� ��ȯ
	int CompareLeftRight(int idx);				//���� �ڽĳ��� ������ �ڽĳ�� �� �켱������ ���� �ڽĳ�� �ε��� ��ȯ
};

void Heap::Init(PriorityComp pc)
{
	numOfdata = 0;
	comp = pc;
	heapVector.resize(MAX);
}

bool Heap::Empty()
{
	if (numOfdata == 0)
		return true;
	else
		return false;
}

void Heap::Print() const
{
	for (int i = 0 ; i <= numOfdata ; ++i)
	{
		cout << heapVector[i] << ' ';
	}
	cout << endl << endl;
}

int Heap::GetParentIdx(int idx)
{
	return idx / 2;
}

int Heap::GetLeftChildIdx(int idx)
{
	return idx * 2;
}

int Heap::GetRightChildIdx(int idx)
{
	return idx * 2 + 1;
}

int Heap::CompareLeftRight(int idx)
{
	int Left = GetLeftChildIdx(idx);
	int Right = GetRightChildIdx(idx);

	if (Left > numOfdata)
		return 0;
	else if (Left == numOfdata)
		return Left;
	else
	{
		if (comp(heapVector[Left], heapVector[Right]) > 0)
			return Left;
		else
			return Right;
	}
}

void Heap::Insert(int data)
{
	int idx = numOfdata + 1;
	while (idx != 1)
	{
		if (comp(data, heapVector[GetParentIdx(idx)]) > 0)
		{
			heapVector[idx] = heapVector[GetParentIdx(idx)];
			idx = GetParentIdx(idx);
		}
		else
			break;
	}
	heapVector[idx] = data;
	numOfdata += 1;
}

int Heap::Delete()
{
	int tempData = heapVector[1];
	int lastElem = heapVector[numOfdata];

	int parentIdx = 1;
	int childIdx;

	while (childIdx = CompareLeftRight(parentIdx))
	{
		if (comp(lastElem, heapVector[childIdx]) >= 0)
			break;
		else
		{
			heapVector[parentIdx] = heapVector[childIdx];
			parentIdx = childIdx;
		}
	}
	heapVector[parentIdx] = lastElem;
	numOfdata -= 1;
	return tempData;
}

int Priority(int d1, int d2)
{
	return d2 - d1;
}

int main(void)
{
	Heap heap;
	heap.Init(Priority);

	heap.Insert(1);
	heap.Print();
	heap.Insert(2);
	heap.Print();
	heap.Insert(3);
	heap.Print();
	heap.Insert(4);
	heap.Print();
	heap.Insert(5);

	heap.Print();

	while (!heap.Empty())
		cout << heap.Delete() << ' ';

	cout << endl << endl;
	return 0;
}
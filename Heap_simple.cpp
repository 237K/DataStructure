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
//

#include <iostream>
#include <vector>
using namespace std;
const static int MAX = 100;
typedef pair<int, int> HeapElement;		//first = Priority / second = data

class Heap
{
private:
	vector<HeapElement> heapVector;
	int numOfdata;
public:
	void Init();
	bool Empty();
	void Insert(int data, int pr);
	int Delete();

	int GetParentIdx(int idx);					//�θ��� �ε��� ��ȯ
	int GetLeftChildIdx(int idx);				//���� �ڽĳ�� �ε��� ��ȯ
	int GetRightChildIdx(int idx);				//������ �ڽĳ�� �ε��� ��ȯ
	int CompareLeftRight(int idx);				//���� �ڽĳ��� ������ �ڽĳ�� �� �켱������ ���� �ڽĳ�� �ε��� ��ȯ
};

void Heap::Init()
{
	numOfdata = 0;
	heapVector.resize(MAX);
}

bool Heap::Empty()
{
	if (numOfdata == 0)
		return true;
	else
		return false;
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
		if (heapVector[Left].first < heapVector[Right].first)
			return Left;
		else
			return Right;
	}
}

void Heap::Insert(int data, int pr)
{
	int idx = numOfdata + 1;
	HeapElement newElem = HeapElement(data, pr);
	
	while (!idx != 1)
	{
		if (pr < heapVector[GetParentIdx(idx)].first)
		{
			heapVector[idx] = heapVector[GetParentIdx(idx)];
			idx = GetParentIdx(idx);
		}
		else
			break;
	}
	heapVector[idx] = newElem;
	numOfdata += 1;
}

int Heap::Delete()
{
	int tempData = heapVector[1].second;
	HeapElement tempElem = heapVector[numOfdata];

	int parentIdx = 1;
	int childIdx;

	while (childIdx = CompareLeftRight(parentIdx))
	{
		if (tempElem.first <= heapVector[childIdx].first)
			break;
		else
		{
			heapVector[parentIdx] = heapVector[childIdx];
			parentIdx = childIdx;
		}
	}
	heapVector[parentIdx] = tempElem;
	numOfdata -= 1;
	return tempData;
}

int main(void)
{
	Heap heap;
	heap.Init();

	heap.Insert(1, 1);
	heap.Insert(2, 2);
	heap.Insert(3, 3);
	heap.Insert(4, 4);
	heap.Insert(5, 5);

	while (!heap.Empty())
		cout << heap.Delete() << ' ';

	cout << endl << endl;
	return 0;
}
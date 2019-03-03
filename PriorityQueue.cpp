//
//	OS Windows
//	2019.03.02
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
//		<9. Priority Queue>
//			1) 사실상 Heap과 유사한 구조라 할 수 있음
//			2) 우선순위큐 ADT
//				a) void PQInit();
//				b) bool PQEmpty();
//				c) void enqueue(int data);
//				d) int dequeue();
//

#include <iostream>
#include <vector>
using namespace std;
const static int MAX = 100;

//heap/////////////////////////////////////////////
typedef int PriorityComp(int d1, int d2);
class Heap	
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

	int GetParentIdx(int idx);					//부모노드 인덱스 반환
	int GetLeftChildIdx(int idx);				//왼쪽 자식노드 인덱스 반환
	int GetRightChildIdx(int idx);				//오른쪽 자식노드 인덱스 반환
	int CompareLeftRight(int idx);				//왼쪽 자식노드와 오른쪽 자식노드 중 우선순위가 높은 자식노드 인덱스 반환
};
//heap/////////////////////////////////////////////


//Priority Queue///////////////////////////////////
class PriorityQ
{
private:
	Heap heap;
public:
	void PQInit(PriorityComp pc);
	bool PQEmpty();
	void enqueue(int data);
	int dequeue();
};
//Priority Queue///////////////////////////////////


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
	for (int i = 0; i <= numOfdata; ++i)
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



void PriorityQ::PQInit(PriorityComp pc)
{
	heap.Init(pc);
}

bool PriorityQ::PQEmpty()
{
	return heap.Empty();
}

void PriorityQ::enqueue(int data)
{
	heap.Insert(data);
}

int PriorityQ::dequeue()
{
	return heap.Delete();
}



int Priority(int d1, int d2)
{
	return d2 - d1;
}


int main(void)
{
	PriorityQ PQ;
	PQ.PQInit(Priority);

	PQ.enqueue(3);
	PQ.enqueue(1);
	PQ.enqueue(5);
	PQ.enqueue(4);
	PQ.enqueue(2);

	while (!PQ.PQEmpty())
		cout << PQ.dequeue() << ' ';

	cout << endl << endl;

	return 0;
}
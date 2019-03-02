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
//			1) 완전이진트리 구조
//			2) 모든 경우에 부모노드의 우선순위 >= 자식노드의 우선순위 를 만족함. 루트노드의 우선순위가 가장 높음
//			3) 루트노드로 올라갈수록 저장된 값이 커지는 완전 이진 트리 = 최대힙(max heap), 반대를 최소힙(min heap) 이라고 함
//			4) 힙에서는 데이터를 삽입하거나 삭제할 때 트리의 높이에 해당하는 수만큼만 비교연산을 진행하면 됨. 
//			5) 힙 기반 데이터 저장/삭제의 시간복잡도 = O(log2n)
//			6) 새로운 노드를 추가한 이후에도 완전이진트리를 유지해야 하므로 연결리스트보다는 배열을 사용하는 것이 좋음
//			7) 왼쪽 자식노드의 인덱스 = 부모노드의 인덱스 * 2
//			8) 오른쪽 자식노드의 인덱스 = 부모노드의 인덱스 * 2 + 1
//			9) 부모노도의 인덱스 = 자식노드의 인덱스 / 2
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

	int GetParentIdx(int idx);					//부모노드 인덱스 반환
	int GetLeftChildIdx(int idx);				//왼쪽 자식노드 인덱스 반환
	int GetRightChildIdx(int idx);				//오른쪽 자식노드 인덱스 반환
	int CompareLeftRight(int idx);				//왼쪽 자식노드와 오른쪽 자식노드 중 우선순위가 높은 자식노드 인덱스 반환
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
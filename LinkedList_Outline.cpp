//
//	OS Windows
//	2019.02.23
//
//	[자료구조]
//		<1. Linked List>
//			1) 배열 기반 리스트
//			2) Linked List의 전체 흐름에 대한 개요
//

#include <cstdio>
using namespace std;

typedef class _node
{
public:
	int data;
	class _node *next;
} Node;

int main(void)
{
	Node *head = NULL;
	Node *tail = NULL;
	Node *cur = NULL;
	Node *newNode = NULL;

	int data[3] = { 11, 22, 33 };

	for (int i = 0; i < 3; ++i)
	{
		newNode = new Node;
		newNode->data = data[i];
		newNode->next = NULL;

		if (head == NULL)
			head = newNode;
		else
			tail->next = newNode;

		tail = newNode;
	}

	printf("========출력========\n");
	if (head == NULL)
		printf("저장된 수가 없습니다.\n");

	else
	{
		cur = head;
		printf("%d ", cur->data);
		while (cur->next != NULL)
		{
			cur = cur->next;
			printf("%d ", cur->data);
		}
	}
	printf("\n\n");

	//메모리 할당 해제
	if (head == NULL)
		return 0;
	else
	{
		Node *delNode = head;
		Node *delNextNode = head->next;						//delNextNode를 설정하는 이유는 delNode를 삭제해버리면 next노드에 접근할 수가 없기 때문

		printf("%d을(를) 삭제합니다.\n", head->data);
		delete delNode;

		while (delNextNode != NULL)
		{
			delNode = delNextNode;
			delNextNode = delNextNode->next;

			printf("%d을(를) 삭제합니다.\n", delNode->data);
			delete delNode;
		}
	}
	return 0;
}
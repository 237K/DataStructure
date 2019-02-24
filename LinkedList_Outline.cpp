//
//	OS Windows
//	2019.02.23
//
//	[�ڷᱸ��]
//		<1. Linked List>
//			1) �迭 ��� ����Ʈ
//			2) Linked List�� ��ü �帧�� ���� ����
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

	printf("========���========\n");
	if (head == NULL)
		printf("����� ���� �����ϴ�.\n");

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

	//�޸� �Ҵ� ����
	if (head == NULL)
		return 0;
	else
	{
		Node *delNode = head;
		Node *delNextNode = head->next;						//delNextNode�� �����ϴ� ������ delNode�� �����ع����� next��忡 ������ ���� ���� ����

		printf("%d��(��) �����մϴ�.\n", head->data);
		delete delNode;

		while (delNextNode != NULL)
		{
			delNode = delNextNode;
			delNextNode = delNextNode->next;

			printf("%d��(��) �����մϴ�.\n", delNode->data);
			delete delNode;
		}
	}
	return 0;
}
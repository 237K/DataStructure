//
//	OS Windows
//	2019.03.01
//
//	[자료구조]
//		<1. Linked List>
//		<2. Circular Linked List>
//		<3. Doubly Linked List>
//		<4. Stack>
//		<5. Queue>
//		<6. Deque>
//		<7. Binary Tree>
//			1) 이진트리 ADT
//				a) BTreeNode MakeBTreeNode(void);
//				b) T GetData(BTreeNode *bt);
//				c) void SetData(T data);
//				d) BTreeNode *GetLeftSubTree(BTreeNode *bt);
//				e) BTreeNode *GetRightSubTree(BTreeNode *bt);
//				f) void MakeLeftSubTree(BTreeNode *main, BTreeNode *sub);
//				g) void MakeRightSubTree(BTreeNode *main, BTreeNode *sub);
//				h) void InorderTraverse(BTreeNode *bt, VisitFuncPtr action);		//중위순회 함수
//				i) void DeleteTree(BTreeNode *bt);
//

#include <iostream>
#include <cstdio>
using namespace std;

typedef struct _btreeNode
{
	int data;
	struct _btreeNode *left;
	struct _btreeNode *right;
} BTreeNode;

BTreeNode *MakeBTreeNode(void);
int GetData(BTreeNode *bt);
void SetData(BTreeNode *bt, int data);

BTreeNode *GetLeftSubTree(BTreeNode *bt);
BTreeNode *GetRightSubTree(BTreeNode *bt);

void MakeLeftSubTree(BTreeNode *main, BTreeNode *sub);
void MakeRightSubTree(BTreeNode *main, BTreeNode *sub);

void InorderTraverse(BTreeNode *bt);								//트리 중위순회 함수

typedef void VisitFuncPtr(int data);
void InorderTraverse(BTreeNode *bt, VisitFuncPtr action);			//트리 중위순회 함수 (노드에 적용할 함수 추가)

void DeleteTree(BTreeNode *bt);

BTreeNode *MakeBTreeNode(void)
{
	BTreeNode *newNode = new BTreeNode;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

int GetData(BTreeNode *bt)
{
	return bt->data;
}

void SetData(BTreeNode *bt, int data)
{
	bt->data = data;
}

BTreeNode *GetLeftSubTree(BTreeNode *bt)
{
	return bt->left;
}

BTreeNode *GetRightSubTree(BTreeNode *bt)
{
	return bt->right;
}

void MakeLeftSubTree(BTreeNode *main, BTreeNode *sub)
{
	if (main->left != NULL)
		delete main->left;
	main->left = sub;
}

void MakeRightSubTree(BTreeNode *main, BTreeNode *sub)
{
	if (main->right != NULL)
		delete main->right;
	main->right = sub;
}

void InorderTraverse(BTreeNode *bt)
{
	if (bt == NULL)
		return;
	else
	{
		InorderTraverse(bt->left);
		cout << bt->data << ' ';
		InorderTraverse(bt->right);
	}
}

void InorderTraverse(BTreeNode *bt, VisitFuncPtr action)
{
	if (bt == NULL)
		return;
	else
	{
		InorderTraverse(bt->left, action);
		action(bt->data);
		InorderTraverse(bt->right, action);
	}
}

void DeleteTree(BTreeNode *bt)				//삭제는 후위순회로 해야함
{
	if (bt == NULL)
		return;
	else
	{
		DeleteTree(bt->left);
		DeleteTree(bt->right);
		cout << "delete " << bt->data << endl;
		delete bt;
		bt = NULL;
	}
}

void ShowIntData(int data)
{
	if (data < 0)
		cout << "Deleted " << endl;
	else
		cout << data << ' ';
}

int main(void)
{
	BTreeNode *bt1 = MakeBTreeNode();
	BTreeNode *bt2 = MakeBTreeNode();
	BTreeNode *bt3 = MakeBTreeNode();
	BTreeNode *bt4 = MakeBTreeNode();
	BTreeNode *bt5 = MakeBTreeNode();

	SetData(bt1, 1);
	SetData(bt2, 2);
	SetData(bt3, 3);
	SetData(bt4, 4);
	SetData(bt5, 5);

	MakeLeftSubTree(bt1, bt2);
	MakeRightSubTree(bt1, bt3);
	MakeLeftSubTree(bt2, bt4);
	MakeRightSubTree(bt2, bt5);

	InorderTraverse(bt1, ShowIntData);
	cout << endl << endl;

	cout << "delete 2 Node" << endl << endl;
	DeleteTree(bt2);
	InorderTraverse(bt1, ShowIntData);
	cout << endl << endl;

	return 0;
}
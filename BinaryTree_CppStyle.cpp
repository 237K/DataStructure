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
//			2) c++ 스타일로 구현
//				a) delete하고나서 NULL가리키도록 명시해도 제대로 동작하지 않아서 if(BTreeNode == NULL) 과 같은 제어문에서 자꾸 에러 발생
//				   check변수를 하나 추가해서 제어문을 if(check == 0) 처럼 구성해보겠음
//

#include <iostream>
using namespace std;

template <typename T>
class BinaryTree;

typedef void VisitFuncPtr(int data);

template <typename T>
class Node
{
	friend class BinaryTree<T>;
private:
	T data;
	int check;
	Node<T> *left;
	Node<T> *right;
public:
	Node(T data, Node<T>* left = NULL, Node<T>* right = NULL)
	{
		this->data = data;
		check = 1;
		this->left = left;
		this->right = right;
	}
	~Node()
	{
		check = 0;
		delete left;
		delete right;
	}
};

template <typename T>
class BinaryTree
{
	friend class Node<T>;
private:
	Node<T> *BTnode;
public:
	BinaryTree(T data = 0)
	{
		BTnode = new Node<T>(data);
	}
	~BinaryTree()
	{
		delete BTnode;
	}
	void SetData(T data)
	{
		BTnode->data = data;
	}
	T GetData()
	{
		if (BTnode != NULL || BTnode->check == 1)
			return BTnode->data;
		else
		{
			cout << "Node is empty" << endl << endl;
			return -1;
		}
	}
	BinaryTree<T>* GetCurSubTree()
	{
		return BTnode;
	}
	BinaryTree<T>* GetLeftSubTree()
	{
		return BTnode->left;
	}
	BinaryTree<T>* GetRightSubTree()
	{
		return BTnode->right;
	}
	void MakeLeftSubTree(BinaryTree<T>* bt)
	{
		if (BTnode != NULL || BTnode->check == 1)
		{
			if (BTnode->left != NULL && BTnode->check == 1)
			{
				delete BTnode->left;
				BTnode->left = NULL;
			}
			BTnode->left = bt;
		}
		else
		{
			cout << "root node is empty" << endl << endl;
			exit(-1);
		}
	}
	void MakeRightSubTree(BinaryTree<T>* bt)
	{
		if (BTnode != NULL || BTnode->check == 1)
		{
			if (BTnode->right != NULL && BTnode->check == 1)
			{
				delete BTnode->right;
				BTnode->right = NULL;
			}
			BTnode->right = bt;
		}
		else
		{
			cout << "root node is empty" << endl << endl;
			exit(-1);
		}
	}
	friend void InorderTraverse(BinaryTree<T> *bt, VisitFuncPtr action);
	friend void DeleteTree(BinaryTree<T> *bt);
};

template <typename T>
void InorderTraverse(BinaryTree<T> *bt, VisitFuncPtr action)
{
	if (bt->BTnode==NULL || bt->BTnode->check == 0)
	{
		cout << "Node is Empty" << endl << endl;
		return;
	}
	else
	{
		InorderTraverse(bt->BTnode->left, action);
		action(bt->BTnode->data);
		InorderTraverse(bt->BTnode->right, action);
	}
}

template <typename T>
void DeleteTree(BinaryTree<T> *bt)
{
	if (bt->BTnode == NULL || bt->BTnode->check == 0)
	{
		cout << "Already deleted" << endl << endl;
		return;
	}
	else
	{
		DeleteTree(bt->BTnode->left);
		DeleteTree(bt->BTnode->right);
		cout << "Delete " << bt->BTnode->data << endl;
		delete bt;
		bt = NULL;
	}
}

void ShowIntData(int data)
{
	cout << data << ' ';
}

int main(void)
{
	BinaryTree<int> *BT1 = new BinaryTree<int>();
	BinaryTree<int> *BT2 = new BinaryTree<int>();
	BinaryTree<int> *BT3 = new BinaryTree<int>();
	BinaryTree<int> *BT4 = new BinaryTree<int>();
	BinaryTree<int> *BT5 = new BinaryTree<int>();

	BT1->SetData(1);
	BT2->SetData(2);
	BT3->SetData(3);
	BT4->SetData(4);
	BT5->SetData(5);

	BT1->MakeLeftSubTree(BT2);
	BT1->MakeRightSubTree(BT3);
	BT2->MakeLeftSubTree(BT4);
	BT2->MakeRightSubTree(BT5);

	cout << "Current Binary tree : ";
	InorderTraverse(BT1, ShowIntData);
	cout << endl << endl;
	cout << "Delete 2 tree" << endl<<endl;
	DeleteTree(BT2);
	cout << "Current Binary tree : ";
	InorderTraverse(BT1, ShowIntData);
	cout << endl << endl;


	return 0;
}
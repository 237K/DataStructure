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
public:
	T data;
	int check;
	BinaryTree<T> *left;
	BinaryTree<T> *right;
public:
	Node(T data, BinaryTree<T>* left = NULL, BinaryTree<T>* right = NULL)
	{
		this->data = data;
		check = 1;
		this->left = left;
		this->right = right;
	}
	~Node()
	{
		delete left;
		delete right;
	}
};

template <typename T>
class BinaryTree
{
	friend class Node<T>;
public:
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
		if (BTnode != NULL)
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
		if (BTnode != NULL)
		{
			if (BTnode->left != NULL)
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
		if (BTnode != NULL)
		{
			if (BTnode->right != NULL)
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

	void InorderTraverse(BinaryTree<T> *bt, VisitFuncPtr action)
	{
		BinaryTree<T> *temp = new BinaryTree<T>();
		temp = bt;

		if (temp == NULL)
		{
			return;
		}
		else
		{
			InorderTraverse(temp->BTnode->left, action);
			action(temp->BTnode->data);
			InorderTraverse(temp->BTnode->right, action);
		}
	}
	void DeleteTree(BinaryTree<T> *bt)
	{
		if (bt == NULL)
		{
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

	//friend void InorderTraverse(BinaryTree<T> *bt, VisitFuncPtr action);
	//friend void DeleteTree(BinaryTree<T> *bt);
};

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
	BT1->InorderTraverse(BT1, ShowIntData);
	cout << endl << endl;
	//cout << "Delete 2 tree" << endl<<endl;
	//BT2->DeleteTree(BT2);
	//cout << "Current Binary tree : ";
	//BT1->InorderTraverse(BT1, ShowIntData);
	//cout << endl << endl;


	return 0;
}
#include <iostream>
#include <vector>
using namespace std;

template<class Type>
class BSTNode;
template<class Type>
class BST;

template<class Type>
class BSTNode
{
	friend class BST<Type>;
public:
	BSTNode(Type d = Type(), BSTNode<Type>* left = nullptr, BSTNode<Type>* right = nullptr) :data(d), leftChild(left), rightChild(right)
	{
	}
	~BSTNode()
	{}
private:
	Type data;
	BSTNode* leftChild;
	BSTNode* rightChild;
};

template<class Type>
class BST
{
public:
	BST() :root(nullptr)
	{}
public:
	bool Insert(const Type& v)
	{
		return Insert(root, v);
	}
	void Inorder()
	{
		return Inorder(root);
	}
	BSTNode<Type>* Find(const Type& key)
	{
		return Find(root, key);
	}
	Type Max()const
	{
		return Max(root);
	}
	Type Min()const
	{
		return Min(root);
	}
	bool Remove(const Type& key)
	{
		return Remove(root,key);
	}
protected:
	bool Insert(BSTNode<Type>*& t, const Type& v)
	{
		if (t == nullptr)
		{
			t = new BSTNode<Type>(v);
			return true;
		}

		if (v == t->data)
			return false;

		if (v < t->data)
			Insert(t->leftChild, v);
		else if (v > t->data, v)
			Insert(t->rightChild, v);
		return true;
	}
	//中序遍历
	void Inorder(BSTNode<Type>* t)
	{
		if (t != nullptr)
		{
			Inorder(t->leftChild);
			cout << t->data << endl;;
			Inorder(t->rightChild);
		}
	}
	BSTNode<Type>* Find(BSTNode<Type>* t, const Type& key)
	{
		if (t == nullptr || key == t->data)
			return t;
		if (key < t->data)
		{
			Find(t->leftChild, key);
		}
		if (key > t->data)
		{
			Find(t->rightChild, key);
		}
	}
	Type Max(BSTNode<Type>* t)const
	{
		BSTNode<Type>* p = t;
		while (p->rightChild != nullptr)
		{
			p = p->rightChild;
		}
		return p->data;
	}
	Type Min(BSTNode<Type>* t)const
	{
		BSTNode<Type>* p = t;
		while (p->leftChild != nullptr)
		{
			p = p->leftChild;
		}
		return p->data;
	}
	bool Remove(BSTNode<Type>*& t, const Type& key)
	{
		//查找结点
		if (t == nullptr)
		{
			return false;
		}
		if (key < t->data)
		{
			Remove(t->leftChild, key);
		}
		else if (key > t->data)
		{
			Remove(t->rightChild, key);
		}
		else
		{
			BSTNode<Type>* p;
			if (t->leftChild != nullptr && t->rightChild != nullptr)
			{
				p = t->leftChild;
				while (p->rightChild != nullptr)
				{
					p = p->rightChild;
				}
				t->data = p->data;
				Remove(p, p->data);
			}
			else
			{
				p = t;
				if (t->leftChild != nullptr)
					t = t->leftChild;
				else
					t = t->rightChild;
				delete p;
			}

			/*if (t->leftChild == nullptr && t->rightChild == nullptr)
			{
					//叶子节点
					delete t;
					t = nullptr;
				}
				else if (t->leftChild != nullptr && t->rightChild == nullptr)
				{
					//有左子树，无右子树
					BSTNode<Type>* p = t;
					t = t->leftChild;
					delete p;
				}
				else if (t->leftChild == nullptr && t->rightChild != nullptr)
				{
					//无左子数，有右子树
					BSTNode<Type>* p = t;
					t = t->rightChild;
					delete p;
				}
				else if (t->leftChild != nullptr && t->rightChild != nullptr)
				{
					BSTNode<Type>* p = t->leftChild;
					while (p->rightChild != nullptr)
					{
						p = p->rightChild;
					}
					t->data = p->data;
					Remove(p,p->data);
				}*/
			}
		return true;
	}
private:
	BSTNode<Type>* root;
};

int main()
{
	vector<int> iv = { 2,3,0,6,4,7,5,9,1,40 };
	BST<int> bst;
	for (auto& e : iv)
	{
		bst.Insert(e);
	}
	bst.Inorder();
	BSTNode<int>* pd = bst.Find(10);
	if (pd == nullptr)
		cout << "nullptr" << endl;
	cout << "Min = " << bst.Min() << endl;
	cout << "Max = " << bst.Max() << endl;
	cout << bst.Remove(2) << endl;
	//cout << bst.Remove(9) << endl;
    return 0;
}

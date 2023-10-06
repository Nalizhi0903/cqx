#include <iostream>
#include <vector>
#include <stack>
using namespace std;

template<class Type>
class AVL;

template<class Type>
class AVLNode
{
	friend class AVL<Type>;
public:
	AVLNode(Type d = Type(), AVLNode* left = nullptr, AVLNode* right = nullptr) :leftChild(left), rightChild(right), data(d)
	{}
	~AVLNode()
	{}
private:
	int balance_element;
	Type data;
	AVLNode* leftChild;
	AVLNode* rightChild;
};

template<class Type>
class AVL
{
public:
	AVL() :root(nullptr)
	{}
public:
	void Insert(const Type& v)
	{
		return Insert(root, v);
	}
	void Inorder()
	{
		return Inorder(root);
	}
	AVLNode<Type>* Find(const Type& key)
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
		return Remove(root, key);
	}
protected:
	void Insert(AVLNode<Type>*& t, const Type& v)
	{
		//插入
		//p初始指向根节点，pr指向空，用栈储存插入路径
		AVLNode<Type>* p = t, * pr = nullptr;
		stack<AVLNode<Type>*> st;
		//循环找到插入位置
		while (p != nullptr)
		{
			if (p->data == v)//不能有重复值
				return;
			if (p->data > v)//插入值大于节点值，p指向左子树
			{
				pr = p;//pr储存当前p的节点，以便后面左右子树插入节点
				st.push(pr);//每当pr=p时储存节点路径
				p = p->leftChild;
			}
			else//插入值小于节点值，p指向右子树
			{
				pr = p;
				st.push(pr);
				p = p->rightChild;
			}
		}
		p = new AVLNode<Type>(v);//创建新节点
		if (t == nullptr)//若为空树则p直接为root赋值
		{
			t = p;
			return;
		}
		if (v < pr->data)//若插入值比节点小，插入左子树
		{
			pr->leftChild = p;
		}
		else
		{
			pr->rightChild = p;//若插入值比节点大，插入右子树
		}
		return;
		//调整平衡
		while (!st.empty())
		{
			pr = st.top();
			st.pop();
			if (pr->leftChild == p)
				pr->balance_element--;
			else
				pr->balance_element++;
			if (pr->balance_element == 0)
				break;
			if (pr->balance_element == 1 || pr->balance_element == -1) //向上回溯
				p = pr;
			else
			{
				//|bf| = 2
				//调整平衡
				if (pr->balance_element < 0)
				{
					if (p->balance_element < 0)        
					{
						//cout<<"RightRotate"<<endl;
						//RotateR(pr);
					}
					else  // <
					{
						//cout<<"LRRotate"<<endl;
						//RotateLR(pr);
					}
				}
				else
				{
					if (p->balance_element > 0)     
					{
						//cout<<"LeftRotate"<<endl;
						//RotateL(pr);
					}
					else  //  > 
					{
						//cout<<"RLRotate"<<endl;
						//RotateRL(pr);
					}
				}
				break;
			}
		}
	}
	//中序遍历
	void Inorder(AVLNode<Type>* t)
	{
		if (t != nullptr)
		{
			Inorder(t->leftChild);
			cout << t->data << endl;;
			Inorder(t->rightChild);
		}
	}
	AVLNode<Type>* Find(AVLNode<Type>* t, const Type& key)
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
	Type Max(AVLNode<Type>* t)const
	{
		AVLNode<Type>* p = t;
		while (p->rightChild != nullptr)
		{
			p = p->rightChild;
		}
		return p->data;
	}
	Type Min(AVLNode<Type>* t)const
	{
		AVLNode<Type>* p = t;
		while (p->leftChild != nullptr)
		{
			p = p->leftChild;
		}
		return p->data;
	}
private:
	AVLNode<Type>* root;
};

int main()
{
	vector<int> v = { 16,13,7,8,15,9,45 };
	AVL<int> avl;
	for (auto& e : v)
	{
		avl.Insert(e);
	}
    return 0;
}

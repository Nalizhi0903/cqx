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
			if (p->data > v)//插入值小于节点值，p指向左子树
			{
				pr = p;//pr储存当前p的节点，以便后面左右子树插入节点
				st.push(pr);//每当pr=p时储存节点路径
				p = p->leftChild;
			}
			else//插入值大于节点值，p指向右子树
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
					if (p->balance_element < 0)	 //往节点的左子树的左子树插入元素，导致左子数的平衡因子-1，并导致节点平衡因子变为-2，右旋转
					{
						RotateR(pr);
					}
					else
					{
						RotateLR(pr);
					}
				}
				else
				{
					if (p->balance_element > 0) //  往节点的右子树的右子树插入元素，导致右子数的平衡因子-1，并导致节点平衡因子变为-2，左旋转
					{
						RotateL(pr);
					}
					else  //  > 
					{
						RotateRL(pr);
					}
				}
				break;
			}
		}
		if (st.empty())
			t = pr;
		else
		{
			p = st.top();
			if (pr->data < p->data)
				p->leftChild = pr;
			else
				p->rightChild = pr;
		}
	}
	bool Remove(AVLNode<Type>*& t, Type v)
	{
		AVLNode<Type>* pr = nullptr, * p = t, * q, * ppr;
		int d, dd = 0;
		stack<AVLNode<Type>*> st;
		//寻找节点
		while (p != nullptr)
		{
			if (p->data == v)
				break;
			pr = p;
			st.push(pr);
			if (p->data > v)
				p = p->leftChild;
			else
				p = p->rightChild;
		}
		//如果没找到删除结点
		if (p == nullptr)
			return false;
		//删除结点
		if (p->leftChild != nullptr && p->rightChild != nullptr)
		{
			pr = p;
			st.push(pr);
			q = p->leftChild;
			while (q->rightChild != nullptr)
			{
				pr = q;
				st.push(pr);
				q = q->rightChild;
			}
			p->data = q->data;
			p = q;
		}
		//q为删除结点p的子树
		if (p->leftChild != nullptr)
			q = p->leftChild;
		else
			q = p->rightChild;
		//如果删除的是根节点，则t=q
		if (pr == NULL)
			t = q;
		else
		{
			//如果删除结点为其父结点的左树，将删除结点的子树连到父结点的左树，反之为右树
			if (pr->leftChild == p)
				pr->leftChild = q;
			else
				pr->rightChild == q;
			//调节平衡因子
			while (!st.empty())
			{
				st.pop();
				if (pr->leftChild == p)
					pr->balance_element--;
				else
					pr->balance_element++;
				if (!st.empty)
				{
					ppr = st.top();
					dd = (ppr->leftChild == pr) ? -1 : 1;
				}
				else
					dd = 0;
				//原先父结点平衡因子为0，删除后，结点平衡因子为1或-1，不影响上面结点平衡因子
				if (pr->balance_element == -1 || pr->balance_element == 1)
					break;
				if(pr->balance_element != 0)//删除后，结点平衡因子为2或-2
				{
					if (pr->balance_element == -2)
					{
						if (ppr->balance_element < 0)
							RotateR(pr);
						else
							RotateLR(pr);
					}
					else
					{
						if (pr->balance_element == 2)
						{
							if (ppr->balance_element < 0)
								RotateL(pr);
							else
								RotateRL(pr);
						}
					}
				}
				else
				{

				}
			}
		}
		
		//重新链接
			

		delete p;
		p = nullptr;
		return true;
	}
	void RotateR(AVLNode<Type>*& ptr)
	{
		AVLNode<Type>* R = ptr;
		ptr = R->leftChild;//先定位节点和旋转的节点
		R->leftChild = ptr->rightChild;
		ptr->rightChild = R;
		ptr->balance_element = R->balance_element = 0;
	}
	void RotateL(AVLNode<Type>*& ptr)
	{
		AVLNode<Type>* L = ptr;
		ptr = L->rightChild;//先定位节点和旋转的节点
		L->rightChild = ptr->leftChild;
		ptr->leftChild = L;
		ptr->balance_element = L->balance_element = 0;
	}
	void RotateLR(AVLNode<Type>*& ptr)
	{
		AVLNode<Type>* L = ptr->leftChild, * R = ptr;
		ptr = L->rightChild;
		//先左转
		L->rightChild = ptr->leftChild;
		ptr->leftChild = L;
		//修改平衡因子
		if (ptr->balance_element <= 0)
			L->balance_element = 0;
		else
			L->balance_element = -1;
		/*
			p节点平衡因子为1时只有右子树，而p节点在左转时没有左子树给L节点的左子树指向，
			导致L节点的缺少左子树，多一个左子树故平衡因子为-1，其他情况则都为0
		*/

		//再右转
		R->leftChild = ptr->rightChild;
		ptr->rightChild = R;
		//修改平衡因子

		if (ptr->balance_element >= 0)
			R->balance_element = 0;
		else
			R->balance_element = 1;
		/*
			p节点平衡因子为-1时只有左子树，而p节点在右转时没有右子树给R节点的左子树指向，
			导致R节点的缺少左子树，多一个右子树故平衡因子为1，其他情况则都为0
		*/
	}
	void RotateRL(AVLNode<Type>*& ptr)
	{
		AVLNode<Type>* R = ptr->rightChild, * L = ptr;
		ptr = R->leftChild;
		//先右转
		R->leftChild = ptr->rightChild;
		ptr->rightChild = R;
		//修改平衡因子
		
		if (ptr->balance_element >= 0)
			R->balance_element = 0;
		else
			R->balance_element = 1;
		/*
			p节点平衡因子为-1时只有左子树，而p节点在右转时没有右子树给R节点的左子树指向，
			导致R节点的缺少左子树，多一个右子树故平衡因子为1，其他情况则都为0
		*/
		//再左转
		L->rightChild = ptr->leftChild;
		ptr->leftChild = L;
		//修改平衡因子
		if (ptr->balance_element == 1)
			L->balance_element = -1;
		else
			L->balance_element = 0;
		/*
			p节点平衡因子为1时只有右子树，而p节点在左转时没有左子树给L节点的左子树指向，
			导致L节点的缺少左子树，多一个左子树故平衡因子为-1，其他情况则都为0
		*/
	}
private:
	AVLNode<Type>* root;
};

void main()
{
	vector<int> v = { 8,9,10,6,7,5,3,1}; 
	AVL<int> avl;
	for (auto& e : v)
	{
		avl.Insert(e);
	}
	avl.Remove(5);

}


#include <iostream>
using namespace std;

typedef enum{ RED, BLACK }Color_t;

template<class Type>
class RBTree;

template<class Type>
class RBNode
{
    friend class RBTree<Type>;
public:
    RBNode(Type d = Type(), RBNode<Type>* left = nullptr, RBNode<Type>* right = nullptr) :data(d), leftChild(left), rightChild(right), parent(nullptr), color(RED)
    {}
    ~RBNode()
    {}

public:
private:
    Type          data;
    Color_t       color;
    RBNode<Type>* leftChild;
    RBNode<Type>* rightChild;
    RBNode<Type>* parent;
};

template<class Type>
class RBTree
{
public:
    RBTree():NIL(BuyNode()), root(NIL)
    {
        NIL->color = BLACK;
        NIL->leftChild = NIL->rightChild = NIL->parent = nullptr;
    }
    ~RBTree()
    {}
public:
    void Insert(const Type& v)
    {
        return Insert(root, v);
    }
    void RotateL(RBNode<Type>* t)
    {
        return RotateL(t);
    }
    void RotateLR(RBNode<Type>* t)
    {
        return RotateLR(t);
    }
    void RotateRL(RBNode<Type>* t)
    {
        return RotateRL(t);
    }
protected:
    void Insert(RBNode<Type>*& t, const Type& v);
    void Insert_FIXUP(RBNode<Type>*& t, RBNode <Type>* x);
    void RotateR(RBNode<Type>* t, RBNode<Type>* ptr);
protected:
    RBNode<Type>* BuyNode(const Type& v = Type())
    {
        RBNode<Type>* s = new RBNode<Type>(v);
        s->leftChild = s->rightChild = s->parent = NIL;
        return s;
    }    
private:
    RBNode<Type>* NIL;//外部节点，为黑色
    RBNode<Type>* root;
};

template<class Type>   
void RBTree<Type>::RotateR(RBNode<Type>* t, RBNode<Type>* ptr)
{
    RBNode<Type>* R = ptr;
    ptr = R->leftChild;
    R->leftChild = ptr->rightChild;
    if (ptr->rightChild != NIL)
        ptr->rightChild->parent = R;
    if (R == t)
        t = ptr;
    else if (R == R->parent->leftChild)
        R->parent->leftChild = ptr;
    else
        R->parent->rightChild = ptr;
    ptr->rightChild = R;
    R->parent = ptr;

}

template <class Type>
void RBTree<Type>::Insert(RBNode<Type>*& t, const Type& v)
{
    //x为插入节点，pr为父结点
    RBNode<Type>* x = t, * pr = NIL;
    while(x != NIL)
    {
        if (x->data == v)
            return;
        pr = x;
        if (x->data > v)
            x = x->leftChild;
        else
            x = x->rightChild;
    }
    x = BuyNode(v);
    if (pr == NIL)  //为空树的时候插入
        t = x;
    else if (x->data < pr->data)
        pr->leftChild = x;
    else
        pr->rightChild = x;
    x->parent = pr;
    //调节平衡
    Insert_FIXUP(t, x);
}

template <class Type>
void RBTree<Type>::Insert_FIXUP(RBNode<Type>*& t, RBNode<Type>* x)
{
    while (x != t && x->parent->color == RED)//若父结点颜色为黑直接插入，可以推出来，父结点为黑的时候插入不影响平衡，因为父结点为黑时，高度不是最大的，插入一个红色的结点并不会超过最大高度
    {
        //父结点为祖父结点的左子树
        if (x->parent->parent->leftChild == x->parent)
        {
            RBNode<Type>* s = x->parent->parent->rightChild;
            //叔伯结点为红色 
            if (s->color == RED)
            {
                //情况3，叔伯结点为红，不旋转，直接更改颜色
                x->parent->color = BLACK;
                s->color = BLACK;
                x->parent->parent->color = RED;
                //检查祖父的父结点的颜色 GG->color
                x = x->parent->parent;
            }
            else
            {
                //叔伯结点为黑色，情况分外侧插入和内侧插入
                if (x->parent->rightChild == x)//内侧 <
                {
                    //情况2，双旋转


                }
                //内侧
                //情况1,单旋转,更改P、G颜色   /
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                RotateR(t, x->parent->parent);
            }
        }
        else
        {

        }
    }
    t->color = BLACK;
}

int main()
{
    RBTree<int> rb;
    int ar[] = { 8,3,10,7 };
    int n = sizeof(ar) / sizeof(ar[0]);
    for (int i = 0; i < n; i++)
    {
        rb.Insert(ar[i]);
    }
    rb.Insert(6);

    return 0;
}

#include <iostream>
using namespace std;

typedef enum{RED,BLACK}Color_t;

template<class Type>
class RBTree;

template<class Type>
class RBNode
{
friend class RBTree<Type>;
public:
    RBNode(Type d = Type(), RBNode<Type>*left = nullptr, RBNode<Type>*right = nullptr):data(d),leftChild(left),rightChild(right),parent(nullptr),color(RED)
    {

    }
    ~RBNode()
    {}

public:
private:
    RBNode<Type>* leftChild;
    RBNode<Type>* rightChild;
    RBNode<Type>* parent;
    Color_t       color;
    Type data;
};

template<class Type>
class RBTree
{
public:
    RBTree():NIL(BuyNode()),root(NIL)
    {}
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
    void RotateR(RBNode<Type>* t)
    {
        return RotateR(t);
    }
protected:
    RBNode<Type>* BuyNode(const Type &v=Type())
    {
        RBNode<Type>* s = new RBNode<Type>(v);
        s->leftChild = s->rightChild = s->parent = NIL;
        return s;
    }
    void Insert(RBNode<Type>* t, const Type& v)
    {
        RBNode<Type>* x = t, pr = NIL;
        if(x != NIL)
        {

        }
        x = BuyNode(v);
    }
private:
    RBNode<Type>* root;
    RBNode<Type>* NIL;//外部节点，为黑色
};

int main()
{
    RBTree<int> rb;
    return 0;
}

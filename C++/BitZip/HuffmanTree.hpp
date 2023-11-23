#pragma once
#include <vector>
#include <queue>
template<class _Ty>
struct HuffmanTreeNode
{
	HuffmanTreeNode<_Ty>* _left;
	HuffmanTreeNode<_Ty>* _right;
	HuffmanTreeNode<_Ty>* _parent;
	_Ty _weight;
	HuffmanTreeNode(const _Ty& weight = _Ty())
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _weight(weight)
	{}
};

template <class _Ty>
class HuffmanTree
{
	typedef HuffmanTreeNode<_Ty> Node;
	class Compare
	{
	public:
		bool operator()(const Node* left, const Node* right)
		{
			return left->_weight > right->_weight;
		}
	};
public:
	HuffmanTree()
		:_root(nullptr)
	{}
	HuffmanTree(const std::vector<_Ty>& vw, const _Ty& invalid)
	{
		//1.用所有的权值构造只有根节点的二叉树森林
		//森林中二叉树应该使用堆（优先级队列）来保存
		std::priority_queue< Node*, std::vector<Node*>, Compare> q;
		for (auto& e : vw)
		{
			if (invalid != e)
			{
				q.push(new Node(e));
			}
		}
		while (q.size() > 1)
		{
			Node* left = q.top();
			q.pop();

			Node* right = q.top();
			q.pop();

			Node* parent = new Node(left->_weight + right->_weight);
			parent->_left = left;
			parent->_right = right;

			left->_parent = parent;
			right->_parent = parent;
			q.push(parent);
		}
		_root = q.top();
	}
	Node* GetRoot()
	{
		return _root;
	}
private:
	Node* _root;
};
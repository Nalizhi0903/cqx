#pragma once
#include <vector>
#include <queue>
template<class _Ty>
struct HuffmanTreeNode
{
	HuffmanTreeNode<_Ty>* _left;
	HuffmanTreeNode<_Ty>* _right;
	_Ty _weight;
	HuffmanTreeNode(const _Ty& weight = _Ty())
		: _left(nullptr)
		, _right(nullptr)
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

	HuffmanTree(const std::vector<_Ty>& vw)
	{
		//1.�����е�Ȩֵ����ֻ�и��ڵ�Ķ�����ɭ��
		//ɭ���ж�����Ӧ��ʹ�öѣ����ȼ����У�������
		std::priority_queue< Node*, std::vector<Node*>, Compare> q;
		for (auto& e : vw)
		{
			q.push(new Node(e));
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

			q.push(parent);
		}
		_root = q.top();
	}
private:
	Node* _root;
};
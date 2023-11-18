// BitZip.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//Huffman编码压缩的过程
/*	1.统计源文件每个字节出现的个数
*	2.用字节频数创建Huffman树
*	3.获取每个字节的Huffman编码
*	4.用得到的编码对源文件中的每个字节进行改写
*/
#include "HuffmanTree.hpp"

int main()
{
	std::vector<int> vt = { 3,1,5,7 };
	HuffmanTree<int>h(vt);
}


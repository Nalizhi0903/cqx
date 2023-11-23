// BitZip.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//Huffman编码压缩的过程
/*	1.统计源文件每个字节出现的个数
*	2.用字节频数创建Huffman树
*	3.获取每个字节的Huffman编码
*	4.用得到的编码对源文件中的每个字节进行改写
*/

#include "HuffmanTree.hpp"
#include "FileCompressHuffman.hpp"
#include <iostream>

bool isQuit = false;

void menu()
{
	std::cout << "Huffman压缩软件" << std::endl;
	std::cout << "1.压缩" << std::endl;
	std::cout << "2.解压缩" << std::endl;
	std::cout << "0.退出" << std::endl;
	FileComprssHuffman fc;
	std::string filename;
	int select = 0;
	std::cin >> select;
	switch (select)
	{
	case 0:
		isQuit = true;
		break;
	case 1:
		std::cout << "请输入压缩的文件名称" << std::endl;
		cin >> filename;
		fc.CompressFile(filename);
		break;
	case 2:
		std::cout << "请输入解压缩的文件名称" << std::endl;
		cin >> filename;
		fc.UnCompressFile(filename);
		break;
	}
}
int main()
{
	while (true)
	{
		menu();
		if (isQuit == true)
		{
			std::cout << "bye" << std::endl;
			break;
		}
	}
}


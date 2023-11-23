#pragma once
#include "HuffmanTree.hpp"
#include <vector>
#include <string>
using namespace std;
struct ByteInfo
{
	unsigned char _ch;
	size_t _appearCount;
	string _chCode;
	ByteInfo(size_t appearCount = 0):_appearCount(appearCount)
	{}
	ByteInfo operator+(const ByteInfo& other)const 
	{
		return ByteInfo(_appearCount + other._appearCount);
	}
	bool operator>(const ByteInfo& other)const
	{
		return _appearCount > other._appearCount;
	}
	bool operator!=(const ByteInfo& other)const
	{
		return _appearCount != other._appearCount;
	}
	bool operator==(const ByteInfo& other)const
	{
		return _appearCount == other._appearCount;
	}
};

class FileComprssHuffman
{
public:
	FileComprssHuffman();
public:
	void CompressFile(const string& FilePath);
	void UnCompressFile(const string& FilePath);
private:
	void GenerateHuffmanCode(HuffmanTreeNode<ByteInfo>* root);
	void WriteHeadInfo(const string& filepath, FILE* fIn);
	string GetFilePostFix(const string& filePath);
	void GetLine(FILE* fIn, string& strInfo);
private:
	vector<ByteInfo> _fileinfo;
};
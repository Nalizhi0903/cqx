#define _CRT_SECURE_NO_WARNINGS
#include "FileCompressHuffman.hpp"
#include "Common.h"
#include <iostream>
using namespace std;
FileComprssHuffman::FileComprssHuffman()
{
	_fileinfo.resize(256);
	for (int i = 0; i < 256; i++)
	{
		_fileinfo[i]._ch = i;
	}
}

void FileComprssHuffman::CompressFile(const string& FilePath)
{
	//1.ͳ��Դ�ļ���ÿ���ַ����ֵĴ���
	FILE* fIn = fopen(FilePath.c_str(), "rb");
	if (fIn == nullptr)
	{
		cout << "��ѹ���ļ�������" << endl;
		return;
	}
	uch rdBuff[1024];
	while (true)
	{
		size_t rd_size = fread(rdBuff, 1, 1024, fIn);
		if (rd_size == 0)
		{
			break;
		}

		for (size_t i = 0; i < rd_size; i++)
		{
			_fileinfo[rdBuff[i]]._appearCount++;
		}
	}
	//��ͳ�ƽ������Huffman��
	ByteInfo valid;
	HuffmanTree<ByteInfo> ht(_fileinfo, valid);

	//��ȡHuffman����
	GenerateHuffmanCode(ht.GetRoot());

	//д������ѹ����������Ϣ
	FILE* fOut = fopen("2.hz", "wb");
	WriteHeadInfo(FilePath, fOut);
	
	//�û�ȡ���ı����Դ�ļ���д
	fseek(fIn, 0, SEEK_SET);//fInָ���ļ���ͷ
	uch bits = 0;
	int bitCount = 0;
	while (true)
	{
		
		size_t rd_size = fread(rdBuff, 1, 1024, fIn);
		if (rd_size == 0)
		{
			break;
		}
		for (size_t i = 0; i < rd_size; i++)
		{
			string& strCode = _fileinfo[rdBuff[i]]._chCode;
			for (size_t j = 0; j < strCode.size(); j++)
			{
				bits <<= 1;
				if (strCode[j] == '1')
					bits |= 1;
				bitCount++;
				if (bitCount == 8)
				{
					fputc(bits, fOut);
					bits = 0;
					bitCount = 0;
				}
			}
		}
		//���һ�ε�bits�е�8������λû�������
		if (bitCount > 0 || bitCount < 8)
		{
			bits <<= (8 - bitCount);
			fputc(bits, fOut);
		}
	}
	std::fclose(fIn);
	std::fclose(fOut);
}

void FileComprssHuffman::GenerateHuffmanCode(HuffmanTreeNode<ByteInfo>* root)
{
	if (root == nullptr)
	{
		return;
	}

	GenerateHuffmanCode(root->_left);
	GenerateHuffmanCode(root->_right);

	//rootΪҶ�ӽ��
	if (root->_left == nullptr && root->_right == nullptr)
	{
		std::string& chCode = _fileinfo[root->_weight._ch]._chCode;
		HuffmanTreeNode<ByteInfo>* cur = root;
		HuffmanTreeNode<ByteInfo>* parent = cur->_parent;
		while (parent)
		{
			if (cur == parent->_left)
			{
				chCode += '0';
			}
			else
			{
				chCode += '1';
			}
			cur = parent;
			parent = cur->_parent;
		}
		reverse(chCode.begin(), chCode.end());
	}
}


void FileComprssHuffman::WriteHeadInfo(const string& filePath, FILE* fOut)
{
	//��ȡԴ�ļ���׺
	string headInfo;
	headInfo += GetFilePostFix(filePath);
	headInfo += '\n';
	//����Ƶ����Ϣ
	string chInfo;
	size_t appearLineCount = 0;
	for (auto& e : _fileinfo)
	{
		if (e._appearCount == 0)
		{
			continue;
		}
		chInfo += e._ch;
		chInfo += ':';
		chInfo += std::to_string(e._appearCount);
		chInfo += '\n';
		appearLineCount++;
	}
	headInfo += std::to_string(appearLineCount);
	headInfo += '\n';

	fwrite(headInfo.c_str(), 1, headInfo.size(), fOut);
	fwrite(chInfo.c_str(), 1, chInfo.size(), fOut);
}

string FileComprssHuffman::GetFilePostFix(const string& filePath)
{
	return filePath.substr(filePath.find_last_of('.') + 1);
}

void FileComprssHuffman::UnCompressFile(const string& FilePath)
{
	if (GetFilePostFix(FilePath) != "hz")
	{
		cout << "ѹ���ļ���ʽ����" << endl;
		return;
	}
	//1.��ȡѹ����Ҫ�õ�����Ϣ
	FILE* fIn = fopen(FilePath.c_str(), "rb");//Ҫ�ö����ƶ�ȡ�ļ���ʽ�������ı�FFΪ�ı���β��־���������ı�����
	if (fIn == nullptr)
	{
		cout << "��ѹ���ļ�·������" << endl;
		return;
	}

	//��ȡԴ�ļ���׺
	string unCompressFile("222.");
	string strInfo;
	GetLine(fIn, strInfo);
	unCompressFile += strInfo;
	//��ȡƵ����Ϣ������
	strInfo = "";
	GetLine(fIn, strInfo);
	size_t lineCount = atoi(strInfo.c_str());
	for (size_t i = 0; i < lineCount; ++i)
	{
		//������Ҫ���⴦��
		strInfo = "";
		GetLine(fIn, strInfo);
		if (strInfo == "")
		{
			strInfo += '\n';
			GetLine(fIn, strInfo);
		}	
		uch ch = strInfo[0];
		_fileinfo[ch]._ch = ch;
		_fileinfo[ch]._appearCount = atoi(strInfo.c_str() + 2);
	}
	//��ԭHuffman��
	HuffmanTree<ByteInfo> ht(_fileinfo, ByteInfo());

	//��ѹ��
	FILE* fOut = fopen(unCompressFile.c_str(), "wb");
	unsigned char rdBuff[1024];
	HuffmanTreeNode<ByteInfo>* cur = ht.GetRoot();
	size_t filesize = 0;
	while (true)
	{
		size_t rd_size = fread(rdBuff, 1, 1024, fIn);
		if (rd_size == 0)
		{
			break;
		}
		for (size_t i = 0; i < rd_size; i++)
		{
			unsigned char ch = rdBuff[i];
			for (int j = 0; j < 8; j++)
			{
				if (ch & 0x80)
				{
					cur = cur->_right;
				}
				else
				{
					cur = cur->_left;
				}
				if (cur->_left == nullptr && cur->_right == nullptr)
				{
					fputc(cur->_weight._ch, fOut);
					cur = ht.GetRoot();
					filesize += 1;
					if (filesize == cur->_weight._appearCount)
						break;
				}
				ch <<= 1;
			}
		}
	}
	fclose(fIn);
	fclose(fOut);
}

void FileComprssHuffman::GetLine(FILE* fIn, string& strInfo)
{
	//��û������βѭ��
	while (!feof(fIn))
	{
		unsigned char ch = fgetc(fIn);
		if (ch == '\n')
		{
			break;
		}
		strInfo += ch;
	}
}
#include <iostream>
#include <fstream>
#include <assert.h>
using namespace std;
//输入输出流
//ifstream ifile 只用输入
//ofstream ofile 只用输出
//fstream iofile 既输入又输出用
int main()
{
    //输出
    int ar[] = {12, 23, 34, 45, 56, 78, 89 , 90};
    int n = sizeof(ar) / sizeof(ar[0]);

    ofstream ofile("Test2.txt", ios::out);//调用构造函数时，打开文件
    /*
    ofstream ofile;
    ofile.open("Test2.txt", ios::out);
    */
    if(!ofile)
    {
        cout << "open faile" << endl;
        return 0;
    }
    for(int i=0; i< n; ++i)
        ofile << ar[i] << " ";
    ofile << endl;
    ofile.close();

    int br[10];
    ifstream ifile;
    ifile.open("Test2.txt", ios::in);
    assert(ifile);
    for(int i = 0; i < 10; ++i)
        ifile >> br[i];
    //输入
    for(auto& e:br)
    {
        cout << e << endl;
    }
    ifile.close();

    //二进制输出
    int cr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int nn = sizeof(cr) / sizeof(cr[0]);
    ofstream ofile1;
    ofile1.open("Test3.txt", ios::out|ios::binary);
    if(!ofile1)
    {
        printf("打开失败\n");
        return 0;
    }
    ofile1.write((const char*) cr, sizeof(int)*nn);
    ofile1.close();
    
    //二进制读入
    /*
    C语言的读取方式
    int dr[10];
    FILE* fp = fopen("Test3.txt", "rb");
    assert(fp != NULL);
    fread(ar, sizeof(int), 10, fp);
    fclose(fp);
    */ 
    
    int dr[10];
    ifstream ifile1;
    ifile1.open("Test3.txt", ios::in | ios::binary);
    assert(ifile1);
    ifile1.read((char*)dr, sizeof(int)*10);
    ifile1.close();

    return 0;
}

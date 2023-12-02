#include <iostream>
using namespace std;

//普通递归
int recursion(int n)
{
  if(n == 1)
  {
    return 1;
  }
  int res = recursion(n -1);//“递”，函数调用自身
  return n + res;//“归”，将当前递归层的结果回
}

//尾递归
//递归调用是函数返回前的最后一个操作，这意味着函数返回到上一层级后，无须继续执行其他操作，因此系统无须保存上一层函数的上下文
//被编译器或解释器优化，使其在空间效率上与迭代相当
int tail_recursion(int n, int res)
{
  if(n == 0)
  {
    return res;
  }
  return tail_recursion(n - 1, n + res);
}

/*普通递归：求和操作是在“归”的过程中执行的，每层返回后都要再执行一次求和操作。
 *尾递归：求和操作是在“递”的过程中执行的，“归”的过程只需层层返回*/
int main()
{
  cout << recursion(10) << endl; 
  cout << tail_recursion(10, 0) << endl;
  return 0;
}
/*递归函数每次调用自身时，系统都会为新开启的函数分配内存，以存储局部变量、调用地址和其他信息等。
这将导致两方面的结果。函数的上下文数据都存储在称为“栈帧空间”的内存区域中，直至函数返回后才会被释
。因此，递归通常比迭代更加耗费内存空间。递归调用函数会产生额外的开销。因此递归通常比循环的时间效率更低。*/

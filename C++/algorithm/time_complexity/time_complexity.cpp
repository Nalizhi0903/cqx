#include <iostream>
using namespace std;
//常数阶O(1)：常数阶的操作数量与输入数据大小 n无关，即不随着 n的变化而变化。
void constant()
{
  for(int i = 0; i < 10; i++)
  {
    cout << i << endl;
  }
}
//线性阶O(n)：线性阶的操作数量相对于输入数据大小 n以线性级别增长。线性阶通常出现在单层循环中。
void linear(int n)
{
  for(int i = 0; i < n; i++)
  {
    cout << i << endl;
  }
}
//平方阶O(n²)：平方阶的操作数量相对于输入数据大小 n以平方级别增长。平方阶通常出现在嵌套循环中，外层循环和内层循环的时间复杂度都为 O(n) ，因此总体的时间复杂度为 O(n²) 。
void squared(int n)
{
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      cout << i*j << endl;
    }
  }
}
//指数阶O(2^n)：生物学的“细胞分裂”是指数阶增长的典型例子：初始状态为 1 个细胞，分裂一轮后变为 2 个，分裂两轮后变为 4 个，以此类推，分裂n轮后有 2^n 个细胞。
void expontential(int n)
{
  int count = 0, base = 1;
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < base; j++)
    {
      count++;
    }
    base *= 2;
  }
}
//指数阶O(2^n)：生物学的“细胞分裂”是指数阶增长的典型例子：初始状态为 1 个细胞，分裂一轮后变为 2 个，分裂两轮后变为 4 个，以此类推，分裂n轮后有 2^n 个细胞。
int logarithmic(float n) {
    int count = 0;
    while (n > 1) {
        n = n / 2;
        count++;
    }
    return count;
}
//线性对数阶常出现于嵌套循环中，两层循环的时间复杂度分别为O(log n)和O(n)
int linearLogRecur(float n) {
    if (n <= 1)
        return 1;
    int count = linearLogRecur(n / 2) + linearLogRecur(n / 2);
    for (int i = 0; i < n; i++) {
        count++;
    }
    return count;
}
int factorialRecur(int n)
{
  if(n == 0)
  {
    return 1;
  }
  return factorialRecur(n -1)*n;
}


int main()
{
  int num = 0;
  cin >> num;
  cout << factorialRecur(num) << endl;
  return 0;
}

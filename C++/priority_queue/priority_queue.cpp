#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
  //priority_queue的底层结构就算堆
	vector<int> vt = { 4,6,2,7,8,9 };
  //默认大堆
	priority_queue<int> pq;
	for (auto& e : vt)
	{
		pq.push(e);
	}
  // 如果要创建小堆，将第三个模板参数换成greater比较方式
  priority_queue<int, vector<int>, greater<int>> pq2(vt.begin(), vt.end());
	cout << pq.top() << endl;
	cout << pq2.top() << endl;
  return 0;
}

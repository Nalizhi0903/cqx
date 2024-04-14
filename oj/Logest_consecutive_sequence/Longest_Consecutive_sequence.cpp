#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

class Solution {
public:
	int longestConsecutive(vector<int>& nums) {
		unordered_map<int, int> m;
		int result = 0;
		for (int n : nums) {
			if (m.find(n) != m.end()) continue;
			int left = m.find(n - 1) == m.end() ? 0 : m[n - 1];
			int right = m.find(n + 1) == m.end() ? 0 : m[n + 1];
			int len = left + right + 1;
			m[n] = 1;
			m[n - left] = m[n + right] = len;
			result = max(result, len);
		}
		return result;
		/*int len = 0;
		int res = 0;
		set<int> st(nums.begin(), nums.end());
		auto it = st.begin();
		int tmp = *it;
		while (it != st.end())
		{
			if (*it != tmp + 1)
			{
				len = 1;
				if (res < len)
					res = len;
				tmp = *it;
				it++;
			}
			else
			{
				tmp = *it;
				len++;
				it++;
				if (res < len)
					res = len;
			}
		}
		return res;*/
	}
};


int main()
{
	vector<int> nums = { 4,7,2,1,9,8,3 };
	set<int> st(nums.begin(), nums.end());
	Solution s;
	cout << s.longestConsecutive(nums);
	return 0;
}
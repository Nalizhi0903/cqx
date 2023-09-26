#include <iostream>
#include <vector>

using namespace std;

class solution
{
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> v;
        v.resize(numRows);
        for(int i = 0; i<numRows; i++)
        {
            v[i].resize(i+1, 0);
            v[i][0] = 1;
            v[i][i] = 1;
            for(int j = 1; j<i; j++)
            {
               v[i][j] = v[i - 1][j - 1] + v[i -1][j]; 
            }
        }
        return v;
    }
};

int main()
{
    solution s;
    vector<vector<int>> result = s.generate(5);
    vector<vector<int>>::iterator it = result.begin();
    while(it != result.end())
    {
        cout << "[";
        vector<int>::iterator it1 = it->begin();
        while(it1 != it->end())
        {
            cout << *it1 << " ";
            it1++;
        }
        cout << "]";
        it++;
    }
    cout << endl;
    return 0;
}

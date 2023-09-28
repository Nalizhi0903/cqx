#include <iostream>
#include <stack>
using namespace std;

class MinStack
{
public:
    MinStack()
    {
    }
    void push(int val)
    {
        if(min_stack.empty() || min_stack.top() >= val)
            min_stack.push(val);
        data_stack.push(val);
    }

    void pop()
    {
        int top_val = data_stack.top();
        data_stack.pop();
        if(top_val == min_stack.top())
            min_stack.pop();
    }
    int top()
    {
        return data_stack.top();
    }
    int GetMin()
    {
        return min_stack.top();
    }

private:
    stack<int> min_stack;
    stack<int> data_stack;
};

int main()
{
    MinStack st;
    st.push(9);
    //st.push(3);
    //st.push(5);
    //st.push(7);
    //cout << st.GetMin() << endl;
    return 0;
}

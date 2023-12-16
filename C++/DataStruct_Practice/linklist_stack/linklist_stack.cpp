#include <iostream>
using namespace std;

typedef struct Node 
{
  int data;
  Node* next;
  Node(int Data):data(Data){};
}Node;

class linkedliststack 
{
public:
  linkedliststack():stacktop(nullptr), stksize(0)
  {}
  ~linkedliststack()
  {}
public:
  int size()
  {
    return stksize;
  }
  void push(int data)
  {
    Node* new_node = new Node(data);
    new_node->next = stacktop;
    stacktop = new_node;
  }
  void pop()
  {
    if(empty())
    {
      perror("栈为空");
    }
    stacktop = stacktop->next;
  }
  int top()
  {
    if(empty())
    {
      perror("栈为空");
    }
    return stacktop->data;
  }
  bool empty()
  {
    if(stacktop == nullptr)
    {
      return true;
    }
    return false;
  }
private:
  Node* stacktop;
  size_t stksize;
};

int main()
{
  linkedliststack stack;
  stack.push(1);
  cout << stack.top() << endl;
  stack.push(2);
  cout << stack.top() << endl;
  stack.push(3);
  cout << stack.top() << endl;
  stack.pop();
  cout << stack.top() << endl;
  return 0;
}

#include <iostream>

typedef struct node 
{
  int data;
  node* next;
  node(int Data):data(Data),next(nullptr){};
}node;

class queue 
{
public:
  queue():front(nullptr), size(0)
  {}
  void push(int data)
  {
    node* new_data = new node(data); 
    if(front == nullptr)
    {
      front = new_data;
      rear = new_data;
    }
    else 
    {
      rear->next = new_data;
      rear = new_data;
    }
    size++;
  }
  void pop()
  {
    if(front == nullptr)
    {
      return;
    }
    front = front->next;
  }
  int show()
  {
    return front->data;
  }
private:
  node* front;
  node* rear;//尾结点
  size_t size;
};

int main()
{
  queue q;
  q.push(1);
  std::cout << q.show() << std::endl;
  q.push(2);
  q.pop();
  std::cout << q.show() << std::endl;
  return 0;
}


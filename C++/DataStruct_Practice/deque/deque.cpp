#include <iostream>

typedef struct ListNode 
{
  int data;
  ListNode* prev;
  ListNode* next;
  ListNode(int data, ListNode* PREV, ListNode* NEXT):data(data), prev(PREV), next(NEXT){};
}ListNode;

class deque 
{
public:
  deque():front(nullptr), rear(nullptr), size(0)
  {}
public:
  void front_push(int data)
  {
    ListNode* new_node = new ListNode(data, nullptr, nullptr);
    if(front == nullptr)
    {
      front = new_node;
      rear = new_node;
    }
    else 
    {
      front->prev = new_node;
      new_node->next = front;
      front = new_node;
    }
    size++;
  }
  void tail_push(int data)
  {
    ListNode* new_node = new ListNode(data, nullptr, nullptr);
    if(front == nullptr)
    {
      front = new_node;
      rear = new_node;
    }
    else 
    {
      rear->next = new_node;
      new_node->prev = rear;
      rear = new_node;
    }
    size++;
  }
  void pop_front()
  {
    if(front == nullptr)
    {
      return;
    }
    front = front->next;
    front->prev = nullptr;
  }
  void pop_tail()
  {
    if(rear == nullptr)
    {
      return;
    }
    rear = rear->prev;
    rear->next = nullptr;
  }
  int show_front()
  {
    return front->data;
  }
  int show_tail()
  {
    return rear->data;
  }
private:
  ListNode* front;
  ListNode* rear;
  size_t size;
};
int main()
{
  deque dq;
  dq.front_push(1);
  std::cout << dq.show_front() << std::endl;;
  dq.front_push(2);
  std::cout << dq.show_front() << std::endl;;
  dq.tail_push(3);
  std::cout << dq.show_tail() << std::endl;;
  dq.pop_front();
  std::cout << dq.show_front() << std::endl;;
  dq.pop_tail();
  std::cout << dq.show_tail() << std::endl;;
  return 0;
}

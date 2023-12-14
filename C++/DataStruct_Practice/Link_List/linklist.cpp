#include <iostream>

typedef struct ListNode
{
  int data;
  ListNode* next;
  ListNode(){};
  ListNode(int new_data):data(new_data),next(nullptr){};
  ListNode(int new_data, ListNode* node):data(new_data), next(node){};
}ListNode;

class List 
{
public:
  List():root(nullptr)
  {}
  ~List()
  {}
public:
  //头插
  void CreatList(int* arr, int num)
  {
    root = new ListNode();
    for(int i = 0; i < num; i++)
    {
      InsListNode(root, *arr);
      arr++;
    }
  }
  void InsListNode(ListNode* iNode, int data)
  {
    ListNode* new_node = new ListNode(data, iNode->next);
    iNode->next = new_node;
  }
  void DelListNode(int data)
  {
    ListNode* tmp = root->next; 
    while(tmp != nullptr)
    {
      if(tmp->next->data == data)
      {
        tmp->next = tmp->next->next; 
        break;
      }
      tmp = tmp->next;
    }
  }
  void showList()
  {
    ListNode* tmp = root->next;
    while(tmp != nullptr)
    {
      std::cout << tmp->data << std::endl;
      tmp = tmp->next;
    }
  }
public:
  ListNode* root;
};

int main()
{
  int arr[5] = {1,2,3,4,5};
  List l;
  l.CreatList(arr, 5);
  l.showList();
  l.DelListNode(3);
  l.showList();
  return 0;
}

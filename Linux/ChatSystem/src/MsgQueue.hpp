#include <iostream>
#include <pthread.h>
#include <queue>

using namespace std;
#define CAPACITY 10
template<class T>
class MsgQueue
{
  public:
    MsgQueue():_capacity(CAPACITY)
    {
      pthread_mutex_init(&_lock, NULL);
      pthread_cond_init(&_cons_cond, NULL);
      pthread_cond_init(&_prod_cond, NULL);

    }
    ~MsgQueue()
    {
      pthread_mutex_destroy(&_lock);
      pthread_cond_destroy(&_cons_cond);
      pthread_cond_destroy(&_prod_cond);
    }
  public:
    void Push(const T& msg)
    {
      pthread_mutex_lock(&_lock);
      while(_que.size() >= _capacity)
      {
        pthread_cond_wait(&_prod_cond, &_lock);
      }
      _que.push(msg);
      pthread_mutex_unlock(&_lock);
      pthread_cond_signal(&_cons_cond);
    }

    void Pop(T* msg)
    {
      pthread_mutex_lock(&_lock);
      while(_que.size() <= 0)
      {
        pthread_cond_wait(&_cons_cond, &_lock);
      }
      *msg = _que.front();
      _que.pop();
      pthread_mutex_unlock(&_lock);
      pthread_cond_signal(&_prod_cond);
    }
  private:
    queue<T> _que;
    size_t _capacity;

    pthread_mutex_t _lock;
    pthread_cond_t _cons_cond;
    pthread_cond_t _prod_cond;
};

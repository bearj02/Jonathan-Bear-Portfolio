/*
 * linked_queue.cpp
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 2 Written.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convience.
// No need to use them.
// Remove any of them if you want.
#include <algorithm>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "linked_queue.h"

using namespace std;

template <typename T>
T LinkedQueue<T>::front() const {
  // TODO
  //assert(!empty());
  //assert(false);
  //cout << this->head->value << endl;
  return (this->head->value);
}

template <typename T>
void LinkedQueue<T>::pop() {
  // TODO
  //assert(!empty());
  //assert(false);
    if (this->size() > 1) {
        Node<T>* prev = this->head;
        this->head = this->head->next;
        --(this->count);
        delete prev;
    }
    else if(size() == 1){
        delete tail;
        head = nullptr;
        tail = nullptr;
        --(this->count);
    }

}

template <typename T>
void LinkedQueue<T>::push(T x) {
  // TODO
  //assert(false);
  Node<T>* newend = new Node<T>;
  newend->value = x;
  newend->next = nullptr;

  if (!head) {
      head = newend;
      tail = newend;
  }
  else {
      (tail)->next = newend;
      tail = newend;
      tail->next = nullptr;
  }
  ++(count);
}

template <typename T>
LinkedQueue<T>::~LinkedQueue() {
  // TODO
  //assert(false);
  if (!this->empty()) {
	  Node<T>* ptr = this->head;
	  while (ptr) {
		  Node<T>* nextptr = ptr->next;
		  delete ptr;
		  ptr = nextptr;
	  }
	  delete this->head;
      this->count = 0;
  }
}
/*
int main() {
    LinkedQueue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    cout << "size: " << queue.size() << endl;
    for (size_t i = 0; i < 4; ++i) {
        cout << "size: " << queue.size() << endl;
        cout << "for loop here 1 " << i << endl;
        cout << queue.front() << endl;
        cout << "for loop here 2 " << i << endl;
        queue.pop();
        cout << "for loop here 3 " << i << endl;
        cout << "size: " << queue.size() << endl;
    }
}*/
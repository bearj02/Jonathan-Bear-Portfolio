#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  List() : first(nullptr), last(nullptr) {}

  //EFFECTS:  returns true if the list is empty
  bool empty() const{
    return first == nullptr;
  }

  //EFFECTS: returns the number of elements in this List
  int size() const{
    if(empty()) return 0;
    int size = 0;
    Node* node_ptr = first;
    while(node_ptr){
      size++;
      node_ptr = node_ptr->next;
    }
    return size;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front(){
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(){
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum){
    Node* n = new Node;
    n->datum = datum;
    n->prev = nullptr;
    if(empty()){
      n->next = nullptr;
      first = last = n;
    }
    else{
      first->prev = n;
      n->next = first;
      first = n;
    }
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){
    Node* n = new Node;
    n->datum = datum;
    n->next = nullptr;
    if(empty()){
      n->prev = nullptr;
      first = last = n;
    }
    else{
      last->next = n;
      n->prev = last;
      last = n;
      
    }
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front(){
    assert(!empty());
    Node * current = first;
    if(size() > 1){
      first = current->next;
      first->prev = nullptr;
    }
    else{
      first = last = nullptr;
    }
    delete current;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back(){
    assert(!empty());
    Node * current = last;
    if(size() > 1){
      last = current->prev;
      last->next = nullptr;
    }
    else{
      first = last = nullptr;
    }
    delete current;
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear(){
    if(!empty()){
      while(size() > 0){
        pop_front();
      }
    }
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

  List(const List<T> & other) : List() {
    copy_all(other);
  }

  List &operator=(List &rhs){
    if(this != &rhs){
      clear();
      copy_all(rhs);
    }
    return *this;
  }

  ~List(){
    clear();
  }

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other){
    for(Node * n = other.first; n; n = n->next){
      push_back(n->datum);
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    Iterator() : node_ptr(nullptr) {}

    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    T & operator*() const{
      assert(node_ptr);
      return node_ptr->datum;
    }

    Iterator &operator++(){
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    bool operator==(Iterator rhs) const{
      if(node_ptr == rhs.node_ptr) return true;
      return false;
    }

    bool operator!=(Iterator rhs) const{
      if(node_ptr == rhs.node_ptr) return false;
      return true;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position
    Iterator(Node *p) : node_ptr(p) {}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const{
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i){
    //assert(contains(i));
    if(!empty()){
      Node* current = i.node_ptr;
      if(size() == 1){
        first = nullptr;
        last = nullptr;
      }
      else if(i.node_ptr == first){
        i.node_ptr->next->prev = nullptr;
        first = i.node_ptr->next;
      }
      else if(i.node_ptr == last){
        i.node_ptr->prev->next = nullptr;
        last = i.node_ptr->prev;
      }
      else{
        i.node_ptr->prev->next = i.node_ptr->next;
        i.node_ptr->next->prev = i.node_ptr->prev;
      }
      delete current;
    }
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum){
    Node* n = new Node;
    n->datum = datum;
    if(empty()){
      first = last = n;
    }
    else if(i.node_ptr == first){
      n->prev = nullptr;
      n->next = first;
      first->prev = n;
      first = n;
    }
    else if(i == end()){
      n->prev = last;
      n->next = nullptr;
      last->next = n;
      last = n;
    }
    else{
      n->prev = i.node_ptr->prev;
      n->next = i.node_ptr;
      i.node_ptr->prev->next = n;
      i.node_ptr->prev = n;
    }
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.



#endif // Do not remove this. Write all your code above this line.

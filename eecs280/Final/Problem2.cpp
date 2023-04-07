#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

class List {
public:
    struct Node {
        int datum;    // the element stored in this Node
        Node *next;   // the next Node or nullptr
        Node *prev;   // the previous Node or nullptr
    };

    List() : first(nullptr), last(nullptr){};

    // You can assume the Big 3 are implemented properly.

    // REQUIRES: list is not empty
    //           cutBefore points to a valid Node in the list
    // EFFECTS:  removes all Nodes before cutBefore and adds appendNode
    //           to the beginning of the list

    void replaceBefore(Node *cutBefore, Node *appendNode);

    // REQUIRES: list is not empty
    //           cutAfter points to a valid Node in the list
    // EFFECTS:  removes all Nodes after cutAfter and adds appendNode
    //           to the end of the list

    void replaceAfter(Node *cutAfter, Node *appendNode){
        for(Node * ptr = last; ptr->prev != cutAfter; ptr = ptr->prev){
            delete ptr;
        }
        cutAfter->next = appendNode;
        appendNode->prev = cutAfter;
    }

    // EFFECTS: Returns the sum of all the Nodes in the linked list.
    // Returns 0 if the list is empty.

    int sum();

    // EFFECTS: Returns the product of all the Nodes in the linked list.
    // Returns 1 if the list is empty.

    int product(){
        int product = 1;
        if(first == nullptr) return product;
        for(Node * ptr = first; ptr->next != nullptr; ptr = ptr->next){
            product *= ptr->datum;
        }
            return product;
    }

private:
  Node *first; // the first Node in the list or nullptr.
  Node *last;  // the last Node in the list or nullptr.
};

int main(){
    return 0;
}
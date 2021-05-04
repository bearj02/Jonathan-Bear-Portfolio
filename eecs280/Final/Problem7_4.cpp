#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;


struct Node {
  int datum;
  Node *left;
  Node *right;
};

//REQUIRES: root points to the root of a valid binary tree
//EFFECTS:  Returns number of nodes in the tree that have 
//          value equal to compare
int countEqual(const Node *root, int compare){
    int numleft = 0;
    if((root->left)) numleft = countEqual(root->left, compare);
    int numright = 0;
    if((root->right)) numright = countEqual(root->right, compare);

    return numleft + numright + (root->datum == compare);
}

int main(){
    Node three_one{1};
    Node three_two{7};
    Node three_three{1};
    Node two_one{2,&three_one};
    Node two_two{4,&three_two,&three_three};
    Node one{1,&two_one,&two_two};
    cout << countEqual(&one,280) << endl;
}
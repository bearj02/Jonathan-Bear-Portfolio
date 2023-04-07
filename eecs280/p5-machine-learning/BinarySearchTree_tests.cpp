// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"

using namespace std; //check this 

TEST(test_1){
    BinarySearchTree<int> first; 

    first.insert(1);

    ASSERT_TRUE(first.size() == 1u); 
    ASSERT_TRUE(first.height() == 1u); 
    ASSERT_TRUE(!first.empty()); 
    first.insert(2); 
    ASSERT_TRUE(first.size() == 2u); 
    ASSERT_TRUE(first.height() == 2u); 
    first.insert(0); 
    ASSERT_TRUE(first.size() == 3u); 
    ASSERT_TRUE(first.height() == 2u); 
    ASSERT_TRUE(first.check_sorting_invariant()); 
}

TEST(test_2){
    BinarySearchTree<int> tree; 

    ASSERT_TRUE(tree.empty()); 
    ASSERT_TRUE(tree.end() == tree.begin());
    ASSERT_TRUE(tree.height() == 0u); 
    ASSERT_TRUE(tree.size() == 0u); 
    ASSERT_TRUE(tree.find(2) == tree.end()); 
    ASSERT_TRUE(tree.min_element() == tree.end()); 
    ASSERT_TRUE(tree.max_element() == tree.end()); 

    ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    cout << "preorder" << endl;
    cout << oss_preorder.str() << endl << endl;
    ASSERT_TRUE(oss_preorder.str() == "");

    ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    cout << "inorder" << endl;
    cout << oss_inorder.str() << endl << endl;
    ASSERT_TRUE(oss_inorder.str() == "");

    ASSERT_TRUE(tree.min_greater_than(20) == tree.end()); 

    BinarySearchTree<int> copy;

    tree = copy; 
    ASSERT_TRUE(tree.height() == 0u); 
    ASSERT_TRUE(tree.empty()); 
    BinarySearchTree<int> tree1(copy); 
    ASSERT_TRUE(tree1.size() == 0u); 
    ASSERT_TRUE(tree.check_sorting_invariant()); 
}

TEST(test_3){

    BinarySearchTree<double> tree; 
    ASSERT_TRUE(tree.empty()); 
    tree.insert(7.8); 
    tree.insert(8.7); 

    BinarySearchTree<double> tree1(tree); 
    ASSERT_TRUE(*tree.begin() == *tree1.begin());
    ASSERT_TRUE(tree.size() == 2u && tree1.size() == 2u); 
    ASSERT_TRUE(tree.height() == 2u && tree1.height() == 2u); 

    BinarySearchTree<double> tree2; 
    tree2.insert(9.9); 
    ASSERT_TRUE(tree2.size() == 1u); 
    tree2 = tree1; 
    ASSERT_TRUE(*tree.begin() == *tree.begin()); 
    ASSERT_TRUE(tree.size() == 2u ); 
    ASSERT_TRUE(tree.height() == 2u); 

}

TEST(test_5){
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty()); 
    tree.insert(10); 
    ASSERT_TRUE(!tree.empty()); 
    ASSERT_TRUE(tree.height() == 1u); 
    ASSERT_TRUE(tree.size() == 1u); 
    ASSERT_TRUE(*tree.min_element() == 10); 
    ASSERT_TRUE(*tree.max_element() == 10);
    ASSERT_TRUE(tree.min_greater_than(11) == tree.end()); 
    ASSERT_TRUE(tree.min_greater_than(1) == tree.begin()); 
    ASSERT_TRUE(tree.check_sorting_invariant()); 
    
    ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    cout << "preorder" << endl;
    cout << oss_preorder.str() << endl << endl;
    ASSERT_TRUE(oss_preorder.str() == "10 ");

    ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    cout << "inorder" << endl;
    cout << oss_inorder.str() << endl << endl;
    ASSERT_TRUE(oss_inorder.str() == "10 "); 
}

TEST(test_6){
    BinarySearchTree<int> tree; 
    tree.insert(10); 
    tree.insert(11); 
    tree.insert(9); 
    ASSERT_TRUE(tree.size() == 3u); 
    ASSERT_TRUE(tree.height() == 2u); 
    ASSERT_TRUE(*tree.min_element() == 9); 
    ASSERT_TRUE(*tree.max_element() == 11);
    ASSERT_TRUE(*tree.min_greater_than(10) == 11); 
    ASSERT_TRUE(*tree.min_greater_than(9) == 10); 
    ASSERT_TRUE(tree.min_greater_than(11) == tree.end()); 
    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_7){
    BinarySearchTree<int> tree; 
    tree.insert(10); 
    tree.insert(12); 
    tree.insert(14); 
    tree.insert(17); 
    tree.insert(19); 

    ASSERT_TRUE(tree.size() == 5u); 
    ASSERT_TRUE(tree.height() == 5u); 
    ASSERT_TRUE(*tree.min_element() == 10); 
    ASSERT_TRUE(*tree.max_element() == 19); 
    ASSERT_TRUE(*tree.min_greater_than(10) == 12); 
    ASSERT_TRUE(*tree.min_greater_than(13) == 14); 
    ASSERT_TRUE(*tree.min_greater_than(18) == 19); 
    ASSERT_TRUE(*tree.min_greater_than(9) == 10); 
    ASSERT_TRUE(tree.min_greater_than(20) == tree.end()); 


    //one sided tree on right
}

TEST(test_8){
    BinarySearchTree<int> tree; 
    tree.insert(10); 
    tree.insert(8); 
    tree.insert(6); 
    tree.insert(4); 
    tree.insert(2); 

    ASSERT_TRUE(tree.size() == 5u); 
    ASSERT_TRUE(tree.height() == 5u); 
    ASSERT_TRUE(*tree.min_element() == 2); 
    ASSERT_TRUE(*tree.max_element() == 10); 
    ASSERT_TRUE(tree.min_greater_than(10) == tree.end()); 
    ASSERT_TRUE(tree.min_greater_than(20) == tree.end()); 
    ASSERT_TRUE(*tree.min_greater_than(3) == 4); 
    ASSERT_TRUE(*tree.min_greater_than(0) == 2); 
    ASSERT_TRUE(*tree.min_greater_than(8) == 10); 
    //one sided tree on the left 
}

TEST(test_9){
    BinarySearchTree<int> tree; 
    tree.insert(10); 
    tree.insert(12); 
    tree.insert(8); 
    tree.insert(9); 
    tree.insert(11); 
    tree.insert(7); 
    tree.insert(6);  

    ASSERT_TRUE(tree.size() == 7u); 
    ASSERT_TRUE(tree.height() == 4u); 
    ASSERT_TRUE(*tree.min_element() == 6); 
    ASSERT_TRUE(*tree.max_element() == 12); 
    ASSERT_TRUE(tree.min_greater_than(13) == tree.end()); 
    ASSERT_TRUE(tree.min_greater_than(12) == tree.end()); 
    ASSERT_TRUE(*tree.min_greater_than(10) == 11); 
    ASSERT_TRUE(*tree.min_greater_than(8) == 9); 
    ASSERT_TRUE(*tree.min_greater_than(6) == 7); 
    ASSERT_TRUE(*tree.min_greater_than(0) == 6); 
    ASSERT_TRUE(*tree.min_greater_than(11) == 12); 
    ASSERT_TRUE(*tree.min_greater_than(7) == 8);

    BinarySearchTree<int> tree1; 
    tree = tree1; 
    ASSERT_TRUE(tree.empty()); 
    //uneven sided tree 
}

TEST(test_10){
    BinarySearchTree<int> tree; 
    tree.insert(10); 
    tree.insert(8); 
    *tree.begin() = 11;
    ASSERT_FALSE(tree.check_sorting_invariant());  
}

//TEST(test_11){
//check iterators
//}

TEST_MAIN()

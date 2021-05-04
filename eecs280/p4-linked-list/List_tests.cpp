// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_pushes) {
    List<int> list;
    ASSERT_EQUAL(list.size(), 0);
    ASSERT_TRUE(list.empty());

    list.push_back(1);
    ASSERT_EQUAL(list.size(), 1);
    ASSERT_FALSE(list.empty());
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(),1);

    list.push_front(2);
    list.push_back(3);
    ASSERT_EQUAL(list.size(), 3);
    ASSERT_EQUAL(list.front(), 2);
    ASSERT_EQUAL(list.back(),3);
    ASSERT_FALSE(list.empty());

    List<int> list2;
    ASSERT_EQUAL(list2.size(), 0);
    ASSERT_TRUE(list2.empty());

    list2.push_front(1);
    ASSERT_EQUAL(list2.size(), 1);
    ASSERT_FALSE(list2.empty());
    ASSERT_EQUAL(list2.front(), 1);
    ASSERT_EQUAL(list2.back(),1);

    list2.push_front(2);
    list2.push_back(3);
    ASSERT_EQUAL(list2.size(), 3);
    ASSERT_EQUAL(list2.front(), 2);
    ASSERT_EQUAL(list2.back(),3);
    ASSERT_FALSE(list2.empty());
}

TEST(test_insert){

    List<int> list;
    list.push_back(1);
    list.push_front(2);
    list.push_back(3);

    List<int>::Iterator begin_iter = list.begin();
    list.insert(begin_iter, 3);
    ASSERT_EQUAL(list.front(),3);
    List<int>::Iterator end_iter = list.end();
    list.insert(end_iter, 4);
    ASSERT_EQUAL(list.back(), 4);
    List<int>::Iterator iter = list.begin();
    ++++iter;
    list.insert(iter,5);
    --iter;
    ASSERT_EQUAL(*iter,5);
}

TEST(test_erase){

    List<int> list;
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    list.push_back(3);
    list.push_back(4);

    
    List<int>::Iterator iter = list.begin();
    ++++iter;
    list.erase(iter);
    List<int>::Iterator iter2 = list.begin();
    ++++iter2;
    ASSERT_EQUAL(*iter2, 3);

    List<int>::Iterator begin_iter = list.begin();
    list.erase(begin_iter);
    ASSERT_EQUAL(list.front(),2);

    List<int>::Iterator end_iter = list.begin();
    ++++end_iter;
    ASSERT_EQUAL(*end_iter,4);
    list.erase(end_iter);
    ASSERT_EQUAL(list.back(), 3);
    
}

TEST(test_pops){
    List<int> list;
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    list.push_back(3);
    list.push_back(4);

    ASSERT_EQUAL(list.size(), 5);
    ASSERT_FALSE(list.empty());

    ASSERT_EQUAL(list.back(),4);
    list.pop_back();
    ASSERT_EQUAL(list.back(),3);

    ASSERT_EQUAL(list.front(), 3);
    list.pop_front();
    ASSERT_EQUAL(list.front(), 2);

    List<int> list2;
    list2.push_front(1);
    ASSERT_EQUAL(list2.back(),1);
    ASSERT_EQUAL(list2.front(),1);
    list2.pop_back();
    ASSERT_TRUE(list2.empty());
    list2.push_front(1);
    list2.pop_front();
    ASSERT_TRUE(list2.empty());

}

TEST(test_clear){
    List<int> list;
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    list.push_back(3);
    list.push_back(4);

    ASSERT_EQUAL(list.size(), 5);
    ASSERT_FALSE(list.empty());

    list.clear();

    ASSERT_EQUAL(list.size(), 0);
    ASSERT_TRUE(list.empty());

    List<int> empty_list;
    ASSERT_EQUAL(empty_list.size(), 0);
    ASSERT_TRUE(empty_list.empty());
    empty_list.clear();
    ASSERT_EQUAL(empty_list.size(), 0);
    ASSERT_TRUE(empty_list.empty());
}

TEST(test_iterator_operators){
    List<int> list;
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    list.push_back(3);
    list.push_back(4);

    List<int>::Iterator iter = list.begin();
    ASSERT_EQUAL(*iter, 3);
    ++iter;
    ASSERT_EQUAL(*iter,2);
    ++++iter;
    ASSERT_EQUAL(*iter,3);
    --iter;
    ASSERT_EQUAL(*iter,1);
    ----iter;
    ASSERT_EQUAL(*iter,3);
    --++iter;
    ASSERT_EQUAL(*iter,3);
    List<int>::Iterator iter2 = list.begin();
    ASSERT_TRUE(iter == iter2);
    ++iter2;
    ASSERT_TRUE(iter != iter2);
    
    List<int>::Iterator end = list.end();
    List<int>::Iterator begin = list.begin();
    --begin;
    ASSERT_TRUE(begin == end);
    ASSERT_FALSE(iter == end);
    ASSERT_TRUE(iter != end);
    ASSERT_FALSE(begin != end);
}

TEST(test_copy_ctor){
    List<int> list;
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    list.push_back(3);
    list.push_back(4);

    List<int> copied_list(list);
    ASSERT_EQUAL(list.front(),copied_list.front());
    ASSERT_EQUAL(list.back(),copied_list.back());

    List<int> a;
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    list.push_back(3);
    list.push_back(4);

    List<int> c;

    List<int> b(c = a);

    List<int>::Iterator iter = a.begin();
    List<int>::Iterator iter2 = b.begin();
    List<int>::Iterator iter3 = c.begin();
    while(iter != a.end()){
        ASSERT_EQUAL(*iter,*iter2);
        ASSERT_EQUAL(*iter,*iter3);
        ASSERT_EQUAL(*iter2,*iter3);
        ++iter;
        ++iter2;
        ++iter3;
    }
}

TEST(test_assignment_op){
    List<int> list;
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    list.push_back(3);
    list.push_back(4);

    List<int> list2;
    list.push_back(4);
    list.push_back(5);
    list.push_back(10);
    list.push_back(-2);
    list.push_back(7);

    list2 = list;
    List<int>::Iterator iter = list.begin();
    List<int>::Iterator iter2 = list2.begin();
    while(iter != list.end()){
        ASSERT_EQUAL(*iter,*iter2);
        ++iter;
        ++iter2;
    }

    List<int> list3;
    list3 = list;
    iter = list.begin();
    List<int>::Iterator iter3 = list3.begin();
    while(iter != list.end()){
        ASSERT_EQUAL(*iter,*iter3);
        ++iter;
        ++iter3;
    }

    List<int> list4;
    List<int> list5;
    list5.push_back(3);
    list5.push_back(5);
    list5.push_back(-2);

    ASSERT_FALSE(list5.empty());
    list5 = list4;
    ASSERT_TRUE(list5.empty());
}

TEST_MAIN()

// Project identifier: 0E04A31E0D60C01986ACB20081C9D8722A1899B6

/*
 * Compile this test against your .h files to make sure they compile. Note how
 * the eecs281 priority queues can be constructed with the different types. We
 * suggest adding to this file or creating your own test cases to test your
 * priority queue implementations more thoroughly.  If you do not call a
 * function from here, it is NOT compiled due to templates!  So for instance,
 * if you don't add code to call updatePriorities(), you could have compiler
 * errors that you don't even know about.
 *
 * Our makefile will build an executable named testPQ if you type 'make testPQ'
 * or 'make alltests' (without the quotes).
 *
 * Notice that testPairing() tests the range-based constructor but main() and
 * testPriorityQueue() do not.  Make sure to test the range-based constructor
 * for other PQ types, and also test the PairingPQ-specific member functions.
 *
 * This is NOT a complete test of your priority queues, you have to add code
 * to do more testing!
 *
 * You do not have to submit this file, but it won't cause problems if you do.
 */

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "Eecs281PQ.h"
#include "BinaryPQ.h"
#include "UnorderedPQ.h"
#include "PairingPQ.h"
#include "SortedPQ.h"

using namespace std;


// Used to test a priority queue containing pointers to integers.
struct IntPtrComp {
    bool operator() (const int *a, const int *b) const {
        return *a < *b;
    }
};


// TODO: Make sure that you're using this-compare() properly, and everywhere
// that you should.  Complete this function by adding a functor that compares
// two HiddenData structures, create a PQ of the specified type, and call
// this function from main().
void testHiddenData(const string &pqType) {
    struct HiddenData {
        int data;
    };
    struct HiddenDataComp {
        bool operator()(const HiddenData &a, const HiddenData &b) const {
            // TODO: Finish this functor; when you do, uncomment the
            // parameters in the line above
            return a.data < b.data;
        }
    };

    cout << "Testing " << pqType << " with hidden data" << endl;

    // TODO: Add code here to actually test with the HiddenData type.
} // testHiddenData()


// TODO: Add more code to this function to test if updatePriorities()
// is working properly.
void testUpdatePrioritiesHelper(Eecs281PQ<int *, IntPtrComp> *pq) {
    vector<int> data;
    data.reserve(100);
    /*int i;
    while(cin >> i){
        data.push_back(i);
    }*/
    data.push_back(10);
    data.push_back(25);
    data.push_back(37);
    data.push_back(18);
    data.push_back(81);

    // NOTE: If you add more data to the vector, don't push the pointers
    // until AFTER the vector stops changing size!  Think about why.
    // You can add up to 100 values, or change the reserve if you want more.

    for (size_t i = 0; i < data.size(); ++i) {
        pq->push(&data[i]);
    } // for

    // Change the first value (which is pointed to by the pq), and check it.
    cout << *(pq->top()) << "\n";
    data[1] = 120;
    pq->updatePriorities();
    cout << *(pq->top()) << "\n";

    assert(*pq->top() == 120);
} // testUpdatePrioritiesHelper()


// TODO: Add more code to this function to test if updatePriorities()
// is working properly.
void testUpdatePriorities(const string &pqType) {
    Eecs281PQ<int *, IntPtrComp> *pq = nullptr;
    cout << "Testing updatePriorities() on " << pqType << endl;

    if (pqType == "Unordered") {
        pq = new UnorderedPQ<int *, IntPtrComp>;
    } // if
    // TODO: Add more types here inside 'else if' statements, like in main().
    else if(pqType == "Sorted"){
        pq = new SortedPQ<int *, IntPtrComp>;
    }
    else if(pqType == "Binary"){
        pq = new BinaryPQ<int *, IntPtrComp>;
    }
    else if(pqType == "Pairing"){
        pq = new PairingPQ<int *, IntPtrComp>;
    }

    if (!pq) {
        cout << "Invalid pq pointer; did you forget to create it?" << endl;
        return;
    } // if

    testUpdatePrioritiesHelper(pq);
    delete pq;
} // testUpdatePriorities()

void printSorted(vector<int> data){
    SortedPQ<int> *pq2 = new SortedPQ<int>(data.begin(),data.end());
    while(pq2->size() > 0){
        cout << pq2->top() << "\n";
        pq2->pop();
    }
    delete pq2;
}


// Very basic testing.
void testPriorityQueue(Eecs281PQ<int> *pq, const string &pqType) {
    cout << "Testing priority queue: " << pqType << endl;

    

    if(pqType.compare("Sorted") == 0){
        vector<int> vec;
        int i = 0;
        cout << "here\n";
        while(cin >> i >> ws){
            vec.push_back(i);
        }
        cout << "here\n";
        Eecs281PQ<int> *pq2;
        cout << "here\n";
        pq2 = new SortedPQ<int>(vec.begin(),vec.end());
        //printSorted(vec);
        cout << "size: " << pq2->size() << "\n";
        cout << "top: " << pq2->top() << "\n";
        assert(pq2->size() == 10000);
        assert(pq2->top() == 99995);
        delete pq2;
    }

    if(pqType.compare("Binary") == 0){
        vector<int> vec = {3, 24, 16, 1, 40, 27, 8, 13, 3, 5};
        Eecs281PQ<int> *pq3;
        pq3 = new BinaryPQ<int>(vec.begin(),vec.end());
        //40, 24, 27, 13, 5, 16, 8, 1, 3, 3
        assert(pq3->size() == 10);
        assert(pq3->top() == 40);
        pq3->pop();
        assert(pq3->top() == 27);
        pq3->pop();
        assert(pq3->top() == 24);
        pq3->pop();
        assert(pq3->top() == 16);
        pq3->pop();
        assert(pq3->top() == 13);
        pq3->pop();
        assert(pq3->top() == 8);
        pq3->pop();
        assert(pq3->top() == 5);
        pq3->pop();
        assert(pq3->top() == 3);
        pq3->pop();
        assert(pq3->top() == 3);
        pq3->pop();
        assert(pq3->top() == 1);
        delete pq3;
    }
    pq->pop();
    pq->push(3);
    pq->push(4);
    assert(pq->size() == 2);
    assert(pq->top() == 4);

    pq->pop();
    assert(pq->size() == 1);
    assert(pq->top() == 3);
    assert(!pq->empty());

    pq->pop();
    assert(pq->size() == 0);
    assert(pq->empty());

    // TODO: Add more testing here!
    pq->push(3);
    pq->push(4);
    pq->push(2);
    assert(pq->size() == 3);
    assert(pq->top() == 4);

    

    cout << "testPriorityQueue() succeeded!" << endl;
} // testPriorityQueue()


// Test the pairing heap's range-based constructor, copy constructor,
// and operator=().
//

void printPairing(Eecs281PQ<int> *pq){
    Eecs281PQ<int> * pq2 = new PairingPQ<int>(*((PairingPQ<int> *)pq));
    while(pq2->size() > 0){
        cout << pq2->top() << "\n";
        pq2->pop();
    }
    delete pq2;
}

//10, 25, 81, 37, 10
void testRangeCtor(){
    cout << "\nTesting Pairing Heap Range constructor\n\n";
    vector<int> vec;
    vec.push_back(10);
    vec.push_back(0);
    vec.push_back(81);
    vec.push_back(37);
    vec.push_back(10);
    PairingPQ<int> * pq = new PairingPQ<int>(vec.begin(), vec.end());
    assert(pq->size() == 5);
    cout << pq->top() << "\n";
    assert(pq->top() == 81);
    pq->pop();
    assert(pq->size() == 4);
    cout << pq->top() << "\n";
    assert(pq->top() == 37);
    pq->pop();
    assert(pq->size() == 3);
    cout << pq->top() << "\n";
    assert(pq->top() == 10);
    pq->pop();
    assert(pq->size() == 2);
    cout << pq->top() << "\n";
    assert(pq->top() == 10);
    pq->pop();
    assert(pq->size() == 1);
    cout << pq->top() << "\n";
    assert(pq->top() == 0);
    pq->pop();
    delete pq;
}

void testAddNode(){
    cout << "\nTesting Pairing Heap addNode function\n\n";
    PairingPQ<int> * pq = new PairingPQ<int>;
    vector<int> vec;
    vec.push_back(10);
    vec.push_back(25);
    vec.push_back(81);
    vec.push_back(37);
    vec.push_back(18);
    vec.push_back(6);
    vec.push_back(25);
    vec.push_back(83);
    vec.push_back(49);
    vec.push_back(25);
    //6, 10, 18, 25, 25, 25, 37, 49, 81, 83
    for(size_t i = 0; i < vec.size(); ++i){
        int output = pq->addNode(vec[i])->getElt();
        assert(output == vec[i]);
        cout << output << "\n";
    }
    UnorderedPQ<int>* pq2 = new UnorderedPQ<int>(vec.begin(),vec.end());

    assert(pq->size() == 10);
    cout << pq->top() << "\n";
    assert(pq->top() == 83);
    pq->pop();
    assert(pq->size() == 9);
    cout << pq->top() << "\n";
    assert(pq->top() == 81);
    pq->pop();
    assert(pq->size() == 8);
    cout << pq->top() << "\n";
    assert(pq->top() == 49);
    pq->pop();
    assert(pq->size() == 7);
    cout << pq->top() << "\n";
    assert(pq->top() == 37);
    pq->pop();
    assert(pq->size() == 6);
    cout << pq->top() << "\n";
    assert(pq->top() == 25);
    pq->pop();
    assert(pq->size() == 5);
    cout << pq->top() << "\n";
    assert(pq->top() == 25);
    pq->pop();
    assert(pq->size() == 4);
    cout << pq->top() << "\n";
    assert(pq->top() == 25);
    pq->pop();
    assert(pq->size() == 3);
    cout << pq->top() << "\n";
    assert(pq->top() == 18);
    pq->pop();
    assert(pq->size() == 2);
    cout << pq->top() << "\n";
    assert(pq->top() == 10);
    pq->pop();
    assert(pq->size() == 1);
    cout << pq->top() << "\n";
    assert(pq->top() == 6);
    pq->pop();
    delete pq;

    assert(pq2->size() == 10);
    cout << pq2->top() << "\n";
    assert(pq2->top() == 83);
    pq2->pop();
    assert(pq2->size() == 9);
    cout << pq2->top() << "\n";
    assert(pq2->top() == 81);
    pq2->pop();
    assert(pq2->size() == 8);
    cout << pq2->top() << "\n";
    assert(pq2->top() == 49);
    pq2->pop();
    assert(pq2->size() == 7);
    cout << pq2->top() << "\n";
    assert(pq2->top() == 37);
    pq2->pop();
    assert(pq2->size() == 6);
    cout << pq2->top() << "\n";
    assert(pq2->top() == 25);
    pq2->pop();
    assert(pq2->size() == 5);
    cout << pq2->top() << "\n";
    assert(pq2->top() == 25);
    pq2->pop();
    assert(pq2->size() == 4);
    cout << pq2->top() << "\n";
    assert(pq2->top() == 25);
    pq2->pop();
    assert(pq2->size() == 3);
    cout << pq2->top() << "\n";
    assert(pq2->top() == 18);
    pq2->pop();
    assert(pq2->size() == 2);
    cout << pq2->top() << "\n";
    assert(pq2->top() == 10);
    pq2->pop();
    assert(pq2->size() == 1);
    cout << pq2->top() << "\n";
    assert(pq2->top() == 6);
    pq2->pop();
    delete pq2;
}

void testUpdateElt(){
    cout << "\nTesting Pairing Heap updateElt function\n\n";
    PairingPQ<int *, IntPtrComp> * pq = new PairingPQ<int *, IntPtrComp>;
    vector<int> vec;
    vec.push_back(10);
    vec.push_back(25);
    vec.push_back(81);
    vec.push_back(37);
    vec.push_back(18);
    vec.push_back(6);
    vec.push_back(25);
    vec.push_back(83);
    vec.push_back(49);
    vec.push_back(25);
    //6, 10, 18, 25, 25, 25, 37, 49, 81, 83
    for(size_t i = 0; i < vec.size(); ++i)
        cout << "Added " << *(pq->addNode(&vec[i])->getElt()) << " to the PQ\n";
    
    cout << "\nOriginal PQ:\n\n";
    assert(pq->size() == 10);
    cout << *(pq->top()) << "\n";
    assert(*(pq->top()) == 83);
    pq->pop();
    assert(pq->size() == 9);
    cout << *(pq->top()) << "\n";
    assert(*(pq->top()) == 81);
    pq->pop();
    assert(pq->size() == 8);
    cout << *(pq->top()) << "\n";
    assert(*(pq->top()) == 49);
    pq->pop();
    assert(pq->size() == 7);
    cout << *(pq->top()) << "\n";
    assert(*(pq->top()) == 37);
    pq->pop();
    assert(pq->size() == 6);
    cout << *(pq->top()) << "\n";
    assert(*(pq->top()) == 25);
    pq->pop();
    assert(pq->size() == 5);
    cout << *(pq->top()) << "\n";
    assert(*(pq->top()) == 25);
    pq->pop();
    assert(pq->size() == 4);
    cout << *(pq->top()) << "\n";
    assert(*(pq->top()) == 25);
    pq->pop();
    assert(pq->size() == 3);
    cout << *(pq->top()) << "\n";
    assert(*(pq->top()) == 18);
    pq->pop();
    assert(pq->size() == 2);
    cout << *(pq->top()) << "\n";
    assert(*(pq->top()) == 10);
    pq->pop();
    assert(pq->size() == 1);
    cout << *(pq->top()) << "\n";
    assert(*(pq->top()) == 6);
    pq->pop();

    PairingPQ<int> * pq1 = new PairingPQ<int>;
    pq1->addNode(vec[0]);
    PairingPQ<int>::Node* a = pq1->addNode(vec[1]); //25
    pq1->addNode(vec[2]);
    PairingPQ<int>::Node* b = pq1->addNode(vec[3]); //37
    pq1->addNode(vec[4]);
    PairingPQ<int>::Node* c = pq1->addNode(vec[5]); //6
    pq1->addNode(vec[6]);
    PairingPQ<int>::Node* d = pq1->addNode(vec[7]); //83
    pq1->addNode(vec[8]);
    PairingPQ<int>::Node* e = pq1->addNode(vec[9]); //25
    cout << "\ntry 1: ";
    pq1->updateElt(a,100);
    cout << a->getElt() << "\n";
    cout << "try 2: ";
    pq1->updateElt(b,50);
    cout << b->getElt() << "\n";
    cout << "try 3: ";
    pq1->updateElt(c,50);
    cout << c->getElt() << "\n";
    cout << "try 4: ";
    pq1->updateElt(d,99);
    cout << d->getElt() << "\n";
    cout << "try 5: ";
    pq1->updateElt(e,32);
    cout << e->getElt() << "\n";
    cout << "\nhere\n";
    //10, 18, 25, 32, 49, 50, 50, 81, 99, 100
    cout << "here\n";
    cout << "\nUpdated PQ:\n\n";
    assert(pq1->size() == 10);
    cout << pq1->top() << "\n";
    assert(pq1->top() == 100);
    pq1->pop();
    assert(pq1->size() == 9);
    cout << pq1->top()<< "\n";
    assert(pq1->top() == 99);
    pq1->pop();
    assert(pq1->size() == 8);
    cout << pq1->top() << "\n";
    assert(pq1->top() == 81);
    pq1->pop();
    assert(pq1->size() == 7);
    cout << pq1->top() << "\n";
    assert(pq1->top() == 50);
    pq1->pop();
    assert(pq1->size() == 6);
    cout << pq1->top() << "\n";
    assert(pq1->top() == 50);
    pq1->pop();
    assert(pq1->size() == 5);
    cout << pq1->top() << "\n";
    assert(pq1->top() == 49);
    pq1->pop();
    assert(pq1->size() == 4);
    cout << pq1->top() << "\n";
    assert(pq1->top() == 32);
    pq1->pop();
    assert(pq1->size() == 3);
    cout << pq1->top() << "\n";
    assert(pq1->top() == 25);
    pq1->pop();
    assert(pq1->size() == 2);
    cout << pq1->top() << "\n";
    assert(pq1->top() == 18);
    pq1->pop();
    assert(pq1->size() == 1);
    cout << pq1->top() << "\n";
    assert(pq1->top() == 10);
    pq1->pop();

    delete pq1;
    delete pq;
}

void testCopyOpCtor(vector<int> & vec){
    cout << "\nTesting Pairing Heap Copy constructor and Assignment Operator\n";
    PairingPQ<int> * pqa = new PairingPQ<int>();
    for(int i : vec) pqa->push(i);
    PairingPQ<int> * pq1 = new PairingPQ<int>(*pqa);
    PairingPQ<int> * pq2 = new PairingPQ<int>();
    pq2->push(2);
    pq2->push(100);
    *pq2 = *pqa;
    pqa->pop();
    pqa->pop();
    pqa->pop();
    pqa->pop();
    pqa->pop();
    
    cout << "\nCopy Ctor: \n\n";
    assert(pq1->size() == 5);
    cout << pq1->top() << "\n";
    assert(pq1->top() == 81);
    pq1->pop();
    assert(pq1->size() == 4);
    cout << pq1->top() << "\n";
    assert(pq1->top() == 37);
    pq1->pop();
    assert(pq1->size() == 3);
    cout << pq1->top() << "\n";
    assert(pq1->top() == 25);
    pq1->pop();
    assert(pq1->size() == 2);
    cout << pq1->top() << "\n";
    assert(pq1->top() == 10);
    pq1->pop();
    assert(pq1->size() == 1);
    cout << pq1->top() << "\n";
    assert(pq1->top() == 10);
    pq1->pop();
    delete pq1;
    cout << "\nAssignment Operator:\n\n";
    assert(pq2->size() == 5);
    cout << pq2->top() << "\n";
    assert(pq2->top() == 81);
    pq2->pop();
    assert(pq2->size() == 4);
    cout << pq2->top() << "\n";
    assert(pq2->top() == 37);
    pq2->pop();
    assert(pq2->size() == 3);
    cout << pq2->top() << "\n";
    assert(pq2->top() == 25);
    pq2->pop();
    assert(pq2->size() == 2);
    cout << pq2->top() << "\n";
    assert(pq2->top() == 10);
    pq2->pop();
    assert(pq2->size() == 1);
    cout << pq2->top() << "\n";
    assert(pq2->top() == 10);
    pq2->pop();
    delete pq2;
    delete pqa;
}

void testPairing(vector<int> & vec) {
    cout << "Testing Pairing Heap separately" << endl;
    Eecs281PQ<int> * pq1 = new PairingPQ<int>(vec.begin(), vec.end());
    cout << "pq1 made\n";
    Eecs281PQ<int> * pq2 = new PairingPQ<int>(*((PairingPQ<int> *)pq1));
    cout << "pq2 made\n";
    // This line is different just to show two different ways to declare a
    // pairing heap: as an Eecs281PQ and as a PairingPQ. Yay for inheritance!
    PairingPQ<int> * pq3 = new PairingPQ<int>();
    
    cout << "pq3 made\n";
    *pq3 = *((PairingPQ<int> *)pq2);
    cout << "pq2 assigned to pq3\n";
    /*pq1->push(3);
    //pq2->pop();
    cout << pq1->size() << "\n";
    cout << pq2->size() << "\n";
    cout << pq3->size() << "\n";
    assert(pq1->size() == 6);
    assert(pq2->size() == 5);
    assert(pq3->size() == 5);
    assert(!pq1->empty());
    assert(pq1->top() == 81);
    pq2->push(pq3->top());
    assert(pq2->top() == pq3->top());*/

    //range constructor
    PairingPQ<int> * pq4 = new PairingPQ<int>(vec.begin(), vec.end());
    assert(pq4->top() == 81);

    //addNode
    cout << "\n";
    printPairing(pq4);
    cout << "\n";
    printPairing(pq1);
    cout << "\n";
    printPairing(pq3);
    pq1->push(120);
    cout << (pq3->addNode(12))->getElt() << "\n";
    cout << (pq4->addNode(120))->getElt() << "\n";
    cout << "\n";
    printPairing(pq4);
    cout << "\n";
    printPairing(pq1);
    cout << "\n";
    printPairing(pq3);


    //updateElement

    cout << "Basic tests done." << endl;
    // TODO: Add more code to test addNode(), updateElt(), etc.

    cout << "Calling destructors" << endl;
    delete pq1;
    delete pq2;
    delete pq3;
    delete pq4;

    cout << "testPairing() succeeded" << endl;
} // testPairing()


int main() {
    // Basic pointer, allocate a new PQ later based on user choice.
    Eecs281PQ<int> *pq;
    vector<string> types{ "Unordered", "Sorted", "Binary", "Pairing" };
    unsigned int choice;

    cout << "PQ tester" << endl << endl;
    for (size_t i = 0; i < types.size(); ++i)
        cout << "  " << i << ") " << types[i] << endl;
    cout << endl;
    cout << "Select one: ";
    cin >> choice;

    if (choice == 0) {
        pq = new UnorderedPQ<int>;
    } // if
    else if (choice == 1) {
        pq = new SortedPQ<int>;
    } // else if
    else if (choice == 2) {
        pq = new BinaryPQ<int>;
    } // else if
    else if (choice == 3) {
        pq = new PairingPQ<int>;
    } // else if
    else {
        cout << "Unknown container!" << endl << endl;
        exit(1);
    } // else
   
    testPriorityQueue(pq, types[choice]);
    testUpdatePriorities(types[choice]);

    if (choice == 3) {
        vector<int> vec;
        vec.push_back(10);
        vec.push_back(25);
        vec.push_back(81);
        vec.push_back(37);
        vec.push_back(10);
        testPairing(vec);
        testCopyOpCtor(vec);
        testRangeCtor();
        testAddNode();
        testUpdateElt();
        
    } // if

    // Clean up!
    delete pq;

    return 0;
} // main()

// Testing file provided for EECS 281 Lab 7

#include "hashtable.h"
#include <string>
#include <iostream>

int main() {

    // VERY BASIC EXAMPLE (will likely not compile with default/empty hashtable.h file)
    /*HashTable<std::string, int> midterm;
    std::cout << "Inserting valid student grades:\n\t";
    std::cout << midterm.insert("sam", 50) << "\n\t";
    std::cout << midterm.insert("fee", 100) << "\n\t";
    std::cout << midterm.insert("milo", 95) << "\n\t";
    std::cout << midterm.insert("gabe", 88) << "\n";
    std::cout << "New size: " << midterm.size() << "\n";
    std::cout << "Attempting to insert duplicate student:\n\t";
    std::cout << midterm.insert("gabe", 56) << "\n";
    std::cout << "New size: " << midterm.size() << "\n";
    std::cout << "Attempting valid [] operations:\n\t";
    std::cout << "sam: " << midterm["sam"] << "\n\t";
    std::cout << "fee: " <<  midterm["fee"] << "\n\t";
    std::cout << "milo: " << midterm["milo"] << "\n\t";
    std::cout << "gabe: " << midterm["gabe"] << "\n";
    std::cout << "Attempting to erase then access sam's grade (will add her back in as default):\n\t";
    std::cout << midterm.erase("sam") << "\n\t";
    std::cout << "New size: " << midterm.size() << "\n\t";
    std::cout << "sam: " << midterm["sam"] << "\n\t";
    std::cout << "New size: " << midterm.size() << "\n";
    std::cout << "Attempting to erase an invalid student:\n\t";
    std::cout << midterm.erase("olaf") << "\n";
    std::cout << "New size: " << midterm.size() << "\n";
    std::cout << "Attempting to add 8 more students to go over initial capacity:\n\t";
    std::cout << "Inserting abc: " << midterm.insert("abc", 50) << "\n\t";
    std::cout << "Inserting def: " << midterm.insert("def", 100) << "\n\t";
    std::cout << "Inserting ghi: " << midterm.insert("ghi", 95) << "\n\t";
    std::cout << "Inserting jkl: " << midterm.insert("jkl", 88) << "\n\t";
    std::cout << "Inserting mno: " << midterm.insert("mno", 50) << "\n\t";
    std::cout << "Inserting pqr: " << midterm.insert("pqr", 100) << "\n\t";
    std::cout << "Inserting stu: " << midterm.insert("stu", 95) << "\n\t";
    std::cout << "Inserting vwx: " << midterm.insert("vwx", 88) << "\n";
    std::cout << "New size: " << midterm.size() << "\n";
    std::cout << "Attempting valid [] operations:\n\t";
    midterm["sam"] = 35;
    std::cout << "sam: " << midterm["sam"] << "\n\t";
    std::cout << "fee: " <<  midterm["fee"] << "\n\t";
    std::cout << "milo: " << midterm["milo"] << "\n\t";
    std::cout << "gabe: " << midterm["gabe"] << "\n\t";
    std::cout << "abc: " << midterm["abc"] << "\n\t";
    std::cout << "def: " <<  midterm["def"] << "\n\t";
    std::cout << "ghi: " << midterm["ghi"] << "\n\t";
    std::cout << "jkl: " << midterm["jkl"] << "\n\t";
    std::cout << "mno: " << midterm["mno"] << "\n\t";
    std::cout << "pqr: " <<  midterm["pqr"] << "\n\t";
    std::cout << "stu: " << midterm["stu"] << "\n\t";
    std::cout << "vwx: " << midterm["vwx"] << "\n";*/
    // ADD MORE TESTS OF YOUR OWN
    //HashTable<std::string, int> test;
    /*std::cout << test.insert("CCC", 8) << "\n\t";
    std::cout << test.insert("DDD", 2) << "\n\t";
    std::cout << test.insert("AAA", 1) << "\n\t";
    std::cout << test.erase("AAA") << "\n";
    std::cout << test.erase("AAA") << "\n";
    //test.printVector();
    std::cout << test.erase("CCC") << "\n";
    std::cout << test.erase("DDD") << "\n";
    std::cout << test.erase("AAA") << "\n";
    std::cout << "New size: " << test.size() << "\n";
    std::cout << "AAA: " << test["AAA"] << "\n";
    std::cout << "New size: " << test.size() << "\n";
    std::cout << test.erase("AAA") << "\n";*/
    /*std::cout << "\t";
    std::cout << test.insert("AAA",0) << "\n";
    //test.printVector();
    std::cout << "\n\t";
    for(int i = 0; i < 26; ++i){
        char c = 'A' + i;
        std::string k = "";
        k += c;
        k += c;
        k += c;
        std::cout << k << " ";
        std::cout << test.insert(k, i) << "\n\t";
    }
    std::cout << "New size: " << test.size() << "\n";
    //test.printVector();
    std::cout << test.erase("BBB") << "\n";
    //test.printVector();
    std::cout << "JJJ:\t" << test["JJJ"] << "\n";
    test["JJJ"] = 5;
    std::cout << test.insert("JJJ",1) << "\n";
    test.insert("BBB",3);
    std::cout << "BBB:\t" << test["BBB"] << "\n";
    //test.printVector();*/
    HashTable<char, int> test2; 
    for(int i = 0; i < 10; ++i){
        std::cout << test2.insert('a'+i,i) << "\n";
        std::cout << test2.erase('a'+i) << "\n";
    }
    //test2.printVector();
    std::cout << test2.insert('d',6) << "\n";
    std::cout << "New size: " << test2.size() << "\n";
    test2.printVector();
    test2['d'+10] = 5;
    std::cout << "New size: " << test2.size() << "\n";
    test2.printVector();
    test2['d'+20] = 4;
    std::cout << "New size: " << test2.size() << "\n";
    test2.printVector();
    test2['d'-10] = 2;
    std::cout << "New size: " << test2.size() << "\n";
    test2.printVector();
    test2.erase('d'+10);
    test2['d'-10] = 3;
    std::cout << "New size: " << test2.size() << "\n";
    test2.printVector();

    HashTable<std::string, int> test3;
    test3["AAA"] = 6;
    HashTable<std::string, int> test4;
    test4.insert("AAA",6);
    test3.printVector();
    test4.printVector();

    return 0;
}

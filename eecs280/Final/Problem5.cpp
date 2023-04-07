#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

class VendingMachineException {
public:
  virtual string print() const = 0;
};

class InsufficientFundsException : public VendingMachineException {
public:
  string print() const {
    return "Insufficient funds";
  }
};

class InvalidEntryException : public VendingMachineException {
public:
  string print() const {
    return "Invalid entry";
  }
};

class OutOfStockException : public VendingMachineException {
public:
  string print() const {
    return "Out of stock";
  }
};

class VendingMachine {
  // This VendingMachine class allows selection of one of five
  // softdrinks, numbered 0 through 4. Each drink costs $1.25.
  // The vend_drink( ) routine sells a drink and returns change
  // but throws an exception if there's not enough money, an
  // invalid selection or if the selection is out of stock.

private:
  static const int NUM_DRINKS = 5;
  int drinks_left[NUM_DRINKS];
  string drinks[NUM_DRINKS];

public:
  VendingMachine()
      : drinks_left{2, 2, 2, 2, 2}, drinks{"Crush", "Fanta", "Sprite", "Pepsi",
                                           "Faygo"} { }

  double vend_drink(int selection, double money) {
    if (money < 1.25)
      throw InsufficientFundsException();
    if (selection < 0 || selection >= NUM_DRINKS)
      throw InvalidEntryException();
    if (drinks_left[selection] == 0)
      throw OutOfStockException();
    drinks_left[selection]--;
    cout << "Vending " << drinks[selection] << endl;
    cout << "Your change is " << money - 1.25 << endl;
    return money - 1.25;
  }
};

void try1(){
    try {
        VendingMachine vm;
        for (int i = 0; i < 2; ++i)
            vm.vend_drink(0, 2.00);
        cout << "Good selection!" << endl;
    }
    catch (VendingMachineException &e) {
        cout << e.print() << endl;
    }
}

void try2(){
    try {
        VendingMachine vm;
        vm.vend_drink(2, 1.25);
        cout << "Good selection!" << endl;
    }
    catch (VendingMachineException &e) {
        cout << e.print() << endl;
    }
}

int main(){
    try1();
    try2();
}
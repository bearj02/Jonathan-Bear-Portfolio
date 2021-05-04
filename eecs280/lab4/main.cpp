#include <iostream>
#include <cassert>
#include <cmath>
#include "lab04.h"

using namespace std;

int main() {

  // TASK 1: Add code to do the following:
  //  - Create a local EmployeeRecord object
  EmployeeRecord *record = new EmployeeRecord;
  //  - Initialize the EmployeeRecord using EmployeeRecord_init
  EmployeeRecord_init(record,"Jonathan Bear","Male",19,2);
  //  - Print the EmployeeRecord using EmployeeRecord_print
  EmployeeRecord_print(record);

  // TASK 2: Add code to do the following:
  //  - Create a Company with the name "eecsSoft"
  Company *comp = new Company("eecsSoft");
  //  - Add EXACTLY three Employees to the company, using the Employee
  //    constructor and the Company hire_employee function
  Employee *e1 = new Employee("Jonathan Bear","Male",19,2);
  Employee *e2 = new Employee("Eric Chen","Male",18,1);
  Employee *e3 = new Employee("Regina Cooper","Female",35,4);

  comp->hire_employee(*e1);
  comp->hire_employee(*e2);
  comp->hire_employee(*e3);
  //  - Print the company to cout using the << operator
  comp->print(cout);

  // TASK 2 - Add code to do the following:
  //  - Promote one employee at the company
  comp->promote_employee("Jonathan Bear");
  //  - Demote one employee at the company
  comp->demote_employee("Regina Cooper");
  //  - Print the company to cout using the << operator
  comp->print(cout);

}

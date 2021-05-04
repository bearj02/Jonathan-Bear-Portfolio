#include <iostream>
#include <cassert>
#include "lab04.h"

using namespace std;

/*************************** Employee C-Style ADT ***************************/

// MODIFIES: *rec
// EFFECTS: Initializes the given EmployeeRecord with name, gender,
//          age and rank information
void EmployeeRecord_init(EmployeeRecord *rec, const string &in_name,
                         const string &in_gender, int in_age,
                         int in_rank) {
  // TASK 1 - YOUR CODE HERE
  rec->age = in_age;
  rec->gender = in_gender;
  rec->name = in_name;
  rec->rank = in_rank;
}

// REQUIRES: rec points to a valid EmployeeRecord
// MODIFIES: *rec
// EFFECTS: Increases the rank of the given EmployeeRecord by one
void EmployeeRecord_promote(EmployeeRecord *rec) {
  // TASK 1 - YOUR CODE HERE
  rec->rank++;
}

// REQUIRES: rec points to a valid EmployeeRecord
// MODIFIES: *rec
// EFFECTS: Decreases the rank of the given EmployeeRecord by one
void EmployeeRecord_demote(EmployeeRecord *rec) {
  // TASK 1 - YOUR CODE HERE
  rec->rank--;
}

// REQUIRES: rec points to a valid EmployeeRecord
// MODIFIES: std::cout
// EFFECTS: Prints the name, gender, age, and rank of the given
//          EmployeeRecord to standard out
void EmployeeRecord_print(const EmployeeRecord *rec) {
  // Verify name and gender strings do not contain the " character
  assert(rec->name.find('"') == std::string::npos);
  assert(rec->gender.find('"') == std::string::npos);

  cout << "NAME: \"" << rec->name << "\""
       << ", GENDER: \"" << rec->gender << "\""
       << ", AGE: " << rec->age
       << ", RANK: " << rec->rank << endl;
}

// REQUIRES: rec points to a valid EmployeeRecord
// EFFECTS: Returns the name of the given EmployeeRecord
const std::string & EmployeeRecord_get_name(const EmployeeRecord *rec) {
  return rec->name;
}

// REQUIRES: rec points to a valid EmployeeRecord
// EFFECTS: Returns the gender of the given EmployeeRecord
const std::string & EmployeeRecord_get_gender(const EmployeeRecord *rec) {
  return rec->gender;
}

// REQUIRES: rec points to a valid EmployeeRecord
// EFFECTS: Returns the age of the given EmployeeRecord
int EmployeeRecord_get_age(const EmployeeRecord *rec) {
  return rec->age;
}

// REQUIRES: rec points to a valid EmployeeRecord
// EFFECTS: Returns the rank of the given EmployeeRecord
int EmployeeRecord_get_rank(const EmployeeRecord *rec) {
  return rec->rank;
}

/***************************** Employee C++ ADT *****************************/

// TASK 2 - Add implementations for the following Employee
//          member functions here.
//  - Constructor
//  - promote
//  - demote

Employee::Employee(const string &in_name, const string &in_gender, 
            int in_age, int in_rank){
  name = in_name;
  gender = in_gender;
  age = in_age;
  rank = in_rank;
}
void Employee::promote(){
  Employee::rank++;
}
void Employee::demote(){
  Employee::rank--;
}

// MODIFIES: os
// EFFECTS: Prints the name, gender, age, and rank of this Employee
//          to the given output stream.
void Employee::print(std::ostream &os) const {
  // Verify name and gender strings do not contain the " character
  assert(name.find('"') == std::string::npos);
  assert(gender.find('"') == std::string::npos);

  os << "NAME: \"" << name << "\""
     << ", GENDER: \"" << gender << "\""
     << ", AGE: " << age
     << ", RANK: " << rank;
}

// EFFECTS: Returns the name of this Employee
const std::string & Employee::get_name() const {
  return name;
}

// EFFECTS: Returns the gender of this Employee
const std::string & Employee::get_gender() const {
  return gender;
}

// EFFECTS: Returns the age of this Employee
int Employee::get_age() const {
  return age;
}

// EFFECTS: Returns the rank of this Employee
int Employee::get_rank() const {
  return rank;
}

// Overloaded << operator for Employee
std::ostream & operator<<(std::ostream &os, const Employee &e) {
  e.print(os);
  return os;
}

/***************************** Company C++ ADT *****************************/

// Constructor
// EFFECTS: Initializes this Company with the given name.
Company::Company(const std::string &name_in)
 : name(name_in) { }

// EFFECTS: Returns the number of employees at this company.
int Company::num_employees() const {
  return employees.size();
}

// REQUIRES: There may not already be an employee at this company whose
//           name matches the given Employee.
// MODIFIES: *this
// EFFECTS: Adds the given Employee to this company.
void Company::hire_employee(const Employee &e) {
  employees.push_back(e);
}

// MODIFIES: *this
// EFFECTS: If this company has an Employee whose name matches the given
//          name, removes that Employee. Otherwise, does nothing.
void Company::fire_employee(const std::string &name) {
  Employee *fired = find_employee(name);
  if (fired) {
    *fired = employees.back();
    employees.pop_back();
  }
}

// MODIFIES: *this
// EFFECTS: If this company has an Employee whose name matches the given
//          name, promotes that Employee. Otherwise, does nothing.
// HINT:    Use find_employee() in this function
void Company::promote_employee(const std::string &name) {
  // TASK 2 - YOUR CODE HERE
  Employee *promoted = find_employee(name);
  if(promoted){
    promoted->promote();
  }
}

// MODIFIES: *this
// EFFECTS: If this company has an Employee whose name matches the given
//          name, demotes that Employee. Otherwise, does nothing.
// HINT:    Use find_employee() in this function
void Company::demote_employee(const std::string &name) {
  // TASK 2 - YOUR CODE HERE
  Employee *demoted = find_employee(name);
  if(demoted){
    demoted->demote();
  }
}

// EFFECTS: Returns a pointer to the Employee in 'company' whose name
//          matches the given name. If no such employee exists, returns a
//          null pointer.
Employee * Company::find_employee(const std::string &name) {
  for (size_t i = 0; i < employees.size(); ++i) {
    if (employees[i].get_name() == name) {
      return &employees[i];
    }
  }
  return nullptr;
}

// EFFECTS: Prints a summary of this company and its employees to the
//          given output stream.
void Company::print(std::ostream &os) const {
  os << "Welcome to " << name << "! Here are our loyal employees: " << endl;
  for (size_t i = 0; i < employees.size(); ++i) {
    os << "  " << employees[i] << endl;
  }
}

// Overloaded << operator for Company
std::ostream & operator<<(std::ostream &os, const Company &c) {
  c.print(os);
  return os;
}

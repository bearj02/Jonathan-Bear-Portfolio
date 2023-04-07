#ifndef LAB04_H
#define LAB04_H

#include <string>
#include <vector>

/*************************** Employee C-Style ADT ***************************/

struct EmployeeRecord {
  std::string name;
  std::string gender;
  int age;
  int rank;
};

// MODIFIES: *rec
// EFFECTS: Initializes the given EmployeeRecord with name, gender,
//          age and rank information
void EmployeeRecord_init(EmployeeRecord *rec,
                         const std::string &in_name,
                         const std::string &in_gender,
                         int in_age, int in_rank);

// REQUIRES: rec points to a valid EmployeeRecord
// MODIFIES: *rec
// EFFECTS: Increases the rank of the given EmployeeRecord by one
void EmployeeRecord_promote(EmployeeRecord *rec);

// REQUIRES: rec points to a valid EmployeeRecord
// MODIFIES: *rec
// EFFECTS: Decreases the rank of the given EmployeeRecord by one
void EmployeeRecord_demote(EmployeeRecord *rec);

// REQUIRES: rec points to a valid EmployeeRecord
// MODIFIES: std::cout
// EFFECTS: Prints the name, gender, age, and rank of the given
//          EmployeeRecord to standard out
void EmployeeRecord_print(const EmployeeRecord *rec);

// REQUIRES: rec points to a valid EmployeeRecord
// EFFECTS: Returns the name of the given EmployeeRecord
const std::string & EmployeeRecord_get_name(const EmployeeRecord *rec);

// REQUIRES: rec points to a valid EmployeeRecord
// EFFECTS: Returns the gender of the given EmployeeRecord
const std::string & EmployeeRecord_get_gender(const EmployeeRecord *rec);

// REQUIRES: rec points to a valid EmployeeRecord
// EFFECTS: Returns the age of the given EmployeeRecord
int EmployeeRecord_get_age(const EmployeeRecord *rec);

// REQUIRES: rec points to a valid EmployeeRecord
// EFFECTS: Returns the rank of the given EmployeeRecord
int EmployeeRecord_get_rank(const EmployeeRecord *rec);

/***************************** Employee C++ ADT *****************************/

class Employee {
private:
  std::string name;
  std::string gender;
  int age;
  int rank;

public:
  // Constructor
  // EFFECTS: Initializes the Employee with name, gender, age and rank
  //          information
  Employee(const std::string &in_name, const std::string &in_gender,
           int in_age, int in_rank);

  // MODIFIES: *this
  // EFFECTS: Increases the rank of the Employee by one
  void promote();

  // MODIFIES: *this
  // EFFECTS: Decreases the rank of the Employee by one
  void demote();

  // MODIFIES: os
  // EFFECTS: Prints the name, gender, age, and rank of this Employee
  //          to the given output stream.
  void print(std::ostream &os) const;

  // EFFECTS: Returns the name of this Employee
  const std::string & get_name() const;

  // EFFECTS: Returns the gender of this Employee
  const std::string & get_gender() const;

  // EFFECTS: Returns the age of this Employee
  int get_age() const;

  // EFFECTS: Returns the rank of this Employee
  int get_rank() const;
};

std::ostream & operator<<(std::ostream &os, const Employee &e);

/***************************** Company C++ ADT *****************************/

class Company {
public:
  // INVARIANT: No two Employees in a company may have the same name

  // Constructor
  // EFFECTS: Initializes this Company with the given name.
  Company(const std::string &name_in);

  // EFFECTS: Returns the number of employees at this company.
  int num_employees() const;

  // REQUIRES: There may not already be an employee at this company whose
  //           name matches the given Employee.
  // MODIFIES: *this
  // EFFECTS: Adds the given Employee to this company.
  void hire_employee(const Employee &e);

  // MODIFIES: *this
  // EFFECTS: If this company has an Employee whose name matches the given
  //          name, removes that Employee. Otherwise, does nothing.
  // HINT:    Use find_employee() in this function
  void fire_employee(const std::string &name);

  // MODIFIES: *this
  // EFFECTS: If this company has an Employee whose name matches the given
  //          name, promotes that Employee. Otherwise, does nothing.
  // HINT:    Use find_employee() in this function
  void promote_employee(const std::string &name);

  // MODIFIES: *this
  // EFFECTS: If this company has an Employee whose name matches the given
  //          name, demotes that Employee. Otherwise, does nothing.
  // HINT:    Use find_employee() in this function
  void demote_employee(const std::string &name);

  // EFFECTS: Returns a pointer to the Employee in 'company' whose name
  //          matches the given name. If no such employee exists, returns a
  //          null pointer.
  Employee * find_employee(const std::string &name);

  // EFFECTS: Prints a summary of this company and its employees to the
  //          given output stream.
  void print(std::ostream &os) const;

private:

  // The name of the company
  std::string name;

  // INVARIANT: No two Employees in a company may have the same name
  std::vector<Employee> employees;

};

// Overloaded << operator for Company
std::ostream & operator<<(std::ostream &os, const Company &c);

#endif // LAB04_H

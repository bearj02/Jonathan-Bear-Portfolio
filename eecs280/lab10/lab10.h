#ifndef LAB10_H
#define LAB10_H

#include <iostream>
#include <algorithm>
#include <string>

/*********************************** Person ***********************************/

class Person {
private:
  std::string name;
  int age;

public:
  //Constructor
  //EFFECTS:  Sets person to have name and age information
  Person(const std::string &name_in, int age_in)
    : name(name_in), age(age_in) {}

  //EFFECTS:  Returns this person's name
  const std::string & get_name() const { return name; }

  //EFFECTS:  Returns this person's age
  int get_age() const { return age; }
};

/********************************** Functors **********************************/

// Comparator CompareName
class CompareName {
public:
  //EFFECTS:  returns whether a's name is before b's (alphabetically)
  bool operator()(const Person &a, const Person &b) const;
};

// Comparator CompareAge
class CompareAge {
public:
  //EFFECTS: returns whether a is younger than b
  bool operator()(const Person &a, const Person &b) const;
};

/****************************** Helper Functions ******************************/

//REQUIRES: arr points to an array of size n > 0
//EFFECTS:  returns a pointer to the maximum person in arr according to the comparator comp
template <typename Comp>
const Person * find_max(const Person *arr, int n, Comp comp);

//REQUIRES: arr points to an array of size n > 0
//EFFECTS:  prints the name of every person in arr for which pred returns true
template <typename Predicate>
void print_if(const Person *arr, int n, Predicate pred);

/******************************* Test Functions *******************************/

//REQUIRES: people points to an array of size num_people > 0
//EFFECTS:  returns a pointer to the last person alphabetically in people
const Person * find_last_person(const Person *people, int num_people);

//REQUIRES: people points to an array of size num_people > 0
//EFFECTS:  returns a pointer to the oldest person in people
const Person * find_oldest_person(const Person *people, int num_people);

//REQUIRES: people points to an array of size num_people > 0
//EFFECTS:  prints the name of every person in people whose age is n
void print_people_with_age_n(const Person *people, int num_people, int n);

#endif /* LAB10_H */

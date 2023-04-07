#include <iostream>
#include "lab10.h"

using namespace std;

int main() {
  const int N = 5;

  Person people[N] = {
    { "Drew", 16 },
    { "Cathy", 34 },
    { "Alice", 16 },
    { "Ernest", 29 },
    { "Bob", 21 }
  };

  cout << "The people we are considering are:" << endl;
  for (Person *ptr = people; ptr < people + N; ++ptr) {
    cout << ptr->get_name() << ", " << ptr->get_age() << endl;
  }
  cout << endl;

  for (int i = 0; i < N; ++i) {
    bool earlier = CompareName()(people[0], people[i]);

    bool younger = CompareAge()(people[0], people[i]);

    cout << people[0].get_name() << "'s name is "
         << (earlier ? "before " : "not before ")
         << people[i].get_name() << "'s name" << endl;

    cout << people[0].get_name() << " is "
         << (younger ? "younger than " : "not younger than ")
         << people[i].get_name() << endl; 
  }

  const Person *last = find_last_person(people, N);
  const Person *oldest = find_oldest_person(people, N);

  cout << "The last person alphabetically is: " << last->get_name() << endl;
  cout << "The oldest person is: " << oldest->get_name() << endl;

  cout << endl;

  cout << "The people who are 16 are:" << endl;
  print_people_with_age_n(people, N, 16);
}

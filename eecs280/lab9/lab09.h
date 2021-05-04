#ifndef LAB09_H
#define LAB09_H

// REQUIRES: n >= 1
// EFFECTS: Prints the hailstone sequence starting at n
void hailstone(int n);

// REQUIRES: n >= 1
// EFFECTS: Prints the hailstone sequence starting at n
void hailstone_iter(int n);

// REQUIRES: 0 <= digit <= 9, n >= 0
// EFFECTS: Returns the number of times digit appears in n
int count_digits(int n, int digit);

// REQUIRES: 0 <= digit <= 9, n >= 0
// EFFECTS: Returns the number of times digit appears in n
int count_digits_iter(int n, int digit);

// REQUIRES: 0 <= digit <= 9, n >= 0
// EFFECTS: Returns the number of times digit appears in n
int count_digits_tail(int n, int digit);

#endif /* LAB09_H */

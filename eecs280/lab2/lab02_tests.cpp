#include "lab02.h"
#include "unit_test_framework.h"

// We define a test case with the TEST(<test_name>) macro.
// <test_name> can be any valid C++ function name.
TEST(true_is_true) {
  ASSERT_TRUE(true);
}

TEST(numbers_are_equal) {
  ASSERT_EQUAL(42, 42);
}

bool compare_arrays(int arr1[], int arr2[], int length) {
  for(int i = 0; i < length; i++)
  {
    if(arr1[i] != arr2[i])
      return false;
  }
  return true;
}

TEST(slideRight) {
  int arr1[5] = {0,3,3,4,1};
  slideRight(arr1, 5);
  int arr2[5] = {1,0,3,3,4};
  ASSERT_TRUE(compare_arrays(arr1, arr2, 5));
}

TEST(flip) {
  int arr1[5] = {0,3,3,4,1};
  flip(arr1, 5);
  int arr2[5] = {1,4,3,3,0};
  ASSERT_TRUE(compare_arrays(arr1, arr2, 5));
}

TEST(removeDuplicates) {
  int arr1[10] = {1,3,3,4,4,4,5,7,9,9};
  int num = removeDuplicates(arr1,10);
  int arr2[10] = {1,3,4,5,7,9,5,7,9,9};
  ASSERT_TRUE(compare_arrays(arr1,arr2,10));
  ASSERT_EQUAL(num,6);
}



TEST_MAIN() // No semicolon!
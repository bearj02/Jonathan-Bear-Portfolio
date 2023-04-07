// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}


// Fills a matrix with negative values and checks
// that Matrix_at returns that value for each element
TEST(test_fill_negative) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = -42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// Fills a large matrix with a value and checks
// that Matrix_at returns that vale for each element
TEST(test_fill_large){
  Matrix *mat = new Matrix;

  const int width = 480;
  const int height = 480;
  const int value = 42;
  Matrix_init(mat, 480, 480);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }
  delete mat;
}

// Fills a 3 x 5 matrix with a value and checks
// that Matrix_print returns the correct string
TEST(test_print_basic){
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);

  ostringstream s;
  Matrix_print(mat,s);

  ostringstream correct;
  correct << "3 5\n";
  correct << "42 42 42 \n";
  correct << "42 42 42 \n";
  correct << "42 42 42 \n";
  correct << "42 42 42 \n";
  correct << "42 42 42 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete mat;
}

TEST(test_fill_border_basic){
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, width, height);
  Matrix_fill(mat,0);
  Matrix_fill_border(mat, value);

  ostringstream s;
  Matrix_print(mat,s);

  ostringstream correct;
  correct << "3 5\n";
  correct << "42 42 42 \n";
  correct << "42 0 42 \n";
  correct << "42 0 42 \n";
  correct << "42 0 42 \n";
  correct << "42 42 42 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete mat;
}

TEST(test_fill_border_one){
  Matrix *mat = new Matrix;

  const int width = 1;
  const int height = 1;
  const int value = 42;
  Matrix_init(mat, width, height);
  Matrix_fill(mat,0);
  Matrix_fill_border(mat, value);

  ostringstream s;
  Matrix_print(mat,s);

  ostringstream correct;
  correct << "1 1\n";
  correct << "42 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete mat;
}

TEST(test_fill_border_small){
  Matrix *mat = new Matrix;

  const int width = 2;
  const int height = 2;
  const int value = 42;
  Matrix_init(mat, width, height);
  Matrix_fill(mat,0);
  Matrix_fill_border(mat, value);

  ostringstream s;
  Matrix_print(mat,s);

  ostringstream correct;
  correct << "2 2\n";
  correct << "42 42 \n";
  correct << "42 42 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete mat;
}

TEST(test_max_basic){
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 2;
  Matrix_init(mat, width, height);

  *Matrix_at(mat,0,0) = 1;
  *Matrix_at(mat,0,1) = 2;
  *Matrix_at(mat,0,2) = 4;
  *Matrix_at(mat,1,0) = 7;
  *Matrix_at(mat,1,1) = 1;
  *Matrix_at(mat,1,2) = 5;

  ASSERT_EQUAL(Matrix_max(mat),7);

  delete mat;
}

TEST(test_min_value_in_row){
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 2;
  Matrix_init(mat, width, height);

  *Matrix_at(mat,0,0) = 1;
  *Matrix_at(mat,0,1) = 2;
  *Matrix_at(mat,0,2) = 4;
  *Matrix_at(mat,1,0) = 7;
  *Matrix_at(mat,1,1) = 1;
  *Matrix_at(mat,1,2) = 5;

  ASSERT_EQUAL(Matrix_min_value_in_row(mat,1,0,3),1);

  delete mat;
}

TEST(test_min_value_in_large_row){
  Matrix *mat = new Matrix;

  const int width = 480;
  const int height = 480;
  const int value = 42;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);
  int min_value = Matrix_min_value_in_row(mat,300,0,400);
  *Matrix_at(mat, 300, 300) = min_value - 1;

  ASSERT_EQUAL(Matrix_min_value_in_row(mat,300,0,400),min_value - 1);

  delete mat;
}

TEST(test_column_of_min_value_in_row){
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 2;
  Matrix_init(mat, width, height);

  *Matrix_at(mat,0,0) = 1;
  *Matrix_at(mat,0,1) = 2;
  *Matrix_at(mat,0,2) = 4;
  *Matrix_at(mat,1,0) = 7;
  *Matrix_at(mat,1,1) = 1;
  *Matrix_at(mat,1,2) = 5;

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,1,0,3),1);

  delete mat;
}

TEST(test_column_min_value_not_whole_row_end_of_selection){
  Matrix *mat = new Matrix;

  const int width = 5;
  const int height = 2;
  Matrix_init(mat, width, height);

  *Matrix_at(mat,0,0) = 8;
  *Matrix_at(mat,0,1) = 5;
  *Matrix_at(mat,0,2) = 4;
  *Matrix_at(mat,0,3) = 3;
  *Matrix_at(mat,0,4) = 2;

  *Matrix_at(mat,1,0) = 7;
  *Matrix_at(mat,1,1) = 1;
  *Matrix_at(mat,1,2) = 5;
  *Matrix_at(mat,1,3) = 4;
  *Matrix_at(mat,1,4) = 4;


  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,0,1,3),2);

  delete mat;
}

TEST(test_column_min_value_not_whole_row_beginning_of_selection){
  Matrix *mat = new Matrix;

  const int width = 5;
  const int height = 2;
  Matrix_init(mat, width, height);

  *Matrix_at(mat,0,0) = 8;
  *Matrix_at(mat,0,1) = 2;
  *Matrix_at(mat,0,2) = 4;
  *Matrix_at(mat,0,3) = 5;
  *Matrix_at(mat,0,4) = 4;

  *Matrix_at(mat,1,0) = 7;
  *Matrix_at(mat,1,1) = 1;
  *Matrix_at(mat,1,2) = 5;
  *Matrix_at(mat,1,3) = 4;
  *Matrix_at(mat,1,4) = 4;


  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,0,1,3),1);

  delete mat;
}

TEST(Matrix_row_and_column){
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 2;
  Matrix_init(mat, width, height);

  *Matrix_at(mat,0,0) = 1;
  *Matrix_at(mat,0,1) = 2;
  *Matrix_at(mat,0,2) = 4;
  *Matrix_at(mat,1,0) = 7;
  *Matrix_at(mat,1,1) = 1;
  *Matrix_at(mat,1,2) = 5;

  int row = 1;
  int column = 2;

  ASSERT_EQUAL(Matrix_row(mat,Matrix_at(mat,1,2)), row);
  ASSERT_EQUAL(Matrix_column(mat,Matrix_at(mat,1,2)), column);

  delete mat;
}

TEST(Matrix_one_row){
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 1;
  Matrix_init(mat, width, height);

  *Matrix_at(mat,0,0) = 1;
  *Matrix_at(mat,0,1) = 2;
  *Matrix_at(mat,0,2) = 4;

  int row = 0;
  int column = 2;

  ASSERT_EQUAL(Matrix_row(mat,Matrix_at(mat,0,2)), row);
  ASSERT_EQUAL(Matrix_column(mat,Matrix_at(mat,0,2)), column);

  delete mat;
}

TEST(Matrix_one_column){
  Matrix *mat = new Matrix;

  const int width = 1;
  const int height = 3;
  Matrix_init(mat, width, height);

  *Matrix_at(mat,0,0) = 1;
  *Matrix_at(mat,1,0) = 2;
  *Matrix_at(mat,2,0) = 4;

  int row = 2;
  int column = 0;

  ASSERT_EQUAL(Matrix_row(mat,Matrix_at(mat,2,0)), row);
  ASSERT_EQUAL(Matrix_column(mat,Matrix_at(mat,2,0)), column);

  delete mat;
}


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here

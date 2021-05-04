// Project UID af1f95f547e44c8ea88730dfb185559ds

#include <cassert>
#include "Matrix.h"

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
  assert(width > 0 && width <= MAX_MATRIX_WIDTH);
  assert(height > 0 && height <= MAX_MATRIX_HEIGHT);
  mat->width = width;
  mat->height = height;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  os << Matrix_width(mat) << " " << Matrix_height(mat) << '\n';
  for(int row = 0; row < Matrix_height(mat); row++){
    for(int column = 0; column < Matrix_width(mat); column++){
      int element = *Matrix_at(mat,row,column);
      os << element << " ";
    }
    os << '\n';
  }

}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  int w = mat->width;
  return w;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
  int row = (int)((ptr-Matrix_at(mat,0,0))/(Matrix_width(mat)));
  return row;
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
  const int* start = Matrix_at(mat,0,0);
  int location = (int)(ptr-start);
  int width = Matrix_width(mat);
  int column = location % width;
  return column;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column && column < Matrix_width(mat));
  int* p = mat->data;
  if(row != 0 || column != 0){
    p = p + row*Matrix_width(mat);
    p = p + column;
  }
  return p;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  const int* start = mat->data;
  
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column && column < Matrix_width(mat));
  const int* cp = start + (row*Matrix_width(mat) + column);
  return cp;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  int* const start = Matrix_at(mat,0,0);
  int* ptr = start;
  while(ptr < (start + Matrix_width(mat)*Matrix_height(mat))){
    *Matrix_at(mat,Matrix_row(mat,ptr),Matrix_column(mat,ptr))=value;
    ++ptr;
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  int* const start = Matrix_at(mat,0,0);
  int* p = start;
  if(Matrix_height(mat) == 1 || Matrix_width(mat) == 1){
    *Matrix_at(mat,0,0) = value;
    while(p < start + (Matrix_height(mat)*Matrix_width(mat))){
      *p = value;
      ++p;
    }
  }
  else{
    while(p < (start + Matrix_width(mat))){
      *p = value;
      p++;
    }
    while(p<(Matrix_at(mat,Matrix_height(mat)-2,Matrix_width(mat)-1) + 1)){
      if(Matrix_column(mat,p)==0||Matrix_column(mat,p)==Matrix_width(mat)-1){
        *p = value;
      }
      ++p;
    }
    while(p<(Matrix_at(mat,Matrix_height(mat)-1,Matrix_width(mat)-1) + 1)){
      *p = value;
      ++p;
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  const int* start = Matrix_at(mat,0,0);
  int* p = (int*)start;
  int max = *p;
  while(p<(Matrix_at(mat,0,0)+(Matrix_width(mat) * Matrix_height(mat)))){
    if(*p > max)
      max = *p;
    p++;
  }
  return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row, 
                                    int column_start, int column_end){
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);
  
  const int* start = Matrix_at(mat,0,0);
  int* p = (int*)start + row*Matrix_width(mat) + column_start;
  int min = *p;
  int colMin = column_start;
  
  for(int col = colMin; col < column_end; col++){
    if(*p < min){
      min = *p;
      colMin = col;
    }
    p++;
  }
  return colMin;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row, 
                            int column_start, int column_end) {
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);
  
  const int* start = Matrix_at(mat,row,column_start);
  int* p = (int*)start;
  int min = *p;

  while(p < start + column_end){
    if(*p < min)
      min = *p;
    ++p;
  }
  return min;
}

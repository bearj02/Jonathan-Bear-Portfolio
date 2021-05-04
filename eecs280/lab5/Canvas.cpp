#include <iostream>
#include <cassert>
#include "Canvas.h"

using namespace std;

/************************** DO NOT MODIFY THIS FILE **************************/

//EFFECTS: creates a new Canvas with size WIDTH x HEIGHT
Canvas::Canvas() {
  for (int r = 0; r < HEIGHT; ++r) {
    for (int c = 0; c < WIDTH; ++c) {
      grid[r][c] = false;
    }
  }
}

//REQUIRES: the pixel is on the canvas (0 <= x < WIDTH and 0 <= y < HEIGHT)
//MODIFIES: *this
//EFFECTS: the pixel at (x,y) is set to ON if value, and OFF otherwise.
void Canvas::set_pixel(int x, int y, bool value) {
  assert(0 <= x && x < WIDTH);
  assert(0 <= y && y < HEIGHT);
  // y: row, x: column
  grid[y][x] = value;
}

//MODIFIES: cout
//EFFECTS: prints this canvas to cout
void Canvas::print() const {
  // Start from top and move down
  for (int r = HEIGHT - 1; r >= 0; --r) {
    for (int c = 0; c < WIDTH; ++c) {
      cout << (grid[r][c] ? PIXEL_ON : PIXEL_OFF) << " ";
    }

    cout << endl;
  }
}

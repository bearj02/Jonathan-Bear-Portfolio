#ifndef CANVAS_H
#define CANVAS_H

/************************** DO NOT MODIFY THIS FILE **************************/

class Canvas {
  // Represents a fixed-size 2D grid of "pixels," which can be set to either
  // "on" or "off". The Canvas can print itself to the terminal for viewing.
  // NOTE: The origin (0,0) for the Canvas is at the bottom left.

public:
  static const int WIDTH = 30;
  static const int HEIGHT = 30;

  static const char PIXEL_ON = '#';
  static const char PIXEL_OFF = ' ';

  //EFFECTS: creates a new Canvas with size WIDTH x HEIGHT
  Canvas();

  //REQUIRES: the pixel is on the canvas (0 <= x < WIDTH and 0 <= y < HEIGHT)
  //MODIFIES: *this
  //EFFECTS: the pixel at (x,y) is set to ON if value, and OFF otherwise.
  void set_pixel(int x, int y, bool value);

  //MODIFIES: cout
  //EFFECTS: prints this canvas to cout
  void print() const;

private:
  // Stores whether each pixel is ON or OFF
  bool grid[HEIGHT][WIDTH];
};

#endif /* CANVAS_H */

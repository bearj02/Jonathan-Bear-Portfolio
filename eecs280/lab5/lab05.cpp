#include <iostream>
#include "Canvas.h"
#include "shapes.h"

using namespace std;

int main() {
  // Shape 1
  Ellipse ellip(5, 2);
  ellip.set_position(20, 20);

  // Shape 2
  Circle circ(3);
  circ.set_position(10, 20);

  // Shape 3
  Rectangle rect(20, 3);
  rect.set_position(15, 10);

  // TASK 1,2: FIX
  const int SIZE = 3;
  Shape* shapes[SIZE] = { &ellip, &circ, &rect };

  Canvas canvas;
  for (int i = 0; i < SIZE; ++i) {
    cout << "Area of shape " << i << ": " << shapes[i]->area() << endl;
    shapes[i]->draw(&canvas);
  }

  canvas.print();
}

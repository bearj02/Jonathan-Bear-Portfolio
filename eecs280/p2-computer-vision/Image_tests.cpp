// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <fstream>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

TEST(basic_image_fill){
  Image *img = new Image;

  const Pixel fillRed = {255,0,0};

  Image_init(img,3,3);
  Image_fill(img,fillRed);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n3 3\n255\n";
  correct << "255 0 0 255 0 0 255 0 0 \n";
  correct << "255 0 0 255 0 0 255 0 0 \n";
  correct << "255 0 0 255 0 0 255 0 0 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

TEST(basic_pixel_set_and_get){
  Image *img = new Image;

  const Pixel fillRed = {255,0,0};
  const Pixel setBlue = {0,0,255};

  Image_init(img,3,3);
  Image_fill(img,fillRed);

  Image_set_pixel(img,1,0,setBlue);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n3 3\n255\n";
  correct << "255 0 0 255 0 0 255 0 0 \n";
  correct << "0 0 255 255 0 0 255 0 0 \n";
  correct << "255 0 0 255 0 0 255 0 0 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  Pixel expected = Image_get_pixel(img,1,0);
  ASSERT_TRUE(Pixel_equal(expected,setBlue));

  delete img;
}

TEST(print_images_from_ppm_file){
  Image *img = new Image;

  ifstream myFile ("dog.ppm");
  istream* in;

  in = &myFile;
  Image_init(img, *in);
  myFile.close();
  ostringstream s;
  Image_print(img, s);

  ostringstream correct;
  correct << "P3\n5 5\n255\n";
  correct << "0 0 0 0 0 0 255 255 250 0 0 0 0 0 0 \n";
  correct << "255 255 250 126 66 0 126 66 0 126 66 0 255 255 250 \n";
  correct << "126 66 0 0 0 0 255 219 183 0 0 0 126 66 0 \n";
  correct << "255 219 183 255 219 183 0 0 0 255 219 183 255 219 183 \n";
  correct << "255 219 183 0 0 0 134 0 0 0 0 0 255 219 183 \n";

  ASSERT_EQUAL(s.str(), correct.str());

  delete img;
}

TEST(image_height_and_width){
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 3, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 0, 2, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);
  Image_set_pixel(img, 1, 2, blue);

  int width = Image_width(img);
  int height = Image_height(img);

  
  ASSERT_EQUAL(width,3);
  ASSERT_EQUAL(height,2);

  delete img; // delete the Image
}

TEST(width_and_height_from_ppm_file){
  Image *img = new Image;

  ifstream myFile ("dog.ppm");
  istream* in;

  in = &myFile;
  Image_init(img, *in);
  myFile.close();
  
  int width = Image_width(img);
  int height = Image_height(img);

  ASSERT_EQUAL(width, 5);
  ASSERT_EQUAL(height, 5);

  delete img;
}


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here

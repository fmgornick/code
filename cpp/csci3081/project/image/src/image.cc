#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
using namespace std;

// empty constructor
Image::Image() : width(1), height(1), components(4), size(4) {
  image = new unsigned char[size];
  for (int i = 0; i < size; i++)
    image[i] = 0;
}

// basic constructor
Image::Image(int w, int h) : width(w), height(h), components(4) {
  size = w * h * 4;

  image = new unsigned char[size];
  for (int i = 0; i < size; i++)
    image[i] = '0';
}

// takes in filename and turns it into image object
Image::Image(string filename) {
  unsigned char *loadedImage =
      stbi_load(filename.c_str(), &width, &height, &components, STBI_rgb_alpha);
  components = 4;
  size = width * height * components;

  image = new unsigned char[size];
  for (int i = 0; i < size; i++) {
    image[i] = loadedImage[i];
  }
  stbi_image_free(loadedImage);
}

Image::Image(unsigned char *buffer, int width, int height)
    : width(width), height(height), components(4) {
  size = width * height * 4;
  image = new unsigned char[size];
  memcpy(image, buffer, size);
}

// copy constructor uses equals operator overloaded later in file
Image::Image(const Image &img) {
  image = NULL;
  *this = img;
}

// deletes dynamically allocated character array
Image::~Image() { delete[] image; }

// writes image object into a file
void Image::SaveAs(string filename) {
  stbi_write_png(filename.c_str(), width, height, 4, image, width * 4);
}

// basic variable getter functions
int Image::GetWidth() { return width; }
int Image::GetHeight() { return height; }
int Image::GetComponentNum() { return components; }
int Image::GetSize() { return size; }

// creates 4 character array to pull out values at specific position
void Image::GetPixel(int x, int y, Color &pixel) {
  pixel.setRGBA(&image[components * (y * width + x)]);
}

// finds position in array and alters pixel values
void Image::SetPixel(int x, int y, Color &p) {
  image[components * (y * width + x)] = p.getR() * 255.0;
  image[components * (y * width + x) + 1] = p.getG() * 255.0;
  image[components * (y * width + x) + 2] = p.getB() * 255.0;
  image[components * (y * width + x) + 3] = p.getA() * 255.0;
}

void Image::SetPixelData(int x, int y, Color &p) {
  image[components * (y * width + x)] = p.getR();
  image[components * (y * width + x) + 1] = p.getG();
  image[components * (y * width + x) + 2] = p.getB();
  image[components * (y * width + x) + 3] = p.getA();
}

// equals operator makes an exact copy without using the same mem addresses
void Image::operator=(const Image &img) {
  width = img.width;
  height = img.height;
  components = img.components;
  size = img.size;

  delete[] image;
  image = new unsigned char[size];
  for (int i = 0; i < size; i++) {
    image[i] = img.image[i];
  }
}

unsigned char *Image::GetData() { return image; }

void Image::SetData(unsigned char *data) { memcpy(image, data, size); }

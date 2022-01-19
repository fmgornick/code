/**
 * @file image.h
 */
#ifndef IMAGE_H_
#define IMAGE_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "color.h"
#include <iostream>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief The main class for Image.  Image is represented as a big unsigned
 * character array, and alters values inside the image by using the color class.
 * Class just contains getters, setters, and the big 3.
 *
 */
class Image {
public:
  /**
   * @brief Constructor for no arguments.
   *
   */
  Image();
  /**
   * @brief Constructor for int width and int height arguments.
   *
   */
  Image(int width, int height);
  /**
   * @brief Constructor for string filename argument.
   *
   */
  Image(std::string filename);
  /**
   * @brief Construct a new Image object with a buffer as the argument
   *
   * @param buffer
   */
  Image(unsigned char *buffer, int width, int height);
  /**
   * @brief Constructor for Image image argument.
   *
   */
  Image(const Image &img);
  /**
   * @brief Destructor.
   *
   */
  ~Image();
  /**
   * @brief Save taking in a string argument filename to save to.
   *
   */
  void SaveAs(std::string filename);
  /**
   * @brief Width getter.
   *
   * @return Int width.
   */
  int GetWidth();
  /**
   * @brief Height getter.
   *
   * @return Int height.
   */
  int GetHeight();
  /**
   * @brief Component number getter.
   *
   * @return Int componentNum.
   */
  int GetComponentNum();
  /**
   * @brief Size getter.
   *
   * @return Int size.
   */
  int GetSize();
  /**
   * @brief Pixel getter given arguments int x, int y, Color p.
   *
   */
  void GetPixel(int x, int y, Color &p);
  /**
   * @brief Pixel setter given arguments int x, int y, Color p.
   *
   */
  void SetPixel(int x, int y, Color &p);
  /**
   * @brief Set the Pixel Data object, does not multiply values by 255
   *
   * @param x
   * @param y
   * @param p
   */
  void SetPixelData(int x, int y, Color &p);
  /**
   * @brief Get the Data object
   *
   * @return unsigned*
   */
  unsigned char *GetData();
  /**
   * @brief Set the Data object
   *
   * @param data
   */
  void SetData(unsigned char *data);
  /**
   * @brief = operator given an Image image
   *
   */
  void operator=(const Image &img);

private:
  unsigned char *image;
  int width, height;
  int components, size;
  // size is used for the size of the image array, but it's not accessible even
  // through getters
};
#endif

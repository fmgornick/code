/**
 * @file color.h
 */
#ifndef COLOR_H_
#define COLOR_H_
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief The main class for Color. 
 * We used a color class to make operations for color arithmatic easier. This makes it easy to add mutliply and set colors equal to eachother. 
 * The color class also makes it easy to get access to comonly used colors like black and white.
 *
 */
class Color {
public:
  /**
   * @brief Constructor for no arguments.
   *
   */
  Color() : r(0), g(0), b(0), a(1) {}
  /**
   * @brief Constructor for float red, float green, and float blue arguments.
   *
   */
  Color(float r, float g, float b) : r(r), g(g), b(b), a(1) {}
  /**
   * @brief Constructor for float red, float green, float blue, and float alpha
   * arguments.
   *
   */
  Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
  /**
   * @brief Red value getter.
   *
   * @return Float red.
   */
  float getR() { return r; }
  /**
   * @brief Green value getter.
   *
   * @return Float green.
   */
  float getG() { return g; }
  /**
   * @brief Blue value getter.
   *
   * @return Float blue.
   */
  float getB() { return b; }
  /**
   * @brief Alpha value getter.
   *
   * @return Float alpha.
   */
  float getA() { return a; }
  /**
   * @brief Luminance getter.
   *
   * @return Float luminance.
   */
  float GetLuminance() { return 0.2126 * r + 0.7152 * g + 0.0722 * b; }
  /**
   * @brief RGBA setter given unsigned char aray of pixels.
   *
   */
  void setRGBA(unsigned char *pixel) {
    r = (float)pixel[0] / 255;
    g = (float)pixel[1] / 255;
    b = (float)pixel[2] / 255;
    a = (float)pixel[3] / 255;
  }
  /**
   * @brief RGBA setter given float values for r,g,b, and a.
   *
   */
  void setRGBA(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }
  /**
   * @brief Red setter.
   *
   */
  void setR(float r) { this->r = r; }
  /**
   * @brief Green setter.
   *
   */
  void setG(float g) { this->g = g; }
  /**
   * @brief Blue setter.
   *
   */
  void setB(float b) { this->b = b; }
  /**
   * @brief Alpha setter.
   *
   */
  void setA(float a) { this->a = a; }
  /**
   * @brief Clear color function.
   *
   */
  void Clear() {
    r = 0.0;
    g = 0.0;
    b = 0.0;
    a = 0.0;
  }
  /**
   * @brief Color black
   *
   */
  static Color black() { return Color(0, 0, 0); }
  /**
   * @brief Color white
   *
   */
  static Color white() { return Color(1, 1, 1); }
  /**
   * @brief = operator given a Color color
   *
   */
  void operator=(const Color &color) {
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
  }
  /**
   * @brief + operator given a Color color
   *
   */
  Color operator+(const Color &color) {
    return Color(r + color.r, g + color.g, b + color.b, a);
  }
  /**
   * @brief - operator given a Color color
   *
   */
  Color operator-(const Color &color) {
    return Color(r - color.r, g - color.g, b - color.b, a);
  }
  /**
   * @brief * operator given a float scalar
   *
   */
  Color operator*(float scalar) {
    return Color(r * scalar, g * scalar, b * scalar, a);
  }
  /**
   * @brief * operator given a Color color
   *
   */
  Color operator*(const Color &color) {
    return Color(r * color.r, g * color.g, b * color.b, a);
  }
  /**
   * @brief / operator given a float scalar
   *
   */
  Color operator/(float scalar) {
    return Color(r / scalar, g / scalar, b / scalar, a);
  }
  /**
   * @brief equality operator for color variables
   *
   */
  int operator==(const Color &color) {
    if (r == color.r && g == color.g && b == color.b)
      return 1;
    return 0;
  }
  /**
   * @brief opposite of equality operator for color variables
   *
   */
  int operator!=(const Color &color) {
    if (r != color.r || g != color.g || b != color.b)
      return 1;
    return 0;
  }

private:
  float r, g, b, a;
};

#endif

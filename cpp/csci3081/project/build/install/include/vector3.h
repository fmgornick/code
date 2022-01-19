/**
 * @file vector3.h
 */
#ifndef VECTOR_3_H_
#define VECTOR_3_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief basic 3D vector class.  Will be primarily used for entity position and
 * velocity
 */
class Vector3 {
public:
  /**
   * @brief default constructor. Sets all the values to 0.
   */
  Vector3() : x(0), y(0), z(0) {}
  /**
   * @brief contructor that takes in 3 arguments for x,y,z components
   */
  Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
  /**
   * @brief getter: returns x value as float
   */
  float GetX() { return x; }
  /**
   * @brief getter: returns y value as float
   */
  float GetY() { return y; }
  /**
   * @brief getter: returns z value as float
   */
  float GetZ() { return z; }
  /**
   * @brief uses the cartesian metric to find 3D magnitude and returns value as
   * a float
   */
  float GetMagnitude() { return std::sqrt(x * x + y * y + z * z); }
  /**
   * @brief returns a new vector with same direction, but new magnitude of 1
   */
  Vector3 Normalize() { return *this / this->GetMagnitude(); }
  /**
   * @brief returns float corresponding to the two vector's dot products
   */
  float DotProduct(Vector3 v) { return x * v.x + y * v.y + z * v.z; }
  /**
   * @brief returns new vector that's the cross product of our current vector
   * and the inputed vector argument
   */
  Vector3 CrossProduct(Vector3 v) {
    float newX = y * v.z - z * v.y;
    float newY = z * v.x - x * v.z;
    float newZ = x * v.y - y * v.x;
    return Vector3(newX, newY, newZ);
  }
  /**
   * @brief set current vector equal to input vector
   */
  void operator=(Vector3 v) {
    x = v.x;
    y = v.y;
    z = v.z;
  }
  /**
   * @brief adds two vectors and returns new sum vector
   */
  Vector3 operator+(Vector3 v) { return Vector3(x + v.x, y + v.y, z + v.z); }
  /**
   * @brief subtracts two vectors and returns new difference vector
   */
  Vector3 operator-(Vector3 v) { return Vector3(x - v.x, y - v.y, z - v.z); }
  /**
   * @brief multiplies two vectors and returns new product vector
   */
  Vector3 operator*(Vector3 v) { return Vector3(x * v.x, y * v.y, z * v.z); }
  /**
   * @brief multiplies current vector by a scalar and returns new product vector
   */
  Vector3 operator*(float s) { return Vector3(x * s, y * s, z * s); }
  /**
   * @brief divides two vectors and returns new quotient vector
   */
  Vector3 operator/(Vector3 v) { return Vector3(x / v.x, y / v.y, z / v.z); }
  /**
   * @brief divides current vector by a scalar and returns new quotient vector
   */
  Vector3 operator/(float s) { return Vector3(x / s, y / s, z / s); }
  /**
   * @brief returns boolean representing euality of the two vectors
   */
  bool operator==(Vector3 v) const {
    return (x == v.x && y == v.y && z == v.z);
  }

private:
  /** @brief value of our 3D array */
  float x;
  /** @brief value of our 3D array */
  float y;
  /** @brief value of our 3D array */
  float z;
};

#endif // !VECTOR_3_H_

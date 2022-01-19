/**
 * @file fft_convolution_test.cc
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "image.h"
#include "gtest/gtest.h"
#include <cmath>
#include <string>
/*******************************************************************************
 * Class Definition
 ******************************************************************************/
/**
 * @brief This is a series of unit tests to check how accurate my FFT image
 * convolution filter works.  In the image directory, there are a series of
 * images with "expected" and "actual" suffixes.  The expected comes from an
 * online gaussian blur filter with size 13 kernel and an (i just guessed)
 * standard deviation of 2.  The site is https://pinetools.com/blur-image.  The
 * actual output comes from our image_processor software, and I check to see how
 * similar the pixel values are by summming up the differences and dividing by
 * the size of the image.
 */
class FilterTest : public ::testing::Test {
public:
  /**
   * @brief Initialize our images with our Image class (which uses stbi image).
   * This way we can have an array of color variables to make it easy to compare
   * RGB values.  Also have a double to calculate the difference of our image.
   * The difference is summed up by every pixel and divided by the size of the
   * image.  Our actual tests check to see if the difference is below a
   * threshold of
   */
  void SetUp() {
    statue_expected =
        Image("/home/user/repo/project/tests/data/images/statue_expected.png");
    statue_actual =
        Image("/home/user/repo/project/tests/data/images/statue_actual.png");

    david_byrne_expected = Image(
        "/home/user/repo/project/tests/data/images/david_byrne_expected.png");
    david_byrne_actual = Image(
        "/home/user/repo/project/tests/data/images/david_byrne_actual.png");

    raccoon_expected =
        Image("/home/user/repo/project/tests/data/images/raccoon_expected.png");
    raccoon_actual =
        Image("/home/user/repo/project/tests/data/images/raccoon_actual.png");

    charlie_expected =
        Image("/home/user/repo/project/tests/data/images/charlie_expected.png");
    charlie_actual =
        Image("/home/user/repo/project/tests/data/images/charlie_actual.png");

    difference = 0.0;
  }

protected:
  Image statue_expected, david_byrne_expected, raccoon_expected,
      charlie_expected;
  Image statue_actual, david_byrne_actual, raccoon_actual, charlie_actual;
  Color p_expected, p_actual;
  double difference;
};

/**
 * @brief check similarity between statue expected and actual blur
 */
TEST_F(FilterTest, StatueBlur) {
  for (int x = 0; x < statue_actual.GetWidth(); x++) {
    for (int y = 0; y < statue_actual.GetHeight(); y++) {
      statue_expected.GetPixel(x, y, p_expected);
      statue_actual.GetPixel(x, y, p_actual);
      difference += std::abs(p_expected.getR() - p_actual.getR());
    }
  }
  difference /= (statue_actual.GetWidth() * statue_actual.GetHeight());
  EXPECT_LT(difference, 0.01)
      << "difference not below given threshold" << std::endl;
}

/**
 * @brief check similarity between image of David Byrne expected and actual blur
 */
TEST_F(FilterTest, DavidByrneBlur) {
  for (int x = 0; x < david_byrne_actual.GetWidth(); x++) {
    for (int y = 0; y < david_byrne_actual.GetHeight(); y++) {
      david_byrne_expected.GetPixel(x, y, p_expected);
      david_byrne_actual.GetPixel(x, y, p_actual);
      difference += std::abs(p_expected.getR() - p_actual.getR());
    }
  }
  difference /=
      (david_byrne_actual.GetWidth() * david_byrne_actual.GetHeight());
  EXPECT_LT(difference, 0.01)
      << "difference not below given threshold" << std::endl;
}

/**
 * @brief check similarity between picture of a raccon expected and actual blur
 */
TEST_F(FilterTest, RaccoonBlur) {
  for (int x = 0; x < raccoon_actual.GetWidth(); x++) {
    for (int y = 0; y < raccoon_actual.GetHeight(); y++) {
      raccoon_expected.GetPixel(x, y, p_expected);
      raccoon_actual.GetPixel(x, y, p_actual);
      difference += std::abs(p_expected.getR() - p_actual.getR());
    }
  }
  difference /= (raccoon_actual.GetWidth() * raccoon_actual.GetHeight());
  EXPECT_LT(difference, 0.01)
      << "difference not below given threshold" << std::endl;
}

/**
 * @brief check similarity between picture of my dog Charlie expected and actual
 * blur
 */
TEST_F(FilterTest, CharlieBlur) {
  for (int x = 0; x < charlie_actual.GetWidth(); x++) {
    for (int y = 0; y < charlie_actual.GetHeight(); y++) {
      charlie_expected.GetPixel(x, y, p_expected);
      charlie_actual.GetPixel(x, y, p_actual);
      difference += std::abs(p_expected.getR() - p_actual.getR());
    }
  }
  difference /= (charlie_actual.GetWidth() * charlie_actual.GetHeight());
  EXPECT_LT(difference, 0.01)
      << "difference not below given threshold" << std::endl;
}

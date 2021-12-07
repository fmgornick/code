#include "./../include/greyscale_filter.h"

GreyScaleFilter::GreyScaleFilter() {}
GreyScaleFilter::~GreyScaleFilter() {}

void GreyScaleFilter::ApplyAtPixel(Color &p) {
  float lum = p.GetLuminance();
  p.setRGBA(lum, lum, lum, p.getA());
}

/*void GreyScaleFilter::ApplyKernel(std::vector<Image *> original,
                            std::vector<Image *> filtered) {
  // iterate through images in input vector
  for (int i = 0; i < original.size(); i++) {
    // set filtered image equal to original then iterate through filtered image
    *filtered[i] = *original[i];
    // create reference to make access easier
    Image &img = *filtered[i];

    // iterate through each pixel in the image
    for (int j = 0; j < img.GetWidth(); j++) {
      for (int k = 0; k < img.GetHeight(); k++) {
        Color p;
        img.GetPixel(j, k, p);
        // find luminance of the pixel
        float lum = p.GetLuminance();
        // set each RGB value to the luminance making it greyscale
        Color newP(lum, lum, lum, p.getA());
        // alter pixel in filtered image
        img.SetPixel(j, k, newP);
      }
    }
  }
}*/

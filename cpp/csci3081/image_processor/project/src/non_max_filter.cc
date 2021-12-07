#include "non_max_filter.h"
#include <math.h>

NonMaxFilter::NonMaxFilter() {}

// original[k] must be the image trying to filter
// original[k+1] must be angle data from a gradient filter, values are between 0
// and 360
void NonMaxFilter::Apply(std::vector<Image *> original,
                         std::vector<Image *> filtered) {
  for (int i = 0; i < original.size(); i += 2) {
    // create reference
    int width = original[i]->GetWidth();
    int height = original[i]->GetHeight() / 2;
    Image img(width, height);

    for (int x = 1; x < img.GetWidth() - 1; x++) {
      for (int y = 1; y < img.GetHeight() - 1; y++) {
        Color q = Color::white(), r = Color::white();
        Color angleColor;
        original[i]->GetPixel(x, y + height, angleColor);
        float angle = angleColor.getR() * 180; // convert to degrees

        if ((angle >= 0 && angle < 22.5) ||
            (angle >= 157.5 && angle <= 180)) { // Angle 0
          original[i]->GetPixel(x, y + 1, q);
          original[i]->GetPixel(x, y - 1, r);
        } else if (angle >= 22.5 && angle < 67.5) { // Angle 45
          original[i]->GetPixel(x + 1, y - 1, q);
          original[i]->GetPixel(x - 1, y + 1, r);
        } else if (angle >= 67.5 && angle < 112.5) { // Angle 90
          original[i]->GetPixel(x + 1, y, q);
          original[i]->GetPixel(x - 1, y, r);
        } else if (angle >= 112.5 && angle < 157.5) { // Angle 135
          original[i]->GetPixel(x - 1, y - 1, q);
          original[i]->GetPixel(x + 1, y + 1, r);
        }

        Color pixel;
        original[i]->GetPixel(x, y, pixel);
        if (pixel.getR() < q.getR() || pixel.getR() < r.getR())
          pixel = Color::black();

        img.SetPixel(x, y, pixel);
      }
    }
    *filtered[i] = img;
  }
}

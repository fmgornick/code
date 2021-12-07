#include "hysteresis_filter.h"

void HysteresisFilter::Apply(std::vector<Image *> original,
                             std::vector<Image *> filtered) {
  for (int i = 0; i < original.size(); i++) {
    *filtered[i] = *original[i];
    Image &img = *filtered[i];

    // iterate thorugh all pixels not on the edges
    for (int j = 1; j < original[i]->GetWidth() - 1; j++) {
      for (int k = 1; k < original[i]->GetHeight() - 1; k++) {
        Color p;
        original[i]->GetPixel(j, k, p);

        // check if pixel is weak, floating point comparison so set error at
        // 10^-3
        if (p != Color::black() && p != Color::white()) {
          // loop through the surrounding pixels
          for (int l = j - 1; l <= j + 1; l++) {
            for (int m = k - 1; m <= k + 1; m++) {
              Color p2;
              original[i]->GetPixel(l, m, p2);
              if (p2 == Color::white())
                p = Color::white();
            }
          }

          if (p != Color::white())
            p = Color::black();
          img.SetPixel(j, k, p);
        }
      }
    }
  }
}

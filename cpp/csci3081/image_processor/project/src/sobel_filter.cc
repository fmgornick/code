#include "sobel_filter.h"
#include <cmath>

void SobelFilter::Apply(std::vector<Image *> original,
                        std::vector<Image *> filtered) {
  for (int i = 0; i < original.size(); i++) {
    int width = original[i]->GetWidth();
    int height = original[i]->GetHeight();
    // top half of output image is intensity, and bottom half is direction
    Image img(width, height * 2);
    int kx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int ky[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

    Color newP;
    float max_gradient = 0;

    for (int j = 1; j < width - 1; j++) {
      for (int k = 1; k < height - 1; k++) {
        newP.Clear();
        Color px, py;
        for (int l = j - 1; l <= j + 1; l++) {
          for (int m = k - 1; m <= k + 1; m++) {
            Color p;
            original[i]->GetPixel(l, m, p);
            px = px + (p * kx[(j - l + 1) + (k - m + 1) * 3]);
            py = py + (p * ky[(j - l + 1) + (k - m + 1) * 3]);
          }
        }

        // calculate pixel values for intensity image
        newP = px * px + py * py;
        newP = newP / (std::sqrt(newP.getR()));
        if (max_gradient < newP.getR())
          max_gradient = newP.getR();
        newP = newP / 4;
        img.SetPixel(j, k, newP);

        // calculate pixel values for direction image
        float theta = std::atan2(py.getR(), px.getR());
        theta = theta / (2 * M_PI);
        newP = Color::white() * theta;
        img.SetPixel(j, k + height, newP);
      }
    }
    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        Color p;
        img.GetPixel(x, y, p);
        p = (p * 4) / max_gradient;
        img.SetPixel(x, y, p);
      }
    }
    *filtered[i] = img;
  }
}

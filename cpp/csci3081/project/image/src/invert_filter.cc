#include "invert_filter.h"

InvertFilter::InvertFilter() {}
InvertFilter::~InvertFilter() {}

void InvertFilter::ApplyAtPixel(Color &p) {
    p = Color::white()-p;
}
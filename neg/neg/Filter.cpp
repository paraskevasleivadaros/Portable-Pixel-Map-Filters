#include "Filter.h"
#include <math.h>

using namespace math;

Filter::Filter() {}
Filter::Filter(const Filter &f) {}
Filter::~Filter() {}

FilterLinear::FilterLinear() : a(0.0), c(0.0) {}
FilterLinear::FilterLinear(Color a, Color c) : a(a), c(c) {}
FilterLinear::~FilterLinear() {}
imaging::Image FilterLinear::operator << (const imaging::Image& image) {
		
	imaging::Image imgObj = image;

	for (unsigned int i = 0; i < imgObj.getWidth(); i++) {
		for (unsigned int j = 0; j < imgObj.getHeight(); j++) {
			
			Color rgb = imgObj.getPosition(i, j)*a + c;

			rgb = rgb.clampToLowerBound(0.0f);
			rgb = rgb.clampToUpperBound(1.0f);

			imgObj.setPosition(i, j, rgb);
		}
	}
	return imgObj;
}

FilterGamma::FilterGamma() : gamma(0.0) {}
FilterGamma::FilterGamma(float gamma) : gamma(gamma) {}
FilterGamma::~FilterGamma() {}
imaging::Image FilterGamma::operator << (const imaging::Image& image) {
		
	imaging::Image imgObj = image;

	for (unsigned int i = 0; i < imgObj.getWidth(); i++) {
		for (unsigned int j = 0; j < imgObj.getHeight(); j++) {

			imgObj(i, j).r = pow(imgObj(i, j).r, gamma);
			imgObj(i, j).g = pow(imgObj(i, j).g, gamma);
			imgObj(i, j).b = pow(imgObj(i, j).b, gamma);
		}
	}
	return imgObj;
}
#include "Filter.h"

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

			// every color channel must be in the range [0,1] 
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
		for (unsigned int j = 0; j < imgObj.getHeight(); j++)
			// applying filter gamma
			imgObj(i, j) = { pow(imgObj(i, j).r, gamma), pow(imgObj(i, j).g, gamma), pow(imgObj(i, j).b, gamma) };		
	}
	return imgObj;
}
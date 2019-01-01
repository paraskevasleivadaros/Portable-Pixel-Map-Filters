#include "Filter.h"


typedef math::Vec3<float> Color;


	Filter::Filter() {}
	Filter::~Filter() {}
	Filter::Filter(const Filter &f) {}

	FilterLinear::FilterLinear() :a(0.0), c(0.0) {}
	FilterLinear::FilterLinear(Color a, Color c) :a(a), c(c) {}
	FilterLinear::~FilterLinear() {}
	imaging::Image FilterLinear::operator << (const imaging::Image & image) {
		
		imaging::Image imgObj = image;

		for (unsigned int i = 0; i < imgObj.getHeight(); i++) {
			for (unsigned int j = 0; j < imgObj.getWidth(); j++) {
			
				Color rgb = a * imgObj.getPosition(i, j) + c;

				rgb = rgb.clampToLowerBound(0.0);
				rgb = rgb.clampToUpperBound(1.0);

				imgObj.setPosition(i, j, rgb);
			}
		}
		return imgObj;
	}

	FilterGamma::FilterGamma() :g(0.0) {}
	FilterGamma::FilterGamma(float g) :g(g) {}
	FilterGamma::~FilterGamma() {}
	imaging::Image FilterGamma::operator << (const imaging::Image & image) {
		
		imaging::Image imgObj = image;

		for (unsigned int i = 0; i < imgObj.getHeight(); i++) {
			for (unsigned int j = 0; j < imgObj.getWidth(); j++) {

				imgObj(i, j).r = pow(imgObj(i, j).r, g);
				imgObj(i, j).g = pow(imgObj(i, j).g, g);
				imgObj(i, j).b = pow(imgObj(i, j).b, g);
			}
		}
		return imgObj;
	}

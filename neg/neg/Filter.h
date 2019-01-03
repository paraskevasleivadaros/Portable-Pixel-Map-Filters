#pragma once

#ifndef _FILTER
#define _FILTER

#include "Image.h"
#include "Vec3.h"

typedef math::Vec3<float> Color;

class Filter {
	public:
		Filter();
		Filter(const Filter &f);
		virtual ~Filter();
	
		virtual imaging::Image operator << (const imaging::Image & image) = 0;
};

class FilterLinear:public Filter {

	public:
		FilterLinear();
		FilterLinear(Color a, Color c);
		~FilterLinear();
		imaging::Image operator << (const imaging::Image & image);

	private:
		Color a,c;
};

class FilterGamma :public Filter {

	public:
		FilterGamma();
		FilterGamma(float gamma);
		~FilterGamma();
		virtual imaging::Image operator << (const imaging::Image & image);
	
	private:
		float gamma;	
};
#endif
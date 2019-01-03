#pragma once

#ifndef _FILTER
#define _FILTER

#include "Image.h"

class Filter {
	
	public:
		Filter();
		Filter(const Filter &f);
		virtual ~Filter();
	
	protected:
		virtual imaging::Image operator << (const imaging::Image& image) = 0;
};

class FilterLinear : public Filter {
	
	private:
		Color a, c;

	public:
		FilterLinear();
		FilterLinear(Color a, Color c);
		~FilterLinear();
		imaging::Image operator << (const imaging::Image& image);
};

class FilterGamma : public Filter {
	
	private:
		float g;

	public:
		FilterGamma();
		FilterGamma(float g);
		~FilterGamma();
		imaging::Image operator << (const imaging::Image& image);
};
#endif
#include "Filter.h"

Filter::Filter() {
	#ifdef _DEBUG
		std::cout << "	f-> Filter constructor\n";
	#endif	
}
Filter::Filter(const Filter &f) {
	#ifdef _DEBUG
		std::cout << "	f-> Filter copy constructor\n";
	#endif	
}
Filter::~Filter() {
	#ifdef _DEBUG
		std::cout << "	f-> Filter destructor\n";
	#endif	
}

FilterLinear::FilterLinear() : a(0.0), c(0.0) {
	#ifdef _DEBUG
		std::cout << "	l-> Filter Linear constructor\n";
	#endif	
}
FilterLinear::FilterLinear(Color a, Color c) : a(a), c(c) {
	#ifdef _DEBUG
		std::cout << "	l-> Filter Linear constructor\n";
	#endif	
}
FilterLinear::~FilterLinear() {
	#ifdef _DEBUG
		std::cout << "	l-> Filter Linear destructor\n";
	#endif	
}
imaging::Image FilterLinear::operator << (const imaging::Image& image) {	
	#ifdef _DEBUG
		std::cout << "	l-> FilterLinear::operator <<\n";
	#endif	

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

FilterGamma::FilterGamma() : gamma(0.0) {
	#ifdef _DEBUG
		std::cout << "	g-> Filter Gamma constructor\n";
	#endif	
}
FilterGamma::FilterGamma(float gamma) : gamma(gamma) {
	#ifdef _DEBUG
		std::cout << "	g-> Filter Gamma constructor\n";
	#endif	
}
FilterGamma::~FilterGamma() {
	#ifdef _DEBUG
		std::cout << "	g-> Filter Gamma destructor\n";
	#endif	
}
imaging::Image FilterGamma::operator << (const imaging::Image& image) {	
	#ifdef _DEBUG
		std::cout << "	g-> FilterGamma::operator <<\n";
	#endif	

	imaging::Image imgObj = image;

	for (unsigned int i = 0; i < imgObj.getWidth(); i++) {
		for (unsigned int j = 0; j < imgObj.getHeight(); j++)
			// applying filter gamma
			imgObj(i, j) = { pow(imgObj(i, j).r, gamma), pow(imgObj(i, j).g, gamma), pow(imgObj(i, j).b, gamma) };		
	}
	return imgObj;
}
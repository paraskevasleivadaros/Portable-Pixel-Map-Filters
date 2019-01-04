#include "../ppm/ppm.h"
#include "Image.h"
#include <ostream>

namespace imaging {

	bool isPPM(std::string& filename);
	bool areEqual(const std::string& a, const std::string& b);

	//Default constructor
	Image::Image() {}

	Image::Image(unsigned int width, unsigned int height) : Array<Color>(width, height) {}

	Image::Image(unsigned int width, unsigned int height, std::vector<Color> & data_ptr) : Array<Color>(width, height, data_ptr) {}

	//Copy constructor
	Image::Image(const Image &src) : Array(src) {}

	//Destructor
	Image::~Image() {}

	//Loads the image data from the specified file, if the extension of the filename matches the format string
	bool Image::load(const std::string & filename, const std::string & format) {

		int i_width, i_height;

		std::string filenameNotConst = filename;
		if (!isPPM(filenameNotConst)) return false;

		if (format != "ppm") return false;

		
		float * f_buffer = ReadPPM(filename.c_str(), &i_width, &i_height); // calling ReadPPM()
		
		float * f_ptr = f_buffer; // temporary pointer that points to f_buffer

		// check if reading the image succeded
		if (f_buffer == nullptr) {
			std::cerr << "Error: Load of Image Failed!\n";
			return false;
		} else {

			buffer.resize(i_width * i_height);
			Color * color = new Color();

			// load into our color vector pointers (that show to green, red, blue of each pixel) the data from the loaded image 
			for (unsigned int i = 0; i < buffer.size(); i++) {

				(*color).r = *f_ptr;
				f_ptr++;

				(*color).g = *f_ptr;
				f_ptr++;

				(*color).b = *f_ptr;
				f_ptr++;

				buffer[i] = *color;
			}

			width = i_width;
			height = i_height;			

			delete[] f_buffer, color; // free the memory
			return true;
		}
	}

	bool Image::save(const std::string & filename, const std::string & format) {

		std::string filenameNotConst = filename;
		if (!isPPM(filenameNotConst)) return false;

		if (format != "ppm") { return false; }

		float *f_buffer = new float[width * height * 3]; // table we will write to the file

		int w = width;
		int h = height;

		// copies the data from buffer to f_buffer
		for (int i = 0; i < w * h; i++) {

			f_buffer[i * 3] = buffer[i].r;
			f_buffer[i * 3 + 1] = buffer[i].g;
			f_buffer[i * 3 + 2] = buffer[i].b;
		}

		bool done = WritePPM(f_buffer, width, height, filename.c_str());

		delete[] f_buffer; // freeing memory

		return done;
	}

	//Checks if format="ppm"
	bool isPPM(std::string& filename) {	return (areEqual(filename.substr(filename.find_last_of(".") + 1), "ppm"));}

	//checks if 2 strings are equal
	bool areEqual(const std::string& a, const std::string& b) {

		if (b.size() != a.size()) return false;

		for (unsigned int i = 0; i < a.size(); ++i) 
			if (tolower(a[i]) != tolower(b[i]))	return false;

		return true;
	}
}
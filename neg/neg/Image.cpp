#include "../ppm/ppm.h"
#include "Image.h"
#include <ostream>
#include <string>

namespace imaging {

	bool isPPM(std::string& filename);
	bool areEqual(const std::string& a, const std::string& b);
	
	//Default constructor
	Image::Image() {}

	Image::Image(unsigned int width, unsigned int height) : Array<Color>(width, height) {}
	
	Image::Image(unsigned int width, unsigned int height, std::vector<Color> & data_ptr) : Array<Color>(width, height, data_ptr) {}
	
	//Copy constructor
	Image::Image(const Image &src) : Array(src) {}

	/*! Copy assignment operator.
	 *
	 *\param right is the source image.
	*/
	/*Image & Image::operator = (const Image & right) {

		if (&right == this)	return *this;
		if (!this->buffer.empty()) this->buffer.clear();

		buffer.resize(width * height);
		for (int i = 0; i < buffer.size(); i++) 
			buffer[i] = right.buffer[i];

		this->width = right.width;
		this->height = right.height;
		return *this;
	}*/

	//destructor
	Image::~Image() {}

	//Loads the image data from the specified file, if the extension of the filename matches the format string
	bool Image::load(const std::string & filename, const std::string & format) {

		std::string filenameNotConst = filename;
		if (!isPPM(filenameNotConst)) return false;

		if (format != "ppm") return false;

		int i_height = height;
		int i_width = width;

		// calls the ReadPPM which returns a pointer to float array and gives values to the 2 integers that we passed
		float * f_buffer = ReadPPM(filename.c_str(), &i_width, &i_height); 
		// temporary pointer that shows in the begining of the table which contains the data we read
		float * f_ptr = f_buffer; 

		// check if we read the image correctly
		// if ReadPPM returned null we failed to read the file and we return false
		if (f_buffer == nullptr) {
			std::cerr << "Error: Image Loading Failed\n";
			return false;
		} else {

			buffer.resize(width*height);
			Color * color = new Color();

			// initialize the pointers that show to green,  red, blue in the array we loaded before
			for (int i = 0; i < buffer.size(); i++) {

				color->r = *f_ptr;
				f_ptr++;

				color->g = *f_ptr;
				f_ptr++;

				color->b = *f_ptr;
				f_ptr++;

				buffer[i] = *color;
			}

			delete[] f_buffer, color; // free the memory
			return true;
		}
	}

	//Stores the image data to the specified file, if the extension of the filename matches the format string.
	bool Image::save(const std::string & filename, const std::string & format) {
		
		std::string filenameNotConst = filename;
		if (!isPPM(filenameNotConst)) return false;
		
		if (format != "ppm") return false;

		Color * color_buffer = getRawDataPtr(); // a pointer to use it to pass all the data

		float * f_buffer = new float[width * height * 3]; // create an new float table, this table we will write to the file
		float * f_ptr = f_buffer; //  a pointer to use it to get access to all the table

		// copy the data from buffer to the new table
		// its color takes a different cell in the table
		for (unsigned int i = 0; i < width*height; i++) {

			*f_ptr = color_buffer->r;
			f_ptr++;

			*f_ptr = color_buffer->g;
			f_ptr++;

			*f_ptr = color_buffer->b;
			f_ptr++;

			color_buffer++;
		}

		delete[] f_buffer, color_buffer; // freeing memory

		return WritePPM(f_buffer, width, height, filename.c_str());
	}

	//Checks if format="ppm"
	bool isPPM(std::string& filename) {

		return (areEqual(filename.substr(filename.find_last_of(".") + 1), "ppm") ? true : false);
	}

	//checks if 2 strings are equal
	bool areEqual(const std::string& a, const std::string& b) {

		if (b.size() != a.size()) return false;

		for (unsigned int i = 0; i < a.size(); ++i) {
			if (tolower(a[i]) != tolower(b[i])) {
				return false;
			}
		}

		return true;
	}
}
#pragma once

#ifndef _ARRAY
#define _ARRAY

#include <vector>
#include <iostream>



namespace math
{
	template <typename T>

	class Array
	{
	public:

	protected:
		 std::vector<T> buffer;                             

		unsigned int width,height;		                 

	public:

		const unsigned int getWidth() const { return width; }
		const unsigned int getHeight() const { return height; }

		T * getRawDataPtr() {
			return buffer;
		}

		T getPosition(unsigned int x, unsigned int y) const {
			//T Color;
			//if x,y pair is out-of-bounds return a black (0,0,0) color
			if ((x > height - 1) || (y > width - 1)) {
				std::cerr << "Out of bounds!" << std::endl;
			}else {
				return buffer[x * width + y];//location of pixel inside array "buffer"
			}
		}

		void setPosition(unsigned int x, unsigned int y, T & value) {
			//if x,y pair is out-of-bounds return a black (0,0,0) color
			if ((x > height - 1) || (y > width - 1)) {
				std::cerr << "Out of bounds!" << std::endl;
			}
			else {
				buffer[x * width + y] = value;
			}
		}

		void setData(const T * & data_ptr) {
			//check if x,y pair is out-of-bounds
			if ((height == 0) || (width == 0) || (data_ptr == nullptr)) return;

			buffer.reserve(width*height);

			for (unsigned int i = 0; i < width * height; i++) {
				buffer[i] = data_ptr[i];
			}
		}

		Array() {
			buffer.reserve(0);
			width = 0;
			height = 0;
		}

		Array(unsigned int width, unsigned int height) {
			buffer.reserve(width * height);
			this->width = width;
			this->height = height;
		}

		Array(unsigned int width, unsigned int height, const T * data_ptr) {
			setData(data_ptr);
			this->width = width;
			this->height = height;
		}

		Array(const Array &src) {
			const T * data_ptr = src.buffer;
			setData(data_ptr);
			this->width = src.getWidth();
			this->height = src.getHeight();
		}

		virtual ~Array(){ buffer.clear(); }

		Array & operator = (const Array & right) {
			if (&right == this)	return *this;
			if (this->buffer != nullptr) delete[] buffer;

			const T * data_ptr = right.buffer;
			setData(data_ptr);
			this->width = right.width;
			this->height = right.height;
			return *this;//returns the object created inside here
		}

		T & operator()(unsigned int i, unsigned int j)
		{
			if (i >= width || j >= height) { std::cout << "Out of bounds!" << std::endl; }
			return buffer[i * width + j];
		}
	};
}

#endif
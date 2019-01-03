#pragma once

#ifndef _ARRAY
#define _ARRAY

#include <vector>
#include <iostream>

namespace math {

	template <typename T>

	class Array {

	protected:

		std::vector<T> buffer;
		unsigned int width, height;

	public:

		 unsigned int getWidth() const { return width; }
		 unsigned int getHeight() const { return height; }

		T * getRawDataPtr() {
			return buffer.data();
		}

		T getPosition(unsigned int x, unsigned int y) const {

			//if x,y pair is out-of-bounds return a black (0,0,0) color
			if ((x > width - 1) || (y > height - 1)) {
				std::cerr << "Error1: Out of bounds!\n";
				return NULL;
			}
			else {
				return buffer[y * width + x];//location of pixel inside array "buffer"
			}
		}

		void setPosition(unsigned int x, unsigned int y, T & value) {
			//if x,y pair is out-of-bounds return a black (0,0,0) color
			if ((x > width - 1) || (y > height - 1)) {
				std::cerr << "Error2: Out of bounds!\n";
				return;
			}
			else {
				buffer[y * width + x] = value;
			}
		}

		void setData(const T * & data_ptr) {
			//check if x,y pair is out-of-bounds
			if ((height == 0) || (width == 0) || (data_ptr == nullptr)) return;

			buffer.resize(width*height);

			for (unsigned int i = 0; i < width * height; i++) {
				buffer[i] = data_ptr[i];
			}
		}

		Array():width(0), height(0){
			buffer.resize(0);
		}

		Array(unsigned int width, unsigned int height):width(width), height(height) {
			buffer.resize(width * height);
		}

		Array(unsigned int width, unsigned int height, std::vector<T> & data_ptr) :width(width), height(height), buffer(data_ptr) {}

		Array(const Array<T> &src):width(src.getWidth()), height(src.getHeight()) {
			buffer.resize(src.width * src.height);
			for (unsigned int i = 0; i < buffer.size(); i++) {
				buffer[i] = src.buffer[i];
			}
		}

		virtual ~Array() { buffer.clear(); }

		Array<T> & operator = (const Array<T> & right) {

			if (&right == this)	return *this;
			if (!this->buffer.empty()) this->buffer.clear();

			buffer.resize(right.width * right.height);
			for (unsigned int i = 0; i < buffer.size(); i++) {
				buffer[i] = right.buffer[i];
			}
			this->width = right.width;
			this->height = right.height;
			return *this;

			/*if (this != &right)
			{
				this->width = right.width;
				this->height = right.height;
				buffer.resize(right.width*right.height);

				for (int i = 0; i < buffer.size(); i++) {
					buffer[i] = right.buffer[i];
				}
			}
			return *this;*/
		}

		T & operator()(unsigned int i, unsigned int j)
		{
			if (i >= width || j >= height) { std::cerr << "Error3: Out of bounds!\n";}
			return buffer[j * width + i];

		}
	};
}
#endif
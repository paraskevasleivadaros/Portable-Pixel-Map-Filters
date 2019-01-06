#pragma once

#ifndef _ARRAY
#define _ARRAY

#include <vector>
#include <iostream>

namespace math {

	template <typename T>

	//------------------------------------ class Array ------------------------------------------------
	class Array {

		protected:

			std::vector<T> buffer;  //! Holds the array data.
			unsigned int width,  //! The width of the image (in pixels)
				height; //! The height of the image (in pixels)

		public:
			// metric accessors

			/*! Returns the width of the array
			 */
			unsigned int getWidth() const { return width; }

			/*! Returns the height of the array
			 */
			unsigned int getHeight() const { return height; }

			// data accessors

		    /*! Obtains a pointer to the internal data.
			 *
			 *  This is NOT a copy of the internal array data, but rather a pointer
			 *  to the internally allocated space, so DO NOT attempt to delete the pointer.
			 */
  			T * getRawDataPtr() { return buffer.data(); }

			/*! Obtains the color of the array at location (x,y).
			 *
			 *  The method should do any necessary bounds checking.
			 *
			 *  \param x is the (zero-based) horizontal index of the pair to get.
			 *  \param y is the (zero-based) vertical index of the pair to get.
			 *
			 *  \return The color of the (x,y) pair as a T object. Returns NULL in case of an out-of-bounds x,y pair.
			 */
			T getPosition(unsigned int x, unsigned int y) const {

				//if x, y pair is out-of-bounds return NULL
				if ((x > width - 1) || (y > height - 1)) {
					std::cerr << "Error1: Out of bounds!\n";
					return NULL;
				} else {
					return buffer[y * width + x]; //returns the position of pixel inside array "buffer"
				}
			}

			// data mutators

			/*! Sets the 3 values for an (x,y) pair.
			 *
			 *  The method should perform any necessary bounds checking.
			 *
			 *  \param x is the (zero-based) horizontal index of the pair to set.
			 *  \param y is the (zero-based) vertical index of the pair to set.
			 *  \param value is the new T for the (x,y) pair.
			 */
			void setPosition(unsigned int x, unsigned int y, T & value) {
				
				// if x, y pair is out-of-bounds just return
				if ((x > width - 1) || (y > height - 1)) {
					std::cerr << "Error2: Out of bounds!\n";
					return;
				} else {
					buffer[y * width + x] = value; // sets the position of pixel inside array "buffer"
				}
			}

			/*! Copies the array data from an external raw buffer to the internal array buffer.
			 *
			 *  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the
			 *  Array object and that the data buffer has been already allocated. If the image buffer is not allocated or the
			 *  width or height of the array are 0, the method should exit immediately.
			 *
			 *  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Array object.
			 */
			void setData(const T * & data_ptr) {
				
				// check if x, y pair is out-of-bounds
				if ((height == 0) || (width == 0) || (data_ptr == nullptr)) return;

				buffer.resize(width*height);
				for (unsigned int i = 0; i < width * height; i++)
					buffer[i] = data_ptr[i];		
			}

			// constructors and destructor

			/*! Default constructor.
			 *
			 * By default, the dimensions of the array should be zero and the buffer size must be set to zero.
			 */
			Array() : width(0), height(0), buffer(std::vector<T>(0)) {}

			/*! Constructor with width and height specification.
			 *
			 * \param width is the desired width of the new Array.
			 * \param height is the desired height of the new Array.
			 */
			Array(unsigned int width, unsigned int height) : width(width), height(height), buffer(std::vector<T>(width*height)) {}

			/*! Constructor with data initialization.
			 *
			 * \param width is the desired width of the new image.
			 * \param height is the desired height of the new image.
			 * \param data_ptr is the source of the data to copy to the internal array buffer.
			 */
			Array(unsigned int width, unsigned int height, std::vector<T> & data_ptr) : width(width), height(height), buffer(data_ptr) {}


			/*! Copy constructor.
			 *
			 * \param src is the source array to replicate in this object.
			 */
			Array(const Array<T> &src) : width(src.getWidth()), height(src.getHeight()) {
				
				buffer.resize(src.width * src.height);
				for (unsigned int i = 0; i < buffer.size(); i++)
					buffer[i] = src.buffer[i];
			}

			/*! The Array destructor.
			 */
			virtual ~Array() { buffer.clear(); }

			/*! Copy assignment operator.
			 *
			 * \param right is the source array.
			 */
			Array<T> & operator = (const Array<T> & right) {

				if (&right == this)	return *this;

				buffer.resize(right.width * right.height);
				for (unsigned int i = 0; i < buffer.size(); i++) 
					buffer[i] = right.buffer[i];
				
				this->width = right.width;
				this->height = right.height;
				return *this;
			}

			/*! Reference assignment operator.
			 *
			 * The method should do any necessary bounds checking.
			 * \param i is the (zero-based) horizontal index of the pair to return.
			 * \param j is the (zero-based) vertical index of the pair to return.
			 *
			 * \return the color of the (x,y) pair as a T object. Prints error message in case of an out-of-bounds x,y pair.
			 */
			T & operator()(unsigned int i, unsigned int j) {

				if (i >= width || j >= height) std::cerr << "Error3: Out of bounds!\n";
				return buffer[j * width + i];
			}
	};
} // namespace math
#endif
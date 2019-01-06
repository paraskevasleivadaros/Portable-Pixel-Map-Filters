#pragma once

#ifndef _FILTER
#define _FILTER

#include "Image.h"

//------------------------------------ class Filter ------------------------------------------------

class Filter {

	public:

		// Constructors, destructor & operator

		/*! Default constructor.
		*/
		Filter();

		/*! Copy constructor.
		 *
		 * \param f is the source filter to replicate in this object.
		 */
		Filter(const Filter &f);

		/*! The Filter destructor.
	     */
		virtual ~Filter();	

		/*! Pure virtual operator << of Filter.
		 */
		virtual imaging::Image operator << (const imaging::Image & image) = 0;
};

class FilterLinear:public Filter {

	public:

		// Constructors, destructor & operator

		/*! Default constructor.
		*/
		FilterLinear();

		/*! Constructor with 2 Color objects specification.
		 *
		 * \param a is the first object of the new filter.
		 * \param c is the second object of the new filter.
		 */
		FilterLinear(Color a, Color c);

		/*! The Filter destructor.
		 */
		~FilterLinear();

		/*! Operator << of Filter.
		 */
		imaging::Image operator << (const imaging::Image & image);

	private:
		/*! 
		 * \param a is the first object of the new filter.
		 * \param c is the second object of the new filter.
		 */
		Color a, c;
};

class FilterGamma :public Filter {

	public:

		// Constructors, destructor & operator

		/*! Default constructor.
		*/
		FilterGamma();

		/*! Constructor with param gamma specification.
		 *
		 * \param gamma is the input for the new filter.
		 */
		FilterGamma(float gamma);

		/*! The Filter destructor.
	     */
		~FilterGamma();

		/*! Operator << of Filter.
		 */
		virtual imaging::Image operator << (const imaging::Image & image);
	
	private:

		/*!
		 * \param gamma is the input of the new filter.
		 */
		float gamma;	
};
#endif
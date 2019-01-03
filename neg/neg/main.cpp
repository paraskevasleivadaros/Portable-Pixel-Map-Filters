//LEIVADAROS PARASKEVAS 3150090
//KOYLOYRIS GEORGIOS 3150080
/*
#include <iostream>
#include <string>
#include "Filter.h"

void line();

int main(int argc, char *argv[]) {

	std::string filename;

	if (argc < 6) {

		std::cerr << "Error: Wrong Input" << std::endl;
		std::cerr << "====" << std::endl;

	}
	else {

		filename = argv[argc - 1];
		line();

		imaging::Image *imgObj = new imaging::Image;

		if (imgObj->load(filename, "ppm")) {

			std::cout << "Image dimensions are: " << imgObj->getWidth() << " X " << imgObj->getHeight() << std::endl;
			line();

			int i = 1;
			while (i < argc - 1) {
				if (argv[i] == std::string("filter")) {
					i++;
					if (argv[i] == std::string("-f")) {
						i++;
						if (argv[i] == std::string("linear")) {
							std::cerr << "====" << std::endl;
							Color a, c;
							i++;
							a.r = (float)atof(argv[i]);
							i++;
							a.g = (float)atof(argv[i]);
							i++;
							a.b = (float)atof(argv[i]);
							i++;
							c.r = (float)atof(argv[i]);
							i++;
							c.g = (float)atof(argv[i]);
							i++;
							c.b = (float)atof(argv[i]);
							i++;

							FilterLinear linear(a, c);
							*imgObj = linear << *imgObj;
							

						}
						else if (argv[i] == std::string("gamma")) {

							i++;
							float g = (float)atof(argv[i]);
							if (g >= 0.5 && g <= 2.0) {
								
								FilterGamma gamma(g);
								*imgObj = gamma << *imgObj;

							}
							else {

								line();
								std::cerr << "Error: Gamma values must be lower than 2.0 and higher than 0.5" << std::endl;
								line();

								system("PAUSE");
								return 1;
							}
						}
						else {

							line();
							std::cerr << "Error: Wrong type of filter" << std::endl;
							line();

							system("PAUSE");
							return 1;
						}

					}
					else { i++; }

				}
				//else { i++; }
			}
		}
		else {
			std::cerr << "Error: Image Failed Loading\n";
		}

		//adds the name of the new image
		std::string newfilename = "filtered_" + filename;

		if (!imgObj->save(newfilename, "ppm")) {

			std::cerr << "Error: Image Failed Saving\n";
		}

		imgObj->~Image();//Destroys the pointer of image object		
	}

	system("PAUSE");
	return 0;
}


void line() {
	std::cout << "*******************************************\n";
}*/





#include <iostream>
#include <string>
#include "Filter.h"
#include "Image.h"

using namespace imaging;
using namespace std;

int main(int argc, char* argv[]) {

	const char* file = nullptr;

	Image* image = new Image(); // create an Image object

	unsigned int i = 1; // pointer for the elements of the input	 

	if (argc < 1)
	{
		cerr << "Low number of input, try again" << endl;

	}
	else {

		file = argv[argc - 1]; // taking the name of the file

		cout << "Loading image " << endl << "----------" << endl;

		if (image->load(file, "ppm")) { // loads the image using the method load of the Image object

			cout << "Load  Succeed" << endl << "----------" << endl << "Image dimensions are: " << image->getWidth() << " X " << image->getHeight() << endl << "----------" << endl; // prints the dimensions of the Image

			cout << "Starting reading the input" << endl << "----------" << endl;

			while (i < argc - 1) { // starting a while loop in ordeer to read the whole input

				// strcmp() = compares 2 strings
				if (strcmp(argv[i], "-f") == 0) { // if we find -f char we expect to execute a filter

					i++; // go to the next element of the input

					if (string("gamma").compare(argv[i]) == 0) { // user selected the gamma 

						i++;

						float gamma = stof(argv[i], nullptr); // converting the string input to float 

						if (gamma < 0.5 || gamma > 2.0) { // check for gamma value. gamma should be between 0.5 and 2.0

							cout << "Gamma value is not acceptable" << endl << "Gamma should be between 0.5 and 2.0" << endl;

							system("pause");

							exit(1);
						}
						else {

							FilterGamma f(gamma); // create a FilterGamma object

							std::cout << "Applying gamma " << gamma << endl << "----------" << endl;

							*image = f << *image; // we apply filter gamma
						}
					}

					// stof() = converts a string to a float
					// takes the string as paremeter and a size_t* variable. The second variable an be nullptr
					if (string("linear").compare(argv[i]) == 0) {

						Color a, c; // we need 2 Colors objects in order to apply the linear filter					

						cout << "Initializing a and c" << endl;

						i++;

						a.r = stof(argv[i], nullptr);

						//cout << "A r = " << a.r << endl;

						i++;
						a.g = stof(argv[i], nullptr);

						//cout << "A g = " << a.g << endl;

						i++;
						a.b = stof(argv[i], nullptr);

						//cout << "A b = " << a.b << endl;

						i++;
						c.r = stof(argv[i], nullptr);

						//cout << "C r = " << c.r << endl;

						i++;
						c.g = stof(argv[i], nullptr);

						//cout << "C g = " << c.g << endl;

						i++;
						c.b = stof(argv[i], nullptr);

						//cout << "C b = " << c.b << endl;

						FilterLinear f(a, c); // create a FilterLinear object with the 2 Colors objects as input

						cout << "Applying linear " << endl << "----------" << endl;

						*image = f << *image; // aplying filter linear
					}

				}
				else {
					i++; // if we dont find -f char we continue to find it
				}
			}
		}
		else {
			cout << "Load failed!" << endl; // load of image has failed
		}
	}

	// Now we have to save the file with the name filtered_imagename.ppm

	string file_name = "filtered_"; // the string we want to to add	

	file_name.append(file); // we add the image name at the end of our file name

	if (image->save(file_name, "ppm")) { // calls the save method to save the file	

		cout << "Save succeed" << endl;
	}
	else {
		cout << "Save failed!" << endl;
	}

	delete image; // free the memory

	system("pause");

	return 0;
}

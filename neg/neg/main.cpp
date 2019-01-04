//LEIVADAROS PARASKEVAS 3150090
//KOYLOYRIS GEORGIOS 3150080
/*
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

		if (!imgObj->save(newfilename, "ppm")) { std::cerr << "Error: Image Failed Saving\n"; }

		imgObj->~Image();//Destroys the pointer of image object		
	}

	system("PAUSE");
	return 0;
}

void line() {
	std::cout << "*******************************************\n";
}
*/

#include "Filter.h"

void spacing() { std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - -\n"; }

int main(int argc, char* argv[]) {

	const char* file = nullptr;

	imaging::Image* image = new imaging::Image(); // create an Image object

	int i = 1; // pointer for the elements of the input	 

	if (argc < 6) {

		spacing();
		std::cerr << "Error: Bad Input\n";
		spacing();

		system("PAUSE");
		exit(1);

	} else {

		// taking the name of the file
		file = argv[argc - 1]; 

		spacing();
		std::cout << "Loading image...\n";
		spacing();

		// loads the image using the method load of the Image object
		if (image->load(file, "ppm")) {

			// prints the dimensions of the Image
			std::cout << "Loading Succeeded!\n";
			spacing();
			
			// prints the dimensions of the Image
			std::cout << "Image dimensions are: " << image->getWidth() << " X " << image->getHeight() << "\n";
			spacing();

			if (std::string(argv[i]) == "filter") {
				std::cout << "Reading image...\n";
				spacing();
			} else {
				system("PAUSE");
				exit(1);
			}

			i++; // go to the next command argument

			// starting a while loop in order to read the whole input
			while (i < argc - 1) {

				// if we find -f char we expect to execute a filter
				if (std::string(argv[i]) == "-f") {

					i++; // go to the next command argument

					// user selected gamma 
					if (std::string(argv[i]) == "gamma") {

						i++;

						// converting the string input to float 
						float gamma = std::stof(argv[i], nullptr);

						// gamma should be between 0.5 and 2.0
						if (gamma < 0.5 || gamma > 2.0) {

							std::cout << "Error: Gamma Value Out Of Bounds\n";
							std::cout << "[Gamma should be between 0.5 and 2.0]\n";
							spacing();

							system("PAUSE");

							exit(1);

						}
						else {

							FilterGamma f(gamma); // create FilterGamma object

							std::cout << "Applying gamma " << gamma << " filter...\n";
							spacing();

							*image = f << *image; //apply gamma filter 
						}
					}

					if (std::string(argv[i]) == "linear") {

						Color a, c; // 2 Colors objects are needed to apply the linear filter					

						std::cout << "Initializing a & c...\n";
						spacing();

						i++;

						a.r = std::stof(argv[i], nullptr);

						//cout << "A r = " << a.r << endl;

						i++;
						a.g = std::stof(argv[i], nullptr);

						//cout << "A g = " << a.g << endl;

						i++;
						a.b = std::stof(argv[i], nullptr);

						//cout << "A b = " << a.b << endl;

						i++;
						c.r = std::stof(argv[i], nullptr);

						//cout << "C r = " << c.r << endl;

						i++;
						c.g = std::stof(argv[i], nullptr);

						//cout << "C g = " << c.g << endl;

						i++;
						c.b = std::stof(argv[i], nullptr);

						//cout << "C b = " << c.b << endl;

						FilterLinear f(a, c); // create a FilterLinear object with the 2 Colors objects as input

						std::cout << "Applying linear ";
						std::cout << argv[i - 5] << " " << argv[i - 4] << " " << argv[i - 3] << " ";
						std::cout << argv[i - 2] << " " << argv[i - 1] << " " << argv[i - 0] << " ";
						std::cout << "filter...\n";
						spacing();
					
						*image = f << *image; // aplying filter linear
					}

				}
				else {
					i++; // if we dont find -f char we continue to find it
				}

		}
		} else {
			std::cerr << "Error: Loading Failed!\n"; // load of image has failed
			spacing();
		}
	}

	// Now we have to save the file with the name filtered_imagename.ppm

	std::string file_name = "filtered_" + (std::string)file; // we add the image name at the end of our file name

	std::cout << "Saving image...\n";
	spacing();

	// call save method to save file	
	if (image->save(file_name, "ppm")) {
		std::cout << "Saving Succeeded!\n";
		spacing();
	} else {
		std::cerr << "Error: Saving Failed!\n";
		spacing();
	}

	delete image; // freeing memory

	system("PAUSE");

	return 0;
}

//LEIVADAROS PARASKEVAS 3150090
//KOYLOYRIS GEORGIOS 3150080

#include "Filter.h"

void spacing() { std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - -\n"; }

int main(int argc, char* argv[]) {

	const char* file = nullptr;

	imaging::Image* imgObj = new imaging::Image(); // create an Image object 

	if (argc < 6) {

		spacing();
		std::cerr << "Error: Bad Input\n";
		spacing();

		system("PAUSE");
		exit(1);

	} else {

		// name of file
		file = argv[argc - 1]; 

		spacing();
		std::cout << "Loading image...\n";
		spacing();

		// loads the image using the method load of the Image object
		if (imgObj->load(file, "ppm")) {

			// prints the dimensions of the Image
			std::cout << "Loading Succeeded!\n";
			spacing();
			
			// prints the dimensions of the Image
			std::cout << "Image dimensions are: " << imgObj->getWidth() << " X " << imgObj->getHeight() << "\n";
			spacing();

			if (std::string(argv[1]) != "filter") {
				system("PAUSE");
				exit(1);
			}

			std::cout << "Reading image...\n";
			spacing();

			int i = 2; // tracks the elements of the input	

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

							std::cout << "Error: Gamma Is Out Of Bounds\n";
							std::cout << "Gamma should be in the range [0.5 and 2.0]\n";
							spacing();

							system("PAUSE");
							exit(1);

						}
						else {

							// Create FilterGamma object
							FilterGamma gammaObj(gamma);

							std::cout << "Applying gamma " << gamma << " filter...\n";
							spacing();

							// Apply gamma filter 
							*imgObj = gammaObj << *imgObj; 
						}
					}

					if (std::string(argv[i]) == "linear") {

						Color a, c; // 2 Colors objects are needed to apply the linear filter					

						std::cout << "Initializing a & c...\n";
						spacing();

						a.r = (float) std::atof(argv[i + 1]);
						a.g = (float) std::atof(argv[i + 2]);
						a.b = (float) std::atof(argv[i + 3]);

						c.r = (float) std::atof(argv[i + 4]);
						c.g = (float) std::atof(argv[i + 5]);
						c.b = (float) std::atof(argv[i + 6]);

						i = i + 6;

						// Create FilterLinear object
						FilterLinear linearObj(a, c); 

						std::cout << "Applying linear ";
						std::cout << argv[i - 5] << " " << argv[i - 4] << " " << argv[i - 3] << " ";
						std::cout << argv[i - 2] << " " << argv[i - 1] << " " << argv[i - 0] << " ";
						std::cout << "filter...\n";
						spacing();

						// Apply linear filter 
						*imgObj = linearObj << *imgObj;
					}
				}
				else {
					i++; // if we don't find -f char we continue to find it
				}
			}
		} else {
			std::cerr << "Error: Loading Failed!\n";
			spacing();
		}
	}

	std::string newfile = "filtered_" + (std::string)file; 

	std::cout << "Saving image...\n";
	spacing();

	// call save method to save file	
	if (imgObj->save(newfile, "ppm")) {
		std::cout << "Saving Succeeded!\n";
		spacing();
	} else {
		std::cerr << "Error: Saving Failed!\n";
		spacing();
	}

	imgObj->~Image(); // freeing memory

	system("PAUSE");
	return 0;
}
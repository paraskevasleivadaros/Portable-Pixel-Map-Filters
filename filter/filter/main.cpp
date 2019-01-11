//LEIVADAROS PARASKEVAS 3150090
//KOYLOYRIS GEORGIOS 3150080

#include "Filter.h"
#include "Debugging.h"

void spacing() { std::cout << "***********************************************\n"; }
#define TERMINATOR { std::cout << "Exiting Program...\n"; spacing(); system("PAUSE"); return 1; }

int main(int argc, char* argv[]) {

	const char* file = nullptr;

	imaging::Image* imgObj = new imaging::Image(); // create an Image object 

	if (argc < 6) {

		spacing();
		std::cerr << "Error: Bad Input\n";
		spacing();
		TERMINATOR

	} else {

		#ifdef PrintArgv
			PrintArgv(argc)
		#endif	

		// name of file
		file = argv[argc - 1]; 

		// loads the image using the method load of the Image object
		if (imgObj->load(file, "ppm")) {

			// prints the dimensions of the image
			spacing();
			std::cout << "Image dimensions are: " << imgObj->getWidth() << " X " << imgObj->getHeight() << "\n";
			spacing();

			#ifdef _DEBUG
				if (std::string(argv[1]) != "filterd") { TERMINATOR }
			#else
				if (std::string(argv[1]) != "filter") { TERMINATOR }
			#endif

			int i = 2; // tracks the elements of the input	

			// starting a while loop in order to read the whole input
			while (i < argc-1) {

				// if we find -f char we expect to execute a filter
				if (std::string(argv[i]) == "-f") {

					i++; // go to the next command argument

					if (std::string(argv[i]) == "gamma") { // user selected "gamma" 

						i++; // go to the next command argument

						// Initialize gamma
						#ifdef _DEBUG
							std::cout << "Initilazing gamma...\n";
						#endif	
						// converting the string input to float 
						float gamma = std::stof(argv[i], nullptr);

						// gamma should in the range [0.5, 2.0]
						if (gamma < 0.5 || gamma > 2.0) {

							std::cerr << "Error: Gamma Is Out Of Bounds\n";
							std::cerr << "Gamma should be in the range [0.5 and 2.0]\n";
							spacing();
							TERMINATOR
						}
						else {

							// Create FilterGamma object
							FilterGamma gammaObj(gamma);

							std::cout << "Applying gamma " << gamma << " filter...\n";
							spacing();

							// Apply gamma filter 
							*imgObj = gammaObj << *imgObj; 
						}
					} else if (std::string(argv[i]) == "linear") {	// user selected "linear" 			

						#ifdef _DEBUG
							std::cout << "Initilazing Color a, c...\n";
						#endif	
						// Initialize Color objects "a" and "c"
						Color a = Color((float)std::atof(argv[i + 1]), (float)std::atof(argv[i + 2]), (float)std::atof(argv[i + 3]));
						Color c = Color((float)std::atof(argv[i + 4]), (float)std::atof(argv[i + 5]), (float)std::atof(argv[i + 6]));

						// Create FilterLinear object
						FilterLinear linearObj(a, c); 

						std::cout << "Applying linear ";
						std::cout << argv[i + 1] << " " << argv[i + 2] << " " << argv[i + 3] << " ";
						std::cout << argv[i + 4] << " " << argv[i + 5] << " " << argv[i + 6] << " ";
						std::cout << "filter...\n";
						spacing();

						i+=6;

						// Apply linear filter 
						*imgObj = linearObj << *imgObj;

					} else {

						std::cerr << "Error: Invalid Filter\n";
						spacing();
						TERMINATOR
					}

				} else if (++i != argc) {
						
					std::cerr << "Error: Invalid Command\n";
					spacing();
					TERMINATOR
				}
				i++;
			}
		} else {
			std::cerr << "Error: Loading Failed!\n";
			spacing();
			TERMINATOR
		}
	}

	std::string newfile = "filtered_" + (std::string)file; 

	// call save method to save file	
	if (!imgObj->save(newfile, "ppm")) {
		std::cerr << "Error: Saving Failed!\n";
		spacing();
		TERMINATOR
	}

	imgObj->~Image(); // freeing memory

	system("PAUSE");
	return 0;
}
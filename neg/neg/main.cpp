//LEIVADAROS PARASKEVAS 3150090
//KOYLOYRIS GEORGIOS 3150080

#include <iostream>
#include <string>
#include "Filter.h"

using namespace imaging;
void line();

int main(int argc, char *argv[]) {

	std::string filename;

	if (argc < 3) {

		std::cerr << "Error: Wrong Input" << std::endl;
		std::cerr << "====" << std::endl;

	} else {

		filename = argv[argc - 1];
		line();

		Image *imgObj = new Image;

		if (imgObj->load(filename, "ppm")) {

			std::cout << "Image dimensions are: " << imgObj->getWidth() << " X " << imgObj->getHeight() << std::endl;
			line();

			int i = 1;
			while (i < argc-1) {
				if (argv[i] == std::string("filter")) {
					i++;
					if (argv[i] == std::string("-f")) {
						i++;
						if (argv[i] == std::string("linear")) {

							Color a, c;
							++i;
							a.r = (float)atof(argv[i]);
							a.g = (float)atof(argv[i + 1]);
							a.b = (float)atof(argv[i + 2]);
							i += 3;
							c.r = (float)atof(argv[i]);
							c.g = (float)atof(argv[i + 1]);
							c.b = (float)atof(argv[i + 2]);
						
							FilterLinear linear(a, c);
							*imgObj = linear << *imgObj;						
							i += 3;

						} else if (argv[i] == std::string("gamma")) {

							++i;
							float g = (float)atof(argv[i]);
							if (g >= 0.5 && g <= 2.0) {
								
								FilterGamma gamma(g);
								*imgObj = gamma << *imgObj;

							}else {

								line();
								std::cerr << "Error: g values must be lower than 2.0 and fewer than 0.5" << std::endl;
								line();

								system("pause");
								return 1;
							}
						} else {

							line();
							std::cerr << "Error: Wrong type of filter" << std::endl;
							line();

							system("pause");
							return 1;
						}

					} else { i++; }

				} else { i++; }
			}
		}
		else {
			std::cerr << "Error: Image Failed Loading\n";
		}	
	
		//adds the name of the new image
		std::string newfilename = "filtered_" + filename;

		if (!imgObj->save(newfilename, "ppm")) {

			std::cerr << "Error: Image Failed Saving\n";
			//return 1;
		}

	imgObj->~Image();//Destroys the pointer of image object		
	}
	
	system("PAUSE");
	return 0;
} 


void line() {
	std::cout << "*******************************************" << std::endl;
}
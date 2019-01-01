//LEIBADAROS PARASKEYAS 3150090
//KOYLOYRIS GEORGIOS 3150080

#include <iostream>
#include <string>
#include "Image.h"

using namespace imaging;

int main(int argc, char *argv[]) {
	
	std::string filename;

	if (argc == 2) { //the name of the file is not provided as an arguement
		
		std::cout << "File name of the image to load: ";
		std::cin >> filename;
		std::cout << "\n";

	} else if (argc == 3) { //the name of the file is provided as an arguement
		
		filename = argv[2];

	} else { //not an input of type "neg <filename>"
		
		std::cerr << "Error: We only take input of type \"neg <filename>\"" << std::endl;
	}

	Image *imgObj = new Image;
	
	if (imgObj->load(filename, "ppm")) {

		std::cout << "Image dimensions are: " << imgObj->getWidth() << " X " << imgObj->getHeight() << std::endl;
		std::cout << "\n";

		unsigned int i,j,w,h;

		w = imgObj->getWidth();
		h = imgObj->getHeight();

		//initializes the buffer of the new image
		for (i = 0; i < h; i++) {
			for (j = 0; j < w; j++) {
				Color rawData;
				rawData.r = 1.0F - imgObj->getPixel(i,j).r;
				rawData.g = 1.0F - imgObj->getPixel(i,j).g;
				rawData.b = 1.0F - imgObj->getPixel(i,j).b;
				imgObj->setPixel(i,j,rawData);
			}
		}
		
		//adds the name of the new image
		std::string newfilename = filename.substr(0, filename.length() - 4);
		newfilename.append("_neg.ppm");
		
		if (!imgObj->save(newfilename, "ppm")) {

			std::cerr << "Error: Negative of Input Image Failed Saving\n";
		}

	} else {

		std::cerr << "Error: Negative of Input Image Failed Loading\n";
	}

	imgObj->~Image();//Destroys the pointer of image object
	
	system("PAUSE");

	return 0;

} 
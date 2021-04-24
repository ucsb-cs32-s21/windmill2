/* ZJW simple C++ code to write out a PPM file representing shapes */

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "ppmR.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include "polygon.h"
#include "windmill.h"

using namespace std;

/*write out PPM data, using the defined implicit equation 
  interior points write a different color then exterior points */

void writeOut(ostream& out, ppmR& theWriter,  
				vector<shared_ptr<Windmill>> Windmills) {

	float res;
	color inC;
	color drawC;
	color background(52, 34, 56);
	bool inTrue = false;
	double curDepth = -1.0;

	//for every point in the 2D space
	for (int y=0; y < theWriter.height; y++) 
	{
		for (int x=0; x < theWriter.width; x++) 
		{
			inTrue = false;
			curDepth = -1;
			for (auto theWindmill : Windmills)
			{
				drawC = theWindmill->eval(x, y, background);
				if (drawC == background || theWindmill->getDepth() < curDepth) {
				//do nothing if background or windmill depth is small
				} 
				else {
				inTrue = true;
				inC = drawC;
				curDepth = theWindmill->getDepth();
				}
			}
			if (inTrue) {
					theWriter.writePixel(out, x, y, inC);
				}
			else {
				theWriter.writePixel(out, x, y, background);
			}
		}
		theWriter.writeNewLine(out);
	}
	
}


/*read command line arguments and write out new ascii file of given size */
int main(int argc, char *argv[]) {

	ofstream outFile;
	int sizeX, sizeY;
	vector<shared_ptr<Windmill>> Windmills;

	if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
		exit(0);
	}

	string outFilename;
	sizeX = stoi(argv[1]);
	sizeY = stoi(argv[2]);
	ppmR theWriter(sizeX, sizeY);

	auto invisible = make_shared<Windmill>(vec2(150,150), -30.0);
	auto Windmill2 = make_shared<Windmill>(vec2(150,150), 2.0);
	Windmill2->translate(vec2(100,100));
	Windmills.push_back(invisible);
	Windmills.push_back(Windmill2);

	outFile.open(argv[3]);
	if (outFile) {
		cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
		theWriter.writeHeader(outFile);
		writeOut(outFile, theWriter, Windmills);
	} else {
		cout << "Error cannot open outfile" << endl;
		exit(0);
	}
}

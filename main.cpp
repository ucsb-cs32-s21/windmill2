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
				vector<shared_ptr<ellipse>> IEs, 
				vector<shared_ptr<Rect> > Rs,
				vector<shared_ptr<Polygon> > Ps,
				Windmill theWindmill) {

	float res;
	color inC;
	color drawC;
	color background(52, 34, 56);
	bool inTrue = false;
	double curDepth = -1.0;

	//for every point in the 2D space
	for (int y=0; y < theWriter.height; y++) {
		for (int x =0; x < theWriter.width; x++) {

			inTrue = false;
			curDepth = -1;
			//iterate through all possible equations (note 'front' determined by order in vector)

			for (auto eq : IEs) {
				res = eq->eval(x, y);
				if (res < 0 && eq->getDepth() > curDepth) {
					inC = eq->getInC();
					inTrue = true;
					curDepth = eq->getDepth();
				}
			}

			for (auto rect: Rs) {
				if (rect->evalIn(x, y) && rect->getDepth() > curDepth){
					inC = rect->getInC();
					inTrue = true;
					curDepth = rect->getDepth();
				}
			}

			for (auto poly: Ps) {
				if (poly->eval(x, y) && poly->getDepth() > curDepth){
					inC = poly->getInC();
					inTrue = true;
					curDepth = poly->getDepth();
				}
			}

			drawC = theWindmill.eval(x, y, background);
			if (drawC == background) {
				//do nothing
			} else {
				inTrue = true;
				inC = drawC;
			}

			if (inTrue) {			
				theWriter.writePixel(out, x, y, inC);
			}
			else
				theWriter.writePixel(out, x, y, background);
		}
		theWriter.writeNewLine(out);
	}
}


/*read command line arguments and write out new ascii file of given size */
int main(int argc, char *argv[]) {

	ofstream outFile;
	int sizeX, sizeY;

	vector<shared_ptr<ellipse>> theEllipses;
	vector<shared_ptr<Rect>> theRects;
	vector<shared_ptr<Polygon>> thePolys;
	vector<color> niceC;
	niceC.push_back(color(117, 119, 186));
	niceC.push_back(color(45, 47, 135));
	niceC.push_back(color(174, 209, 238));
	niceC.push_back(color(239, 174, 115));
	niceC.push_back(color(186, 140, 117));

	if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
		exit(0);
	}

	string outFilename;
	sizeX = stoi(argv[1]);
	sizeY = stoi(argv[2]);
	ppmR theWriter(sizeX, sizeY);

	Windmill theWindmill(vec2(150,150), 0.0);

	/*
	Windmill temp(vec2(150,150), 1.0);
	vector<shared_ptr<Rect>> r = temp.getRects();
	vector<shared_ptr<ellipse>> e = temp.getEllipses();
	vector<shared_ptr<Polygon>> p = temp.getPolys();
	for (auto rectangle : r)
	{
		theRects.push_back(rectangle);
	}
	for (auto ellipse : e)
	{
		theEllipses.push_back(ellipse);
	}
	for (auto polygon : p)
	{
		thePolys.push_back(polygon);
	}
	*/

	outFile.open(argv[3]);
	if (outFile) {
		cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
		theWriter.writeHeader(outFile);
		writeOut(outFile, theWriter, theEllipses, theRects, thePolys, theWindmill);
	} else {
		cout << "Error cannot open outfile" << endl;
		exit(0);
	}
}

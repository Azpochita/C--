#include "Triangle.h"
#include "Colour.h"

int Triangle::TrianglesExisting;
int Triangle::TrianglesCreated;
double TRIANGLE_SIDE_TO_HEIGHT = 0.86666666;

void Triangle::TriangleDisplay(BMP& myImageValue, string theOutputFile)
 {
	int yHeight = 0;
	double offset = 0;
	int t1 = 0; 
	int t2 = 0;
    yHeight = static_cast<int> (sideLength * sqrt(3.0)/2.0 );
    if(yLocation < 0|| yLocation > pageLength ||
        yLocation + yHeight > pageLength)
    {
        cerr << "point may be located outside of plotting page\n"
            << endl;
        return;
    }
    
    if(xLocation < 0|| xLocation >= pageWidth || 
        xLocation + sideLength > pageWidth )
    {
        cerr << "point may be located outside of plotting page\n"
            << endl;
        return;
    }
    
    // each pixel within the Triangle must be Set to the correct colour
    // myImageValue(i,j) is pixel j in row i
    // each value in the Colour object is Set for each pixel in 
    // the Triangle
	yHeight = static_cast<int> (sideLength * sqrt(3.0)/2.0 );
    for(int j=yLocation; j<(yLocation+yHeight); j++)
    {
		offset = static_cast<double>(sideLength) / yHeight/ 2.0;
		t1 = static_cast<int>( ceil( (j-yLocation+1) * offset) );
		t2 = static_cast<int>( floor( (j-yLocation+1) * offset) );
        for (int i=0; i < sideLength; i++)
        {
			if( i < t1 || i > sideLength - t2) continue;
            myImageValue(i+xLocation,j)->Red = triangColour.GetRedNumber();
            myImageValue(i+xLocation,j)->Blue = triangColour.GetBlueNumber();
            myImageValue(i+xLocation,j)->Green = triangColour.GetGreenNumber();
            myImageValue(i+xLocation,j)->Alpha = triangColour.GetAlphaNumber();
        }
    }
    
    //write generated bitmap image to a file
    myImageValue.WriteToFile(theOutputFile.c_str());
}

void Triangle::TriangleDivide(Triangle* TriList)
{
	int halfSide;
	int yHalf;
	halfSide = sideLength / 2;
	// constant below is  = sqrt(3.0)/4 * sidelength
	yHalf = static_cast<int> (halfSide * TRIANGLE_SIDE_TO_HEIGHT);
	TriList[2] = Triangle(xLocation + halfSide / 2, yLocation + yHalf, halfSide, triangColour);
	TriList[1] = Triangle(xLocation + halfSide, yLocation, halfSide, triangColour);
	TriList[0] = Triangle(xLocation, yLocation, halfSide, triangColour);
}

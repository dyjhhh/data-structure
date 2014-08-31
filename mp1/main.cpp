#include "png.h"
#include <stdio.h>
#include <string>

using namespace std;

int main()
{
	//RGBAPixel pix = RGBAPixel(125, 125, 125);
	PNG input("in.png");
	PNG output(input.width(), input.height());

	//cout << input.width() - 1 << endl;
	
	for(unsigned int i = 0; i < input.width() ; i++)
	{
		for(unsigned int j = 0; j < input.height() ; j++)
		{
			int targetX = input.width() - 1 - i;
			int targetY = input.height() - 1 - j;
			//cout << "targetX: " << targetX << endl << "targetY: " << targetY << endl;
			
			output(targetX, targetY)->red = input(i, j)->red;
			output(targetX, targetY)->green = input(i, j)->green;
			output(targetX, targetY)->blue = input(i, j)->blue;
			output(targetX, targetY)->alpha = input(i, j)->alpha;
			
		}
	}

	output.writeToFile("out.png");
	
}

#include "rgbapixel.h"
#include <iostream>
using namespace std;

RGBAPixel::RGBAPixel()
{
	red = 255;
	green = 255;
	blue = 255;
	alpha = 255;
}

RGBAPixel::RGBAPixel(unsigned char red_temp, unsigned char green_temp, unsigned char blue_temp)
{
	red = red_temp;
	green = green_temp;
	blue = blue_temp;
	alpha = 255;
}

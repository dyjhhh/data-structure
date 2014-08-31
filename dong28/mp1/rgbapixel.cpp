#include "rgbapixel.h"
#include <string>

RGBAPixel::RGBAPixel()
{
	red = 255;
	green = 255;
	blue = 255;
	alpha = 255;
}

RGBAPixel::RGBAPixel(unsigned char redVal, unsigned char greenVal, unsigned char blueVal)
{
	red = redVal;
	green = greenVal;
	blue = blueVal;
	alpha = 255;
}

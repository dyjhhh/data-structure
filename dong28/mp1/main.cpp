#include "png.h"
#include "rgbapixel.h"
#include "png.h"

using namespace std;

int main()
{
  PNG oldImage;
  oldImage.readFromFile("in.png");
  size_t vertical = oldImage.height();
  size_t horizontal = oldImage.width();

	//have initialized newImage just so that the pixels are accessible

  PNG newImage;
  newImage.readFromFile("in.png");
	
  //we will flip the image horizontally and vertically to rotate it by 180 degrees
  for(size_t x = 0; x < oldImage.width() ; x++)
	{
		for(size_t y = 0; y < oldImage.height() ; y++)
		{
	newImage(horizontal-x-1, vertical-y-1)->red = oldImage(x,y)->red;
	newImage(horizontal-x-1, vertical-y-1)->green = oldImage(x,y)->green;
	  newImage(horizontal-x-1, vertical-y-1)->blue = oldImage(x,y)->blue;
	        }
        }
	newImage.writeToFile("out.png");
	
}

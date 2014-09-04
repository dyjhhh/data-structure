#include <cstdlib>
#include "png.h"

#include<iostream>  //added
using namespace std;  //added

// sets up the output image
PNG * setupOutput(int w, int h);


// Returns my favorite color
RGBAPixel * myFavoriteColor(int intensity);



int sketchify()
{
	// Load in.png
  PNG * original=new PNG; //added
        
	original->readFromFile("in.png");
	int width  = original->width();
	int height = original->height();
         
	// Create out.png
	PNG * output=new PNG;
	output -> resize (width, height);	

	// Loud our favorite color to color the outline
	RGBAPixel * myPixel = myFavoriteColor(192);

	// Go over the whole image, and if a pixel differs from that to its upper
	// left, color it my favorite color in the output
	for (int y = 1;  y < height; y++)
	{
		for (int x = 1;  x < width; x++)
		{
			// Calculate the pixel difference
			RGBAPixel * prev = (*original)(x-1, y-1);
			RGBAPixel * curr = (*original)(x  , y  );
			int diff = abs(curr->red   - prev->red  ) +
					   abs(curr->green - prev->green) +
					   abs(curr->blue  - prev->blue );

			// If the pixel is an edge pixel,
			// color the output pixel with my favorite color
			RGBAPixel * currOutPixel = (*output)(x,y);
			if (diff > 100)
			  //cout <<"line 47"<< endl                          
				*currOutPixel =* myPixel;
		}
	}
	
	// Save the output file
	output->writeToFile("out.png");

	// Clean up memory
	delete myPixel;
	delete output;
	delete original;
        myPixel = NULL;
        output = NULL;
        original = NULL;
	return 0;
	cout << "reached line 74" << endl;
}

// sets up the output image
PNG * setupOutput (int w, int h)
{
            PNG * image = new PNG (w, h);
            return image;

}


//returns my favorite color
RGBAPixel * myFavoriteColor (int intensity)
{RGBAPixel* color = new RGBAPixel;
  color -> red =0;
  color ->green = intensity/2;
  color ->blue = intensity;
  return color;
}

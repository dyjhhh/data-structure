
#include <iostream>
#include "png.h"
#include "rgbapixel.h"
using namespace std;

PNG rotate(PNG p);

int main() {


	PNG in("in.png");
	
	PNG out = rotate(in);

	out.writeToFile("out.png");

}
	


PNG rotate(PNG p) {
	int height = p.height();
	int width = p.width();
	PNG out = PNG(width, height);

	for (int x = 0; x < width; x++) {

		for (int y = 0; y < height; y++) {
			
			*out(x,y) = *p((width-1)-x, (height-1)-y);
			
		}

	}


	return out;

}

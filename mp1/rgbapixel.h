#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H

class RGBAPixel {
public:
	RGBAPixel();
	RGBAPixel(unsigned char redVal, unsigned char greenVal, unsigned char blueVal);
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;

};

#endif

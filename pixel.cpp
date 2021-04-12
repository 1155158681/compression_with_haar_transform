/*
	Pixel
	File containing the object "Pixel."
*/

#include "pixel.h"
#include <iostream>
using namespace std;

Pixel::Pixel() {
	red = green = blue = 0;
}

Pixel::Pixel(int red, int green, int blue) {
	setPixel(red, green, blue);
}
Pixel::Pixel(unsigned int rgb) {
	setPixel(rgb);
}

void Pixel::setPixel(int red, int green, int blue) {
	setRed(red);
	setGreen(green);
	setBlue(blue);
}

void Pixel::setPixel(unsigned int rgb) {
	// STORED AS (RRGGBBAA)h
	red = rgb >> 16;
	green = (rgb >> 8) - (red << 8);
	blue = rgb - (red << 16) - (green << 8);
}

void Pixel::setRed(int red) {
	if(!isPixelValue(red))
		cerr << "Error: Wrong Pixel Value.\n";
	else
		this->red = red;
}

void Pixel::setBlue(int blue) {
	if(!isPixelValue(blue))
		cerr << "Error: Wrong Pixel Value.\n";
	else
		this->blue = blue;
}

void Pixel::setGreen(int green) {
	if(!isPixelValue(green))
		cerr << "Error: Wrong Pixel Value.\n";
	else
		this->green = green;
}

int Pixel::getRed() const {
	return red;
}

int Pixel::getBlue() const {
	return blue;
}

int Pixel::getGreen() const {
	return green;
}

inline bool Pixel::isPixelValue(int val) {
	return val >= 0 && val < 256;
}

void Pixel::printPixelData() {
	cout << "Pixel Data\n";
	cout << "--------------------\n";
	cout << "R: \t" << red << endl;
	cout << "G: \t" << green << endl;
	cout << "B: \t" << blue << endl;
	cout << "--------------------\n";
}

int Pixel::getRGB() {
	return (red << 16) + (green << 8) + (blue);
}

bool operator==(const Pixel& lhs, const Pixel& rhs) {
	return lhs.getRed() == rhs.getRed() 
		&& lhs.getBlue() == rhs.getBlue() 
		&& lhs.getGreen() == rhs.getGreen();
}

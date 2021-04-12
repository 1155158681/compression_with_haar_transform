/*
	BitmapHandler
	This file is dedicated for creating an interface to read
	bitmap files, with the defined BitmapHandler class for the
	handling agent.
*/

#ifndef BITMAPHANDLER_H
#define BITMAPHANDLER_H

#include <iostream>
#include <fstream>
#include "pixel.h"


class BitmapHandler {
	public:
		BitmapHandler(char const* fileName);
		BitmapHandler();
		~BitmapHandler();
		bool isError();
		Pixel& pixel(int row, int col);
		int getHeight();
		int getWidth();
		
		void saveBMP();
	
	private:
		char const* fileName;
		int height, width, bitPerPixel;
		int byteWidth;
		Pixel* pixels;
		bool modeError;
		
		void parseBMP();
};

#endif

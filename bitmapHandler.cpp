/*
	BitmapHandler
	This file is dedicated for creating an interface for reading
	bitmap files, with the defined BitmapHandler class for the
	handling agent.
*/

#include "bitmapHandler.h"
#include "byteHandler.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

BitmapHandler::BitmapHandler(char const* fileName) {
	modeError = false;
	height = width = bitPerPixel = byteWidth = 0;
	
	this->fileName = fileName;
	
	fstream fs;
	fs.open(fileName, fstream::in | fstream::out | fstream::binary);
	if(fs.fail()) {
		cerr << "File at: [" << fileName << "] does not exists.\n";
		modeError = true;
		return;
	}
	
	clog << "Successfully found file at [" << fileName << "].\n";
	fs.close();
	
	try {
		parseBMP();
		clog << "Initialized BitmapReader...\n";
	} catch (char const* e) {
		cerr << "Error: " << e << endl;
	}
}

BitmapHandler::BitmapHandler() {
	modeError = false;
	height = width = bitPerPixel = 0;
}

BitmapHandler::~BitmapHandler() {
	delete(pixels);
}

int BitmapHandler::getHeight() {
	return height;
}

int BitmapHandler::getWidth() {
	return width;
}

void BitmapHandler::parseBMP() {
	fstream fs;
	fs.open(fileName, fstream::in | fstream::out | fstream::binary);
	if(fs.fail())
		throw "parseBMP() failed: Missing target file.";
	try {
		unsigned char header[54];
		fs.read((char*) &header[0], 54);
		
		// Read data from Windows BITMAPINFOHEADER
		width = byte_to_int(header, 21, 18);
		height = byte_to_int(header, 25, 22);
		bitPerPixel = byte_to_int(header, 29, 28);
		
		clog << "Bitmap Data\n";
		clog << "--------------------\n";
		clog << "Width:  \t" << width << endl;
		clog << "Height: \t" << height << endl;
		clog << "Bit/Px: \t" << bitPerPixel << endl;
		clog << "--------------------\n";
		
		if(bitPerPixel != 24)
			throw "Bit/Px another than 24 is not supported.\n";
		
		pixels = new Pixel[abs(height)*width];
		
		// with the assumption of BMPINFOHEADER
		// ie. start of pixelarray is at 54 bytes
		
		// calculating byteWidth
		byteWidth = width * bitPerPixel / 8;
		byteWidth += (4 - bitPerPixel % 4) % 4;	// padding
		
		fs.seekg(54, ios::beg);
		
		// reading row by row
		for(int i = 0; i < height; i++) {
			unsigned char row[byteWidth];
			fs.read((char*) &row[0], byteWidth);
			for(int j = 0; j < width; j++) {
				// reading pixels
				int cursor = i * width + j;
				pixels[cursor].setPixel(byte_to_uint(row, j * 3 + 2,  j * 3));
			}
		}
		
	} catch (char const* e) {
		cerr << "Error: " << e << endl;
		modeError = true;
		throw "Error in Parsing BMP...";
	} catch (...) {
		throw "Unexpected Error in Parsing BMP...";
	}
}

Pixel& BitmapHandler::pixel(int row, int col) {
	if(modeError)
		throw "Error in BitmapReader, cannot access pixels.";
	
	if(height < 0)
		return pixels[row * width + col];
	else
		return pixels[(abs(height) - row - 1) * width + col];
}

bool BitmapHandler::isError() {
	return modeError;
}

void BitmapHandler::saveBMP() {
	if(modeError)
		throw "Error in BitmapReader, cannot save bitmap file.";
	
	fstream fs;
	fs.open(fileName, ios::in | ios::out | ios::binary);
	// writing row by row
	for(int i = 0; i < height; i++) {
		unsigned char row[byteWidth] = {0};
		for(int j = 0; j < width; j++) {
			row[3 * j] = int_to_byte(pixels[i * width + j].getBlue());
			row[3 * j + 1] = int_to_byte(pixels[i * width + j].getGreen());
			row[3 * j + 2] = int_to_byte(pixels[i * width + j].getRed());
		}
		fs.seekp(54 + i * byteWidth);
		fs.write((char*) &row[0], byteWidth);
	}
}

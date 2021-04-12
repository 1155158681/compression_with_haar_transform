/*
	iHaarCompress
	This file serves as the interface between haarTransform,
	bitmapReader and huffmanCoding.
*/

#include "iHaarCompress.h"
#include "bitmapHandler.h"
#include "haarTransform.h"

iHaarCompress::iHaarCompress(BitmapHandler* bmpHandler) {
	this->bmpHandler = bmpHandler;
	red_matrix = new int*[getImageHeight()];	
	blue_matrix = new int*[getImageHeight()];
	green_matrix = new int*[getImageHeight()];
	
	for(int i = 0; i < getImageHeight(); i++) {
		red_matrix[i] = new int[getImageWidth()];
		blue_matrix[i] = new int[getImageWidth()];
		green_matrix[i] = new int[getImageWidth()];
		for(int j = 0; j < getImageWidth(); j++) {
			Pixel& px = bmpHandler->pixel(i, j);
			red_matrix[i][j] = px.getRed();
			blue_matrix[i][j] = px.getBlue();
			green_matrix[i][j] = px.getGreen();
		}
	}
}

iHaarCompress::~iHaarCompress() {
	for(int i = 0; i < getImageHeight(); i++) {
		delete(red_matrix[i]);
		delete(blue_matrix[i]);
		delete(green_matrix[i]);
	}
	delete(red_matrix);
	delete(blue_matrix);
	delete(green_matrix);
}

int iHaarCompress::getImageHeight() {
	return bmpHandler->getHeight();
}

int iHaarCompress::getImageWidth() {
	return bmpHandler->getWidth();
}

void iHaarCompress::updatePixel() {
	for(int i = 0; i < getImageHeight(); i++) {
		for(int j = 0; j < getImageWidth(); j++) {
			bmpHandler->pixel(i, j).setPixel(
				red_matrix[i][j],
				green_matrix[i][j],
				blue_matrix[i][j]
			);
		}
	}
}

void iHaarCompress::exportCompressedBitmap(int maxIteration) {
	#define process1(x) 	mHaarRecursiveTransform((x), getImageHeight(), getImageWidth(), maxIteration); \
						mHaarNormalization((x), getImageHeight(), getImageWidth(), maxIteration);
	
	process1(red_matrix);
	process1(green_matrix);
	process1(blue_matrix);
	
	updatePixel();
	bmpHandler->saveBMP();
	
	#undef process1
}

void iHaarCompress::exportCompressedBinary(int maxIteration) {
	
}

void iHaarCompress::exportCompressedCodedBinary(int maxIteration) {
	
}

void iHaarCompress::exportDecompressedBitmap(int maxIteration) {
	#define process2(x) mHaarDenormalization((x), getImageHeight(), getImageWidth(), maxIteration); \
						mReverseHaarRecursiveTransform((x), getImageHeight(), getImageWidth(), maxIteration);
	
	process2(red_matrix);
	process2(green_matrix);
	process2(blue_matrix);
	
	updatePixel();
	bmpHandler->saveBMP();
	
	#undef process2
}

void iHaarCompress::exportDecompressedBinary(int maxIteration) {
	
}

void iHaarCompress::exportDecompressedCodedBinary(int maxIteration) {
	
}

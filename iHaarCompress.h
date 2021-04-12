/*
	iHaarCompress
	This file serves as the interface between haarTransform,
	bitmapReader and huffmanCoding.
*/

#ifndef IHAARCOMPRESS_H
#define IHAARCOMPRESS_H

#include "bitmapHandler.h"
#include "haarTransform.h"

class iHaarCompress {
	public:
		iHaarCompress(BitmapHandler* bmpHandler);
		~iHaarCompress();
		int getImageHeight();
		int getImageWidth();
		
		void updatePixel();
		void exportCompressedBitmap(int maxIteration);
		void exportCompressedBinary(int maxIteration);
		void exportCompressedCodedBinary(int maxIteration);	// with Huffman Coding
		
		void exportDecompressedBitmap(int maxIteration);
		void exportDecompressedBinary(int maxIteration);
		void exportDecompressedCodedBinary(int maxIteration);
		
	private:
		BitmapHandler* bmpHandler;
		
		int** red_matrix;
		int** blue_matrix;
		int** green_matrix;
};

#endif

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
//		iHaarCompress(BitmapHandler* bmpHandler);
		iHaarCompress(char const* fileName);
		~iHaarCompress();
		int getImageHeight();
		int getImageWidth();
		
		void updatePixel();
		void exportCompressedBitmap(int maxIteration);
		void exportBinary(char const* fileName = "outputBinary.bin");
		void exportCompressedBinary(int maxIteration, char const* fileName = "outputcompressedBinary.bin");
		void exportCompressedCodedBinary(int maxIteration, char const* fileName = "outputCompressedCodedBinary.bin");
		// with Huffman Coding
		
		void exportDecompressedBitmap(int maxIteration);
		void exportDecompressedBinary(int maxIteration, char const* fileName = "outputDecompressedBitmap.bin");
		void exportDecompressedCodedBinary(int maxIteration, char const* fileName = "outputDecompressedCodedBinary.bin");
		
	private:
		BitmapHandler bmpHandler;
		char const* fileName;
		int height, width;
		
		void initPixelMatrix();
		
		int** red_matrix;
		int** blue_matrix;
		int** green_matrix;
};

#endif

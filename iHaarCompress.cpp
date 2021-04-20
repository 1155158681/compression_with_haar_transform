/*
	iHaarCompress
	This file serves as the interface between haarTransform,
	bitmapReader and huffmanCoding.
*/

#include "iHaarCompress.h"
#include "bitmapHandler.h"
#include "haarTransform.h"
#include "huffmanCoding.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define process1(x, y) mHaarRecursiveTransform((x), height, width, y); \
						mHaarNormalization((x), height, width, y);
#define process2(x, y) mHaarDenormalization((x), height, width, y); \
					mReverseHaarRecursiveTransform((x), height, width, y);

using namespace std;

iHaarCompress::iHaarCompress(char const* fileName) : bmpHandler(fileName) {
	
	height = width = 0;
	
	this->fileName = fileName;
	height = bmpHandler.getHeight();
	width = bmpHandler.getWidth();
	
	clog << "Initializing Bitmap of size [" << height << ", " << width << "] into iHaarCompress...\n";
	
	
	initPixelMatrix();
	clog << "Initialized iHaarCompress...\n";
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
	return height;
}

int iHaarCompress::getImageWidth() {
	return width;
}

void iHaarCompress::updatePixel() {
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			bmpHandler.pixel(i, j).setPixel(
				red_matrix[i][j],
				green_matrix[i][j],
				blue_matrix[i][j]
			);
		}
	}
}

void iHaarCompress::exportCompressedBitmap(int maxIteration) {
	process1(red_matrix, maxIteration);
	process1(green_matrix, maxIteration);
	process1(blue_matrix, maxIteration);
	
	updatePixel();
	bmpHandler.saveBMP();
	
}

void iHaarCompress::exportBinary(char const* fileName) {
	ofstream ofs(fileName, ios::binary);
	if(ofs.fail())
		throw "Error in exportCompressBinary(int, char const*).";
	
	// Binary are stored as follows:
	// 1. Header - (only has HEIGHT and WIDTH)
	// 2. PixelArray - (Top to bottom, left to right, no padding)
	
	ofs.write((char*) &height, sizeof(height));
	ofs.write((char*) &width, sizeof(width));
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			ofs.write((char*) &red_matrix[i][j], sizeof(red_matrix[i][j]));
			ofs.write((char*) &green_matrix[i][j], sizeof(green_matrix[i][j]));
			ofs.write((char*) &blue_matrix[i][j], sizeof(blue_matrix[i][j]));
		}
	}
	
	ofs.close();
}

void iHaarCompress::exportCompressedBinary(int maxIteration, char const* fileName) {
	process1(red_matrix, maxIteration);
	process1(green_matrix, maxIteration);
	process1(blue_matrix, maxIteration);
	
	exportBinary(fileName);
}

void iHaarCompress::exportCompressedCodedBinary(int maxIteration, char const* fileName) {
	exportCompressedBinary(maxIteration, fileName);
	// FIRST 2 BYTES ARE HEADERS
	// Get byte stream of the rest of folder
	
	ifstream ifs(fileName, ios::binary);
	ifs.seekg(0, ios::end);
	int fileSize = ifs.tellg();
	fileSize -= 2;	// header
	
	clog << "fileSize: " << fileSize << endl;
	
	unsigned char *fileByteStream= new unsigned char[fileSize];
	ifs.seekg(2);
	ifs.read((char*) &fileByteStream[0], fileSize);
	ifs.close();
	
	c173::Huffman_Coding_uchar huffman(fileByteStream, fileSize);
	vector<unsigned char> huffmanTree = huffman.make_tree_stream();
	
	
	ofstream ofs(fileName, ios::binary | ios::trunc);
	
	// Write header (height, width)
	ofs.seekp(ios::beg);
	ofs.write((char*) &height, sizeof(height));
	ofs.write((char*) &width, sizeof(width));
	
	// Write huffman tree into file
	for(int i = 0; i < huffmanTree.size(); i++)
		ofs.write((char*) &huffmanTree[i], 1);
	
	// Evaluate coded stream and write to file
	unsigned char buffer = 0;
	int buffer_cursor = 0;
	for(int i = 0; i < fileSize; i++) {
		string code = huffman.encode(fileByteStream[i]);
		for(int j = 0; j < code.length(); j++) {
			if(code[j] == '1')
				buffer |= (1 << (7 - buffer_cursor));
			buffer_cursor ++;
			
			if(buffer_cursor == 8) {
				// Flush buffer
				ofs.write((char*) &buffer, 1);
				buffer = 0;
				buffer_cursor = 0;
			}
		}
	}
	// Flush remaining buffer
	ofs.write((char*) &buffer, 1);
	
	// Finalizing
	ofs.close();
}

void iHaarCompress::exportDecompressedBitmap(int maxIteration) {
	process2(red_matrix, maxIteration);
	process2(green_matrix, maxIteration);
	process2(blue_matrix, maxIteration);
	
	updatePixel();
	bmpHandler.saveBMP();
	
}

void iHaarCompress::exportDecompressedBinary(int maxIteration, char const* fileName) {
	
}

void iHaarCompress::exportDecompressedCodedBinary(int maxIteration, char const* fileName) {

}

void iHaarCompress::initPixelMatrix() {
	red_matrix = new int*[height];	
	blue_matrix = new int*[height];
	green_matrix = new int*[height];
	
	for(int i = 0; i < height; i++) {
		red_matrix[i] = new int[width];
		blue_matrix[i] = new int[width];
		green_matrix[i] = new int[width];
		for(int j = 0; j < width; j++) {
			Pixel& px = bmpHandler.pixel(i, j);
			red_matrix[i][j] = px.getRed();
			blue_matrix[i][j] = px.getBlue();
			green_matrix[i][j] = px.getGreen();
		}
	}
}

#undef process1
#undef process2

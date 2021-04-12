#include <fstream>
#include <iostream>

#include "bitmapHandler.h"
#include "haarTransform.h"
#include "byteHandler.h"
#include "iHaarCompress.h"

using namespace std;

int main() {
	
	
//	try {
//		// Test area
//		char const* fileName = "source.bmp";
//		BitmapHandler bmpHandler = BitmapHandler(fileName);
//		if(bmpHandler.isError())
//			cout << "Error in bmpHandler\n";
//		else {
//			
////			while(true) {
////				int row, col;
////				cout << "Which pixel would you like to know about?\n";
////				cout << "Input: [row] [col] (0 based)\n";
////				cin >> row >> col;
////				bmpHandler.pixel(row, col).printPixelData();	
////			}
//			
//			Pixel* pixels = new Pixel[1000];
//			int len = 1;
//			
//			pixels[0] = bmpHandler.pixel(0,0);
//			for(int i = 0; i < bmpHandler.getHeight(); i++) {
//				for(int j = 0; j < bmpHandler.getWidth(); j++) {
//					Pixel pixel = bmpHandler.pixel(i,j);
//					bool flag_duplicate = false;
//					for(int k = 0; k < len; k++) {
//						flag_duplicate |= (pixel == pixels[k]);
//					}
//					if(!flag_duplicate) {
//						pixels[len] = pixel;
//						len++;
//					}
//				}
//			}
//			
//			for(int i = 0; i < len; i++) {
//				pixels[i].printPixelData();
//			}
//		}
//
//	} catch (char const* e) {
//		cout << "Error: " << e << endl;
//	}
	
	
	{
		int r = 4, c = 4;
	
	//	int matrix[r][c] = {
	//		{148, 128, 85, 168, 50, 250, 109, 15}, 
	//		{130, 64, 197, 97, 173, 161, 103, 98}, 
	//		{206, 55, 195, 155, 82, 30, 15, 83},
	//		{63, 209, 227, 160, 154, 61, 128, 93}, 
	//		{211, 32, 192, 99, 137, 126, 170, 173}, 
	//		{107, 12, 192, 60, 215, 184, 187, 96}, 
	//		{45, 167, 109, 16, 64, 163, 147, 146}, 
	//		{117, 165, 29, 131, 149, 67, 91, 153}, 
	//	};
		
		int matrix[r][c] = {
			{148, 128, 85, 168}, 
			{130, 64, 197, 97}, 
			{206, 55, 195, 155},
			{63, 209, 227, 160}
		};
		
		int* arr[c];
		for(int i = 0; i < c; i++) {
			arr[i] = matrix[i];
		}
		
		cout << "1A ---------------------\n";
		
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c; j++) {
				cout << matrix[i][j] << "\t";
			}
			cout << "\n";
		}
		
		cout << "1B ---------------------\n";
		
		mHaarRecursiveTransform(arr, r, c, 1);
		// mHaarNormalization(arr, r, c, 1);
		
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c; j++) {
				cout << matrix[i][j] << "\t";
			}
			cout << "\n";
		}
		
		cout << "2A ---------------------\n";
		
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c; j++) {
				cout << matrix[i][j] << "\t";
			}
			cout << "\n";
		}
		
		cout << "2B ---------------------\n";
		
		// mHaarDenormalization(arr, r, c, 2);
		mReverseHaarRecursiveTransform(arr, r, c, 1);
		
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c; j++) {
				cout << matrix[i][j] << "\t";
			}
			cout << "\n";
		}
	}
	

		
		
//	char const* fileName = "image/source.bmp";
//	BitmapHandler bmpHandler = BitmapHandler(fileName);
//	iHaarCompress iComp = iHaarCompress(&bmpHandler);
//	iComp.exportCompressedBitmap(1);
	
	
	/* last
	{
		cout << "ImageCompression and Decompression\n";
		cout << "\twith \"Haar Transform\" and \"Huffman Coding\"\n";
		cout << endl;
		cout << "1. Please rename the target image to \"source.bmp\" and put in the same folder as the executable.\n";
		cout << "2. Note that the file should be *uncompressed* for compression and vice versa.\n";
		cout << "3. Make sure the file has color depth of 24 bits encoded in RGB.
		
		system("pause");
		
		// Locate Target Image
		
		
		// Menu for action
		// 1. Compression
		// 2. Decompression
		// 3. Compression and Decompression
		
	}
	*/
	
	return 0;
	
}

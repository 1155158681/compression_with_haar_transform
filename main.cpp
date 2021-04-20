#include <fstream>
#include <iostream>

#include "bitmapHandler.h"
#include "haarTransform.h"
#include "byteHandler.h"
#include "iHaarCompress.h"
#include "huffmanCompress.h"

using namespace std;

int main() {
	
	{
		int r = 8, c = 8;
	
		int matrix[r][c] = {
			{148, 128, 85, 168, 50, 250, 109, 15}, 
			{130, 64, 197, 97, 173, 161, 103, 98}, 
			{206, 55, 195, 155, 82, 30, 15, 83},
			{63, 209, 227, 160, 154, 61, 128, 93}, 
			{211, 32, 192, 99, 137, 126, 170, 173}, 
			{107, 12, 192, 60, 215, 184, 187, 96}, 
			{45, 167, 109, 16, 64, 163, 147, 146}, 
			{117, 165, 29, 131, 149, 67, 91, 153}, 
		};
		
//		int matrix[r][c] = {
//			{148, 128, 85, 168}, 
//			{130, 64, 197, 97}, 
//			{206, 55, 195, 155},
//			{63, 209, 227, 160}
//		};
		
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
		
//		mHaarRecursiveTransform(arr, r, c, 1);
		mHaarTransform(arr, r, c);
//		mHaarNormalization(arr, r, c, 1);
		
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
		
//		mReverseHaarRecursiveTransform(arr, r, c, 1);
		mReverseHaarTransform(arr, r, c);
//		mHaarNormalization(arr, r, c, 1);
		
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c; j++) {
				cout << matrix[i][j] << "\t";
			}
			cout << "\n";
		}
	}
	

	int n;
	cin >> n;
		
	char const* fileName = "image/source.bmp";
	
	iHaarCompress iComp = iHaarCompress(fileName);
	
	iComp.exportCompressedBitmap(3);
	iComp.exportDecompressedBitmap(3);
	
//	iComp.exportBinary("image/original.bin");
//	iComp.exportCompressedCodedBinary(n, "image/coded.bin");
//	
	/* last
	{
		cout << "ImageCompression and Decompression\n";
		cout << "\twith \"Haar Transform\" and \"Huffman Coding\"\n";
		cout << endl;
		cout << "1. Please rename the target image to \"source.bmp\" and put in the same folder as the executable.\n";
		cout << "2. Note that the file should be *uncompressed* for compression and vice versa.\n";
		cout << "3. Make sure the file has color depth of 24 bits encoded in RGB.\n";
		cout << "(You can use MS Paint for quick conversion.)\n";
		cout << endl;
		cout << "Press any keys to continue...\n";
		
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

/*
	HuffmanCompress
	The file contains algorithm for encoding binary data
	via Huffman Coding process.
*/

#include "huffmanCompress.h"
#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>

using namespace std;

void huffmanCompress(char const* fileName, int headerBuffer) {
	ifstream ifs(fileName, ios::binary);
	
	if(ifs.fail())
		throw "Error in huffmanCompress(char const*, int).";
	
	int fileSize;
	ifs.seekg(0, ios::end);
	fileSize = ifs.tellg();
	
	unsigned char* file = new unsigned char[fileSize];
	ifs.seekg(ios::beg);
	ifs.read((char*) &file[0], fileSize);
	
	clog << "huffmanCompress(char const*, int): Reading file with " << fileSize << " characters.\n";
	
	unsigned char bucket[256] = {0};
	int bucketCount[256] = {0};
	int cursor = 0;
	
	// bucket
	for(int i = headerBuffer; i < fileSize; i++) {
		bool found = false;
		
		for(int j = 0; j < cursor; j++) {
			if(bucket[j] == file[i]) {
				bucketCount[j]++;
				found = true;
				break;
			}
		}
		
		if(!found) {
//			clog << "New element found: " << (int)file[i] << endl;
			bucket[cursor] = file[i];
			bucketCount[cursor] = 1;
			cursor++;
		}
	}
	
	// descending sort (insertion sort)
	for(int i = 0; i < cursor; i++) {
		int maxCursor = i;
		
		for(int j = i + 1; j < cursor; j++) {
			if(bucketCount[maxCursor] < bucketCount[j])
				maxCursor = j;
		}
		
		// swapping
		unsigned char tmp = bucket[maxCursor];
		int tmpCount = bucketCount[maxCursor];
		
		bucket[maxCursor] = bucket[i];
		bucketCount[maxCursor] = bucketCount[i];
		
		bucket[i] = tmp;
		bucketCount[i] = tmpCount;
	}
	
	// constructing huffman tree
	
	
	clog << "Encoding [" << fileName << "] with Huffman Tree:" << endl;
	clog << "--------------------\n";
	for(int i = 0; i < cursor; i++) {
		clog << (int) bucket[i] << "\t";
		for(int j = 0; j < i; j++)
			clog << 1;
		clog << 0 << endl;
	}
	clog << "--------------------\n";
	
	
	ifs.close();
	
	// coding
	ofstream ofs(fileName, ios::trunc | ios::binary);
	
	if(ofs.fail())
		throw "Error in huffmanCompress(char const*, int).";
	
	// insert header
	for(int i = 0; i < headerBuffer; i++)
		ofs.write((char*) &file[i], sizeof(file[i]));
	
	// write in terms of buffer (min write size = 1 byte)
	unsigned char buffer = 0;
	int bufferSize = 0;
	
	for(int i = headerBuffer; i < fileSize; i++) {
		for(int j = 0; j < cursor; j++) {
			if(file[i] == bucket[j]) {
				// the huffman code should be (1){j - 1} 0
				for(int k = 0; k < j; k++) {
					// appending 1
					buffer |= 1;
					bufferSize++;
					// check if buffer is full
					if(bufferSize == sizeof(unsigned char) * 8) {
						// clear buffer
						ofs.write((char*) &buffer, sizeof(unsigned char));
						buffer = 0;
						bufferSize = 0;
					} else {
						// push buffer
						buffer <<= 1;
					}
				}
				
				// adding the final 0 in huffman code
				bufferSize++;
				if(bufferSize == sizeof(unsigned char) * 8){ 
					// clear buffer
					ofs.write((char*) &buffer, sizeof(unsigned char));
					buffer = 0; 
					bufferSize = 0;
				} else {
					// push buffer
					buffer <<= 1;
				}

				break;
			}
		}
	}
	
	// clear buffer if non-empty
	if(bufferSize > 0) {
		buffer <<= (sizeof(unsigned int) - bufferSize - 1);
		ofs.write((char*) &buffer, sizeof(unsigned char));
	}
	
	// finalizing
	delete file;
	ofs.close();
}

void huffmanDecompress(char const* fileName, int hearBuffer) {
	ifstream ifs(fileName, ios::binary);
	
	if(ifs.fail())
		throw "Error in huffmanDecompress(char const*, int).";
	
	int fileSize;
	ifs.seekg(0, ios::end);
	fileSize = ifs.tellg();
	
	unsigned char* file = new unsigned char[fileSize];
	ifs.seekg(ios::beg);
	ifs.read((char*) &file[0], fileSize);
	
	clog << "huffmanDecompress(char const*, int): Reading file with " << fileSize << " characters.\n";
	
	
}

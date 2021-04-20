#include "huffmanCoding.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void print_binary(unsigned char c) {
    for(int i = 0; i < 8; i++) {
        int mask = 1 << (7 - i);
        cout << ((c & mask) >> (7 - i));
    }
}

int main() {
//    const int SIZE = 8;
//    unsigned char data[SIZE] = {123, 23, 12, 242, 3, 3, 32, 23};
//
//    for(int i = 0; i < SIZE; i++) {
//        print_binary(data[i]);
//    }
//    
//    cout << endl;
//	
//	c173::Huffman_Coding_uchar huff(data, SIZE);
//    
//    vector<unsigned char> tree_stream;
//    tree_stream = huff.make_tree_stream();
//	
//	unsigned char arr[tree_stream.size()];
//	for(int i = 0; i < tree_stream.size(); i++) {
//		arr[i] = tree_stream[i];
//		print_binary(arr[i]);
//		cout << " ";
//	}
//	
//	cout << endl;
//	
//    for(int i = 0; i < SIZE; i++) {
//    	cout << huff.encode(data[i]) << " - \t" << (int) huff.decode(huff.encode(data[i])) << "\t ( ";
//		print_binary((int) huff.decode(huff.encode(data[i]))); 
//		cout << " )" << endl;
//    }
//    
//    // make stream
//    unsigned char compressed_stream[SIZE] = {0};
//    int compressed_stream_cursor = 0;
//    unsigned char buffer = 0;
//    int buffer_cursor = 0;
//	for(int i = 0; i < SIZE; i++) {
//		string code = huff.encode(data[i]);
//		for(int j = 0; j < code.length(); j++) {
//			if(code[j] == '1')
//				buffer |= (1 << (7 - buffer_cursor));
//			buffer_cursor ++;
//			if(buffer_cursor == 8) {
//				// flush
//				clog << "flush\n";
//				compressed_stream[compressed_stream_cursor] = buffer;
//				buffer = 0;
//				buffer_cursor = 0;
//				compressed_stream_cursor++;
//			}
//		}
//	}
//	// flush rest
//	compressed_stream[compressed_stream_cursor] = buffer;
//	buffer = 0;
//	buffer_cursor = 0;
//	compressed_stream_cursor++;
//	
//	for(int i = 0; i < SIZE; i++) {
//		print_binary(compressed_stream[i]);
//	}
//	
//	cout << "\nDECODING NOW!!\n";
//	
//	unsigned char decode_stream[SIZE] = {0};
//	huff.decode_stream(compressed_stream, SIZE, decode_stream, SIZE);
//	
//	for(int i = 0; i < SIZE; i++) {
//		cout << i << "\t";
//		print_binary(decode_stream[i]);
//		cout << endl;
//	}


	ifstream ifs("coded.bin", ios::binary);
	if(ifs.fail())
		cout << "failed\n";
	ifs.seekg(0, ios::end);
	cout << ifs.tellg();
	
	ifs.close();
	
	return 0;
}

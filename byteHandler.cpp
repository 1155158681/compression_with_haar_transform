/*
	ByteHandler
	This file is dedicated for interrepting byte data
	and convert to desired data type.
*/

#include "byteHandler.h"
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

unsigned int byte_to_uint(unsigned char* arr, int from, int to) {
	unsigned int result = 0;
	int byte_shift = 8 * min(abs(to - from), 3);
	int increment = (to - from) / abs(to - from);
	for(int i = from; i != to + increment; i += increment) {
		result += ((unsigned int) arr[i]) << byte_shift;
		byte_shift -= 8;
	}
	
	return result;
}

int byte_to_int(unsigned char* arr, int from, int to) {
	int result = (int) byte_to_uint(arr, from, to);
	return result;
}

// only extracts the last byte
unsigned char int_to_byte(int val) {
	val -= ((val >> 8) << 8);
	return (unsigned char) val;
}

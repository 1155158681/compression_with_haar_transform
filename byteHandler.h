/*
	ByteHandler
	This file is dedicated for interrepting byte data
	and convert to desired data type.
*/

#ifndef BYTEHANDLER_H
#define BYTEHANDLER_H

unsigned int byte_to_uint(unsigned char* arr, int from, int to);
int byte_to_int(unsigned char* arr, int from, int to);
unsigned char int_to_byte(int val);

#endif

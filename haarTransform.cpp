/*
	HaarTransform
	This file contains the modified transformation based 
	on Haar tranform and the reverse transformation.
*/

#include "haarTransform.h"
#include <iostream>
using namespace std;

void mHaarTransform(int** matrix, int length, int width) {
	if(length % 2 + width % 2 > 0)
		throw "Error in mHaarTransform: length or width not divisible by 2.";
	
	// row operation
	for(int i = 0; i < length; i++) {
		// average and difference
		for(int j = 0; j < width; j++) {
			if(j % 2 == 0)
				matrix[i][j] = matrix[i][j] + matrix[i][j+1];
			else
				matrix[i][j] = matrix[i][j-1] - 2 * matrix[i][j];
		}
		// rearraging
		for(int j = 1; j < width / 2; j++) {
			for(int k = 0; k < (width - j * 2) / 2; k++) {
				 // swapping
				 int tmp = matrix[i][j + 2 * k];
				 matrix[i][j + 2 * k] = matrix[i][j + 2 * k+1];
				 matrix[i][j + 2 * k+1] = tmp;
			}
		}
	}
	
	// col operation
	for(int i = 0; i < width; i++) {
		// average and difference
		for(int j = 0; j < length; j++) {
			if(j % 2 == 0)
				matrix[j][i] = matrix[j][i] + matrix[j+1][i];
			else
				matrix[j][i] = matrix[j-1][i] - 2 * matrix[j][i];
		}
		// rearraging
		for(int j = 1; j < length / 2; j++) {
			for(int k = 0; k < (length - j * 2) / 2; k ++) {
				// swapping
				int tmp = matrix[j + 2 * k][i];
				matrix[j + 2 * k][i] = matrix[j + 2 * k+1][i];
				matrix[j + 2 * k+1][i] = tmp;
			}
		}
	}
}

void mReverseHaarTransform(int** matrix, int length, int width) {
	if(length % 2 + width % 2 > 0)
		throw "Error in mReverseHaarTransform: length or width not divisible by 2.";
	
	// col operation
	for(int i = 0; i < width; i++) {
		// rearraging
		for(int j = 1; j < length / 2; j++) {
			for(int k = 0; k < (length - j * 2) / 2; k ++) {
				// swapping
				int tmp = matrix[j + 2 * k][i];
				matrix[j + 2 * k][i] = matrix[j + 2 * k+1][i];
				matrix[j + 2 * k+1][i] = tmp;
			}
		}
		// average and difference
		for(int j = 0; j < length; j++) {
			if(j % 2 == 0)
				matrix[j][i] = (matrix[j][i] + matrix[j+1][i]) / 2;
			else
				matrix[j][i] = matrix[j-1][i] - matrix[j][i];
		}
		
	}
	
	// row operation
	for(int i = 0; i < length; i++) {
		// rearraging
		for(int j = 1; j < width / 2; j++) {
			for(int k = 0; k < (width - j * 2) / 2; k++) {
				 // swapping
				 int tmp = matrix[i][j + 2 * k];
				 matrix[i][j + 2 * k] = matrix[i][j + 2 * k+1];
				 matrix[i][j + 2 * k+1] = tmp;
			}
		}
		// average and difference
		for(int j = 0; j < width; j++) {
			if(j % 2 == 0)
				matrix[i][j] = (matrix[i][j] + matrix[i][j+1]) / 2;
			else
				matrix[i][j] = matrix[i][j-1] - matrix[i][j];
		}
	}
}

void mHaarRecursiveTransform(int** matrix, int length, int width, int maxIteration) {
	if(length % 2 + width % 2 > 0)
		return;
	
	if(maxIteration == 0)
		return;
	maxIteration--;
	
	mHaarTransform(matrix, length, width);	
	mHaarRecursiveTransform(matrix, length / 2, width / 2, maxIteration);
}

void mReverseHaarRecursiveTransform(int** matrix, int length, int width, int maxIteration) {
	if(maxIteration == 0)
		return;
	maxIteration--;
	
	if(length % 2 + width % 2 == 0)
		mReverseHaarRecursiveTransform(matrix, length / 2, width / 2, maxIteration);
	else
		return;
	
	mReverseHaarTransform(matrix, length, width);
}

void mHaarNormalization(int** matrix, int length, int width, int maxIteration) {
	if(maxIteration == 0)
		return;
	maxIteration--;
	
	if(length % 2 + width % 2 == 0)
		// recursion
		mHaarNormalization(matrix, length / 2, width / 2, maxIteration);
	
	// normalizing
	for(int i = 0; i < length; i++)
		for(int j = 0; j < width; j++)
			if(matrix[i][j] < 0)
				matrix[i][j] = 0;
			else
				matrix[i][j] /= 4;
}


void mHaarDenormalization(int** matrix, int length, int width, int maxIteration) {
	if(maxIteration == 0)
		return;
	maxIteration--;
	
	if(length % 2 + width % 2 == 0)
		// recursion
		mHaarDenormalization(matrix, length / 2, width / 2, maxIteration);
	
	// denormalizing
	for(int i = 0; i < length; i++)
		for(int j = 0; j < width; j++)
			matrix[i][j] *= 4;
}

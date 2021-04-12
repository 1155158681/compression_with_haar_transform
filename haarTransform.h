/*
	HaarTransform
	This file contains the modified transformation based 
	on Haar tranform and the reverse transformation.
*/

#ifndef HAARTRANSFORM_H
#define HAARTRANSFORM_H

void mHaarTransform(int** matrix, int length, int width);
void mReverseHaarTransform(int** matrix, int length, int width);

void mHaarRecursiveTransform(int** matrix, int length, int width, int maxIteration = -1);
void mReverseHaarRecursiveTransform(int** matrix, int length, int width, int maxIteration = -1);

// Converts everything back to (0, 255)
// Removes all negatives
void mHaarNormalization(int** matrix, int length, int width, int maxIteration = -1);
void mHaarDenormalization(int** matrix, int length, int width, int maxIteration = -1);

#endif

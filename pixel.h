/*
	Pixel
	File containing the object "Pixel."
*/

#ifndef PIXEL_H
#define PIXEL_H

class Pixel {
	public:
		Pixel();
		Pixel(int red, int green, int blue);
		Pixel(unsigned int rgb);
		void setPixel(int red, int green, int blue);
		void setPixel(unsigned int rgb);
		
		void setRed(int red);
		void setBlue(int blue);
		void setGreen(int green);
		
		int getRed();
		int getBlue();
		int getGreen();
		
		void printPixelData();
		int getRGB();
	private:
		int red, green, blue;
		inline bool isPixelValue(int val);
};

#endif

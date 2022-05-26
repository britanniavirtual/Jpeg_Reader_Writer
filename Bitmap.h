#pragma once

#define MAX_INDEX 1024

//----------------------------------------------------------
//
//----------------------------------------------------------
struct rgb
{
	int r;
	int g;
	int b;

	rgb()
	{
		r = 255;
		g = 255;
		b = 255;
	}

	rgb(int r, int g, int b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
};
//----------------------------------------------------------
// Desc: Just the bitmap data
//----------------------------------------------------------
class BitmapMin
{
public:
	rgb **map;
	int width = MAX_INDEX;
	int height = MAX_INDEX;
	BitmapMin();
	~BitmapMin();

	void shutDown();
};

class POINT
{
public:
	float x;
	float y;
};

//----------------------------------------------------------
// Desc: Utility routines applicable to BitmapMin objects
//----------------------------------------------------------
class BitmapUtils
{
public:

	BitmapUtils();
	~BitmapUtils();

	void rgbFill(BitmapMin *input, rgb color);

	void rotate90deg(BitmapMin *input);
	void flipHorizontal(BitmapMin *input);
	void flipVertical(BitmapMin *input);

	rgb rectColor = { 234, 235, 66 };
	int rectWidth = 3;
	void drawRectangle(BitmapMin *input, int sx, int sy, int ex, int ey);
	void drawLine(BitmapMin *input, float degrees, float magnitude, int stX, int stY, rgb color);
	void resample(BitmapMin *input, int newWidth, int newHeight);

	int readJpeg(string fileName, BitmapMin * bitmap);
	int writeJpeg(string fileName, BitmapMin * bitmap);

private:

	BitmapMin *temporary;
};



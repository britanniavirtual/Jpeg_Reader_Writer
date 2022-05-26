#pragma once

#define MAX_INDEX 1024

//----------------------------------------------------------
//
//----------------------------------------------------------
struct colour
{
	int r;
	int g;
	int b;
};

//----------------------------------------------------------
//
//----------------------------------------------------------
struct rgb
{
	int r;
	int g;
	int b;
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

	void RGBFill(BitmapMin *input, int r, int g, int b);

	void rotate90deg(BitmapMin *input);
	void flipHorizontal(BitmapMin *input);
	void flipVertical(BitmapMin *input);

	void drawRectangle(BitmapMin *input, int sx, int sy, int ex, int ey);
	int rectWidth = 3;

	rgb rectColor = { 234, 235, 66 };

	void drawLine(BitmapMin *input, float angle, float magnitude, int stX, int stY, string color);
	void resize(BitmapMin *input, int width, int height);

	void drawRect(BitmapMin *input);

	int readJpeg(string fileName, BitmapMin * bitmap);
	int writeJpeg(string fileName, BitmapMin * bitmap);

private:

	BitmapMin *tmp;
};



#include "JointHeader.h"

int main()
{
	BitmapMin bmp;
	BitmapUtils utils;

	utils.readJpeg("test.jpg", &bmp);
	utils.writeJpeg("output.jpg", &bmp);

	cout << "Read: test.jpg" << endl;
	cout << "Wrote: output.jpg" << endl;

	system("PAUSE");
}
#include "JointHeader.h"

int main()
{
	BitmapMin bmp;
	BitmapUtils u;

	u.readJpeg("test.jpg", &bmp);
	//Test rectangle
	//u.drawRectangle(&bmp,32,32,128,128);
	u.writeJpeg("output.jpg", &bmp);

	cout << "Read: test.jpg" << endl;
	cout << "Wrote: output.jpg" << endl;

	system("PAUSE");
}
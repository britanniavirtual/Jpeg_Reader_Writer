#include "JointHeader.h"

int main()
{
	BitmapMin bmp;
	BitmapUtils u;

	u.readJpeg("test.jpg", &bmp);
	u.writeJpeg("output.jpg", &bmp);

	cout << "Read: test.jpg" << endl;
	cout << "Wrote: output.jpg" << endl;

	system("PAUSE");
}
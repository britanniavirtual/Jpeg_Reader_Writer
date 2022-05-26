#include "JointHeader.h"


//--------------------------------------
//
//--------------------------------------
BitmapMin::BitmapMin()
{
	map = new rgb*[MAX_INDEX];
	for (int i = 0; i < MAX_INDEX; i++)
	{
		map[i] = new rgb[MAX_INDEX];
	}

	width = MAX_INDEX;
	height = MAX_INDEX;
}


//------------------------------
// Destructor
//------------------------------
BitmapMin::~BitmapMin()
{
	/*
	for (int i = 0; i < MAX_INDEX; i++)
	{
		delete[] map[i];
	}
	delete[] map;
	*/
}

//------------------------------
// Free allocated memory as needed
//------------------------------
void BitmapMin::shutDown()
{
	for (int i = 0; i < MAX_INDEX; i++)
	{
		delete[] map[i];
	}
	delete[] map;
}

//--------------------------------------
// Draw a line on a bitmap (1 pixel width)
//--------------------------------------
void BitmapUtils::drawLine(BitmapMin *input, float degrees, float magnitude, int stX, int stY, rgb color)
{
	//Line is made of 2 equal segments
	int r1 = color.r;
	int g1 = color.g;
	int b1 = color.b;

	int r2 = color.r;
	int g2 = color.g;
	int b2 = color.b;

	for (int n = 0; n < magnitude / 2; n++)
	{
		int x = stX + cos(degrees * 0.0174533) * n;
		int y = stY + sin(degrees * 0.0174533) * n;

		if (degrees == 0 || degrees == 180 || degrees == 360)
		{
			x = stX + n;
			y = stY;
		}

		if (degrees == 90 || degrees == 270 || degrees == -90)
		{
			x = stX;
			y = stY + n;
		}

		if (x >= 0 && x < input->height && y >= 0 && y < input->width)
		{
			input->map[x][y].r = r1;
			input->map[x][y].g = g1;
			input->map[x][y].b = b1;
		}
	}

	for (int n = 0; n < magnitude / 2; n++)
	{
		int x = stX - cos(degrees * 0.0174533) * n;
		int y = stY - sin(degrees * 0.0174533) * n;

		if (degrees == 0 || degrees == 180 || degrees == 360)
		{
			x = stX - n;
			y = stY;
		}

		if (degrees == 90 || degrees == 270 || degrees == -90)
		{
			x = stX;
			y = stY - n;
		}

		if (x >= 0 && x < input->height && y >= 0 && y < input->width)
		{
			input->map[x][y].r = r2;
			input->map[x][y].g = g2;
			input->map[x][y].b = b2;
		}
	}
}


//--------------------------------------
// Resample a BitmapMin object to new dimensions
//--------------------------------------
void BitmapUtils::resample(BitmapMin *input, int width, int height)
{
	double scaleWidth = (double)width / (double)input->width;
	double scaleHeight = (double)height / (double)input->height;

	BitmapMin tmpBmp;
	for (int cy = 0; cy < MAX_INDEX; cy++)
	{
		for (int cx = 0; cx < MAX_INDEX; cx++)
		{
			tmpBmp.map[cx][cy] = input->map[cx][cy];
		}
	}

	for (int cy = 0; cy < height; cy++)
	{
		for (int cx = 0; cx < width; cx++)
		{
			int nearestMatchY = (int)(cy / scaleHeight);
			int nearestMatchX = (int)(cx / scaleWidth);

			input->map[cx][cy] = tmpBmp.map[nearestMatchX][nearestMatchY];
		}
	}

	for (int cy = 0; cy < MAX_INDEX; cy++)
	{
		for (int cx = 0; cx < MAX_INDEX; cx++)
		{
			if (cx >= width || cy >= height)
			{
				input->map[cx][cy].r = 0;
				input->map[cx][cy].g = 255;
				input->map[cx][cy].b = 0;
			}
		}
	}

	input->width = height;
	input->height = width;
}


//--------------------------------------
//
//--------------------------------------
void BitmapUtils::drawRectangle(BitmapMin *input, int sx, int sy, int ex, int ey)
{
	for (int a = sx - (rectWidth); a < ex + (rectWidth); a++)
	{
		for (int b = -rectWidth; b < rectWidth; b++)
		{
			if (b + sy >= 0 && a >= 0)
			{
				input->map[a][b + sy].r = rectColor.r;
				input->map[a][b + sy].g = rectColor.g;
				input->map[a][b + sy].b = rectColor.b;
			}
		}
	}

	for (int a = sx; a < ex + rectWidth * 2; a++)
	{
		for (int b = -rectWidth; b < rectWidth; b++)
		{
			if (b + ey >= 0 && a - rectWidth >= 0)
			{
				input->map[a - rectWidth][b + ey].r = rectColor.r;
				input->map[a - rectWidth][b + ey].g = rectColor.g;
				input->map[a - rectWidth][b + ey].b = rectColor.b;
			}
		}
	}

	for (int a = sy; a < ey; a++)
	{
		for (int b = -rectWidth; b < rectWidth; b++)
		{
			if (b + sx >= 0)
			{
				input->map[b + sx][a].r = rectColor.r;
				input->map[b + sx][a].g = rectColor.g;
				input->map[b + sx][a].b = rectColor.b;
			}
		}
	}

	for (int a = sy; a < ey; a++)
	{
		for (int b = -rectWidth; b < rectWidth; b++)
		{
			if (b + ex >= 0)
			{
				input->map[b + ex][a].r = rectColor.r;
				input->map[b + ex][a].g = rectColor.g;
				input->map[b + ex][a].b = rectColor.b;
			}
		}
	}

	for (int a = sx; a < ex + rectWidth * 2; a++)
	{
		for (int b = -rectWidth; b < rectWidth; b++)
		{
			if (b + ey >= 0 && a - rectWidth >= 0)
			{
				input->map[a - rectWidth][b + ey].r = rectColor.r;
				input->map[a - rectWidth][b + ey].g = rectColor.g;
				input->map[a - rectWidth][b + ey].b = rectColor.b;
			}
		}
	}
}


//--------------------------------------
// 
//--------------------------------------
void BitmapUtils::rgbFill(BitmapMin *input, rgb color)
{
	for (int i = 0; i < MAX_INDEX; i++)
	{
		for (int j = 0; j < MAX_INDEX; j++)
		{
			input->map[j][i].r = color.r;
			input->map[j][i].g = color.g;
			input->map[j][i].b = color.b;
		}
	}
}

//--------------------------------------
//
//--------------------------------------
BitmapUtils::BitmapUtils()
{
	temporary = new BitmapMin;
	temporary->width = MAX_INDEX;
	temporary->height = MAX_INDEX;
}

//--------------------------------------
//
//--------------------------------------
BitmapUtils::~BitmapUtils()
{
	delete temporary;
}

//--------------------------------------
//
//--------------------------------------
void BitmapUtils::flipHorizontal(BitmapMin *input)
{
	for (int i = 0; i < input->width; i++)
	{
		for (int j = 0; j < input->height; j++)
		{
			temporary->map[j][i].r = input->map[j][i].r;
			temporary->map[j][i].g = input->map[j][i].g;
			temporary->map[j][i].b = input->map[j][i].b;
		}
	}

	int depth = input->width;
	int select = 0;
	for (int i = 0; i < input->width; i++)
	{
		for (int j = 0; j < input->height; j++)
		{
			int p = i;
			select = depth - p;
			input->map[j][i].r = temporary->map[j][select].r;
			input->map[j][i].g = temporary->map[j][select].g;
			input->map[j][i].b = temporary->map[j][select].b;
		}
	}
}


//--------------------------------------
//
//--------------------------------------
void BitmapUtils::flipVertical(BitmapMin *input)
{
	for (int i = 0; i < input->width; i++)
	{
		for (int j = 0; j < input->height; j++)
		{
			temporary->map[j][i].r = input->map[j][i].r;
			temporary->map[j][i].g = input->map[j][i].g;
			temporary->map[j][i].b = input->map[j][i].b;
		}
	}

	int depth = input->height;
	int select = 0;
	for (int i = 0; i < input->width; i++)
	{
		for (int j = 0; j < input->height; j++)
		{
			int p = j;

			select = depth - p - 1;

			input->map[j][i].r = temporary->map[select][i].r;
			input->map[j][i].g = temporary->map[select][i].g;
			input->map[j][i].b = temporary->map[select][i].b;
		}
	}
}

//--------------------------------------
//
//--------------------------------------
void BitmapUtils::rotate90deg(BitmapMin *input)
{
	for (int i = 0; i < input->width; i++)
	{
		for (int j = 0; j < input->height; j++)
		{
			temporary->map[j][i].r = input->map[j][i].r;
			temporary->map[j][i].g = input->map[j][i].g;
			temporary->map[j][i].b = input->map[j][i].b;
		}
	}

	for (int i = 0; i < input->width; i++)
	{
		for (int j = 0; j < input->height; j++)
		{
			input->map[input->height - j - 1][i].r = temporary->map[i][j].r;
			input->map[input->height - j - 1][i].g = temporary->map[i][j].g;
			input->map[input->height - j - 1][i].b = temporary->map[i][j].b;
		}
	}
}






//--------------------------------------
//
//--------------------------------------
int BitmapUtils::writeJpeg(string fileName, BitmapMin * img)
{
	stringstream fn;
	fn << fileName;

	unsigned char *raw_image = NULL;
	int bytes_per_pixel = 3;   /* or 1 for GRACYSCALE images */

	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	JSAMPROW row_pointer[1];

	//Open file
	FILE *outfile = fopen(fn.str().c_str(), "wb");

	//Resolution of the bitmap object
	POINT targRes2 = { img->width, img->height };

	cinfo.image_height = targRes2.y;
	cinfo.image_width = targRes2.x;

	raw_image = (unsigned char*)malloc(targRes2.x * targRes2.y * 3);

	//Access pixels
	for (int i = 0; i < targRes2.y; i++)
	{
		for (int j = 0; j < targRes2.x; j++)
		{
			int curI = targRes2.y - i - 1;

			raw_image[(i*cinfo.image_width * 3) + (j * 3) + 0] = img->map[curI][j].r; // Red Pixel
			raw_image[(i*cinfo.image_width * 3) + (j * 3) + 1] = img->map[curI][j].g; // Green Pixel
			raw_image[(i*cinfo.image_width * 3) + (j * 3) + 2] = img->map[curI][j].b; // Blue Pixel // Now you have pixel (i,j). You can do any thing with this.
		}
	}

	if (!outfile)
	{
		return -1;
	}

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo, outfile);

	cinfo.image_width = targRes2.x;
	cinfo.image_height = targRes2.y;
	cinfo.input_components = bytes_per_pixel;
	cinfo.in_color_space = JCS_RGB;

	jpeg_set_defaults(&cinfo);
	jpeg_start_compress(&cinfo, TRUE);

	while (cinfo.next_scanline < cinfo.image_height)
	{
		row_pointer[0] = &raw_image[cinfo.next_scanline * cinfo.image_width *  cinfo.input_components];
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	fclose(outfile);


	return 1;
}

//--------------------------------------
//
//--------------------------------------
int BitmapUtils::readJpeg(string fileName, BitmapMin * bitmap)
{
	struct jpeg_decompress_struct cinfo;

	FILE * infile = fopen(fileName.c_str(), "rb");//Open the file

	if (!infile)
	{
		//cout << "File " << fileName << " not found!";
	}

	JSAMPARRAY buffer;
	struct jpeg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, infile);
	jpeg_read_header(&cinfo, TRUE);
	jpeg_start_decompress(&cinfo);
	int width = static_cast<int>(cinfo.output_width);
	int height = static_cast<int>(cinfo.output_height);

	bitmap->width = cinfo.output_width;
	bitmap->height = cinfo.output_height;

	buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr)&cinfo, JPOOL_IMAGE, cinfo.output_width * cinfo.output_components, 1);
	int curX = 0;
	int curY = 0;
	int tmpHeight = cinfo.output_height;
	while (cinfo.output_scanline < cinfo.output_height)
	{
		(void)jpeg_read_scanlines(&cinfo, buffer, 1);

		unsigned char* pixel_row = (unsigned char*)(buffer[0]);

		for (int i = 0; i < cinfo.output_width; i++)
		{
			int red = (int)(*pixel_row++);
			int green = (int)(*pixel_row++);
			int blue = (int)(*pixel_row++);

			bitmap->map[tmpHeight - curY - 1][curX].r = red;   //Red Pixel
			bitmap->map[tmpHeight - curY - 1][curX].g = green; //Green Pixel
			bitmap->map[tmpHeight - curY - 1][curX].b = blue;  //Blue Pixel

			curX++;
		}
		curY++;
		curX = 0;
	}

	int x = width;
	int y = height;

	fclose(infile);

	return 1;
}

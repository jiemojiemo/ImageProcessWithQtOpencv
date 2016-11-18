#include "Magic/Embosser.h"
#include  "DataStructure/MImage.h"
REGISTER_INTO_FACTORY(Embosser);

void Emboss(cv::Mat& im)
{
	IplImage *image = new IplImage(im);
	int width = image->width;
	int height = image->height;
	int step = image->widthStep;
	int channel = image->nChannels;
	uchar* data = (uchar *)image->imageData;
	for (int i = 0; i < width - 1; i++)
	{
		for (int j = 0; j < height - 1; j++)
		{
			for (int k = 0; k < channel; k++)
			{
				int temp = data[(j + 1)*step + (i + 1)*channel + k] - data[j*step + i*channel + k] + 128;//¸¡µñ  
				//int temp = data[j*step+i*channel+k]-data[(j+1)*step+(i+1)*channel+k]+128;//µñ¿Ì  
				if (temp > 255)
				{
					data[j*step + i*channel + k] = 255;
				}
				else if (temp < 0)
				{
					data[j*step + i*channel + k] = 0;
				}
				else
				{
					data[j*step + i*channel + k] = temp;
				}
			}
		}
	}
	delete image;
}

void Embosser::DoMagic(MImage& img)
{
	Emboss(img.GetMat());
}


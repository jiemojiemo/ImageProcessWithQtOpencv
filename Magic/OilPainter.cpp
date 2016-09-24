#include "Magic/OilPainter.h"
#include "imgproc.hpp"
#include "DataStructure/Image.h"

#include <vector>

REGISTER_INTO_FACTORY(OilPainter);

void OilProcess(cv::Mat& im)
{
	using namespace cv;
	using namespace std;

	Mat dst(im.rows, im.cols, CV_8UC3);

	Mat  intensityLUT(im.rows, im.cols, CV_8UC1);
	Mat  rgbLUT(im.rows, im.cols, CV_8UC3); //r/g/b

	int intensity = 20;
	int radius = 3;
	int pixelIntensityValue[100];
	Vec3f pixelIntensityRGB[100];

	cvtColor(im, intensityLUT, CV_RGB2GRAY);
	intensityLUT = intensityLUT *(intensity / 255.);


	for (int y = 0; y < im.rows; y++)
	{
		for (int x = 0; x < im.cols; x++) //for each pixel
		{
			vector<int> pixelIntensityCount;
			vector<Vec3f> pixelIntensityRGB;
			pixelIntensityCount.assign(100, 0);
			pixelIntensityRGB.assign(100, Vec3f(0, 0, 0));
			for (int yy = -radius; yy <= radius; yy++)
			{
				for (int xx = -radius; xx <= radius; xx++)
				{
					if (y + yy > 0 && y + yy < im.rows && x + xx > 0 && x + xx < im.cols)
					{
						int intensityVal = intensityLUT.at<uchar>(y + yy, x + xx);
						pixelIntensityCount[intensityVal]++; // priority
						pixelIntensityRGB[intensityVal] += im.at<Vec3b>(y + yy, x + xx); //red

					}
				}
			}
			vector<int>::iterator it;
			int pos = distance(pixelIntensityCount.begin(), max_element(pixelIntensityCount.begin(), pixelIntensityCount.end()));
			Vec3b v(pixelIntensityRGB[pos][0] / pixelIntensityCount[pos], pixelIntensityRGB[pos][1] / pixelIntensityCount[pos], pixelIntensityRGB[pos][2] / pixelIntensityCount[pos]);
			dst.at<Vec3b>(y, x) = v;
		}
	}
	im = dst;
}

void OilPainter::DoMagic(Image& img)
{
	OilProcess(img.GetMat());
}


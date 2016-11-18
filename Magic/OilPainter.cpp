#include "Magic/OilPainter.h"
#include "imgproc.hpp"
#include "DataStructure/MImage.h"

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

cv::Mat OilPaint(cv::Mat& I, int brushSize, int coarseness)
{
using namespace cv;
using namespace std;
	assert(!I.empty());
	if (brushSize < 1) brushSize = 1;
	if (brushSize > 8) brushSize = 8;

	if (coarseness < 1) coarseness = 1;
	if (coarseness > 255) coarseness = 255;

	int width = I.cols;
	int height = I.rows;

	int lenArray = coarseness + 1;
	int* CountIntensity = new int[lenArray];
	uint* RedAverage = new uint[lenArray];
	uint* GreenAverage = new uint[lenArray];
	uint* BlueAverage = new uint[lenArray];

	/// 图像灰度化
	cv::Mat gray;
	cvtColor(I, gray, cv::COLOR_BGR2GRAY);


	/// 目标图像
	cv::Mat dst = cv::Mat::zeros(I.size(), I.type());

	for (int nY = 0; nY < height; nY++)
	{
		// 油画渲染范围上下边界
		int top = nY - brushSize;
		int bottom = nY + brushSize + 1;

		if (top < 0) top = 0;
		if (bottom >= height) bottom = height - 1;

		for (int nX = 0; nX < width; nX++)
		{
			// 油画渲染范围左右边界
			int left = nX - brushSize;
			int right = nX + brushSize + 1;

			if (left < 0) left = 0;
			if (right >= width) right = width - 1;

			//初始化数组
			for (int i = 0; i < lenArray; i++)
			{
				CountIntensity[i] = 0;
				RedAverage[i] = 0;
				GreenAverage[i] = 0;
				BlueAverage[i] = 0;
			}


			// 下面这个内循环类似于外面的大循环
			// 也是油画特效处理的关键部分
			for (int j = top; j < bottom; j++)
			{
				for (int i = left; i < right; i++)
				{
					uchar intensity = static_cast<uchar>(coarseness*gray.at<uchar>(j, i) / 255.0);
					CountIntensity[intensity]++;

					RedAverage[intensity] += I.at<Vec3b>(j, i)[2];
					GreenAverage[intensity] += I.at<Vec3b>(j, i)[1];
					BlueAverage[intensity] += I.at<Vec3b>(j, i)[0];
				}
			}

			// 求最大值，并记录下数组索引
			uchar chosenIntensity = 0;
			int maxInstance = CountIntensity[0];
			for (int i = 1; i < lenArray; i++)
			{
				if (CountIntensity[i] > maxInstance)
				{
					chosenIntensity = (uchar)i;
					maxInstance = CountIntensity[i];
				}
			}

			dst.at<Vec3b>(nY, nX)[2] = static_cast<uchar>(RedAverage[chosenIntensity] / static_cast<float>(maxInstance));
			dst.at<Vec3b>(nY, nX)[1] = static_cast<uchar>(GreenAverage[chosenIntensity] / static_cast<float>(maxInstance));
			dst.at<Vec3b>(nY, nX)[0] = static_cast<uchar>(BlueAverage[chosenIntensity] / static_cast<float>(maxInstance));
		}

	}

	delete[] CountIntensity;
	delete[] RedAverage;
	delete[] GreenAverage;
	delete[] BlueAverage;

//#ifdef _DEBUG
//	imshow("dst", dst);
//	waitKey();
//#endif
	I = dst;
	return dst;
}
void OilPainter::DoMagic(MImage& img)
{
	OilPaint(img.GetMat(), 3,25);
}


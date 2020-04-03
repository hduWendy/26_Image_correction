// 26_Image_correction.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
	//读取本地的一张图片，图像校正，并显示出来
	cv::Mat dstMat;
	cv::Mat srcMat = imread("C:/Users/lenovo/Desktop/推文/1.jpg");
	cv::Mat sampleMat = imread("C:/Users/lenovo/Desktop/数图图片/lena_rot.jpg");
	if (srcMat.empty()|| sampleMat.empty())return-1;

	int sample_height = sampleMat.rows; //行数
	int sample_width = sampleMat.cols; //每行元素的总元素数量
	int src_height = srcMat.rows; //行数
	int src_width = srcMat.cols; //每行元素的总元素数量

	int sample_x1, sample_y2, sample_x3, sample_y4;
	for (int i = 0; i<sample_width; i++)
	{
		if (sampleMat.at<Vec3b>(0, i)[0] != 255)
		{
			sample_x1 = i;
			break;
		}
	} //单行处理结束  
	for (int j = 0; j<src_height; j++)
	{
		if (sampleMat.at<Vec3b>(j , sample_width - 1)[0] != 255)
		{
			sample_y2 = j;
			break;
		}
	} //单行处理结束  
	for (int i = sample_width - 1; i >= 0; i--)
	{
		if (sampleMat.at<Vec3b>(src_height - 1, i)[0] != 255)
		{
			sample_x3 = i;
			break;
		}
	} //单行处理结束  
	for (int j = src_height - 1; j >= 0; j--)
	{
		if (sampleMat.at<Vec3b>(j, 0)[0] != 255)
		{
			sample_y4 = j;
			break;
		}
	} //单行处理结束  
	//
	const cv::Point2f src_pt[] = {
		cv::Point2f(0,0),
		cv::Point2f(sample_width - 1,0),
		cv::Point2f(sample_width - 1,src_height - 1)
	};
	//
	const cv::Point2f dst_pt[] = {
		cv::Point2f(sample_x1,0),
		cv::Point2f(sample_width - 1,sample_y2),
		cv::Point2f(sample_x3,src_height - 1)
	};
	//
	const cv::Mat affine_matrix = cv::getAffineTransform(src_pt, dst_pt);

	cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

	imshow("src", srcMat);
	imshow("dst", dstMat);
	imshow("sample", sampleMat);
	//等待用户按键
	waitKey(0);
	return 0;
}

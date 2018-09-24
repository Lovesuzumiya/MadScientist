// MyfirstOpenCV.cpp: 定义控制台应用程序的入口点。
//<pre name = "code" class = "cpp">


#include "stdafx.h"
#include<iostream>
#include<core/core.hpp>
#include<highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int Threshold = 0;//全局变量阈值
Mat image = imread("E:\\图片\\2b.png");
Mat grayImage;
Mat binary;

void on_Trackbar(int, void*);//定义关于滑动条的回调函数

void on_Mouse(int event,int x,int y,int flags, void*);//定义关于鼠标响应的回调函数

void Reverse(cv::Mat image)//定义一个二值化反转函数void Reverse，作用在矩阵上，把每一个点的像素值变为原来的反
{
	int height = image.rows;
	int width = image.cols*image.channels();
	for (int i = 0; i< height; i++)
	{
		for (int j = 0; j< width; j++)
		{
			image.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);   // 每一个像素反转
		}
	}
}

int main()
{
	int key=waitKey(30);
	//图片读入成功与否判定
	if (!image.data)
	{
		cout << "Error" << endl;
		return -1;
	}

	namedWindow("2B", 1);
	imshow("2B", image);
	createTrackbar("Threshold", "2B", &Threshold, 255, on_Trackbar);

	cvtColor(image, grayImage, CV_BGR2GRAY);
	threshold(grayImage, binary, Threshold , 255, CV_THRESH_BINARY);
	
	waitKey();
	namedWindow("2B_Binary");
	imshow("2B_Binary", binary);
	imwrite("2B_Binary.png", binary);
	
	setMouseCallback("2B_Binary", on_Mouse);

	waitKey(0);
	imwrite("Reverse.png", binary);

	binary.release();
	grayImage.release();
	image.release();
	destroyAllWindows();
	
    return 0;
}

void on_Trackbar(int,void*)
{
	cout << "Threshold value: " << endl;
	cout << "Threshold" << Threshold << endl;
}

void on_Mouse(int event, int x, int y, int flags, void*)
{
	if (event == EVENT_LBUTTONUP)
	{
		cout << "进行二值化反转" << endl;
		Reverse(binary);
		imshow("Reverse", binary);
	}
}
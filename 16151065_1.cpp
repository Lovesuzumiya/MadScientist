// 16151065_1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<iostream>

int main()
{
	cv::VideoCapture capture(0);
	cv::Mat frame;
	while(true)
	{
		capture >> frame;
		if (frame.empty())
			break;
		cv::imshow("16151065", frame);
		if (cv::waitKey(30) >= 0)
			break;
	}
	capture.release();
	cv::destroyAllWindows;
    return 0;
}


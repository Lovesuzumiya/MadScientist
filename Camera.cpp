
#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<iostream>

int main()
{
	cv::VideoCapture capture(0);//'0'means you open a camera on your computer,not a USB camera or a native video. 
	cv::Mat frame;
	while(true)
	{
		capture >> frame;
		if (frame.empty())
			break;
		cv::imshow("Camera", frame);
		if (cv::waitKey(30) >= 0)//'30'means delayed time is 30ms.If it is set as 0,it means this camera can only catch the first picture and if you want see the next you can press any button.However,this loop is designed to break when you press one button.Then cause a bug.
			break;
	}
	capture.release();
	cv::destroyAllWindows;
    return 0;
}


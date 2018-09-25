//<pre name = "code" class = "cpp">
//This code can achieve following functions:
//1.read and show an image in your computer;
//2.transfer the image to a binary image,the threshold of which is determined by a trackbar;
//3.reverse the image through a mouse callback function.
//4.save the binary version and reverse version.

#include "stdafx.h"
#include<iostream>
#include<core/core.hpp>
#include<highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int Threshold = 0;
Mat image = imread("E:\\Images\\2b.png");//an image in NieR:Automata
Mat grayImage;
Mat binary;

void on_Trackbar(int, void*);//Define a callback function on trackbar to decide the threshold on binary image.

void on_Mouse(int event,int x,int y,int flags, void*);//efine a callback function on mouse,which reacts to mouse left click.

void Reverse(cv::Mat image)//reverse each pixel
{
	int height = image.rows;
	int width = image.cols*image.channels();
	for (int i = 0; i< height; i++)
	{
		for (int j = 0; j< width; j++)
		{
			image.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);   // the real one step to reverse
		}
	}
}

int main()
{
	//judge weather the image is read or not
	if (!image.data)
	{
		cout << "Error" << endl;
		return -1;
	}

	namedWindow("2B", 1);
	imshow("2B", image);
	createTrackbar("Threshold", "2B", &Threshold, 255, on_Trackbar);//set a trackbar on the picture so we can decise the threshold

	cvtColor(image, grayImage, CV_BGR2GRAY);//turn the picture to a black-and-white version,or you will get a colored 'binary' picture
	threshold(grayImage, binary, Threshold , 255, CV_THRESH_BINARY);//'255'means all pixel values are accepted.If you set it at 200,for example,the maxium pixel value will be 200.
	
	waitKey();
	threshold(grayImage, binary, Threshold, 255, CV_THRESH_BINARY);//Noticed that Threshold is a global assignment
	namedWindow("2B_Binary");
	imshow("2B_Binary", binary);
	imwrite("2B_Binary.png", binary);//we will use the mat binary later,so you have to save it now.
	
	setMouseCallback("2B_Binary", on_Mouse);//left click

	waitKey(0);
	imwrite("Reverse.png", binary);//binary is reversed,and the former one is covered.

	binary.release();
	grayImage.release();
	image.release();
	destroyAllWindows();
	
    return 0;
}

void on_Trackbar(int,void*)
{
	cout << "Threshold value: " << endl;
	cout << "Threshold = " << Threshold << endl;
}


void on_Mouse(int event, int x, int y, int flags, void*)
{
	if (event == EVENT_LBUTTONUP)
	{
		cout << "Reverse" << endl;
		Reverse(binary);
		imshow("Reverse", binary);
	}
}

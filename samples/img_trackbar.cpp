/*
g++ -Wall -o salida E6_2.cpp `pkg-config --cflags --libs opencv`
*/

#include<iostream>

#include<opencv2/core/core.hpp> // core data structures, data types and memory management
#include<opencv2/ml/ml.hpp> // statistical models and clasification algorithms
#include<opencv/cv.h>
#include<opencv2/imgproc/imgproc.hpp>  // image filtering, 
#include<opencv2/highgui/highgui.hpp> //GUI, reading and writing images and video
#include <stdlib.h>
#include <stdio.h>


using namespace std;

using namespace cv;
//call back function for trackbar event
const int slider_max = 3;
int slider;
Mat img;

void on_trackbar(int pos, void*){
	Mat img_converted;
	
		if( pos == 0 ){
			imshow("Trackbarr app",img);
		}
		if(pos == 1){
			cvtColor(img, img_converted, CV_RGB2GRAY);
		}
		if (pos == 2){
			cvtColor(img, img_converted, CV_RGB2YUV);
		}
		if (pos == 3){
			cvtColor(img, img_converted, CV_RGB2HSV);
		}
	
		imshow("Trackbar app", img_converted);
}


int main(void){
	img = imread("i06_79008885.jpg");
	namedWindow("Trackbar app", WINDOW_NORMAL);
	imshow("Trackbar app", img);
	slider = 0;
	//int createTrackbar(const string& trackbarname, const string& winname, 	int* value, int count, TrackbarCallback onChange=0, void* userdata=0)
	createTrackbar("RGB<->Grayscale","Trackbar app", &slider ,slider_max, on_trackbar);
	while(char (waitKey(1) != 'q')) {}
	
	return 0; 
	
}

#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/ml/ml.hpp>
#include<opencv/cv.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

// g++ -Wall -o sample1 sample1.cpp `pkg-config --cflags --libs opencv`

using namespace std;
using namespace cv;

int main(int argc, char **argv){

    Mat im; // create a Mat data type to hold the image im.

	im = imread("i06_79008885.jpg", CV_LOAD_IMAGE_GRAYSCALE); // load the image to im
	// the type of image is CV_8UC3  8 bits per pixel per channel and its unsigned char and 3 channels

	namedWindow("Hello");
	imshow("Hello", im);

	if(waitKey(3000)>0){return -1;}



}

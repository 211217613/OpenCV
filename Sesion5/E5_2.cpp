
/*
g++ -Wall -o salida E4_5.cpp `pkg-config --cflags --libs opencv`

*/

#include<iostream>

#include<opencv2/core/core.hpp>
#include<opencv2/ml/ml.hpp>
#include<opencv/cv.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>




using namespace std;

using namespace cv;


int valor=0;
int PEPSI=0;
int Amin = 0;
int Amax = 0;

int Bmin = 0;
int Bmax = 0;

int Cmin = 0;
int Cmax = 0;

int main(void)
{
	namedWindow("opencv");
	

	createTrackbar("A_min", "opencv", &Amin, 255, NULL);
	createTrackbar("A_max", "opencv", &Amax, 255, NULL);

	createTrackbar("B_min", "opencv", &Bmin, 255, NULL);
	createTrackbar("B_max", "opencv", &Bmax, 255, NULL);

	createTrackbar("C_min", "opencv", &Cmin, 255, NULL);
	createTrackbar("C_max", "opencv", &Cmax, 255, NULL);

	
	Mat Imagen;

	VideoCapture cap(0);
	
	

	if(!cap.isOpened())	return -1;
	
	while(1)
	{
		cap >> Imagen;

		cvtColor(Imagen,Imagen,CV_RGB2HSV);

		GaussianBlur(Imagen, Imagen, Size(7, 7),0,0);

		inRange(Imagen, Scalar(Amin,Bmin,Cmin), Scalar(Amax,Bmax,Cmax) ,Imagen);
		imshow("Camara 1", Imagen);
		if(waitKey(30)>0) break;
	}

	

}

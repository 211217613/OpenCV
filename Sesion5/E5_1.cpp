
/*
g++ -Wall -o salida E5_2.cpp `pkg-config --cflags --libs opencv`

*/


#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream> 
#include <stdlib.h>
#include <stdio.h>




using namespace std;

using namespace cv;



int main(void){
	Mat Imagen;

	VideoCapture cap(0);
	
	if(!cap.isOpened())	return -1;
	
	while(1){

		cap >> Imagen;

		cvtColor(Imagen,Imagen,CV_RGB2HSV);

		GaussianBlur(Imagen, Imagen, Size(7, 7),0,0);

		inRange(Imagen, Scalar(50,50,50), Scalar(90,90,90) ,Imagen);
		imshow("Camara 1", Imagen);
		if(waitKey(30)>0) break;
	}
}

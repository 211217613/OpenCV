
/*
g++ -Wall -o salida E4_1.cpp `pkg-config --cflags --libs opencv`

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

int main(void)
{
	Mat Imagen;

	VideoCapture cap(0);

	if(!cap.isOpened())	return -1;
	
	while(1)
	{
		cap >> Imagen;
		erode(Imagen, Imagen, Mat(), Point(-1, -1), 10, 1, 1);
		//cvtColor(Imagen,Imagen,CV_RGB2GRAY);
		//integral(Imagen,Imagen);
		//GaussianBlur(Imagen, Imagen, Size(5, 5),0,0);
		//blur(Imagen, Imagen, Size(50,50), Point(-1,-1));
	
		
		imshow("Camara 1", Imagen);
		if(waitKey(30)>0) break;
	}
	

	

}

/*
g++ -Wall -o E4_1 E4_1.cpp `pkg-config --cflags --libs opencv`

*/

#include<iostream>

#include<opencv2/core/core.hpp>
#include<opencv2/ml/ml.hpp>
#include<opencv/cv.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>



using namespace std;

using namespace cv;



int main(void)
{
	Mat Imagen;

	VideoCapture cam1(0);

	if(!cam1.isOpened())	return -1;
	
	while(1)
	{
		cam1 >> Imagen;
		cvtColor(Imagen, Imagen, CV_BGR2Luv );	
		//cvtColor(Imagen, Imagen, CV_BGR2GRAY );
		//cvtColor(Imagen, Imagen, CV_BGR2HSV );
		//cvtColor(Original, Result, Transformation );	
		imshow("Camara 1", Imagen);
		if(waitKey(30)>0){
			 break;
		};
	}
	

	

}


/*
g++ -Wall -o salida E4_1A.cpp `pkg-config --cflags --libs opencv`

*/


/*Bibliotecas*/
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

	VideoCapture CAM1(0);

	if(!CAM1.isOpened())	return -1;
	
	while(1)
	{
		CAM1 >> Imagen;
		
		cvtColor(Imagen, Imagen, CV_BGR2Luv);
		imshow("Camara 1", Imagen);
		if(waitKey(30)>0) break;
	}
	

	

}

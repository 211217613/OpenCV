
/*
g++ -Wall -o salida E3_1.cpp `pkg-config --cflags --libs opencv`

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

	VideoCapture vigilancia1(0);

	if(!vigalancia1.isOpened())	return -1;
	
	while(1)
	{
		vigilancia1 >> Imagen;
		imshow("Camara 1", Imagen);
		if(waitKey(30)>0) break;
	}
	

	

}


/*
g++ -Wall -o salida E4_4.cpp `pkg-config --cflags --libs opencv`

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
	Mat Imagen, Taco;

	VideoCapture CAM1(0);

	if(!CAM1.isOpened())	return -1;
	
	while(1)
	{
		CAM1 >> Imagen;
		
		erode(Imagen, Taco, Mat(), Point(-1, -1), 10, 1, 1);
		blur(Taco, Taco, Size(50,50), Point(-1,-1));
		GaussianBlur(Taco, Taco, Size(11,11),0,0);
		cvtColor(Taco, Taco, CV_BGR2HSV);
		imshow("Camara 1", Imagen);	
		imshow("FIltro BLUR", Taco);
		if(waitKey(30)>0) break;
	}
	

	

}

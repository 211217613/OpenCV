
/*
g++ -Wall -o salida E4_3.cpp `pkg-config --cflags --libs opencv`

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
		
		GaussianBlur(Imagen,Taco, Size(50,50),0,0 );
		imshow("Camara 1", Imagen);	
		imshow("FIltro BLUR", Taco);
		if(waitKey(30)>0) break;
	}
	

	

}


/*
g++ -Wall -o E4_2 E4_2.cpp `pkg-config --cflags --libs opencv`

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
	Mat ImagenBlur;

	VideoCapture cam1(0);

	if(!cam1.isOpened())	return -1;
	
	while(1)
	{
		cam1 >> Imagen;
		GaussianBlur(Imagen, ImagenBlur, Size(100,100), 0, 0);
		//blur(Imagen, ImagenBlur, Size(100,100), Point(-1,-1) );
		//erode()
		imshow("Filter GaussianBlur", ImagenBlur);	
		imshow("Camara 1", Imagen);
		if(waitKey(5) > 0){
			 break;
		};
	}
	

	

}

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

int VAR1;

double cuenta = 0;

using namespace std;
using namespace cv;

static void onMouse( int event, int x, int y, int, void*){

	cout << cuenta++ << endl;

}


int main(){
	int A_min = 0, A_max = 0, B_min = 0, B_max = 0, C_min = 0, C_max = 0;
	Mat Imagen, Img_HSV, Img_Filtrada, Img_Filtro_Color;
	VideoCapture camweb(0);
	
	// function que merite crear una ventatna llada barras
	namedWindow("Barras");
	namedWindow("Color");
	
	setMouseCallback("Color", onMouse, 0);
	
	createTrackbar("VARIABLE1","Barras", &VAR1, 255, NULL);
	createTrackbar("A_min","Barras", &A_min, 255, NULL);
	createTrackbar("A_max","Barras", &A_max, 255, NULL);
	createTrackbar("B_min","Barras", &B_min, 255, NULL);
	createTrackbar("B_max","Barras", &B_max, 255, NULL);
	createTrackbar("C_min","Barras", &C_min, 255, NULL);
	createTrackbar("C_max","Barras", &C_max, 255, NULL);

	

	if( !camweb.isOpened() ){
		return -1;
	}

	while(1){

		camweb >> Imagen;
		cvtColor(Imagen, Img_HSV, CV_RGB2GRAY);
		imshow("Barras", Img_HSV);
		
		// stop and wait for a key stroke
		// has to be used after imshow for the image to be drawn
		if( waitKey(15) > 0)
		break;

	}

	return 0;
}

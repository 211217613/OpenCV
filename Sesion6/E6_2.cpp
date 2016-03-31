
/*
g++ -Wall -o salida E6_2.cpp `pkg-config --cflags --libs opencv`

*/


#include <opencv2/core/core.hpp> // core data structures, data types and memory management
#include <opencv2/ml/ml.hpp>
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>  // i
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cv;

double cuenta = 0;

static void onMouse( int event, int x, int y, int, void* ){
	switch(event){
		case CV_EVENT_LBUTTONDOWN:    
			//cout << cuenta++ <<  endl;
			//cout << "X " << x << endl;
			//cout << "Y " << y << endl;
			if((x > 9) && (x<241) && (y > 3 ) && (y<137))
				cout << "BOTON1" << endl;
			if((x > 9) && (x<241) && (y > 147 ) && (y<282))
				cout << "BOTON2" << endl;
			
			break;
	}
}

int main(void){
	Mat Imagen;
	namedWindow("Color");
	Imagen = imread("menu.png", CV_LOAD_IMAGE_COLOR); 
	imshow("Color", Imagen);
	// three events
	setMouseCallback( "Color", onMouse, 0 );

	while(1){	
		if(waitKey(30)=='c') break;
	}

}

/*
g++ -Wall -o window window.cpp `pkg-config --cflags --libs opencv`
*/

#include <iostream>

#include <opencv2/core/core.hpp> // core data structures, data types and memory management
#include <opencv2/ml/ml.hpp> // statistical models and clasification algorithms
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>  // image filtering, 
#include <opencv2/highgui/highgui.hpp> //GUI, reading and writing images and video
#include <stdlib.h>
#include <stdio.h>


using namespace std;
using namespace cv;

int main(void){
	Mat camara, plantilla, camara_small;
	plantilla = imread("Plantilla.png", CV_LOAD_IMAGE_COLOR);
	VideoCapture cam(1);
	namedWindow("Videos", WINDOW_AUTOSIZE);

	Rect rect(Point(280, 0), Size(320, 240));
	
	while(1){
		cam >> camara;

		resize(camara, camera_small, Size(320, 240), 0, 0, INTER_CUBIC);
		imshow("Sistema", plantilla);	
		camara_small.copyTo(plantilla(rect));
		putText(plantilla, "Practica6", Point(30, 240), FONT_HERSHEY_PLAIN, 2, Scalar(0,255,0), 1, CV_AA);
		putText(plantilla, "Letter:", Point(30, 340), FONT_HERSHEY_PLAIN, 2, Scalar(0,255,0), 1, CV_AA);
		if( waitKey(30) > 0) break; // waitKey() function: stop and wait for (x seconds)
	}
}

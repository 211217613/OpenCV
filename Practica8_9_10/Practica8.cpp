/*
g++ -Wall -o salida Practica8.cpp `pkg-config --cflags --libs opencv`
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
Mat plantilla, camera, camera_small, camera_gray, camera_gray_small, camera_flip, camera_flip_small;
Mat inicio_png, cam_png, plot_png, grafica;
int i;

int inicio_fcn();
int cam_fcn();

static void onMouse( int event, int x, int y, int, void* ){
	switch(event){
		case CV_EVENT_LBUTTONDOWN:  

			if (i == 0){
				if((x >= 250) && (x <= 350) && (y >= 100 ) && (y <= 200))
					putText(plantilla, "1", Point(604,128), FONT_HERSHEY_PLAIN, 8, Scalar(0,255,0), 1, CV_AA);


			}  
			if (i == 1){
				if((x >= 40) && (x <= 359) && (y >= 50 ) && (y <= 289))
					imshow("BIG", camera);
			}


			if((x >= 0) && (x <= 100) && (y >= 0 ) && (y <= 50)){
				cout << i << endl;
				i = 0;	

			}

			if((x >= 101) && (x <= 200) && (y >= 0 ) && (y <= 50)){
				i = 1;
				cout << i << endl;				
			}

			if((x >= 737) && (x <= 792) && (y >= 477 ) && (y <= 532)){
				system("shutdown -P 1");
			}

			if((x >= 200) && (x <= 300) && (y >= 0 ) && (y <= 50)){
				char command [20];	
				int amp = 1 , freq = 1, func = 1;
				sprintf ( command, "./plot %d %d %d",amp, freq, func);
				//system("./plot 2 4 2");
				system(command);
				system("gnuplot plot.plt");
				cout<< "grafica" << endl;
				i = 2;
			}

			if((x >= 500) && (x <= 600) && (y >= 0 ) && (y <= 50)){
				system("mail < filename.ascii rubenavazquez@gmail.com -s");
			}

		break;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void){
	i = 0;
	VideoCapture cam(0);
	
	if( !cam.isOpened() )
		return -1;
	
	plantilla = imread("Plantilla.png", CV_LOAD_IMAGE_COLOR);
	inicio_png = imread("Keypad.png",CV_LOAD_IMAGE_COLOR);
	plot_png = imread("plot.png", CV_LOAD_IMAGE_COLOR);
	grafica = imread("Grafica.png", CV_LOAD_IMAGE_COLOR);

	
	
	namedWindow("Main");
		
	//putText(plantilla, "adc0:", Point(301,270), FONT_HERSHEY_PLAIN, 2, Scalar(0,255,0), 1, CV_AA);
	setMouseCallback("Main", onMouse, 0);	
	

	for( ; ; ){
		cam >> camera;
		cvtColor(camera, camera_gray, CV_RGB2GRAY);
		imshow("Main", inicio_png);

		switch (i){

			case 0:{
			//	Rect first(Point(50, 100), Size(300, 400));
				//inicio_png.copyTo(plantilla(first));
				break;
			}

			case 1:{
				imshow("Main", plantilla);
		
				Rect cam1(Point(40, 50), Size(320, 240));
				Rect cam2(Point(440, 50), Size(320, 240));
				Rect cam3(Point(40, 330), Size(320, 240));
				Rect cam4(Point(440, 330), Size(320, 240));

				resize(camera_gray, camera_gray, Size(320, 240), 0, 0, INTER_CUBIC);
				resize(camera, camera_small, Size(320, 240), 0, 0, INTER_CUBIC);
				resize(camera, camera_small, Size(320, 240), 0, 0, INTER_CUBIC);
				resize(camera, camera_small, Size(320, 240), 0, 0, INTER_CUBIC);


				camera_small.copyTo(plantilla(cam1));
				camera_small.copyTo(plantilla(cam2));
				camera_small.copyTo(plantilla(cam3));
				camera_small.copyTo(plantilla(cam4));
				break;
			}

			case 2:
				
				imshow("Main", grafica);
				//imshow("Main", plot_png);
				Rect plot(Point(120, 50), Size(500, 480));
				plot_png.copyTo(grafica(plot));
				break;

		}

		if( waitKey(30) > 0) break;
	}
}


int inicio_fcn(){
	// puts text in a namedWindow box
	//void putText( Mat& img, const string& text, Point org, int fontFace, double fontScale, Scalar color,int thickness=1, int lineType=8, bool     bottomLeftOrigin=false )

	putText(plantilla, "1", Point(450,150), FONT_HERSHEY_PLAIN, 8, Scalar(0,255,255), 1, CV_AA);
	putText(plantilla, "1", Point(480,150), FONT_HERSHEY_PLAIN, 8, Scalar(0,255,0), 1, CV_AA);
	putText(plantilla, "1", Point(500,150), FONT_HERSHEY_PLAIN, 8, Scalar(0,255,0), 1, CV_AA);
	putText(plantilla, "1", Point(550,150), FONT_HERSHEY_PLAIN, 8, Scalar(0,255,0), 1, CV_AA);
	

	return 0;
}


int cam_fcn(){


 	return 0;
}
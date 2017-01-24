/*
g++ -Wall -o salida E6_2.cpp `pkg-config --cflags --libs opencv`
*/


#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp> // statistical models and clasification algorithms
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>  // image filtering, 
#include <opencv2/highgui/highgui.hpp> //GUI, reading and writing images and video

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <sys/ioctl.h>


using namespace std;
using namespace cv;
Mat plantilla;
Mat camera, camera_small;


void buttonCallBack(int state, void *){

	switch(state){
		case 0:
			std::cout << " The button has been pressed" << endl;
			break;
		case 1:
			std::cout << " The button has been depressed" << endl;
			break;
	
	}

}


void buttonCallBackSave(int state, void *){

	if(state != 1){
		std::cout << " The button has been pressed" << endl;
		std::cout << " Saving.... " << endl;
		imwrite( "ImagenX.png", camera);
	}

}

static void cuandoElRatonSeMueve( int event, int x, int y, int, void *){
	switch (event){
	case CV_EVENT_LBUTTONDOWN:
		std::cout << "X: " << x << " Y: " << y << endl;
		
		// fix these
		if (x >= 4 && x <= 133 && y >= 181 && y <= 240 ){
			std::cout << "LED off " << endl;
			putText(plantilla, "LED ON", Point(53,266), FONT_HERSHEY_PLAIN, 2, Scalar(255,255,255), 1);
			putText(plantilla, "LED OFF", Point(53,266), FONT_HERSHEY_PLAIN, 2, Scalar(0,255,0), 1);
			
		}
		
		if (x >= 141 && x <= 270 && y >= 182 && y <= 241 ){
			std::cout << "LED on " << endl;
			putText(plantilla, "LED OFF", Point(53,266), FONT_HERSHEY_PLAIN, 2, Scalar(255,255,255), 1);
			putText(plantilla, "LED ON", Point(53,266), FONT_HERSHEY_PLAIN, 2, Scalar(255,0,0), 1);
			
		}
		
		break;
	
	}
	
}

int main(void){
	
	VideoCapture cam(0);
	
	if( !cam.isOpened() )
		return -1;
	
	plantilla = imread("Plantilla.png", CV_LOAD_IMAGE_COLOR);
	namedWindow("Sistema");
	
	
	// puts text in a namedWindow box
	//void putText( Mat& img, const string& text, Point org, int fontFace, double fontScale, Scalar color,int thickness=1, int lineType=8, bool     bottomLeftOrigin=false )
	
//	int createButton( const string& bar_name, ButtonCallback on_change, void* userdata=NULL, inttype=CV_PUSH_BUTTON, bool initial_button_state=0 )

	createButton("LED OFF",buttonCallBack,NULL,CV_PUSH_BUTTON,1);
	createButton("LED ON",buttonCallBack,NULL,CV_PUSH_BUTTON,1);
	
	createButton("Save",buttonCallBackSave,NULL,CV_PUSH_BUTTON,1);
	putText(plantilla, "Practica5", Point(30,30), FONT_HERSHEY_PLAIN, 2, Scalar(0,255,0), 1, CV_AA);
	setMouseCallback("Sistema", cuandoElRatonSeMueve, 0);	
	Rect taco(Point(280, 0), Size(320, 240));
	for( ; ; ){
		cam >> camera;
		resize(camera, camera_small, Size(320, 240), 0, 0, INTER_CUBIC);
		//imshow("Camera 1", camera_small);
		imshow("Sistema", plantilla);	
		camera_small.copyTo(plantilla(taco));
		if( waitKey(30) > 0) break;
	}


}

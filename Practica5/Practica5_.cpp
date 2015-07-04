/*
g++ -Wall -o salida practica5.cpp `pkg-config --cflags --libs opencv`
*/
// CPP cout include
#include <iostream>

// OpenCV libraries
#include <opencv2/core/core.hpp> // core data structures, data types and memory management
#include <opencv2/ml/ml.hpp> // statistical models and clasification algorithms
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>  // image filtering, 
#include <opencv2/highgui/highgui.hpp> //GUI, reading and writing images and video
#include <stdlib.h>
#include <stdio.h> //sprintf()
//end OpenCV Libraries


#include "Buttons.h"
#include "ArduinoSerial.h"

int i = 0;
int fd;

using namespace std;
using namespace cv;

Mat plantilla;
Mat camera, camera_small;


void buttonCallBackLedOff(int state, void *){
// buttons initial value is 1 or when the button is not pressed it is 1
// if the button changes state which means it is pressed send a 0 to the port to turn led off
// I want to drive LED13 pin low to turn off the led via a serial comm
	if(state != 1){
		cout << " The button has been pressed" << endl;
		cout << " Turning LED OFF . . . " << endl;
		putText(plantilla, "LED ON", Point(53,266), FONT_HERSHEY_PLAIN, 2, Scalar(255,255,255), 1);
		putText(plantilla, "LED OFF", Point(53,266), FONT_HERSHEY_PLAIN, 2, Scalar(0,255,0), 1);
		serialport_writebyte(fd, 0); // initial value of the button is 1
	}
}


void buttonCallBackLedOn(int state, void *){
// I want to drive LED13 pin high to turn on the led via a serial comm
	if(state != 1){
		cout << " The button has been pressed" << endl;
		cout << " Turning LED ON . . . " << endl;
		putText(plantilla, "LED OFF", Point(53,266), FONT_HERSHEY_PLAIN, 2, Scalar(255,255,255), 1);
		putText(plantilla, "LED ON", Point(53,266), FONT_HERSHEY_PLAIN, 2, Scalar(255,0,0), 1);
		serialport_writebyte(fd, 1);
	}
}


void buttonCallBackSave(int state, void *){
	if(state != 1){
		char imagen[11];
		while(1){
			cout << " The button has been pressed" << endl;
			cout << " Saving.... " << endl;
			sprintf ( imagen, "Imagen%d.png",i);
			i++;
			imwrite( imagen, camera);
			puts(imagen);
			break;
		}// End While
	}// End If
}// End buttonCallBackSave

	
int main(void){

    /*  START serial port declarations */	
	fd = serialport_init("/dev/ttyACM0", B9600);
	/* END serial port declarations */
	
	VideoCapture cam(0);
	
	if( !cam.isOpened() )
		return -1;
	
	plantilla = imread("Plantilla.png", CV_LOAD_IMAGE_COLOR);
	namedWindow("Sistema");
	
	
	// puts text in a namedWindow box
	//void putText( Mat& img, const string& text, Point org, int fontFace, double fontScale, Scalar color,int thickness=1, int lineType=8, bool     bottomLeftOrigin=false )
	
//	int createButton( const string& bar_name, ButtonCallback on_change, void* userdata=NULL, inttype=CV_PUSH_BUTTON, bool initial_button_state=0 )

	createButton("LED OFF",buttonCallBackLedOff,NULL,CV_PUSH_BUTTON,1);
	createButton("LED ON",buttonCallBackLedOn,NULL,CV_PUSH_BUTTON,1);
	
	createButton("Save",buttonCallBackSave,NULL,CV_PUSH_BUTTON,1);
	putText(plantilla, "Practica5", Point(30,30), FONT_HERSHEY_PLAIN, 2, Scalar(0,255,0), 1, CV_AA);
	putText(plantilla, "adc0:", Point(301,270), FONT_HERSHEY_PLAIN, 2, Scalar(0,255,0), 1, CV_AA);
	//setMouseCallback("Sistema", cuandoElRatonSeMueve, 0);	
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
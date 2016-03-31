
/*
g++ -Wall -o salida E7_8.cpp `pkg-config --cflags --libs opencv`

*/

#include<iostream>

#include<opencv2/core/core.hpp>
#include<opencv2/ml/ml.hpp>
#include<opencv/cv.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include <stdio.h>    
#include <stdlib.h> 
#include <stdint.h>   
#include <string.h>   
#include <unistd.h>   
#include <fcntl.h>   
#include <errno.h>    
#include <termios.h>  
#include <sys/ioctl.h>
#include <getopt.h>

using namespace std;

using namespace cv;

Mat plantilla = imread("Plantilla.png",CV_LOAD_IMAGE_COLOR);

int estado1=0, estado2=0;

static void onMouse( int event, int x, int y, int, void* )
{
	switch(event)
	{
	case CV_EVENT_LBUTTONDOWN:    
	
		if((x > 15) && (x<133) && (y > 179 ) && (y<240)) {
			estado2 = 0;
			estado1 = 1;	
			 }

		if((x > 146) && (x<264) && (y > 177 ) && (y<240)) {
			estado1 = 0;
			estado2 = 1;	
			 }

			
			
		break;
	
	}
}


int main(void)
{
	Mat img;	
	Mat img_ch;
	namedWindow("Practica5");
	setMouseCallback( "Practica5", onMouse, 0 );
	
	VideoCapture Local210(0);

	if(!Local210.isOpened()) return -1;

	//Region Of Interest
	//Rect roi(Point(466,12), Size(320, 240));

	
	Rect camara_reducida(Point(279,7), Size(320, 240));

	while(1)
	{
		Local210 >> img;

		if(estado1 == 1)
		{
			cvtColor(img, img, CV_BGR2HSV);
			
			estado2 = 0;
		}
		if(estado2 == 1)
		{
			
			
			estado1 = 0;
		}
		
		
		resize(img, img_ch, Size(320, 240), 0, 0, INTER_CUBIC);
		//imshow("IMagenReducida", img_ch);
		img_ch.copyTo(plantilla(camara_reducida));
	
		imshow("Practica5", plantilla);
		//if(waitKey(30)>0) break;


		if(waitKey(30)>0) break;


	}
	
}
	



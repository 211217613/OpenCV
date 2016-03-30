
/*
g++ -Wall -o salida E7_4.cpp `pkg-config --cflags --libs opencv`

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


static void CuandoELRatonSeMueve( int event, int x, int y, int, void* )
{
	
}


int main(void)
{
	namedWindow("Practica5");
	while(1)
	{
		imshow("Practica5", plantilla);
		//if(waitKey(30)>0) break;
		if(waitKey(30)=='r') break;


	}
	
}
	



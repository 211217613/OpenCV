
/*
g++ -Wall -o salida E6_1.cpp `pkg-config --cflags --libs opencv`

*/


/*
EVENT_MOUSEMOVE      	-- Cualquier movimiento del mouse
EVENT_LBUTTONDOWN    	-- Click izquierdo al precionarlo
EVENT_RBUTTONDOWN	-- CLick derecho al precionarlo
EVENT_MBUTTONDOWN	-- CLick scroll al precionarlo
EVENT_LBUTTONUP		-- CLick izquierdo al soltarlo
EVENT_RBUTTONUP		-- Click derecho al soltarlo
EVENT_MBUTTONUP		-- CLick scroll al soltarlo
EVENT_LBUTTONDBLCLK	-- Doble click izquierdo
EVENT_RBUTTONDBLCLK	-- Doble click derecho
EVENT_MBUTTONDBLCLK	-- Doble ciick del scroll

x			-- Coordenada x 
y			-- Coordenada y

*/

#include<iostream>

#include<opencv2/core/core.hpp>
#include<opencv2/ml/ml.hpp>
#include<opencv/cv.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

using namespace cv;


double cuenta = 0;


static void CuandoElMouseSeMueva( int event, int x, int y, int, void* )
{
	if (CV_EVENT_LBUTTONDBLCLK > Point(40,50) && CV_EVENT_LBUTTONDBLCLK < Point(359,289) ){
		cout << "Hello" << endl;
	}
	
}

int main(void)
{
	Mat Imagen;
	
	namedWindow("Color");
	
    setMouseCallback( "Color", CuandoElMouseSeMueva, 0 );

	VideoCapture camweb(0);

	if(!camweb.isOpened())  return -1;
	
	camweb >> Imagen;

	imshow("Color", Imagen);

	while(1){
	  if(waitKey(30)=='c')
	  break;
	}
	
}

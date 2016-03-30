
/*
g++ -Wall -o salida E4_5.cpp `pkg-config --cflags --libs opencv`

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


int valor=0;
int PEPSI=0;

void si_se_mueve(int, void* = NULL) 
{ 
 	cout << "El valor de la barra es: " << valor<<endl;
} 
void libro(int, void* = NULL) 
{ 
 	cout << "El valor de la barra es: " << PEPSI<<endl;
} 

int main(void)
{
	namedWindow("opencv");
	

	createTrackbar("Barra1", "opencv", &valor, 512, si_se_mueve);
	createTrackbar("BARA_LIBRE","opencv",&PEPSI, 4, libro);

	
	while(1)
	{	
		
	
		if(waitKey(30)>0) break;
	}
	

	

}

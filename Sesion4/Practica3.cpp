
/*
g++ -Wall -o salida Practica3.cpp `pkg-config --cflags --libs opencv`

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

int main(void)
{
	Mat Imagen;
	 int option = 0;

	VideoCapture cap(0);

	if(!cap.isOpened())	return -1;
	cout << "Choose one of the following options\n ";
    cout << "(1) Filtro 2D" << endl;
    cout << "(2) GaussianBlur" << endl;
    cout << "(3) blur" << endl;
    cout << "(4) blur + HSV" << endl;
    cout << "(5) blur + GRAY" << endl;
    cout << "(6) erode + blur + GaussianBlur + HSV" << endl;
    cin >> option;

	while(1)
	{
		cap >> Imagen;


		switch ( option ){
			case 1:
			//void filter2D(InputArray src, OutputArray dst, int ddepth, InputArray kernel, Point anchor=Point(-1,-1), double delta=0, int borderType=BORDER_DEFAULT )
          filter2D(Imagen, Imagen, 16 , Mat());
            break;
			case 2: GaussianBlur(Imagen, Imagen, Size(5, 5),0,0);
                    break;

			case 3:blur(Imagen, Imagen, Size(50,50), Point(-1,-1));
                   break;

			case 4:blur(Imagen, Imagen, Size(50,50), Point(-1,-1));
                   cvtColor(Imagen, Imagen, CV_BGR2HSV);
                   break;

			case 5:blur(Imagen, Imagen, Size(50,50), Point(-1,-1));
                   cvtColor(Imagen, Imagen, CV_BGR2GRAY);
                   break;

			case 6:erode(Imagen, Imagen, Mat(), Point(-1, -1), 10, 1, 1);
                   blur(Imagen, Imagen, Size(50,50), Point(-1,-1));
                   GaussianBlur(Imagen, Imagen, Size(5, 5),0,0);
                   cvtColor(Imagen, Imagen, CV_BGR2HSV);
                   break;

            default:
                cout << " Whats going on \n";
                break;

		}


		imshow("Camara 1", Imagen);
		if(waitKey(30)>0) break;
	}




}

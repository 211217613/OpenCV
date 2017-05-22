#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;
using namespace cv;
int Sepia = 0, BW = 0, Saturation = 0, Color1 = 0, Color2 = 0, Color3 = 0, Save = 0;

/*
(1) Sepia
(2) B/W
(3) Saturacion
(4) Color1
(5) Color2
(6) Color5
(7) Guardar a la imagen (8.png).

void Foo(int,void*);
*/	

void trackbarCallBack1(int value, void *){
	if(value > 0)
		Sepia  = value;
}

void trackbarCallBack2(int value, void *){
	if(value > 0)
		BW  = value;
}
void trackbarCallBack3(int value, void *){
	if(value > 0)
		Saturation  = value;
}
void trackbarCallBack4(int value, void *){
	if(value > 0)
		Color1  = value;
}
void trackbarCallBack5(int value, void *){
	if(value > 0)
		Color2  = value;
}
void trackbarCallBack6(int value, void *){
	if(value > 0)
		Color3  = value;
}
void trackbarCallBack7(int value, void *){
	if(value > 0)
		Save  = value;
}


int main(){
	
	Mat Imagen, Img_HSV, Img_Filtrada, Img_Filtro_Color;

	VideoCapture camweb(-1);
	namedWindow("Barras");


	// Mat Sat, ch2, ch3;
	// // "channels" is a vector of 3 Mat arrays:
	// vector<Mat> channels(3);
	// // split img:

	vector<Mat> layers;
	
	
	// // get the channels (dont forget they follow BGR order in OpenCV)
	// Sat = channels[0];
	// ch2 = channels[1];
	// ch3 = channels[2];
	
	
	//int createTrackbar( const string& trackbarname, const string& winname, int* value, int count,TrackbarCallback onChange=0, void* userdata=0 )
	createTrackbar("Sepia","Barras", &Sepia, 255, trackbarCallBack1, NULL);
	createTrackbar("B/W","Barras", &BW, 255, trackbarCallBack2, NULL);
	createTrackbar("Saturation","Barras", &Saturation, 255, trackbarCallBack3, NULL);
	createTrackbar("Color 1","Barras", &Color1, 255,trackbarCallBack4, NULL);
	createTrackbar("Color 2","Barras", &Color2, 255, trackbarCallBack5, NULL);
	createTrackbar("Color 3","Barras", &Color3, 255, trackbarCallBack6, NULL);
	createTrackbar("Save Image","Barras", &Save, 1, trackbarCallBack7, NULL);

	//createTrackbar("4", "Practica6", &slider, slider_max,on_trackbar4);

	
	// Verify the camera opened correctly, if not, terminate the program
	if( !camweb.isOpened() ){
		return -1;
	}

	while(1){

		camweb >> Imagen;
		cvtColor(Imagen, Img_HSV, CV_RGB2HSV);
		/*  C++: void mixChannels( const Mat* src, size_t nsrcs, Mat* dst, size_t ndsts, const int* fromTo, size_tnpairs )
			C++: void mixChannels( const vector<Mat>& src, vector<Mat>& dst, const int* fromTo, size_t npairs )  
		 */
		//mixChannels(Imagen,)

		split(Img_HSV, layers);
		imshow("layer 0", layers[0]);
		imshow("layer 1",layers[1]);
		//imshow("layer 2", layers[2]);
		//split(Imagen, channels);
		
		imshow("Barras", Imagen);       
		
		// stop and wait for a key stroke
		// has to be used after imshow for the image to be drawn
		if( waitKey(15) > 0)
		break;
	}

	return 0;
}

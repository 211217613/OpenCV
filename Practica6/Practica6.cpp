//g++ Practica6.cpp -o Practica6 `pkg-config --cflags --libs opencv` 
/* OPENCV Libraries begin*/
#include <opencv2/core/core.hpp> 
#include <opencv2/ml/ml.hpp> 
#include <opencv/cv.h> 
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/highgui/highgui.hpp>
/* OPENCV Libraries end*/ 
#include <iostream> 
#include <cv.h> 
#include <highgui.h>
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <termios.h> 

#include "Serial.h"

using namespace std; 
using namespace cv;
 
const int train_samples = 1, maxRoi = 300; 
const int classes = 5; 
const int sizex = 300; 
const int sizey = 400; 
const int ImageSize = sizex * sizey; 
const int xDim = 640, yDim = 300;
int slider_pos1, slider_pos2, slider_pos3, slider_pos4;
char pathToImages[] = "images1"; 
unsigned char c; 
// Sirve para pre-procesar a la imagen de tal manera que la adapta al tamaño de las imagenes imagenes originales con las que se calibra el programa 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//Callback function fortrackbar event
void on_trackbar1(int pos,void *){
	if(pos > 0)
		slider_pos1  = pos;
}

void on_trackbar2(int pos,void *){
	if(pos > 0)
		slider_pos2  = pos;
}

void on_trackbar3(int pos,void *){
	if(pos > 0)
		slider_pos3  = pos;
}

void on_trackbar4(int pos,void *){
	if(pos > 0)
		slider_pos4  = pos;
}



void PreProcessImage(Mat *inImage,Mat *outImage,int sizex, int sizey){
	 Mat grayImage,blurredImage,thresholdImage,contourImage,regionOfInterest; 
	 vector<vector<Point> > contours; 
	 cvtColor(*inImage,grayImage , COLOR_BGR2GRAY); 
	 GaussianBlur(grayImage, blurredImage, Size(5, 5), 2, 2); 
	 adaptiveThreshold(blurredImage, thresholdImage, 255, 1, 1, 11, 2); 
	 thresholdImage.copyTo(contourImage);  

	 findContours(contourImage, contours, RETR_LIST, CHAIN_APPROX_SIMPLE); 
	 int idx = 0; 
	 size_t area = 0; 
	 for (size_t i = 0; i < contours.size(); i++){ 
		if (area < contours[i].size() ){ 
			 idx = i; 
			 area = contours[i].size(); 
     	 } 
	 } 
	 Rect rec = boundingRect(contours[idx]); 
	 regionOfInterest = thresholdImage(rec); 
	 resize(regionOfInterest,*outImage, Size(sizex, sizey)); 
} 
////////////////////////////////////////////////////////////////////////////////////////////////// 
//sirve para entrenar al programa con las imagenes originales 
void LearnFromImages(CvMat* trainData, CvMat* trainClasses){ 
	 Mat img; 
	 char file[255]; 
	 for (int i = 0; i < classes; i++){ 
		 sprintf(file, "%s/%d.png", pathToImages, i); 
		 img = imread(file, 1); 
		 if (!img.data){ 
			cout << "File " << file << " not found\n";  
			exit(1); 
		 } 
		 Mat outfile; 
		 PreProcessImage(&img, &outfile, sizex, sizey); 
		 for (int n = 0; n < ImageSize; n++){ 
			trainData->data.fl[i * ImageSize + n] = outfile.data[n]; 
		 } 
		 trainClasses->data.fl[i] = i; 
	 } 
} 
int main(int argc,char** argv){ 
	int fd;
	/*  START serial port declarations */	
	fd = serialport_init("/dev/ttyACM0", B9600);
	/* END serial port declarations */

	int slider_max1 = 70, slider_max = 255, slider = 0;
	//Creates OpenCV objects for storing 
	Mat imagen, imagenGray, imagenHSV, HSVblur, YUVblur, color, color2, imagen_contornos, staged_image, imagen_file; 
	Mat plantilla = imread("plantilla.png"), camara_small;

	//Rect rect(Point(560, 0), Size(xDim, yDim));
	Rect rect1(Point(0,0), Size(300,400));
	cout << "DEBUG 2" << endl;
	namedWindow("Practica6", WINDOW_NORMAL);
	createTrackbar("1", "Practica6", &slider, slider_max1,on_trackbar1);
	createTrackbar("2", "Practica6", &slider, slider_max,on_trackbar2);
	createTrackbar("3", "Practica6", &slider, slider_max,on_trackbar3);
	createTrackbar("4", "Practica6", &slider, slider_max,on_trackbar4);

	
	//putText(plantilla, "Practica6", Point(300, 30), FONT_HERSHEY_PLAIN, 2, Scalar(0,255,0), 1, CV_AA);
	

	VideoCapture camara(0); 
	if(!camara.isOpened())
	 return -1; 

	CvMat* sample2 = cvCreateMat(1, ImageSize,CV_32FC1); 
	
	Rect rec; 
	CvMat* trainData = cvCreateMat(classes * train_samples,ImageSize, CV_32FC1); 
	CvMat* trainClasses = cvCreateMat(classes * train_samples, 1, CV_32FC1); 
	LearnFromImages(trainData, trainClasses); 
	KNearest knearest(trainData, trainClasses); 

	vector<vector<Point> > contornos;// arreglo de arreglos 
	Mat image(480,640, CV_8UC3, Scalar(0,0,0)), imagen_small; 

	for(;;){ 

		camara >> imagen;
		//cvtColor(imagen,imagenGray,CV_BGR2GRAY); //imagenGray 
		//imshow("GRAY",imagenGray); 
		 // ALL COLOR INFO STORED IN UV CHANNELS && ARE INVARIANT TO ILL AND BRIGHTNESS Y STORES ILLUMINATION
		cvtColor(imagen,imagenHSV,CV_BGR2HSV); 
		GaussianBlur(imagenHSV,HSVblur,Size(45,45),2,2); 


		//resize(imagen, camara_small, Size(xDim, yDim), 0, 0, INTER_CUBIC);
		//resize(imagenHSV, imagen_small, Size(300, 400), 0, 0, INTER_CUBIC);
		
		//imagen_small.copyTo(plantilla(rect1));
	//  inRange(src    , srcLB(00,109,86)                           ,srcUB(145,255,255)                         ,dst )	  
		inRange(imagenHSV, Scalar(00,03,140),Scalar(49,255,255),color); // filter 
		
		adaptiveThreshold(color,color2,255,1,1,11,2); 
		imshow("Practica6", color2);

		////////////////////////////////////////////////////////////////////// 
		
		color2.copyTo(imagen_contornos);
		imwrite("contorno.png",imagen_contornos); 
		imagen_file=imread("contorno.png",1); 

//		findContours(InputOutputArray image, OutputArrayOfArrays contours, int mode, int method,Point offset=Point() )
		findContours(imagen_contornos      ,contornos                    ,RETR_LIST, CHAIN_APPROX_SIMPLE); 
	//	imshow("imagen_contornos", imagen_contornos);
		///////////////////////////////////////////////////////////////////// 
		 
		 //se inicia ciclo for para instruccion de contornos
		for (size_t i=0; i < contornos.size(); i++){ 
			//cout << "DEBUG: Entering first for" << endl;
			vector < Point > cnt =contornos [i]; //guarda la posicion de contornos en la iteracion de contornos 
			//Calcula el area de cada contorno superior a los 100 pixeles
			if(contourArea(cnt) > maxRoi){ 
				//cout << "DEBUG: Entering first if" << endl;
				//cout << "contourArea " << contourArea(cnt) << endl;
				rec = boundingRect(cnt); //se rodea con un rectangulo a los contornos encontrados 
				//cout << "rec.height " << rec.height << endl;
				if(rec.height > 50){ 
					Mat roi = imagen_file(rec); 
					Mat stagedImage; 
					PreProcessImage(&roi, &stagedImage, sizex, sizey);  
					for (int n = 0; n < ImageSize; n++){ 
					  sample2->data.fl[n] = stagedImage.data[n]; 
					} 
					int result = knearest.find_nearest(sample2, 1); 
					char clear = '5';

					switch (result){
						case 0: cout << "R" << endl;
							serialport_writebyte(fd, clear);
							serialport_writebyte(fd, '0');
							break;
						case 1: cout << "U" << endl;
							serialport_writebyte(fd, clear);
							serialport_writebyte(fd, '1');
							break;
						case 2: cout << "B" << endl;
							serialport_writebyte(fd, clear);
							serialport_writebyte(fd, '2');
							break;
						case 3: cout << "E" << endl;
							serialport_writebyte(fd, clear);
							serialport_writebyte(fd, '3');
							break;
						case 4: cout << "N" << endl;
							serialport_writebyte(fd, clear);
							serialport_writebyte(fd, '4');
							break;
						default: serialport_writebyte(fd, clear);
					}
					
					imshow("Detected Image", stagedImage); 
					//imshow("contorno1",roi);  
					rectangle(image,Point(rec.x,rec.y),Point(rec.x + rec.width, rec.y + rec.height), Scalar(0,0,255),2); 
					i=contornos.size()+1; 	  
				}  
			} 
		} 
		if(waitKey(30)>=0){
			camara.release();
			destroyAllWindows();
			break;
		} 
	} 
	return 0; 
} //end main
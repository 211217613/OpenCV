
/*
g++ -Wall -o salida E5_3.cpp `pkg-config --cflags --libs opencv`

*/

#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>




using namespace std;

using namespace cv;


int A_min;
int A_max;

int B_min;
int B_max;

int C_min;
int C_max;

int VAR1;
int main(void)
{
	/* Funcion que permite crear una ventana llamada Barras*/
	namedWindow("Barras");

	/* 

	Funcion que crea una barra de desplazamiento
	que se llama: VARIABLE1, dentro de la ventana Barras.
	El valor de la barra de desplazamiento se guarda en la variable VAR1.
	Cual es el valor maximo que podria tomar la VAR1: 65536
	Cual es el valor maximo que podria tomar la barra: 255
	Que sucedera si la barra se desplaza: cambia el valor de VAR1 y no se
	llama a ninguna funcion.


	*/
	createTrackbar("VARIABLE1", "Barras", &VAR1, 255, NULL);
	createTrackbar("A_min","Barras", &A_min, 255, NULL);
	createTrackbar("A_max","Barras", &A_max, 255, NULL);

	createTrackbar("B_min","Barras", &B_min, 255, NULL);
	createTrackbar("B_max","Barras", &B_max, 255, NULL);

	createTrackbar("C_min","Barras", &C_min, 255, NULL);
	createTrackbar("C_max","Barras", &C_max, 255, NULL);
	
	
	/*
	Declaracion de 4 matrices donde se guardaran a las imagenes de la 		camara web o del resultado de aplicar filtros digitales.	
	*/
	Mat Imagen, Img_HSV, Img_Filtrada, Img_Filtro_Color;

	/*
	Genera un objeto llamada camweb, que toma el recurso de la 
	camara web 0.
	*/
	VideoCapture camweb(0);

	/*
	Asegura que camara web este habilitada correctamente, en caso de 
	no estar disponible (apagada o desconectada) el programa se cierra
	automaticamente. 
	*/

	if(!camweb.isOpened())  return -1;
	
	/*Ciclo repetito principal*/
	while(1)
	{
		/*
			Asignar la imagen de la camara web 0 a la matriz 
			Imagen.
		*/
		camweb >> Imagen;

		/*
			Muestra a la matriz anterior, en una ventana 
			llamada "Original".

		*/
		//imshow("Original", Imagen);

		/*
			Convierte a la imagen original al espacio de color HSV
			y guarda la conversion en la matriz Img_HSV.

		*/
		cvtColor(Imagen, Img_HSV, CV_BGR2HSV);
		//imshow("HSV", Img_HSV);

		/*

			APlica un filtro digital gaussiano a la imagen
			Img_HSV y guarda el resultado en la matriz 
			IMg_Filtrada. Las caracteristicas del filtro es>
			ventana de 31 x 31 pixeles con una 
			varianza automatica.
		*/
		
		GaussianBlur(Img_HSV, Img_Filtrada, Size(7, 7),0,0);
		//imshow("Filtro Gaussiano ", Img_Filtrada);

		inRange(Img_Filtrada, Scalar(A_min, B_min, C_min), Scalar(A_max, B_max, C_max), Img_Filtro_Color);
		imshow("Color", Img_Filtro_Color);

		/*
		WaitKey es una funcion que espera un tiempo definido
		por el usuario a que introduzca una tecla especifica o como 
		en este ejemplo, cualquier tecla, la espera durante 30ms. SI 
		el usuario precionase una tecla, la instruccion siguiente 
		rompe al ciclo while y por lo tanto termina al programa.


		*/
		if(waitKey(30)=='c') break;
	}
}
/*

g++ operacion.cpp -o plot

*/
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>

#define PI 3.141595


using namespace std;

unsigned int Muestras = 200;
int Amplitud = 0;
int Frecuencia = 0;
int operacion = 0;
double Tiempo[1000];



int main(int argc, char **argv)
{
	double x = 0.0;
	double z = 0.0;
	if(argc>3)
	{
		Amplitud = atoi(argv[1]);
		Frecuencia = atoi(argv[2]);
		operacion = atoi(argv[3]);
	}
	ofstream file("data.dat");
	file << "#x y" << endl;

	x = 0.0;

	for(int i=0; i<1000; i++)
	{
		Tiempo[i] = x;
		x = x+0.001;
	}
switch(operacion)
		{
		case 0:
			for(int i=0; i<1000; i++)
			{
				file << Tiempo[i] << ' ' << Amplitud*sin(PI*Frecuencia*Tiempo[i]) << endl;
			}
			file.close();
		break;
		case 1:
			for(int i=0; i<1000; i++)
			{
				file << Tiempo[i] << ' ' << Amplitud*cos(PI*Frecuencia*Tiempo[i]) << endl;
			}
			file.close();
		break;
		case 2:
			for(int i=0; i<1000; i++)
			{
				file << Tiempo[i] << ' ' << (Frecuencia*Tiempo[i])+Amplitud << endl;
			}
			file.close();
		break;
		case 3:
			for(int i=0; i<1000; i++)
			{
				file << Tiempo[i] << ' ' << pow(Tiempo[i], Frecuencia)<< endl;
			}
			file.close();

		break;
}
			return 0;
}

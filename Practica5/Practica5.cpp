/*
g++ -Wall -o salida practica5.cpp `pkg-config --cflags --libs opencv`
*/

#include<iostream>

// OpenCV libraries
#include<opencv2/core/core.hpp> // core data structures, data types and memory management
#include<opencv2/ml/ml.hpp> // statistical models and clasification algorithms
#include<opencv/cv.h>
#include<opencv2/imgproc/imgproc.hpp>  // image filtering, 
#include<opencv2/highgui/highgui.hpp> //GUI, reading and writing images and video
#include <stdlib.h>
#include <stdio.h> //sprintf()

//serial IO libraries
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
int i = 0;
using namespace std;
using namespace cv;

//*******************************************************
//Serial initialization
int serialport_init(const char* serialport, int baud);

int serialport_writebyte(int fd, uint8_t b);

int serialport_write(int fd, const char* str);
//********************************************************
Mat plantilla;
Mat camera, camera_small;

// Function prototypes
void buttonCallBackLedOff(int state, void *);
void buttonCallBackLedOn(int state, void *);

void buttonCallBack(int state, void *){

	switch(state){
		case 0:
			cout << " The button has been pressed" << endl;
			break;
		case 1:
			cout << " The button has been depressed" << endl;
			break;
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

int fd;
	
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

//********************************************************************************************************

int serialport_init(const char* serialport, int baud){

    struct termios toptions;

    int fd;
   

    //fprintf(stderr,"init_serialport: opening port %s @ %d bps\n",

    //        serialport,baud);



    //fd = open(serialport, O_RDWR | O_NOCTTY | O_NDELAY);

    fd = open(serialport, O_RDWR | O_NOCTTY);

    if (fd == -1)  {

        perror("init_serialport: Unable to open port ");

        return -1;

    }

    

    if (tcgetattr(fd, &toptions) < 0) {

        perror("init_serialport: Couldn't get term attributes");

        return -1;

    }

    speed_t brate = baud; // let you override switch below if needed

    switch(baud) {

    case 4800:   brate=B4800;   break;

    case 9600:   brate=B9600;   break;

// if you want these speeds, uncomment these and set #defines if Linux

//#ifndef OSNAME_LINUX

//    case 14400:  brate=B14400;  break;

//#endif

    case 19200:  brate=B19200;  break;

//#ifndef OSNAME_LINUX

//    case 28800:  brate=B28800;  break;

//#endif

    //case 28800:  brate=B28800;  break;

    case 38400:  brate=B38400;  break;

    case 57600:  brate=B57600;  break;

    case 115200: brate=B115200; break;

    }

    cfsetispeed(&toptions, brate);

    cfsetospeed(&toptions, brate);



    // 8N1

    toptions.c_cflag &= ~PARENB;

    toptions.c_cflag &= ~CSTOPB;

    toptions.c_cflag &= ~CSIZE;

    toptions.c_cflag |= CS8;

    // no flow control

    toptions.c_cflag &= ~CRTSCTS;



    toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines

    toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl



    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw

    toptions.c_oflag &= ~OPOST; // make raw



    // see: http://unixwiz.net/techtips/termios-vmin-vtime.html

    toptions.c_cc[VMIN]  = 0;

    toptions.c_cc[VTIME] = 20;

    

    if( tcsetattr(fd, TCSANOW, &toptions) < 0) {

        perror("init_serialport: Couldn't set term attributes");

        return -1;

    }
    return fd;
}

int serialport_write(int fd, const char* str){

    int len = strlen(str);

    int n = write(fd, str, len);

    if( n!=len ) 
        return -1;
    return n;
}

int serialport_writebyte( int fd, uint8_t b){

    int n = write(fd,&b,1);

    if( n != 1)
        return -1;
    return 0;
}


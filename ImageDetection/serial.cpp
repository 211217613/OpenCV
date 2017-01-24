/*  http://todbot.com/arduino/host/arduino-serial/arduino-serial.c */

#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
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

// TODO: remove namespaces
// TODO: rename cpp
// TODO: seperate functionality into different files
// TODO: use cmake
using namespace std;
using namespace cv;

/*
Plantilla 3: SOn los elementos basicos que permiten comunicar al arduino y linux mediante el puerto de comuncacion serial.
Contiene 3 funciones:

 serialport_init -> inicializar el puerto serial con dos parametros de entrada, el puerto y la velocidad.

	serialport_writebyte -> escribir un byte (0-255) en puerto serial indicado por la variable fd.

TTYACM0   TTYACM1
 COM1       COM2   

serialport_write -> escribir una cadena de caracteres en puerto serial indicado por la variable fd.


*/
int serialport_init(const char* serialport, int baud);

int serialport_writebyte(int fd, uint8_t b);

int serialport_write(int fd, const char* str);

int serialport_read_until(int fd, char* buf, char until);

// From other file...keeping here to see whats good
// int main(void){
//     int fd = 0;
//     int rc = 0;
//     char dato[3] ={'1','1','1'};


//     fd = serialport_init("/dev/ttyACM0", B9600);

//     if(fd == -1) return -1; // Si no se abre el puerto termina el program

//         usleep(3000 * 1000 );    // Retardo de 3,000,000 us = 3s

//     rc = serialport_write(fd, dato);
//     if(rc==-1) return -1;

//     rc = serialport_writebyte(fd, 'A');
//     if(rc==-1) return -1;

//     close(fd);
//     exit(EXIT_SUCCESS);    
// }

int main(void){
	int fd = 0;
	int opc;
    char comando;
    char numero[20];
	char dato[30] = {};
	//char c[30]={};
	//char escribe[30]={};
    //TODO: better error handling of serial port connections
	fd = serialport_init("/dev/ttyACM0", B9600);

 	if(fd == -1) return -1; // Si no se abre el puerto termina el program
        usleep(3000 * 1000 );	 // Retardo de 3,000,000 us = 3s
    for(;;){
		std::fflush(stdout);     
		fflush(stdin); 
        serialport_read_until(fd, dato, 0x0A);  
        std::cout << dato <<  endl;
        std::cout << "Selecciona una opcion" << endl;
        std::cout << "0 enviar operacion, 1 enviar numero : ";
        std::cin >> opc;
		switch(opc){
			case 0:
				 std::cout << "Ingresa la operacion: *, +, % " ;
				 std::cin >> comando;
			         serialport_writebyte(fd, comando);
				 break;
			case 1:
				 std::cout << "Ingresa el numero" ;
				 std::cin >> numero;
			         serialport_write(fd, numero);
				 break;
			case 2:
				return 1;
			default:
				std::cout << "Error" << endl;

		}
               
		if(waitKey(30)>0) break;	
    }
	close(fd);
	exit(EXIT_SUCCESS);    
}


int serialport_init(const char* serialport, int baud){
    struct termios toptions;
    int fd;
    fd = open(serialport, O_RDWR | O_NOCTTY);
    if (fd == -1){
        perror("init_serialport: Unable to open port ");
        return EXIT_FAILURE; // TODO: use exit status
    }

    
    if (tcgetattr(fd, &toptions) < 0){
        perror("init_serialport: Couldn't get term attributes");
        return -1; // TODO: use exit status
    }

    speed_t brate = baud; // let you override switch below if needed
    switch(baud) {
        case 4800:   brate=B4800;   break;
        case 9600:   brate=B9600;   break;

        case 19200:  brate=B19200;  break;
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
    toptions.c_cflag &= ~CRTSCTS;
    toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    toptions.c_oflag &= ~OPOST; // make raw
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
    if( n!=1)
        return -1;
    return 0;
}

int serialport_read_until(int fd, char* buf, char until){
    char b[1];
    int i=0;
    do { 
        int n = read(fd, b, 1);  // read a char at a time
        if( n==-1) return -1;    // couldn't read
        if( n==0 ) {
            usleep( 10 * 1000 ); // wait 10 msec try again
            continue;
        }
        buf[i] = b[0]; i++;
    } while( b[0] != until );

    buf[i] = 0;  // null terminate the string
    return 0;
}
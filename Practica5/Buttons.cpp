#include <iostream>

// OpenCV libraries
#include <opencv2/core/core.hpp> // core data structures, data types and memory management
#include <opencv2/ml/ml.hpp> // statistical models and clasification algorithms
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>  // image filtering, 
#include <opencv2/highgui/highgui.hpp> //GUI, reading and writing images and video
//end OpenCV Libraries

#include <stdlib.h>
#include <stdio.h> //sprintf()


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
// SERIAL headers

#include <opencv2/highgui/highgui.hpp> //GUI, reading and writing images and video

#include "Serial.h"

int fd;

extern Mat plantilla, camera, camera_small;


void buttonCallBackLedOff(int state, void *){
// buttons initial value is 1 or when the button is not pressed it is 1
// if the button changes state which means it is pressed send a 0 to the port to turn led off
// I want to drive LED13 pin low to turn off the led via a serial comm
	if(state != 1){
		std::cout << " The button has been pressed" << endl;
		std::cout << " Turning LED OFF . . . " << endl;
		cv::putText(plantilla, "LED ON", Point(53,266), FONT_HERSHEY_PLAIN, 2, Scalar(255,255,255), 1);
		cv::putText(plantilla, "LED OFF", Point(53,266), FONT_HERSHEY_PLAIN, 2, Scalar(0,255,0), 1);
		serialport_writebyte(fd, 0); // initial value of the button is 1
	}
}

void buttonCallBackLedOn(int state, void *){
// I want to drive LED13 pin high to turn on the led via a serial comm
	if(state != 1){
		std::cout << " The button has been pressed" << endl;
		std::cout << " Turning LED ON . . . " << endl;
		cv::putText(plantilla, "LED OFF", Point(53,266), FONT_HERSHEY_PLAIN, 2, Scalar(255,255,255), 1);
		cv::putText(plantilla, "LED ON", Point(53,266), FONT_HERSHEY_PLAIN, 2, Scalar(255,0,0), 1);
		serialport_writebyte(fd, 1);
	}
}

void buttonCallBackSave(int state, void *){
        int image_index = 0;
	if(state != 1){
		char imagen[11];
		while(1){
			std::cout << " The button has been pressed" << endl;
			std::cout << " Saving.... " << endl;
			sprintf(imagen, "Imagen%d.png", image_index);
			i++;
			cv::imwrite( imagen, camera);
			puts(imagen);
			break;
		}// End While
	}// End If
}// End buttonCallBackSave

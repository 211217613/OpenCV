int main(){
	
	// Declare  Imagen of type Mat: Mat is a CV object where images are stored
	Mat Imagen;
	
	// Create an object cap(0) of type VideoCapture
	VideoCapture cap(0);
	
	if( !cap.isOpened() ){
		return -1;
	}
	
	while(1){
		cap >> Imagen;
		
		cvtColor(Imagen, Imagen, CV_RGB2HSV);
		
		GaussianBlur(Imagen, Imagen, Size(7, 7), 0, 0);
		
		// es el rango a trabajar
		inRange(Imagen, Scalar(50,50,50), Scalar(90,90,90), Imagen);
		
		// display Imagen and title window Camera1
		imshow("Camera1", Imagen)
		
		if( waitKey(15) > 0 ){
			break;
		}
	}
	
}

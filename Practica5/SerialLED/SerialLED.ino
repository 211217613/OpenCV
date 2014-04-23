#define LEDPIN  13
int inputByte = 0;
void setup(){
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, HIGH);
  if(!Serial){ 
   Serial.println("Serial port not ready");
  }
  else{
    Serial.println("serial port ready");
  }
}

void loop(){
  
  int serialData = Serial.available();
  int ledStatus = digitalRead(LEDPIN);
  int adc0 = analogRead(A0);
  //Serial.println(adc0);
  //delay(1000);
  
  
  // read serial port data going to send b1 or b0
  if(serialData > 0){
    Serial.print("Led Status is: ");
    Serial.println(ledStatus);
    inputByte = Serial.read();
    Serial.print("Bytes waiting in buffer: ");
    Serial.println(serialData);
    Serial.print("inputByte is: ");
    Serial.println(inputByte);
    if( inputByte == 1 ){
      digitalWrite(LEDPIN, HIGH);
      Serial.println(inputByte);
     }
    else{
      digitalWrite(LEDPIN, LOW);
    } 
  }
}

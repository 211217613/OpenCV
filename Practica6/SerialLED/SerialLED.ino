#define R 2
#define U 3
#define B 4
#define E 5
#define N 6
char inputByte = 0;
void setup(){
  Serial.begin(9600);
  
  pinMode(R, OUTPUT);
  pinMode(U, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(N, OUTPUT);

  digitalWrite(R, LOW);
  digitalWrite(U, LOW);
  digitalWrite(B, LOW);
  digitalWrite(E, LOW);
  digitalWrite(N, LOW);
  
  if(!Serial){ 
   Serial.println("Serial port not ready");
  }
  else{
    Serial.println("serial port ready");
  }
}

void loop(){
  
  int serialData = Serial.available();
  int ledStatus = digitalRead(R);
  
  // read serial port data going to send b1 or b0
  if(serialData > 0){
    Serial.print("Led Status is: ");
    Serial.println(ledStatus);
    inputByte = Serial.read();
    Serial.print("Bytes waiting in buffer: ");
    Serial.println(serialData);
    Serial.print("inputByte is: ");
    Serial.println(inputByte);
    switch(inputByte){
      case '0': digitalWrite(R, HIGH); break;
      case '1': digitalWrite(U, HIGH); break;
      case '2': digitalWrite(B, HIGH); break;
      case '3': digitalWrite(E, HIGH); break;
      case '4': digitalWrite(N, HIGH); break;
      case '5': digitalWrite(R,LOW);
                digitalWrite(U,LOW);
                digitalWrite(B,LOW);
                digitalWrite(E,LOW);
                digitalWrite(N,LOW);
    }
  }
}

int i=13;
char temp[3] = {0,0,0};
char operacion = 0;
int decenas = 0;
int unidades = 0;
int resultado = 0;
int A=0, B=0;

void setup()
{
  while(i>=0 && i<14)
    {
        pinMode(i, OUTPUT);
        i=i-1;
    }
   Serial.begin(9600);
   
}
void mensaje(int opcion)
{
 switch(opcion)
  {
  case 0:  
         Serial.println("Ingresa la operacion +,*,% : ");
          break;
  case 1:
         Serial.println("OPeracion incorrecta!, ingresala nuevamente...");
        break;
  case 2:
        Serial.println("Error 403 ");
         break;
  case 3:
        Serial.println("Ingresa un numero del 00 al 99.. ");
         break;
  case 4:
        Serial.println("Numero incorrecto, ingresa nuevamente...");
        break;
  case 5:
        Serial.println("Error 405");
        break;
  case 6:
        Serial.print("El resultado es: ");
        Serial.println(resultado);
        break;
  default:
        Serial.println("Error 402 ");
  }
          
}

void leer(int que)
{
   switch(que)
    {
        case 0:
                for(;;)
                {
                 if(Serial.available()==1)
                    {
                      operacion = Serial.read();
                      if(operacion == '+' || operacion == '*' || operacion == '%')
                        break;
                      else
                        
                        mensaje(1);
                     
                    } 
                }
                break;
         case 1:
               for(;;)
                {
                 if(Serial.available()==2)
                    {
                      temp[0] = Serial.read();
                      temp[1] = Serial.read();
                      if(temp[0] >= 0x30 && temp[0]<= 0x39 && temp[1] >= 0x30 && temp[1]<=0x39)
                       {
                         decenas = temp[0]-0x30;
                         unidades = temp[1]-0x30;
                         A = decenas*10+unidades*1;
                         break;
                       }
                      else
                      mensaje(4);
                    } 
                }
                break;
         case 2:
               for(;;)
                {
                 if(Serial.available()==2)
                    {
                      temp[0] = Serial.read();
                      temp[1] = Serial.read();
                      if(temp[0] >= 0x30 && temp[0]<= 0x39 && temp[1] >= 0x30 && temp[1]<=0x39)
                       {
                         decenas = temp[0]-0x30;
                         unidades = temp[1]-0x30;
                         B = decenas*10+unidades*1;
                         break;
                       }
                      else
                      mensaje(4);
                    } 
                }
                break;
           
        default :
                  mensaje(2);
    } 
}
void realiza_operacion(){
  switch(operacion){
    case '+' :resultado = A+B;
              break;
    case '*' :resultado = A*B;
              break;
    case '%' :resultado = A%B;
              break;
    default :mensaje(5);
   } 
}

void loop(){
  mensaje(0);
  leer(0);
  mensaje(3);
  leer(1);
  mensaje(3);
  leer(2);
  realiza_operacion();
  mensaje(6);
}

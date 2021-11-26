//----------------------------------------------------------------------------------
//Variables
//----------------------------------------------------------------------------------
const int P1_pin = PA_7; //Entradas de los sensores
const int P2_pin = PE_3;
const int P3_pin = PE_2;
const int P4_pin = PE_1;

int P1 = 0; //Variables que guardan el valor del sensor
int P2 = 0;
int P3 = 0;
int P4 = 0;

int P1_R = PE_0; //Leds indicadores
int P1_G = PB_3;

int P2_R = PF_0;
int P2_G = PC_4;

int P3_R = PB_6;
int P3_G = PC_7;

int P4_R = PA_4;
int P4_G = PD_6;

void setup() {
  // put your setup code here, to run once:
  pinMode(P1_pin,INPUT);  //Configuramos los sensores como entradas
  pinMode(P2_pin,INPUT);
  pinMode(P3_pin,INPUT);
  pinMode(P4_pin,INPUT);


  pinMode(P1_R, OUTPUT);  //Y las leds como salidas 
  pinMode(P1_G, OUTPUT);

  pinMode(P2_R, OUTPUT);   
  pinMode(P2_G, OUTPUT);

  pinMode(P3_R, OUTPUT);   
  pinMode(P3_G, OUTPUT);

  pinMode(P4_R, OUTPUT);   
  pinMode(P4_G, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly: 
//----------------------------------------------------------------------------------
//Sensor 1
//----------------------------------------------------------------------------------
    if (P1 == LOW) {              //Verificamos el valor del sensor, Low significa que el senor ha detectado un vehiculo
    digitalWrite(P1_R, HIGH);     //Mientras que high indica que el parqueo esta libre
    digitalWrite(P1_G, LOW);
  }
  else {
    digitalWrite(P1_R, LOW);
    digitalWrite(P1_G, HIGH);
}
  
  P1 = digitalRead(P1_pin); //Leemos el valor del primer sensor

//----------------------------------------------------------------------------------
//Sensor 2
//----------------------------------------------------------------------------------
  if (P2 == LOW) {              //Replicamos el sensor uno para el resto de sensores
    digitalWrite(P2_R, HIGH);
    digitalWrite(P2_G, LOW);
  }
  else {
    digitalWrite(P2_R, LOW);
    digitalWrite(P2_G, HIGH);
}
  
  P2 = digitalRead(P2_pin);

//----------------------------------------------------------------------------------
//Sensor 3
//----------------------------------------------------------------------------------
  if (P3 == LOW) {
    digitalWrite(P3_R, HIGH);
    digitalWrite(P3_G, LOW);
  }
  else {
    digitalWrite(P3_R, LOW);
    digitalWrite(P3_G, HIGH);
}
  
  P3 = digitalRead(P3_pin);

//----------------------------------------------------------------------------------
//Sensor 4
//----------------------------------------------------------------------------------
  if (P4 == LOW) {
    digitalWrite(P4_R, HIGH);
    digitalWrite(P4_G, LOW);
  }
  else {
    digitalWrite(P4_R, LOW);
    digitalWrite(P4_G, HIGH);
}
  
  P4 = digitalRead(P4_pin);
}

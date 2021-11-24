const int P1_pin = PA_7;
const int P2_pin = PE_3;
const int P3_pin = PE_2;
const int P4_pin = PE_1;

int P1 = 0;
int P2 = 0;
int P3 = 0;
int P4 = 0;

int P1_R = PE_0;
int P1_G = PB_3;

int P2_R = PF_0;
int P2_G = PC_4;

int P3_R = PB_6;
int P3_G = PC_7;

int P4_R = PA_4;
int P4_G = PD_6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(P1_pin,INPUT);
  pinMode(P2_pin,INPUT);
  pinMode(P3_pin,INPUT);
  pinMode(P4_pin,INPUT);


  pinMode(P1_R, OUTPUT);   //Configuración de la led RGB incluida en la placa
  pinMode(P1_G, OUTPUT);

  pinMode(P2_R, OUTPUT);   //Configuración de la led RGB incluida en la placa
  pinMode(P2_G, OUTPUT);

  pinMode(P3_R, OUTPUT);   //Configuración de la led RGB incluida en la placa
  pinMode(P3_G, OUTPUT);

  pinMode(P4_R, OUTPUT);   //Configuración de la led RGB incluida en la placa
  pinMode(P4_G, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly: 
  Serial.print("\t Digital Reading=");
  Serial.println(P1);

    if (P1 == LOW) {
    digitalWrite(P1_R, HIGH);
    digitalWrite(P1_G, LOW);
  }
  else {
    digitalWrite(P1_R, LOW);
    digitalWrite(P1_G, HIGH);
}
  
  P1 = digitalRead(P1_pin);

  if (P2 == LOW) {
    digitalWrite(P2_R, HIGH);
    digitalWrite(P2_G, LOW);
  }
  else {
    digitalWrite(P2_R, LOW);
    digitalWrite(P2_G, HIGH);
}
  
  P2 = digitalRead(P2_pin);

  if (P3 == LOW) {
    digitalWrite(P3_R, HIGH);
    digitalWrite(P3_G, LOW);
  }
  else {
    digitalWrite(P3_R, LOW);
    digitalWrite(P3_G, HIGH);
}
  
  P3 = digitalRead(P3_pin);

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

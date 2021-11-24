const int P1_pin = PA_7;
const int P2_pin = PE_3;
const int P3_pin = PE_2;
const int P4_pin = PE_1;

int P1 = 0;
int P2 = 0;
int P3 = 0;
int P4 = 0;
/*Cantidad total de parqueos*/
uint8_t ContParqueos = 4;
/*Sirven para llevar control de los parqueos disponibles*/
uint8_t DispParqueos[] = { 1, 1, 1, 1 };
uint8_t LEDParqueos[] = { 128, 8, 16, 2 };
//
//int P1_R = PE_0;
//int P1_G = PB_3;
//
//int P2_R = PF_0;
//int P2_G = PC_4;
//
//int P3_R = PB_6;
//int P3_G = PC_7;
//
//int P4_R = PA_4;
//int P4_G = PD_6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial3.begin(115200);
  Serial3.setTimeout(50);
  pinMode(P1_pin,INPUT);
  pinMode(P2_pin,INPUT);
  pinMode(P3_pin,INPUT);
  pinMode(P4_pin,INPUT);

//
//  pinMode(P1_R, OUTPUT);   //Configuración de la led RGB incluida en la placa
//  pinMode(P1_G, OUTPUT);
//
//  pinMode(P2_R, OUTPUT);   //Configuración de la led RGB incluida en la placa
//  pinMode(P2_G, OUTPUT);
//
//  pinMode(P3_R, OUTPUT);   //Configuración de la led RGB incluida en la placa
//  pinMode(P3_G, OUTPUT);
//
//  pinMode(P4_R, OUTPUT);   //Configuración de la led RGB incluida en la placa
//  pinMode(P4_G, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly: 
  Serial.print("\t Digital Reading=");
  Serial.println(P1);
  Serial.println(P2);
  Serial.println(P3);
  Serial.println(P4);
while (Serial3.available()){
//    if (P1 == LOW) {
//      Serial3.write(48);
//   
////    digitalWrite(P1_R, HIGH);
////    digitalWrite(P1_G, LOW);
//
//  }
//  else {
////    digitalWrite(P1_R, LOW);
////    digitalWrite(P1_G, HIGH);
//}
//  
//  P1 = digitalRead(P1_pin);
//
//  if (P2 == LOW) {
//    Serial3.write(49);
////    digitalWrite(P2_R, HIGH);
////    digitalWrite(P2_G, LOW);
//  }
//  else {
////    digitalWrite(P2_R, LOW);
////    digitalWrite(P2_G, HIGH);
//}
//  
//  P2 = digitalRead(P2_pin);
//
//  if (P3 == LOW) {
//    Serial3.write(50);
////    digitalWrite(P3_R, HIGH);
////    digitalWrite(P3_G, LOW);
//  }
//  else {
////    digitalWrite(P3_R, LOW);
////    digitalWrite(P3_G, HIGH);
//}
//  
//  P3 = digitalRead(P3_pin);
//
//  if (P4 == LOW) {
//    Serial3.write(51);
////    digitalWrite(P4_R, HIGH);
////    digitalWrite(P4_G, LOW);
//  }
//  else {
////    digitalWrite(P4_R, LOW);
////    digitalWrite(P4_G, HIGH);
//}
//  
//  P4 = digitalRead(P4_pin);
//}
//}


if ((P1 == LOW) && (DispParqueos[0] == 1))
        {
            ContParqueos--;
            DispParqueos[0] = 0;
           // LEDParqueos[0] = 64;
        }
        if ((P1 == HIGH) && (DispParqueos[0] == 0))
        {
            ContParqueos++;
            DispParqueos[0] = 1;
            //LEDParqueos[0] = 128;
        }
        /*--------------------------------------------------------------------*/
        /*----------------------------Parqueo 2-------------------------------*/
        if ((P2 == LOW) && (DispParqueos[1] == 1))
        {
            ContParqueos--;
            DispParqueos[1] = 0;
           // LEDParqueos[1] = 4;
        }
        if ((P2 == HIGH) && (DispParqueos[1] == 0))
        {
            ContParqueos++;
            DispParqueos[1] = 1;
            //LEDParqueos[1] = 8;
        }
        /*--------------------------------------------------------------------*/
        /*----------------------------Parqueo 3-------------------------------*/
        if ((P3 == LOW) && (DispParqueos[2] == 1))
        {
            ContParqueos--;
            DispParqueos[2] = 0;
            //LEDParqueos[2] = 32;
        }
        if ((P3 == HIGH) && (DispParqueos[2] == 0))
        {
            ContParqueos++;
            DispParqueos[2] = 1;
            //LEDParqueos[2] = 16;
        }
        /*--------------------------------------------------------------------*/
        /*----------------------------Parqueo 4-------------------------------*/
        if ((P4 == LOW) && (DispParqueos[3] == 1))
        {
            ContParqueos--;
            DispParqueos[3] = 0;
           // LEDParqueos[3] = 1;
        }
        if ((P4 == HIGH) && (DispParqueos[3] == 0))
        {
            ContParqueos++;
            DispParqueos[3] = 1;
            //LEDParqueos[3] = 2;
        }
        /*--------------------------------------------------------------------*/
        /**********************************************************************/
        /*Envio de datos via UART5*/
        /**********************************************************************/
        /* Se suma el total de parkeos disponibles*/
        uint8_t TotalParkDisp = DispParqueos[0] + DispParqueos[1]
                + DispParqueos[2] + DispParqueos[3];
        /*--------------------------------------------------------------------*/
        /*Se crea un arreglo de chars para enviar los datos via UART*/
        char data_send[] = { DispParqueos[0] + 48, DispParqueos[1] + 48,
                             DispParqueos[2] + 48, DispParqueos[3] + 48,
                             TotalParkDisp + 48, '\n' };
        /*--------------------------------------------------------------------*/
        /*Rutina que manda los valores del arreglo chars, separando los datos por comas y terminando con un fin de linea*/
        uint8_t i;
        for (i = 0; i < 255 && data_send[i] != '\n'; i++)
        {
            Serial3.write(data_send[i]);
            Serial3.write(',');
        }
       Serial3.write('\n');
        /*--------------------------------------------------------------------*/
    }
}

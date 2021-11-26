  /*************************************************************************************************
  ESP32 Web Server
  Ejemplo de creación de Web server con acceso a SPIFFS
  Basándose en los ejemplos de:
  https://github.com/khoih-prog/WiFiWebServer
  https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
  https://github.com/luisllamasbinaburo/ESP32-Examples
  https://www.luisllamas.es/esp8266-esp32/
**************************************************************************************************/
//************************************************************************************************
// Librerías
//************************************************************************************************
#include <WiFi.h>
#include <SPIFFS.h>
#include <WebServer.h>
//************************************************************************************************
// Variables globales
//************************************************************************************************
// SSID & Password
const char* ssid = "Parqueo F&J";  // Enter SSID here
const char* password = "12345671";  //Enter Password here
IPAddress local_ip(192,168,1,75);
IPAddress gateway(192,168,1,75);
IPAddress subnet(255,255,255,0);
char com;
String parqueo1;
String parqueo2;
String parqueo3;
String parqueo4;
String parqueo5;
String parqueo6;
String parqueo7;
String parqueo8;
String totalpark;
String datos = "";
String getValue(String data, char separator, int index);

String estadopark1;
String estadopark2;
String estadopark3;
String estadopark4;
String estadopark5;
String estadopark6;
String estadopark7;
String estadopark8;
uint8_t total;

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

uint8_t LED1pin = 2;
bool LED1status = LOW;
int status1, status2, status3;
int go; 

//************************************************************************************************
// Configuración
//************************************************************************************************
void setup() {
  pinMode(32, OUTPUT);                        // Pin para el led
  pinMode(33, OUTPUT);                        // Pin para el led
  pinMode(25,OUTPUT);                        // Pin para el led
  pinMode(26, OUTPUT);                        // Pin para el led
  pinMode(27, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12,OUTPUT);
  
  #define RXD2 16 
  #define TXD2 17
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pinMode(LED1pin, OUTPUT);
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("password: ");
  Serial.println(password);

  server.on("/", handle_OnConnect); // página de inicio
  server.on("/s1", handle_s1); // handler al haber uno ocupado
  server.on("/s2", handle_s2); //
  server.on("/s3", handle_s3); //
  server.on("/s4", handle_s4); //
  server.on("/s5", handle_s5); //
  server.on("/s6", handle_s6); //
  server.on("/s7", handle_s7); //
  server.on("/s8", handle_s8); //
  server.onNotFound([]() {                  // si el cliente solicita una uri desconocida
    //if (!HandleFileRead(server.uri()))      // enviar archivo desde SPIFF, si existe
      //handleNotFound();             // sino responder con un error 404 (no existe)
  });
  //server.onNotFound(handle_NotFound); //si no se encuentra el uri, responder con error 404 (no existe)

  server.begin(); // iniciar servidor
  Serial.println("HTTP server started");
  delay(100);
}
//************************************************************************************************
// loop principal
//************************************************************************************************
//void loop() {
//  server.handleClient(); // escuchar solicitudes de clientes
//  if (LED1status)
//  {
//    digitalWrite(LED1pin, HIGH);
//  }
//  else
//  {
//    digitalWrite(LED1pin, LOW);
//  }
//  Serial.println("Message Received: ");
//  Serial.println(Serial2.readString()); 
////if (Serial2.available()){                      
////    com = Serial2.read();                   // Guardar lo leído en Message
////    Serial.write(com);                     // Escribir lo que se recibe
//// 
////  delay(4);
////  if(com == 48){                          // Recibe un 1
////    digitalWrite(32,HIGH);
////    digitalWrite(33,LOW);
////    digitalWrite(25,LOW);
////    digitalWrite(26,LOW);
////      
////  }
////    if(com == 49){                          // Recibe un 1
////    digitalWrite(32,LOW);
////    digitalWrite(33,HIGH);
////    digitalWrite(25,LOW);
////    digitalWrite(26,LOW);
////  
////  }
////
////    if(com == 50){                          // Recibe 0
////    digitalWrite(32,LOW);
////    digitalWrite(33,LOW);
////    digitalWrite(25,HIGH);
////    digitalWrite(26,LOW);
////     
////  }
////
////   if(com == 51){                          // Recibe 0
////    digitalWrite(32,LOW);
////    digitalWrite(33,LOW);
////    digitalWrite(25,LOW);
////    digitalWrite(26,HIGH);
////   
////      
////  }
////   }
//  
//}
void loop() {
//  server.handleClient();
//  while (Serial2.available()) {
//    char inByte = Serial2.read();
//    if (inByte != '\n') {
//      //convierto todo a datos
//      // los datos enviados de la TivaC separados por comas
//      datos.concat(inByte);
//    } else {
//      //Se utiliza la función getValue para separarlos según las comas, debido a que los datos no tienen la misma longitud siempre
//      parqueo1 = getValue(datos, ',', 0);
//      parqueo2 = getValue(datos, ',', 1);
//      parqueo3 = getValue(datos, ',', 2);
//      parqueo4 = getValue(datos, ',', 3);
//      totalpark = getValue(datos, ',', 4);
//      //se limpia la cadena para la proxima lectura
//      datos = "";
//    }
//    //Rutinas con las cuales se define si la TivaC envia si el parqueo esta o no ocupado
//    if (parqueo1 == "1")estadopark1 = "Disponible"; //Si es uno el parqueo esta disponible 
//    else estadopark1 = "Ocupado";//Sera 0 si el parque esta ocupado
//    if (parqueo2 == "1")estadopark2 = "Disponible";
//    else estadopark2 = "Ocupado";
//    if (parqueo3 == "1")estadopark3 = "Disponible";
//    else estadopark3 = "Ocupado";
//    if (parqueo4 == "1")estadopark4 = "Disponible";
//    else estadopark4 = "Ocupado";
//  }
//}
 server.handleClient(); // escuchar solicitudes de clientes
  if (Serial2.available()) {
    char inByte = Serial2.read();
    if (inByte != '\n') {
      //convierto todo a datos
      // los datos enviados de la TivaC separados por comas
      datos.concat(inByte);
    } else {
      //Se utiliza la función getValue para separarlos según las comas, debido a que los datos no tienen la misma longitud siempre
      parqueo1 = getValue(datos, ',', 0);
      parqueo2 = getValue(datos, ',', 1);
      parqueo3 = getValue(datos, ',', 2);
      parqueo4 = getValue(datos, ',', 3);
      parqueo1 = getValue(datos, ',', 4);
      parqueo2 = getValue(datos, ',', 5);
      parqueo3 = getValue(datos, ',', 6);
      parqueo4 = getValue(datos, ',', 7);
      totalpark = getValue(datos, ',', 8);
      //se limpia la cadena para la proxima lectura
      datos = "";
    }
    //Rutinas con las cuales se define si la TivaC envia si el parqueo esta o no ocupado
    if (parqueo1 == "1")estadopark1 = "Disponible"; //Si es uno el parqueo esta disponible 
    else estadopark1 = "Ocupado";//Sera 0 si el parque esta ocupado
    if (parqueo2 == "1")estadopark2 = "Disponible";
    else estadopark2 = "Ocupado";
    if (parqueo3 == "1")estadopark3 = "Disponible";
    else estadopark3 = "Ocupado";
    if (parqueo4 == "1")estadopark4 = "Disponible";
    else estadopark4 = "Ocupado";
    if (parqueo5 == "1")estadopark5 = "Disponible"; //Si es uno el parqueo esta disponible 
    else estadopark5 = "Ocupado";//Sera 0 si el parque esta ocupado
    if (parqueo6 == "1")estadopark6 = "Disponible";
    else estadopark6 = "Ocupado";
    if (parqueo7 == "1")estadopark7 = "Disponible";
    else estadopark7 = "Ocupado";
    if (parqueo8 == "1")estadopark8 = "Disponible";
    else estadopark8 = "Ocupado";
    
  
    status2 = Serial2.read();
    //status3 = 0;
    if(status2 == '0'){
      Serial.print("0");
      go = 0;
      server.send(200, "text/html", SendHTML(go));
    }
    if(status2 == '1'){
      Serial.print("1");
      go = 1;
      server.send(200, "text/html", SendHTML(go));
    }
    if(status2 == '2'){
      Serial.print("2");
      go = 2;
      server.send(200, "text/html", SendHTML(go));
    }
    if(status2 == '3'){
      Serial.print("3");
      go = 3;
      server.send(200, "text/html", SendHTML(go));
    }
    if(status2 == '4'){
      Serial.print("4");
      go = 4;
      server.send(200, "text/html", SendHTML(go));
    }


//    //status2 es tiva1 y status3 es tiva2
//    if (status2 == '0' and status3 == '0') {
//      Serial.print("0");
//      go = 0;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s8\">Update</a>\n";
//
//    }
//    if (status2 == '0' and status3 == '1') {
//      Serial.print("1");
//      go = 1;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '0' and status3 == '2') {
//      Serial.print("2");
//      go = 2;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '0' and status3 == '3') {
//      Serial.print("3");
//      go = 3;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '0' and status3 == '4') {
//      Serial.print("4");
//      go = 4;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '1' and status3 == '0') {
//      Serial.print("1");
//      go = 1;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '1' and status3 == '1') {
//      Serial.print("2");
//      go = 2;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '1' and status3 == '2') {
//      Serial.print("3");
//      go = 3;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '1' and status3 == '3') {
//      Serial.print("4");
//      go = 4;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '1' and status3 == '4') {
//      Serial.print("5");
//      go = 5;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '2' and status3 == '0') {
//      Serial.print("2");
//      go = 2;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '2' and status3 == '1') {
//      Serial.print("3");
//      go = 3;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '2' and status3 == '2') {
//      Serial.print("4");
//      go = 4;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '2' and status3 == '3') {
//      Serial.print("5");
//      go = 5;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '2' and status3 == '4') {
//      Serial.print("6");
//      go = 6;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '3' and status3 == '0') {
//      Serial.print("3");
//      go = 3;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '3' and status3 == '1') {
//      Serial.print("4");
//      go = 4;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '3' and status3 == '2') {
//      Serial.print("5");
//      go = 5;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '3' and status3 == '3') {
//      Serial.print("6");
//      go = 6;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '3' and status3 == '4') {
//      Serial.print("7");
//      go = 7;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '4' and status3 == '0') {
//      Serial.print("4");
//      go = 4;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '4' and status3 == '1') {
//      Serial.print("5");
//      go = 5;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '4' and status3 == '2') {
//      Serial.print("6");
//      go = 6;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '4' and status3 == '3') {
//      Serial.print("7");
//      go = 7;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
//    if (status2 == '4' and status3 == '4') {
//      Serial.print("8");
//      go = 8;
//      server.send(200, "text/html", SendHTML(go));
//      //ptr += "<a class=\"button button-off\" href=\"/s7\">Update</a>\n";
//    }
  }
}

//************************************************************************************************
// Handler de página de inicio
//************************************************************************************************
// Handler de página de inicio
//************************************************************************************************
void handle_OnConnect() {
  //8
  digitalWrite(32, HIGH); //
  digitalWrite(33, HIGH); //
  digitalWrite(25, HIGH); //
  digitalWrite(26, HIGH); //
  digitalWrite(27, HIGH); //
  digitalWrite(14, HIGH); //
  digitalWrite(12, HIGH); //
  status1 = 0; // inicia todo libre, por defecto
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML
}
//************************************************************************************************
// Handler de 1 ocupado
//************************************************************************************************
void handle_s1() {
  //7
  digitalWrite(32, HIGH); //
  digitalWrite(33, HIGH); //
  digitalWrite(25, HIGH); //
  digitalWrite(26, LOW); //
  digitalWrite(27, LOW); //
  digitalWrite(14, LOW); //
  digitalWrite(12, LOW); //
  status1 = 1;
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML

}
//************************************************************************************************
// Handler de 2 ocupados
//************************************************************************************************
void handle_s2() {
  //6
  digitalWrite(32, HIGH); //
  digitalWrite(33, LOW); //
  digitalWrite(25, HIGH); //
  digitalWrite(26, HIGH); //
  digitalWrite(27, HIGH); //
  digitalWrite(14, HIGH); //
  digitalWrite(12, HIGH); //
  status1 = 2;
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML
}

//************************************************************************************************
// Handler de 3 ocupado
//************************************************************************************************
void handle_s3() {
  //5
  digitalWrite(32, HIGH); //
  digitalWrite(33, LOW); //
  digitalWrite(25, HIGH); //
  digitalWrite(26, HIGH); //
  digitalWrite(27, LOW); //
  digitalWrite(14, HIGH); //
  digitalWrite(12, HIGH); //
  status1 = 3;
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML
}
//************************************************************************************************
// Handler de 4 ocupados
//************************************************************************************************
void handle_s4() {
  //4
  digitalWrite(32, LOW); //
  digitalWrite(33, HIGH); //
  digitalWrite(25, HIGH); //
  digitalWrite(26, LOW); //
  digitalWrite(27, LOW); //
  digitalWrite(14, HIGH); //
  digitalWrite(12, HIGH); //
  status1 = 4;
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML
}

//************************************************************************************************
// Handler de 5 ocupado
//************************************************************************************************
void handle_s5() {
  //3
  digitalWrite(32, HIGH); //
  digitalWrite(33, HIGH); //
  digitalWrite(25, HIGH); //
  digitalWrite(26, HIGH); //
  digitalWrite(27, LOW); //
  digitalWrite(14, LOW); //
  digitalWrite(12, HIGH); //
  status1 = 5;
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML
}
//************************************************************************************************
// Handler de 6 ocupados
//************************************************************************************************
void handle_s6() {
  //2
  digitalWrite(32, HIGH); //
  digitalWrite(33, HIGH); //
  digitalWrite(25, LOW); //
  digitalWrite(26, HIGH); //
  digitalWrite(27, HIGH); //
  digitalWrite(14, LOW); //
  digitalWrite(12, HIGH); //
  status1 = 6;
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML
}

//************************************************************************************************
// Handler de 7 ocupado
//************************************************************************************************
void handle_s7() {
  //1
  digitalWrite(32, LOW); //
  digitalWrite(33, HIGH); //
  digitalWrite(25, HIGH); //
  digitalWrite(26, LOW); //
  digitalWrite(27, LOW); //
  digitalWrite(14, LOW); //
  digitalWrite(12, LOW); //
  status1 = 7;
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML
}
//************************************************************************************************
// Handler de 8 ocupados
//************************************************************************************************
void handle_s8() {
  //0
  digitalWrite(32, HIGH); //
  digitalWrite(33, HIGH); //
  digitalWrite(25, HIGH); //
  digitalWrite(26, HIGH); //
  digitalWrite(27, HIGH); //
  digitalWrite(14, HIGH); //
  digitalWrite(12, LOW); //
  status1 = 8;
  server.send(200, "text/html", SendHTML(status1)); //responde con un OK (200) y envía HTML
}
//************************************************************************************************
// Procesador de HTML
//************************************************************************************************
String SendHTML(uint8_t led1stat) {
  String ptr = "<!DOCTYPE html> <html>\n"
               "<head><meta name=\\\"viewport\\\" content=\\\"width=device-width, initial-scale=1.0, user-scalable=no\\\"\n"
               "<h1> P3 Fernando Arribas y Josue Salazar </h1>\n"
               "<script>\n"
               "<!--\n"
               "function timedRefresh(timeoutPeriod) {\n"
               "\tsetTimeout(\"location.reload(true);\",timeoutPeriod);\n"
               "}\n"
               "\n"
               "window.onload = timedRefresh(1000);\n"
               "\n"
               "//   -->\n"
               "</script>"
               "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n"
               "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n"
               ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n"
               ".button-on {background-color: #3498db;}\n"
               ".button-on:active {background-color: #2980b9;}\n"
               ".button-off {background-color: #34495e;}\n"
               ".button-off:active {background-color: #2c3e50;}\n"
               "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n"
               "table.blueTable {\n"
               "  border: 1px solid #1C6EA4;\n"
               "  background-color: #EEEEEE;\n"
               "  width: 100%;\n"
               "  text-align: left;\n"
               "  border-collapse: collapse;\n"
               "}\n"
               "table.blueTable td, table.blueTable th {\n"
               "  border: 1px solid #AAAAAA;\n"
               "  padding: 3px 2px;\n"
               "}\n"
               "table.blueTable tbody td {\n"
               "  font-size: 13px;\n"
               "}\n"
               "table.blueTable tr:nth-child(even) {\n"
               "  background: #D0E4F5;\n"
               "}\n"
               "table.blueTable thead {\n"
               "  background: #1C6EA4;\n"
               "  background: -moz-linear-gradient(top, #5592bb 0%, #327cad 66%, #1C6EA4 100%);\n"
               "  background: -webkit-linear-gradient(top, #5592bb 0%, #327cad 66%, #1C6EA4 100%);\n"
               "  background: linear-gradient(to bottom, #5592bb 0%, #327cad 66%, #1C6EA4 100%);\n"
               "  border-bottom: 2px solid #444444;\n"
               "}\n"
               "table.blueTable thead th {\n"
               "  font-size: 15px;\n"
               "  font-weight: bold;\n"
               "  color: #FFFFFF;\n"
               "  border-left: 2px solid #D0E4F5;\n"
               "}\n"
               "table.blueTable thead th:first-child {\n"
               "  border-left: none;\n"
               "}\n"
               "</style>\n"
               "</head>\n"
               "\n"
               "<table class='blueTable'>\n"
               "<thead>\n"
               "<tr>\n"
               "<th>P1</th>\n"
               "<th>P2</th>\n"
               "<th>P3</th>\n"
               "<th>P4</th>\n"
               "</tr>\n"
               "</thead>\n"
               "<tfoot>\n"
               "<tr>\n"
               "<td colspan=\"4\">&nbsp;</td>\n"
               "</tr>\n"
               "</tfoot>\n"
               "<tbody>\n"
               "<tr>\n"
               "<td>" + estadopark1 + "</td>\n"
               "<td>" + estadopark2 + "</td>\n"
               "<td>" + estadopark3 + "</td>\n"
               "<td>" + estadopark4 + "</td>\n"
               "</tr>\n"
               "</tbody>\n"
               "</table>\n"
               "<body>\n"
               "</style>\n"
               "</head>\n"
               "\n"
               "<table class='blueTable'>\n"
               "<thead>\n"
               "<tr>\n"
               "<th>P5</th>\n"
               "<th>P6</th>\n"
               "<th>P7</th>\n"
               "<th>P8</th>\n"
               "</tr>\n"
               "</thead>\n"
               "<tfoot>\n"
               "<tr>\n"
               "<td colspan=\"4\">&nbsp;</td>\n"
               "</tr>\n"
               "</tfoot>\n"
               "<tbody>\n"
               "<tr>\n"
               "<td>" + estadopark5 + "</td>\n"
               "<td>" + estadopark6 + "</td>\n"
               "<td>" + estadopark7 + "</td>\n"
               "<td>" + estadopark8 + "</td>\n"
               "</tr>\n"
               "</tbody>\n"
               "</table>\n"
               "<body>\n"
               "<h1> &#128664 Servidor Parqueomatic &#128664  </h1>\n"
               "";

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

//************************************************************************************************
// Handler de not found
//************************************************************************************************
void handleNotFound() {
  server.send(404, "text/plain", "Not found");
}
//************************************************************************************************
// Obtener el tipo de contenido del archivo
//************************************************************************************************
String GetContentType(String filename)
{
  if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}
//************************************************************************************************
// Enviar al servidor el archivo desde SPIFFS
//************************************************************************************************
void ServeFile(String path)
{
  File file = SPIFFS.open(path, "r");
  size_t sent = server.streamFile(file, GetContentType(path));
  file.close();
}
//************************************************************************************************
// Enviar al servidor el archivo desde SPIFFS
//************************************************************************************************
void ServeFile(String path, String contentType)
{
  File file = SPIFFS.open(path, "r");
  size_t sent = server.streamFile(file, contentType);
  file.close();
}
//************************************************************************************************
// Handler de not found
//************************************************************************************************
bool HandleFileRead(String path)
{
  if (path.endsWith("/")) path += "index.html";
  Serial.println("handleFileRead: " + path);

  if (SPIFFS.exists(path))
  {
    ServeFile(path);
    return true;
  }
  Serial.println("\tFile Not Found");
  return false;
}
String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

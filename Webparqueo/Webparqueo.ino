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


WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

uint8_t LED1pin = 2;
bool LED1status = LOW;

//************************************************************************************************
// Configuración
//************************************************************************************************
void setup() {
  pinMode(32, OUTPUT);                        // Pin para el led
  pinMode(32, OUTPUT);                        // Pin para el led
  pinMode(25,OUTPUT);                        // Pin para el led
  pinMode(26, OUTPUT);                        // Pin para el led
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
  server.on("/led1on", handle_led1on); // handler al activar led
  server.on("/led1off", handle_led1off); // handler al desactivar led
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
void loop() {
  server.handleClient(); // escuchar solicitudes de clientes
  if (LED1status)
  {
    digitalWrite(LED1pin, HIGH);
  }
  else
  {
    digitalWrite(LED1pin, LOW);
  }
  
if (Serial2.available()){                      
    com = Serial2.read();                   // Guardar lo leído en Message
    Serial.write(com);                     // Escribir lo que se recibe
 
  delay(4);
  if(com == 48){                          // Recibe un 1
    digitalWrite(32,HIGH);
    digitalWrite(33,LOW);
    digitalWrite(25,LOW);
    digitalWrite(26,LOW);
      
  }
    if(com == 49){                          // Recibe un 1
    digitalWrite(32,LOW);
    digitalWrite(33,HIGH);
    digitalWrite(25,LOW);
    digitalWrite(26,LOW);
  
  }

    if(com == 50){                          // Recibe 0
    digitalWrite(32,LOW);
    digitalWrite(33,LOW);
    digitalWrite(25,HIGH);
    digitalWrite(26,LOW);
     
  }

   if(com == 51){                          // Recibe 0
    digitalWrite(32,LOW);
    digitalWrite(33,LOW);
    digitalWrite(25,LOW);
    digitalWrite(26,HIGH);
   
      
  }
   }
  
}
//************************************************************************************************
// Handler de página de inicio
//************************************************************************************************
void handle_OnConnect() {
  handle_led1off(); // inicia LED apagado, por defecto
}
//************************************************************************************************
// Handler de led1on
//************************************************************************************************
void handle_led1on() {
  LED1status = HIGH;
  Serial.println("GPIO2 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status)); //responde con un OK (200) y envía HTML
}
//************************************************************************************************
// Handler de led1off
//************************************************************************************************
void handle_led1off() {
  LED1status = LOW;
  Serial.println("GPIO2 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status)); //responde con un OK (200) y envía HTML
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
//               "<td>" + p1disp + "</td>\n"
//               "<td>" + p2disp + "</td>\n"
//               "<td>" + p3disp + "</td>\n"
//               "<td>" + p4disp + "</td>\n"
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
//               "<td>" + p5disp + "</td>\n"
//               "<td>" + p6disp + "</td>\n"
//               "<td>" + p7disp + "</td>\n"
//               "<td>" + p8disp + "</td>\n"
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

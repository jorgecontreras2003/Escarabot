#include "Print.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
//Librerias propias
#include "index.h" //Nuestra página web en HTML 

ESP8266WebServer server(80); //Crea el objeto server en el puerto 80

//Nombre y password del punto WIFI
const char *ssid = "BattleBots_Bosque";
// const char *password = "123456"; //no usamos password


/** Handle Root
 * @brief Envía el contenido de index.h
 */
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}


/** Handle Button Request
 * @brief Esta función toma los valores enviados desde la página web y según su valor, llama a distintas funciones de motores.
  * Los botones de la página web ejecutan esta funcion -> sendRequest('http://192.168.4.1/B?val=1') 
 * La función sendRequest() crea una instancia de XMLHttpRequest() y la envía a través de WiFi a nuestra ESP8266.
 */

/**
when you push http://192.168.4.2/send?var1=hello&var2=good 45 ( use form get method in html tags )

in esp sketch use , String x = server.arg("var1"); and String y = server.arg("var2");
*/

void handleButtonRequest(void) {

  int Rho = server.arg("R").toInt();
  int Theta = server.arg("t").toInt();
  int Attack = server.arg("a").toInt();
  
  motorControl(Rho, Theta, Attack);
  server.send(200, "text/plain", "OK"); //enviamos una confirmación al servidor

}




/** Run Web Server
 * @brief Función principal que configura la conección wifi, crea el servidor y conecta las funciones.
 */

void run_web_server(void) {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Create a new SoftAP network
  WiFi.softAP(ssid);


  // Print the IP address of the SoftAP network
  Serial.print("Access Point IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.println("Copien esta IP y péguenla en su navegador");




  server.on("/Button", HTTP_GET, handleButtonRequest); //Cuando estemos en la página Button, llamamos a la función handleButtonRequest y le 
  server.on("/", handleRoot);      //Which routine to handle at root location
  
  // Set up web server
  server.onNotFound([]() {
    handleRoot();
  });

  server.begin();
  Serial.println("Web server started");
}

void handle_client(void) {
  server.handleClient();
}
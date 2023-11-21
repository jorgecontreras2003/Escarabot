/** Clase 5 Control WiFi 
  @name Clase5_Wifi_2023-2
  @purpose: En esta clase aprenderán a usar la funcionalidad wifi de la ESP8266
  @author: Marcelo Jimenez
  @version: Esta corresponde al ejercicio de la clase práctica.  
*/

#include "motores.h"
#include "web_server.h"

void setup() {
  run_web_server();
  motors_setup();
  }

void loop() {
  handle_client();
}

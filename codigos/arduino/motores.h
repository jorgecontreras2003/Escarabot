#include <math.h>

// nombramos los pines
int motor_B1 = 12; // pin motor A1
int motor_B2 = 14; // pin motor A2
int pin_vel_B = 15; // pin control de velocidad motor A

int motor_A1 = 5; // pin motor B1
int motor_A2 = 4; // pin motor B2
int pin_vel_A = 13; // pin control de velocidad motor A

int armaA = 0; // pins arma
int armaB = 2; 

int base_speed = 100;

int SPEED_A = 0; //velocidades iniciales
int SPEED_B = 0;

bool dir = true;

/** motors setup
 * @brief Función que configura inificalmente los motores
 */
void motors_setup()
{
  // configuramos el motor A como salida (OUTPUT)
  pinMode(motor_A1, OUTPUT); // motor A1
  pinMode(motor_A2, OUTPUT); // motor A2
  pinMode(pin_vel_A, OUTPUT); // control velocidad A
  
  // configuramos el motor B como salida (OUTPUT)
  pinMode(motor_B1, OUTPUT); // motor B1
  pinMode(motor_B2, OUTPUT); // motor B2
  pinMode(pin_vel_B, OUTPUT); // control velocidad B
  
  // partimos con el motor A apagado (LOW)
  digitalWrite(motor_A1, LOW); // motor A1
  digitalWrite(motor_A2, LOW); // motor A2  
  
  // configuramos las armas como salidas (OUTPUT)
  pinMode(armaA, OUTPUT);
  pinMode(armaB, OUTPUT);

  // partimos con el motor B apagado (LOW)
  digitalWrite(motor_B1, LOW); // motor A1
  digitalWrite(motor_B2, LOW); // motor A2

  // partimos con el arma apagada (LOW)
  digitalWrite(armaA, LOW);
  digitalWrite(armaB, LOW);
}

/** motor Foward Backward
 * @brief Función controla el movimiento hacia adelante o hacia atrás de los motores.
 * @param dir1 es un valor de verdad (true o false) que permite elegir una dirección
 */
void motor_FWBW(bool dir1)
{ 
  if (dir1) {
    digitalWrite(motor_A1, LOW);
    digitalWrite(motor_A2, HIGH);
    analogWrite(pin_vel_A, SPEED_A);
    digitalWrite(motor_B1, LOW);
    digitalWrite(motor_B2, HIGH);
    analogWrite(pin_vel_B, SPEED_B);
  }
  else {
    digitalWrite(motor_A1, !LOW);
    digitalWrite(motor_A2, !HIGH);
    analogWrite(pin_vel_A, SPEED_A);
    digitalWrite(motor_B1, !LOW);
    digitalWrite(motor_B2, !HIGH);
    analogWrite(pin_vel_B, SPEED_B);
  }
}

void motor_LR(bool dir2) {
  if (dir2) {
    digitalWrite(motor_A1, !LOW);
    digitalWrite(motor_A2, !HIGH);
    analogWrite(pin_vel_A, SPEED_A);
    digitalWrite(motor_B1, LOW);
    digitalWrite(motor_B2, HIGH);
    analogWrite(pin_vel_B, SPEED_B);
  }
  else {
    digitalWrite(motor_A1, LOW);
    digitalWrite(motor_A2, HIGH);
    analogWrite(pin_vel_A, SPEED_A);
    digitalWrite(motor_B1, !LOW);
    digitalWrite(motor_B2, !HIGH);
    analogWrite(pin_vel_B, SPEED_B);
  }
} 

/** Motor Stop
 * @brief Función que detiene los motores
 */
void motor_stop(void)
{
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, LOW);
}

void ataque(int p){
  if (p == -1) {
    digitalWrite(armaA, LOW);
    digitalWrite(armaB, HIGH);
  }

  else if (p == 1) {
    digitalWrite(armaA, HIGH);
    digitalWrite(armaB, LOW);
  }

  else {
    digitalWrite(armaA, LOW);
    digitalWrite(armaB, LOW);
  }
}

void motorControl(int R, int t, int a) {
  float x;

  float pctg = R/100.0; // porcentaje en decimal
  int max_speed = base_speed*pctg;

  if (abs(t) > 90){
    x = 190 - abs(t);
  }
  else {
    x = abs(t);
  }

  float proportion = (x-20.0)/(50.0);
  int sub_speed = max_speed*proportion;
    
  Serial.println(String(max_speed) + "," + String(pctg));

  if (R == 0) {
    motor_stop();
  }
  else if (abs(t)<=20){
    SPEED_A = max_speed;
    SPEED_B = max_speed;
    motor_LR(false);
  }
  else if (abs(t)>= 160){
    SPEED_A = max_speed;
    SPEED_B = max_speed;
    motor_LR(true);
  }
  else if (abs(t) < 70){
    SPEED_A = max_speed;
    SPEED_B = sub_speed;
    motor_FWBW(t > 0);
  }
  else if (abs(t) > 110){
    SPEED_B = max_speed;
    SPEED_A = sub_speed;
    motor_FWBW(t > 0);
  }
  else {
    SPEED_A = max_speed;
    SPEED_B = max_speed;
    motor_FWBW(t > 0);
  }

  ataque(a);
}
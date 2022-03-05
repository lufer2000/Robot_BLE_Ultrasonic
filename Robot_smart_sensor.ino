#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A4 
#define ECHO_PIN A5 
#define MAX_DISTANCE 200 
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
Servo myservo;   

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

int derA = 11; // Positivo/Frente do lado direito
int derB = 3; // Negativo/Trás do lado direito
int izqA = 5; // Positivo/Frente do lado esquerdo
int izqB = 6; // Negativo/Trás do lado esquerdo

int vel1 = 255; // Velocidade dos motores Smartphone frente / trás (0-255)
int vel2 = 125; // Velocidade dos motores Smartphone direita / esquerda (0-255)
int vel3 = 190; // Velocidade dos motores sensores (0-255)

int estado = 'g'; // inicia parado

void setup() {
  Serial.begin(9600); // inicia el puerto serial para comunicacion con el Bluetooth
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);

  myservo.attach(9);  
  myservo.write(90); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
} 

void loop() { 

if(Serial.available()>0){ // lee el bluetooth y almacena en estado
estado = Serial.read();
}
if(estado=='a'){ // Forward
  Serial.println(estado);
analogWrite(derB, 0); 
analogWrite(izqB, 0); 
analogWrite(derA, vel1); 
analogWrite(izqA, vel1); 
}
if(estado=='d'){ // right
    Serial.println(estado);
analogWrite(derB, 0); 
analogWrite(izqB, vel2);
analogWrite(izqA, 0);
analogWrite(derA, vel2);  
}
if(estado=='c'){ // Stop
    Serial.println(estado);
analogWrite(derB, 0); 
analogWrite(izqB, 0); 
analogWrite(derA, 0); 
analogWrite(izqA, 0); 
}
if(estado=='b'){ // left
    Serial.println(estado);
analogWrite(derB, vel2); 
analogWrite(izqB, 0); 
analogWrite(derA, 0); 
analogWrite(izqA, vel2); 
} 

if(estado=='e'){ // Reverse
    Serial.println(estado);
analogWrite(derA, 0); 
analogWrite(izqA, 0);
analogWrite(derB, vel1); 
analogWrite(izqB, vel1); 
}
if (estado =='f'){ // Boton ON se mueve sensando distancia
  int distanceR = 0;
  int distanceL = 0;
  delay(40);
  
  if(distance<=40)
  {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);
    
    if(distanceR>=distanceL)
    {
      turnRight();
      moveStop();
    }else
    {
      turnLeft();
      moveStop();
    }
    }else
    {
      moveForward();
    }
    
 distance = readPing();
}

if (estado=='g'){ // Boton OFF, detiene los motores no hace nada 
  Serial.println(estado);
  analogWrite(derB, 0); 
  analogWrite(izqB, 0); 
  analogWrite(derA, 0); 
  analogWrite(izqA, 0); 
  }
}

int lookRight()
{
    myservo.write(20); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(90); 
    return distance;
}

int lookLeft()
{
    myservo.write(160); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(90); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  analogWrite(derB, 0); 
  analogWrite(izqB, 0); 
  analogWrite(derA, 0); 
  analogWrite(izqA, 0);
  } 
  
void moveForward() {
  analogWrite(derB, 0); 
  analogWrite(izqB, 0); 
  analogWrite(derA, vel3); 
  analogWrite(izqA, vel3);
  }

void moveBackward() {
  analogWrite(derA, 0); 
  analogWrite(izqA, 0);
  analogWrite(derB, vel3); 
  analogWrite(izqB, vel3);
  }  

void turnRight() {
  analogWrite(derB, vel3); 
  analogWrite(izqB, 0); 
  analogWrite(derA, 0); 
  analogWrite(izqA, vel3);     
  
  delay(300);
  moveForward;
  } 
 
void turnLeft() {
  analogWrite(derB, 0); 
  analogWrite(izqB, vel3);
  analogWrite(izqA, 0);
  analogWrite(derA, vel3);
  
  delay(300);
  moveForward();
  }  



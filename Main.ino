#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME "Carrinho robô"
#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define MOTOR1_IN1 33
#define MOTOR1_IN2 32
#define MOTOR2_IN1 25
#define MOTOR2_IN2 26

int x = 50;
int y = 50;
int Speed = 255; 

char auth[] = "";
char ssid[] = ""; 
char pass[] = ""; 

void setup() {
  Serial.begin(9600);

  
  pinMode(MOTOR1_IN1, OUTPUT);
  pinMode(MOTOR1_IN2, OUTPUT);
  pinMode(MOTOR2_IN1, OUTPUT);
  pinMode(MOTOR2_IN2, OUTPUT);

  
  ledcAttachPin(MOTOR1_IN1, 0);
  ledcSetup(0, 5000, 8); 
  ledcAttachPin(MOTOR1_IN2, 1);
  ledcSetup(1, 5000, 8); 
  ledcAttachPin(MOTOR2_IN1, 2);
  ledcSetup(2, 5000, 8); 
  ledcAttachPin(MOTOR2_IN2, 3);
  ledcSetup(3, 5000, 8); 

  Blynk.begin(auth, ssid, pass);
}


BLYNK_WRITE(V0) {
  x = param.asInt();
}


BLYNK_WRITE(V1) {
  y = param.asInt();
}


BLYNK_WRITE(V2) {
  Speed = param.asInt();
}

void smartcar() {
  if (y > 70) {
    carForward();
    Serial.println("carForward");
  } else if (y < 30) {
    carBackward();
    Serial.println("carBackward");
  } else if (x < 30) {
    carLeft();
    Serial.println("carLeft");
  } else if (x > 70) {
    carRight();
    Serial.println("carRight");
  } else if (x < 70 && x > 30 && y < 70 && y > 30) {
    carStop();
    Serial.println("carStop");
  }
}

void loop() {
  Blynk.run(); 
  smartcar();  
}


void carForward() {
  ledcWrite(0, Speed);
  ledcWrite(1, 0);
  ledcWrite(2, Speed);
  ledcWrite(3, 0);
}


void carBackward() {
  ledcWrite(0, 0);
  ledcWrite(1, Speed);
  ledcWrite(2, 0);
  ledcWrite(3, Speed);
}


void carLeft() {
  ledcWrite(0, 0);
  ledcWrite(1, Speed);
  ledcWrite(2, Speed);
  ledcWrite(3, 0);
}


void carRight() {
  ledcWrite(0, Speed);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, Speed);
}

void carStop() {
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
}

#include <Servo.h>

// SETTINGS ////////////////////////////////////////////////////////////////////

#define gameRunTimeMS       60000ul // 1000 * 60 * 1 minutes
#define trunkMoveSpeed      1000
#define minX                0
#define maxX                180
#define minY                140
#define maxY                180

// PINS ////////////////////////////////////////////////////////////////////////

#define RED_LED_PIN         11
#define GREEN_LED_PIN       10
#define SWITCH_PIN          8
#define SERVO_1_PIN         3
#define SERVO_2_PIN         6

Servo servo1;
Servo servo2;

unsigned long gameStartMS = 0;
unsigned long elapsed = 0;
bool gameRunning = false;

void setup() {

  Serial.begin(115200);
  
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  
  servo1.attach(SERVO_1_PIN);
  servo2.attach(SERVO_2_PIN);

  servo1.write(90);
  servo2.write(180);
}

void loop() {

  /*
  Serial.print("Switch: ");
  Serial.print(digitalRead(SWITCH_PIN));
  Serial.print(", gameRunning: ");
  Serial.println(gameRunning);
  */
  
  if (gameRunning == false) {

    if (!digitalRead(SWITCH_PIN)) {

      gameStartMS = millis();
      gameRunning = true;
    }
    
  } else {

    elapsed = millis() - gameStartMS;
    
    /*
    Serial.print(gameStartMS);
    Serial.print(", ");
    Serial.print(millis());
    Serial.print(", ");
    Serial.println(elapsed);
    */
    
    if (digitalRead(SWITCH_PIN) || (elapsed > gameRunTimeMS)) {

      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, LOW);
      gameRunning = false;
      servo1.write(90);
      servo2.write(0); 

      while (!digitalRead(SWITCH_PIN)) {
        
        delay(1);
      }
      
    } else {

      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(RED_LED_PIN, LOW);
      servo1.write(int(random(0, 180)));
      servo2.write(int(random(60, 180))); 
      delay(trunkMoveSpeed);
    }
  }
}


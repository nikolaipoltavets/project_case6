#include <Keypad.h>
#include <Servo.h>
#include <Stepper.h>

Servo myServo;

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {7, 6, 5, 4};    
byte colPins[COLS] = {3, 2, 1, 0};    

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const String correctPin = "77"; 
String inputCode = "";    

int count = 0;

const int servoPin = 9;         
const int servoOpenAngle = 90;   
const int servoCloseAngle = 0;  
const unsigned long openTime = 3500; 
const int stepsPerRevolution = 2038*3.2;

Stepper myStepper(stepsPerRevolution, 10, 12, 11, 13);

void stopen() {
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(19, OUTPUT);
  myServo.attach(servoPin);      
//  myServo.write(servoOpenAngle); /
//  delay(500);/
  myServo.write(servoCloseAngle); 
  myStepper.setSpeed(9);
  pinMode(18, OUTPUT);
}

void loop() {
  char key = keypad.getKey();

  if (Serial.available()) {
    String com = Serial.readStringUntil('\n');
    if(com == "1") {
      activateMoto();
    }
  }

  if (key) { 
    Serial.println(key);
    if (key == '*') { 
      Serial.println(inputCode);
      if (inputCode == correctPin) {
        
        activateServo();
      } else {
         digitalWrite(18, 1);
        delay(1000);
        digitalWrite(18, 0);
        delay(100);
      }
      inputCode = ""; 
    } else if (key == '*') { 
      inputCode = "";
    } else {
      inputCode += key; 
    }
  }
}

void activateMoto() {
  count=count+1;
  Serial.println(count);
  Serial.println(count%2);
  if(count%2 == 0) {
    digitalWrite(19, HIGH);
    myStepper.step(stepsPerRevolution);// Открытие
    stopen() ;
    digitalWrite(19, LOW);
    delay(2000);
    digitalWrite(19, HIGH);
    myStepper.step(-stepsPerRevolution/2);// Закрытие
    stopen() ;
    digitalWrite(19, LOW);
    delay(1000);
    digitalWrite(19, HIGH);
    myStepper.step(stepsPerRevolution/2);
    stopen() ;
    digitalWrite(19, LOW);
    delay(2000);
    digitalWrite(19, HIGH);
    myStepper.step(-stepsPerRevolution);
    stopen() ;
    digitalWrite(19, LOW);
  } else {
    digitalWrite(19, HIGH);
    myStepper.step(stepsPerRevolution);// Открытие
    stopen() ;
    digitalWrite(19, LOW);
    delay(2000);
    digitalWrite(19, HIGH);
    myStepper.step(-stepsPerRevolution);// Закрытие
    stopen() ;
    digitalWrite(19, LOW);
    delay(1000);
  }
}

void activateServo() {
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 0);
  delay(100);
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 0);
  delay(100);
  digitalWrite(18, 1);
  delay(100);
  myServo.write(servoOpenAngle);
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 0);
  delay(100);
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 0);
  delay(100);
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 0);
  delay(100);
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 0);
  delay(100);
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 0);
  delay(100);
  delay(openTime);
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 0);
  delay(100);
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 0);
  delay(100);
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 0);
  delay(100);
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 0);
  delay(100);
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 0);
  delay(100);
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 0);
  delay(100);
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 0);
  delay(100);
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 0);
  delay(100);
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 0);
  delay(100);
  digitalWrite(18, 1);
  delay(100);
  digitalWrite(18, 0);
  delay(100);
  myServo.write(servoCloseAngle);
  delay(openTime);// Закрытие
}

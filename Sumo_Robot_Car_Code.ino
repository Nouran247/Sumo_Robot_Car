// Sumo Robot Car Code

#include <Ps3Controller.h>
#include <dummy.h>
#include <EEPROM.h>

// ===================== Motor Pins ===================== //

// Front Right Motor
const int FR_FORWARD   = 16;
const int FR_BACKWARD  = 17;
const int FR_PWM       = 15;

// Front Left Motor
const int FL_FORWARD   = 25;
const int FL_BACKWARD  = 33;
const int FL_PWM       = 32;

// Back Left Motor
const int BL_FORWARD   = 26;
const int BL_BACKWARD  = 27;
const int BL_PWM       = 13;

// Back Right Motor
const int BR_FORWARD   = 19;
const int BR_BACKWARD  = 18;
const int BR_PWM       = 22;

// PWM Channels
const int CH_FR = 0;
const int CH_FL = 1;
const int CH_BL = 2;
const int CH_BR = 3;

// PWM Config
const int PWM_FREQ = 500;
const int PWM_RES  = 8;

// ===================== Sensor Pins ===================== //
const int SENSOR_FRONT = 2;
const int SENSOR_RIGHT = 21;

// ===================== Color Enum ===================== //
enum Color { WHITE = 0, BLACK = 1 };

// ===================== Setup ===================== //

void onConnect() {
  Serial.println("PS3 controller connected.");
}

void setup() {
  Serial.begin(115200);

  // Motor Direction Pins
  pinMode(FR_FORWARD, OUTPUT); pinMode(FR_BACKWARD, OUTPUT);
  pinMode(FL_FORWARD, OUTPUT); pinMode(FL_BACKWARD, OUTPUT);
  pinMode(BL_FORWARD, OUTPUT); pinMode(BL_BACKWARD, OUTPUT);
  pinMode(BR_FORWARD, OUTPUT); pinMode(BR_BACKWARD, OUTPUT);

  // PWM Setup
  ledcSetup(CH_FR, PWM_FREQ, PWM_RES);
  ledcSetup(CH_FL, PWM_FREQ, PWM_RES);
  ledcSetup(CH_BL, PWM_FREQ, PWM_RES);
  ledcSetup(CH_BR, PWM_FREQ, PWM_RES);

  ledcAttachPin(FR_PWM, CH_FR);
  ledcAttachPin(FL_PWM, CH_FL);
  ledcAttachPin(BL_PWM, CH_BL);
  ledcAttachPin(BR_PWM, CH_BR);

  // Sensor Setup
  pinMode(SENSOR_FRONT, INPUT);
  pinMode(SENSOR_RIGHT, INPUT);

  // PS3 Controller
  Ps3.attach(onConnect);
  Ps3.begin("ec:62:60:a2:60:f8");
}

// ===================== Main Loop ===================== //

void loop() {
  int frontColor = digitalRead(SENSOR_FRONT);
  int rightColor = digitalRead(SENSOR_RIGHT);

  if (Ps3.isConnected()) {
    int leftY  = Ps3.data.analog.stick.ly;
    int rightX = Ps3.data.analog.stick.rx;
    int R1     = Ps3.data.button.r1;
    int R2     = Ps3.data.button.r2;

    stopMotors();

    // Forward/Backward
    if (leftY < -10) {
      R1 ? moveForward(250) : moveForward((leftY * -1.5) + 5);
    }
    else if (leftY > 10) {
      R2 ? moveBackward(230) : moveBackward((leftY * 1.2) - 5);
    }

    // Turning
    else if (rightX > 10) {
      rightX <= 100 ? turnRight(110 - rightX) : turnRight(-150);
    }
    else if (rightX < -10) {
      rightX >= -100 ? turnLeft(110 + rightX) : turnLeft(-150);
    }
    else {
      stopMotors();
    }
  }
}

// ===================== Motion Functions ===================== //

void stopMotors() {
  digitalWrite(FR_FORWARD, LOW); digitalWrite(FR_BACKWARD, LOW);
  digitalWrite(FL_FORWARD, LOW); digitalWrite(FL_BACKWARD, LOW);
  digitalWrite(BL_FORWARD, LOW); digitalWrite(BL_BACKWARD, LOW);
  digitalWrite(BR_FORWARD, LOW); digitalWrite(BR_BACKWARD, LOW);
}

void moveForward(int speed) {
  digitalWrite(FR_FORWARD, HIGH); digitalWrite(FR_BACKWARD, LOW); ledcWrite(CH_FR, speed);
  digitalWrite(FL_FORWARD, HIGH); digitalWrite(FL_BACKWARD, LOW); ledcWrite(CH_FL, speed);
  digitalWrite(BL_FORWARD, HIGH); digitalWrite(BL_BACKWARD, LOW); ledcWrite(CH_BL, speed);
  digitalWrite(BR_FORWARD, HIGH); digitalWrite(BR_BACKWARD, LOW); ledcWrite(CH_BR, speed);
}

void moveBackward(int speed) {
  digitalWrite(FR_FORWARD, LOW); digitalWrite(FR_BACKWARD, HIGH); ledcWrite(CH_FR, speed);
  digitalWrite(FL_FORWARD, LOW); digitalWrite(FL_BACKWARD, HIGH); ledcWrite(CH_FL, speed);
  digitalWrite(BL_FORWARD, LOW); digitalWrite(BL_BACKWARD, HIGH); ledcWrite(CH_BL, speed);
  digitalWrite(BR_FORWARD, LOW); digitalWrite(BR_BACKWARD, HIGH); ledcWrite(CH_BR, speed);
}

void turnRight(int speed) {
  if (speed >= 0) {
    digitalWrite(FR_FORWARD, HIGH); digitalWrite(FR_BACKWARD, LOW); ledcWrite(CH_FR, speed);
    digitalWrite(BR_FORWARD, HIGH); digitalWrite(BR_BACKWARD, LOW); ledcWrite(CH_BR, speed);
  } else {
    digitalWrite(FR_FORWARD, LOW); digitalWrite(FR_BACKWARD, HIGH); ledcWrite(CH_FR, abs(speed));
    digitalWrite(BR_FORWARD, LOW); digitalWrite(BR_BACKWARD, HIGH); ledcWrite(CH_BR, abs(speed));
  }
  digitalWrite(FL_FORWARD, HIGH); digitalWrite(FL_BACKWARD, LOW); ledcWrite(CH_FL, 250);
  digitalWrite(BL_FORWARD, HIGH); digitalWrite(BL_BACKWARD, LOW); ledcWrite(CH_BL, 250);
}

void turnLeft(int speed) {
  if (speed >= 0) {
    digitalWrite(FL_FORWARD, HIGH); digitalWrite(FL_BACKWARD, LOW); ledcWrite(CH_FL, speed);
    digitalWrite(BL_FORWARD, HIGH); digitalWrite(BL_BACKWARD, LOW); ledcWrite(CH_BL, speed);
  } else {
    digitalWrite(FL_FORWARD, LOW); digitalWrite(FL_BACKWARD, HIGH); ledcWrite(CH_FL, abs(speed));
    digitalWrite(BL_FORWARD, LOW); digitalWrite(BL_BACKWARD, HIGH); ledcWrite(CH_BL, abs(speed));
  }
  digitalWrite(FR_FORWARD, HIGH); digitalWrite(FR_BACKWARD, LOW); ledcWrite(CH_FR, 250);
  digitalWrite(BR_FORWARD, HIGH); digitalWrite(BR_BACKWARD, LOW); ledcWrite(CH_BR, 250);
}

#include <EEPROM.h>

// Front right motor pins
const int m_frontRight_forward = 8;
const int m_frontRight_backwards = 9;

// Front left motor pins
const int m_frontLeft_forward = 7;
const int m_frontLeft_backwards = 6;

// Back left motor pins
const int m_backLeft_forward = 10;
const int m_backLeft_backwards = 11;

// Back right motor pins
const int m_backRight_forward = 12;
const int m_backRight_backwards = 13;

// Sensor pins (reassigned to analog pins)
const int sensor_back = A0;
const int sensor_right = A1;
const int sensor_left = A2;

enum color {
  white = 0,
  black = 1
};

void setup() {
  Serial.begin(9600);

  // Motor setup
  pinMode(m_frontRight_forward, OUTPUT);
  pinMode(m_frontRight_backwards, OUTPUT);
  pinMode(m_frontLeft_forward, OUTPUT);
  pinMode(m_frontLeft_backwards, OUTPUT);
  pinMode(m_backLeft_forward, OUTPUT);
  pinMode(m_backLeft_backwards, OUTPUT);
  pinMode(m_backRight_forward, OUTPUT);
  pinMode(m_backRight_backwards, OUTPUT);

  // Sensor setup
  pinMode(sensor_back, INPUT);
  pinMode(sensor_right, INPUT);
  pinMode(sensor_left, INPUT);
}

void loop() {
  int front_sensor = analogRead(sensor_back);
  int right_sensor = analogRead(sensor_right);
  int left_sensor = analogRead(sensor_left);

  // Simple thresholding for sensor colors
  int threshold = 512;
  int back_sensor_color = (front_sensor > threshold) ? white : black;
  int right_sensor_color = (right_sensor > threshold) ? white : black;
  int left_sensor_color = (left_sensor > threshold) ? white : black;

  // Motor control logic
  if (back_sensor_color == black) {
    move_backwards();
    delay(250);
    turn_right();
    delay(250);
  } else if (left_sensor_color == black) {
    turn_right();
    delay(250);
  } else if (right_sensor_color == black) {
    turn_left();
    delay(250);
  } else {
    move_forward();
  }

  delay(50);
  stop_motors();
}

void stop_motors() {
  digitalWrite(m_frontRight_forward, LOW);
  digitalWrite(m_frontRight_backwards, LOW);
  digitalWrite(m_frontLeft_forward, LOW);
  digitalWrite(m_frontLeft_backwards, LOW);
  digitalWrite(m_backLeft_forward, LOW);
  digitalWrite(m_backLeft_backwards, LOW);
  digitalWrite(m_backRight_forward, LOW);
  digitalWrite(m_backRight_backwards, LOW);
}

void move_forward() {
  digitalWrite(m_frontRight_forward, HIGH);
  digitalWrite(m_frontRight_backwards, LOW);
  digitalWrite(m_frontLeft_forward, HIGH);
  digitalWrite(m_frontLeft_backwards, LOW);
  digitalWrite(m_backLeft_forward, HIGH);
  digitalWrite(m_backLeft_backwards, LOW);
  digitalWrite(m_backRight_forward, HIGH);
  digitalWrite(m_backRight_backwards, LOW);
}

void move_backwards() {
  digitalWrite(m_frontRight_forward, LOW);
  digitalWrite(m_frontRight_backwards, HIGH);
  digitalWrite(m_frontLeft_forward, LOW);
  digitalWrite(m_frontLeft_backwards, HIGH);
  digitalWrite(m_backLeft_forward, LOW);
  digitalWrite(m_backLeft_backwards, HIGH);
  digitalWrite(m_backRight_forward, LOW);
  digitalWrite(m_backRight_backwards, HIGH);
}

void turn_right() {
  digitalWrite(m_frontRight_forward, LOW);
  digitalWrite(m_frontRight_backwards, LOW);
  digitalWrite(m_frontLeft_forward, HIGH);
  digitalWrite(m_frontLeft_backwards, LOW);
  digitalWrite(m_backLeft_forward, HIGH);
  digitalWrite(m_backLeft_backwards, LOW);
  digitalWrite(m_backRight_forward, LOW);
  digitalWrite(m_backRight_backwards, LOW);
}

void turn_left() {
  digitalWrite(m_frontRight_forward, HIGH);
  digitalWrite(m_frontRight_backwards, LOW);
  digitalWrite(m_frontLeft_forward, LOW);
  digitalWrite(m_frontLeft_backwards, LOW);
  digitalWrite(m_backLeft_forward, LOW);
  digitalWrite(m_backLeft_backwards, LOW);
  digitalWrite(m_backRight_forward, HIGH);
  digitalWrite(m_backRight_backwards, LOW);
}

#include <Servo.h>

Servo myServo;

const int trigPin = 10;
const int echoPin = 11;
const int servoPin = 9;
const int ledPin = 7;

long duration;
float distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(0); // الوضع الابتدائي

  digitalWrite(ledPin, LOW);

  Serial.begin(9600);
}

void loop() {

  // إرسال نبضة إلى حساس HC-SR04
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // قراءة زمن رجوع الموجة
  duration = pulseIn(echoPin, HIGH);

  // حساب المسافة بالسنتيمتر
  distance = duration * 0.0343 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // التحكم في السيرفو والـ LED
  if (distance <= 10) {
    myServo.write(180);          // تحريك السيرفو إلى 90 درجة
    digitalWrite(ledPin, HIGH); // تشغيل LED
  } else {
    myServo.write(0);           // إعادة السيرفو للوضع الأصلي
    digitalWrite(ledPin, LOW);  // إطفاء LED
  }

  delay(200);
}
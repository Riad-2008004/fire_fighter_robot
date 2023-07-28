#include <Servo.h>
Servo myservo;

int pos = 0;

boolean fire = false;

const int Left_S = 9;
const int Right_S = 10;
const int Forward_S = 8;
const int LM1 = 2;
const int LM2 = 3;
const int RM1 = 4;
const int RM2 = 5;
const int pump = 6;

void setup()
{
  Serial.begin(9600);
  pinMode(Left_S, INPUT);
  pinMode(Right_S, INPUT);
  pinMode(Forward_S, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);

  myservo.attach(11);
  myservo.write(90);
}


void loop()
{
  int sensorstatus2 = digitalRead(Left_S);
  int sensorstatus1 = digitalRead(Right_S);
  int sensorstatus3 = digitalRead(Forward_S);
  myservo.write(90);

  if (sensorstatus1 == 1 && sensorstatus2 == 1 && sensorstatus3 == 1)
  {

    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
  }

  else if (sensorstatus3 == 0)
  {

    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    fire = true;
  }

  else if ( sensorstatus2 == 0)
  {

    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
  }

  else if ( sensorstatus1 == 0)
  {

    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
  }

  delay(300);

  while (fire == true)
  {
    {
      delay (500);

      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, HIGH);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, HIGH);

      analogWrite(pump, 255); delay(400);
      Serial.println("The pump is ON");

      for (pos = 80; pos <= 100; pos += 1)
      {
        myservo.write(pos);
        delay(15);
      }
      for (pos = 100; pos >= 80; pos -= 1)
      {
        myservo.write(pos);
        delay(15);
      }

      analogWrite(pump, 0);
      Serial.println("The pump is OFF");

      fire = false;
    }
    myservo.write(90);
  }
}

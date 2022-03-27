#include "L298N.h"
#include <Servo.h>

//舵机
 const int servo_pin=4;
 Servo myservo;
//
//const int ENA=10;
const int IN1=9;
const int IN2=8;

L298N motor(IN1,IN2);

void setup(){
    Serial.begin(9600);
//    motor.setSpeed(255);
     myservo.attach(servo_pin);
     myservo.write(180);
     Serial.println("Please put in data.");
}

void loop(){
    if(Serial.available()){
        char s=Serial.read();
        if(s=='0'){
            motor.forward();
            delay(100);
             myservo.write(0);
            delay(1000);
            delay(1000);
            motor.backward();
            delay(1000);
            myservo.write(180);
            motor.stop();
        }
    }
}

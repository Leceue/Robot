#include "L298N.h"
#include <Servo.h>

//舵机
 const int servo_pin=2;
 Servo myservo;

//const int ENA=10;
const int IN1=41;
const int IN2=43;

L298N motor(IN1,IN2);

void setup(){
    Serial.begin(9600);
     myservo.attach(servo_pin);
     myservo.write(180);
     Serial.println("Please put in data.");
}

void loop(){
    if(Serial.available()){
        char s=Serial.read();
        if(s=='0'){
            motor.forward();
//              motor.backwardB();

//            delay(100);
//             myservo.write(0);
//            delay(1000);
//            delay(1000);
//            motor.backwardB();
//            delay(100);
//            motor.stop();
//            delay(100);
//            myservo.write(180);

            delay(100);
            myservo.write(45);
            delay(1500);
            motor.backward();
//            motor.forwardB();
            delay(70);
            motor.stop();
            
            myservo.write(0);
//            delay(100);
            motor.stop();
            delay(1000);
            myservo.write(180);
        }
    }
}
// Test1

//            delay(1000);
//            motor.backwardB();
//            delay(100);
//            motor.stop();

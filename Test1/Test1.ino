#include <Servo.h>

//舵机
const int servo_pin=4;
Servo myservo;

void setup(){
    Serial.begin(9600);
    myservo.attach(servo_pin);
    myservo.write(120);
    Serial.println("Please put in data.");
}

void loop(){
    if(Serial.available()){
        char s=Serial.read();
        if(s=='A'){
            myservo.write(0);
        }
        if(s=='B'){
            myservo.write(120);
        }
        delay(50);
    }
}
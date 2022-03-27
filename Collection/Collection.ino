#include "L298NX2.h"
#include "PS2X_lib.h"
#include <Servo.h>

//motor1
const int EN1_A=24;
const int IN1_1=5;
const int IN2_1=4;
const int IN3_1=3;
const int IN4_1=2;
const int EN1_B=22;

L298NX2 driver_1(EN1_A,IN1_1,IN2_1,EN1_B,IN3_1,IN4_1);
//motor1：左侧两个轮子的控制
//左前 IN3 IN4
//左后 IN1 IN2

//motor2
const int EN2_A=43;
const int IN1_2=45;
const int IN2_2=47;
const int IN3_2=51;
const int IN4_2=49;
const int EN2_B=53;

L298NX2 driver_2(EN2_A,IN1_2,IN2_2,EN2_B,IN3_2,IN4_2);
//motor2：右侧两个轮子的控制
//右前 IN1 IN2
//右后 IN3 IN4

//ps2_control
const int PS2_DAT=6;
const int PS2_CMD=7;
const int PS2_SEL=8;
const int PS2_CLK=9;

//舵机引脚
const int D_Right=52;
const int D_Left=50;
Servo DJ_Right,DJ_Left;

#define pressures true
#define rumble false

PS2X ps2x;

int error=0;
int type=0;
byte vibrate=0;
int speed=180;

void (*resetFunc) (void)=0;

void setup(){
    Serial.begin(115200);

    delay(500);

    error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

    if(error == 0){
        Serial.print("Found Controller, configured successful ");
        Serial.print("pressures = ");
        if (pressures)
            Serial.println("true ");
        else
            Serial.println("false");
        Serial.print("rumble = ");
        if (rumble)
            Serial.println("true)");
        else
            Serial.println("false");
            Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
            Serial.println("holding L1 or R1 will print out the analog stick values.");
            Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
    }  
    else if(error == 1)
        Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

    else if(error == 2)
        Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

    else if(error == 3)
        Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

    type = ps2x.readType(); 
    switch(type) {
        case 0:
            Serial.println("Unknown Controller type found ");
            break;
        case 1:
            Serial.println("DualShock Controller found ");
            break;
        case 2:
            Serial.println("GuitarHero Controller found ");
            break;
        case 3:
            Serial.println("Wireless Sony DualShock Controller found ");
            break;
    }
    driver_1.setSpeedA(speed);
    driver_1.setSpeedB(speed);
    driver_2.setSpeedA(speed);
    driver_2.setSpeedB(speed);
    DJ_Right.attach(D_Right);
    DJ_Left.attach(D_Left);
    DJ_Right.write(90);
    DJ_Left.write(90);
}

void loop(){
    if(error==1) resetFunc();
    if(type==1){
        ps2x.read_gamepad(false,vibrate);
        if(ps2x.Button(PSB_PAD_UP)){
            driver_1.forwardA();
            driver_1.forwardB();
            driver_2.forwardA();
            driver_2.forwardB();
            Serial.println("前进");
        }
        if(ps2x.Button(PSB_PAD_DOWN)){
            driver_1.backwardA();
            driver_1.backwardB();
            driver_2.backwardA();
            driver_2.backwardB();
            Serial.println("后退");
        }
        if(ps2x.Button(PSB_PAD_LEFT)){
            driver_1.backwardB();
            driver_1.forwardA();
            driver_2.forwardA();
            driver_2.backwardB();
            Serial.println("左移");
        }
        if(ps2x.Button(PSB_PAD_RIGHT)){
            driver_1.forwardB();
            driver_1.backwardA();
            driver_2.backwardA();
            driver_2.forwardB();
            Serial.println("右移");
        }
        if(ps2x.Button(PSB_SQUARE)){
            driver_1.setSpeedA(130);
            driver_1.setSpeedB(130);
            driver_2.setSpeedA(130);
            driver_2.setSpeedB(130);
            driver_1.backwardB();
            driver_1.backwardA();
            driver_2.forwardA();
            driver_2.forwardB();
            Serial.println("左转");
        }
        if(ps2x.Button(PSB_CIRCLE)){
            driver_1.setSpeedA(130);
            driver_1.setSpeedB(130);
            driver_2.setSpeedA(130);
            driver_2.setSpeedB(130);
            driver_1.forwardB();
            driver_1.forwardA();
            driver_2.backwardA();
            driver_2.backwardB();
            Serial.println("右转");
        }
        if(ps2x.Button(PSB_GREEN)){
            if(speed<=240) speed+=10;
            driver_1.setSpeedA(speed);
            driver_1.setSpeedB(speed);
            driver_2.setSpeedA(speed);
            driver_2.setSpeedB(speed);
            Serial.println("加速");
        }
        if(ps2x.Button(PSB_CROSS)){
            if(speed>=90) speed-=10;
            driver_1.setSpeedA(speed);
            driver_1.setSpeedB(speed);
            driver_2.setSpeedA(speed);
            driver_2.setSpeedB(speed);
            Serial.println("减速");
        }
        if(ps2x.Button(PSB_R1)){
            DJ_Right.write(90);
            DJ_Left.write(90);
        }
        if(ps2x.Button(PSB_R2)){
            DJ_Right.write(0);
            DJ_Left.write(180);
        }
        delay(50);
        driver_1.setSpeedA(speed);
        driver_1.setSpeedB(speed);
        driver_2.setSpeedA(speed);
        driver_2.setSpeedB(speed);
        driver_1.stop();
        driver_2.stop();
    }
}

#include <Arduino.h>
#include <Bounce2.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

#define LIGHT1 26
#define LIGHT2 25
#define LIGHT3 33
//threshold 35
#define SWITCH1 0 //T0
#define SWITCH2 2 //T1
#define SWITCH3 15 //T2

const int threshold =  40; 

void Connect_Wifi(const char* ssid,const char* password){
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
    Serial.println(WiFi.localIP());
}

void main_task(void *param){//will run in paralelled

}


void setup() {
    Serial.begin(115200);
    pinMode(LIGHT1,OUTPUT);
    pinMode(LIGHT2,OUTPUT);
    pinMode(LIGHT3,OUTPUT);
    Connect_Wifi("OPPO_KUY","oppopass");
    xTaskCreatePinnedToCore(main_task, "main_task", 10000, NULL, 1, NULL, 0);
    touchAttachInterrupt(T0, click1, threshold);
    touchAttachInterrupt(T1, click2, threshold);
    touchAttachInterrupt(T2, click3, threshold);
    
}

void loop() {    
 Serial.println(touchRead(T0) );
 delay(200);

 Serial.println(touchRead(T1) );
 delay(200);

 Serial.println(touchRead(T2) );
 delay(200);

}

void click1() {
    if (mode1 == "MANUAL"){
        if (digitalRead(LIGHT1) == 1){
            digitalWrite(LIGHT1,LOW);
        }else if (digitalRead(LIGHT1) == 0){
            digitalWrite(LIGHT1,HIGH);
    }
    Serial.println("click!");
    }
}

void click2() {
    if (mode2 == "MANUAL") {
            if (digitalRead(LIGHT2) == 1){
            digitalWrite(LIGHT2,LOW);
        }else if (digitalRead(LIGHT2) == 0){
            digitalWrite(LIGHT2,HIGH);
    }
    Serial.println("click!");
    }
    
}

void click3() {
    if (mode3 == "MANUAL"){
        if (digitalRead(LIGHT3) == 1){
            digitalWrite(LIGHT3,LOW);
        }else if (digitalRead(LIGHT3) == 0){
            digitalWrite(LIGHT3,HIGH);
    }
    Serial.println("click!");
    }
}
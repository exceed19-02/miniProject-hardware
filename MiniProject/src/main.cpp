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
    
}



void loop() {

}
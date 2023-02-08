#include <Arduino.h>
#include <Bounce2.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#define RED 26
#define YELLOW 25
#define GREEN 33
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
    pinMode(RED,OUTPUT);
    pinMode(YELLOW,OUTPUT);
    pinMode(GREEN,OUTPUT);
    Connect_Wifi("OPPO_KUY","oppopass");
    xTaskCreatePinnedToCore(main_task, "main_task", 10000, NULL, 1, NULL, 0);
    
}



void loop() {

}
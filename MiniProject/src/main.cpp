#include <Arduino.h>
#include <Bounce2.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#define LDR 34
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

// from 1-3
int light_id1, light_id2, light_id3;
bool status1, status2, status3;
String mode1, mode2, mode3;
int brightness1, brightness2, brightness3;

void GET_Data(int light_id){
    while(1){
        DynamicJsonDocument doc(2048);
        HTTPClient http;
        const String url = "http://group2.exceed19.online";
        http.begin(url);

        int httpResponseCode = http.GET();
        if (httpResponseCode >= 200 && httpResponseCode < 300) {
            Serial.print("HTTP ");
            Serial.println(httpResponseCode);
            String payload = http.getString();
            deserializeJson(doc, payload);

            light_id1 = doc[0]["light_id1"];
            light_id2 = doc[0]["light_id2"];
            light_id3 = doc[0]["light_id3"];

            status1 = doc[1]["status1"];
            status2 = doc[1]["status2"];
            status3 = doc[1]["status3"];

            mode1 = (const char *)doc[2]["mode1"];
            mode2 = (const char *)doc[2]["mode2"];
            mode3 = (const char *)doc[2]["mode3"];


            brightness1 = doc[3]["brightness1"];
            brightness2 = doc[3]["brightnes2"];
            brightness3 = doc[3]["brightnes3"];
            // *** write your code here ***
            // set up JSON
            Serial.println(payload);
            
    
        }else{
            Serial.print("Error ");
            Serial.println(httpResponseCode);
        }

        Serial.println("----------------------------------");
    }
}



void main_task(void *param){//will run in paralelled
    while(1){
        int ldr = map(analogRead(LDR),3500,4095,0,255);
        if (ldr<0){
            ldr = 0;
        }
        //manual never run in here,disregard switch
        //ROOM1 , LIGHT1
        if(mode1=="auto"){
            if (ldr < 10){
                digitalWrite(LIGHT1, HIGH);
            }
            else {
                digitalWrite(LIGHT1,LOW);
            
            if (ldr < 10){
                digitalWrite(LIGHT2, HIGH);
            }
            else {
                digitalWrite(LIGHT2,LOW);

            if (ldr < 10){
                digitalWrite(LIGHT3, HIGH);
            }
            else {
                digitalWrite(LIGHT3,LOW);

        }
        if(mode1=="disco"){

        }

        //ROOM2 , LIGHT2

        //ROOM3 , LIGHT3
    }
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
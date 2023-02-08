#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>

const String baseUrl = "http://group2.exceed19.online";

int light_id; // from 1-3
bool status;
String mode;

void GET_Data(int light_id){
    while(1){
        DynamicJsonDocument doc(2048);
        HTTPClient http;
        const String url = baseUrl;
        http.begin(url);

        int httpResponseCode = http.GET();
        if (httpResponseCode >= 200 && httpResponseCode < 300) {
            Serial.print("HTTP ");
            Serial.println(httpResponseCode);
            String payload = http.getString();
            deserializeJson(doc, payload);

            // *** write your code here ***
            // set up JSON
            Serial.println();
            Serial.println((int)doc["light_id"]);
            Serial.println((bool)doc["status"]);
            Serial.println((const char *)doc["mode"]);

            light_id = (int)doc["light_id"];
            status = (bool)doc["status"];
            mode = (const char*)doc["mode"];
            
    
        }else{
            Serial.print("Error ");
            Serial.println(httpResponseCode);
        }

        Serial.println("----------------------------------");
    }
}

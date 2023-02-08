#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>

const String baseUrl = "http://group2.exceed19.online";

// from 1-3
int light_id1, light_id2, light_id3;
bool status1, status2, status3;
String mode1, mode2, mode3;
int brightness1, brightness2, brightness3;

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

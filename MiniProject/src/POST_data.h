#include <Arduino.h>
#include <Bounce2.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

void POST_data(int light_id, bool status, String mode, int brightness){
/*
light_id : int (1-3)
status : bool[True: เปิด, False: ปิด]
mode : enum[“AUTO”,”MANUAL”,”DISCO”]
brightness : int(0-100)

*/
    String url="<Request for post url>";
    String json;//body for post request
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    DynamicJsonDocument doc(2048);
    doc["light_id"] = light_id;
    doc["status"] = status;
    doc["mode"] = mode;
    doc["brightness"] = brightness;

    serializeJson(doc, json);
    int httpCode = http.POST(json);
    if (httpCode/100==2) {
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
    } else {
        Serial.println("Error on HTTP request");
    }
}
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
#define SWITCH1 0 //T1
#define SWITCH2 2 //T2
#define SWITCH3 15 //T3
bool prev_SWITCH1=false,prev_SWITCH2=false,prev_SWITCH3=false;
bool curr_SWITCH1=false,curr_SWITCH2=false,curr_SWITCH3=false;

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
TaskHandle_t getdata=NULL;
/*
http://group2.exceed19.online/ 
http://ecourse.cpe.ku.ac.th/exceed02/
*/

int ldr_value(){
    int ldr = map(analogRead(LDR),3500,4095,0,100);
    if(ldr<0)ldr=0;
    return ldr;
}

void GET_Data(void *param){
    while(1){
        DynamicJsonDocument doc(2048);
        HTTPClient http;
        const String url = "https://ecourse.cpe.ku.ac.th/exceed02/";
        http.begin(url);

        int httpResponseCode = http.GET();
        if (httpResponseCode >= 200 && httpResponseCode < 300) {
            Serial.print("HTTP ");
            Serial.println(httpResponseCode);
            String payload = http.getString();
            deserializeJson(doc, payload);

            light_id1 = doc[0]["light_id1"];
            light_id2 = doc[1]["light_id2"];
            light_id3 = doc[2]["light_id3"];

            status1 = doc[0]["status1"];
            status2 = doc[1]["status2"];
            status3 = doc[2]["status3"];

            mode1 = (const char *)doc[0]["mode1"];
            mode2 = (const char *)doc[1]["mode2"];
            mode3 = (const char *)doc[2]["mode3"];


            brightness1 = doc[0]["brightness1"];
            brightness2 = doc[1]["brightnes2"];
            brightness3 = doc[2]["brightnes3"];
            Serial.println(payload);
            
    
        }else{
            Serial.print("Error ");
            Serial.println(httpResponseCode);
        }

        Serial.println("----------------------------------");
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}
void PUT_Data(int light_id, bool status, String mode){//put = update
/*
light_id : int (1-3)
status : bool[True: เปิด, False: ปิด]
mode : enum[“AUTO”,”MANUAL”,”DISCO”]
brightness : int(0-100)


*/
    String url="https://ecourse.cpe.ku.ac.th/exceed02/update";
    String json;//body for post request
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    DynamicJsonDocument doc(2048);
    doc["light_id"] = light_id;
    doc["status"] = status;
    doc["mode"] = mode;
    doc["brightness"] = ldr_value();

    serializeJson(doc, json);
    int httpCode = http.PUT(json);
    if (httpCode/100==2) {
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
    } else {
        Serial.println("Error on HTTP request");
    }
}




//MANUAL
void update_touch1(void *param){
    while(1){
        curr_SWITCH1 = digitalRead(SWITCH1);
        if (curr_SWITCH1==true && prev_SWITCH1==false){
            if(mode1=="MANUAL"){
                if (digitalRead(LIGHT1) == 1){
                    digitalWrite(LIGHT1,LOW);
                    PUT_Data(1,false,"MANUAL");
                }else if (digitalRead(LIGHT1) == 0){
                    digitalWrite(LIGHT1,HIGH);
                    PUT_Data(1,true,"MANUAL");
                }
            }
        }
        prev_SWITCH1 = curr_SWITCH1;
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}
void update_touch2(void *param){
    while(1){
        curr_SWITCH2 = digitalRead(SWITCH2);
        if (curr_SWITCH2==true && prev_SWITCH2==false){
            if(mode2=="MANUAL"){
                if (digitalRead(LIGHT2) == 1){
                    digitalWrite(LIGHT2,LOW);
                    PUT_Data(2,false,"MANUAL");
                }else if (digitalRead(LIGHT2) == 0){
                    digitalWrite(LIGHT2,HIGH);
                    PUT_Data(2,true,"MANUAL");
                }
            }
        }
        prev_SWITCH2 = curr_SWITCH2;
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}
void update_touch3(void *param){
    while(1){
        curr_SWITCH3 = digitalRead(SWITCH3);
        if (curr_SWITCH3==true && prev_SWITCH3==false){
            if(mode3=="MANUAL"){
                if (digitalRead(LIGHT3) == 1){
                    digitalWrite(LIGHT3,LOW);
                    PUT_Data(3,false,"MANUAL");
                }else if (digitalRead(LIGHT3) == 0){
                    digitalWrite(LIGHT3,HIGH);
                    PUT_Data(3,true,"MANUAL");
                }
            }
        }
        prev_SWITCH3 = curr_SWITCH3;
        vTaskDelay(10/portTICK_PERIOD_MS);
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
            }
        }
        if(mode1=="disco"){

        }

        //ROOM2 , LIGHT2
        if(mode2=="auto"){
            if (ldr < 10){
                digitalWrite(LIGHT2, HIGH);
            }
            else {
                digitalWrite(LIGHT2,LOW);
            }
        }
        if(mode2=="disco"){

        }

        //ROOM3 , LIGHT3
        if(mode3=="auto"){
            if (ldr < 10){
                digitalWrite(LIGHT3, HIGH);
            }
            else {
                digitalWrite(LIGHT3,LOW);
            }
        }
        if(mode3=="disco"){

        }
    }
}



void setup() {
    Serial.begin(115200);
    pinMode(LIGHT1,OUTPUT);
    pinMode(LIGHT2,OUTPUT);
    pinMode(LIGHT3,OUTPUT);
    Connect_Wifi("OPPO_KUY","oppopass");
    xTaskCreatePinnedToCore(main_task, "main_task", 10000, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(GET_Data, "get_data", 10000, NULL, 1, &getdata, 0);
    
    //SWITCH TOUCH
    xTaskCreatePinnedToCore(update_touch1, "update_touch1", 10000, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(update_touch2, "update_touch2", 10000, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(update_touch3, "update_touch3", 10000, NULL, 1, NULL, 0);
    
}

void loop() {

}


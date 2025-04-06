#define relay0 LED_BUILTIN
#define relay1 14
#define relay2 15
#define relay3 16
#define trigP 17
#define echoP 18
#define ldrP 34
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>  // Include the mDNS library
#include <html.h>
#include <Preferences.h>
Preferences prefs;
const char* ssid = "realme P1 5G";  // WiFi SSID
const char* password = "";          // WiFi Password
int duration,distance,ldr,mode,new_distance;
bool r0,r1,r2,r3;
WebServer server(80);  // Create a web server on port 80
unsigned long timerStarttime = 0;  // Timer start time
unsigned long timerDuration = 0;  // Store user-input timer duration (in milliseconds)
unsigned int ap=0;
String state="off"; 
// Dummy sensor values for Auto Mode
int sensor1 = 12;
int sensor2 = 34;
void handleWifiPage(){
  server.send(200,"text/html",wifi);
}
void handleWifi(){
  if (server.hasArg("ssid") && server.hasArg("pass")) {
        String ssid = server.arg("ssid");
        String pass = server.arg("pass");
        WiFi.begin(ssid,pass);
        for(int i=0;WiFi.status()!=WL_CONNECTED && i<5;i++){
          delay(1000);
        }
        if(WiFi.status()==WL_CONNECTED){
          prefs.begin("wifi",false);
          prefs.putString("ssid",ssid);
          prefs.putString("pass",pass);
          prefs.end();
          ESP.restart();
        }

    } else {
        server.send(400, "text/html", "<h2>Bad Request</h2>");
    }
}
void handleRoot() {
    server.send(200, "text/html", html);
}

void handleToggleLED() {
  int r=server.arg("r").toInt();
  if(server.hasArg("r")){
    switch(r){
      case 0:
        r0=!r0;
        break;
      case 1:
        r1=!r1;
        break;
      case 2:
        r2=!r2;
        break;
      case 3:
        r3=!r3;
        break;
    }
    server.send(200, "text/plain","Toggled");
  }
  Serial.print("Relay States");
  Serial.println(r0);
  Serial.println(r1);
  Serial.println(r2);
  Serial.println(r3);
}

void handleStartTimer() {
  if (server.hasArg("time")) {
    int time = server.arg("time").toInt();  // Get time from the webpage
    timerDuration = time * 1000;  // Convert seconds to milliseconds
    timerStarttime = millis();  // Start timer
    server.send(200, "text/plain", "Timer Started for " + String(time) + " seconds");
  }
  Serial.print("Timer started for");
  Serial.println(timerDuration/1000);
}


void handleGetSensorData() {
  sensor1 = ldr;
  sensor2 = new_distance;
  String json = "{\"sensor1\": " + String(sensor1) + ", \"sensor2\": " + String(sensor2) + ", \"mode\":" + mode + ", \"state\":\""+state+"\"}";
  server.send(200, "application/json", json);
  Serial.println(json);
}
void handleMode(){
  if(server.hasArg("mode")){
    mode=server.arg("mode").toInt();
    server.send(200, "text/plain", "OK");
  }
  Serial.print("Mode=");
  Serial.println(mode);
}
void setup() {
  Serial.begin(115200);
  pinMode(relay0,OUTPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(ldrP,INPUT);
  pinMode(trigP,OUTPUT);
  pinMode(echoP,INPUT);
  // Connect to Wi-Fi
  prefs.begin("wifi",true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(prefs.getString("ssid",""), prefs.getString("pass",""));
  prefs.end();
  for(int i=0;WiFi.status()!=WL_CONNECTED && i<5;i++){
    delay(1000);
  }
  if(WiFi.status()!=WL_CONNECTED){
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("ESP32-Connect",NULL);
    IPAddress local_IP(192, 168, 4, 1);
    IPAddress gateway(192, 168, 4, 1);
    IPAddress subnet(255, 255, 255, 0); 
    WiFi.softAPConfig(local_IP, gateway, subnet);
    server.on("/", HTTP_GET, handleWifiPage);
    server.on("/wifi", HTTP_POST, handleWifi);
  }
  else{
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
  // Define routes
  server.on("/", handleRoot);
  server.on("/toggleLED", handleToggleLED);
  server.on("/startTimer", handleStartTimer);
  server.on("/getSensorData", handleGetSensorData);
  server.on("/changeMode",handleMode);
  }
  if (!MDNS.begin("esp32")) {  // Set the hostname to "esp32.local"
    Serial.println("Error starting mDNS");
  } else {
    Serial.println("mDNS responder started. Access via http://esp32.local");
  }
  MDNS.addService("_http","_tcp",80);
  MDNS.addServiceTxt("_http","_tcp","board","ESP32");
  server.begin();
}

void loop() {
  server.handleClient();
  switch(mode){
    case 0:
      digitalWrite(relay0,r0);
      digitalWrite(relay1,r1);
      digitalWrite(relay2,r2);
      digitalWrite(relay3,r3);
      break;
    case 1:
      if (timerStarttime > 0 && (millis() - timerStarttime) < timerDuration) {
        digitalWrite(relay0,HIGH);
        digitalWrite(relay1,HIGH);
        digitalWrite(relay2,HIGH);
        digitalWrite(relay3,HIGH);
      } 
      else if (timerStarttime > 0) {
        digitalWrite(relay0,LOW);
        digitalWrite(relay1,LOW);
        digitalWrite(relay2,LOW);
        digitalWrite(relay3,LOW);
        timerStarttime = 0;  // Reset the timer
        timerDuration = 0;  // Reset the duration
      }
      break;
    case 2:
      digitalWrite(trigP,LOW);
      delayMicroseconds(2);
      digitalWrite(trigP,HIGH);
      delayMicroseconds(10);
      digitalWrite(trigP,LOW);
      duration=pulseIn(echoP,HIGH);
      new_distance=duration*0.034/2;
      ldr=analogRead(ldrP);
      if(ldr>200 || new_distance!=distance){
        digitalWrite(relay0,HIGH);
        digitalWrite(relay1,HIGH);
        digitalWrite(relay2,HIGH);
        digitalWrite(relay3,HIGH);
        state="ON";
      }
      else{
        digitalWrite(relay0,LOW);
        digitalWrite(relay1,LOW);
        digitalWrite(relay2,LOW);
        digitalWrite(relay3,LOW);
        state="OFF";
      }
      distance=new_distance;
      break;
  }
}


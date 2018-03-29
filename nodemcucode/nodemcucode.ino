#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

const boolean HOTSPOT = true;

#if HOTSPOT
  char ssid[] = "";            // network SSID (name) 
  char pass[] = "";   // network password
#else
  char ssid[] = "";    // network SSID (name) 
  char pass[] = "";   // network password
#endif

int status = WL_IDLE_STATUS;
WiFiClient client;

const char *host = "maker.ifttt.com";

unsigned long myChannelNumber = 422727;
const char * myWriteAPIKey = "U13ZLEL8DFSJW86P";

int INPUT_PIN = 14; // using GPIO pin  as input (marked D5 on board)
int val = 0;

void setup() {
  initHardware();
  connectToWiFi();
}

void loop() {
  if(WiFi.status() == WL_CONNECTED){  // if connected to wifi
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off (LOW is the voltage level)
    val = 0;
    for(int i = 0; i < 6; i++){
      val += digitalRead(INPUT_PIN);
      delay(300);
    }
    val /= 6;
    Serial.println(val);
    
    if (val == 1){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      ThingSpeak.writeField(myChannelNumber, 1, val, myWriteAPIKey);
      sendText();
      delay(20000); // ThingSpeak will only accept updates every 20 seconds apparently
    }
    else if (val == 0){
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED LOW (HIGH is the voltage level)
      ThingSpeak.writeField(myChannelNumber, 1, val, myWriteAPIKey);
      delay(20000); // ThingSpeak will only accept updates every 20 seconds appparently
    }   
 }
 else{
    Serial.println("Error in WiFi connection");   
    return;
 }
}

void sendText(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  Serial.print("Connecting to ");
  Serial.println(host);
  
  const int httpPort = 80;
  if(!client.connect(host,httpPort)){
    Serial.println("Connection failed");
    for(int i = 0; i < 6; i++){
      digitalWrite(LED_BUILTIN, LOW);
      delay(300);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(300);
    }
    digitalWrite(LED_BUILTIN, LOW);
    return;
  }

  String url = "/trigger/fire/with/key/p6jLJhijKsaxu7xL_jMcbuyx-b-1JW8k0G3aV8VMwu8";

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  Serial.println();
  Serial.println("Closing connection");
  client.stop();
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  return;
}

void initHardware(){
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(INPUT_PIN, INPUT);
  Serial.begin(9600);
}

void connectToWiFi() {
  byte ledStatus = LOW;
  Serial.println();
  Serial.println("Attempting to connect to: " + String(ssid));
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid,pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    //Blink the LED
    digitalWrite(LED_BUILTIN, ledStatus);
    ledStatus = (ledStatus == LOW) ? HIGH : LOW;

    delay(100);
  }
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(LED_BUILTIN, LOW);
  ThingSpeak.begin(client);
  Serial.println("Connected to ThingSpeak");
}


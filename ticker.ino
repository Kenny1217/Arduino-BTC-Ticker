#include <Arduino.h>
#include <ArduinoJson.h> //Used To Handle Json
#include <ESP8266WiFi.h> //Used To Connect To The Internet
#include <ESP8266HTTPClient.h>

char ssid[] = ""; //SSID Name
char pwd[] = ""; //Wifi Password
const String url = "http://api.coindesk.com/v1/bpi/currentprice.json"; //Url
HTTPClient http;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Connecting to "); //Print Text
  Serial.print(ssid); //Print SSID
  WiFi.begin(ssid,pwd); //Connect To Wifi
  Serial.println(); //New Line
  Serial.println("Connecting..."); //Print Text
  while(WiFi.status() != WL_CONNECTED){ //While Not Connected To Wifi
    delay(1000); //1 Second Delay
    Serial.print("."); //Print Text
  }
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  digitalWrite(LED_BUILTIN, LOW); //Turn Led On
  Serial.println(); //New Line
  Serial.println("Wifi Connected Successfully"); //Successfully Connected To Wifi
  Serial.print("Ip Address: "); //Print Text
  Serial.print(WiFi.localIP()); //Print Ip Address
}

void loop() {
  // put your main code here, to run repeatedly:
  http.begin(url); //Begin HTTP Session
  int code = http.GET(); //Get Status Code
  if (code == 200) { //Check If Status Is Ok
    String payload = http.getString(); //Store JSON
    DynamicJsonDocument jsonBuffer(1100);
    deserializeJson(jsonBuffer, payload);
    JsonObject bpi = jsonBuffer["bpi"];
    JsonObject bpi_USD = bpi["USD"]; //Get USD Price
    float rate = bpi_USD["rate_float"]; //Store USD Price
    String price = "$";
    price += rate;
    Serial.println();
    Serial.println(price); 
  } 
  else {
    Serial.print("Failed to request coindesk API - is the internet connection active? Return code: ");
    Serial.println(code);
  }
  
  http.end(); //End Session
  delay(60000); //Coindesk's API updates once a minute













  
  
   

}

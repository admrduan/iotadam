#include <ThingSpeak.h>         
#include <DHTesp.h>                
#include <WiFi.h>         

const int DHT_PIN = 15;                                           
const char * SSID = "Wokwi-GUEST"; 
const char * PASS = "";            
                                

unsigned long myChannelNumber =  1996735;       
const char * myWriteAPIKey = "OAFYZAVJZQ8VBBFU"; 
const char * server = "api.thingspeak.com"; 
unsigned long lastTime = 0;
unsigned long TimerDelay = 10000;

int temperatureC;
int humidity;
WiFiClient  client; 
DHTesp dhtSensor;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  dhtSensor.getPin();
  delay(10);

  WiFi.begin(SSID, PASS);                                
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());


  ThingSpeak.begin(client);
}

void loop() 
{
  temperatureC = dhtSensor.getTemperature();
  Serial.print("Temperature (C) :");
  Serial.println(temperatureC);
  humidity = dhtSensor.getHumidity();
  Serial.print("Humidity (%): ");
  Serial.println(humidity);

  ThingSpeak.setField(1, temperatureC);
  ThingSpeak.setField(2, humidity);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 100){
    Serial.println("program berhasil dijalankan");
  }else{
    Serial.println("berhasil dijalankan");
  }
delay(TimerDelay);
}
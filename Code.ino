#include <WiFi.h>
#include <ModbusIP_ESP8266.h>
#include "DHT.h"

//setup pin
#define DHTPIN 14
#define DHTTYPE DHT11

//setup modbus address
#define TEMPERATURE_ADDRESS 100
#define HUMIDITY_ADDRESS 101
#define LED_ADDRESS 102

//setup wifi
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

//setup alamat IP
IPAddress local_IP(192, 168, 1, 123);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

DHT dht(DHTPIN, DHTTYPE);
ModbusIP mb;

void setup() {
  Serial.begin(115200);
  Serial.println(F("MODBUS TCP OVER WIFI ESP32"));

  WiFi.config(local_IP, gateway, subnet);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Terhubung!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin();
  mb.server();

  mb.addHreg(TEMPERATURE_ADDRESS);
  mb.addHreg(HUMIDITY_ADDRESS);
  
}

void loop() {

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  mb.Hreg(TEMPERATURE_ADDRESS, temperature * 10);
  mb.Hreg(HUMIDITY_ADDRESS, humidity * 10);

  mb.task();
  delay(50);

}

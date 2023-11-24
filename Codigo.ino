#include "ArduinoJson.h"
#include "EspMQTTClient.h"
#include "DHT.h"

int pressao = 0;

// Pinos dos LEDs
int redLed = 2;
int greenLed = 4;
int blueLed = 17;

DHT dht(16, DHT22);

// MQTT Configuracoes
EspMQTTClient client{
  "Wokwi-GUEST", //SSID do WiFi
  "",     // Senha do wifi
  "mqtt.tago.io",  // Endereço do servidor
  "Default",       // Usuario
  "d37e46b3-abb0-443c-8d3b-7fe4dc7ad41a", // Token do device 
  "esp",           // Nome do device
  1883             // Porta de comunicação
};
void setup() {
  Serial.begin(9600);
  Serial.println("Conectando WiFi");
  while (!client.isWifiConnected()) {
    Serial.print('.'); client.loop(); delay(1000);
  }
  Serial.println("WiFi Conectado");
  Serial.println("Conectando com Servidor MQTT");
  while (!client.isMqttConnected()) {
    Serial.print('.'); client.loop(); delay(1000);
  }
  Serial.println("MQTT Conectado");

  dht.begin();
  pinMode(34, INPUT);

    Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
}
// Callback da EspMQTTClient
void onConnectionEstablished()
{}

char bufferJson[100];
void loop() {
  int sensorValue = analogRead(34);
  pressao = map(sensorValue, 0, 1023, 40, 180);
  Serial.print("BPM: ");
  Serial.println(pressao);
  StaticJsonDocument<300> documentoJson;
  documentoJson["variable"] = "pressao";
  documentoJson["value"] = pressao;
  documentoJson["unit"] = "bpm";
  serializeJson(documentoJson, bufferJson);
  Serial.println(bufferJson);
  client.publish("topicoTDSPI", bufferJson);
  delay(1500);
  client.loop();

 
  if (pressao < 60) {
    // LED azul
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, HIGH);
  } else if (pressao >= 60 && pressao <= 100) {
    // LED verde
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    digitalWrite(blueLed, LOW);
  } else {
    // LED vermelho
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, LOW);
  }
  delay(1000);
}
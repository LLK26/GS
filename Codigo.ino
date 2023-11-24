int sensorPin = A0;
int bpm = 0;

// Pinos dos LEDs
int redLed = 2;
int greenLed = 3;
int blueLed = 4;

void setup() {
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  bpm = map(sensorValue, 0, 1023, 40, 180);
  Serial.print("BPM: ");
  Serial.println(bpm);

 
  if (bpm < 60) {
    // LED azul
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, HIGH);
  } else if (bpm >= 60 && bpm <= 100) {
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
#include <HTTPClient.h>

const char* ssid = "Galaxy A2044D7";
const char* password = "aopt9798";

const char* serverName = "http://192.168.171.87:5000/sensor/data";

const int trigPin = 23;
const int echoPin = 22;

float duration_us, distance_cm;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print("Connecting to WiFi......");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Mengirim pulsa trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Mengukur durasi pulsa echo
  duration_us = pulseIn(echoPin, HIGH);

  // Konversi durasi ke jarak dalam cm
  distance_cm = 0.017 * duration_us;

  // Menampilkan jarak
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  HTTPClient http;
  http.begin(serverName);
  http.addHeader("Content-Type", "application/json");

  String jsonData = "{\"distance\":" + String(distance_cm) + "}";
  int httpResponseCode = http.POST(jsonData);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  } else {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  // Menunggu sebelum pengukuran berikutnya
  delay(5000);
}

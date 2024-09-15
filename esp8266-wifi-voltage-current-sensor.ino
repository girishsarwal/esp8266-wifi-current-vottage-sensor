#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

// Access Point credentials
const char* ssid = "ESP8266_AP";
const char* password = "your_password";

// Web server on port 80
ESP8266WebServer server(80);

// Shunt and voltage divider pins
const int currentPin = A0;  // Use A0 for current measurement
const int voltagePin = A1;  // Use A1 for voltage measurement

// Voltage and current scaling factors
const float shuntResistance = 0.0015;    // Shunt resistor in ohms (1.5 mOhms)
const float adcMaxVoltage = 3.3;         // Max ADC voltage (3.3V for ESP8266)
const float adcMaxValue = 1023.0;        // Max ADC value (10-bit resolution)
const float voltageDividerRatio = 0.066; // Divider ratio for 50V max voltage

void setup() {
  Serial.begin(115200);

  // Set up Access Point
  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Define server routes
  server.on("/", handleRoot);
  server.on("/parameters", handleParameters);

  // Start server
  server.begin();
  Serial.println("Web server started");
}

// Serve the root route with HTML that polls /parameters every 5 seconds
void handleRoot() {
  String html = "<html><body>";
  html += "<h1>ESP8266 Voltage and Current</h1>";
  html += "<p>Voltage: <span id='voltage'>Loading...</span> V</p>";
  html += "<p>Current: <span id='current'>Loading...</span> A</p>";
  html += "<script>";
  html += "function updateValues() {";
  html += "  fetch('/parameters').then(response => response.json()).then(data => {";
  html += "    document.getElementById('voltage').innerText = data.voltage;";
  html += "    document.getElementById('current').innerText = data.current;";
  html += "  });";
  html += "}";
  html += "setInterval(updateValues, 5000);"; // Update every 5 seconds
  html += "updateValues();";  // Initial load
  html += "</script>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

// Serve the /parameters route with JSON data for voltage and current using ArduinoJson
void handleParameters() {
  // Read voltage
  int voltageAdc = analogRead(voltagePin);
  float voltage = (voltageAdc / adcMaxValue) * adcMaxVoltage / voltageDividerRatio;

  // Read current
  int currentAdc = analogRead(currentPin);
  float current = (currentAdc / adcMaxValue) * adcMaxVoltage / shuntResistance;

  // Create JSON object using ArduinoJson
  StaticJsonDocument<200> doc;
  doc["voltage"] = voltage;
  doc["current"] = current;

  // Serialize the JSON object to a string and send it
  String jsonResponse;
  serializeJson(doc, jsonResponse);
  server.send(200, "application/json", jsonResponse);
}

void loop() {
  server.handleClient();  // Handle web server requests
}
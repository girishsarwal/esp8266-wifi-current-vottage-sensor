# ESP8266 Voltage and Current Monitor
This project uses an ESP8266 microcontroller to measure voltage (5V-50V) and current (5A-50A) and serves these values over Wi-Fi through a simple web interface. The ESP8266 operates as an Access Point (AP), allowing you to connect to it and access the real-time data.

The data is displayed dynamically on a webpage that updates every 5 seconds. The backend uses the ArduinoJson library to serve the data in JSON format.

@ Features
- Measures voltage between 5V to 50V using a voltage divider.
- Measures current between 5A to 50A using a shunt resistor.
- Operates as an Access Point (AP), allowing easy connection without an external network.
- Provides real-time monitoring of voltage and current values.
- Displays a dynamic webpage that updates data every 5 seconds using JavaScript.
- Serves the data as a JSON response at a /parameters endpoint.

# Hardware Requirements
- ESP8266 (e.g., NodeMCU, Wemos D1 Mini)
-Voltage divider (e.g., 680kΩ and 47kΩ resistors)
- Shunt resistor (1.5mΩ recommended for 50A measurement)
- Power supply and wiring for the ESP8266 and sensors

# Software Requirements
- Arduino IDE
- ESP8266 board package installed in Arduino IDE
- ArduinoJson library (Install via Arduino Library Manager)
- ESP8266WiFi and ESP8266WebServer libraries (default in ESP8266 core)

# Circuit Diagram
Coming Soon

## Voltage Divider
The voltage divider is used to scale the input voltage (5V to 50V) down to a range that the ESP8266 can read through its ADC (0V to 3.3V). Choose your required resistors according to the voltage and the voltage divider formula

```
𝑅1=680𝑘
𝑅2=47𝑘Ω
```

## Shunt Resistor
The shunt resistor (e.g., 1.5mΩ) is used to measure the current based on Ohm’s Law. The voltage drop across the resistor is read by the ESP8266's ADC.

# Getting Started
Follow the steps below to set up the project on your ESP8266.

1. Clone the Repository
```bash
git clone https://github.com/yourusername/esp8266-voltage-current-monitor.git
```

2. Install Required Libraries
Make sure you have the following libraries installed in your Arduino IDE:

ESP8266 Board Package:
Go to `File > Preferences` and add this URL to the "Additional Board Manager URLs":

```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

Then, go to `Tools > Board > Board Manager`, search for `ESP8266`, and install the package.

ArduinoJson:
Open Arduino IDE and go to `Sketch > Include Library > Manage Libraries`.
Search for ArduinoJson and install the latest version.

3. Configure the Code
Open the ESP8266_Voltage_Current_Monitor.ino file in the Arduino IDE and modify the following sections if necessary:

Access Point Credentials: Change the SSID and password for the ESP8266 AP mode:

```cpp
const char* ssid = "ESP8266_AP";
const char* password = "your_password";
```

4. Upload the Code
Select your ESP8266 board under `Tools > Board` (e.g., NodeMCU 1.0 or Wemos D1 Mini).
Connect the ESP8266 to your computer.
Compile and upload the code using the Arduino IDE.

5. Connect to the ESP8266
After uploading, connect your computer or smartphone to the ESP8266's Wi-Fi network (ESP8266_AP by default).
Open a web browser and go to the ESP8266’s IP address (usually 192.168.4.1).

6. Access the Web Interface
Once connected, you can:

View real-time voltage and current values on the root route (/).
Access the raw voltage and current data in JSON format by visiting the /parameters endpoint.

# Endpoints
`/` : Displays the web interface that dynamically updates the voltage and current values every 5 seconds.
`/parameters` : Returns a JSON response with the current voltage and current measurements.
Example JSON response:

```json
{
  "voltage": 12.34,
  "current": 15.67
}
```

Example Usage
Connect to the ESP8266’s AP.
Navigate to `http://192.168.4.1/` on your browser.

The webpage will display the real-time voltage and current, automatically refreshing every 5 seconds.
Optionally, use tools like Postman or curl to fetch data from the `/parameters` endpoint.

```bash
curl http://192.168.4.1/parameters
```

# Troubleshooting
Cannot Connect to ESP8266 AP: Ensure that your ESP8266 is powered correctly and the code was uploaded successfully.
Incorrect Voltage or Current Readings: Double-check the wiring of the voltage divider and shunt resistor. Ensure proper resistor values are used.

# License
This project is licensed under the MIT License - see the LICENSE file for details.

# Contributing
Feel free to contribute by opening issues or submitting pull requests. See the CONTRIBUTING.md for more details.

# Acknowledgments
This project was built using the ArduinoJson library.
Thanks to the ESP8266 core for Arduino.

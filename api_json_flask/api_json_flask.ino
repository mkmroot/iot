#include <ESP8266WiFi.h>    // For ESP8266, use WiFi.h for ESP32
#include <ESP8266HTTPClient.h>  // For ESP8266, use HTTPClient.h for ESP32
#include <ArduinoJson.h>    // ArduinoJson library to parse JSON

// Replace with your network credentials
const char* ssid = "RSHome";
const char* password = "0Per@ti0n@2022";

// Flask API endpoint
const char* serverName = "http://192.168.0.15:5000/api/saved-data";
//const char* serverName = "http://192.168.43.105:5000/api/saved-data";


// Pin connected to the LED
const int D4 = 2;  // D4 on NodeMCU is GPIO2 inbuild_LED
const int D2 = 4;  // D2 on NodeMCU is GPIO4

void setup() {
  // Initialize serial monitor for debugging
  Serial.begin(115200);

  // Initialize the LED pin as an output
  pinMode(D4, OUTPUT);
  pinMode(D2, OUTPUT);

  // Connect to the Wi-Fi network
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }

  // Once connected, print the IP address
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if connected to the WiFi
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;
    // Make the HTTP request to the Flask server
    http.begin(client,serverName);  // Specify the Flask server URL
    int httpCode = http.GET();  // Make the GET request

    // Check if the request was successful
    if (httpCode > 0) {
      String payload = http.getString();  // Get the server response
      Serial.println(httpCode);  // Print the HTTP status code
      Serial.println(payload);   // Print the response payload

      // Parse the JSON response
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
        // Extract values from JSON
        const char* point1 = doc["Point1"];  // Get the "Point1" value
        const char* point2 = doc["Point2"];  // Get the "Point1" value
        int age = doc["age"];            // Get the "age" value

        // Key-Value matching condition
        if (String(point1) == "ON") {
          digitalWrite(D4, LOW);  // Turn the LED on if Point1 is ON (esp8266 LOW=On)
          Serial.println("LED is ON (Point1=ON)");
        } else {
          digitalWrite(D4, HIGH);   // Turn the LED off otherwise
          Serial.println("LED is OFF");
        }

        // Key-Value matching condition
        if (String(point2) == "ON") {
          digitalWrite(D2, LOW);  // Turn the LED on if Point2 is ON (esp8266 LOW=On)
          Serial.println("Fan is ON (Point2=ON)");
        } else {
          digitalWrite(D2, HIGH);   // Turn the LED off otherwise
          Serial.println("LED is OFF");
        }

                // Key-Value matching condition
       // if (age == 25) {
       //   digitalWrite(D2, HIGH);  // Turn the LED on if Point2 is ON (esp8266 LOW=On)
       //   Serial.println("Fan is ON (25)");
       // } else {
       //   digitalWrite(D2, LOW);   // Turn the LED off otherwise
       //   Serial.println("Fan is OFF");
       // }
        
      } else {
        Serial.println("Error parsing JSON");
      }
    } else {
      Serial.println("Error in HTTP request");
    }

    http.end();  // End the HTTP connection
  }

  delay(1000);  // Wait for 10 seconds before making another request
}

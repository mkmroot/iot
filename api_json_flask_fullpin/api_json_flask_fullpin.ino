#include <ESP8266WiFi.h>    // For ESP8266, use WiFi.h for ESP32
#include <ESP8266HTTPClient.h>  // For ESP8266, use HTTPClient.h for ESP32
#include <ArduinoJson.h>    // ArduinoJson library to parse JSON

// Replace with your network credentials
const char* ssid = "RSHome";
const char* password = "0Per@ti0n@2022";

// Flask API endpin
const char* serverName = "http://192.168.0.15:5000/api/data";
//const char* serverName = "http://192.168.43.105:5000/api/saved-data";


// Pin connected to the LED
const int D0 = 16;
const int D1 = 5;
const int D2 = 4;  // D2 on NodeMCU is GPIO4
const int D3 = 5;
const int D4 = 2;  // D4 on NodeMCU is GPIO2 inbuild_LED
const int D5 = 14;
const int D6 = 12;
const int D7 = 13;
const int D8 = 15;

void setup() {
  // Initialize serial monitor for debugging
  Serial.begin(115200);

  // Initialize the LED pin as an output
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);  

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
        const char* pin0 = doc["Pin0"];
        const char* pin1 = doc["Pin1"];  // Get the "Pin1" value
        const char* pin2 = doc["Pin2"];  // Get the "Pin2" value
        const char* pin3 = doc["Pin3"];  // Get the "Pin3" value
        const char* pin4 = doc["Pin4"];  // Get the "Pin4" value
        const char* pin5 = doc["Pin5"];  // Get the "Pin5" value
        const char* pin6 = doc["Pin6"];  // Get the "Pin6" value
        const char* pin7 = doc["Pin7"];  // Get the "Pin7" value
        const char* pin8 = doc["Pin8"];  // Get the "Pin8" value        

        // Key-Value matching condition
        if (String(pin0) == "ON") {
          digitalWrite(D0, LOW);  // Turn the LED on if pin1 is ON (esp8266 LOW=On)
          Serial.println("LED is ON (pin1=ON)");
        } else {
          digitalWrite(D0, HIGH);   // Turn the LED off otherwise
          Serial.println("LED is OFF");
        }

        // Key-Value matching condition
        if (String(pin1) == "ON") {
          digitalWrite(D1, LOW);  // Turn the LED on if pin2 is ON (esp8266 LOW=On)
          Serial.println("Fan is ON (pin2=ON)");
        } else {
          digitalWrite(D1, HIGH);   // Turn the LED off otherwise
          Serial.println("LED is OFF");
        }

        // Key-Value matching condition
        if (String(pin2) == "ON") {
          digitalWrite(D2, LOW);  // Turn the LED on if pin2 is ON (esp8266 LOW=On)
          Serial.println("Fan is ON (pin2=ON)");
        } else {
          digitalWrite(D2, HIGH);   // Turn the LED off otherwise
          Serial.println("LED is OFF");
        }

        // Key-Value matching condition
        if (String(pin3) == "ON") {
          digitalWrite(D3, LOW);  // Turn the LED on if pin2 is ON (esp8266 LOW=On)
          Serial.println("Fan is ON (pin2=ON)");
        } else {
          digitalWrite(D3, HIGH);   // Turn the LED off otherwise
          Serial.println("LED is OFF");
        }

        // Key-Value matching condition
        if (String(pin4) == "ON") {
          digitalWrite(D4, LOW);  // Turn the LED on if pin2 is ON (esp8266 LOW=On)
          Serial.println("Fan is ON (pin2=ON)");
        } else {
          digitalWrite(D4, HIGH);   // Turn the LED off otherwise
          Serial.println("LED is OFF");
        }

        // Key-Value matching condition
        if (String(pin5) == "ON") {
          digitalWrite(D5, LOW);  // Turn the LED on if pin2 is ON (esp8266 LOW=On)
          Serial.println("Fan is ON (pin2=ON)");
        } else {
          digitalWrite(D5, HIGH);   // Turn the LED off otherwise
          Serial.println("LED is OFF");
        }

        // Key-Value matching condition
        if (String(pin6) == "ON") {
          digitalWrite(D6, LOW);  // Turn the LED on if pin2 is ON (esp8266 LOW=On)
          Serial.println("Fan is ON (pin2=ON)");
        } else {
          digitalWrite(D6, HIGH);   // Turn the LED off otherwise
          Serial.println("LED is OFF");
        }

        // Key-Value matching condition
        if (String(pin7) == "ON") {
          digitalWrite(D7, LOW);  // Turn the LED on if pin2 is ON (esp8266 LOW=On)
          Serial.println("Fan is ON (pin2=ON)");
        } else {
          digitalWrite(D7, HIGH);   // Turn the LED off otherwise
          Serial.println("LED is OFF");
        }


        // Key-Value matching condition
        if (String(pin8) == "ON") {
          digitalWrite(D8, LOW);  // Turn the LED on if pin2 is ON (esp8266 LOW=On)
          Serial.println("Fan is ON (pin2=ON)");
        } else {
          digitalWrite(D8, HIGH);   // Turn the LED off otherwise
          Serial.println("LED is OFF");
        }

                // Key-Value matching condition
       // if (age == 25) {
       //   digitalWrite(D2, HIGH);  // Turn the LED on if pin2 is ON (esp8266 LOW=On)
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

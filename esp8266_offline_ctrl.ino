#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "MyESP8266AP";       // SSID of the access point
const char* password = "mypassword";    // Password for the access point

ESP8266WebServer server(80);            // Create a web server object that listens on port 80

const int ledPin = 2;                   // GPIO2 (D4 on NodeMCU)

void handleRoot() {
  // Get the current state of the LED
  String ledState = (digitalRead(ledPin) == LOW) ? "ON" : "OFF";

  // HTML content to be served
  String html = "<!DOCTYPE html>"
                "<html>"
                "<head>"
                "<title>ESP8266 Web Server</title>"
                "<style>"
                "body { font-family: Arial, sans-serif; text-align: center; }"
                "h1 { color: #333; }"
                "button { padding: 10px 20px; font-size: 16px; }"
                "</style>"
                "</head>"
                "<body>"
                "<h1>ESP8266 LED Control</h1>"
                "<p>LED is currently: <strong>" + ledState + "</strong></p>"
                "<p><button onclick=\"location.href='/LEDON'\">Turn ON</button></p>"
                "<p><button onclick=\"location.href='/LEDOFF'\">Turn OFF</button></p>"
                "</body>"
                "</html>";

  server.send(200, "text/html", html);  // Send the HTTP response
}

void handleLEDOn() {
  digitalWrite(ledPin, LOW);            // Turn the LED on (active low)
  server.sendHeader("Location", "/");   // Redirect to the root page
  server.send(303);                     // Send the HTTP redirect
}

void handleLEDOff() {
  digitalWrite(ledPin, HIGH);           // Turn the LED off
  server.sendHeader("Location", "/");   // Redirect to the root page
  server.send(303);                     // Send the HTTP redirect
}

void setup() {
  pinMode(ledPin, OUTPUT);              // Set the LED pin as an output
  digitalWrite(ledPin, HIGH);           // Make sure the LED is off (active low)

  Serial.begin(115200);                 // Start the Serial communication
  WiFi.softAP(ssid, password);          // Set the ESP8266 as an access point

  Serial.print("Access Point IP address: ");
  Serial.println(WiFi.softAPIP());      // Print the IP address of the access point

  server.on("/", handleRoot);           // Associate the handler function to the path "/"
  server.on("/LEDON", handleLEDOn);     // Associate the handler function to the path "/LEDON"
  server.on("/LEDOFF", handleLEDOff);   // Associate the handler function to the path "/LEDOFF"
  server.begin();                       // Start the web server
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();                // Handle client requests
}

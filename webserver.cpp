#include "webserver.h"

// Define the WebServer object
WebServer webServer(port);

// Define a function for handling HTTP requests
void handleRequest() {
  String message = "Hello, world!";
  webServer.send(200, "text/plain", message);
}

// Define a function for starting the web server
void startWebServer(WebServer *server, MySQL_Connection *conn) {
  // Connect to the Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi successfully!");

  // Start the web server
  server->begin();
  Serial.println("Web server started!");

  // Handle HTTP requests
  server->on("/", HTTP_GET, handleRequest);

  // Keep the web server running
  while (true) {
    server->handleClient();
  }
}

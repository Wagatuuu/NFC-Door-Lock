#ifndef WEBSERVER_H
#define WEBSERVER_H

// Include the necessary libraries
#include <WiFi.h>
#include <WebServer.h>
#include <MySQL_Connection.h>

// Define the SSID and password of your Wi-Fi network
const char* ssid = "your_SSID";
const char* password = "your_password";

// Define the IP address and port number for the web server
IPAddress ip(197,136,96,14);
const int port = 5500;

// Declare a function for starting the web server
void startWebServer(WebServer *server, MySQL_Connection *conn);

#endif // WEBSERVER_H

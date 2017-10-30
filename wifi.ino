#include "WifiEndpoint.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "herpderp";
const char* password = "worldwideweb";

ESP8266WebServer server(80);

void setupWifi(){
  WifiEndpoint tempEndpoint = {"temp", handleTemp};
  WifiEndpoint soilEndpoint = {"moisture", handleMoisture};


  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  addEndpoint(tempEndpoint);
  addEndpoint(soilEndpoint);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loopWifi(void) {
  server.handleClient();
}

void addEndpoint(WifiEndpoint endpoint) {
  String ep = "/" + endpoint.name;
  Serial.println(ep);
  server.on(ep.c_str(), endpoint.callback);
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleTemp(void) {
  server.send(200, "application/json", "{\"temp\":" + String(getDS18B20Temperature(), 2) + "}");
}

void handleMoisture(void) {
  server.send(200, "application/json", "{\"moisture\":" + String(getSoilMoisture()) + "}");
}

#include <ESP8266WiFi.h>
#include "index_html.h"
#include "style_css.h"

const char* ssid = "NamaWifi";
const char* password = "PasswordWifi";

WiFiServer server(80);
const int ledPin = D1;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String req = client.readStringUntil('\r');
  client.flush();

  // Handle LED
  if (req.indexOf("/ON") != -1) digitalWrite(ledPin, HIGH);
  if (req.indexOf("/OFF") != -1) digitalWrite(ledPin, LOW);

  // Serve HTML
  if (req.indexOf("GET / ") != -1 || req.indexOf("GET /HTTP") != -1) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.print(html_page);
  }
  // Serve CSS
  else if (req.indexOf("GET /style.css") != -1) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/css");
    client.println();
    client.print(css_style);
  }
  // Response kosong untuk /ON dan /OFF
  else {
    client.println("HTTP/1.1 204 No Content");
    client.println();
  }

  client.stop();
}

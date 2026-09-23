#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// =====================================================
// Wi-Fi
// =====================================================

consht char* ssid = "Home_Automation";
const char* password = "12345678";

// =====================================================
// RELAY PINS
// ESP8266 GPIO numbers
// =====================================================

#define RELAY1 5    // GPIO5  = D1
#define RELAY2 4    // GPIO4  = D2
#define RELAY3 14   // GPIO14 = D5
#define RELAY4 12   // GPIO12 = D6

// =====================================================
// WEB SERVER
// =====================================================

ESP8266WebServer server(80);

// Relay states
bool relay1State = false;
bool relay2State = false;
bool relay3State = false;
bool relay4State = false;

// =====================================================
// WEB PAGE
// =====================================================

String webpage() {

  String html = R"rawliteral(

<!DOCTYPE html>

<html>

<head>

<meta name="viewport" content="width=device-width, initial-scale=1">

<title>ESP8266 Relay Control</title>

<style>

body {
    font-family: Arial, sans-serif;
    background: #111827;
    color: white;
    text-align: center;
    margin: 0;
    padding: 20px;
}

h1 {
    margin-bottom: 30px;
}

.container {
    max-width: 500px;
    margin: auto;
}

.relay {
    background: #1f2937;
    padding: 20px;
    margin: 15px 0;
    border-radius: 15px;
}

.status {
    font-size: 18px;
    margin: 10px;
}

button {
    border: none;
    padding: 12px 25px;
    margin: 5px;
    border-radius: 8px;
    font-size: 16px;
    cursor: pointer;
}

.on {
    background: #22c55e;
    color: white;
}

.off {
    background: #ef4444;
    color: white;
}

</style>

</head>

<body>

<div class="container">

<h1>ESP8266 Relay Control</h1>

<div class="relay">

<h2>Relay 1</h2>

<div class="status">
Status: <b>%R1%</b>
</div>

<a href="/relay1/on">
<button class="on">ON</button>
</a>

<a href="/relay1/off">
<button class="off">OFF</button>
</a>

</div>


<div class="relay">

<h2>Relay 2</h2>

<div class="status">
Status: <b>%R2%</b>
</div>

<a href="/relay2/on">
<button class="on">ON</button>
</a>

<a href="/relay2/off">
<button class="off">OFF</button>
</a>

</div>


<div class="relay">

<h2>Relay 3</h2>

<div class="status">
Status: <b>%R3%</b>
</div>

<a href="/relay3/on">
<button class="on">ON</button>
</a>

<a href="/relay3/off">
<button class="off">OFF</button>
</a>

</div>


<div class="relay">

<h2>Relay 4</h2>

<div class="status">
Status: <b>%R4%</b>
</div>

<a href="/relay4/on">
<button class="on">ON</button>
</a>

<a href="/relay4/off">
<button class="off">OFF</button>
</a>

</div>

</div>

</body>

</html>

)rawliteral";

  html.replace("%R1%", relay1State ? "ON" : "OFF");
  html.replace("%R2%", relay2State ? "ON" : "OFF");
  html.replace("%R3%", relay3State ? "ON" : "OFF");
  html.replace("%R4%", relay4State ? "ON" : "OFF");

  return html;
}

// =====================================================
// HOME PAGE
// =====================================================

void handleRoot() {

  server.send(200, "text/html", webpage());

}

// =====================================================
// RELAY 1
// =====================================================

void relay1On() {

  relay1State = true;

  // Most relay modules are ACTIVE LOW
  digitalWrite(RELAY1, LOW);

  server.sendHeader("Location", "/");
  server.send(303);

}

void relay1Off() {

  relay1State = false;

  digitalWrite(RELAY1, HIGH);

  server.sendHeader("Location", "/");
  server.send(303);

}

// =====================================================
// RELAY 2
// =====================================================

void relay2On() {

  relay2State = true;

  digitalWrite(RELAY2, LOW);

  server.sendHeader("Location", "/");
  server.send(303);

}

void relay2Off() {

  relay2State = false;

  digitalWrite(RELAY2, HIGH);

  server.sendHeader("Location", "/");
  server.send(303);

}

// =====================================================
// RELAY 3
// =====================================================

void relay3On() {

  relay3State = true;

  digitalWrite(RELAY3, LOW);

  server.sendHeader("Location", "/");
  server.send(303);

}

void relay3Off() {

  relay3State = false;

  digitalWrite(RELAY3, HIGH);

  server.sendHeader("Location", "/");
  server.send(303);

}

// =====================================================
// RELAY 4
// =====================================================

void relay4On() {

  relay4State = true;

  digitalWrite(RELAY4, LOW);

  server.sendHeader("Location", "/");
  server.send(303);

}

void relay4Off() {

  relay4State = false;

  digitalWrite(RELAY4, HIGH);

  server.sendHeader("Location", "/");
  server.send(303);

}

// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  // Relay pins
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  // Make sure all relays are OFF
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);

  // ===================================================
  // CONNECT TO WIFI
  // ===================================================

  Serial.println();
  Serial.println("Connecting to Wi-Fi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println();

  Serial.println("Wi-Fi connected!");

  Serial.print("IP Address: ");

  Serial.println(WiFi.localIP());

  // ===================================================
  // SERVER ROUTES
  // ===================================================

  server.on("/", handleRoot);

  server.on("/relay1/on", relay1On);
  server.on("/relay1/off", relay1Off);

  server.on("/relay2/on", relay2On);
  server.on("/relay2/off", relay2Off);

  server.on("/relay3/on", relay3On);
  server.on("/relay3/off", relay3Off);

  server.on("/relay4/on", relay4On);
  server.on("/relay4/off", relay4Off);

  // Start server
  server.begin();

  Serial.println("Web server started!");

}

// =====================================================
// LOOP
// =====================================================

void loop() {

  server.handleClient();

}
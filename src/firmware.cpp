/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-websocket-server-arduino/
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#include <WiFi.h>
#include <WiFiSTA.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "parser.h"

extern char tempString[32];
extern unsigned long currentPos;
extern int speedNumber;

#define __DEBUG__ false

#if __DEBUG__
	#define PRINT echo
#endif

#define __AP__

// Replace with your network credentials
#ifdef __AP__
	const char* ssid = "ESP32MotorizedFocuser";
	const char* password = "1234";
#else
	const char* ssid = "HUAWEI-E5180-AE10";
	const char* password = "49TTJ4J607E";
#endif

// the IP address for the shield:
IPAddress local_ip(192, 168, 1, 143);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255,255,255,0);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const int led = 2;
const int capteurLuminosite = 34;


void echo(const char *format, int value)
{
	char s[32];
	sprintf(s,format,value);
	Serial.println(s);
}



int pos = 0;
int speed = 1;
bool engaged = false;
bool connected = false;
bool ledstatus = false;

void blink()
{
	if (ledstatus)	digitalWrite(led, LOW);
	else digitalWrite(led, HIGH);
	ledstatus = !ledstatus;
}

void initserver(){
	// //----------------------------------------------------Serial
	// Serial.begin(9600);
	// Serial.println("Serial on\n");


	//----------------------------------------------------GPIO
	pinMode(led, OUTPUT);
	digitalWrite(led, LOW);

	//   //----------------------------------------------------SPIFFS
	if(!SPIFFS.begin(true))
	{
		Serial.println("Erreur SPIFFS...");
		return;	
	}

	File root = SPIFFS.open("/");
	File file = root.openNextFile();

	while(file)
	{
		Serial.print("File: ");
		Serial.println(file.name());
		file.close();
		file = root.openNextFile();
	}

	//----------------------------------------------------WIFI
	#ifdef __AP__
	  	// Connect to Wi-Fi network with SSID and password
  		Serial.print("Setting AP (Access Point)…");
  		// Remove the password parameter, if you want the AP (Access Point) to be open
  		WiFi.softAP(ssid, password);
  		IPAddress IP = WiFi.softAPIP();
  		Serial.print("AP IP address: ");
  		Serial.println(IP);
	#else
		WiFi.begin(ssid, password);
		Serial.print("Tentative de connexion...");
	
		while(WiFi.status() != WL_CONNECTED)
		{
			Serial.print(".");
			delay(100);
		}
		connected = true;
		Serial.println("\n");
		Serial.println("Connexion etablie!");
		Serial.print("Adresse IP: ");
		Serial.println(WiFi.localIP());
	#endif

	//----------------------------------------------------SERVER
	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
	{
		request->send(SPIFFS, "/index.html", "text/html");
	});

	server.on("/w3.css", HTTP_GET, [](AsyncWebServerRequest *request)
	{
		request->send(SPIFFS, "/w3.css", "text/css");
	});

	server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
	{
		request->send(SPIFFS, "/script.js", "text/javascript");
	});

	// Increase speed
	server.on("/vplus", HTTP_GET, [](AsyncWebServerRequest *request){
		blink();
		speedplus();
		request->send(200);
	});

	// decrease speed
	server.on("/vmoins", HTTP_GET, [](AsyncWebServerRequest *request){
		blink();
		speedmoins();
		request->send(200);
	});

	// Step+
	server.on("/avant", HTTP_GET, [](AsyncWebServerRequest *request){
		blink();
		gofwd();
		request->send(200);
	});

	// Step-
	server.on("/arriere", HTTP_GET, [](AsyncWebServerRequest *request){
		blink();
		gobwd();
		request->send(200);
	});

	// Route for root / web page
	server.on("/lock", HTTP_GET, [](AsyncWebServerRequest *request){
		engaged = !engaged;
		// PRINT("lock : %d",engaged);
		request->send(200);
	});

	server.on("/position",  HTTP_GET, [](AsyncWebServerRequest *request){
		sprintf(tempString,"%0lu",currentPos);
		// String position = String(getpos());
		// String position = String(0);
		request->send(200, "text/plain", String(tempString));
	});

	server.on("/speed",  HTTP_GET, [](AsyncWebServerRequest *request){
		sprintf(tempString,"%d",speedNumber);
		request->send(200, "text/plain", tempString);
	});

	server.on("/zero",  HTTP_GET, [](AsyncWebServerRequest *request){
		gotozero();
		request->send(200);
	});

	server.on("/engaged",  HTTP_GET, [](AsyncWebServerRequest *request){
		if (engaged)
		{
			request->send(200, "text/plain", String("DEBRAYE"));
		}
		else
		{
			request->send(200, "text/plain", String("EMBRAYE"));
		}
	});

	// Start server
	server.begin();
	Serial.println("Serveur actif!");
}

// void loop() {
// 	if (connected)
// 	{
// 		// PRINT("position : %06d", pos);
// 		// PRINT("vitesse : %02d", speed);
// 		// PRINT("engagé : %d", engaged);
// 		// delay(1000);
// 	}
// }

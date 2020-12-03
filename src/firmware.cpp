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

#define __DEBUG__ true

#if __DEBUG__
	#define PRINT echo
#endif

// Replace with your network credentials
const char* ssid = "HUAWEI-E5180-AE10";
const char* password = "49TTJ4J607E";

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
int speed = 0;
bool engaged = false;
bool connected = false;
bool ledstatus = false;



void setup(){
	//----------------------------------------------------Serial
	Serial.begin(9600);
	Serial.println("Serial on\n");


	//----------------------------------------------------GPIO
	pinMode(led, OUTPUT);
	digitalWrite(led, LOW);
	pinMode(capteurLuminosite, INPUT);

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



	// Print ESP Local IP Address
	Serial.println(WiFi.localIP());


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
		speed =min(5,speed+1);
		request->send(200);
	});

	// decrease speed
	server.on("/vmoins", HTTP_GET, [](AsyncWebServerRequest *request){
		speed =max(1,speed-1);
		request->send(200);
	});

	// Step+
	server.on("/avant", HTTP_GET, [](AsyncWebServerRequest *request){
		if (ledstatus)	digitalWrite(led, LOW);
		else digitalWrite(led, HIGH);
		ledstatus = !ledstatus;
		pos++;
		PRINT("position : %06d", pos);
		request->send(200);
	});

	// Step-
	server.on("/arriere", HTTP_GET, [](AsyncWebServerRequest *request){
		pos=max(0,pos-1);
		request->send(200);
	});

	// Route for root / web page
	server.on("/lock", HTTP_GET, [](AsyncWebServerRequest *request){
		engaged = !engaged;
		// PRINT("lock : %d",engaged);
		request->send(200);
	});

	server.on("/position",  HTTP_GET, [](AsyncWebServerRequest *request){
		String position = String(pos);
		request->send(200, "text/plain", position);
	});

	server.on("/speed",  HTTP_GET, [](AsyncWebServerRequest *request){
		String sp = String(speed);
		request->send(200, "text/plain", sp);
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

void loop() {
	if (connected)
	{
		// PRINT("position : %06d", pos);
		// PRINT("vitesse : %02d", speed);
		// PRINT("engagé : %d", engaged);
		// delay(1000);
	}
}

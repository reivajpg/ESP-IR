# ESP-IR_ServiceMenu
Service remote control for TV based on ESP8266

ESP-IR_ServiceMenu described here uses a ESP-12 sender to control TV.
Features:
-	Simulates one or more IR remote controllers for TV/DVD/Interactive TV.
-	 Uses a minimal number of components.
-	Can be controlled by a tablet or other device through a build-in webserver.
-	Pictures of original remote controls are used to control the ESP-IR.
-	The strongest available WiFi network is automatically selected.  Passwords are kept in the SPIFFS filesystem.
-	Heavily commented source code, easy to add extra functionality.
-	Debug information through serial output.
-	Update of software over WiFi (OTA).

Update 20-07-2017: Correction for IRremoteESP8266 v2.0 library.

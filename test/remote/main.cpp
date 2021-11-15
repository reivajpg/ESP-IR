/* So this is a running server to access a file in the SPIFFS files sytems
 *  made by FS.h.  Go to tools, ESP sketch data upload, and it loads a file system based on everything in the 'data' folder
 *  contained in the sketch's main folder.  Server is more stable than previous, with client and system timeouts managed at top.
 *  Now has shorter, and slightly smarter code, and does not crash (probably).
 */  

#include <ESP8266WiFi.h>
#include "FS.h"
#include <IRremoteESP8266.h>

#define CLIENT_TIMEOUT 5.0     //client timeout in seconds when waiting to become "ready"
const char* ssid = "yourwifi";
const char* password = "yourwifipassword";

// Globals
WiFiServer server(80);
WiFiClient client;
IRsend irsend(2);

// ------------- SIMPLIFICATION---------------
int sendpage(String filename){
  
  File f = SPIFFS.open(filename, "r");
  if (!f) {
      Serial.print(filename);
      Serial.println(": open failed");
      return 1;
  }
  String s;
  if (filename.indexOf(".jpg") != -1)  {  //if it's a jpeg
     s = "HTTP/1.1 200 OK\r\nContent-Type: image/jpg\r\nContent-Transfer-Encoding: binary\r\n\r\n";
  }
  else if (filename.indexOf(".htm") != -1) {
     s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  }
  else {
    s= "";
  }
  
  long buf_size = 500;
  long bufi = 0;
  for (int i = 0; i < f.size(); i++){
     bufi++;
     s+= (char)f.read();
     if (bufi > buf_size-1){
        bufi = 0;
        client.print(s);
        s="";
     }
  }
  client.print(s);
  f.close();
  delay(1);
  return 0;
}
int wait_for_client(){    //but not indefinitedly
  // Check if a client has connected
  client = server.available();
  if (!client) {
    delay(100);
    return 1;
  }
  long ite = CLIENT_TIMEOUT * 10;          //ite is iteration, ten per second
  while(!client.available()){
    delay(100);
    ite -= 1;
    if (ite < 1) {
      Serial.println("Client timeout");     //client connected but never became "ready."  This happens for some reason.
      client.stop();
      return 1; 
    }
  } 
  //while(1) {delay(100);}
  return 0;
}
// --------------IR --------------
bool send_ir_cmd(String cmd){     //returns true if command was sent sucessfully, obviously.  accepts format "IRFORMAT-Data-datalengthinbits" example: "NEC-5132547896-32"
  if (cmd.indexOf("NEC") != -1){   //okay, NEC, we know howo to do this
      long data = parse_long_from_string(cmd, cmd.indexOf("-")+1, cmd.lastIndexOf("-")-1);
      int datalen = parse_int_from_string(cmd, cmd.lastIndexOf("-")+1, cmd.length() -1);
      irsend.sendNEC(data, datalen);
      delay(40);
  }
  else {                         // elseifs for other than NEC belong here somewhere
    return false;
  }
} 
int parse_int_from_string(String inputstr, int startindex, int endindex) {
  int i = startindex;
  int res = 0;
  while (i <= endindex)  {
    res = res * 10 + (uint8_t)inputstr.charAt(i) - '0';
    i++;
  }
  return res;
}
long parse_long_from_string(String inputstr, int startindex, int endindex) {
  int i = startindex;
  long res = 0;
  while (i <= endindex)  {
    res = res * 10 + (uint8_t)inputstr.charAt(i) - '0';
    i++;
  }
  return res;
}
//------------------------------SETUP----------------------
void setup() {
  //IR
  irsend.begin();
  delay(10);
    
  //Serial
  Serial.begin(74880);
  delay(10);
  
  //WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());

  //file system
  if (SPIFFS.begin()){
    Serial.println("File system mounted successfully");
  }
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    Serial.print(dir.fileName());
    File f = dir.openFile("r");
    Serial.print(" : ");
    Serial.println(f.size());
    f.close();
    }
   
}
//-------------------------------------MAIN LOOP-------------------
void loop() {
  //waiting for connection
  if (wait_for_client()) return;   //wait_for_client returns non-zero if the wait was not fruitful

  // A client!
  // Read the request
  String req = client.readStringUntil(' ');
  req = client.readStringUntil(' ');
  Serial.println(req);
  client.flush();

  if (req.indexOf("favicon.ico") !=-1){      //google chrome sends several of these annoying requests, i ignore them
    client.stop();
    return;
  }
  else if(req.length() == 1){                //if the request is only a "/", then just serve the index page
     req = "/index.htm";
     sendpage(req);
  }
  else if(req.indexOf(".") == -1){// if there is not "." so it's not a file in the system.. probably
      if (!send_ir_cmd(req)){
         //not an ir command
         Serial.println("Not recognized" );
      }
      else {
          //req = "/index.htm";
          //sendpage(req);
      }
  }
  else {
     if (sendpage(req)){    //if page not found
        req = "/not_found.htm";
        sendpage(req);
     }
  }

  client.stop();
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}
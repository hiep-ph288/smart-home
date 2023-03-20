#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

// Giao tiếp với Uno R3
// KHoi tao cong uart moi
SoftwareSerial mySerial(D7, D8);  // RX D7  TX D8
#include <WiFiUdp.h>
#include <NTPClient.h>

WiFiUDP u;
NTPClient n(u, "2.asia.pool.ntp.org", 7 * 3600);  // Server NTP
#include "index.h"                                //Our HTML webpage contents with javascripts


String s = "";

#define LED 2  //On board LED

String ledState = "0";
String servogarastate = "0";
String ServoState = "0";

String ledStatePN = "0";

String quatState = "0";
String quatStatePK = "0";
String statemaybom = "0";
String quatwcstate = "0";



String tempn = "0";
String humpn = "0";
String doamdat = "0";

String tempk = "0";
String humpk = "0";
String temwc = "0";
String humwc = "0";
String gas = "gas";
String gioup;
String hengio;

//SSID and Password of your WiFi router
// const char* ssid = "Siliconnn";
// const char* password = "88888888";
 const char* ssid = "Silicon";
 const char* password = "12344321";

// const char* ssid = "hoangson1510";
// const char* password = "123456789";
//const char* ssid = "Bob Gin Awesome Family";
//const char* password = "303G1n@home";

ESP8266WebServer server(80);  //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
  String s = MAIN_page;              //Read HTML contents
  server.send(200, "text/html", s);  //Send web page
}

void reciveforweb(void) {
  String dataresponse = "";
  uint8_t dem = 0;

  while (Serial.available()) {
    char c = (char)Serial.read();
    dem++;
    if (c == 't') {
      if (((uint8_t)dataresponse.toInt() > 0) && (dem == 3)) {
        tempn = dataresponse;
      }
      dataresponse = "";
      dem = 0;
    } else if (c == 'h') {
      if (((uint8_t)dataresponse.toInt() > 0) && (dem == 3)) {
        humpn = dataresponse;
      }
      dataresponse = "";
      dem = 0;
    } else if (c == 'p') {
      if (((uint8_t)dataresponse.toInt() > 0) && (dem == 3)) {
        tempk = dataresponse;
      }
      dataresponse = "";
      dem = 0;
    } else if (c == 'o') {
      if (((uint8_t)dataresponse.toInt() > 0) && (dem == 3)) {
        humpk = dataresponse;
      }
      dataresponse = "";
      dem = 0;
    } else if (c == 'b') {
      if (((uint8_t)dataresponse.toInt() > 0) && (dem == 3)) {
        doamdat = dataresponse;
      }
      dataresponse = "";
      dem = 0;
    } else if (c == 'u')  //wc
    {
      if (((uint8_t)dataresponse.toInt() > 0) && (dem == 3)) {
        temwc = dataresponse;
      }
      dataresponse = "";
      dem = 0;
    } else if (c == 'y') {
      if (((uint8_t)dataresponse.toInt() > 0) && (dem == 3)) {
        humwc = dataresponse;
      }
      dataresponse = "";
      dem = 0;
    } else if (c == 'f') {
      if ((dem == 3)) {
        // gas = dataresponse;
        // Serial.println(gas);

        gas = dataresponse;
        // Serial.println("gas",gas);
      }
      dataresponse = "";
      dem = 0;
    } else if (c == 'l') {
      if (dem == 2) {
        ledState = dataresponse;
      }
      dataresponse = "";
      dem = 0;
    } else if (c == 'd') {
      if (dem == 2) {
        servogarastate = dataresponse;
      }
      dataresponse = "";
      dem = 0;
    } else if (c == 's') {
      if (dem == 2) {
        ledStatePN = dataresponse;
      }
      dataresponse = "";
      dem = 0;
    } else if (c == 'q') {
      if (dem == 2) {
        quatState = dataresponse;
      }
      dataresponse = "";
      dem = 0;
    } else if (c == 'a') {
      if (dem == 2) {
        quatStatePK = dataresponse;
      }
      dataresponse = "";
      dem = 0;
    } else {
      dataresponse = dataresponse + c;
    }
  }
}

//----------------------------------------------------------------
void handleprint() {
  hengio = server.arg("result");
}

void realTime(void) {
  static unsigned char demin = 0;
  static unsigned char flagHenGioOld = 0;
  demin++;
  if (demin > 100) {
    String gio;
    n.update();
    gio = n.getFormattedTime();
    for (int i = 0; i < 5; i++) {
      gioup = gioup + gio[i];
    }
    if (gioup == hengio) {
      if (flagHenGioOld == 0) {
        flagHenGioOld = 1;
        Serial.print("*");
        delay(100);
        Serial.print("*");
        delay(100);
        Serial.print("*");
      }
    } else {
      flagHenGioOld = 0;
    }
    demin = 0;
    gioup = "";
  }
}

//-----------------------------------------------------------------
void handleTEMPprint() {
  String tempfromweb = server.arg("result1");
  tempfromweb = tempfromweb + "n";

  //SEND ARDUINO
  Serial.print(tempfromweb);
  delay(100);
  Serial.print(tempfromweb);
  delay(100);
  Serial.print(tempfromweb);
}

void handleTEMPPKprint() {
  String tempfromwebPK = server.arg("result2");
  tempfromwebPK = tempfromwebPK + "k";

  //SEND ARDUINO
  Serial.print(tempfromwebPK);
  delay(100);
  Serial.print(tempfromwebPK);
  delay(100);
  Serial.print(tempfromwebPK);
}

//------------------------------------------------------------------
void handleTEMPPN() {
  server.send(200, "text/plane", tempn);  //Send TEM-PN value only to client ajax request
}

void handleTEMPPK() {
  server.send(200, "text/plane", tempk);  //Send TEM-PK value only to client ajax request
}

void handleTEMPWC() {
  server.send(200, "text/plane", temwc);  //Send TEM-WC value only to client ajax request
}

void handleHUMPN() {
  server.send(200, "text/plane", humpn);  //Send HUM-PN value only to client ajax request
}

void handleHUMPK() {
  server.send(200, "text/plane", humpk);  //Send HUM-PK value only to client ajax request
}
void handledoamdat() {
  server.send(200, "text/plane", doamdat);  //Send HUM-PK value only to client ajax request
}


void handleHUMWC() {
  server.send(200, "text/plane", humwc);  //Send HUM-WC value only to client ajax request
}

void handleGAS() {
  server.send(200, "text/plane", gas);  //Send GAS value only to client ajax request
}

//-------------------------------------------------------------------
void handleLED() {
  String t_state = server.arg("LEDstate");  //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
  if (t_state == "1") {
    ledState = "1";  //Feedback parameter
  } else {
    ledState = "0";  //Feedback parameter
  }
  server.send(200, "text/plane", ledState);  //Send web page

  //SEND ARDUINO
  t_state = t_state + "l";
  Serial.print(t_state);
  delay(100);
  Serial.print(t_state);
  delay(100);
  Serial.print(t_state);
}
void handleServo() {
  String t_state = server.arg("ServoState");  //Refer  xhttp.open("GET", "setServo?ServoState="+led, true);
  // gui json

  // Serial.print(t_state);
  if (t_state == "1") {
    ServoState = "1";  //Feedback parameter
  } else {
    ServoState = "0";  //Feedback parameter
  }
  server.send(200, "text/plane", ServoState);  //Send web page
  //SEND ARDUINO
  t_state = t_state + "r";
  Serial.print(t_state);
  mySerial.print(t_state);
  delay(10);
}
// led Phòng ngủ
void handleLEDPN() {
  String t_state = server.arg("LEDstatePN");  //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
  if (t_state == "1") {
    ledStatePN = "1";  //Feedback parameter
  } else {
    ledStatePN = "0";  //Feedback parameter
  }
  server.send(200, "text/plane", ledStatePN);  //Send web page

  //SEND ARDUINO
  t_state = t_state + "z";
  Serial.print(t_state);
  delay(100);
  Serial.print(t_state);
  delay(100);
  Serial.print(t_state);
}


void handleQUAT() {
  String q_state = server.arg("QUATstate");
  if (q_state == "0") {
    quatState = "1";  //Feedback parameter
  } else {
    quatState = "0";  //Feedback parameter
  }
  server.send(200, "text/plane", quatState);  //Send web page

  //SEND ARDUINO
  q_state = q_state + "q";
  Serial.print(q_state);
  delay(100);
  Serial.print(q_state);
  delay(100);
  Serial.print(q_state);
}
// servo cua gara
void handleservogara() {
  String q_state = server.arg("servogarastate");
  if (q_state == "1") {
    servogarastate = "1";  //Feedback parameter
  } else {
    servogarastate = "0";  //Feedback parameter
  }
  server.send(200, "text/plane", servogarastate);  //Send web page

  //SEND ARDUINO
  q_state = q_state + "i";
  Serial.print(q_state);
  delay(100);
  Serial.print(q_state);
  delay(100);
  Serial.print(q_state);
}
// quạt cho phòng khách

void handleQUATPK() {
  String q_state = server.arg("QUATstatePK");
  if (q_state == "0") {
    quatStatePK = "1";  //Feedback parameter
  } else {
    quatStatePK = "0";  //Feedback parameter
  }
  server.send(200, "text/plane", quatStatePK);  //Send web page

  //SEND ARDUINO
  q_state = q_state + "v";
  Serial.print(q_state);
  delay(100);
  Serial.print(q_state);
  delay(100);
  Serial.print(q_state);
}
// bat may bom

void handlemaybom() {
  String q_state = server.arg("statemaybom");
  if (q_state == "1") {
    statemaybom = "1";  //Feedback parameter
  } else {
    statemaybom = "0";  //Feedback parameter
  }
  server.send(200, "text/plane", statemaybom);  //Send web page

  //SEND ARDUINO
  q_state = q_state + "s";
  Serial.print(q_state);
  delay(100);
  Serial.print(q_state);
  delay(100);
  Serial.print(q_state);
}
// bat quat wc

void handlequatwc() {
  String q_state = server.arg("quatwcstate");
  if (q_state == "1") {
    quatwcstate = "1";  //Feedback parameter
  } else {
    quatwcstate = "0";  //Feedback parameter
  }
  server.send(200, "text/plane", quatwcstate);  //Send web page

  //SEND ARDUINO
  q_state = q_state + "w";
  Serial.print(q_state);
  delay(100);
  Serial.print(q_state);
  delay(100);
  Serial.print(q_state);
}

//-------------------------------------------------------------------
void sendsttbuttonled(void) {
  server.send(200, "text/plane", ledState);  //Send web page
}
void sendsttbuttonledPN(void) {
  server.send(200, "text/plane", ledStatePN);  //Send web page
}
void sendsttServo(void) {
  server.send(200, "text/plane", ServoState);  //Send web page
}
// servo cua gara
void sendsttservogara(void) {
  server.send(200, "text/plane", servogarastate);  //Send web page
}

void sendsttbuttonquat(void) {
  server.send(200, "text/plane", quatState);  //Send web page
}
void sendsttbuttonquatPK(void) {
  server.send(200, "text/plane", quatStatePK);  //Send web page
}
void sendsttmaybom(void) {
  server.send(200, "text/plane", statemaybom);  //Send web page
}
void sendsttquatwc(void) {
  server.send(200, "text/plane", quatwcstate);  //Send web page
}

//==============================================================
//                  SETUP
//==============================================================
void setup(void) {
  Serial.begin(115200);
  mySerial.begin(9600);
  n.begin();

  WiFi.begin(ssid, password);  //Connect to your WiFi router
                               //  Serial.println("");

  //Onboard LED port Direction output
  pinMode(LED, OUTPUT);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //  If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  server.on("/", handleRoot);  //Which routine to handle at root location. This is display page
  server.on("/setLED", handleLED);
  server.on("/setLEDPN", handleLEDPN);
  server.on("/setServo", handleServo);


  server.on("/setQUAT", handleQUAT);
  server.on("/setQUATPK", handleQUATPK);
  server.on("/setmaybom", handlemaybom);
  server.on("/setquatwc", handlequatwc);



  // servo gara

  server.on("/setservogara", handleservogara);
  server.on("/setTIME", handleprint);

  server.on("/readTEMPPN", handleTEMPPN);
  server.on("/readTEMPPK", handleTEMPPK);
  server.on("/readTEMPWC", handleTEMPWC);

  server.on("/readHUMPN", handleHUMPN);
  server.on("/readHUMPK", handleHUMPK);
  // do am dat
  server.on("/readdoamdat", handledoamdat);
  server.on("/readHUMWC", handleHUMWC);


  server.on("/readGAS", handleGAS);

  server.on("/setLEDstt", sendsttbuttonled);
  server.on("/setLEDsttPN", sendsttbuttonledPN);

  server.on("/setQUATstt", sendsttbuttonquat);
  server.on("/setServostt", sendsttServo);

  server.on("/setQUATsttPK", sendsttbuttonquatPK);
  server.on("/setmaybom", sendsttmaybom);
  server.on("/setquatwc", sendsttquatwc);

  server.on("/setTEMP", handleTEMPprint);
  server.on("/setTEMPPK", handleTEMPPKprint);

  server.begin();  //Start server
}

//==============================================================
//                     LOOP
//==============================================================
void loop(void) {
  reciveforweb();
  realTime();
  server.handleClient();
}

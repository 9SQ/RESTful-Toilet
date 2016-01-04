#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>

#define LED 5
#define IR 12

const char* ssid = “**********”;
const char* password = "**********";
MDNSResponder mdns;
ESP8266WebServer server(80);

IRsend irsend(IR);

unsigned int ir_stop1[81] = {5950,2850,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,1550,600,500,600,1550,600,500,600,1550,600,500,600,1550,600,500,600,1550,600,1550,600,500,600,1550,600,1550,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,600};
unsigned int ir_stop2[81] = {5950,2850,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600};

unsigned int ir_rear1[81] = {5950,2850,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,1550,600,500,600,500,600,500,600,500,600,500,600};
unsigned int ir_rear2[81] = {5950,2850,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,1550,600,1550,600,500,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,1550,600,500,600,1550,600,1550,600,500,600,500,600};

unsigned int ir_soft1[81] = {5950,2850,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,1550,600,500,600,500,600,500,600,500,600,500,600};
unsigned int ir_soft2[81] = {5950,2850,600,500,600,1600,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,1550,600,1550,600,500,600,500,600,1550,600,500,600,1550,600,500,600,1550,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600};

unsigned int ir_bidet1[81] = {5950,2850,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,500,600};
unsigned int ir_bidet2[81] = {5950,2850,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,1550,600,1550,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,1550,600,500,600,1550,600,1550,600,500,600,500,600};

unsigned int ir_big[81] = {5950,2850,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,1550,600,1550,600,500,600,500,600,500,600,500,600,1550,600,500,600,1550,600,1550,600,500,600,500,600,500,600,500,600};

unsigned int ir_small[81] = {5950,2850,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600};

void handleRoot() {
  String s = "<!DOCTYPE html><html><head><meta charset=\"utf-8\">";
  s += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  s += "<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js\"></script>";
  s += "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css\">";
  s += "<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js\"></script>";
  s += "<script>function rest(cmd,method){var http = new XMLHttpRequest();var url = \"/washlet\";http.open(method, url, true);http.send(\"c=\"+cmd);http.onreadystatechange=function(){if(http.readyState == 4 && http.status == 200){alert(http.responseText);}}}</script>";
  s += "</head><body>";
  s += "<div class=\"container\"><div class=\"row\"><div class=\"col-md-12 text-center\">";
  s += "<h1 class=\"page-header\">RESTful Toilet</h1>";
  s += "<h2>洗浄</h2>";
  s += "<div class=\"btn-group\" role=\"group\" aria-label=\"rear\">";
  s += "<button type=\"button\" class=\"btn btn-primary btn-lg\" onclick=\"rest('rear','POST');\">おしり</button>";
  s += "<button type=\"button\" class=\"btn btn-primary btn-lg\" onclick=\"rest('soft','POST');\">やわらか</button>";
  s += "<button type=\"button\" class=\"btn btn-primary btn-lg\" onclick=\"rest('bidet','POST');\">ビデ</button>";
  s += "</div><br>&nbsp;<br>";
  s += "<p><button type=\"button\" class=\"btn btn-danger btn-lg\" onclick=\"rest('stop','POST');\">ストップ</button></p>";
  s += "<hr>";
  s += "<h2>流す</h2>";
  s += "<div class=\"btn-group\" role=\"group\" aria-label=\"flow\">";
  s += "<button type=\"button\" class=\"btn btn-info btn-lg\" onclick=\"rest('big','DELETE');\">大</button>";
  s += "<button type=\"button\" class=\"btn btn-info btn-lg\" onclick=\"rest('small','DELETE');\">小</button>";
  s += "</div>";
  s += "</div></div></div>";
  s += "</body></html>";
  server.send(200, "text/html", s);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleWashlet() {
  String s = "";
  if (server.method() == HTTP_POST) {
    if (server.arg("c") == "rear") {
      Serial.println("rear");
      s += "おしり洗浄開始";
      irsend.sendRaw(ir_rear1, 81, 38);
      delay(10);
      irsend.sendRaw(ir_rear2, 81, 38);
    }
    else if (server.arg("c") == "soft") {
      Serial.println("soft");
      s += "おしりやわらか洗浄開始";
      irsend.sendRaw(ir_soft1, 81, 38);
      delay(10);
      irsend.sendRaw(ir_soft2, 81, 38);
    }
    else if (server.arg("c") == "bidet") {
      Serial.println("front");
      s += "ビデ開始";
      irsend.sendRaw(ir_bidet1, 81, 38);
      delay(10);
      irsend.sendRaw(ir_bidet2, 81, 38);
    }
    else if (server.arg("c") == "stop") {
      Serial.println("stop");
      s += "ストップ";
      irsend.sendRaw(ir_stop1, 81, 38);
      delay(10);
      irsend.sendRaw(ir_stop2, 81, 38);
    }
    else {
      s += "error";
    }
  }
  else if (server.method() == HTTP_DELETE) {
    if (server.arg("c") == "big") {
      Serial.println("big");
      s += "流しました(大)";
      irsend.sendRaw(ir_big, 81, 38);
    }
    else if (server.arg("c") == "small") {
      Serial.println("small");
      s += "流しました(小)";
      irsend.sendRaw(ir_small, 81, 38);
    }
    else {
      s += "error";
    }
  }
  else {
    s += "error";
  }
  server.send(200, "text/plain", s);
}

void setup(void) {
  irsend.begin();
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  pinMode(LED, OUTPUT);
  
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED, HIGH);
    delay(250);
    digitalWrite(LED, LOW);
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("toilet", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/washlet", handleWashlet);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  
  digitalWrite(LED, HIGH);
}

void loop(void) {
  server.handleClient();
}

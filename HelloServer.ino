#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "CMCC_KF"
#define STAPSK  "dswybsmm"
#endif
const uint8_t in1 = 2; //D4
const uint8_t in2 = 14; //D5
const uint8_t in3 = 12; //D6
const uint8_t in4 = 13; //D7
//上面定义了板上的4个控制端，12一组，34一组
const uint8_t speedPinA = 5;  //D1
const uint8_t speedPinB = 4;  //D2
//上面定义了PWM引脚
//下面开始定义方向
//tup=0; tdown=1; tleft=2; tright=3;
int turn = 8;
const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

const int led = 13;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
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
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
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

  server.on("/", handleRoot);

  server.on("/up", []() {
    turn = 0;
    Serial.println("向前");
    server.send(200, "application/json;charset=utf-8", "{\"state\":200,\"msg\":\"向前\"}");
  });
  server.on("/down", []() {
    turn = 1;
    Serial.println("向后");
    server.send(200, "application/json;charset=utf-8","{\"state\":200,\"msg\":\"向后\"}");
  });
  server.on("/left", []() {
    turn = 2;
    Serial.println("向左");
    server.send(200, "application/json;charset=utf-8", "{\"state\":200,\"msg\":\"向左\"}");
  });
  server.on("/right", []() {
    turn = 3;
    Serial.println("向右");
    server.send(200, "application/json;charset=utf-8","{\"state\":200,\"msg\":\"向右\"}");
  });
  server.on("/stop", []() {
    turn = 4;
    Serial.println("停止");
    server.send(200, "application/json;charset=utf-8", "{\"state\":200,\"msg\":\"停止\"}");
  });
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  //让网络连接后初始化针脚，防止小车不受控制
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //下面程序开始时让控制端都为高电平，电机保持不动。
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
}

void loop(void) {
  server.handleClient();
  MDNS.update();
  switch (turn) //通过这个循环，控制小车方向
  {
    case 0: //前进
      _mup(in1, in2, in3, in4);
      //读入电位器的值，然后通过PWM输出，控制电机转速
      _mSetSpeed(speedPinA, 1000);
      _mSetSpeed(speedPinB, 1000);
      break;
    case 1: //后退
      _mdown(in1, in2, in3, in4);
      //读入电位器的值，然后通过PWM输出，控制电机转速
      _mSetSpeed(speedPinA, 1000);
      _mSetSpeed(speedPinB, 1000);
      break;
    case 2: //左转
      _mleft(in1, in2, in3, in4);
      _mSetSpeed(speedPinA, 800);
      _mSetSpeed(speedPinB, 600);
      break;
    case 3: //右转
      _mright(in1, in2, in3, in4);
      _mSetSpeed(speedPinA, 600);
      _mSetSpeed(speedPinB, 800);
      break;
    case 4: //停止
      _mStop(in1, in2, in3, in4);
      break;
  };
}
void _mleft(int pin1, int pin2, int pin3, int pin4) //左转
{
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, HIGH);
}
void _mright(int pin1, int pin2, int pin3, int pin4) //右转
{
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, LOW);
}
void _mup(int pin1, int pin2, int pin3, int pin4) //前进
{
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, LOW);
}
void _mdown(int pin1, int pin2, int pin3, int pin4) //后退
{
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, HIGH);
}
void _mStop(int pin1, int pin2, int pin3, int pin4) //紧急制动，实际就是将电机两个端短接了
{
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, HIGH);
}
void _mSetSpeed(int pinPWM, int SpeedValue) //控制速度，实际上就是断断续续的控制298N的使能端，手抖的厉害的可以用个按钮自己尝试一下，估计也能实现对电机速度的控制，O(∩_∩)O~
{
  if (SpeedValue > 1023) SpeedValue = 1023;
  analogWrite(pinPWM, SpeedValue);
}

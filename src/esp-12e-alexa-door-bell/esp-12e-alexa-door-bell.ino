//Builkd using Arduino IDE
//Arduino ISE Board: NodeMCU 1.0 (ESP-12E Module)
#include <GDBStub.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include "config.h"  // Copy config.h.sample
#include "secrets.h" // Copy secrets.h.sample
#include "StateMachine.hpp"


const long FLASH_MARK=10;
const long FLASH_PERIOD=150;
const long SEQUENCE_PERIOD=(FLASH_PERIOD*10);
int flashes = 1;

void ledWrite(bool state)
{
  digitalWrite(LED_BUILTIN,!state);
}

WiFiClientSecure httpsClient;
const uint16_t port = 443;

class DoorbellStateMachine : public StateMachine
{
public:
    DoorbellStateMachine() {
        InitStateMachine();
    }

    void Execute() {
      EvaluateEvents();
    }

    void EvaluateEvents()
    {
      switch (CurrentState()) {
      case StateId_ConnectWiFi:
        flashes = 2;
        if(WiFi.status() == WL_CONNECTED) {
          WiFi_is_connected();
        }
        break;

      case StateId_Sense:
        flashes = 3;
        if (digitalRead(4)) {
          SwitchIsPushed();
        }
        break;

      case StateId_Report:
        //if (http.GET() == HTTP_CODE_OK) {
        //  ReportSuccessful();
        //}
        break;
      }
    }

    //Actions
    void Print_connected() override {
      Serial.println("WiFi Connected");
    }

    void PrintSwitchIsPushed() override {
      Serial.println("Switch was pushed");
    }

    void NotifyAlexa() override {
      ledWrite(true);
      Serial.printf("NotifyAlexa() called\r\n");
      httpsClient.setInsecure();
      if (!httpsClient.connect(host, port)) {
        Serial.println("Connection failed");
      }
      Serial.printf("Calling http://%s%s", host, page);
      httpsClient.print(String("GET ") + page + " HTTP/1.1\r\n" +
              "Host: " + host + "\r\n" +
              "User-Agent: esp-12e-alexa-door-bell\r\n" +
              "Connection: close\r\n\r\n");
      while (httpsClient.connected()) {
        String line = httpsClient.readStringUntil('\n');
        Serial.println(line);
        if (line.startsWith("HTTP/1.1 200 OK")) {
          Serial.println("Report Successful");
          ReportSuccessful();
          break;
        }
      }
      ledWrite(false);
    }
    
};
DoorbellStateMachine* stateMachine;

int epoch = 0;

void setup() {
  Serial.begin(115200);
  gdbstub_init();
  pinMode(4, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("\r\n\r\nsetup()");  
  Serial.printf("Web hook URL: http://%s%s", host, page);

  stateMachine = new DoorbellStateMachine();
  WiFi.begin(ssid, pass);
}


void loop() {
  epoch++;
  long msSinceBoot = millis();
  ledWrite(msSinceBoot%FLASH_PERIOD<FLASH_MARK && msSinceBoot%SEQUENCE_PERIOD<flashes*FLASH_PERIOD);
  

  StateId currentState = stateMachine->CurrentState();
  std::string name = (StateNames.find(currentState))->second;
  //Serial.printf("State: %s\r\n", name.c_str());

  stateMachine->Execute();
}

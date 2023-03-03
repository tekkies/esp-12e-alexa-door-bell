//Builkd using Arduino IDE
//Arduino ISE Board: NodeMCU 1.0 (ESP-12E Module)
#include <GDBStub.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include "config.h"  // Copy config.h.sample
#include "secrets.h" // Copy secrets.h.sample
#include "StateMachine.hpp"


int flashOnMs = 1;
int flashOffMs = 1;
void FlashMode(int onMs, int offMs)
{
  flashOnMs = onMs;
  flashOffMs = offMs;
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
        FlashMode(500, 500);
        if(WiFi.status() == WL_CONNECTED) {
          WiFi_is_connected();
        }
        break;

      case StateId_Sense:
        FlashMode(10, 200);
        if (!digitalRead(4)) {
          SwitchIsPushed();
        }
        break;

      case StateId_Report:
        FlashMode(1000,0);
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
        Serial.printf("NotifyAlexa() called\r\n");
        httpsClient.setInsecure();
        if (!httpsClient.connect(host, port)) {
          Serial.println("Connection failed");
        }
        httpsClient.print(String("GET ") + page + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: esp-12e-alexa-door-bell\r\n" +
               "Connection: close\r\n\r\n");
        while (httpsClient.connected()) {
          String line = httpsClient.readStringUntil('\n');
          Serial.println(line);
          if (line == "\r") {
            Serial.println("Headers received");
            break;
        }
      }
    }


};
DoorbellStateMachine* stateMachine;

int epoch = 0;

void setup() {
  pinMode(4, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  gdbstub_init();
  Serial.println("\r\n\r\nsetup()");  
  stateMachine = new DoorbellStateMachine();
  WiFi.begin(ssid, pass);
}


void loop() {
  epoch++;
  digitalWrite(LED_BUILTIN,millis() % (flashOnMs+flashOffMs) > flashOnMs);

  StateId currentState = stateMachine->CurrentState();
  std::string name = (StateNames.find(currentState))->second;
  //Serial.printf("State: %s\r\n", name.c_str());

  stateMachine->Execute();
}

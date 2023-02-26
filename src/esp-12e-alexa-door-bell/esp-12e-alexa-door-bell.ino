//Builkd using Arduino IDE
//Arduino ISE Board: NodeMCU 1.0 (ESP-12E Module)
#include <GDBStub.h>
#include <ESP8266WiFi.h>

#include "config.h"
#include "secrets.h"
#include "StateMachine.hpp"


int flashOnMs = 1;
int flashOffMs = 1;
void FlashMode(int onMs, int offMs)
{
  flashOnMs = onMs;
  flashOffMs = offMs;
}

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
          WiFiConnected();
        }
        break;

      case StateId_Sense:
        FlashMode(10, 200);
        if (!digitalRead(4)) {
          SwitchPushed();
        }
        break;

      case StateId_Report:
        FlashMode(1000,0);
        break;
      }
    }

    //Actions
    void NotifyAlexa() override {
        Serial.printf("NotifyAlexa() called\r\n");
    }
};
DoorbellStateMachine* stateMachine;

int epoch = 0;

void setup() {
  pinMode(4, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  gdbstub_init();
  Serial.println("setup()");  
  stateMachine = new DoorbellStateMachine();
  WiFi.begin(ssid, pass);
}


void loop() {
  epoch++;
  digitalWrite(LED_BUILTIN,millis() % (flashOnMs+flashOffMs) > flashOnMs);

  StateId currentState = stateMachine->CurrentState();
  std::string name = (StateNames.find(currentState))->second;
  Serial.printf("State: %s\r\n", name.c_str());

  stateMachine->Execute();
}

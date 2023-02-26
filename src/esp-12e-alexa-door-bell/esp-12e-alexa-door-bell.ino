//Builkd using Arduino IDE
//Arduino ISE Board: NodeMCU 1.0 (ESP-12E Module)
#include <GDBStub.h>
#include <ESP8266WiFi.h>

#include "config.h"
#include "secrets.h"
#include "StateMachine.hpp"


class DoorbellStateMachine : public StateMachine
{
public:
    DoorbellStateMachine()
    {
        InitStateMachine();
    }

    void Execute()
    {
      EvaluateEvents();
    }

    void EvaluateEvents()
    {
      switch (CurrentState())
      {
      case StateId_Sense:
          if (!digitalRead(4))
          {
              SwitchPushed();
          }
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
  digitalWrite(LED_BUILTIN,epoch % 10 ? 0 : 1);
  Serial.println(epoch);
  
  if(WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi Connected");
  }

  StateId currentState = stateMachine->CurrentState();
  std::string name = (StateNames.find(currentState))->second;
  Serial.printf("State: %s\r\n", name.c_str());

  stateMachine->Execute();
}

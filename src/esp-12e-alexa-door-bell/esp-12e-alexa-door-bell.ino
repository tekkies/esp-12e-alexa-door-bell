//Builkd using Arduino IDE
//Arduino ISE Board: NodeMCU 1.0 (ESP-12E Module)
#include <GDBStub.h>
#include <ESP8266WiFi.h>

#include "config.h"
#include "secrets.h"
#include "StateMachine.hpp"


class MyStateMachine : public StateMachine
{
public:
    MyStateMachine()
    {
        InitStateMachine();
    }

    void NotifyAlexa() override {
        Serial.printf("NotifyAlexa() called\r\n");
    }
};
MyStateMachine* myStateMachine;

int epoch = 0;
#define GPIO_4 4

void setup() {
  pinMode(GPIO_4, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  gdbstub_init();
  Serial.println("setup()");  
  myStateMachine = new MyStateMachine();
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

  StateId currentState = myStateMachine->CurrentState();
  std::string name = (StateNames.find(currentState))->second;
  Serial.printf("State: %s\r\n", name.c_str());
  switch (currentState)
  {
  case StateId_Sense:
      if (!digitalRead(GPIO_4))
      {
          myStateMachine->SwitchPushed();
      }
      break;
  }
}

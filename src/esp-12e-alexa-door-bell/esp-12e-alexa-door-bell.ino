//Builkd using Arduino IDE
//Arduino ISE Board: NodeMCU 1.0 (ESP-12E Module)
#include <ESP8266WiFi.h>

#include "config.h"
#include "secrets.h"
#include "stateMachine.h"

const char version[] = "0.0.1";

ADC_MODE(ADC_VCC);


class SuccessState : IState {
  public: 
    SuccessState(String name) : IState(name) {}
    void execute()
    {
        IState::execute();
        ESP.deepSleep(sleepSeconds * 1e6); 
    }
};

class FailState : IState {
  public: 
    FailState(String name) : IState(name) {
      }
    void execute()
    {
      IState::execute();
      Serial.println("Failed");  
    }
};


class FlipState : IState {
  public: 
    FlipState(String name) : IState(name) {
      exitStates = new char*[2];
      exitStates[0]="FlopState";
      exitStates[2]=NULL;
    }
    void execute()
    {
      IState::execute();
      Serial.println("Flip");  
      setState("FlopState");
    }
};


class FlopState : IState {
  public: 
    FlopState(String name) : IState(name) {
      exitStates = new char*[2];
      exitStates[0]="FlipState";
      exitStates[2]=NULL;
    }
    
    void execute()
    {
      IState::execute();
      Serial.println("Flop");  
      setState("FlipState");
    }
};


#define DECLARESTATE(aState) (IState*)(new aState(#aState))
IState *states[] = 
{
  DECLARESTATE(SuccessState),
  DECLARESTATE(FailState),
  DECLARESTATE(DelayState),
  DECLARESTATE(FlipState),
  DECLARESTATE(FlopState),
  NULL
};


void setup() {
  Serial.begin(115200);
  Serial.println("setup");  
  WiFi.begin(ssid, pass);
  setState("FlipState");
}


void loop() {
  Serial.println("loop");
  
  //Serial.println(state->stateName);  
  if(WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi Connected");
  }
  state->execute();
}

# esp-12e-alexa-door-bell

[![stability-alpha](https://img.shields.io/badge/stability-alpha-f4d03f.svg)](https://github.com/mkenney/software-guides/blob/master/STABILITY-BADGES.md#alpha)

Announce the doorbell on Alexa using ESP-12E WiFi module from a 15V AC or DC power supply.

A practical teaching project to learn electronics and coding with my kid: "It's like a puzzle that when you complete, your life get's an upgrade"

Designing the high-level program flow using PlantUML, then generating the state machine C++ abstract classes allows very simple program design around the setup() loop() Arduino paradigm. 

## PlantUML Based Program Flow
![Software Design](src/esp-12e-alexa-door-bell/fsm.plantuml.png)

### State Machine Implementation
[FloHsm](https://github.com/tzijnge/FloHsm) is used to convert the PlantUML source used to crete the diagram above to generate C++ abstract classes. The details of the states, events and actions are then implemented in a concrete subclass, e.g.

#### State/Event
Here, the state case statement is called in every time loop() runs, so on each loop, the code checks to see it the button is pressed.  If so, the event triggers and we move to the next state.
```
case StateId_Sense:
  if (!digitalRead(4)) {
    SwitchIsPushed(); //Trigger an event
  }
  break;
```
#### Action
```
void NotifyAlexa() override {
      Serial.printf("NotifyAlexa() called\r\n");
      ...
}
```

## LED States
``..    `` WiFi Connecting

``...   `` Sensing

``______`` Reporting

## Circuit Design
![Circuit Design](hardware/esp-12e-alexa-door-bell.TinyCad.png)

## Board Layout
![Board Layout](hardware/esp-12e-alexa-door-bell.VeeCAD.png)

## Power Supply Design
 ![Power Supply Simulator](hardware/power-supply.ltspice.png)

# Development Environment
## Windows
### Toolchain
* [Install Arduino IDE and ESP8266 Suport](https://arduino-esp8266.readthedocs.io/en/latest/installing.html)
* [Visual Studio Code](https://code.visualstudio.com/download)
  * Install Plugin: "Arduino" by Microsoft

### Build & Deploy
* Regenerate state machine template code if the state diagram has changed
* Run from folder src\esp-12e-alexa-door-bell
  
#### Using [FloHsm by tzijnge](https://github.com/tzijnge/FloHsm)
  * FloHsm.py fsm.plantuml
#### Using Docker
  * `` docker run -v $(pwd):/run tekkiesuk/flohsm:latest fsm.plantuml``
    * A couple or warnings is normal

#### Using VS Code
  * Open the .ino file
  * <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd>, Arduino: Select Serial Port
  * <kbd>Ctrl</kbd> + <kbd>ALT</kbd> + <kbd>U</kbd>
    * Alternative: <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd>, Arduino: Upload
#### Using Arduino IDE
* Select Board NODEMCU 1.0
* Select Port
* Sketch, Upload
 
### Debug
#### Using VS Code
* Open the .ino file
* Close the serial monitor if you have it open, otherwise the debugger will not be able to connect
* First Build & Deploy
  * **Remember to redeploy if you change the code**
* <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd>, Arduino: Upload
* Place a breakpoint inside ``loop()``
* Press <kbd>F5</kbd>
* **CAVEAT:** It appears only one breakpoint can be set at a time due to hardware limitations

 # Credits
Built standing on the shoulders of these giants:
 - [LTspice](https://www.analog.com/en/design-center/design-tools-and-calculators/ltspice-simulator.html)
 - [TinyCAD by matt123p](https://github.com/matt123p/TinyCAD)
 - [VeeCAD by Roger Lascelles](http://veecad.com)
 - [FloHsm by tzijnge](https://github.com/tzijnge/FloHsm)

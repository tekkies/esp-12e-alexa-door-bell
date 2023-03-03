# esp-12e-alexa-door-bell

[![stability-alpha](https://img.shields.io/badge/stability-alpha-f4d03f.svg)](https://github.com/mkenney/software-guides/blob/master/STABILITY-BADGES.md#alpha)

Announce the doorbell on Alexa using ESP-12E WiFi module from a 15V AC or DC power supply.

A practical teaching project to learn electronics and coding with my kid: "It's like a puzzle that when you complete, your life get's an upgrade"

## Software Design
![Software Design](src/esp-12e-alexa-door-bell/fsm.plantuml.png)

Code generated using [FloHsm by tzijnge](https://github.com/tzijnge/FloHsm)

## LED States
``_ _ _ _`` WiFi Connecting

``. . . .`` Sensing

``_______`` Report

## Circuit Design
![Circuit Design](hardware/esp-12e-alexa-door-bell.TinyCad.png)

## Board Layout
![Board Layout](hardware/esp-12e-alexa-door-bell.VeeCAD.png)

## Power Supply Design
 ![Power Supply Simulator](hardware/power-supply.ltspice.png)

# Development
* Generate FSM template code
  * `` docker run -v $(pwd):/run tekkiesuk/flohsm:latest fsm.plantuml``
    * A couple or warnings is normal
* Build binary in Arduino Studio

 # Credits
Built standing on the shoulders of these giants:
 - [LTspice](https://www.analog.com/en/design-center/design-tools-and-calculators/ltspice-simulator.html)
 - [TinyCAD by matt123p](https://github.com/matt123p/TinyCAD)
 - [VeeCAD by Roger Lascelles](http://veecad.com)
 - [FloHsm by tzijnge](https://github.com/tzijnge/FloHsm)

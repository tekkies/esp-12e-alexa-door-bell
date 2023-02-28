# esp-12e-alexa-door-bell

[![stability-wip](https://img.shields.io/badge/stability-wip-lightgrey.svg)](https://github.com/mkenney/software-guides/blob/master/STABILITY-BADGES.md#work-in-progress)

Announce the doorbell on Alexa using ESP-12E WiFi module from a 15V AC or DC power supply.

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



# Setup CI

## Create GitHub Runner
- ``docker build --tag esp-12e-alexa-door-bell-build --progress=plain ci/arduino``
- ``docker run --interactive --tty esp-12e-alexa-door-bell-build``
- [Configure the runner](https://github.com/tekkies/esp-12e-alexa-door-bell/settings/actions/runners/new?arch=x64&os=linux)


 # Credits
Built standing on the shoulders of these giants:
 - [LTspice](https://www.analog.com/en/design-center/design-tools-and-calculators/ltspice-simulator.html)
 - [TinyCAD by matt123p](https://github.com/matt123p/TinyCAD)
 - [VeeCAD by Roger Lascelles](http://veecad.com)
 - [FloHsm by tzijnge](https://github.com/tzijnge/FloHsm)
    - Be patient, then just go with the defaults when asked

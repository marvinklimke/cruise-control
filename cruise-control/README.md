# Cruise Control for a Recreational Craft

This repository contains the code for a cruise control system for a recreational
craft. Atmel Studio 7.0 was used to create this AVR-GCC-based project.

## Device Info

* Atmel AVR ATmega328P
* Data bus: 8 Bit
* Clock: 16 MHz external oscillator
* Flash: 32 KBytes ISP

## Internal Modules

Internal C modules are located in the `cruise-control` folder.

| Module   | Description                                                    |
|----------|----------------------------------------------------------------|
| `adc`    | Provides access to the internal analog to digital converter    |
| `bt`     | Preparation for serial over bluetooth connection to smartphone |
| `clock`  | System clock and simple delay functions                        |
| `engine` | Interrupt handling for engine RPM measurement                  |
| `main.c` | Main controller loop                                           |
| `pid`    | Performs computations of the PID controller                    |
| `servo`  | Actuation of the servo drive for manipulated variable          |
| `ui`     | User interaction via hardware switches and lights              |

## External Modules

External modules are located in the `cruise-control/lib` folder. The following
modules are used:

* I2C master library by Peter Fleury
* Updated UART library by Andy Gock

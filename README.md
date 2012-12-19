#LAMPS - The Open Hardware SLA Printer
LAMPS is an open control board and SLA printer design.  

##License
The entire lamps project (PCB, Source Code, Design Files... EVERYTHING) is licensed under the Creative Commons - Attribution Non Commercial Share Alike (3.0) (CC BY-NC-SA 3.0). http://creativecommons.org/licenses/by-nc-sa/3.0/

That means you can use my design, but you are not allowed to profit or sell any part of it.  If you are looking for an exception, contact me and I'll take it under consideration.

##LAMPS Board
LAMPS is the PCB control board that rides on top of an Arduino Mega 2560.  It provides Galvanometer control (Through 12 bit DACs).  It also controls the laser, buttons, Z Stepper Motor (Through Pololu Carrier), End Stops, LEDs, etc...  (It is the Brainz).

Version 1.0 of the LAMPS board has been manufactured and tested... I found a few issues with the board and am currently redesigning and removing a few unnecessary components for 1.1. Release date T.B.D.

##Firmware
The firmware for LAMPS is a fork of Marlin (The best open source RepRap firmware I know of), and can be found here: https://github.com/beardface/Marlin-LAMPS
The firmware is very much an active work-in-progress, and I encourage you to fork, and contribute.

##Parts
All of the parts are available as sketchup (skp) and stl files.

##Non-Printer Parts
The parts were all designed to be used with Misumi 2020 rails.

###LAMPS IS A WORK IN PROGRESS.

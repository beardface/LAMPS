LAMPS - The Open Hardware SLA Printer
-------------------------------------
LAMPS is an open control board and SLA printer design.  

#License
The entire lamps project (PCB, Source Code, Design Files... EVERYTHING) is licensed under the Creative Commons - Attribution Non Commercial Share Alike (3.0) (CC BY-NC-SA 3.0). http://creativecommons.org/licenses/by-nc-sa/3.0/

That means you can use my design, but you are not allowed to profit or sell any part of it.  If you are looking for an exception, contact me and I'll take it under consideration.

#LAMPS Board
LAMPS is the PCB control board that rides on top of an Arduino Mega 2560.  It provides Galvanometer control (Through 12 bit DACs).  It also controls the laser, buttons, Z Stepper Motor (Through Pololu Carrier), End Stops, LEDs, etc...  (It is the Brainz).

Version 1.0 of the LAMPS board has been manufactured and tested... I found a few issues with the board and am currently redesigning and removing a few unnecessary components for 1.1. Release date T.B.D.

#Firmware
The firmware for LAMPS is a fork of Marlin (The best open source RepRap firmware I know of), and can be found here: https://github.com/beardface/Marlin-LAMPS
The firmware is very much an active work-in-progress, and I encourage you to fork, and contribute.

#Parts
All of the parts are available as sketchup (skp) and stl files.

##Printed Parts
* 1x [Laser Mount](https://github.com/beardface/LAMPS/blob/master/parts/lasermount.stl)
* 1x [Mirror Mount](https://github.com/beardface/LAMPS/blob/master/parts/mirrormount.stl)
* 4x [Vibrating Vat Mount](Mount https://github.com/beardface/LAMPS/blob/master/parts/vibrating_vat_mount.stl)
* 1x [Z-Axis Top Mount](https://github.com/beardface/LAMPS/blob/master/parts/z_top_mount.stl)
* 1x [Z-Axis Bottom Mount](https://github.com/beardface/LAMPS/blob/master/parts/z_bottom_mount.stl)
* 1x [Build Platform Mount](https://github.com/beardface/LAMPS/blob/master/parts/platform_mount.stl)
* 1x [Build Stage](https://github.com/beardface/LAMPS/blob/master/parts/build_platform_connector.stl)

##Laser Cut Parts
###Platform
Use 3/16"-1/4" thick acrylic for the platforms.
* 1x [Vat Platform](https://github.com/beardface/LAMPS/blob/master/parts/top_platform.svg)
* 1x [Component Platform](https://github.com/beardface/LAMPS/blob/master/parts/bottom_platform.svg)

###VAT
Use 1/4" Clear (Transparent) Acrylic for the VAT!
* 1x [Vat Back](https://github.com/beardface/LAMPS/blob/master/parts/vat_design/vat_back.svg)
* 1x [Vat Front](https://github.com/beardface/LAMPS/blob/master/parts/vat_design/vat_front.svg)
* 1x [Vat Bottom](https://github.com/beardface/LAMPS/blob/master/parts/vat_design/vat_bottom.svg)
* 1x [Vat Handle](https://github.com/beardface/LAMPS/blob/master/parts/vat_design/vat_handle.svg)
* 2x [Vat Sides](https://github.com/beardface/LAMPS/blob/master/parts/vat_design/vat_side.svg)

##Non-Printed Parts
* 1x NEMA 17 Stepper Motor (Low Profile!)
* 1x LAMPS Electronics Kit (w/Pololu and 2x endstops)
* 1x LAMPS Musimi 2020 Rail Kit and connectors
* 1x 405nm Laser (20mw-150mw) -- Build properties/cure time/etc... vary by laser!
* 1x 3" Square Mirror
* 1x Laser Galvo Set (20kpps) w/power supply
* 1x +/-12V Power Supply (~1-3Amps)
* Screws, Nuts, Wires, Solder, Patience

###LAMPS IS A WORK IN PROGRESS.

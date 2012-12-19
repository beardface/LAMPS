LAMPS - The Open Hardware SLA Printer
-------------------------------------
LAMPS (Laser Arduino Mega Pololu Shield|SLAPrinter)is an open control board and SLA printer design.  The SLA Printer strives to be a low-cost, small footprint (It is only 200mmx350mm!), highly capable SLA Printer. The build platform size is currently 80mmx80mm, but could probably be increased by someone who is motivated to enhance the design.

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
* 4x [Vibrating Vat Mount](https://github.com/beardface/LAMPS/blob/master/parts/vibrating_vat_mount.stl)
* 1x [Z-Axis Top Mount](https://github.com/beardface/LAMPS/blob/master/parts/z_top_mount.stl)
* 1x [Z-Axis Bottom Mount](https://github.com/beardface/LAMPS/blob/master/parts/z_bottom_mount.stl)
* 1x [Build Platform Mount](https://github.com/beardface/LAMPS/blob/master/parts/platform_mount.stl)
* 1x [Build Stage](https://github.com/beardface/LAMPS/blob/master/parts/build_platform_connector.stl)
* 1x Endstop Mount

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
* 2x 8mm Smooth Rod (~260mm)
* 1x 8mm Threaded Rod (~260mm) and 2-M8 nuts
* 2x LM8UU Bearings
* 1x LAMPS Electronics Kit (w/Pololu and 2x endstops)
* 1x LAMPS PCB Build Platform
* 1x LAMPS Musimi 2020 Rail Kit and connectors
  * 4x  350mm 2020 Extrusions w/end tapping holes
  * 11x 160mm 2020 Extrusions
  * 1x  110mm 2020 Extrusion
* 1x LAMPS Enclsoure & Hatch Kit
* 1x 405nm Laser (20mw-150mw) -- Build properties/cure time/etc... vary by laser!
* 1x 3" Square Mirror
* 1x Laser Galvo Set (20kpps) w/power supply
* 1x +/-12V Power Supply (~1-3Amps)
* USB Cable
* Power Cable
* Screws, Nuts, Wires, Solder, Patience

##Optional (But Useful) Non-Printed Parts
* 1xLCD Screen
* 1xSD Card Reader (and corresponding circuit... T.B.D.)
* 1x Power Switch (110-250VAC), lighted
* 1x Power Terminal (Two combine power into single input)
* 1x 3-Prong Power Jack
 
###LAMPS IS A WORK IN PROGRESS.

##Some words of Caution
* Careful with 110-250VAC, it can --bite-- Seriously Harm you if you aren't careful
* Some 405nm Resins can be toxic while curing- take the appropriate measures to ensure you are working in a well ventelated room

~LAMPS design, details, and parts list are provided without any warranty or gaurantee- this is a community project, so lets work together to solve issues that may arise!

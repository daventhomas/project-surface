# Arduino Software #

The Arduino software in this repository has two sections.
  * Arduino Workspace for the ATMega2560, which does the TUIO to serial conversion.
  * Arduino Surface for the ATMega8u2 which does the serial to Touch driver USB conversion and shows as a touch panel device which passes the Windows 8 touch HCK tests.

It can be built via the command line or in [Eclipse](http://playground.arduino.cc/code/eclipse) with the Eclipse project being in Arduino Workspace in the trunk.

You can test the ATMega2560 code using the standard serial debugging, but once you reprogram the Mega 8u2, you loose the ability to use the serial port USB debugging, as the USB port is now a touch driver.

This means you need to have an ISP programmer to program the 8U2 and, once it is programmed, to make any updates to the 8U2 and the 2560.
I started off using an [AVRISP MkII](http://www.atmel.com/tools/AVRISPMKII.aspx), but found if you want to do any serious debugging you really need an [AVR Dragon](http://www.atmel.com/tools/avrdragon.aspx), so I recommend the Dragon, although it still doesn't work very well when trying to debug interrupt routines.

The ATMega8u2 code is based on the [LUFA project](http://www.fourwalledcubicle.com/LUFA.php), so start by reading up about this before making any changes or if you have build issues.

You can also read up about Touch devices on [MSDN](http://msdn.microsoft.com/en-gb/library/windows/hardware/hh852381.aspx) if you need more details on the Touch HID information reported in Descriptors.c and Arduinosurface.c.
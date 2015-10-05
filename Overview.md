# Overview #

Project Surface is based on the work I did for our Innovation Days at work.
<a href='http://www.youtube.com/watch?feature=player_embedded&v=2V5IyHYHS4w' target='_blank'><img src='http://img.youtube.com/vi/2V5IyHYHS4w/0.jpg' width='425' height=344 /></a>

So thanks to [Citrix](http://www.citrix.com) for allowing me to do blue sky research and then open sourcing the details and to my Dad for inspiring me with his various projects over the years.

Hopefully any one following these instructions can build a relatively cheap touch surface and use it with a standard Windows 8 PC with no extra drivers.

![http://project-surface.googlecode.com/svn/wiki/project-surface.png](http://project-surface.googlecode.com/svn/wiki/project-surface.png)

# Details #

To get started you will need to decide on the type of touch surface you want to build. There are various type of table, but the one I chose uses IR edge lit plexiglas, a back surface projection layer, front-surfaced mirror, projector and IR camera using TUIO.

The software is using [CCV](http://ccv.nuigroup.com/) running on a Macbook passing TUIO packets to an [Arduino MegaADK board with ethernet](http://www.arduino.cc/).

The [Arduino software](ArduinoSoftware.md) in this repository is based on the [LUFA project](http://www.fourwalledcubicle.com/LUFA.php) and provides a standard USB touch device to Windows 8, which passes the HCK tests.
This enables a zero driver install on Windows 8, once the CCV software is calibrated.

The project video shows Windows 8 running on a Macbook Pro in a Parallels VM. The Macbook is also running a native build of CCV doing the Vision processing which passes the TUIO packets through ethernet to the Arduino board which converts them to Windows 8 touch device input via USB.

Some pictures of the hardware are shown on the [Hardware page](Hardware.md) along with details of the hardware and the suppliers I used.
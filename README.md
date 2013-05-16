Arduino Library
===============
My Arduino Library consists of a set of libaries/classes I frequently use in my projects.
Over time these library will grow and the single libraries may be enriched with additional funcitonality as required by my own projects.

Library Content
===============

TSwitch
-------
Class to handle hardware switches including debouncing on a configurable pin.
The usage of the internal timer is protected against overrun.

TCounter
--------
Counter class for UPDOWN and CYCLING counting between defined bounderies. When a  boundary is hit, a signal flag is set. 

TTimer
------
Timer class with with milli-second resolution. When the timer expires a configurable function is being called.
The usage of the internal timer is protected against overrun.

Usage
=====
1 Drop the libraries into the Adruino user libraries folder
2 Open the Arduino IDE 
3 Play around with the provided example

Requirements
============
Requires: Arduino IDE 1.0+

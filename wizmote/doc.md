# WIZ Remote // LEDnify 429328

## Hardware

SoC: ESP-WROOM-02D (ESP 8266), with programming header

Pins:
 - IO16: Wakeup // PSU enable?
 - IO14: S9 // Moon Button
 - IO13: Shift register ~PL
 - IO5 : Shift register Data out
 - IO4 : Shift register Clock in

 - IO0: Programming
 - RX : Programming
 - TX : Programming

## Firmware

With a self build adapter reading (and writing) of Firmware is possible. 
The stock firmware is unencrypted and appears to still contain debug symbols (at least the version I dumped).
The remote has ESP-NOW functionality according to the debug symbols the firmware contains.
Further analysis is still pending.

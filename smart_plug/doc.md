# WIZ Plug // LEDnify 429330

## Hardware

SoC: WIZ 8285-Board (ESP8266)

Pins:
 - IO4: LED Red  (Active LOW)
 - IO5: LED Blue (Active LOW)
 - IO12: Relay (Active HIGH)
 - IO13: User Button (pullup, low on press)

## Firmware

With a self build adapter reading (and writing) of Firmware is possible. 
The stock firmware is unencrypted and contains some interesting strings and URLs.
The firmware contains a few certificates, and it appears that they are also used for getting the firmware from WiZs' servers.
Further analysis is still pending.

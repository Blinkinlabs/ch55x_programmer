# CH55x Reset Controller

Get yours here: https://shop-nl.blinkinlabs.com/products/ch55x-reset-controller

The CH55x Reset Controller is a one-touch solution for putting WCH CH554 and CH552 microcontrollers into bootloader mode. The reset controller performs a simple sequence to achieve this:

1.    Disconnects both power and USB data lines from the devive
2.    Connects a 10k resistor from 3.3V to the D+ USB line
3.    Connects the power and USB data lines to the device
4.    After a short delay, disconnects the 10k resistor from the device


Notes:

*    This will only work with USB-powered CH55x devices, if the device has power from a battery or other power source, the CH55x will not reset
*    Connect the computer to the 'DUT IN' micro USB port
*    Connect your WCH CH55x device to the 'DUT OUT' USB A port
*    This board was designed to work with 3.3V powered CH55x devices. It may work with 5V powered devices, but this is untested.
*    The board includes a 'control in' connection for remotely controlling the bootloader sequence, however this is not supported in the software for the device.


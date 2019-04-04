# Replacement motor driver for INGCO mini drills

This is replacement motor driver for [INGCO](http://ingcotools.com) mini drills / die grinders. This project is mainly developed to replace motor speed controller of the *INGCO  MG1502.2* mini drill. 

![PCB of mini drill controller](https://raw.githubusercontent.com/dilshan/mini-drill-driver/master/resources/motor-speed-small.png)

This speed controller is designed based on Microchip [PIC12F629](https://www.microchip.com/wwwproducts/en/PIC12F629) 8-bit CMOS microcontroller.  This MCU is used for zero-crossing detection, determine TRIAC firing times and to handle buttons and switches.

As an original board, the controller supply comes from the mains through a simple RCD circuit. 

The firmware of this controller is design to operate with 4MHz internal-oscillator of the MCU. The current version of this controller is designed to work with 50Hz AC power sources. For 60Hz, *TIMER0* timing value needs to be changed in the firmware source code. 

Compare with the original *MG1502.2* controller board this controller is not equipped with LCD. We remove LCD from this design due to the unavailability of compatibaly LCD modules. Also, we design this controller using commonly available through-hole type components.  

**WARNING:** This controller board is powered by AC mains voltage. Avoid touching the board when power is applied. If possible, use an isolation transformer for the testing.

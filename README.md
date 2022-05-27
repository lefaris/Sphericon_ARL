# Agile Robotics Lab | Sphericon

![Sphericon](https://github.com/lefaris/Sphericon_ARL/blob/main/Figures/DSC01661.JPG)

## Code
### BLE
To run Arduino code using bluetooth low energy connectivity, first install a BLE app such as LightBlue on the app store.  Upload ArdA_Demo.ino to one Arduino Nano 33 BLE, and ArdB_Demo.ino to another Arduino Nano 33 BLE.  Connect a bluetooth device to each Arduino using the LightBlue app.  Once connected, send 0x35 to each Arduino to begin oscillations.

###  No BLE
To run Arduino code without the bluetooth low energy connectivity, upload sphericon_stepper.ino to each Arduino.  As soon as the code is uploaded, the motor assembly will start to swing.  A mechanical switch to enable the start of the code will be added to the PCBs in a future version.

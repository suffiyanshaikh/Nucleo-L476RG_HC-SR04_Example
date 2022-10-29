# <h2 align="left">
<img src="https://readme-typing-svg.herokuapp.com/?lines=Nucleo-L476RG_HC-SR04_+Sensor_Example;&center=false&size=15">
</h2>


**In order to demonstrate how the ultrasonic sensor HS-SR04 can be interfaced with the STM32 Controller, example code is developed utilising the mbed os platform and Nucleo-l476RG board.Refer to the datasheet in the reference for further information about the HS-SR04 sensor.**

**Connections**

|Nucleo Pins |HC-SR04 Pins|
|:-----------|:-------------:|
|5V          | VCC           |
|GND         | GND           |
|PA_6        | Trigger       |
|PA_7        | Echo          |
 

**Code Overview**

The trigger pulses in the following example are generated in regular intervals in accordance with the timeout specified in the code. The object's distance is printed if it exceeds the threshold value.
 
 # Output Snaps
 
 ![image](https://user-images.githubusercontent.com/42150715/198844394-f05da121-1da3-46c2-9af6-9ccfc0bd44db.png)

#
 **References:**
* [https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf).
* [https://os.mbed.com/](https://os.mbed.com/)

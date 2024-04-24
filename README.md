# SmartStreetLight
Here are the resources for a next-generation public lighting system designed to revolutionize urban environments. Dive into our comprehensive documentation and resources to explore the inner workings of this innovative system. Join our community to contribute and illuminate the path to smarter, safer, and more sustainable cities. 

## Here's an explanation of each part of the code: <br>*
*Include Statements:*<br>
* Includes necessary libraries for the project, such as RGBLed for controlling RGB LEDs, DHT for interfacing with DHT temperature and humidity sensors, and thingProperties.h for IoT cloud communication.<br><br>
*Global Variables:*<br>
* Defines pins for various components like LEDs, sensors, and PIR motion sensors.
* Defines constants and variables for time intervals, sensor thresholds, and previous millis for timing functions.<br><br>
*Class Definitions:*<br>
* Defines custom classes for LDR (Light Dependent Resistor) and LED (Light Emitting Diode) to encapsulate functionality related to reading sensor values, controlling LED brightness, and handling fading effects.<br><br>
*Instance Creation:*<br>
* Creates instances of the custom LDR and LED classes, as well as instances for RGB LED control and DHT sensor reading.<br><br>
*Interrupt Service Routine (ISR):*<br>
* Defines an ISR for handling changes in PIR motion sensor state. This ISR updates the 'pirState' variable when motion is detected.<br><br>
*Setup Function:*<br>
* Initializes serial communication, sensors, pins, and IoT cloud connection.
* Sets up interrupt handling for the PIR motion sensor.<br><br>
*Loop Function:*<br>
* Continuously updates the IoT cloud connection and reads temperature and humidity data from the DHT sensor.
* Checks sensor readings and executes appropriate lighting control functions based on the selected mode.
* Updates RGB LED color based on sensor readings and system state.
* Prints sensor values and system status to the serial monitor.<br><br>
*Cloud Variable Change Callbacks:*<br>
* Defines callback functions for handling changes to IoT cloud variables ('mode', 'threshold', and 'iOmessage').
* Executes corresponding actions based on the received values.<br><br>

This code integrates various components to create an automatic lighting system that adjusts lighting based on sensor inputs and communicates with an IoT cloud platform for remote monitoring and control. It demonstrates the use of interrupts, custom classes, and IoT cloud integration to create a versatile and responsive lighting system.<br><br>

### Dashboard of the Smart Street Light:
![image](https://github.com/chinmaykrishnroy/SmartStreetLight/assets/65699140/6c497935-34bc-445d-a07f-a85a47305df8)

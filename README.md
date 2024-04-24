# SmartStreetLight

Welcome to SmartStreetLight, your resource for a next-generation public lighting system designed to revolutionize urban environments. Explore our comprehensive documentation and resources to delve into the inner workings of this innovative system. Join our community to contribute and illuminate the path to smarter, safer, and more sustainable cities.

## Code Explanation:

### Include Statements:
- Includes necessary libraries for the project, such as RGBLed for controlling RGB LEDs, DHT for interfacing with DHT temperature and humidity sensors, and thingProperties.h for IoT cloud communication.

### Global Variables:
- Defines pins for various components like LEDs, sensors, and PIR motion sensors.
- Defines constants and variables for time intervals, sensor thresholds, and previous millis for timing functions.

### Class Definitions:
- Defines custom classes for LDR (Light Dependent Resistor) and LED (Light Emitting Diode) to encapsulate functionality related to reading sensor values, controlling LED brightness, and handling fading effects.

### Instance Creation:
- Creates instances of the custom LDR and LED classes, as well as instances for RGB LED control and DHT sensor reading.

### Interrupt Service Routine (ISR):
- Defines an ISR for handling changes in PIR motion sensor state. This ISR updates the 'pirState' variable when motion is detected.

### Setup Function:
- Initializes serial communication, sensors, pins, and IoT cloud connection.
- Sets up interrupt handling for the PIR motion sensor.

### Loop Function:
- Continuously updates the IoT cloud connection and reads temperature and humidity data from the DHT sensor.
- Checks sensor readings and executes appropriate lighting control functions based on the selected mode.
- Updates RGB LED color based on sensor readings and system state.
- Prints sensor values and system status to the serial monitor.

### Cloud Variable Change Callbacks:
- Defines callback functions for handling changes to IoT cloud variables ('mode', 'threshold', and 'iOmessage').
- Executes corresponding actions based on the received values.

This code integrates various components to create an automatic lighting system that adjusts lighting based on sensor inputs and communicates with an IoT cloud platform for remote monitoring and control. It demonstrates the use of interrupts, custom classes, and IoT cloud integration to create a versatile and responsive lighting system.

## Failure Detection

The automatic lighting system implemented in this project utilizes redundant sensors and sophisticated error detection algorithms to identify failures and isolate the faulty component.

### Features:

- **Redundant Sensors:** Multiple sensors are employed for critical functions such as light sensing (LDRs), motion detection (PIR sensor), and environmental monitoring (DHT temperature and humidity sensor).
- **Error Detection Algorithms:** Custom algorithms analyze readings from redundant sensors and compare them against predefined thresholds or expected ranges.
- **Fault Isolation:** Upon detecting an error, the system isolates the faulty component by analyzing sensor readings and system behavior.

### How It Works:

1. **Redundant Sensors:** The system cross-references readings from multiple sensors to validate data consistency and identify discrepancies.
2. **Error Detection Algorithms:** Algorithms analyze sensor readings and flag error conditions when readings deviate beyond acceptable limits.
3. **Fault Isolation:** By analyzing sensor readings, the system identifies the faulty component or sensor causing the issue.

### Feedback Mechanisms:

Upon detecting an error, the system triggers feedback mechanisms to alert maintenance personnel or take corrective actions. This may include visual indicators, serial monitor messages, or cloud-based notifications.

### Usage:

1. Clone the repository.
2. Upload the code to your Arduino board.
3. Connect the sensors as per the wiring instructions.
4. Monitor system behavior using the serial monitor and observe feedback mechanisms for error detection.

### Contributions:

Contributions to enhance fault detection algorithms, improve error handling, or add new features are welcome! Please open a pull request with your changes.

### Dashboard of the Smart Street Light:
![image](https://github.com/chinmaykrishnroy/SmartStreetLight/assets/65699140/6c497935-34bc-445d-a07f-a85a47305df8)

### Working Prototype on the breadboard:
![smartlight](https://github.com/chinmaykrishnroy/SmartStreetLight/assets/65699140/9be5cd26-c499-46da-bc10-8a98500d6594)

/*
  Sketch generated by the Arduino IoT Cloud Thing "Untitled"
  https://create.arduino.cc/cloud/things/e55c69b8-5e43-43f9-a2c4-e3c6ed138843

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  String iOmessage;
  float dhtHumidity;
  float dhtTemp;
  int mode;
  int threshold;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <RGBLed.h>
#include <DHT.h>
#include <DHT_U.h>


const short led_ = 2;
const short dhtPin = 4;

const short Rgb = 19;
const short rGb = 18;
const short rgB = 5;
const short lamp = 13;
const short ledPin = 33;
const short pir = 34;
const short ldr1 = 39;
const short ldr2 = 36;
//const short dhtPin = 4;

const long interval = 5000;
const long inteval = 4000;
const long intervl = 2000;
unsigned long previousMillis = 0;
unsigned long previousMills = 0;
unsigned long previosMillis = 0;
volatile bool pirState = 0;
bool ledState = 0;
bool _ledState = 0;
bool ledState_ = 0;

int aT = 220;
int bT = 215;
short overH = 95;
short overT = 35;


class LDR {

private:
  short L1, L2;
  int L1val = 0, L2val = 0;

public:
  LDR(short LDR1, short LDR2) {
    Serial.begin(115200);
    this->L1 = LDR1;
    this->L2 = LDR2;
    pinMode(L1, INPUT_PULLUP);
    pinMode(L2, INPUT_PULLUP);
  }

  int smoothRead(int Pin) {
    int i;
    int value = 0;
    int numReadings = 10;

    for (i = 0; i < numReadings; i++) {
      value = value + analogRead(Pin);
      delay(1);
    }
    value = value / numReadings;
    return value;
  }

  int readValueA(int mapping_LowerLim = 0, int mapping_UpperLim = 4095) {
    L1val = smoothRead(L1);
    L1val = map(L1val, 0, 4095, mapping_LowerLim, mapping_UpperLim);
    return L1val;
  }

  int readValueB(int mapping_LowerLim = 0, int mapping_UpperLim = 4095) {
    L2val = smoothRead(L2);
    L2val = map(L2val, 0, 4095, mapping_LowerLim, mapping_UpperLim);
    return L2val;
  }

  void printValue(int mapping_LowerLim = 0, int mapping_UpperLim = 4095) {
    L1val = smoothRead(L1);
    L2val = smoothRead(L2);
    L1val = map(L1val, 0, 4095, mapping_LowerLim, mapping_UpperLim);
    L2val = map(L2val, 0, 4095, mapping_LowerLim, mapping_UpperLim);
    Serial.print("LDR1: ");
    Serial.print(L1val);
    Serial.print("\tLDR2: ");
    Serial.print(L2val);
    Serial.println();
  }

  bool ifError(int threshold = 1000) {
    L1val = smoothRead(L1);
    L2val = smoothRead(L2);
    if (abs(L1val - L2val) > threshold || (L1val == 0 || L2val == 0) || L1val < 500 || L2val < 500) return true;
    return false;
  }

  void printError(int threshold = 1000) {
    L1val = smoothRead(L1);
    L2val = smoothRead(L2);
    if (abs(L1val - L2val) > threshold || (L1val == 0 || L2val == 0) || L1val < 500 || L2val < 500) Serial.println("LDR ERROR!");
    else Serial.println("LDR Working!");
  }

  bool belowThreshold(int threshold) {
    if (!ifError()) {
      if ((readValueA(0, 255) < threshold) && (readValueB(0, 255) < threshold)) return 1;
      return 0;
    }
    return 0;
  }

  bool aboveThreshold(int threshold) {
    if (!ifError()) {
      if ((readValueA(0, 255) >= threshold) && (readValueB(0, 255) >= threshold)) return 1;
      return 0;
    }
    return 0;
  }
};


class LED {
private:
  short ledPin;
public:
  int brightness, toBrightness, fromBrightness;
  bool ledState;
  LED(short ledPin) {
    this->ledPin = ledPin;
    pinMode(this->ledPin, OUTPUT);
    digitalWrite(this->ledPin, 0);
  }

  void on(int brightness = 100) {
    this->brightness = brightness;
    brightness = map(brightness, 0, 100, 0, 255);
    analogWrite(ledPin, brightness);
    if (brightness == 0) ledState = 0;
    else ledState = 1;
  }

  void off() {
    analogWrite(ledPin, 0);
    ledState = 0;
  }

  void fade(short fromBrightness, short toBrightness, int fadeTimeMillis = 1000) {
    this->brightness = brightness;
    this->toBrightness = toBrightness;
    this->fromBrightness = fromBrightness;
    if (toBrightness - fromBrightness > 0) {
      for (short i = fromBrightness; i <= toBrightness; i++) {
        this->on(i);
        delay((int)(fadeTimeMillis / 100));
      }
    } else if (toBrightness - fromBrightness < 0) {
      for (short i = fromBrightness; i >= toBrightness; i--) {
        this->on(i);
        delay((int)(fadeTimeMillis / 100));
      }
    } else this->off();
    if (brightness == 0) ledState = 0;
    else ledState = 1;
  }
};



RGBLed rgbLED(Rgb, rGb, rgB, RGBLed::COMMON_ANODE);
LDR sensors(ldr1, ldr2);
LED light(lamp);
LED led(ledPin);
DHT dht(dhtPin, DHT22);
//TaskHandle_t Task1;


portMUX_TYPE synch = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR pirStateUpdate() {
  portENTER_CRITICAL(&synch);
  pirState = !pirState;
  portEXIT_CRITICAL(&synch);
}



void printTemp(bool unit = 0) {
  Serial.print("Temperature: ");
  Serial.print(dht.readTemperature(unit));
  Serial.println(" C");
}

void printHumidity() {
  Serial.print("Humidity: ");
  Serial.print(dht.readHumidity());
  Serial.println(" %");
}

float readTemp(bool unit = 0) {
  return dht.readTemperature(unit);
}

float readHumidity() {
  return dht.readHumidity();
}

bool isOverHumid(float percentage) {
  if (dht.readHumidity() > percentage) return true;
  return false;
}

bool isOverHot(float temperature, bool unit = 0) {
  if (dht.readTemperature(unit) > temperature) return true;
  return false;
}

void lighting(bool trig, short minBright = 10, short maxBright = 100) {
  if (trig) {
    if (light.toBrightness != maxBright) light.fade(minBright, maxBright);
  } else {
    if (light.toBrightness != minBright) light.fade(maxBright, minBright);
  }
}

void lighting_(bool trig, short minBright = 0, short maxBright = 100) {
  if (trig) {
    if (led.toBrightness != maxBright) led.fade(minBright, maxBright);
  } else {
    if (led.toBrightness != minBright) led.fade(maxBright, minBright);
  }
}

void lightingDigital(bool trig, short lowBright = 0, short highBright = 100) {
  if (trig) {
    if (light.brightness != highBright) light.on(highBright);
  } else {
    if (light.brightness != lowBright) light.on(lowBright);
  }
}

void lightingDigital_(bool trig, short lowBright = 0, short highBright = 100) {
  if (trig) {
    if (led.brightness != highBright) led.on(highBright);
  } else {
    if (led.brightness != lowBright) led.on(lowBright);
  }
}

void lightUp(bool type = 0) {
  unsigned long currentMillis = millis();
  if ((currentMillis - previousMillis >= interval) || pirState) {
    previousMillis = currentMillis;
    if (pirState) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    if (type) lightingDigital(ledState);
    else lighting(ledState);
  }
}

void lightUpPIR(bool type = 0) {
  unsigned long currentMills = millis();
  if ((currentMills - previousMills >= inteval) || pirState) {
    previousMills = currentMills;
    if (pirState) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    if (type) lightingDigital(ledState, 0, 100);
    else lighting(ledState, 0, 100);
  }
}

bool lightUpLDR(bool type = 0) {
  unsigned long crrentMillis = millis();
  if ((crrentMillis - previosMillis >= intervl) || sensors.belowThreshold(bT)) {
    previosMillis = crrentMillis;
    Serial.println();
    if (sensors.belowThreshold(bT)) {
      ledState_ = 1;
    } else if (sensors.aboveThreshold(aT)) {
      ledState_ = 0;
    }
    if (type) lightingDigital_(ledState_, 0, 100);
    else lighting_(ledState_, 0, 100);
    if (ledState_) return true;
    else return false;
  }
}

short lightUpBoth() {
  short out;
  if (sensors.belowThreshold(bT)) {
    led.on(10);
    if (isOverHumid(overH)) lighting(true, 0, 100);
    else lightUp();
    out = 1;
  } else if (sensors.aboveThreshold(aT)) {
    light.off();
    led.off();
    out = 0;
  } else {
    Serial.println("Sensor values are between the threshold values!");
    out = -1;
  }
  return out;
}

void offAll(){
  light.off();
  led.off();
}

void dhtException() {
  led.off();
  light.off();
  rgbLED.setColor(255, 0, 0);
  delay(100);
  printTemp();
  printHumidity();
  rgbLED.off();
  delay(100);
}


void blink(){
  rgbLED.setColor(255,155,100);
  delay(100);
  rgbLED.off();
  delay(100);
  rgbLED.setColor(RGBLed::RED);
  delay(100);
  rgbLED.off();
  delay(100);
  rgbLED.setColor(RGBLed::BLUE);
  delay(100);
  rgbLED.off();
  delay(100);
  rgbLED.setColor(RGBLed::GREEN);
  delay(100);
  rgbLED.off();
  delay(100);
  rgbLED.setColor(RGBLed::MAGENTA);
  delay(100);
  rgbLED.off();
  delay(100);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(led_, OUTPUT);
  pinMode(pir, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pir), pirStateUpdate, CHANGE);
  
  rgbLED.setColor(0,20,0);
  
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
  
  rgbLED.off();
  
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  dhtTemp = dht.readTemperature();
  dhtHumidity = dht.readHumidity();
    if (!isOverHot(35) && (readTemp() > -40 && readTemp() < 140) && (readHumidity() >= 0 && readHumidity() <= 100)) {
    sensors.printValue();
    sensors.printError();
    printTemp();
    printHumidity();
    
    if (mode == 0) offAll();
    else if (mode == 1) Serial.println(lightUpBoth());
    else if (mode == 2) lightUpPIR();
    else if (mode == 3) lightUpLDR();
    else Serial.print("Invalid command!");

    if (mode == 0) rgbLED.setColor(1, 1, 1);
    else if (sensors.ifError()) rgbLED.setColor(5, 0, 0);
    else if (pirState) rgbLED.setColor(0, 5, 5);
    else if (sensors.belowThreshold(bT)) rgbLED.setColor(50, 0, 20);
    else rgbLED.setColor(5, 3, 0);
    if (sensors.belowThreshold(bT)) Serial.println("Below Threshold");
    else if (sensors.aboveThreshold(aT)) Serial.println("Above Threshold");
    else {
      Serial.print("aboveThreshold ");
      Serial.println(sensors.aboveThreshold(aT));
      Serial.print("belowThreshold ");
      Serial.println(sensors.belowThreshold(bT));
    }
    Serial.print("LDR A: ");
    Serial.println(sensors.readValueA(0, 255));
    Serial.print("LDR B: ");
    Serial.println(sensors.readValueB(0, 255));
  } else {
    dhtException();
  }
  threshold = sensors.readValueA(0,255);
}

/*
  Since Mode is READ_WRITE variable, onModeChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onModeChange()  {
  if (mode) digitalWrite(led_, 1);
  else digitalWrite(led_, 0);
  light.off();
  led.off();
}

/*
  Since Threshold is READ_WRITE variable, onThresholdChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onThresholdChange()  {
  // Add your code here to act upon Threshold change
}

/*
  Since IOmessage is READ_WRITE variable, onIOmessageChange() is
  executed every time a new value is received from IoT Cloud.
*/

void onIOmessageChange()  {
  String theMessage = iOmessage, finalMessage = iOmessage;
  theMessage.toUpperCase();
  if (theMessage=="HELLO" || theMessage=="HI") iOmessage="Hello there!";
  else if (theMessage=="CLEAR") iOmessage="\x1b";
  else iOmessage = theMessage;
}
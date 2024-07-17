# LGUF_IoT
Code + documentation for Living Green Urban Farms IoT agricultural automation. There are three versions of this platform. 

Version A) Collection, storage and transmission of data from all sensors.

Version B) Collection, storage and transmission of data from all sensors with calibration logic for all soil moisture sensors every 2 seconds.

Version C) Collection, storage and transmission of data from all sensors with calibration logic for all soil moisture sensors every 5 minutes.

## Wiring Schema:
### Soil Moisture Sensors (x6):  
VCC to 3.3V  
GND to GND  
Analog Output to:  
Sensor 1: GPIO 34  
Sensor 2: GPIO 35  
Sensor 3: GPIO 32  
Sensor 4: GPIO 33  
Sensor 5: GPIO 25  
Control/Calibration Sensor: GPIO 26    

### DHT22 Sensor (Ambient Temperature + Humidity):  
VCC to 3.3V  
GND to GND  
Data to GPIO 2 (add a pull-up resistor, if necessary, usually internal pull-up is sufficient for DHT22 on ESP32)    

### DS18B20 Sensor (Water/Nutrient Solution Temperature):  
VCC to 3.3V  
GND to GND  
Data to GPIO 4  
4.7kΩ resistor between Data and VCC (3.3V)    

### TDS Sensor:  
VCC to 3.3V  
GND to GND  
Analog Output to GPIO 36    

### CO2 Sensor:  
VCC to 3.3V  
GND to GND  
Analog Output to GPIO 39    

### Optional Capacitors for Power Stability:  
0.1µF capacitor close to the power pins (3.3V and GND) of the ESP-WROOM-32  
10µF capacitor close to the power pins (3.3V and GND) of the ESP-WROOM-32    

### Notes:  
Pull-up Resistor for DS18B20: The DS18B20 sensor requires a pull-up resistor to function correctly. This resistor ensures that the data line is pulled high when no device is pulling it low, which is necessary for reliable communication.  
Decoupling Capacitors: These capacitors help filter out noise and stabilize the power supply, ensuring the ESP-WROOM-32 and sensors receive a clean and stable voltage.  
Power Supply: Ensure that your power supply can handle the total current draw of the ESP-WROOM-32 and all connected sensors. Using an external power supply might be necessary if you experience instability.  
Adjust the pin numbers and the number of soil moisture sensors as per your setup. Not all ESP32 boards have the same layout and/or pcb naming methodologies.  
Calibrate the sensors as needed based on the specific ranges and characteristics of your sensors.  
Add error handling and any additional processing based on your requirements.  
This is baseline code specifically for the ESP-WROOM-32 that reads data from multiple sensors. There may be variations required in both the wiring and code implementation for other variants of the ESP32.    

This covers:  
Up to 6 capacitive soil moisture sensors (analog inputs)  
1 humidity + ambient temperature sensor (DHT22)  
1 TDS sensor (analog input)  
1 water temperature sensor (DS18B20)  
1 CO2 sensor (analog input)    

## REQUIRED Libraries:  
You'll need to install the following libraries:  
DHT for the DHT22 sensor  
OneWire and DallasTemperature for the DS18B20 sensor    
You can install these libraries via the Arduino IDE Library Manager.

### Additional Notes: TBD

#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Pin definitions
#define DHTPIN 2              // Pin for DHT22
#define DHTTYPE DHT22         // DHT 22 (AM2302)
#define ONE_WIRE_BUS 4        // Pin for DS18B20

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Initialize OneWire and DallasTemperature libraries for DS18B20
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Soil moisture sensor pins
const int soilMoisturePins[6] = {34, 35, 32, 33, 25, 26}; // Added a control sensor at the end

// TDS sensor pin
const int tdsPin = 36;

// CO2 sensor pin
const int co2Pin = 39;

// Variables to hold sensor readings
float soilMoisture[6];
float humidity;
float temperature;
float waterTemp;
float tds;
float co2;

float controlValue = 0;
float calibrationFactor[5] = {1, 1, 1, 1, 1}; // Calibration factors for the other sensors

void setup() {
  Serial.begin(115200);

  // Start DHT sensor
  dht.begin();

  // Start DS18B20 sensor
  sensors.begin();

  // Initialize soil moisture sensor pins
  for (int i = 0; i < 6; i++) {
    pinMode(soilMoisturePins[i], INPUT);
  }

  // Initialize TDS and CO2 sensor pins
  pinMode(tdsPin, INPUT);
  pinMode(co2Pin, INPUT);
}

void loop() {
  // Read the control soil moisture sensor
  controlValue = analogRead(soilMoisturePins[5]);
  Serial.print("Control Soil Moisture Sensor: ");
  Serial.println(controlValue);

  // Read soil moisture sensors and apply calibration
  for (int i = 0; i < 5; i++) {
    soilMoisture[i] = analogRead(soilMoisturePins[i]) * calibrationFactor[i];
    Serial.print("Soil Moisture Sensor ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(soilMoisture[i]);
  }

  // Calibrate the soil moisture sensors
  calibrateSoilMoistureSensors();

  // Read DHT22 sensor
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Read DS18B20 sensor
  sensors.requestTemperatures();
  waterTemp = sensors.getTempCByIndex(0);
  Serial.print("Water Temperature: ");
  Serial.print(waterTemp);
  Serial.println(" *C");

  // Read TDS sensor
  tds = analogRead(tdsPin);
  Serial.print("TDS: ");
  Serial.println(tds);

  // Read CO2 sensor
  co2 = analogRead(co2Pin);
  Serial.print("CO2: ");
  Serial.println(co2);

  delay(2000);  // Wait for 2 seconds before the next loop
}

void calibrateSoilMoistureSensors() {
  for (int i = 0; i < 5; i++) {
    float currentValue = analogRead(soilMoisturePins[i]);
    if (controlValue != 0) {
      calibrationFactor[i] = controlValue / currentValue;
    }
  }
}

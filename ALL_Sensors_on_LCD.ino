#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>






// Define pin connections
#define MICROPHONE_PIN 33 // Analog pin where the microphone module is connected  //Microphone


// Define pin connections
#define SENSOR_135 27 // Analog pin where the sensor is connected  //Mq135

// Function to calculate ppm concentration from sensor reading
float calculatePPM(int sensorValue) {
  // Conversion factor for ppm calculation (this is a simple approximation)
  float ppm = (sensorValue / 1024.0) * 1000; // You may need to adjust this based on your sensor's characteristics
  return ppm; 
}

// Define pin connections
#define SENSOR_7 25 // Analog pin where the sensor is connected   //Mq7

#include<DHT.h>
#define SENSOR_PIN 26  //DHT11
DHT sensor(SENSOR_PIN , DHT11);
float hum, temp;



LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display


void setup() {
  // put your setup code here, to run once:
  lcd.init();                       // Initialize the LCD
  lcd.backlight();                  // Turn on the backlight
  lcd.clear();                      // Clear the LCD screen

  Serial.begin(9600);
  sensor.begin();
  pinMode(SENSOR_PIN, INPUT);
  pinMode(12, INPUT);

  // Debug console
  Serial.begin(9600);
  //pinMode(D2, OUTPUT);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:


 





  hum=sensor.readHumidity();
  temp=sensor.readTemperature();
  //MQ7
  
  // Read analog value from sensor
  int sensorValue = analogRead(SENSOR_7);

  // Convert analog value to voltage
  float voltage = sensorValue * (5.0 / 4096.0);

  //MQ135
  // Read analog value from sensor
  int sensorValue135 = analogRead(SENSOR_135);
  
  float ppmco2 = calculatePPM(sensorValue135);
  // Calculate ppm concentration
  float ppm = calculatePPM(sensorValue); //PPM value of CO function to calculate it

  //Microphone
  // Read analog value from microphone
  int micValue = analogRead(MICROPHONE_PIN);
  float voltage_mic = micValue * (5.0 / 1023.0); // Convert analog value to voltage (assuming 5V Arduino)
  float dB = 20 * log10(voltage); // Convert voltage to decibels (dB)

  lcd.setCursor(0, 0); // Set the cursor to the first column and first row
  //DHT 11
  lcd.print("  Humidity"); 
  lcd.print(" Temp");
 
                
  

  lcd.setCursor(0,1);
  lcd.print(hum);
  Serial.print(hum);
  Serial.print(temp);
  lcd.print("  ");
  lcd.print(temp);
  delay(2000);

  lcd.init();                       // Initialize the LCD
  lcd.backlight();                  // Turn on the backlight
  lcd.clear(); 
  lcd.setCursor(0, 0); // Set the cursor to the first column and first row
  lcd.print("Carbon Monooxide");
  Serial.print("Carbon Monooxide");
  lcd.setCursor(0,1);
  lcd.print(sensorValue);
  delay(2000);
  
  lcd.init();                       // Initialize the LCD
  lcd.backlight();                  // Turn on the backlight
  lcd.clear(); 
  lcd.setCursor(0, 0); // Set the cursor to the first column and first row
  lcd.print("Carbon Dioxide");
  lcd.setCursor(0,1);
  //lcd.print(sensorValue135);
  lcd.print(ppmco2);
  lcd.print(" ");
  lcd.print(ppm);
  delay(2000);

  //Microphone
  lcd.init();                       // Initialize the LCD
  lcd.backlight();                  // Turn on the backlight
  lcd.clear(); 
  lcd.setCursor(0, 0); // Set the cursor to the first column and first row
  lcd.print("Sound");
  lcd.setCursor(0,1);
  lcd.print(dB);
  delay(2000);

  
  // LDR

  lcd.init();                       // Initialize the LCD
  lcd.backlight();                  // Turn on the backlight
  lcd.clear();
  int data = analogRead(12);
  lcd.setCursor(0, 0); // Set the cursor to the first column and first row


  if(data<400){
    lcd.print("Dim Light");
  }
  else if(data>1000){
    lcd.print("Good Light");
  }
  else{
    lcd.print("Morderate Light");
  }
  delay(2000);


  lcd.init();                       // Initialize the LCD
  lcd.backlight();                  // Turn on the backlight
  lcd.clear();
  delay(3000);
}

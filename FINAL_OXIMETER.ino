#define BLYNK_TEMPLATE_ID "TMPLcYhz2NBA"
#define BLYNK_DEVICE_NAME "WIFI OXIMETER"
#define BLYNK_AUTH_TOKEN "7SQu5AJ1b2YIsFOM0vyIV2FAYpHAN68q"

//Wire.h will allow us to communicate through the I2C protocol.
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "MAX30100_PulseOximeter.h"
#include <SimpleTimer.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 

char auth[] = "7SQu5AJ1b2YIsFOM0vyIV2FAYpHAN68q";
 
 
/* WiFi credentials */
char ssid[] = "Nidhee";
char pass[] = "nidhee1243";
 
#define REPORTING_PERIOD_MS     1300        // is defined to delay the measurements
SimpleTimer timer;
 
PulseOximeter pox;                          // object is created 
uint32_t tsLastReport = 0;                 // is created to store the time at which the last beat occurred.
 
void onBeatDetected()                      //a callback routine is defined which is executed when a pulse is detected
{
     Serial.println("Beat!");
}
 
// for the OLED display
 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
 
//Next, we will initialize the display by creating an object of Adafruit_SSD1306 and specifying the width, height, I2C instance (&Wire), and -1 as parameters inside it.’ -1′ specifies that the OLED display which we are using does not have a RESET pin. 
//If you are using the RESET pin then specify the GPIO through which you are connecting it with your development board.
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void setup()
{
    Serial.begin(115200);
    Blynk.begin(auth, ssid, pass);
    // initialize with the I2C addr 0x3C
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    Serial.print("Initializing pulse oximeter..");
  
 
    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip


    //function call makes sure that we can communicate with the sensor. begin() function returns 1 on success (or 0 if it fails) 
    //It also configures the MAX30100 to begin collecting data
    
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
        digitalWrite(1,HIGH);
    }

    //function sets the current through the IR LED. The following line sets the current of 24mA through the IR LED.
    //set the LED current to a lower value than 50mA
     pox.setIRLedCurrent(MAX30100_LED_CURR_24MA);
 
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
 
   timer.setInterval(3000L, getSendData);

 //we will clear the buffer by using clearDisplay() on the Adafruit_SSD1306 object.
     display.clearDisplay();
     display.setTextColor(WHITE);
}
 
void loop()
{
 
  timer.run(); // Initiates SimpleTimer
  Blynk.run();
// Make sure to call update as fast as possible
//In the main loop, the biometric data is collected from the MAX30100 sensor with the update() function. It actually pulls data in from sensor FIFO.
pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
 
 
  // to android cell phone application
        Serial.print("BPM: ");
        Serial.print(pox.getHeartRate());
        //blue.println("\n");
        
        Serial.print("SpO2: ");
        Serial.print(pox.getSpO2());
        Serial.print("%");
        Serial.println("\n");
 
Blynk.virtualWrite(V7,pox.getHeartRate() );
Blynk.virtualWrite(V8,pox.getSpO2());
 
 //For this we use millis() instead of delay(). Since delay() pauses the entire code, we cannot get the updated measurement.
        tsLastReport = millis();
        
    }
 
 
}
 
void getSendData()
{
  
        
// Oled display
  display.clearDisplay();
  // display R G B Values
  display.setTextSize(2);
  display.setCursor(0,0); // column row
  display.print("BPM:");
 
  display.setTextSize(2);
  display.setCursor(55, 0);
  display.print(pox.getHeartRate());
 
    display.setTextSize(2);
  display.setCursor(0,50);
  display.print("SpO2:");
 
  display.setTextSize(2);
  display.setCursor(60, 50);
  display.print(pox.getSpO2());
   display.setCursor(95, 50);
  display.print("%");
 display.display(); 
}

//Real Time Clock Module libraries
#include <Wire.h>
#include "RTClib.h"

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

RTC_PCF8523 rtc;
  
//Adafruit Neopixel library to control the LED boards
#include <Adafruit_NeoPixel.h>
  
//Number of LEDs
#define NUM_LEDS 8
  
//Define the clock and data lines
 #define LED_PIN 6
#define CLOCK_PIN 13

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 255 // Set BRIGHTNESS to about 1/5 (max = 255)

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRBW + NEO_KHZ800);
  
  //This is where you decide when you want the "sunrise" to begin (5:18 pm). Currently it's set to end at 5:30 am. So you better wake up!
  //The delay(18000); in the "sunriseAnimation();" functions will equate for each function to be 3 minutes long with a total of 10 steps for each function
  //18000 = 18 seconds x 10 = 180 seconds = 3 minutes
  int startHour = 6;
  int startMin = 20;
  int startMin2 = 23;
  int startMin3 = 24;
  int startMin4 = 27;


  //Initialize the starting RGB values for the two 9-led boards
  int r1 = 29;  
  int g1 = 52; 
  int b1 = 125;
  
  void setup() { 

    if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (! rtc.initialized() || rtc.lostPower()) {
    Serial.println("RTC is NOT initialized, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    //
    // Note: allow 2 seconds after inserting battery or applying external power
    // without battery before calling adjust(). This gives the PCF8523's
    // crystal oscillator time to stabilize. If you call adjust() very quickly
    // after the RTC is powered, lostPower() may still return true.
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  // When the RTC was stopped and stays connected to the battery, it has
  // to be restarted by clearing the STOP bit. Let's do this to ensure
  // the RTC is running.
  rtc.start();
  

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
  
  // Use the serial monitor to view time/date output
  Serial.begin(9600);
  
  // Call rtc.begin() to initialize the real-time clock module library
  rtc.begin(); 
  }
  
  void loop() {
  
    static int8_t lastSecond = -1;
    //get new data from the RTC
    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  

//START OF CALLING ANIMATIONS FROM RTC
  
//  the following if statements will be how you call the functions that will change the colors
      if (now.hour() == startHour && now.minute() == startMin) {
        sunriseAnimation(); //this is how to call the animation function. In order for something to happen during the run of the program, it must be called in loop.
      }
      else if (now.hour() == startHour && now.minute() == startMin2) {
        sunriseAnimation2(); 
      }
      else if (now.hour() == startHour && now.minute() == startMin3) {
        sunriseAnimation3();
      }
      else if (now.hour() == startHour && now.minute() == startMin4) {
        sunriseAnimation4(); 
      }
      else { //this is how you "shut off" the LEDs for anytime outside of the sunrise alarm times previously designated 
            for (int i = 0; i < 8; i++) {
      strip.setPixelColor(i, 0, 0, 0);   
      strip.show();
            }
      }
  delay(10000);
    //following lines are from example code to print time to Serial Moniter
    //THis can help with debugging so adding it in here.
    if (now.second() != lastSecond) // If the second has changed
    {
      printTime(); // Print the new time
  
      lastSecond = now.second(); // Update lastSecond value
    }
  
    
  }


  
//This is the first animation cycle. It will last 3 minutes total and incrementally change the colors for 10 steps
void sunriseAnimation() {
  
    for( int i = 0; i < 10; i++ ) {
        //equations for the 2 9-led boards
        r1 = r1 + 22;  // bringing up the red value by 22 for 10 steps to end up at desired color for next animation cycle
        g1 = g1 + 3;    // bringing up the green value by 3 for 10 steps to end up at desired color for next animation cycle
        b1 = b1 - 10;  // bringing down the blue value by 10 for 10 steps to end up at desired color for next animation cycle

       
        // Sets the color for the two side panels of 9 leds
        for(int x = 0; x < 8; x++){
            strip.setPixelColor(x, r1, g1, b1);        
        }strip.show();
        
       
        
        //18 second delay between color change. Remember you're waking up slowly here!
        delay(18000);

        //Can be used for debugging. Will show the colors values changing with each step to ensure they are meeting desired effect
//        Serial.println(rtc.minute());
//        Serial.print("red: ");
//        Serial.println(r1);
//         Serial.print("green: ");
//        Serial.println(g1);
//         Serial.print("blue: ");
//        Serial.println(b1);
  
    } //second for loop
}

//second cycle. A little more brightness and moving colors more toward daylight. Works just like the previous animation
void sunriseAnimation2() {
    //increment brightness for second cycle

    r1 = 249;  
    g1 = 82; 
    b1 = 25;

    for( int i = 0; i < 10; i++ ) {
        r1 = r1 + 0;  
        g1 = g1 + 9;  
        b1 = b1 + 0;  
  
        for(int x = 0; x < 8; x++){
            strip.setPixelColor(x, r1, g1, b1);   
            
        }strip.show();

        delay(18000);

    } //second for loop
}

void sunriseAnimation3() {

    r1 = 249;  
    g1 = 172; 
    b1 = 25;

    for( int i = 0; i < 10; i++ ) {
        r1 = r1 + 0;  // Full Redness
        g1 = g1 + 6;    // Step up to yellow by adding green
        b1 = b1 + 15;  // Blue starts at full and goes down to zero 
  
        // Now loop though each of the LEDs and set each one to the current color
        for(int x = 0; x < 8; x++){
            strip.setPixelColor(x, r1, g1, b1);   
            
        }strip.show();
        delay(18000);
  
    } //second for loop
  
}

void sunriseAnimation4() {

    r1 = 249;  
    g1 = 232; 
    b1 = 175;
  
    for( int i = 0; i < 10; i++ ) {
        r1 = r1 + 0;  // Full Redness
        g1 = g1 + 2;    // Step up to yellow by adding green
        b1 = b1 + 8;  // Blue starts at full and goes down to zero 
  
        // Now loop though each of the LEDs and set each one to the current color
        for(int x = 0; x < 8; x++){
            strip.setPixelColor(x, r1, g1, b1);   
            
        }strip.show();

        delay(18000);
  
    } //second for loop
}


//function from the RTC example code to print time in your serial moniter
//Can help with debugging
void printTime()
{
  
//  Serial.print(String(rtc.hour()) + ":"); // Print hour
//  if (rtc.minute() < 10)
//    Serial.print('0'); // Print leading '0' for minute
//  Serial.print(String(rtc.minute()) + ":"); // Print minute
//  if (rtc.second() < 10)
//    Serial.print('0'); // Print leading '0' for second
//  Serial.print(String(rtc.second())); // Print second
//
//  if (rtc.is12Hour()) // If we're in 12-hour mode
//  {
//    // Use rtc.pm() to read the AM/PM state of the hour
//    if (rtc.pm()) Serial.print(" PM"); // Returns true if PM
//    else Serial.print(" AM");
//  }
//
//  Serial.print(" | ");
//
//  // Few options for printing the day, pick one:
//  Serial.print(rtc.dayStr()); // Print day string
//  //Serial.print(rtc.dayC()); // Print day character
//  //Serial.print(rtc.day()); // Print day integer (1-7, Sun-Sat)
//  Serial.print(" - ");
//#ifdef PRINT_USA_DATE
//  Serial.print(String(rtc.month()) + "/" +   // Print month
//               String(rtc.date()) + "/");  // Print date
//#else
//  Serial.print(String(rtc.date()) + "/" +    // (or) print date
//               String(rtc.month()) + "/"); // Print month
//#endif
//  Serial.println(String(rtc.year()));        // Print year
}

/*
  ---------------------------------------------------------
  Project         : Ultrasonic Distance Indicator
  Youtube Channel : @AmithLabs
  Author          : Amith Wijekoon
  ---------------------------------------------------------

  FINAL WORKING VERSION

  Features:
  - Live distance measurement using HC-SR04
  - OLED live distance display in mm
  - WS2812B RGB LED distance indicator
  - Green / Yellow / Red warning zones
  - Smooth 24 LED bar indication
  - 390mm measuring range

  Hardware Used:
  - Arduino UNO
  - HC-SR04 Ultrasonic Sensor
  - WS2812B 5V LED Strip
  - 0.91" OLED Display (I2C)

  LED Logic:
  - 260mm ~ 390mm  = Green
  - 130mm ~ 260mm  = Yellow
  - 0mm   ~ 130mm  = Red

  LED Resolution:
  - 24 LEDs across 390mm
  - 1 LED = 16.25mm

  OLED I2C Pins:
  SDA = A4
  SCL = A5

  Ultrasonic Sensor Pins:
  TRIG = D9
  ECHO = D10

  LED Strip Pin:
  DIN = D6

  Important:
  - Use external 5V supply for LED strip
  - Connect Arduino GND and LED power GND together
  - Recommended:
      * 330 Ohm resistor on DATA line
      * 1000uF capacitor across 5V and GND

  ---------------------------------------------------------
*/

#include <FastLED.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// =========================================================
// LED STRIP SETTINGS
// =========================================================

// LED data pin connected to WS2812B DIN
#define LED_PIN         6

// Total number of LEDs in strip
#define NUM_LEDS        24

// Create LED array
CRGB leds[NUM_LEDS];


// =========================================================
// ULTRASONIC SENSOR SETTINGS
// =========================================================

// HC-SR04 Trigger Pin
#define TRIG_PIN        9

// HC-SR04 Echo Pin
#define ECHO_PIN        10


// =========================================================
// OLED DISPLAY SETTINGS
// =========================================================

// OLED display width
#define SCREEN_WIDTH    128

// OLED display height
#define SCREEN_HEIGHT   32

// Create OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


// =========================================================
// VARIABLES
// =========================================================

// Variable to store measured distance in millimeters
float distanceMM = 0;


// =========================================================
// SETUP FUNCTION
// Runs only once when Arduino powers ON
// =========================================================

void setup() {

  // -------------------------------------------------------
  // Configure Ultrasonic Sensor Pins
  // -------------------------------------------------------

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);


  // -------------------------------------------------------
  // Initialize WS2812B LED Strip
  // -------------------------------------------------------
  // LED Type  : WS2812
  // Data Pin  : D6
  // Color Type: GRB
  // -------------------------------------------------------

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);


  // -------------------------------------------------------
  // Initialize OLED Display
  // -------------------------------------------------------

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Clear OLED screen
  display.clearDisplay();

  // Update display
  display.display();


  // -------------------------------------------------------
  // Turn OFF all LEDs at startup
  // -------------------------------------------------------

  FastLED.clear();
  FastLED.show();

}


// =========================================================
// MAIN LOOP FUNCTION
// Runs continuously forever
// =========================================================

void loop() {

  // =======================================================
  // STEP 1 : READ DISTANCE FROM HC-SR04 SENSOR
  // =======================================================

  // Send LOW pulse before trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send 10us HIGH pulse to trigger sensor
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  // Stop trigger pulse
  digitalWrite(TRIG_PIN, LOW);

  // Read echo pulse duration
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Convert time into distance (millimeters)
  //
  // Sound speed = 0.343 mm/us
  // Divide by 2 because signal travels forward and back
  //
  distanceMM = duration * 0.343 / 2;


  // =======================================================
  // STEP 2 : DISPLAY DISTANCE ON OLED
  // =======================================================

  // Clear OLED buffer
  display.clearDisplay();

  // Set text size
  display.setTextSize(2);

  // Set text color
  display.setTextColor(WHITE);

  // Set text position
  display.setCursor(20, 10);

  // Print measured distance
  display.print(distanceMM, 0);

  // Print unit
  display.print("mm");

  // Update OLED display
  display.display();


  // =======================================================
  // STEP 3 : CONTROL LED STRIP
  // =======================================================

  // Turn OFF all LEDs first
  FastLED.clear();


  // -------------------------------------------------------
  // Only operate LEDs within 390mm range
  // -------------------------------------------------------

  if(distanceMM <= 390) {

    // -----------------------------------------------------
    // LED Calculation
    // -----------------------------------------------------
    //
    // 390mm / 24 LEDs = 16.25mm per LED
    //
    // Example:
    // 162mm = around 10 LEDs
    //
    // constrain() limits value between 0 and 24
    // -----------------------------------------------------

    int ledCount = constrain(distanceMM / 16.25, 0, 24);


    // Variable to store selected LED color
    CRGB color;


    // =====================================================
    // DISTANCE COLOR ZONES
    // =====================================================

    // -----------------------------------------------------
    // GREEN ZONE
    // 260mm ~ 390mm
    // -----------------------------------------------------

    if(distanceMM > 260) {

      color = CRGB(0, 255, 0);

    }

    // -----------------------------------------------------
    // YELLOW ZONE
    // 130mm ~ 260mm
    // -----------------------------------------------------

    else if(distanceMM > 130) {

      color = CRGB(255, 255, 0);

    }

    // -----------------------------------------------------
    // RED ZONE
    // 0mm ~ 130mm
    // -----------------------------------------------------

    else {

      color = CRGB(255, 0, 0);

    }


    // =====================================================
    // TURN ON REQUIRED LEDs
    // =====================================================

    // Turn ON LEDs from LED 0 up to ledCount
    for(int i = 0; i < ledCount; i++) {

      leds[i] = color;

    }

  }


  // =======================================================
  // STEP 4 : UPDATE LED STRIP
  // =======================================================

  FastLED.show();


  // Small delay for stable operation
  delay(50);

}
/*
 * v0.2  - Sine-cosine closed curve test
 * v0.1  - I switched to the 'Earle F. Philhower' board version. I2C pins GP4 GP5
 * v0.01 - Simple sine curve, amplitude set with potentiometer
 */

float version = 0.2;

#define LED 25

#define SETPOINT_PIN A0
float valuePoti;
float Setpoint;

float frommin = -1.0;
float frommax = 1.0;
float incr = 1.0 / 20.0;

// ------------------ I2C Oled ------------------
// ------------------ I2C Oled ------------------
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// ------------------ VOID LIST ------------------
float mapfloat();

// ------------------ SETUP ------------------
// ------------------ SETUP ------------------
void setup() {
  Serial.begin(115200);

  // ------------------ I2C Oled ------------------
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { // Address 0x3D or 0x3C for 128x64
    Serial.println(F("-- SSD1306 allocation failed --"));
    for (;;);
  }

  // ------------------ Potentiometer ------------------  
  pinMode(LED, OUTPUT);
  pinMode(SETPOINT_PIN, INPUT);

  // ------------------ INITIAL DISPLAY  ------------------
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(44, 3);
  display.println("PICO");
  display.setCursor(44, 20);
  display.println("Sine");
  display.setCursor(44, 37);
  display.println("Test");
  display.setTextSize(1);
  display.setCursor(54, 55);
  display.println("v" + String(version));
  display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
  display.display();
  delay(1000);
  
}

// ------------------ LOOP ------------------
// ------------------ LOOP ------------------
void loop() {

  display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
  float a = 0.0;
  int countC = 0;
  
  //------------- Read Poti ------------------
  int valuePot = analogRead(SETPOINT_PIN);
  float setRot = mapfloat(float(valuePot), 1.0, 4095.0, 0.01, 4.0);
  float setRott = exp(setRot);

  float tomin = 1.0;
  float tomax = 63.0;

  for (int i = 0; i <= 128; i++) {
    float sina = float(sin(a));
    float cosa = float(cos(a));
    float X = cosa - sina / setRott;
    float Y = cosa * sina;
    
    float mapX = mapfloat(X, frommin, frommax, tomin, tomax);
    float mapY = mapfloat(Y, frommin, frommax, tomin, tomax);
    
    display.drawPixel(int(mapX)+32, int(mapY), SSD1306_WHITE);

    a = a + incr;
  }


  display.display();
  display.clearDisplay();

}
// ------------------ END LOOP ------------------
// ------------------ END LOOP ------------------

// ------------------ VOIDS ------------------
// ------------------ VOIDS ------------------
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

/*
 * v0.1  - I switched to the 'Earle F. Philhower' board version. I2C pins GP4 GP5
 * v0.01 - Simple sine curve, amplitude set with potentiometer
 */


float version = 0.1;

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
void drawBorder();
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
  delay(2000);
  
}

// ------------------ LOOP ------------------
// ------------------ LOOP ------------------
void loop() {

  drawBorder();
  float a = 0.0;
  int countC = 0;
  
  //------------- Read Poti ------------------
  valuePoti = float(analogRead(SETPOINT_PIN));
  Serial.println(valuePoti);
  Setpoint = mapfloat(valuePoti, 0.0, 4096.0, 2.0, 63.0);
  int valuePot = analogRead(SETPOINT_PIN);
  int setLed = map(valuePot, 30, 4096, 0, 255);
  //Serial.println(Setpoint);

  float Mod = 64.0 - Setpoint;
  float tomin = 1.0 + Mod;
  float tomax = 63.0 - Mod;

  for (int i = 0; i <= 128; i++) {
    float sina = float(sin(a));
    float mapY = mapfloat(sina, frommin, frommax, tomin, tomax);
    display.drawPixel(i, int(mapY), SSD1306_WHITE);
    a = a + incr;
    if(countC == 32){
      display.drawCircle(i, 32, 2, SSD1306_WHITE);
      countC = 0;
    }
    countC += 1;
  }
  display.setTextSize(1);
  display.setTextColor(WHITE);
  int texty ;
  if(tomin < 30){
    texty = 54;
  }
  else{
    texty = 2;
  }
  display.setCursor(100, texty);
  display.print("sine");
  display.display();
  display.clearDisplay();
  analogWrite(LED, setLed);

}
// ------------------ END LOOP ------------------
// ------------------ END LOOP ------------------

// ------------------ VOIDS ------------------
// ------------------ VOIDS ------------------
void drawBorder() {
  display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
  display.drawLine(0,32,128,32,SSD1306_WHITE);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

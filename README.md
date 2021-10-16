## Pico_sine


- How to draw sine curve.

- I made two versions. Sine curve test and sine-cosine closed curve test.

### Note

Now I changed to [Earle F. Philhower](https://github.com/earlephilhower/arduino-pico) board version.

Add to Arduino IDE:
- File
	- Preferences
		- Additional Boards Manager URLs:
		- <https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json>
        - Then go to ->
            - Tools
                - Board manager... 
                - raspberry pi pico (Earle F. Philhower)

### Used parts:
- Raspberry Pi Pico
- SSD1306 I2C 0,96" Oled Display
- Potentiometer 

<p align="center">
    <img src="https://github.com/zsoltibaba37/Pico_sine/blob/main/RASP_PI_PICO_01.png?raw=true" alt="pico" width="300" />
</p>

<p align="center">
<img src="https://github.com/zsoltibaba37/Pico_sine/blob/main/SSD1306.jpg?raw=true" alt="oled" width="300"/>
</p>

<p align="center">
<img src="https://github.com/zsoltibaba37/Pico_sine/blob/main/Grove-Rotary_Angle_Sensor.jpg?raw=true" alt="rotary" width="300"/>
</p>
 

### Included libraries
```
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
```

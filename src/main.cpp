#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_SSD1306.h>
#include <SCoop.h>
#include <SPI.h>
#include <Wire.h>
#include <math.h>

#define TFT_CS 10
#define TFT_DC 7
#define TFT_RST 8

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 oled = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

int status[] = {0, 0, 0, 0, 0, 0, 0};
char data[2];

void oled_show(){
    oled.clearDisplay();
    for(int i=0; i<7; i++){
        if (status[i] == 1){
            oled.fillRect(i*15, 0, 10, 32, SSD1306_WHITE);
        }
    }
    oled.display();
}

void init_screen() {
    for(int & statu : status){
        statu = 1;
    }
    oled_show();
}

void random_show(){
    randomSeed(analogRead(1));
    for(int & statu : status){
        statu = int(random(2));
    }
    oled_show();
}

void addText(char *text, int size, int length, uint16_t color){
    int y = display.getCursorY();
    if (size == 2 && length > 20){
        int lines = ceil((double)length / 20);
        Serial.println("lines: " + String(lines));
        y += lines * 16;
    }
    if (y >= 112){
        display.fillRect(0, 0, 240, 120, ST77XX_BLACK);
        display.setCursor(0, 0);
    }
    Serial.println("now X=" + String(display.getCursorX()) + ", Y=" + String(display.getCursorY()));
    display.setTextSize(size);
    display.setTextColor(color);
    display.println(text);
    Serial.println("now X=" + String(display.getCursorX()) + ", Y=" + String(display.getCursorY()));
}

void setup() {
    Serial.begin(9600);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    init_screen();
    Serial.println("oled init success");

    Serial.println("ST7789 TFT Test!");
    display.init(240, 240);
    Serial.println("inti success!");
    display.setRotation(2);
    display.fillScreen(ST77XX_BLACK);
    display.setTextWrap(true);
    // tft.drawRect(0, 0, 240, 120, ST77XX_WHITE);
    display.setCursor(0, 0);
}

void loop() {
    // put your main code here, to run repeatedly:
    if(Serial.available()){
        char tag = Serial.read();
        if(tag == '0'){
            Serial.readBytes(data, 2);
            Serial.print(data[0]);
            Serial.println(data[1]);

            for(int i=0; i<2; i++){
                data[i] = '\0';
            }
        }else if(tag == '1'){
            String msg = Serial.readString();
            int length = msg.length() + 1;
            char *buffer = new char[length];
            msg.toCharArray(buffer, length);
            addText(buffer, 2, length, ST77XX_WHITE);
            delete[] buffer;
        }
    }

    random_show();
    delay(20);
}

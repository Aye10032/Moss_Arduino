#include <Adafruit_GFX.h> 
#include <Adafruit_ST7789.h> 
#include <SPI.h> 
#include <math.h>

#define TFT_CS 10 
#define TFT_DC 7
#define TFT_RST 8 

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST); 

char data[2];

void setup() { 
  Serial.begin(9600); 
  Serial.println("ST7789 TFT Test!"); 
  tft.init(240, 240);
  Serial.println("inti success!");   
  tft.setRotation(2); 
  tft.fillScreen(ST77XX_BLACK); 
  tft.setTextWrap(true);
  tft.drawRect(0, 0, 240, 120, ST77XX_WHITE);
  tft.setCursor(0, 0);
}

void loop() { 
  // nothing to see here
  if(Serial.available()){
    char tag = Serial.read();
    if(tag == '0'){
      Serial.readBytes(data, 2);
      Serial.print(data[0]);
      Serial.println(data[1]);
    }else if(tag == '1'){
      String msg = Serial.readString();
      int length = msg.length() + 1;
      char *buffer = new char[length];
      msg.toCharArray(buffer, length);
      addText(buffer, 2, length, ST77XX_WHITE);
      delete[] buffer;
    }
  }

  for(int i=0; i<2; i++){
    data[i] = '\0';
  }      
}

void addText(char *text, int size, int length, uint16_t color){
  int y = tft.getCursorY();
  if (size == 2 && length > 20){
    int lines = ceil((double)length / 20);
    Serial.println("lines: " + String(lines));
    y += lines * 16;
  }
  if (y >= 112){
    tft.fillRect(1, 1, 238, 118, ST77XX_BLACK);
    tft.setCursor(0, 0);        
  }
  Serial.println("now X=" + String(tft.getCursorX()) + ", Y=" + String(tft.getCursorY()));
  tft.setTextSize(size);
  tft.setTextColor(color);
  tft.println(text);      
  Serial.println("now X=" + String(tft.getCursorX()) + ", Y=" + String(tft.getCursorY()));
}

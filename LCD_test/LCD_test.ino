#include <Adafruit_GFX.h> 
#include <Adafruit_ST7789.h> 
#include <SPI.h> 

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
  tft.fillScreen(ST77XX_WHITE); 
  tft.setRotation(1); 
  tft.fillScreen(ST77XX_BLUE); 
  tft.setCursor(0, 0); 
  tft.setTextColor(ST77XX_YELLOW); 
  tft.setTextSize(2); 
  tft.println("Hello World!"); 
  tft.setTextSize(1); 
  tft.setCursor(0, 40); 
  tft.println("I'm a ST7789 TFT!"); 
}

void loop() { 
  // nothing to see here
  if(Serial.available()){
    char tag = Serial.read();
    if(tag == '0'){
      Serial.readBytes(data, 2);
      Serial.print(data[0]);
      Serial.println(data[1]);
    }
  }

  for(int i=0; i<2; i++){
    data[i] = '\0';
  }      
}

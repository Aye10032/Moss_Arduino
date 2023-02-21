#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int status[] = {0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Serial.println("screen init success");
  
  init_screen();
  delay(2000); // Pause for 2 seconds

  status[1] = 0;
  status[5] = 0;
  smal_lcd_show();
}

void loop() {
  // put your main code here, to run repeatedly:
  random_show();
  delay(500);
}

void init_screen() {
  for(int i=0; i<7; i++){
    status[i] = 1;
  }
  smal_lcd_show();
}

void smal_lcd_show(){
  display.clearDisplay();
  for(int i=0; i<7; i++){
    if (status[i] == 1){
      display.fillRect(i*15, 0, 10, 32, SSD1306_WHITE);
    }    
  }
  display.display();
}

void random_show(){
  randomSeed(analogRead(1));  
  for(int i=0; i<7; i++){
    status[i] = random(2);
  }
  smal_lcd_show();  
}

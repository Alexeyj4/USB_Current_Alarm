#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <AD9833.h>   // библиотека для работы с модулем AD9833

const int i_pin=14; //I sensor I pin A0
const int btn_pin=9; //Button pin
const int manual_switch_pin=4; // switch pin //switch for manual set 8300

const int SCREEN_WIDTH=128; // OLED display width, in pixels
const int SCREEN_HEIGHT=64; // OLED display height, in pixels
const int first_string=12;  //first string on LCD
const int second_string=28;  //second string on LCD
const int third_string=44;  //third string on LCD
const int fourth_string=62;  //fourth string on LCD

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

void setup() { 
  // put your setup code here, to run once:

Serial.begin(9600);

pinMode(btn_pin, INPUT_PULLUP); 
pinMode(i_pin, INPUT);
analogReference(INTERNAL);

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
  Serial.println("SSD1306 allocation failed");
  for(;;);
}

display.setFont(&FreeSerif9pt7b);
display.clearDisplay();
display.setTextSize(1);             
display.setTextColor(WHITE);        
display.setCursor(0,first_string);             
display.println("Loading...");
display.display();
delay(1000);


}


void loop() {  
  // put your main code here, to run repeatedly:
  Serial.print(digitalRead(btn_pin));
  Serial.print("---");
  Serial.println(analogRead(i_pin));

  display.clearDisplay();             
  display.setCursor(0,first_string);             
  display.println(analogRead(i_pin));
  display.display();

  if(digitalRead(btn_pin)==0) tone(3,1000,1000);
  
  delay(100);

  

}

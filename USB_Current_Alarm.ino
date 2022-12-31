#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <AD9833.h>   // библиотека для работы с модулем AD9833

const int i_pin=14; //I sensor I pin A0
const int btn_pin=9; //Button pin
const int buzzer_pin=3; //Button pin
const int manual_switch_pin=4; // switch pin //switch for manual set 8300

const int SCREEN_WIDTH=128; // OLED display width, in pixels
const int SCREEN_HEIGHT=64; // OLED display height, in pixels
const int first_string=12;  //first string on LCD
const int second_string=28;  //second string on LCD
const int third_string=44;  //third string on LCD
const int fourth_string=62;  //fourth string on LCD

const float filter_coef=100; //filter for measuring current
const int display_bypass_value=1000; //display bypass for increase perfomance
int display_bypass_iterator=0;

float i; //current current IN ADC UNITS

int i_min0=4; //i in mA
int i_min=10;
int i_max=16; //i must be 0.._min0 or i_min..i_max
int i_not_ok_flag=0; //flag if i is abnormal //0-ok; 1-low; 2-high



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
display.setTextSize(1);             
display.setTextColor(WHITE);        


}


int i2ma(float i_adc){
  return floor(i_adc/10);
}
 

void display_bypass(){
  display_bypass_iterator++;
  if(display_bypass_iterator>=display_bypass_value){
    display_bypass_iterator=0;
    display.clearDisplay();             
    display.setCursor(0,first_string);             
    display.print("i=");display.print(i2ma(i));display.print(" mA");
    display.display();
  }
}

void check_i(int i_ma){
  i_not_ok_flag=0;
  if(i_ma<i_min0)return;
  if(i_ma<i_min){i_not_ok_flag=1; return;}
  if(i_ma>i_max){i_not_ok_flag=2; return;}
}



void loop() {  
  // put your main code here, to run repeatedly:
  
  i=i+( float(analogRead(i_pin)-i) /filter_coef);


  display_bypass();
  
  check_i(i2ma(i));
  if(i_not_ok_flag==1)tone(buzzer_pin,13000,50);
  if(i_not_ok_flag==2)tone(buzzer_pin,10000,50);
  

  

  

}

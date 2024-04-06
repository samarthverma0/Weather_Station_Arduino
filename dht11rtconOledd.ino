#include <RTClib.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <Wire.h>

#include <DHT.h>
#include <DHT_U.h>

#define DHT11_WAIT 1000 // 2 secs delay for every sensor pickup

#define celsius     0
#define fahrenheit  1

#define DHT11_UNIT  celsius

RTC_DS3231 RTC;

//#define DHT11_UNIT  fahrenheit
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);

// Uncomment one of the lines below for whatever DHT sensor type you're using!
#define DHTTYPE DHT11 // DHT 11

uint8_t DHTPin = 7;
DHT dht(DHTPin, DHTTYPE);

float Temp;
float Humidity;
float Temp_F;

void setup() {
  Serial.begin(115200);
  Serial.println("start");
  Wire.begin();
  RTC.begin();
  pinMode(DHTPin, INPUT);
  dht.begin();
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
   // init done
  display.display();
  delay(100);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));


   

}

void loop() {

  delay(DHT11_WAIT);
  DateTime now = RTC.now();

  
  // read sensor
  Humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  Temp = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  Temp_F= dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(Humidity) || isnan(Temp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // display values in OLED
  display.setCursor(0,0);
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature = ");
  display.print(Temp);
  display.print("C");    
            
  // display humidity
  display.setCursor(0, 10);
  display.print("Humidity = ");
  display.print(Humidity);
  display.print("%");

  //display rtc
  display.setTextSize(1);                            
  display.setTextColor(WHITE,BLACK);
  display.setCursor(0,30);
  display.print("Date = ");
  display.print(now.year(), DEC);
  display.print('/');
  display.print(now.month(), DEC);
  display.print('/');
  display.print(now.day(), DEC);

  display.setTextSize(1);                            
  display.setTextColor(WHITE,BLACK);
  display.setCursor(0,20); 
  display.print("Time = ");                          
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  display.print(':');
  display.print(now.second(), DEC);
  

  
  display.display(); 

}
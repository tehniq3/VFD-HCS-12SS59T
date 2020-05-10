/*
 *  VFD.cpp, vacuum fluroescent example for Samsung HCS-12SS59T, V0.9 171112 qrt@qland.de
 *  https://www.eevblog.com/forum/projects/serial-controlled-vfd-samsung-hcs-12ss59t-am-i-missing-something/
 *  https://github.com/qrti/VFD-HCS-12SS59T
 *  
 *  "RTC clock & DHT sensor" adapted by Nicu FLORICA (niq_ro)
*/
// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "RTClib.h"
RTC_DS1307 rtc;

#include "VFD.h"

#include "DHT.h"  // https://github.com/tehniq3/used_library

#define DHTPIN 7     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);
// NOTE: For working with a faster chip, like an Arduino Due or Teensy, you
// might need to increase the threshold for cycle counts considered a 1 or 0.
// You can do this by passing a 3rd parameter for this threshold.  It's a bit
// of fiddling to find the right value, but in general the faster the CPU the
// higher the value.  The default for a 16mhz AVR is a value of 6.  For an
// Arduino Due that runs at 84mhz a value of 30 works.
// Example to initialize DHT sensor for Arduino Due:
//DHT dht(DHTPIN, DHTTYPE, 30);


int hh, mm, ss;
int tt, uu;
int zz, ll, aa;

unsigned long timp;
unsigned long rest;

String sirdeafisat;

void setup()
{
	pinMode(Pin_RED_LED13, OUTPUT);
	digitalWrite(Pin_RED_LED13, HIGH);

	Serial.begin(9600);
	Vfd.init();

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  }
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  dht.begin();

for (byte i = 0; i <= 3; i++) 
{
	Vfd.write("niq_ro's    ");		// display
  Vfd.display(); 
  delay(1000);
  Vfd.write("       clock");    // display
  Vfd.display(); 
  delay(1000);
}

} // end setup																	
																				
void loop()
{
  
/*
    DateTime now = rtc.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
*/

/*
 tt = random(27,30); 
 uu = random(45,49); 
*/

  uu = dht.readHumidity();  // Read relative humidity in %
  tt = dht.readTemperature(); // Read temperature as Celsius

if (isnan(uu) || isnan(tt))
  {
    Serial.println("Failed to read from DHT sensor!");
    uu = 50;
    tt = 25;
    return;
  }
 
/*
hh = random(24);
mm = random(60);
ss = random(60);

*/

for (int i = 0; i < 5; i++) 
{
  /*
 timp = millis()/1000;
 hh = timp/3600;   // hour
 hh = hh%24;
 rest = timp%3600; // rest
 mm = rest/60;   // minutes
 ss = rest%60;   // seconds
 */
 
 DateTime now = rtc.now();
 hh = now.hour(), DEC;
 mm = now.minute(), DEC; 
 ss = now.second(), DEC;
  
String deafisat;
if (hh < 10) deafisat = deafisat + " ";
deafisat = deafisat + hh;
deafisat = deafisat + "-";
if (mm < 10) deafisat = deafisat + "0";
deafisat = deafisat + mm;
deafisat = deafisat + "-";
if (ss < 10) deafisat = deafisat + "0";
deafisat = deafisat + ss;
deafisat = deafisat + " ";
if (tt < 10) deafisat = deafisat + " ";
deafisat = deafisat + tt;
deafisat = deafisat + "C";

// string to char: https://stackoverflow.com/questions/7383606/converting-an-int-or-string-to-a-char-array-on-arduino/7391187
String str = deafisat; // Define
int str_len = str.length() + 1; // Length (with one extra character for the null terminator)
char char_array[str_len]; // Prepare the character array (the buffer) 
str.toCharArray(char_array, str_len); // Copy it over

Vfd.write(char_array);  // display
  Vfd.display(); 
  delay(1000);  
}

for (int i = 0; i < 5; i++) 
{
/*
 timp = millis()/1000;
 hh = timp/3600;   // hour
 hh = hh%24;
 rest = timp%3600; // rest
 mm = rest/60;   // minutes
 ss = rest%60;   // seconds
*/

 DateTime now = rtc.now();
 hh = now.hour(), DEC;
 mm = now.minute(), DEC; 
 ss = now.second(), DEC;

String deafisat;
if (hh < 10) deafisat = deafisat + " ";
deafisat = deafisat + hh;
deafisat = deafisat + "-";
if (mm < 10) deafisat = deafisat + "0";
deafisat = deafisat + mm;
deafisat = deafisat + "-";
if (ss < 10) deafisat = deafisat + "0";
deafisat = deafisat + ss;
deafisat = deafisat + " ";
if (uu < 10) deafisat = deafisat + " ";
deafisat = deafisat + uu;
deafisat = deafisat + "/";

// string to char: https://stackoverflow.com/questions/7383606/converting-an-int-or-string-to-a-char-array-on-arduino/7391187
String str = deafisat; // Define
int str_len = str.length() + 1; // Length (with one extra character for the null terminator)
char char_array[str_len]; // Prepare the character array (the buffer) 
str.toCharArray(char_array, str_len); // Copy it over

Vfd.write(char_array);  // display
  Vfd.display(); 
  delay(1000);  
}

for (int i = 0; i < 3; i++) 
{
DateTime now = rtc.now();
/*
 zz = 5;  // day
 ll = 5;  // month
 aa = 2020; // yesr
*/

 zz = now.day(), DEC;
 ll = now.month(), DEC;
 aa = now.year(), DEC;
  
String deafisat = "  ";
if (zz < 10) deafisat = deafisat + "0";
deafisat = deafisat + zz;
deafisat = deafisat + "/";
if (ll < 10) deafisat = deafisat + "0";
deafisat = deafisat + ll;
deafisat = deafisat + "/";
deafisat = deafisat + aa;

// string to char: https://stackoverflow.com/questions/7383606/converting-an-int-or-string-to-a-char-array-on-arduino/7391187
String str = deafisat; // Define
int str_len = str.length() + 1; // Length (with one extra character for the null terminator)
char char_array[str_len]; // Prepare the character array (the buffer) 
str.toCharArray(char_array, str_len); // Copy it over

Vfd.write(char_array);  // display
  Vfd.display(); 
  delay(1000);  
}

} // end main loop

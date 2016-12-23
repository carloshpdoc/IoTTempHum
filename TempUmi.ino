#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

//Constants
#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22 
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor 


//Variables
int chk;
float um;  
float temp;

void setup()
{
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
    um = dht.readHumidity();
    temp= dht.readTemperature();
    Serial.print("Umidade: ");
    Serial.print(um);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    delay(2000);
}

   

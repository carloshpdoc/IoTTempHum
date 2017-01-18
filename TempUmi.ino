#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


#include <ESP8266WiFi.h>
 
const char* ssid = "---";
const char* password = "---!";
 
WiFiServer server(80);

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

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop()
{
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  um = dht.readHumidity();
  temp= dht.readTemperature();
  
  //Response to the client
  String buf = "";
  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
  buf += "<html lang=\"en\"><head><meta http-equiv=\"refresh\" content=\"2\" name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  buf += "<title>WebServer ESP8266</title>";
  buf += "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:80%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;} .q{float: right;width: 64px;text-align: right;}</style>";
  buf += "</head>";
  buf += "<h3> ESP8266 Web Server</h3>";
   
  buf += String("<div><h4>Temperatura</h4>")+ temp + " *C</div>";
  buf += String("<div><h4>Umidade</h4>")+ um +" %</div>";
 
  buf += "<h4>Som Livre</h4>";
   buf += "</html>\n";
  //Sends the response to the client.
  client.print(buf);
  client.flush();
  client.stop();
  delay(2000);
}

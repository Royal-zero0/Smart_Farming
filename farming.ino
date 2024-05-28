#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>  // Including library for dht



#define BLYNK_TEMPLATE_ID "TMPL_R7yyOnw"
#define BLYNK_DEVICE_NAME "esp"
#define BLYNK_AUTH_TOKEN "CisLrR9XeumZhDkZcUosq47SZsur6R6A"
char auth[] = "CisLrR9XeumZhDkZcUosq47SZsur6R6A";       //Authentication code sent by Blynk
char ssid[] = "realme7";                        //WiFi SSID
char pass[] = "dhiraj2003";                 //WiFi Password


#define DHTPIN D4          
DHT dht(DHTPIN, DHT11);
#define buzzer D1
#define rainPin D7
 const int SensorPin = A0;
int pumpw = D3; 
int pumpf = D2;
#define pirPin1 D0
#define pirPin2 D9
#define pirPin3 D6
 
#define pirPin5 D8
int wpump;
int fpump;
int motion;
int manual;
BlynkTimer timer;

BLYNK_WRITE(V3) {
  wpump = param.asInt();
}
 
BLYNK_WRITE(V4) {
   fpump= param.asInt();
}
BLYNK_WRITE(V5) {
  motion = param.asInt();
}
BLYNK_WRITE(V6) {
  manual = param.asInt();
}
void setup()
{
  Serial.begin(115200);
  
  Blynk.begin(auth, ssid, pass,"blynk.cloud", 8080);
  
  pinMode(pumpf, OUTPUT);
  pinMode(pumpw, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pirPin1, INPUT);
  pinMode(pirPin2, INPUT);
  pinMode(pirPin3, INPUT);
 
  pinMode(pirPin5, INPUT);
  pinMode(SensorPin, INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(rainPin, INPUT);

  

  dht.begin();
  
  
  
  timer.setInterval(1L, getPirValue1);
  timer.setInterval(1L, getPirValue2);
  timer.setInterval(1L, getPirValue3);
  timer.setInterval(1L, rain);
  timer.setInterval(1L, getPirValue5);
 
  timer.setInterval(1L, rainSensor);
  timer.setInterval(1L, soilsensor );
  
}



void rainSensor() {
  int value = digitalRead(rainPin);
  
  
  Serial.println("Rain");
  Serial.println(value);
  
  
  
  
}

int moisturePercentage;
void soilsensor()
{ 
   int moisture = analogRead(SensorPin);
   moisturePercentage=map(moisture,1023,450,0,100);
   
   Serial.println("Soil moisture");
   Serial.println(moisturePercentage);
   Blynk.virtualWrite(V2,moisturePercentage);
if(manual==1){
 if (wpump == 1 ) {
   digitalWrite(pumpw, HIGH);
  }
 
else{
  digitalWrite(pumpw, LOW);
}
}
 else{ 
    if(moisturePercentage > 60){
   
  
    Blynk.notify("Soil Moisture level looks good... ");
    digitalWrite(pumpw, LOW);
  }
  else
  {
     Blynk.notify("Soil need water ");
     digitalWrite(pumpw, HIGH);
  }
}
   
}



int pirValue1;
int pi1 = 0;
void getPirValue1(void)        
{ 
  
  if (motion == 0 ){
    int pirValue1 = 0;
  }
  else{
  int pirValue1 = digitalRead(pirPin1);
  Serial.println("Motion ");
  Serial.println(pirValue1);
  
    
  
  if (pirValue1 == 1 && pi1 == 0)
  {
    Serial.println("Motion detected east");
    Blynk.notify("Motion detected in your farm") ;
    pi1=1;
    digitalWrite(buzzer, HIGH); 
    delay(1000);
    digitalWrite(buzzer,LOW);
  }
}
  if(pirValue1 == 0)
  {
    pi1=0;
  }
}
int pi2 = 0;
void getPirValue2(void)        
{ 
  int pirValue2 = digitalRead(pirPin2);
  Serial.println("Motion ");
  Serial.println(pirValue2);
  if (pirValue2 == 1 && pi2 == 0)
  {
    Serial.println("Motion detected west");
   // Blynk.notify("Motion detected in your farm west") ;
    pi2=1;
    //digitalWrite(buzzer, HIGH); 
    
    //digitalWrite(buzzer,LOW);
  }
  if(pirValue2 == 0)
  {
    pi2=0;
  }
}
int pi3 = 0;
void getPirValue3(void)        
{ 
  int pirValue3 = digitalRead(pirPin3);
  Serial.println("Motion ");
  Serial.println(pirValue3);
  if (pirValue3 == 1 && pi3 == 0)
  {
    Serial.println("Motion detected north");
   // Blynk.notify("Motion detected in your farm north") ;
    pi3=1;
    //digitalWrite(buzzer, HIGH); 
    
    //digitalWrite(buzzer,LOW);
  }
  if(pirValue3 == 0)
  {
    pi3=0;
  }
}
void rain(void)        
{ 
  int rainState = digitalRead(rainPin);
  Serial.println("rain");
   Serial.println(rainState);
  
  
  
  if (rainState == 0 )
  {
   Blynk.notify("It's Raining outside!"); 
    Serial.println("It's Raining outside!");
 
    
    
  }
}


int pi5 = 0;

void getPirValue5(void)        
{ 
  int pirValue5 = digitalRead(pirPin5);
  Serial.println("Motion ");
  Serial.println(pirValue5);
  if (pirValue5 == 1 && pi5 == 0)
  {
    Serial.println("Motion detected");
    Blynk.notify("Motion detected in your farm") ;
    pi5=1;
    //digitalWrite(buzzer, HIGH); 
    
    //digitalWrite(buzzer,LOW);
  }
  if(pirValue5 == 0)
  {
    pi5=0;
  }
}


void loop() {
  Blynk.run();
  timer.run();
  
  
  
 if (fpump == 1 ){ 
 digitalWrite(pumpf, HIGH);
 }else
 {
  digitalWrite(pumpf, LOW);
 }
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(t);
  Blynk.virtualWrite(V0, t);
  Serial.print("Humidity: ");
  Blynk.virtualWrite(V1, h);
  Serial.println(h);
 
 
  }

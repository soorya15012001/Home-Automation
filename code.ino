
#include <SoftwareSerial.h> //Librarey for serial connection with ESP

SoftwareSerial ESP(2,3); //ESP is connected to 12 and 13 pin of Arduino

 
String sendData = "https://api.thingspeak.com/channels/1077533/feeds.json?api_key=QSR5LPNC0T7QSYRN&results=2";
String output = ""; //Initialize a null string variable 
#define Relay1 6

void setup() 
{
  pinMode(Relay1,OUTPUT);
  
  delay(2000);

  Serial.begin (9600);
  delay(100);
  ESP.begin(9600);
    
    ESP_talk("AT+RST");
    ESP_talk("AT+CWMODE=1");
    ESP_talk("AT+CWJAP=\"Soorya\",\"soor1234\"");

  Serial.println("Wifi Connected"); 
  delay(1000);  

}

void loop() {

 String cmd = "AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80";   

 ESP_talk("AT+CIPMUX=0");
 ESP_talk(cmd);
    delay(100); 
 ESP_talk("AT+CIPSEND=76" );  
    delay(100);
  output = "";
 ESP_talk(sendData,1000);
    delay(100);

char incoming_value=output[126]; // Extracted the last value as that is the value needed.

    Serial.print("incoming_value is : ");   
    Serial.println(incoming_value);
    
    if (incoming_value == '0') 
    {
      
      digitalWrite(Relay1,LOW);
    }
    if (incoming_value == '1') 
    {
     
      digitalWrite(Relay1,HIGH);
    }
}

void ESP_talk(String AT_cmd)
{
  
  Serial.print("Sent: ");
  Serial.print(AT_cmd);
  ESP.println(AT_cmd); 
  Serial.println("");
  
  output=""; 

    while (ESP.available())
    {
      char i = ESP.read(); // read one char 
      output += i; //Combine char to string 
    }
 
  
  Serial.println("Received: ");
  Serial.print(output);
  
}

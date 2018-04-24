#include <vector>

int sensorPin = A0;
String inputString="";
std::vector<float> tempInCelsius;
std::vector<float> timeOfTemp;
int i = 0;
unsigned long timeNow = 0;
unsigned long timeLast = 0;

//Time start Settings:

int startingHour = 00; // set your starting hour here, not below at int hour. This ensures accurate daily correction of time

float seconds = 0;
int minutes = 0;
int hours = startingHour;
int days = 0;
float timeOfReading;
float timeInSeconds;
float temprature;
float timing;

void printVectors(int j){
      while( j > 0 ) {
        int tempSize = j - 1;
        int timeSize = j - 1;
        temprature = tempInCelsius[tempSize]; 
        j = j - 1 ;
        timing = timeOfTemp[timeSize];
        Serial.print(temprature);
        Serial.print(",");
        Serial.print(" ");
        Serial.println(timing);
      }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}
void loop()                     // run over and over again
{
timeNow = millis()/1000;        // the number of milliseconds that have passed since boot
seconds = timeNow - timeLast;   //the number of seconds that have passed since the last time 60 seconds was reached.

if (seconds == 60) {
  seconds = 0;
  timeLast = timeNow;
  minutes = minutes + 1;
}
else if (seconds > 60){
  timeLast = timeNow;
  seconds = seconds - 60;
  minutes = minutes + 1;  
}

//if one minute has passed, start counting milliseconds from zero again and add one minute to the clock.

timeInSeconds = seconds/100;
timeOfReading = minutes;
timeOfReading += timeInSeconds;

 //getting the voltage reading from the temperature sensor
 int reading = analogRead(sensorPin); 
 
 // converting that reading to voltage
 float voltage = reading * 3.3;
 voltage /= 1024.0;
 
 float temperatureC = -((voltage - 0.5) * 100) ;  //converting from 10 mv per degree wit 500 mV offset
                                                //to degrees ((voltage - 500mV) times 100)
 
 tempInCelsius.push_back(temperatureC);
 timeOfTemp.push_back(timeOfReading);
                                    
  delay(1000);                                  //waiting 1 second
  
  if(Serial.available()){
  while(Serial.available())
    {
      char inChar = (char)Serial.read();        //read the input
      inputString += inChar;                    //make a string of the characters coming on serial
    }
    if(inputString.equals("send")){             //If sending the data is requested
   printVectors(tempInCelsius.size());          //Send the data
        while(true){
       delay(7000);
  if(Serial.available()){                       //if there is a request 
    String inputStrin = "";
  while(Serial.available())                    
    {
      char inCha = (char)Serial.read(); //read the input
      inputStrin += inCha;        //make a string of the characters coming on serial
    }
    if(inputStrin.equals("ack")) {              //if the is an acknowledgement 
        while(tempInCelsius.size() > 0){        //Erase the old data
        timeOfTemp.pop_back();
        tempInCelsius.pop_back();
        }break;
        }
    }
    else
       printVectors(tempInCelsius.size());      //if there is no requests retransmit
        }     
    } inputString = "";
  }
  
       delay(10000);                  //waiting 10 second

}

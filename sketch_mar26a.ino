
int sensorPin = A0;
String inputString="";
float myTempsInCelsius[10];
int i = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}
void loop()                     // run over and over again
{
 //getting the voltage reading from the temperature sensor
 int reading = analogRead(sensorPin);  
 
 // converting that reading to voltage
 float voltage = reading * 3.3;
 voltage /= 1024.0; 
 
 // print out the voltage
 Serial.print(voltage); Serial.println(" volts");
 
 // now print out the temperature
 float temperatureC = -((voltage - 0.5) * 100) ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC); Serial.println(" degrees C");
 
 // now convert to Fahrenheit
 float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
 Serial.print(temperatureF); Serial.println(" degrees F");
 myTempsInCelsius[i] = temperatureC;
 i=i+1;
 if(i == 10){
  i=0;
 }
                                    
  delay(1000);                  //waiting a second
  
  if(Serial.available()){
  while(Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }    
    if(inputString.equals("average")){    //calculating average
      int j;
      float average = 0.0;
      for (j = 0; j < 10; j = j + 1) {
        average = average + myTempsInCelsius[j];
        }
        average = average/10;
        Serial.print("average value: " ); Serial.println(average);
    }
    inputString = "";
  }
       delay(5000);                  //waiting 5 second

}

#include <Servo.h>
#include <PID_v1.h>

Servo servoLeft; // Left Servo Connected to digital pin 11 
Servo servoRight; // Left Servo Connected to digital pin 10
int analogpin0 = 0;
int analogpin1 = 1;
int analogpin2 = 2;
int analogpin4 = 4;
float val = 0;
float voltage = 0;
float temp0;
float temp1;
float temp2;
float temp4;
unsigned long interval = 5000;
unsigned long interval1 = 600000;
unsigned long interval3 = 1000;
unsigned long previousMillis = 0;
unsigned long previousMillis1 = 0;


//PID Stuff
double val1, Setpoint, Input, Output;
int fanPin = 3; 
int tempPin = 1;
PID myPID(&Input, &Output, &Setpoint,5,1,1, DIRECT);

void setup()
{
  //Servo Setup
  servoLeft.attach(11); //small smotor to digi pin11
  servoRight.attach(10); //small smotor to digi pin10
     
  //Starting PID Setup
  Setpoint = 365;
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 254);//0 and 254 are the limits of the signal to the fan motor
  myPID.SetSampleTime(1000);
    Serial.begin(9600);
    Serial.println("Time, Set Point, Temp, Fan Speed");
}

void loop()
{ 
  
  if ((unsigned long)(millis() - previousMillis1) >= interval3) {
  previousMillis1 = millis();
        val = analogRead(analogpin0); // Top Left Thermocouple
            voltage = val * (5.0 / 1023.0); 
                temp0 = ((voltage - 1.25)/0.005); //Stores temp from analog pin 0
            
  Serial.print("Temp pin-0 =");
  Serial.println(temp0);
  
        val = analogRead(analogpin1); // Top Right Thermocouple
            voltage = val * (5.0 / 1023.0);
                temp1 = ((voltage - 1.25)/0.005); //Stores temp from analog pin 1
            
  Serial.print("Temp pin-1 =");
  Serial.println(temp1);
  
        val = analogRead(analogpin2); // Bottom Left Thermocouple
            voltage = val * (5.0 / 1023.0);
                temp2 = ((voltage - 1.25)/0.005); //Stores temp from analog pin 2
            
  Serial.print("Temp pin-2 =");
  Serial.println(temp2);
  
        val = analogRead(analogpin4); //Coal Box Thermocouple (Omega)
          voltage = val * (5.0 / 1023.0);
              temp4 = ((voltage - 1.25)/0.005); //Stores temp from analog pin 4
          
  Serial.print("Temp pin-4 ="); 
  Serial.println(temp4);
  
  int average = ((temp0+temp1+temp2)/3);
  
  Serial.print("average =");
  Serial.print(average);
  
     if ((unsigned long)(millis() - previousMillis) >= interval) {
  previousMillis = millis();
  
  //PID stuff
  
  Serial.print(millis());Serial.print(", ");
  Serial.print(Setpoint);Serial.print(", ");
  val1 = analogRead(tempPin);
  Serial.print(val1);Serial.print(", ");
  Input = average;
  myPID.Compute();
  int invOutput = map(Output, 0, 254, 254, 0);
  Serial.println(Output);
  analogWrite(fanPin, invOutput);
  
  //Side Vent stuff
         if ( average >= 110)
        
            {servoLeft.write(90);
            servoRight.write(90);
            }
         else if ( average <= 105)
           { servoLeft.write(180);
             servoRight.write(180);
           }
         else { Serial.print("Perfect Temperature");
       }
         
  }
}
}
            
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
          


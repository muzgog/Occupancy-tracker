#include <NewPing.h>
#include <NewTone.h>
 
// Select which PWM-capable pins are to be used.
#define RED_PIN    10
#define GREEN_PIN   11
#define BLUE_PIN  9
 
#define TRIGGER_PIN  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters).
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
boolean triggered = false;
 
 
#define ALARM 3
float sinVal;
int toneVal;
 
void setup(){
   
 //set pinModes for RGB strip
   pinMode(RED_PIN,OUTPUT);
   pinMode(BLUE_PIN,OUTPUT);
   pinMode(GREEN_PIN,OUTPUT);
   
   pinMode(ALARM, OUTPUT);
 
   //reset lights
   analogWrite(RED_PIN,0);
   analogWrite(BLUE_PIN,0);
   analogWrite(GREEN_PIN,0);
 
  delay(5000);
Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.  
 
 
}
 
void loop(){
    if(triggered == true){
      alarm();
    }
    else{
      delay(50);// Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
      unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
      unsigned int distance = uS / US_ROUNDTRIP_CM;
      Serial.println(distance);
      if(distance < 50){
         triggered = true;
      }
   }
}
 
void alarm(){
 //  color(255,0,0); //red
   //analogWrite(RED_PIN,0); 
   analogWrite(BLUE_PIN,0);
   delay(100);
  // color(255,255,0); //yelow
   delay(100);
   
   for (int x=0; x<180; x++) {
    // convert degrees to radians then obtain sin value
    sinVal = (sin(x*(3.1412/180)));
    // generate a frequency from the sin value
    toneVal = 2000+(int(sinVal*1000));
    NewTone(ALARM, toneVal);
  }
}
 
//helper function enabling us to send a colour in one command
void color (unsigned char red, unsigned char green, unsigned char blue)     // the color generating function
{    
    analogWrite(RED_PIN, red);    
    analogWrite(BLUE_PIN, blue);
    analogWrite(GREEN_PIN, green);
}

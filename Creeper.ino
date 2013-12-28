/*
 Fade
 
 This example shows how to fade an LED on pin 9
 using the analogWrite() function.
 
 This example code is in the public domain.
 
 */
int brightness = 0;    // how bright the LED is
int brightness2 = 255;
int fadeAmount = 1;    // how many points to fade the LED by
int count = 0;

int LED1_Pin = 0;
int LED2_Pin = 1;
int potPin = 3;
int pot_val = 0;

int LED_direction = 1; // Positive means fading in, negative means fading out

void setup()  { 
  // declare pin 9 to be an output:
  pinMode(LED1_Pin, OUTPUT);
  pinMode(LED2_Pin, OUTPUT);
} 

void loop()  { 
  // set the brightness of pin 9:
  analogWrite(LED1_Pin, brightness);
  analogWrite(LED2_Pin, brightness2);
  pot_val = analogRead(potPin);
  
  fadeAmount = 15*pot_val/1024*LED_direction;

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;
  brightness2 = 255 - brightness;


  // reverse the direction of the fading at the ends of the fade: 
    if (brightness <= 0 || brightness >= 255) {
    LED_direction = LED_direction*(-1);  
    }
  
  delay(10);                            
}

// The following bit setup is from http://www.insidegadgets.com/2011/02/27/how-to-use-the-pin-change-interrupt-on-attiny85/

#include <avr/sleep.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


int brightness = 0;    // how bright the LED is
int brightness2 = 255;
int fadeAmount = 1;    // how many points to fade the LED by
int count = 0;

int LED1_Pin = 0;
int LED2_Pin = 1;
int potPin = 3;
int pot_val = 0;

const int ButtonPin = 2;
int button_state = 0;
int button_pushed = 0; // This is the indicator that the button was pushed and released
int button_press_initiate[1];     // storage for button press function
int button_press_completed[1];    // storage for button press function

int LED_direction = 1; // Positive means fading in, negative means fading out

int mode = 2;

void setup()  { 
  // declare pin 9 to be an output:
  pinMode(LED1_Pin, OUTPUT);
  pinMode(LED2_Pin, OUTPUT);
  
  sbi(GIMSK,PCIE); // Turn on Pin Change interrupt
  sbi(PCMSK,PCINT2); // Set pin 2 as interrupt to wake from sleep
} 

void loop()  {
  
  button_state = digitalRead(ButtonPin);
  button_pushed = button_press (button_state, button_press_initiate, button_press_completed);
 
  if (mode == 2 | mode == 1){
    
    delay(10);

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
      
      if (button_pushed == 1){
      mode += 1;
      button_pushed = 0;
      }
     
      if (mode >= 3){mode = 0;} 
    
  }
 if (mode == 0){
   
   analogWrite(LED1_Pin,  0); // Shut off LEDs for sleep mode
   analogWrite(LED2_Pin,  0); // Shut off LEDs for sleep mode
   
   system_sleep();
   
   delay(1);
   
   if (button_state == 1){
   mode += 1;
   button_pushed = 0;
   }  
 }
}


int button_press (int button_indicator, int button_press_initiated[1], int button_press_complete[1]){
	if (button_indicator == 0 && button_press_initiated[0] == 1) {
	button_press_complete[0] = 1;
	button_press_initiated[0] = 0;
	}
	else if (button_indicator == 1){
	button_press_initiated[0] = 1;
	button_press_complete[0] = 0;
	}
	else {button_press_complete[0] = 0;}
return button_press_complete[0];
}

void system_sleep() { 
  // From http://www.insidegadgets.com/2011/02/27/how-to-use-the-pin-change-interrupt-on-attiny85/
  cbi(ADCSRA,ADEN); // Switch Analog to Digital converter OFF
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep mode
  sleep_mode(); // System sleeps here
  sbi(ADCSRA,ADEN);  // Switch Analog to Digital converter ON
}

ISR(PCINT0_vect) {
}



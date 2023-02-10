/*************************
	Programmer: (C)xVjVx
  Date: 02/01/2023
  About: Traffic ligther
**************************/

const int RED_LED = 3;
const int YELLOW_LED = 4;
const int GREEN_LED = 5;
const int POWER_ON_LED = 6;
const int POWER_BUTTON = 2;
const int ERROR_BUTTON = 8;

const bool DEBUG = true;

const int STANDBY = 0;
const int POWER_ON = 1;
const int ANALIZE_HARDWARE = 2;
const int ERROR_HARDWARE = 3;
const int RED_STATE = 4;
const int YELLOW_STATE = 5;
const int GREEN_STATE = 6;

int ASMState = STANDBY;

int activeLed = RED_LED;
int ledState = HIGH;
int blinkerCounter = 1;

int TRAFFIC_LIGHT[] = {RED_LED, YELLOW_LED, GREEN_LED};
int lightCounter = 0;

void setup(void){
    pinMode(POWER_BUTTON, INPUT);
      pinMode(ERROR_BUTTON, INPUT);
      pinMode(POWER_ON_LED, OUTPUT);
      pinMode(RED_LED, OUTPUT);
      pinMode(YELLOW_LED, OUTPUT);
      pinMode(GREEN_LED, OUTPUT);
     
      Serial.begin(9600);
 
      digitalWrite(POWER_ON_LED, LOW);
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
}

void loop(void)    {
  switch(ASMState)    {
    case STANDBY:    {
        bool buttonState = digitalRead(POWER_BUTTON);
 
          if(buttonState == true)    {
              ASMState = POWER_ON;
        }
     
        break;
    }
    case POWER_ON:    {  
      digitalWrite(POWER_ON_LED, HIGH);
     
      delay(500);
     
      ASMState = ANALIZE_HARDWARE;
      break;
    }
    case ANALIZE_HARDWARE:    {
      digitalWrite(activeLed, ledState);
     
      if(++blinkerCounter > 6)    {
          blinkerCounter = 1;
        activeLed = TRAFFIC_LIGHT[++lightCounter];
        if(lightCounter > 3) ASMState = RED_STATE;
      }
     
      if(ledState == HIGH)    {
        ledState = LOW;
      }
      else    {
          ledState = HIGH;
      }
     
      bool buttonState = digitalRead(ERROR_BUTTON);
 
        if(buttonState == true)    {
        digitalWrite(activeLed, LOW);
          ASMState = ERROR_HARDWARE;
      }
      else    {
          delay(350);
      }
     
      break;
    }
    case ERROR_HARDWARE:    {
      digitalWrite(POWER_ON_LED, LOW);
     
      break;
    }
    case RED_STATE:    {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      delay(3000);
      ASMState = YELLOW_STATE;
      break;
    }
    case YELLOW_STATE:    {
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, HIGH);
      delay(2000);
      ASMState = GREEN_STATE;
      break;
    }
    case GREEN_STATE:    {
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      delay(5000);
      ASMState = RED_STATE;
      break;
    }
  }
}
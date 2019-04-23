
/*
 *  NON-BLOCKING TRAFICLIGHTS
 *  -----------------------------
 *  
 *  tinkercad: https://www.tinkercad.com/things/251WpyNofbW
 *  
 *  Main State Configurations
 *  ------------------------
 *    STATE 0     |    STATE 1     |    STATE 2     |    STATE 3     |    STATE 4     |    STATE 5     |
 *                |                |                |                |                |                |
 *    ####        |                |                |          ####  |                |                |
 *    ####        |                |                |          ####  |                |                |
 *    ####        |                |                |          ####  |                |                |
 *    ----  ----  |    ----  ----  |    ----  ----  |    ----  ----  |    ----  ----  |    ----  ----  |
 *                |    ####        |          ####  |                |          ####  |    ####        |
 *                |    ####        |          ####  |                |          ####  |    ####        |
 *                |    ####        |          ####  |                |          ####  |    ####        |
 *    ----  ----  |    ----  ----  |    ----  ----  |    ----  ----  |    ----  ----  |    ----  ----  |
 *          ####  |          ####  |    ####  ####  |    ####        |    ####        |    ####  ####  |
 *          ####  |          ####  |    ####  ####  |    ####        |    ####        |    ####  ####  |
 *          ####  |          ####  |    ####  ####  |    ####        |    ####        |    ####  ####  |
 *                |                |                |                |                |                |
 *    TL1 - TL2   |    TL1 - TL2   |    TL1 - TL2   |    TL1 - TL2   |    TL1 - TL2   |    TL1 - TL2   |   
 */

// traficlight 1 pins
const int TL1_GREEN_PIN = 10;
const int TL1_YELLOW_PIN = 9;
const int TL1_RED_PIN = 8;

// traficlight 2 pins
const int TL2_GREEN_PIN = 7;
const int TL2_YELLOW_PIN = 6;
const int TL2_RED_PIN = 5;

// traficlight 1 state
int tl1_GreenState = LOW;
int tl1_YellowState = LOW;
int tl1_RedState = LOW;

// traficlight 2 state
int tl2_GreenState = LOW;
int tl2_YellowState = LOW;
int tl2_RedState = LOW;

// utils
const long INTERVAL = 1000;   // interval between state change
int mainState = 0;            // mainstate represents the traficlights formation
long previousTime = 0;
long currentTime;

// button configuration
const int BUTTON_PIN = 2;

//
void setup() {
  pinMode(TL1_GREEN_PIN, OUTPUT); 
  pinMode(TL1_YELLOW_PIN, OUTPUT); 
  pinMode(TL1_RED_PIN, OUTPUT); 
  
  pinMode(TL2_GREEN_PIN, OUTPUT); 
  pinMode(TL2_YELLOW_PIN, OUTPUT); 
  pinMode(TL2_RED_PIN, OUTPUT); 
  
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

//
void loop() {
  currentTime = millis();
  
  // 
  if (currentTime - previousTime >= INTERVAL || previousTime == 0) {
    previousTime = currentTime; // updates previous time to current time
    
    resetLightStates();     // resets all light states to LOW
    setLightStates();       // set sellected lightstates to HIGH
    writeLightStates();     // writes lightstates to digital pins
    incrementMainState();   // increments mainstate
  }
  
  // code here can be exuceted asynchronous while the ligth are waiting... 
  asyncButton(); 
}

// sets all light states to LOW
void resetLightStates() {
  // traficlight 1 state
  tl1_GreenState = LOW;
  tl1_YellowState = LOW;
  tl1_RedState = LOW;
  
  // traficlight 2 state
  tl2_GreenState = LOW;
  tl2_YellowState = LOW;
  tl2_RedState = LOW;
}

// set sellected lightstates to HIGH (Reference at Main State Configuration diagram)
void setLightStates() {
  switch(mainState) {
    case 0: {
        tl1_GreenState = HIGH;
        tl2_RedState = HIGH;
        break;
    }

    case 1: {
        tl1_YellowState = HIGH;
        tl2_RedState = HIGH;
        break;
    }

    case 2: {
        tl1_RedState = HIGH;
        tl2_RedState = HIGH;
        tl2_YellowState = HIGH;
        break;
    }

    case 3: {
        tl1_RedState = HIGH;
        tl2_GreenState = HIGH;
        break;
    }

    case 4: {
        tl1_RedState = HIGH;
        tl2_YellowState = HIGH;
        break;
    }

    case 5: {
        tl1_RedState = HIGH;
        tl1_YellowState = HIGH;
        tl2_RedState = HIGH;
        break;
    }
  }
}

// writes all pin values so the updated states will light the LEDs
void writeLightStates() {
  // traficlight 1 state
  digitalWrite(TL1_GREEN_PIN, tl1_GreenState);
  digitalWrite(TL1_YELLOW_PIN, tl1_YellowState);
  digitalWrite(TL1_RED_PIN, tl1_RedState);
  
  // traficlight 2 state
  digitalWrite(TL2_GREEN_PIN, tl2_GreenState);
  digitalWrite(TL2_YELLOW_PIN, tl2_YellowState);
  digitalWrite(TL2_RED_PIN, tl2_RedState);
}

// increments mainState and resets when the state reaches above 5 (conditional operator)
void incrementMainState() {
  mainState = (mainState < 5) ? ++mainState : 0;
}

// sets the LED_BUILTIN to high each time the button is pressed (asynchronous)
void asyncButton() {
  digitalWrite(LED_BUILTIN, digitalRead(BUTTON_PIN));
}

#include <Servo.h>
//include other libraries

int state;

#define PREFILL  1
#define FILL  2
#define PRE_FLIGHT  3
#define LAUNCH  4
#define SHUTDOWN  5
#define OPEN  180
#define CLOSED  90

// Arbitrary numbers for GSE serial input tests
char serialData;
#define FILL_START 6
#define FILL_STOP 7
#define GO 8
#define STOP 9


Servo oxValve;
Servo fuelValve;
Servo ventValve;
Servo mainValve;


//Code to set up servos and stuff here
void setup() {
  ventValve.attach(9);
  mainValve.attach(10);
  oxValve.attach(11);
  fuelValve.attach(12);
  
  state = PREFILL;
  Serial.begin(9600);
}

void loop(){
 // flightState(int state)

  {
    switch(state)
    {
      case PREFILL:
      
        // Print a line to serial to show it is in case PREFILL
      Serial.println("Case PREFILL");
          
        // intialize(); //initialize
        //Self-test sensors
        //self-test valves
        
      
        while(state == PREFILL)
        {
          //send diagnostic telemetry
        
          //if(Fill start command received from GSE)
          
          // serial input to test code
            if(Serial.available())
              {
               serialData = Serial.read();
    
               if(serialData == '6')
                 {
                    Serial.println("Break PREFILL");
                    state= FILL;
                    break;
                  }
              }
        }
        
        break;
      
      case FILL:
        // Print a line to serial to show it is in case FILL
        Serial.println("Case FILL");
            
        ventValve.write(OPEN); //open vent valves
        mainValve.write(CLOSED); //close main valves


        while (state == FILL)
        {
          //monitor pressures/temperatures
          //check measurements against redlines
        
          //if(fill stop command received from GSE)
          
            if(Serial.available())
              {
               serialData = Serial.read();
    
               if(serialData == '7')
                 {
                    Serial.println("Break FILL");
                    state= PRE_FLIGHT;
                    break;
                  }
              }
        }
        break;
      
      case PRE_FLIGHT:
       // Print a line to serial to show it is in case PRE-FLIGHT
      Serial.println("Case PRE-FLIGHT");
      
        ventValve.write(CLOSED); //close vent valves
        //self-test sensors
        //self-test valves

        while (state == PRE_FLIGHT)
        {
          //monitor pressures/temperatures
          //check measurements against bluelines and redlines
        
          //if(blue lines good && go command received)
              if(Serial.available())
              {
               serialData = Serial.read();
    
               if(serialData == '8')
                 {
                    Serial.println("Break PRE_FLIGHT");
                    state= LAUNCH;
                    break;
                  }
              }
        }
        break;
      
      case LAUNCH:
      // Print a line to serial to show it is in case LAUNCH
      Serial.println("Case LAUNCH");   
        
        //arm igniter
        //start countdown
        //send ignite command to GSE

      
        delay(10000); //wasn't sure if delays came before or after so I did both
        fuelValve.write(OPEN); //Open fuel valves (delay)
        delay(10000);
        oxValve.write(OPEN); //Open ox valves (delay)
        delay(10000);
      
        while (state == LAUNCH)
       {
          //monitor pressures/temperatures
          //check measurements against redlines
        
         //if(specified time after ignition has elapsed)
         if (1==1) // left this as 1==1 just so it compiles, add in if the time has elapsed later
         {
          // timing
          Serial.println("Break LAUNCH");
          state = SHUTDOWN;
          break;
         }
       }
       break;
      
     case SHUTDOWN:
      // Print a line to serial to show it is in case SHUTDOWN
      Serial.println("Case SHUTDOWN");
     
        oxValve.write(CLOSED); //close ox valves
        delay(10000); //arbitrary guess?
        fuelValve.write(CLOSED); //close fuel valves
        ventValve.write(OPEN); //open vent valves
      
        while (state == SHUTDOWN)
        {
          //monitor pressures/temperatures
          //check measurements against redlines
        
          //if(power removed or reset command sent)
            if(Serial.available())
              {
               serialData = Serial.read();
    
               if(serialData == '9')
                 {
                    Serial.println("Break SHUTDOWN");
                    state = 0;
                    break;
                  }
              }
        }
        break;

      default:
      // Print a line to serial to show it is in case PREFILL
      Serial.println("Case DEFAULT");
      break; 
      
    }
  }
}
// test
// kyleTest
// test via brendan

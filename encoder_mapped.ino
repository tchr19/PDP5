/* What is a rotary encoder? 
   * A rotary encoder is a type of position sensor that converts 
   * the angular position (rotation) of a knob into an output 
   * signal that is used to determine which direction the knob is 
   * being turned
 * 
 * What encoder are we using? 
   * From my understanding we are using an incremental encoder, wich 
   * informs how many increments the shaft has moved, where the absolut
   * reports the angle in wich the know are positioned in compared to
   * the starting position. 
   * 
 * See the following link for more information on a rotary encoder:
   * https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/
   * 
   * pins with interupt: 2,3,18,19,20,21
 */

// Defining the two datapins, DT and CLK for the azimuth encoder (LEFT)
# define azimuthCLK 18 // Chanel B blue
# define azimuthDT 19 // Chanel A yellow

// Defining the two datapins, DT and CLK for the elevation encoder (RIGHT)
# define elevationCLK 2 // Chanel A Yellow 
# define elevationDT 3 // Chanel B Blue

// We define our global variables for the two encoders
volatile int azimuthCounter = 0;
volatile int azimuthCurrentStateCLK;
volatile int azimuthLastStateCLK;
//String azimuthCurrentDir = "";

volatile int elevationCounter = 0; 
volatile int elevationCurrentStateCLK;
volatile int elevationLastStateCLK;
//String elevationCurrentDir = "";

void setup() {
  // We start by defining the pins as inputs
  // Encoder TAKES INPUT and deliver to the serial monitor. 
  pinMode(azimuthCLK, INPUT);
  pinMode(azimuthDT, INPUT);
  pinMode(elevationCLK, INPUT);
  pinMode(elevationDT, INPUT);

  // Setup the serial monitor
  Serial.begin(9600);

  // Read the initial state of CLK on azimuth and elevation
  azimuthLastStateCLK = digitalRead(azimuthCLK);
  elevationLastStateCLK = digitalRead(elevationCLK);
}

void loop() {
  // Read the current state of 
    azimuthCurrentStateCLK = digitalRead(azimuthCLK);
    elevationCurrentStateCLK = digitalRead(elevationCLK);


    // If the last and the current state of CLK are different, than
    // than change have occured. 
    // React to only 1 state change to avoid double count
    if (azimuthCurrentStateCLK != azimuthLastStateCLK 
    && azimuthCurrentStateCLK == 1) {

        // If DT is different from the CLK cariable, than the encoder
        // have been turned Counter clock-wise (CCW) - decrement 
        if (digitalRead(azimuthDT) != azimuthCurrentStateCLK) {
            azimuthCounter --;
            //azimuthCurrentDir = "CCW";
        } else {
            // Encoder is rotating clock-wise. Increment 
            azimuthCounter ++;
            //azimuthCurrentDir = "CW";
        }



        //Serial.print("0"); //Azimuth
        //Serial.print("  |  Direction: ");
        //Serial.print(azimuthCurrentDir);
        //Serial.print(",");
        Serial.print(azimuthCounter);
        Serial.print(",");
        Serial.println(elevationCounter);
        //Serial.write("10");
        //Serial.write("13");
        
    } else if(elevationCurrentStateCLK != elevationLastStateCLK 
    && elevationCurrentStateCLK == 1) {
        // If DT is different from the CLK cariable, than the encoder
        // have been turned Counter clock-wise (CCW) - decrement 
        if (digitalRead(elevationDT) != elevationCurrentStateCLK) {
            elevationCounter --;
            //elevationCurrentDir = "CCW";
        } else {
            // Encoder is rotating clock-wise. Increment 
            elevationCounter ++;
            //elevationCurrentDir = "CW";
        }

        Serial.print(azimuthCounter);
        Serial.print(",");
        Serial.println(elevationCounter);
    }

    
    
    // We need to remember last state of the encoder
    azimuthLastStateCLK = azimuthCurrentStateCLK;
    elevationLastStateCLK = elevationCurrentStateCLK;
    delay(1);

    // Elevation mapping
    if (elevationCounter == -1) {
      elevationCounter = 359;
    } else if (elevationCounter == 360) {
      elevationCounter = 0;
    }

    // Azimuth mapping
    if (azimuthCounter == -1) {
      azimuthCounter = 359;
    } else if (azimuthCounter == 360) {
      azimuthCounter = 0;
    }
}

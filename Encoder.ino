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
# define azimuthCLK 2 // Chanel A yellow
# define azimuthDT 3 // Chanel B blue

// Defining the two datapins, DT and CLK for the elevation encoder (RIGHT)
# define elevationCLK 18 // Chanel A Yellow 
# define elevationDT 19 // Chanel B Blue

// We define our global variables for the two encoders
volatile int azimuthCounter = 0;
volatile int azimuthCurrentStateCLK;
volatile int azimuthLastStateCLK;
String azimuthCurrentDir = "";

volatile int elevationCounter = 0; 
volatile int elevationCurrentStateCLK;
volatile int elevationLastStateCLK;
String elevationCurrentDir = "";

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
            azimuthCurrentDir = "CW";
        } else {
            // Encoder is rotating clock-wise. Increment 
            azimuthCounter ++;
            azimuthCurrentDir = "CCW";
        }

        Serial.print("Direction: ");
        Serial.print(azimuthCurrentDir);
        Serial.print("  |  Counter: ");
        Serial.println(azimuthCounter);
        Serial.print("  |  Azimuth");
    } else if(elevationCurrentStateCLK != elevationLastStateCLK 
    && elevationCurrentStateCLK == 1) {
        // If DT is different from the CLK cariable, than the encoder
        // have been turned Counter clock-wise (CCW) - decrement 
        if (digitalRead(elevationDT) != elevationCurrentStateCLK) {
            elevationCounter --;
            elevationCurrentDir = "CW";
        } else {
            // Encoder is rotating clock-wise. Increment 
            elevationCounter ++;
            elevationCurrentDir = "CCW";
        }

        Serial.print("Direction: ");
        Serial.print(elevationCurrentDir);
        Serial.print("  |  Counter: ");
        Serial.println(elevationCounter);
        Serial.print("  |  Elevation");
    }
    // We need to remember last state of the encoder
    azimuthLastStateCLK = azimuthCurrentStateCLK;
    elevationLastStateCLK = elevationCurrentStateCLK;
    delay(1);

}
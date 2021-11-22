#include <ODriveArduino.h>
#include <EasyTransfer.h>
#include <SoftwareSerial.h>
#include <ODriveArduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/*
// Serial to the ODrive
SoftwareSerial odrive_serial1(10, 11); //RX (ODrive TX), TX (ODrive RX)  // undercarriage
SoftwareSerial odrive_serial2(10, 11); //RX (ODrive TX), TX (ODrive RX)
SoftwareSerial odrive_serial3(10, 11); //RX (ODrive TX), TX (ODrive RX)
*/

#define odrive_serial1 Serial1 //TX = 1 , RX = 0
#define odrive_serial2 Serial2 //TX = 8 , RX = 7
#define odrive_serial3 Serial3 //TX = 14 , RX = 15

// ODrive objects

ODriveArduino odrive1(odrive_serial1);  
ODriveArduino odrive2(odrive_serial2);   
ODriveArduino odrive3(odrive_serial3);  

// declare rf24 info

// declare variables

// data structures?

/*
  struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO

    int16_t menuDown;
    int16_t Select;
    int16_t menuUp;
    int16_t toggleBottom;
    int16_t toggleTop;
    int16_t mode;
    int16_t RLR;
    int16_t RFB;
    int16_t RT;
    int16_t LLR;
    int16_t LFB;
    int16_t LT;
  };
  //**************remote control****************
  struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t mode;
  int16_t count;
  };
  //**************remote control****************
  SEND_DATA_STRUCTURE mydata_send;
  RECEIVE_DATA_STRUCTURE mydata_remote
*/

struct headPosition
{
  float x; //mm
  float y;
  float z;
  float rx; //?
  float ry;
  float rz;
}

struct radioMessageRemote
{
  struct joystickPos
  {
    float joystickX;
    float joystickY;
    float joystickZ;
  }
  int lockMode;
  int mode;
  int positionLock;
  int signalStrength;
}

struct radioMessageRobot
{
  int batteryPercent;
  float currentDraw;
  float voltage;
  int modeRobot;
  int signalStrength;
}

struct armValues
{
  
}

const int limbLength[3]

const int voltageSensor = *insert analog pin here*;

float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int voltValue = 0;

float motorPosition[totalMotorNumber - 1];

void setup() {

  //declare int float etc
  Serial.begin(1152000);
  odrive_serial1.begin(115200);  // front right leg
  odrive_serial2.begin(115200);
  odrive_serial3.begin(115200);

  radio.begin();                            //Starting the radio communication
  radio.openWritingPipe(addresses[0]);      //Setting the address at which we will send the data
  radio.openReadingPipe(1, addresses[1]);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);            //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.

}

void loop() {
  // put your main code here, to run repeatedly:
  timeBegin = millis();
  
  voltValue = analogRead(voltageSensor);
  vOUT = (value * 5.0) / 1024.0;
  vIN = vOUT / (R2/(R1+R2));

  readRadio();
  readArmPosition();
  calculateNewArmPosition();
  moveArm(CurrentArmPosition, newArmPosition)

  timeCurrent = millis();
  timeDifference = timeCurrent - timeBegin;

  if (timeDifference < 10)
  {
    delay(10 - timeDifference);
  }
}

void calculateNewArmPosition()
{
  readJoystick();
  coordinates +- to coords based on joystick input
}

void gearRatioCalc ( ? )
{
  for( i = 0; i < motorNumber; i++)
  {
    armJointAngle[i] = ((motorPosition[i] / maxEncoderPositions) * 360) / gearRatio[i]
  }
}

void readArmPosition ()
{
    for (int motor = 0; motor < 2; ++motor)
    {
      odrive_serial1 << "r axis" << motor << ".encoder.pos_estimate\n";
      motorPosition[motor] = odrive.readFloat();
    }
    
    for (motor = 0; motor < 2; ++motor)
    {
      odrive_serial2 << "r axis" << motor << ".encoder.pos_estimate\n";
      motorPosition[motor + 1] = odrive.readFloat();
    }
    
    for (motor = 0; motor < 2; ++motor)
    {
      odrive_serial3 << "r axis" << motor << ".encoder.pos_estimate\n";
      motorPosition[motor + 3] = odrive.readFloat();
    }
  
  inverseKinematics (motorPosition[]);
}

void inverseKinematics ()
{
  //.......
}

void forwardKinematics ()
{

  //.......
}

void moveArm()
{
    calculateInterpolation();
}

/*
  void setup() {
  // initialize serial ports
  Serial.begin(9600);    // USB serial port 0
  Serial3.begin(9600);   // serial port 3
  }

  byte rx_byte = 0;        // stores received byte

  void loop() {
  // check for data byte on USB serial port
  if (Serial.available()) {
    // get byte from USB serial port
    rx_byte = Serial.read();
    // send byte to serial port 3
    Serial3.write(rx_byte);
  }
  // check for data byte on serial port 3
  if (Serial3.available()) {
    // get a byte from serial port 3
    rx_byte = Serial3.read();
    // send the byte to the USB serial port
    Serial.write(rx_byte);
  }
  }

*/

* /

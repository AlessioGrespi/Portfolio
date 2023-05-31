#include <LiquidCrystal.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

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

int VRx = A0;
int VRy = A1;
int VRz = A2;
int SW = 2;

int xPosition = 0;
int yPosition = 0;
int zPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;
int mapZ = 0;

RF24 radio(9, 10);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int numRows = 2;

const int numCols = 16;

void setup()
{
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(VRz, INPUT);
  pinMode(SW, INPUT_PULLUP);

  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();                            //Starting the radio communication
  radio.openWritingPipe(addresses[0]);      //Setting the address at which we will send the data
  radio.openReadingPipe(1, addresses[1]);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);            //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.

  lcd.begin(numCols, numRows);
}


void loop()
{
  timeBegin = millis();

  radio.startListening();                    //This sets the module as receiver
  if (radio.available())                     //Looking for incoming data
  {
    radio.read(radioMessageRobot);
  }

  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  zPosition = analogRead(VRz);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  mapZ = map(zPosition, 0, 1023, -512, 512);

  radioMessageRemote.joystickPos = {mapX, mapY, mapZ};

  //radioMessageRemote.JoystickY = mapY;
  //radioMessageRemote.JoystickZ = mapZ;
      
  radio.stopListening();   
  
  Serial.print(radioMessageRemote);
  radio.write(radioMessageRemote);

  lcd.setCursor(0, 0);
  lcd.print("Mode: %i", modeRobot);
  lcd.setCursor(0, 10);
  
  lcd.setCursor(1, 0);
  lcd.print("Batt: %i%", batteryPercent);
  lcd.setCursor(1, 10);
  lcd.print("%2f V", voltage);
  lcd.setCursor(1, 13);
  lcd.print("%2f A", Current);

  timeCurrent = millis();
  timeDifference = timeCurrent - timeBegin;

  if (timeDifference < 10)
  {
    delay(10 - timeDifference);
  }

}

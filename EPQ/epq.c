//Includes LCD, Servo libraries
#include <LiquidCrystal.h>
#include <Servo.h>

//Includes Gyro communication library
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include <Wire.h>
#endif
#include <I2Cdev.h>

#include <MPU6050_6Axis_MotionApps20.h>

MPU6050 mpu; //Gyro definitions commands in this subsection have been copied from an existing program
#define OUTPUT_READABLE_YAWPITCHROLL
#define OUTPUT_READABLE_WORLDACCEL
#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;
// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
  mpuInterrupt = true;
}


LiquidCrystal lcd(37, 23, 25, 39, 27, 41); //initiates LCD
int lcdmode = 1; // mode switcher for lcd
int lcdmodeswitch = 42;

//states all subloops
void gyroSetup();
void gyroRead();
void gyroPitch();
void gyroRoll();
void gyroYaw();

//sets the various pins on the arduino to its relative component and name
int pos_yaw = 42;
int neg_yaw = 52;
int pos_pitch = 53;
int neg_pitch = 50;
int pos_roll = 49;
int neg_roll = 40;

int gyromode = 0; //sets the gyro mode, mode = 1 : saving a value, mode != 1 : not saving a value
int servo_lock = 44; //locks camera on its specific orientation
int y_lock = 47; //locks yaw orientation
int p_lock = 46; //locks pitch orientaion
int r_lock = 44; //locks roll orientation

//sets servos to midpoint
int ppos = 90;
int ypos = 90;
int rpos = 90;

//sets servo reset button (makes all servos at midpoint)
int servo_reset = 30;

//definitions for Angle lock program
int pangle;
int yangle;
int rangle;
int pitch;
int yaw;
int roll;

//initiates the names as servos
Servo yaw_servo;
Servo pitch_servo;
Servo roll_servo;

void setup() {

  lcd.begin(16, 2);
  lcd.print("Hello, world!");
  delay(2500);
  lcd.clear();

  void gyroSetup(); //Gyro setup program

  yaw_servo.attach(5);
  pitch_servo.attach(3);
  roll_servo.attach(4);
  yaw_servo.write(90);
  pitch_servo.write(90);
  roll_servo.write(90);

  pinMode(pos_pitch, INPUT);
  pinMode(neg_pitch, INPUT);
  pinMode(pos_yaw, INPUT);
  pinMode(neg_yaw, INPUT);
  pinMode(pos_roll, INPUT);
  pinMode(neg_roll, INPUT);
  pinMode(servo_reset, INPUT);
  pinMode(servo_lock, INPUT);
  pinMode(p_lock, INPUT);
  pinMode(y_lock, INPUT);
  pinMode(r_lock, INPUT);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("-=Ready=-");
  delay(2000);

}

void loop() {

  if (digitalRead(pos_pitch) == HIGH || digitalRead(neg_pitch) == HIGH) { //Manual Pitch movement
    if (digitalRead(pos_pitch) == HIGH && ppos < 180) {
      ppos++;
      pitch_servo.write(ppos);
      delay(15);
    }
    if (digitalRead(neg_pitch) == HIGH && ppos > 0) {
      ppos--;
      pitch_servo.write(ppos);
      delay(15);
    }
  }

  if (digitalRead(pos_roll) == HIGH || digitalRead(neg_roll) == HIGH) { //Manual Roll Movement
    if (digitalRead(pos_roll) == HIGH && rpos < 180) {
      rpos++;
      roll_servo.write(rpos);
      delay(15);
    }
    if (digitalRead(neg_roll) == HIGH && rpos > 0) {
      rpos--;
      roll_servo.write(rpos);
      delay(15);
    }
  }

  if (digitalRead(pos_yaw) == HIGH || digitalRead(neg_yaw) == HIGH) { //Manual Yaw Movement
    if (digitalRead(pos_yaw) == HIGH && ypos < 180) {
      ypos++;
      yaw_servo.write(ypos);
      delay(15);
    }
    if (digitalRead(neg_yaw) == HIGH && ypos > 0) {
      ypos--;
      yaw_servo.write(ypos);
      delay(15);
    }
  }

  if (digitalRead(servo_reset) == HIGH) { //Resets Servos to midpoint 90 degrees
    pitch_servo.write(90); //moves servos to midpoint
    yaw_servo.write(90);
    roll_servo.write(90);
    int ppos = 90; //Restates arduino value of servos to midpoint
    int ypos = 90;
    int rpos = 90;
  }

  if (digitalRead(servo_lock) == HIGH || (digitalRead(r_lock) == HIGH || digitalRead(y_lock) == HIGH || digitalRead(p_lock) == HIGH )) { //Lock orientations
    delay(10);
    gyromode ++;
    if (gyromode == 1) { //mode number for saving Gimbal lock angle
      int yangle = yaw;
      int rangle = roll;
      int pangle = pitch;
      delay (200);
    }
    if (digitalRead(servo_lock) == HIGH) { //All axis lock
      void gyroPitch();
      void gyroRoll();
      void gyroYaw();
    }
    if (digitalRead(y_lock) == HIGH) { //Yaw axis lock
      void gyroYaw();
    }
    if (digitalRead(p_lock) == HIGH) { //Pitch axis lock
      void gyroPitch();
    }
    if (digitalRead(r_lock) == HIGH) { //Roll axis lock
      void gyroRoll();
    }
  }
  else {
    int gyromode = 0; //Resets mode to 0
  }
}

void gyroRoll() { //Roll movement based on gyro
  if (roll + 5 <= rangle || roll - 5 >= rangle) {
    if (roll + 5 <= rangle && rpos >= 0) {
      rpos--;
      roll_servo.write(rpos);
      delay(15);
    }
    if (roll - 5 >= rangle && rpos <= 175) {
      rpos++;
      yaw_servo.write(rpos);
      delay(15);
    }
  }
}

void gyroPitch() { //Pitch movement based on gyro
  if (digitalRead(p_lock) == HIGH) {
    if (pitch + 5 <= pangle || pitch - 5 >= pangle) {
      if (pitch + 5 <= pangle && ppos >= 0) {
        ppos--;
        pitch_servo.write(ppos);
        delay(15);
      }
      if (pitch - 5 >= pangle && ppos <= 175) {
        ppos++;
        pitch_servo.write(ppos);
        delay(15);
      }
    }
  }
}

void gyroYaw() { //Yaw movement based on gyro
  if (yaw + 5 <= yangle || yaw - 5 >= yangle) {
    if (yaw + 5 <= yangle && ypos >= 0) {
      ypos--;
      yaw_servo.write(ypos);
      delay(15);
    }
    if (yaw - 5 >= yangle && ypos <= 175) {
      ypos++;
      yaw_servo.write(ypos);
      delay(15);
    }
  }
}

void gyroSetup() { //Gyro setup commands in this subsection have been copied from an existing program

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  // initialize serial communication
  // (115200 chosen because it is required for Teapot Demo output, but it's
  // really up to you depending on your project)
  Serial.begin(4800);
  while (!Serial); // wait for Leonardo enumeration, others continue immediately

  // NOTE: 8MHz or slower host processors, like the Teensy @ 3.3v or Ardunio
  // Pro Mini running at 3.3v, cannot handle this baud rate reliably due to
  // the baud timing being too misaligned with processor ticks. You must use
  // 38400 or slower in these cases, or use some kind of external separate
  // crystal solution for the UART timer.

  // initialize device
  lcd.setCursor(2, 0);
  Serial.println("Initializing I2C devices..");
  lcd.print("Initializing");
  mpu.initialize();

  // verify connection
  Serial.println(F("Testing device connections..."));
  lcd.setCursor(2, 1);
  lcd.print("..");
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
  lcd.setCursor(4, 1);
  lcd.print("..");

  // load and configure the DMP
  Serial.println(F("Initializing DMP..."));
  devStatus = mpu.dmpInitialize();
  lcd.setCursor(6, 1);
  lcd.print("..");

  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(80);
  mpu.setYGyroOffset(46);
  mpu.setZGyroOffset(14);
  mpu.setZAccelOffset(1100); // 1688 factory default for my test chip

  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);
    lcd.setCursor(8, 1);
    lcd.print("..");

    // enable Arduino interrupt detection
    Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    lcd.setCursor(10, 1);
    lcd.print("..");

    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    dmpReady = true;
    lcd.setCursor(12, 1);
    lcd.print("..");

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ERROR");
  }

}

void gyroRead() { //Reading gyro angles - commands in this section have been copied and modified from an existing program
  // put your main code here, to run repeatedly:
  // if programming failed, don't try to do anything
  if (!dmpReady) return;

  // wait for MPU interrupt or extra packet(s) available
  while (!mpuInterrupt && fifoCount < packetSize) {
    // other program behavior stuff here
    // .
    // .
    // .
    // if you are really paranoid you can frequently test in between other
    // stuff to see if mpuInterrupt is true, and if so, "break;" from the
    // while() loop to immediately process the MPU data
    // .
    // .
    // .
  }

  // reset interrupt flag and get INT_STATUS byte
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();

  // get current FIFO count
  fifoCount = mpu.getFIFOCount();

  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    // reset so we can continue cleanly
    mpu.resetFIFO();
    Serial.println(F("FIFO overflow!"));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Data overflow");

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
  } else if (mpuIntStatus & 0x02) {
    // wait for correct available data length, should be a VERY short wait
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

    // read a packet from FIFO
    mpu.getFIFOBytes(fifoBuffer, packetSize);

    // track FIFO count here in case there is > 1 packet available
    // (this lets us immediately read more without waiting for an interrupt)
    fifoCount -= packetSize;

#ifdef OUTPUT_READABLE_YAWPITCHROLL
    // display Euler angles in degrees
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    Serial.print("ypr\t");
    Serial.print(ypr[0] * 180 / M_PI);
    Serial.print("\t");
    Serial.print(ypr[1] * 180 / M_PI);
    Serial.print("\t");
    Serial.println(ypr[2] * 180 / M_PI);
    yaw = (ypr[0] * 180 / M_PI);
    pitch = (ypr[1] * 180 / M_PI);
    roll = (ypr[2] * 180 / M_PI);
#endif
  }
}


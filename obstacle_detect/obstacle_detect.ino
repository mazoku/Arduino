#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <avr/pgmspace.h>
#include <Wire.h>
#include <LSM303.h>

// #define LOG_SERIAL // write log output to serial port

#define LED 13
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12

// Accelerometer Settings
#define RA_SIZE 3  // number of readings to include in running average of accelerometer readings
#define XY_ACCELERATION_THRESHOLD 1000 //2400  // for detection of contact (~16000 = magnitude of acceleration due to gravity)

// Sound Effects
ZumoBuzzer buzzer;

// Motors
ZumoMotors motors;
#define FORWARD_SPEED 200  // forward speed
#define BACKWARD_SPEED 100  // backward speed
#define TURN_SPEED 100  // turn speed
 
// Timing
unsigned long loop_start_time;
unsigned long contact_made_time;
#define MIN_DELAY_BETWEEN_CONTACTS   1000  // ms = min delay between detecting new contact event

// RunningAverage class 
// based on RunningAverage library for Arduino
// source:  http://playground.arduino.cc/Main/RunningAverage
template <typename T> 
class RunningAverage
{
  public:
    RunningAverage(void);
    RunningAverage(int);
    ~RunningAverage();
    void clear();
    void addValue(T);
    T getAverage() const;
    void fillValue(T, int);
  protected:
    int _size;
    int _cnt;
    int _idx;
    T _sum;
    T * _ar;
    static T zero;
};

// Accelerometer Class -- extends the LSM303 Library to support reading and averaging the x-y acceleration 
//   vectors from the onboard LSM303DLHC accelerometer/magnetometer
class Accelerometer : public LSM303
{
  typedef struct acc_data_xy
  {
    unsigned long timestamp;
    int x;
    int y;
    float dir;
  } acc_data_xy;
  
  public: 
    Accelerometer() : ra_x(RA_SIZE), ra_y(RA_SIZE) {};
    ~Accelerometer() {};
    void enable(void);
    void getLogHeader(void);
    void readAcceleration(unsigned long timestamp);
    float len_xy() const;
    float dir_xy() const;
    int x_avg(void) const;
    int y_avg(void) const;
    long ss_xy_avg(void) const;
    float dir_xy_avg(void) const;
  private:
    acc_data_xy last;
    RunningAverage<int> ra_x;
    RunningAverage<int> ra_y;   
};

Accelerometer lsm303;
boolean in_contact;  // set when accelerometer detects contact with opposing robot


//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
void setup()
{  
  // Initiate the Wire library and join the I2C bus as a master
  Wire.begin();
  
  motors.flipLeftMotor(true);
  motors.flipRightMotor(true);
  
  // Initiate LSM303
  lsm303.init();
  lsm303.enable();
  
  Serial.begin(9600);
  lsm303.getLogHeader();

  pinMode(LED, HIGH);
  //buzzer.playMode(PLAY_AUTOMATIC);
  buzzer.playNote(NOTE_G(3), 200, 15);
  button.waitForButton();
  Serial.println("Starting detection.");
}


//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
void loop()
{
  //motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  lsm303.readAcceleration(loop_start_time); 

  if (check_for_contact()){
    on_contact_made();
  }
}


//-----------------------------------------------------------------------------------------------------------------
// check for contact, but ignore readings immediately after turning or losing contact
boolean check_for_contact(){
  static long threshold_squared = (long) XY_ACCELERATION_THRESHOLD * (long) XY_ACCELERATION_THRESHOLD;
  boolean contacted = lsm303.ss_xy_avg() > threshold_squared;
  boolean cooldowned = (millis() - contact_made_time) > MIN_DELAY_BETWEEN_CONTACTS;
  return (contacted && cooldowned);
}


//-----------------------------------------------------------------------------------------------------------------
// sound horn and accelerate on contact -- fight or flight
void on_contact_made(){  
  Serial.println("Contact!\n");
  
  //change_direction();
  
  in_contact = true;
  contact_made_time = millis();
  buzzer.playNote(NOTE_G(3), 200, 15);
}


//-----------------------------------------------------------------------------------------------------------------
void change_direction(){
  move_stop();
  move_backward(BACKWARD_SPEED);
  delay(500);
  move_turn_around(TURN_SPEED);
  delay(500);
  move_forward(FORWARD_SPEED);
}


//-----------------------------------------------------------------------------------------------------------------
// reset forward speed
void on_contact_lost(){
  Serial.print("contact lost");
  Serial.println();
  in_contact = false;
}


//-----------------------------------------------------------------------------------------------------------------
void move_forward(int speed){
  motors.setSpeeds(speed, speed);
}


//-----------------------------------------------------------------------------------------------------------------
void move_stop(){
  motors.setSpeeds(0, 0);
}


//-----------------------------------------------------------------------------------------------------------------
void move_backward(int speed){
  motors.setSpeeds(-speed, -speed);
}


//-----------------------------------------------------------------------------------------------------------------
void move_turn_around(int speed){
  motors.setSpeeds(speed, -speed);
}


// class Accelerometer -- member function definitions
// enable accelerometer only
// to enable both accelerometer and magnetometer, call enableDefault() instead
void Accelerometer::enable(void)
{
  // Enable Accelerometer
  // 0x27 = 0b00100111
  // Normal power mode, all axes enabled
  writeAccReg(LSM303::CTRL_REG1_A, 0x27);

  if (getDeviceType() == LSM303::device_DLHC)
  writeAccReg(LSM303::CTRL_REG4_A, 0x08); // DLHC: enable high resolution mode
}


//-----------------------------------------------------------------------------------------------------------------
void Accelerometer::getLogHeader(void)
{
  Serial.print("millis    x      y     len     dir  | len_avg  dir_avg  |  avg_len");
  Serial.println();
}


//-----------------------------------------------------------------------------------------------------------------
void Accelerometer::readAcceleration(unsigned long timestamp)
{
  readAcc();
  if (a.x == last.x && a.y == last.y) return;
  
  last.timestamp = timestamp;
  last.x = a.x;
  last.y = a.y;
  
  ra_x.addValue(last.x);
  ra_y.addValue(last.y);
 
 /*Serial.print(last.timestamp);
 Serial.print("  ");
 Serial.print(last.x);
 Serial.print("  ");
 Serial.print(last.y);
 Serial.print("  ");
 Serial.print(len_xy());
 Serial.print("  ");
 Serial.print(dir_xy());
 Serial.print("  |  ");
 Serial.print(sqrt(static_cast<float>(ss_xy_avg())));
 Serial.print("  ");
 Serial.print(dir_xy_avg());
 Serial.println();*/
}


float Accelerometer::len_xy() const{
  return sqrt(last.x*a.x + last.y*a.y);
}


float Accelerometer::dir_xy() const{
  return atan2(last.x, last.y) * 180.0 / M_PI;
}


int Accelerometer::x_avg(void) const{
  return ra_x.getAverage();
}


int Accelerometer::y_avg(void) const{
  return ra_y.getAverage();
}


long Accelerometer::ss_xy_avg(void) const{
  long x_avg_long = static_cast<long>(x_avg());
  long y_avg_long = static_cast<long>(y_avg()); 
  return x_avg_long*x_avg_long + y_avg_long*y_avg_long;
}


float Accelerometer::dir_xy_avg(void) const{
  return atan2(static_cast<float>(x_avg()), static_cast<float>(y_avg())) * 180.0 / M_PI;
}



// RunningAverage class 
// based on RunningAverage library for Arduino
// source:  http://playground.arduino.cc/Main/RunningAverage
// author:  Rob.Tillart@gmail.com
// Released to the public domain

template <typename T>
T RunningAverage<T>::zero = static_cast<T>(0);


template <typename T>
RunningAverage<T>::RunningAverage(int n){
  _size = n;
  _ar = (T*) malloc(_size * sizeof(T));
  clear();
}


template <typename T>
RunningAverage<T>::~RunningAverage(){
  free(_ar);
}


// resets all counters
template <typename T>
void RunningAverage<T>::clear() { 
  _cnt = 0;
  _idx = 0;
  _sum = zero;
  for (int i = 0; i< _size; i++) _ar[i] = zero;  // needed to keep addValue simple
}


// adds a new value to the data-set
template <typename T>
void RunningAverage<T>::addValue(T f){
  _sum -= _ar[_idx];
  _ar[_idx] = f;
  _sum += _ar[_idx];
  _idx++;
  if (_idx == _size) _idx = 0;  // faster than %
  if (_cnt < _size) _cnt++;
}


// returns the average of the data-set added so far
template <typename T>
T RunningAverage<T>::getAverage() const{
  if (_cnt == 0) return zero; // NaN ?  math.h
  return _sum / _cnt;
}

// fill the average with a value
// the param number determines how often value is added (weight)
// number should preferably be between 1 and size
template <typename T>
void RunningAverage<T>::fillValue(T value, int number){
  clear();
  for (int i = 0; i < number; i++) 
  {
    addValue(value);
  }
}

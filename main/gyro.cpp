// Basic demo for accelerometer readings from Adafruit MPU6050
#include "gyro.h"
#include "config.h"

Gyro::Gyro(): acc_x_arr({0}), acc_y_arr({0}), acc_z_arr({0}),
              acc_x(0), acc_y(0), acc_z(9.8),tick(0), reading_idx(0), curr_direction(SIDE::STAY), wire(0){}

void Gyro::getGyroRead(){
  this->mpu.getEvent(&this->a, &this->g, &this->temp);
}

void Gyro::updateArrays(){
  this->acc_x_arr[this->reading_idx] = this->a.acceleration.x;
  this->acc_y_arr[this->reading_idx] = this->a.acceleration.y;
  this->acc_z_arr[this->reading_idx] = this->a.acceleration.z;
}

double Gyro::getArrAvg(double* arr){
    double sum = 0;
    for (int i = 0; i < 10; ++i) {
        sum += arr[i];
    }
    // Compute average
    double average = sum / 10.0;
    return average;
}

bool Gyro::setup() {

  wire.begin(PIN_GYRO_SDA, PIN_GYRO_SCL);

  // Try to initialize!
  while (!mpu.begin(0x68, &wire)) {
    Serial.println("Failed to find MPU6050 chip");
    return false;
  }

  this->mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  this->mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  this->mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  return false;
}

Gyro::SIDE Gyro::getCurDir(){
  return this->curr_direction;
}

void Gyro::update(int dt) {
    this->tick += dt;

    if(this->tick >= 50){
      this->getGyroRead();
      this->updateArrays();

      this->reading_idx++;

      if(this->reading_idx >= 8) {
          this->reading_idx = 0;
          this->acc_x = this->getArrAvg(this->acc_x_arr);
          this->acc_y = this->getArrAvg(this->acc_y_arr);
          this->acc_z = this->getArrAvg(this->acc_z_arr);
      
      
        // Decide which axis dominates
        if (abs(this->acc_x) > abs(this->acc_y)) {
          // Move along X
          if (this->acc_x < -3){ 
            this->curr_direction = SIDE::RIGHT;
          }else if (this->acc_x > 3){ 
            this->curr_direction = SIDE::LEFT;
          }
          else{
            this->curr_direction = SIDE::STAY;
          }
        } else {
          // Move along Y
          if (this->acc_y > 3){ 
            this->curr_direction = SIDE::DOWN;
          }
          else if (this->acc_y < -3){ 
            this->curr_direction = SIDE::UP;
          }
          else{
            this->curr_direction = SIDE::STAY;
          }
        }
      }

      this->tick = 0;
    }
}


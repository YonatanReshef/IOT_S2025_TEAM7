#ifndef GYRO_H
#define GYRO_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

// Sides for movement
enum SIDE {
    LEFT,
    RIGHT,
    UP,
    DOWN
};



class Gyro
{   
private:
    // MPU6050 object
    Adafruit_MPU6050 mpu;

    //acceleration arrays in each axis
    double acc_x_arr[10];
    double acc_y_arr[10];
    double acc_z_arr[10];

    //acceleration values in each exis
    double acc_x, acc_y, acc_z;

    // sensors for mpu
    sensors_event_t a, g, temp;


    // index in arrays for next reading
    int reading_idx;

    
    // Get the average of an array
    double getArrAvg(double* arr)

    // Put the next reading in the arrays
    void updateArrays();

    // get the Gyro readings
    void getGyroRead();

public:
    Gyro();
    ~Gyro() = default;


    void setup();
    void update();

    // Add any other necessary methods or members here
}






#endif
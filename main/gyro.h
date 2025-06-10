#ifndef GYRO_H
#define GYRO_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>


enum Color {
    LEFT,
    RIGHT,
    UP,
    DOWN
};


class Gyro
{   
private:
    Adafruit_MPU6050 mpu;

    double acc_x_arr[10];
    double acc_y_arr[10];
    double acc_z_arr[10];

    double acc_x, acc_y, acc_z;

    sensors_event_t a, g, temp;



    int reading_idx;

    

    double getArrAvg(double* arr)
    void updateArrays();
    void getGyroRead();

public:
    Gyro();
    ~Gyro() = default;


    void setup();
    void update();

    // Add any other necessary methods or members here
}






#endif
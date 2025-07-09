
#ifndef CONFIG_H
#define CONFIG_H
// here define constants and pins

// ==== optic comm pins ====
#define PIN_LED_OUT_U 19
#define PIN_LED_OUT_L 18
#define PIN_LED_OUT_R 12
#define PIN_LED_OUT_D 13

#define PIN_RECVR_U 33
#define PIN_RECVR_L 32
#define PIN_RECVR_R 34
#define PIN_RECVR_D 35

// ==== gyro pins ====
#define PIN_GYRO_SDA 21 // can switch to 18
#define PIN_GYRO_SCL 22 // can switch to 19

// ==== LED matrix ====
#define PIN_MAT_IN 27

// ==== Buttons ====
#define PIN_START_BTN 4


// ==== Settings ====
#define DELTA_TIME 10
#define BRIGHTNESS 10


#endif
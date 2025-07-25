
#ifndef CONFIG_H
#define CONFIG_H
// here define constants and pins

// ==== optic comm pins ====
#define PIN_LED_OUT_U 13
#define PIN_LED_OUT_L 12
#define PIN_LED_OUT_R 18
#define PIN_LED_OUT_D 19

#define PIN_RECVR_U 35
#define PIN_RECVR_L 34
#define PIN_RECVR_R 32
#define PIN_RECVR_D 33

// ==== gyro pins ====
#define PIN_GYRO_SDA 21 // can switch to 18
#define PIN_GYRO_SCL 22 // can switch to 19

// ==== LED matrix ====
#define PIN_MAT_IN 27

// ==== Buttons ====
#define PIN_START_BTN 4


// ==== Settings ====
#define DELTA_TIME 10
#define BRIGHTNESS 25


#endif
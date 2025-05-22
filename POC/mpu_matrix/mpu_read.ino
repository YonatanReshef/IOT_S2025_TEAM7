// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define MATRIX_WIDTH 16
#define MATRIX_HEIGHT 16
#define PIN        12
#define NUMPIXELS  256
#define BRIGHTNESS 20

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int pos_x = MATRIX_WIDTH / 2;
int pos_y = MATRIX_HEIGHT / 2;

int tick = 0;

/* Get new sensor events with the readings */
sensors_event_t a, g, temp;


double gyro_x[10] = {0};
double gyro_y[10] = {0};
double gyro_z[10] = {0};

double acc_x[10] = {0};
double acc_y[10] = {0};
double acc_z[10] = {0};

double tempeture[10] = {0};


Adafruit_MPU6050 mpu;



int getPixelIndex(int x, int y) {
  if (y % 2 == 0) {
    // left to right
    return y * MATRIX_WIDTH + x;
  } else {
    // right to left
    return y * MATRIX_WIDTH + (MATRIX_WIDTH - 1 - x);
  }
}



void get_gyro_read(){
  mpu.getEvent(&a, &g, &temp);
}


void update_arrays(){
  int turn = tick % 10;

  gyro_x[turn] = g.gyro.x;
  gyro_y[turn] = g.gyro.y;
  gyro_z[turn] = g.gyro.z;

  acc_x[turn] = a.acceleration.x;
  acc_y[turn] = a.acceleration.y;
  acc_z[turn] = a.acceleration.z;

  tempeture[turn] = temp.temperature;
}


double avg_arr(double* arr){
    Serial.println("In Comp");
    double sum = 0;
    for (int i = 0; i < 10; ++i) {
        sum += arr[i];
    }

    Serial.print("Sum is: ");
    Serial.print(sum);
    Serial.println(" ");

    // Compute average
    double average = sum / 10.0;

    return average;
}

void get_average(){

  Serial.println("In Avg1");

  double g_avg_x = avg_arr(gyro_x);
  double g_avg_y = avg_arr(gyro_y);
  double g_avg_z = avg_arr(gyro_z);

  Serial.println("In avg");

  Serial.print("Rotation X: ");
  Serial.print(g_avg_x);
  Serial.print(", Y: ");
  Serial.print(g_avg_y);
  Serial.print(", Z: ");
  Serial.print(g_avg_z);
  Serial.println(" rad/s");

  double a_avg_x = avg_arr(acc_x);
  double a_avg_y = avg_arr(acc_y);
  double a_avg_z = avg_arr(acc_z);



  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a_avg_x);
  Serial.print(", Y: ");
  Serial.print(a_avg_y);
  Serial.print(", Z: ");
  Serial.print(a_avg_z);
  Serial.println(" m/s^2");

  double temp_avg = avg_arr(tempeture);

  Serial.print("Temperature: ");
  Serial.print(temp_avg);
  Serial.println(" degC");

  Serial.println("");

}





void setup(void) {
  Serial.begin(115200);
  sleep(1)
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");


  // NeoPixel setup
  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);
  pixels.clear();

  // Light up center pixel immediately
  int centerIndex = getPixelIndex(pos_x, pos_y);
  pixels.setPixelColor(centerIndex, pixels.Color(255, 0, 0));
  pixels.show();


  delay(100);
}

void loop() {
  get_gyro_read();
  update_arrays();

  if (tick % 10 == 0) {
    get_average();

    // Calculate average acceleration
    double ax = avg_arr(acc_x);
    double ay = avg_arr(acc_y);

    // Decide which axis dominates
    if (abs(ax) > abs(ay)) {
      // Move along X
      if (ax < -3 && pos_x < 15) pos_x++;
      else if (ax > 3 && pos_x > 0) pos_x--;
    } else {
      // Move along Y
      if (ay > 3 && pos_y > 0) pos_y--;
      else if (ay < -3 && pos_y < 15) pos_y++;
    }

    pixels.clear();
    int index = getPixelIndex(pos_x, pos_y);
    pixels.setPixelColor(index, pixels.Color(255, 0, 0));
    pixels.show();
  }

  tick++;
  delay(10);
}



// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

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

void setup(void) {
  Serial.begin(115200);
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
  delay(100);
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



void loop() {
  get_gyro_read();

  update_arrays();

  if(tick % 10 == 0){
    Serial.println(" int 10th tick");
    get_average();
  }

  tick += 1;

  delay(10);
}
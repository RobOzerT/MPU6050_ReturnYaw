#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

void setup() {
  calibrateMPU();
}

void loop() {
  printYaw();
  delay(100); // Delay for 0.1 second.
}

void calibrateMPU() {
  // All kinds of things that need to be done.
  Serial.begin(9600);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print("MPU6050 status: ");
  Serial.println(status);
  while (status != 0) { } // Stop everything if could not connect to MPU6050.
  
  Serial.println("Calculating offsets, do not move MPU6050");
  delay(1000);
  // mpu.upsideDownMounting = true; // Uncomment this line if the MPU6050 is mounted upside-down.
  mpu.calcOffsets(); // Gyro and accelerometer.
  Serial.println("Done!\n");
}

void printYaw() {
  mpu.update();
  
  float yaw = getYaw();
  
  Serial.print("Yaw: ");
  Serial.println(yaw);
}

float getYaw() {
  float yaw = mpu.getAngleZ();
  if (yaw < 0) {
    yaw += 360; 
  }
  return yaw;
}

#include "I2Cdev.h"
#include "MPU6050.h"//mpu library
#include "Wire.h"//i2c library
#define TCAADDR 0x70 //mux address
​
MPU6050 sensor_1;
MPU6050 sensor_2;
MPU6050 sensor_3;
​
int ax1, ay1, az1, ax2, ay2, az2, ax3, ay3, az3;
//MPU address
#define MPU 0x68
​
void tcaselect(uint8_t i)//read mux buses
{
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}
​
void setup() {
  Serial.begin(57600);
  
  Wire.begin();           //Ininit I2C  and serial port
  tcaselect(1);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
 
  
  if (sensor_1.testConnection()) Serial.println("Sensor1 started successfully");
  else Serial.println("Error detecting sensor1");
​
  tcaselect(2);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  if (sensor_2.testConnection()) Serial.println("Sensor2 started successfully");
  else Serial.println("Error detecting sensor2");
​
  tcaselect(3);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
 
  
  if (sensor_3.testConnection()) Serial.println("Sensor3 started successfully");
  else Serial.println("Error detecting sensor3");
​
}
​
void loop() {
  tcaselect(1);
  Wire.beginTransmission(MPU); 
  sensor_1.getAcceleration(&ax1, &ay1, &az1);
  Wire.write(0x3B);  // register MPU6050  starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);// From 0x3B, it gets 6 registers 
  ax1=Wire.read()<<8|Wire.read();//Each value uses 2 registers
  ay1=Wire.read()<<8|Wire.read();
  az1=Wire.read()<<8|Wire.read();
  float accel_ang_x1=atan(ax1/sqrt(pow(ay1,2) + pow(az1,2)))*(180.0/3.14);//x angle
  float accel_ang_y1=atan(ay1/sqrt(pow(ax1,2) + pow(az1,2)))*(180.0/3.14);//y angle
  Serial.print("Inclination in X1:");
  Serial.println(accel_ang_x1); 
  
  Serial.print("Incliniation in Y1:");
  Serial.println(accel_ang_y1);
​
 
​
  tcaselect(2);
  Wire.beginTransmission(MPU); 
  sensor_1.getAcceleration(&ax2, &ay2, &az2);
  Wire.write(0x3B);  // register MPU6050  starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);// From 0x3B, it gets 6 registers 
  ax1=Wire.read()<<8|Wire.read();//Each value uses 2 registers
  ay1=Wire.read()<<8|Wire.read();
  az1=Wire.read()<<8|Wire.read();
  float accel_ang_x2=atan(ax2/sqrt(pow(ay2,2) + pow(az2,2)))*(180.0/3.14);//x angle
  float accel_ang_y2=atan(ay2/sqrt(pow(ax2,2) + pow(az2,2)))*(180.0/3.14);//y angle
  Serial.print("Inclination in X2:");
  Serial.println(accel_ang_x2); 
  
  Serial.print("Inclination in Y2:");
  Serial.println(accel_ang_y2);
​
  tcaselect(3);
  Wire.beginTransmission(MPU); 
  sensor_1.getAcceleration(&ax3, &ay3, &az3);
  Wire.write(0x3B);  // register MPU6050  starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);// From 0x3B, it gets 6 registers 
  ax1=Wire.read()<<8|Wire.read();//Each value uses 2 registers
  ay1=Wire.read()<<8|Wire.read();
  az1=Wire.read()<<8|Wire.read();
  float accel_ang_x3=atan(ax3/sqrt(pow(ay3,2) + pow(az3,2)))*(180.0/3.14);//x angle
  float accel_ang_y3=atan(ay3/sqrt(pow(ax3,2) + pow(az3,2)))*(180.0/3.14);//y angle
  Serial.print("Inclination in X3:");
  Serial.println(accel_ang_x3); 
  
  Serial.print("Inclination in Y3:");
  Serial.println(accel_ang_y3);
​
​
  delay(500);
}

#include "I2Cdev.h"
#include "MPU6050.h"//mpu library
#include "Wire.h"//i2c library
#define TCAADDR 0x70 //mux address

MPU6050 sensor_1; 
MPU6050 sensor_2; 
MPU6050 sensor_3; 
MPU6050 sensor_4;
MPU6050 sensor_5; 
MPU6050 sensor_6; 
MPU6050 sensor_7; 
MPU6050 sensor_8;


int16_t ax1, ay1, az1, ax2, ay2, az2, ax3, ay3, az3, ax4, ay4, az4;
int16_t ax5, ay5, az5, ax6, ay6, az6, ax7, ay7, az7, ax8, ay8, az8;

const uint16_t MPU = 0x68;  
uint8_t size = 6;

void tcaselect(uint8_t i)//read mux buses
{
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void setup() {
  Wire.begin();           //Ininit I2C  and serial port
  Serial.begin(115200);

  //Sensor 1 and 2 in unit 1
  tcaselect(0);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  if (sensor_1.testConnection()) Serial.println("Sensor 1 started successfully");
  else Serial.println("Error detecting sensor1"); 

  sensor_1.setXAccelOffset(-4810);
  sensor_1.setYAccelOffset(-2600);
  sensor_1.setZAccelOffset(1867);


  tcaselect(1);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  if (sensor_2.testConnection()) Serial.println("Sensor2 started successfully");
  else Serial.println("Error detecting sensor2"); 

  sensor_2.setXAccelOffset(1043);
  sensor_2.setYAccelOffset(820);
  sensor_2.setZAccelOffset(1099);
 
  //Sensor 3 and 4 in unit 2
  tcaselect(2);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  if (sensor_3.testConnection()) Serial.println("Sensor3 started successfully");
  else Serial.println("Error detecting sensor3"); 

  sensor_3.setXAccelOffset(-753);
  sensor_3.setYAccelOffset(-624);
  sensor_3.setZAccelOffset(2338);
  
  tcaselect(3);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  if (sensor_4.testConnection()) Serial.println("Sensor4 started successfully");
  else Serial.println("Error detecting sensor4"); 

  sensor_4.setXAccelOffset(287);
  sensor_4.setYAccelOffset(4116);
  sensor_4.setZAccelOffset(1173);
  
  //Sensor 5 and 6 in unit 3
  tcaselect(4);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  if (sensor_5.testConnection()) Serial.println("Sensor5 started successfully");
  else Serial.println("Error detecting sensor5"); 

  sensor_5.setXAccelOffset(1880 );
  sensor_5.setYAccelOffset(-432);
  sensor_5.setZAccelOffset(345);
  
  tcaselect(5);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  if (sensor_6.testConnection()) Serial.println("Sensor6 started successfully");
  else Serial.println("Error detecting sensor6"); 

  sensor_6.setXAccelOffset(-3999);
  sensor_6.setYAccelOffset(-2244 );
  sensor_6.setZAccelOffset(1117);

  //Sensor 7 and 8 in unit 4
  tcaselect(6);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  if (sensor_7.testConnection()) Serial.println("Sensor7 started successfully");
  else Serial.println("Error detecting sensor7"); 

  sensor_7.setXAccelOffset(-3600);
  sensor_7.setYAccelOffset(470);
  sensor_7.setZAccelOffset(916);
  
  tcaselect(7);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  if (sensor_8.testConnection()) Serial.println("Sensor8 started successfully");
  else Serial.println("Error detecting sensor8"); 

  sensor_8.setXAccelOffset(-3449);
  sensor_8.setYAccelOffset(-887);
  sensor_8.setZAccelOffset(1326);



}

void loop() { 
  tcaselect(0);
  Wire.beginTransmission(MPU);  
  ax1 = sensor_1.getAccelerationX();
  ay1 = sensor_1.getAccelerationY();
  az1 = sensor_1.getAccelerationZ();
  Wire.write(0x3B);  // register MPU6050  starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,size,true);// From 0x3B, it gets 6 registers 
  ax1=Wire.read()<<8|Wire.read();//Each value uses 2 registers
  ay1=Wire.read()<<8|Wire.read();
  az1=Wire.read()<<8|Wire.read();

  //sensor_print("X1: ", " Y1: ", " Z1: ", ax1, ay1, az1);
  

  tcaselect(1);
  Wire.beginTransmission(MPU); 
  ax2 = sensor_2.getAccelerationX();
  ay2 = sensor_2.getAccelerationY();
  az2 = sensor_2.getAccelerationZ();
  Wire.write(0x3B);  // register MPU6050  starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,size,true);// From 0x3B, it gets 6 registers 
  ax2=Wire.read()<<8|Wire.read();//Each value uses 2 registers
  ay2=Wire.read()<<8|Wire.read();
  az2=Wire.read()<<8|Wire.read();

  //sensor_print(" X2: ", " Y2: ", " Z2: ", ax2, ay2, az2);

  sensor_differential_print("Unit 1 X: ", " Y: ", " Z: ", ax1, ay1, az1, ax2, ay2, az2);

  tcaselect(2);
  Wire.beginTransmission(MPU); 
  ax3 = sensor_3.getAccelerationX();
  ay3 = sensor_3.getAccelerationY();
  az3 = sensor_3.getAccelerationZ();
  Wire.write(0x3B);  // register MPU6050  starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,size,true);// From 0x3B, it gets 6 registers 
  ax3=Wire.read()<<8|Wire.read();//Each value uses 2 registers
  ay3=Wire.read()<<8|Wire.read();
  az3=Wire.read()<<8|Wire.read();

  //sensor_print(" X3: ", " Y3: ", " Z3: ", ax3, ay3, az3);

  tcaselect(3);
  Wire.beginTransmission(MPU);
  ax4 = sensor_4.getAccelerationX();
  ay4 = sensor_4.getAccelerationY();
  az4 = sensor_4.getAccelerationZ();
  
  Wire.write(0x3B);  // register MPU6050  starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,size,true);// From 0x3B, it gets 6 registers 
  ax4=Wire.read()<<8|Wire.read();//Each value uses 2 registers
  ay4=Wire.read()<<8|Wire.read();
  az4=Wire.read()<<8|Wire.read();

  //sensor_print(" X4: ", " Y4: ", " Z4: ", ax4, ay4, az4);
  sensor_differential_print(" Unit 2 X: ", " Y: ", " Z: ", ax3, ay3, az3, ax4, ay4, az4);
  

  tcaselect(4);
  Wire.beginTransmission(MPU); 
  ax5 = sensor_5.getAccelerationX();
  ay5 = sensor_5.getAccelerationY();
  az5 = sensor_5.getAccelerationZ();
  Wire.write(0x3B);  // register MPU6050  starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,size,true);// From 0x3B, it gets 6 registers 
  ax5=Wire.read()<<8|Wire.read();//Each value uses 2 registers
  ay5=Wire.read()<<8|Wire.read();
  az5=Wire.read()<<8|Wire.read();

  //sensor_print(" X5: ", " Y5: ", " Z5: ", ax5, ay5, az5);
  

  tcaselect(5);
  Wire.beginTransmission(MPU); 
  ax6 = sensor_6.getAccelerationX();
  ay6 = sensor_6.getAccelerationY();
  az6 = sensor_6.getAccelerationZ();
  Wire.write(0x3B);  // register MPU6050  starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,size,true);// From 0x3B, it gets 6 registers 
  ax6=Wire.read()<<8|Wire.read();//Each value uses 2 registers
  ay6=Wire.read()<<8|Wire.read();
  az6=Wire.read()<<8|Wire.read();

  //sensor_print(" X6: ", " Y6: ", " Z6: ", ax6, ay6, az6);

  sensor_differential_print("Unit 3 X: ", " Y: ", " Z: ", ax5, ay5, az5, ax6, ay6, az6);


  tcaselect(6);
  Wire.beginTransmission(MPU); 
  ax7 = sensor_7.getAccelerationX();
  ay7 = sensor_7.getAccelerationY();
  az7 = sensor_7.getAccelerationZ();
  Wire.write(0x3B);  // register MPU6050  starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,size,true);// From 0x3B, it gets 6 registers 
  ax7=Wire.read()<<8|Wire.read();//Each value uses 2 registers
  ay7=Wire.read()<<8|Wire.read();
  az7=Wire.read()<<8|Wire.read();

  //sensor_print(" X7: ", " Y7: ", " Z7: ", ax7, ay7, az7);
  

  tcaselect(7);
  Wire.beginTransmission(MPU); 
  ax8 = sensor_8.getAccelerationX();
  ay8 = sensor_8.getAccelerationY();
  az8 = sensor_8.getAccelerationZ();
  Wire.write(0x3B);  // register MPU6050  starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,size,true);// From 0x3B, it gets 6 registers 
  ax8=Wire.read()<<8|Wire.read();//Each value uses 2 registers
  ay8=Wire.read()<<8|Wire.read();
  az8=Wire.read()<<8|Wire.read();

  //sensor_print(" X8: ", " Y8: ", " Z8: ", ax8, ay8, az8);

  sensor_differential_print("Unit 4 X: ", " Y: ", " Z: ", ax7, ay7, az7, ax8, ay8, az8);

  //Serial.println();
  


}


void sensor_print(char x[], char y[], char z[], int16_t ax, int16_t ay, int16_t az){ //Function to print x,y,z values for each sensor
  Serial.print(x);
  Serial.print(ax/16384.0);
      
  Serial.print(y);
  Serial.print(ay/16384.0);
      
  Serial.print(z);
  Serial.print(az/16384.0);
}

void sensor_differential_print(char x[], char y[], char z[], int16_t ax, int16_t ay, int16_t az, int16_t bx, int16_t by, int16_t bz){ //Function to print differentials for each unit (consisting of 2 sensors)
  Serial.print(",");
  Serial.print(x);
  Serial.print(",");
  Serial.print((ax-bz)/16384.0);
  Serial.print(",");
      
  Serial.print(y);
  Serial.print(",");
  Serial.print((ay+by)/16384.0);
  Serial.print(",");
      
  Serial.print(z);
  Serial.print(",");
  Serial.println(-(az-bx)/16384.0);
}

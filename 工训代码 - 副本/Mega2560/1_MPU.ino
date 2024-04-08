#include <JY901.h>   //调用陀螺仪库
float MPU_val;       //存储陀螺仪数据

//陀螺仪读值
void MPU() {
  while (Serial.available()) {
    JY901.CopeSerialData(Serial.read()); //Call JY901 data cope function
//    delay(2);
  }
  MPU_val=(float)JY901.stcAngle.Angle[2]/32768*180;
  Serial.println(MPU_val);
  }
//陀螺仪读值

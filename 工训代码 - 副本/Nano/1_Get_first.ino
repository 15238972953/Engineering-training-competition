void Servo_Place_0(){  //m    抓取位置0的物料
  Servo_5.write(55);
  Servo_4.write(80);
  Servo_3.write(37);
  Servo_2.write(100);
  Servo_1.write(90);  //
  delay(500);

  Servo_5.write(55);
  Servo_4.write(80);
  Servo_3.write(41);
  Servo_2.write(100);
  Servo_1.write(90);  //
  delay(500);

  Servo_5.write(55);
  Servo_4.write(105);
  Servo_3.write(41);
  Servo_2.write(100);
  Servo_1.write(90);  //
  delay(500);

  Servo_5.write(55);
  Servo_4.write(105);
  Servo_3.write(41);
  Servo_2.write(100);
  Servo_1.write(40);  //
  delay(500);
  
  Servo_5.write(55);
  Servo_4.write(105);
  Servo_3.write(41);
  Servo_2.write(100);
  Servo_1.write(40);  //
  delay(500);

  Servo_5.write(90);
  Servo_4.write(90);
  Servo_3.write(41);
  Servo_2.write(100);
  Servo_1.write(40);  //
  delay(500);

  Serial.print('m');
}

void Servo_Place_1(){  //n  抓取位置1的物料
  Servo_5.write(35);
  Servo_4.write(80);
  Servo_3.write(37);
  Servo_2.write(110);
  Servo_1.write(90);  //
  delay(500);

  Servo_5.write(35);
  Servo_4.write(80);
  Servo_3.write(10);
  Servo_2.write(110);
  Servo_1.write(90);  //
  delay(500);

  Servo_5.write(35);
  Servo_4.write(87);
  Servo_3.write(10);
  Servo_2.write(110);
  Servo_1.write(90);  //
  delay(500);
  
  Servo_5.write(35);
  Servo_4.write(87);
  Servo_3.write(10);
  Servo_2.write(110);
  Servo_1.write(40);  //
  delay(500);

  Servo_5.write(35);
  Servo_4.write(87);
  Servo_3.write(30);
  Servo_2.write(110);
  Servo_1.write(40);  //
  delay(500);

  Servo_5.write(90);
  Servo_4.write(90);
  Servo_3.write(41);
  Servo_2.write(100);
  Servo_1.write(40);  //
  delay(500);
  
  Serial.print('n');
}

void Servo_Place_2(){  //o   夹取位置2的物料
  Servo_5.write(8);
  Servo_4.write(80);
  Servo_3.write(37);
  Servo_2.write(103);
  Servo_1.write(90);  //
  delay(500);

  Servo_5.write(8);
  Servo_4.write(80);
  Servo_3.write(16);
  Servo_2.write(103);
  Servo_1.write(90);  //
  delay(500);

  Servo_5.write(8);
  Servo_4.write(89);
  Servo_3.write(16);
  Servo_2.write(103);
  Servo_1.write(90);  //
  delay(500);
  
  Servo_5.write(8);
  Servo_4.write(89);
  Servo_3.write(16);
  Servo_2.write(103);
  Servo_1.write(40);  //
  delay(500);

  Servo_5.write(8);
  Servo_4.write(89);
  Servo_3.write(40);
  Servo_2.write(103);
  Servo_1.write(40);  //
  delay(500);

  Servo_5.write(90);
  Servo_4.write(90);
  Servo_3.write(41);
  Servo_2.write(100);
  Servo_1.write(40);  //
  delay(500);

  Serial.print('o');
}

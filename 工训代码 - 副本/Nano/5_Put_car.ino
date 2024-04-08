void Servo_Put_Blue(){  //s  放置蓝色物料至车上
  Servo_5.write(110);
  Servo_4.write(85);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(40);  //
  delay(500);

  Servo_5.write(110);
  Servo_4.write(100);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(40);  //
  delay(500);

  Servo_5.write(110);
  Servo_4.write(100);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(75);   //
  delay(500);

  Servo_5.write(110);
  Servo_4.write(80);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(90);  //
  delay(500);

  Servo_5.write(90);
  Servo_4.write(80);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(90);   //
  delay(500);

  Serial.print('s');
}




void Servo_Put_Red(){  //S   放置红色物料至车上
  Servo_5.write(90);
  Servo_4.write(85);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(40);  //
  delay(500);

  Servo_5.write(90);
  Servo_4.write(100);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(40);  //
  delay(500);

  Servo_5.write(90);
  Servo_4.write(100);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(75);   //
  delay(500);

  Servo_5.write(90);
  Servo_4.write(80);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(90);  //
  delay(500);

  Servo_5.write(90);
  Servo_4.write(80);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(90);   //
  delay(500);

  Serial.print('S');
}




void Servo_Put_Greed(){  //t  放置绿色物料至车上
  Servo_5.write(70);
  Servo_4.write(85);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(40);  //
  delay(500);

  Servo_5.write(70);
  Servo_4.write(100);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(40);  //
  delay(500);

  Servo_5.write(70);
  Servo_4.write(100);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(75);   //
  delay(500);

  Servo_5.write(70);
  Servo_4.write(80);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(90);  //
  delay(500);

  Servo_5.write(90);
  Servo_4.write(80);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(90);   //
  delay(500);

  Serial.print('t');
}

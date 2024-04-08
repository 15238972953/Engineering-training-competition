void Servo_Place_345_Get(){  //T   下层物料爪子加紧
  Servo_1.write(40);
  delay(500);
  Serial.print('T');
}

void Servo_Place_3(){  //M  抓取位置3物料，退车后的预备下降
  Servo_5.write(55);
  Servo_4.write(80);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(90);  //
  delay(500);

  Servo_5.write(55);
  Servo_4.write(80);
  Servo_3.write(37);
  Servo_2.write(132);
  Servo_1.write(90);  //
  delay(500);
  
  Servo_5.write(55);
  Servo_4.write(123);
  Servo_3.write(37);
  Servo_2.write(132);
  Servo_1.write(90);  //
  delay(500);

  Serial.print('M');
}



void Servo_Place_4(){  //N   抓取位置4物料，退车后的预备下降
  Servo_5.write(33);
  Servo_4.write(80);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(90);  //
  delay(500);

  Servo_5.write(33);
  Servo_4.write(80);
  Servo_3.write(37);
  Servo_2.write(141);
  Servo_1.write(90);  //
  delay(500);
  
  Servo_5.write(33);
  Servo_4.write(109);
  Servo_3.write(2);
  Servo_2.write(141);
  Servo_1.write(90);  //
  delay(500);

  Serial.print('N');
}



void Servo_Place_5(){  //O   抓取位置5物料，退车后的预备下降
  Servo_5.write(8);
  Servo_4.write(80);
  Servo_3.write(37);
  Servo_2.write(30);
  Servo_1.write(90);  //
  delay(500);

  Servo_5.write(8);
  Servo_4.write(80);
  Servo_3.write(37);
  Servo_2.write(141);
  Servo_1.write(90);  //
  delay(500);
  
  Servo_5.write(8);
  Servo_4.write(112);
  Servo_3.write(10);
  Servo_2.write(141);
  Servo_1.write(90);  //
  delay(500);

  Serial.print('O');
}



void Servo_Place_3_Up(){  //U   抓取位置3物料，退车后的抬起到车上
  Servo_5.write(55);
  Servo_4.write(105);
  Servo_3.write(60);
  Servo_2.write(100);
  Servo_1.write(40);  //
  delay(500);
  
  Servo_5.write(90);
  Servo_4.write(105);
  Servo_3.write(60);
  Servo_2.write(100);
  Servo_1.write(40);  //
  delay(500);

  Servo_5.write(90);
  Servo_4.write(90);
  Servo_3.write(41);
  Servo_2.write(100);
  Servo_1.write(40);  //
  delay(500);
}



void Servo_Place_4_Up(){  //v   抓取位置4物料，退车后的抬起到车上
  Servo_5.write(35);
  Servo_4.write(87);
  Servo_3.write(30);
  Servo_2.write(110);
  Servo_1.write(40);  //
  delay(500);
  
  Servo_5.write(90);
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
}



void Servo_Place_5_Up(){  //V  抓取位置5物料，退车后的抬起到车上
  Servo_5.write(8);
  Servo_4.write(89);
  Servo_3.write(40);
  Servo_2.write(103);
  Servo_1.write(40);  //
  delay(500);
  
  Servo_5.write(90);
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
}

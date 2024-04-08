int Read_HMI() {
}

void HMI_Print_Mission(String Mission) {
  String HMI_String1 = "t0.txt=\"";
  String HMI_String2 = "\"";
  String HMI_String = "";
  HMI_String+=HMI_String1;
  HMI_String+=Mission;
  HMI_String+=HMI_String2;
  Serial2.print(HMI_String); //指令
//  Serial.print(HMI_String); //指令
  Serial2.write(0XFF);         //结束符
  Serial2.write(0XFF);
  Serial2.write(0XFF);
  HMI_String="";
}

void HMI_Print_Place(String Place) {
  String HMI_String1 = "t1.txt=\"";
  String HMI_String2 = "\"";
  String HMI_String = "";
  HMI_String+=HMI_String1;
  HMI_String+=Place;
  HMI_String+=HMI_String2;
  Serial2.print(HMI_String); //指令
//  Serial.print(HMI_String); //指令
  Serial2.write(0XFF);         //结束符
  Serial2.write(0XFF);
  Serial2.write(0XFF);
  HMI_String="";
}

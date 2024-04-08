#include <SoftwareSerial.h>           // 软串口库
SoftwareSerial MV_Serial(4, 2);
//SoftwareSerial Wifi_Serial(A0, A1);

String MV_Read = "";
String Mission = "";
String Place = "";

#include<Servo.h>

Servo Servo_1;
Servo Servo_2;
Servo Servo_3;
Servo Servo_4;
Servo Servo_5;

int Servo_val_5=90;
int Servo_val_4=135;
int Servo_val_3=150;
int Servo_val_2=90;
int Servo_val_1=90;

//int Servo_val_5=90;
//int Servo_val_4=90;
//int Servo_val_3=90;
//int Servo_val_2=90;
//int Servo_val_1=90;

char Serial_Read;

#define Servo_Set_      1
#define Servo_Move_     2
byte systemMode = Servo_Move_;

void setup() {
  Serial.begin(9600);
  MV_Serial.begin(9600);
  
  Servo_1.attach(6);
  Servo_2.attach(10);
  Servo_3.attach(9);
  Servo_4.attach(5);
  Servo_5.attach(11);
  
  Servo_1.write(Servo_val_1);
  Servo_2.write(Servo_val_2);
  Servo_3.write(Servo_val_3);
  Servo_4.write(Servo_val_4);
  Servo_5.write(Servo_val_5);
}

void loop() {
  while(MV_Serial.available()>0){
    MV_Read = MV_Serial.readStringUntil('\n');
  }

  MV_read();
  
  while(Serial.available()>0){
    Serial_Read = (char)Serial.read();}
    
  if(Serial_Read=='1'){
    MV_Serial.print('1');
    Serial_Read=' ';
  }

  if(Serial_Read=='2'){
    MV_Serial.print('2');
    Serial_Read=' ';
  }
  
  if(Serial_Read=='k') {
    systemMode=Servo_Set_;
  }

  if(Serial_Read=='K') {
    systemMode=Servo_Move_;
  }
   
  runMode();
}

void runMode(){
  if (systemMode == Servo_Set_){    
    Servo_Set();               
  }

  if (systemMode == Servo_Move_){
    Servo_Move();
  }
}

//OpenMV读取函数
void MV_read(){
  if(MV_Read.length()==7) {
    Serial.print(MV_Read+'\n');
    for(int i=0;i<7;i++){
      if(MV_Read[i]!='+'){
        Mission+=MV_Read[i];
      }
    }
    MV_Read="";
  }
  if(MV_Read.length()==6) {
    Serial.print(MV_Read+'\n');
    Place=MV_Read;
    MV_Read="";
  }
}
//OpenMV读取函数


void Servo_Move(){
  switch (Serial_Read){
    case 'l':  //扫码位置
      Servo_Mission();
      Serial_Read= 'K';
      break;
    
    case 'L':  //颜色识别位置
      Servo_Place();
      Serial_Read= 'K';
      break;
      
    case 'm':  //抓取左上
      Servo_Place_0();
      Serial_Read= 'K';
      break;

    case 'n':  //抓取中上
      Servo_Place_1();
      Serial_Read= 'K';
      break;

    case 'o':  //抓取右上
      Servo_Place_2();
      Serial_Read= 'K';
      break;

    case 'M':  //抓取左下
      Servo_Place_3();
      Serial_Read= 'K';
      break;

    case 'N':  //抓取中下
      Servo_Place_4();
      Serial_Read= 'K';
      break;

    case 'O':  //抓取右下
      Servo_Place_5();
      Serial_Read= 'K';
      break;

    case 'p':  //放置蓝色第一层
      Servo_Put_Blue_1();
      Serial_Read= 'K';
      break;

    case 'P':  //放置蓝色第二层
      Servo_Put_Blue_2();
      Serial_Read= 'K';
      break;

    case 'q':  //放置红色第一层
      Servo_Put_Red_1();
      Serial_Read= 'K';
      break;

    case 'Q':  //放置红色第二层
      Servo_Put_Red_2();
      Serial_Read= 'K';
      break;

    case 'r':  //放置绿色第一层
      Servo_Put_Greed_1();
      Serial_Read= 'K';
      break;

    case 'R':  //放置绿色第二层
      Servo_Put_Greed_2();
      Serial_Read= 'K';
      break;

    case 's':  //放置蓝色在车上
      Servo_Put_Blue();
      Serial_Read= 'K';
      break;

    case 'S':  //放置红色在车上
      Servo_Put_Red();
      Serial_Read= 'K';
      break;

    case 't':  //放置绿色在车上
      Servo_Put_Greed();
      Serial_Read= 'K';
      break;

    case 'T':  //位置345的抓取
      Servo_Place_345_Get();
      Serial_Read= 'K';
      break;

    case 'U':
      Servo_Place_3_Up();
      Serial_Read= 'K';
      break;

    case 'v':
      Servo_Place_4_Up();
      Serial_Read= 'K';
      break;

    case 'V':
      Servo_Place_5_Up();
      Serial_Read= 'K';
      break;
  }
}

void Servo_Set(){
  switch (Serial_Read){
    case 'a':
      Servo_val_1-=1;
//      if(Servo_val_1<80) Servo_val_1=80;
      Servo_1.write(Servo_val_1);
      Serial.print("Servo_val_1=");Serial.println(Servo_val_1);
      Serial_Read= 'k';
      break;
    
    case 'A':
      Servo_val_1-=10;
//      if(Servo_val_1<80) Servo_val_1=80;
      Servo_1.write(Servo_val_1);
      Serial.print("Servo_val_1=");Serial.println(Servo_val_1);
      Serial_Read= 'k';
      break;
      
    case 'b':
      Servo_val_1+=1;
//      if(Servo_val_1>150) Servo_val_1=150;
      Servo_1.write(Servo_val_1);
      Serial.print("Servo_val_1=");Serial.println(Servo_val_1);
      Serial_Read= 'k';
      break;

    case 'B':
      Servo_val_1+=10;
//      if(Servo_val_1>150) Servo_val_1=150;
      Servo_1.write(Servo_val_1);
      Serial.print("Servo_val_1=");Serial.println(Servo_val_1);
      Serial_Read= 'k';
      break;

    case 'c':
      Servo_val_2-=1;
//      if(Servo_val_2>270) Servo_val_2=270;
      Servo_2.write(Servo_val_2);
      Serial.print("Servo_val_2=");Serial.println(Servo_val_2);
      Serial_Read= 'k';
      break;

    case 'C':
      Servo_val_2-=10;
//      if(Servo_val_2>270) Servo_val_2=270;
      Servo_2.write(Servo_val_2);
      Serial.print("Servo_val_2=");Serial.println(Servo_val_2);
      Serial_Read= 'k';
      break;

    case 'd':
      Servo_val_2+=1;
//      if(Servo_val_2<0) Servo_val_2=0;
      Servo_2.write(Servo_val_2);
      Serial.print("Servo_val_2=");Serial.println(Servo_val_2);
      Serial_Read= 'k';
      break;

    case 'D':
      Servo_val_2+=10;
//      if(Servo_val_2<0) Servo_val_2=0;
      Servo_2.write(Servo_val_2);
      Serial.print("Servo_val_2=");Serial.println(Servo_val_2);
      Serial_Read= 'k';
      break;

    case 'e':
      Servo_val_3-=1;
//      if(Servo_val_3>190) Servo_val_3=190;
      Servo_3.write(Servo_val_3);
      Serial.print("Servo_val_3=");Serial.println(Servo_val_3);
      Serial_Read= 'k';
      break;

    case 'E':
      Servo_val_3-=10;
//      if(Servo_val_3>190) Servo_val_3=190;
      Servo_3.write(Servo_val_3);
      Serial.print("Servo_val_3=");Serial.println(Servo_val_3);
      Serial_Read= 'k';
      break;

    case 'f':
      Servo_val_3+=1;
//      if(Servo_val_3<80) Servo_val_3=80;
      Servo_3.write(Servo_val_3);
      Serial.print("Servo_val_3=");Serial.println(Servo_val_3);
      Serial_Read= 'k';
      break;

    case 'F':
      Servo_val_3+=10;
//      if(Servo_val_3<80) Servo_val_3=80;
      Servo_3.write(Servo_val_3);
      Serial.print("Servo_val_3=");Serial.println(Servo_val_3);
      Serial_Read= 'k';
      break;

    case 'g':
      Servo_val_4+=1;
//      if(Servo_val_4>270) Servo_val_4=270;
      Servo_4.write(Servo_val_4);
      Serial.print("Servo_val_4=");Serial.println(Servo_val_4);
      Serial_Read= 'k';
      break;

    case 'G':
      Servo_val_4+=10;
//      if(Servo_val_4<0) Servo_val_4=0;
      Servo_4.write(Servo_val_4);
      Serial.print("Servo_val_4=");Serial.println(Servo_val_4);
      Serial_Read= 'k';
      break;

    case 'h':
      Servo_val_4-=1;
//      if(Servo_val_4<0) Servo_val_4=0;
      Servo_4.write(Servo_val_4);
      Serial.print("Servo_val_4=");Serial.println(Servo_val_4);
      Serial_Read= 'k';
      break;

    case 'H':
      Servo_val_4-=10;
//      if(Servo_val_4<0) Servo_val_4=0;
      Servo_4.write(Servo_val_4);
      Serial.print("Servo_val_4=");Serial.println(Servo_val_4);
      Serial_Read= 'k';
      break;

    case 'i':
      Servo_val_5+=1;
//      if(Servo_val_5<0) Servo_val_5=0;
      Servo_5.write(Servo_val_5);
      Serial.print("Servo_val_5=");Serial.println(Servo_val_5);
      Serial_Read= 'k';
      break;

    case 'I':
      Servo_val_5+=10;
//      if(Servo_val_5<0) Servo_val_5=0;
      Servo_5.write(Servo_val_5);
      Serial.print("Servo_val_5=");Serial.println(Servo_val_5);
      Serial_Read= 'k';
      break;

    case 'j':
      Servo_val_5-=1;
//      if(Servo_val_5<0) Servo_val_5=0;
      Servo_5.write(Servo_val_5);
      Serial.print("Servo_val_5=");Serial.println(Servo_val_5);
      Serial_Read= 'k';
      break;

    case 'J':
      Servo_val_5-=10;
//      if(Servo_val_5<0) Servo_val_5=0;
      Servo_5.write(Servo_val_5);
      Serial.print("Servo_val_5=");Serial.println(Servo_val_5);
      Serial_Read= 'k';
      break;
  }
}

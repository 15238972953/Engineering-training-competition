#define ADVANCE_ 0   // 前进模式
#define Advance_ 1   // 不带计数前进模式
#define BACK_    2   // 后退模式
#define Back_    3   // 不带计数后退模式
#define LEFT_    4   // 左移模式
#define Left_    5   // 不带计数左移模式
#define RIGHT_   6   // 右移模式
#define Right_   7   // 不带计数右移模式
#define STOP_    8   // 停止模式
#define Start_   9   // 开始模式
#define FOUR_STRAIGHTEN  10  // 四向摆正
#define THREE_STRAIGHTEN 11  // 三向摆正
byte systemMode = STOP_;    // 系统模式标志

int Speed_High =450 ;  // 速度值(快)
int Speed_Low =200;    // 速度值(慢)
int Speed_LowLow =150; // 速度值(慢)
int Spd;

String Target_Value;   //串口读值
int miss;
int front_base,after_base,left_base,right_base;
int front_BASE,after_BASE,left_BASE,right_BASE;
int count_X =0;
int count_Y =0;

int stage_Mission_Nano=1;
int stage_Mission_OpenMV=1;
int stage_Place_Nano=1;
int stage_Place_OpenMV=1;

int stage_Get_012=1;
int stage_Get_3=1;
int stage_Get_4=1;
int stage_Get_5=1;

int stage_Put_1=1;
int stage_Put_2=1;

int stage_1o1=1;
int stage_1o6=1;
int stage_2o6=1;
int stage_7o4=1;

int stage_Place_Up=0;

#define Wait_    0
#define Mission_ 1
#define Servo_   2
char HMI_Read='L';
byte HMI_Mode = Wait_;

String Nano_Read= "";
String MV_Read = "";
String Mission = "";
String Place = "";

char same=0;//上层搬运判断符

void setup() {
  Serial.begin(9600);      //打开串口
  Serial2.begin(9600);      //打开串口
  Serial3.begin(9600);      //打开串口
  
  Timer5_();
  dianji_Interrupt();
  MOTOR_init();
  XUNJI_init();
}

void loop() { 
  while(Serial2.available()>0){
    HMI_Read = (char)Serial2.read();
  }

  while(Serial3.available()>0){
    Nano_Read = Serial3.readStringUntil('\n');
  }
  
  Nano_read();
  
  if(HMI_Read=='L') {
    zuobiao_detachInterrupt();
    HMI_Mode=Wait_;
  }
  
  if(HMI_Read=='l') {
//    count_X=0;
//    count_Y=0;
    zuobiao_attachInterrupt();
    HMI_Mode=Mission_;
  }
  
  if(HMI_Read=='k') {
    Serial3.print('k');
    HMI_Mode=Servo_;
  }

  if(HMI_Read=='m') {
    Serial3.print('1');
    HMI_Read='L';
  }

  if(HMI_Read=='M') {
    Serial3.print('2');
    HMI_Read='L';
  }

  if(HMI_Mode==Wait_) {
    STOP();
  }

  if(HMI_Mode==Mission_) {
    MISSION();
  }
  
  if(HMI_Mode==Servo_) {
    Servo_Set();
  }
}

void MISSION(){
//  if(count_X==0&&count_Y==0) {
//      Spd=Speed_Low;
//      systemMode=Left_;
//    }
//
//  if(count_X==1&&count_Y==0) {
//      Spd=Speed_High;
//      systemMode=ADVANCE_;
//    }
//
//  if(count_X==1&&count_Y==1) {
//      Spd=Speed_High;
//      systemMode=ADVANCE_;
//    }
//
//  if(count_X==1&&count_Y==5) {
//      Spd=Speed_Low;
//      systemMode=ADVANCE_;
//    }
//
//  if(count_X==1&&count_Y==7) {
//      Spd=Speed_High;
//      systemMode=LEFT_;
//    }
//
//  if(count_X==5&&count_Y==7) {
//      Spd=Speed_Low;
//      systemMode=LEFT_;
//    }
//
//  if(count_X==7&&count_Y==7) {
//      Spd=Speed_High;
//      systemMode=BACK_;
//    }
//
//  if(count_X==7&&count_Y==3) {
//      Spd=Speed_Low;
//      systemMode=BACK_;
//    }
//
//  if(count_X==7&&count_Y==1) {
//      Spd=Speed_High;
//      systemMode=RIGHT_;
//    }
//
//  if(count_X==3&&count_Y==1) {
//      Spd=Speed_Low;
//      systemMode=RIGHT_;
//    }
////跑图


    if(count_X==0&&count_Y==0) {
      Spd=Speed_Low;
      systemMode=Start_;
    }//开机首先慢速左移到黑线上
    
    if(count_X==1&&count_Y==0) {
      if(stage_Mission_Nano==1){
        Serial3.print('l');  //给Nano发送准备扫码
        stage_Mission_Nano=2;
      }
      if(stage_Mission_OpenMV==1){
        Serial3.print('1');  //给OpenMV发送扫码指令
        stage_Mission_OpenMV=2;
      }
      Spd=Speed_High;
      systemMode=ADVANCE_;
    }//上线开始前移，准备扫码

    if(count_X==1&&count_Y==1) {
      if(stage_1o1==1){
        Spd=Speed_Low;
        systemMode=ADVANCE_;
      }//第一次到达(1,1)后前移
      if(stage_1o1==2){
        stage_1o1=3;
        Spd=Speed_Low;
        RIGHT(Spd,0,0);
        delay(750);
        BACK(Spd,0,0);
        delay(750);
        HMI_Read='H';
        systemMode = STOP_;
      }//第二次到达(1,1)后返回
    }

    if(count_X==1&&count_Y==2) {
      stage_1o1=2;
      Spd=Speed_LowLow;
      systemMode=ADVANCE_;
    }
    
    if(count_X==1&&count_Y==3) {
      if(stage_Place_Nano==1){
        Serial3.print('L');  //给Nano发送颜色识别指令
        stage_Place_Nano=2;
      }
      Spd=Speed_High;
      systemMode=ADVANCE_;
    }//到达(1,3)后快速前移

    if(count_X==1&&count_Y==5) {
      Spd=Speed_LowLow;
      systemMode=ADVANCE_;
    }//到达(1,5)后慢速前移

    if(count_X==1&&count_Y==6) {
      if(stage_1o6==1){
        if(stage_Place_OpenMV==1){
          STOP();
          Serial3.print(2);  //给OpenMV发送颜色识别指令
          delay(100);
          while(Serial3.available()>0){
            MV_Read = Serial3.readStringUntil('\n');
          }
          Nano_read();
          stage_Place_OpenMV=2;
        }
        if(stage_Get_012==1){
          STOP();
          for(int i=0;i<3;i++){
            same=Mission[i];
            for(int j=0;j<3;j++){
              if(same==Place[j]){
                if(j==0){  //抓取位置0（左上）
                  Serial3.print('m');delay(7000);
                  //Nano_Ready();
                  if(same=='1'){
                    Serial3.print('S');
                  }
                  if(same=='2'){
                    Serial3.print('t');
                  }
                  if(same=='3'){
                    Serial3.print('s');
                  }
                }
                if(j==1){  //抓取位置1（中上）
                  Serial3.print('n');delay(7000);
                  //Nano_Ready();
                  if(same=='1'){
                    Serial3.print('S');
                  }
                  if(same=='2'){
                    Serial3.print('t');
                  }
                  if(same=='3'){
                    Serial3.print('s');
                  }
                }
                if(j==2){  //抓取位置2（右上）
                  Serial3.print('o');delay(7000);
                  //Nano_Ready();
                  if(same=='1'){
                    Serial3.print('S');
                  }
                  if(same=='2'){
                    Serial3.print('t');
                  }
                  if(same=='3'){
                    Serial3.print('s');
                  }
                }
              }
            }
          }
          stage_Get_012=2;
        }
        Spd=Speed_High;
        systemMode=LEFT_;
      }//第一次到达(1,6)原料区，上层抓取任务，并左移
      
      if(stage_1o6==2){
        stage_2o6=3;
        if(stage_Get_3==2){
          STOP();
          Serial3.print('T');delay(1000);
          //Nano_Ready();
          stage_Get_3=3;
        }//下层抓取第一次
        Spd=Speed_LowLow;
        systemMode=LEFT_;
      }//

      if(stage_1o6==3){
        stage_2o6=4;
        if(stage_Get_4==2){
          STOP();
          Serial3.print('T');delay(1000);
          //Nano_Ready();
          stage_Get_4=3;
        }//下层抓取第二次
        Spd=Speed_LowLow;
        systemMode=LEFT_;
      }

      if(stage_1o6==4){
        stage_2o6=5;
        if(stage_Get_5==2){
          STOP();
          Serial3.print('T');delay(1000);
          //Nano_Ready();
          stage_Get_5=3;
        }//下层抓取第三次
        Spd=Speed_High;
        systemMode=LEFT_;
      }
    }

    if(count_X==2&&count_Y==6){
      if(stage_2o6==1){
        stage_1o6=2;
        Spd=Speed_High;
        systemMode=LEFT_;
      }//第一次路过(2,6)，快速左移
      
      if(stage_2o6==2){
        if(stage_Get_3==1){
          STOP();
          same=Mission[3];
          for(int i=3;i<6;i++){
            if(same==Place[i]){
              if(i==3){
                stage_Place_Up=3;
                Serial3.print('M');delay(7000);
                //Nano_Ready();
              }
              if(i==4){
                stage_Place_Up=4;
                Serial3.print('N');delay(7000);
                //Nano_Ready();
              }
              if(i==5){
                stage_Place_Up=5;
                Serial3.print('O');delay(7000);
                //Nano_Ready();
              }
            }
          }
          stage_Get_3=2;
        }
        Spd=Speed_LowLow;
        systemMode=RIGHT_;
      }
      
      if(stage_2o6==3){
        if(stage_Get_3==3) {
          stage_1o6=3;
          STOP();
          if(stage_Place_Up==3){
            Serial3.print('U');delay(7000);
            //Nano_Ready();
          }
          if(stage_Place_Up==4){
            Serial3.print('v');delay(7000);
            //Nano_Ready();
          }
          if(stage_Place_Up==5){
            Serial3.print('V');delay(7000);
            //Nano_Ready();
          }
          same=Mission[3];
          if(same=='1'){
            Serial3.print('S');delay(7000);
            //Nano_Ready();
          }
          if(same=='2'){
            Serial3.print('t');delay(7000);
            //Nano_Ready();
          }
          if(same=='3'){
            Serial3.print('s');delay(7000);
            //Nano_Ready();
          }
          stage_Get_3=4;
        }
        if(stage_Get_4==1) {
          STOP();
          same=Mission[4];
          for(int i=3;i<6;i++){
            if(same==Place[i]){
              if(i==3){
                stage_Place_Up=3;
                Serial3.print('M');delay(7000);
                //Nano_Ready();
              }
              if(i==4){
                stage_Place_Up=4;
                Serial3.print('N');delay(7000);
                //Nano_Ready();
              }
              if(i==5){
                stage_Place_Up=5;
                Serial3.print('O');delay(7000);
                //Nano_Ready();
              }
            }
          }
          stage_Get_4=2;
        }
        Spd=Speed_LowLow;
        systemMode=RIGHT_;
      }

      if(stage_2o6==4){
        if(stage_Get_4==3){
          stage_1o6=4;
          STOP();
          if(stage_Place_Up==3){
            Serial3.print('U');delay(7000);
            //Nano_Ready();
          }
          if(stage_Place_Up==4){
            Serial3.print('v');delay(7000);
            //Nano_Ready();
          }
          if(stage_Place_Up==5){
            Serial3.print('V');delay(7000);
            //Nano_Ready();
          }
          same=Mission[4];
          if(same=='1'){
            Serial3.print('S');delay(7000);
            //Nano_Ready();
          }
          if(same=='2'){
            Serial3.print('t');delay(7000);
            //Nano_Ready();
          }
          if(same=='3'){
            Serial3.print('s');delay(7000);
            //Nano_Ready();
          }
          stage_Get_4=4;
        }
        if(stage_Get_5==1) {
          STOP();
          same=Mission[5];
          for(int i=3;i<6;i++){
            if(same==Place[i]){
              if(i==3){
                stage_Place_Up=3;
                Serial3.print('M');delay(7000);
                //Nano_Ready();
              }
              if(i==4){
                stage_Place_Up=4;
                Serial3.print('N');delay(7000);
                //Nano_Ready();
              }
              if(i==5){
                stage_Place_Up=5;
                Serial3.print('O');delay(7000);
                //Nano_Ready();
              }
            }
          }
          stage_Get_5=2;
        }
        Spd=Speed_LowLow;
        systemMode=RIGHT_;
      }

      if(stage_2o6==5){
        if(stage_Get_5==3) {
          STOP();
          if(stage_Place_Up==3){
            Serial3.print('U');delay(7000);
            //Nano_Ready();
          }
          if(stage_Place_Up==4){
            Serial3.print('v');delay(7000);
            //Nano_Ready();
          }
          if(stage_Place_Up==5){
            Serial3.print('V');delay(7000);
            //Nano_Ready();
          }
          same=Mission[5];
          if(same=='1'){
            Serial3.print('S');
          }
          if(same=='2'){
            Serial3.print('t');
          }
          if(same=='3'){
            Serial3.print('s');
          }
          stage_Get_5=4;
        }
        Spd=Speed_High;
        systemMode=LEFT_;
      }
    }

   if(count_X==6&&count_Y==6){
      stage_2o6=2;
      Spd=Speed_Low;
      systemMode=LEFT_;
    }

    if(count_X==7&&count_Y==6){
      Spd=Speed_LowLow;
      systemMode=BACK_;
    }

    if(count_X==7&&count_Y==4){
      if(stage_7o4==1){
        if(stage_Put_1==1){
          STOP();
          for(int i=0;i<3;i++){
            if(Mission[i]=='1'){
              Serial3.print('q');delay(7000);
              //Nano_Ready();
            }
            if(Mission[i]=='2'){
              Serial3.print('r');delay(7000);
              //Nano_Ready();
            }
            if(Mission[i]=='3'){
              Serial3.print('p');delay(7000);
              //Nano_Ready();
            }
          }
          stage_Put_1=2;
        }
        Spd=Speed_High;
        systemMode=RIGHT_;
      }
      
      if(stage_7o4==2){
        if(stage_Put_2==1){
          STOP();
          for(int i=3;i<6;i++){
            if(Mission[i]=='1'){
              Serial3.print('Q');delay(7000);
              //Nano_Ready();
            }
            if(Mission[i]=='2'){
              Serial3.print('R');delay(7000);
              //Nano_Ready();
            }
            if(Mission[i]=='3'){
              Serial3.print('P');delay(7000);
              //Nano_Ready();
            }
          }
          stage_Put_2=2;
        }
        Spd=Speed_High;
        systemMode=BACK_;
      }
    }

    if(count_X==3&&count_Y==4){
      stage_7o4=2;
      Spd=Speed_Low;
      systemMode=RIGHT_;
    }

    if(count_X==2&&count_Y==4){
      Spd=Speed_Low;
      systemMode=ADVANCE_;
    }
    
    if(count_X==7&&count_Y==2){
      Spd=Speed_Low;
      systemMode=BACK_;
    }

    if(count_X==7&&count_Y==1){
      Spd=Speed_High;
      systemMode=RIGHT_;
    }
    
    runMode();
}

void runMode(){  
  if (systemMode == ADVANCE_) {     
    front_base=front_GetTraceDate();
    front_BASE=front_xunji_PID(front_base);
    after_base=after_GetTraceDate();
    after_BASE=after_xunji_PID(after_base);
    ADVANCE(Spd,front_BASE,after_BASE);             
  }

  if (systemMode == BACK_) {     
    after_base=after_GetTraceDate();
    after_BASE=after_xunji_PID(after_base);
    front_base=front_GetTraceDate();
    front_BASE=front_xunji_PID(front_base);
    BACK(Spd,after_BASE,front_BASE);              
  }

  if (systemMode == LEFT_) {     
    left_base=left_GetTraceDate();
    left_BASE=left_xunji_PID(left_base);
    right_base=right_GetTraceDate();
    right_BASE=right_xunji_PID(right_base);
    LEFT(Spd,left_BASE,right_BASE);               
  }

  if (systemMode == RIGHT_) {     
    right_base=right_GetTraceDate();
    right_BASE=right_xunji_PID(right_base);
    left_base=left_GetTraceDate();
    left_BASE=left_xunji_PID(left_base);
    RIGHT(Spd,right_BASE,left_BASE);                 
  }

  if (systemMode == Advance_) {     
    front_base=front_GetTraceDate();
    front_BASE=front_xunji_PID(front_base);
    after_base=after_GetTraceDate();
    after_BASE=after_xunji_PID(after_base);
    ADVANCE(Spd,front_BASE,after_BASE);             
  }

  if (systemMode == Back_) {     
    after_base=after_GetTraceDate();
    after_BASE=after_xunji_PID(after_base);
    front_base=front_GetTraceDate();
    front_BASE=front_xunji_PID(front_base);
    BACK(Spd,after_BASE,front_BASE);                
  }

  if (systemMode == Left_) {     
    left_base=left_GetTraceDate();
    left_BASE=left_xunji_PID(left_base);
    right_base=right_GetTraceDate();
    right_BASE=right_xunji_PID(right_base);
    LEFT(Spd,left_BASE,right_BASE);                
  }

  if (systemMode == Right_) {     
    right_base=right_GetTraceDate();
    right_BASE=right_xunji_PID(right_base);
    left_base=left_GetTraceDate();
    left_BASE=left_xunji_PID(left_base);
    RIGHT(Spd,right_BASE,left_BASE);            
  }

  if (systemMode == Start_) {     
    LEFT(Spd,0,0);               
  }

  if (systemMode == FOUR_STRAIGHTEN) {   
    front_base=front_GetTraceDate();
    front_BASE=front_xunji_PID(front_base);
    right_base=right_GetTraceDate();
    right_BASE=right_xunji_PID(right_base);
    after_base=after_GetTraceDate();
    after_BASE=after_xunji_PID(after_base);  
    left_base=left_GetTraceDate();
    left_BASE=left_xunji_PID(left_base);
    STRAIGHTEN(front_BASE,right_BASE,after_BASE,left_BASE);            
  }

  if (systemMode == THREE_STRAIGHTEN) {     
    front_base=front_GetTraceDate();
    front_BASE=front_xunji_PID(front_base);
    right_base=right_GetTraceDate();
    right_BASE=right_xunji_PID(right_base);
    after_base=after_GetTraceDate();
    after_BASE=after_xunji_PID(after_base);  
    STRAIGHTEN(front_BASE,right_BASE,after_BASE,-right_BASE);            
  }
  
  if (systemMode == STOP_) {
    STOP();
  }
}

void Nano_Ready(){
  while(Serial3.available()<=0){
    delay(1);
  }
  while(Serial3.available()>0){
    char Nano_Serial_Read_char = Serial3.read();
    delay(1000);
  }
}


//坐标计数外部中断使能
void zuobiao_attachInterrupt(){
  attachInterrupt(3, READ_ENCODER_X, FALLING); //X轴计数
  attachInterrupt(2, READ_ENCODER_Y, FALLING); //Y轴计数
}
//坐标计数外部中断使能

//坐标计数外部中断关闭
void zuobiao_detachInterrupt(){
  detachInterrupt(3); //X轴计数关闭
  detachInterrupt(2); //Y轴计数关闭
}
//坐标计数外部中断关闭

//X轴计数函数
void READ_ENCODER_X(){
  if(systemMode==LEFT_||systemMode==Start_){
    count_X +=1;
//    Serial.print("X:");
//    Serial.println(count_X);
  }
  if(systemMode==RIGHT_){
    count_X -=1;
//    Serial.print("X:");
//    Serial.println(count_X);
  }
}
//X轴计数函数

//Y轴计数函数
void READ_ENCODER_Y(){
  if(systemMode==ADVANCE_){
    count_Y +=1;
//    Serial.print("Y:");
//    Serial.println(count_Y);
  }
  if(systemMode==BACK_){
    count_Y -=1;
//    Serial.print("Y:");
//    Serial.println(count_Y);
  }
}
//Y轴计数函数

//Nano读取函数
void Nano_read(){
  if(Nano_Read.length()==7) {
    HMI_Print_Mission(Nano_Read);
    for(int i=0;i<7;i++){
      if(MV_Read[i]!='+'){
        Mission+=Nano_Read[i];
      }
    }
    Nano_Read="";
  }
  if(Nano_Read.length()==6) {
    HMI_Print_Place(Nano_Read);
    Place=Nano_Read;
    Nano_Read="";
  }
}
//Nano读取函数

void Servo_Set(){
  switch (HMI_Read){
    case 'a':
      Serial3.print('a');
      HMI_Read= 'k';
      break;
    
    case 'A':
      Serial3.print('A');
      HMI_Read= 'k';
      break;
      
    case 'b':
      Serial3.print('b');
      HMI_Read= 'k';
      break;

    case 'B':
      Serial3.print('B');
      HMI_Read= 'k';
      break;

    case 'c':
      Serial3.print('c');
      HMI_Read= 'k';
      break;

    case 'C':
      Serial3.print('C');
      HMI_Read= 'k';
      break;

    case 'd':
      Serial3.print('d');
      HMI_Read= 'k';
      break;

    case 'D':
      Serial3.print('D');
      HMI_Read= 'k';
      break;

    case 'e':
      Serial3.print('e');
      HMI_Read= 'k';
      break;

    case 'E':
      Serial3.print('E');
      HMI_Read= 'k';
      break;

    case 'f':
      Serial3.print('f');
      HMI_Read= 'k';
      break;

    case 'F':
      Serial3.print('F');
      HMI_Read= 'k';
      break;

    case 'g':
      Serial3.print('g');
      HMI_Read= 'k';
      break;

    case 'G':
      Serial3.print('G');
      HMI_Read= 'k';
      break;

    case 'h':
      Serial3.print('h');
      HMI_Read= 'k';
      break;

    case 'H':
      Serial3.print('H');
      HMI_Read= 'k';
      break;

    case 'i':
      Serial3.print('i');
      HMI_Read= 'k';
      break;

    case 'I':
      Serial3.print('I');
      HMI_Read= 'k';
      break;

    case 'j':
      Serial3.print('j');
      HMI_Read= 'k';
      break;

    case 'J':
      Serial3.print('J');
      HMI_Read= 'k';
      break;
  }
}

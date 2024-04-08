//电机引脚定义
#define PWMA 12   //A电机转速
#define DIRA1 34
#define DIRA2 35  //A电机方向
#define ENA1 18   //A电机编码器（中断号5）
#define ENA2 31

#define PWMB 8    //B电机转速
#define DIRB1 37
#define DIRB2 36  //B电机方向
#define ENB1 19   //B电机编码器（中断号4）
#define ENB2 38

#define PWMC 9    //C电机转速
#define DIRC1 43
#define DIRC2 42  //C电机方向
#define ENC1 3    //C电机编码器（中断号1）
#define ENC2 49

#define PWMD 5    //D电机转速
#define DIRD1 A4             //26
#define DIRD2 A5  //D电机方向  //27
#define END1 2    //D电机编码器（中断号0）
#define END2 A1
//电机引脚定义
//左前方为电机A   右前方为电机B
//左后方为电机C   右后方为电机D

#include <TimerFive.h>  //定时中断头文件库

float Velocity_A;  //Velocity存储计算出的速度值（cm/s）
float Velocity_B;
float Velocity_C;
float Velocity_D;

int Count_A=0;  //Count计数变量
int Count_B=0;
int Count_C=0;
int Count_D=0;

int value_A;  //value存储计算出的PWM值
int value_B;
int value_C;
int value_D;

float Target_A,Target_B,Target_C,Target_D;  //Target目标值

float Velocity_KP =0.43, Velocity_KI =0.024;  //Velocity_KP,Velocity_KI.PI参数

float startPWM=25;        //初始PWM
float PWM_Restrict=230;  //startPW+PWM_Restric=255 限幅


//电机端口初始化
void MOTOR_init() {
  pinMode(PWMA, OUTPUT);
  pinMode(DIRA1, OUTPUT);pinMode(DIRA2, OUTPUT);
  pinMode(ENA1, INPUT);pinMode(ENA2, INPUT);
  
  pinMode(PWMB, OUTPUT);
  pinMode(DIRB1, OUTPUT);pinMode(DIRB2, OUTPUT);
  pinMode(ENB1, INPUT);pinMode(ENB2, INPUT);
  
  pinMode(PWMC, OUTPUT);
  pinMode(DIRC1, OUTPUT);pinMode(DIRC2, OUTPUT);
  pinMode(ENC1, INPUT);pinMode(ENC2, INPUT);
  
  pinMode(PWMD, OUTPUT);
  pinMode(DIRD1, OUTPUT);pinMode(DIRD2, OUTPUT);
  pinMode(END1, INPUT);pinMode(END2, INPUT);
  
//  STOP();
}
//电机端口初始化


//内部中断调用函数
void Timer5_() {
  Timer5.initialize(5000);  //单位微秒
  Timer5.attachInterrupt(control);  //内部中断调用control函数
}
//内部中断调用函数


//编码器外部中断函数
void dianji_Interrupt() {
  attachInterrupt(5, READ_ENCODER_A, CHANGE);  //开启A电机外部中断,触发方式为CHANGE
  attachInterrupt(4, READ_ENCODER_B, CHANGE);  //开启B电机外部中断,触发方式为CHANGE
  attachInterrupt(1, READ_ENCODER_C, CHANGE);  //开启C电机外部中断,触发方式为CHANGE
  attachInterrupt(0, READ_ENCODER_D, CHANGE);  //开启D电机外部中断,触发方式为CHANGE
}
//编码器外部中断函数


//编码器计数函数
void READ_ENCODER_A() {
    if (digitalRead(ENA1) == HIGH) 
    {     
     if (digitalRead(ENA2) == LOW)      
       Count_A++;  //根据另外一相电平判定方向
     else      
       Count_A--;
    }
    
    else 
    {    
     if (digitalRead(ENA2) == LOW)      
       Count_A--;  //根据另外一相电平判定方向
     else      
       Count_A++;
    }
}

void READ_ENCODER_B() {
    if (digitalRead(ENB1) == HIGH) 
    {     
     if (digitalRead(ENB2) == LOW)      
       Count_B++;  //根据另外一相电平判定方向
     else      
       Count_B--;
    }
    
    else 
    {    
     if (digitalRead(ENB2) == LOW)      
       Count_B--;  //根据另外一相电平判定方向
     else      
       Count_B++;
    }
}

void READ_ENCODER_C() {
    if (digitalRead(ENC1) == HIGH) 
    {     
     if (digitalRead(ENC2) == LOW)      
       Count_C++;  //根据另外一相电平判定方向
     else      
       Count_C--;
    }
    
    else 
    {    
     if (digitalRead(ENC2) == LOW)      
       Count_C--;  //根据另外一相电平判定方向
     else      
       Count_C++;
    }
}

void READ_ENCODER_D() {
    if (digitalRead(END1) == HIGH) 
    {     
     if (digitalRead(END2) == LOW)      
       Count_D++;  //根据另外一相电平判定方向
     else      
       Count_D--;
    }
    
    else 
    {    
     if (digitalRead(END2) == LOW)      
       Count_D--;  //根据另外一相电平判定方向
     else      
       Count_D++;
    }
}
//编码器计数函数


//内部中断函数
void control() {       
  Velocity_A=Count_A*57.12;  //单位时间内读取速度信息
  Count_A=0;                 //计数清零
  Velocity_B=Count_B*57.12;
  Count_B=0;
  Velocity_C=Count_C*57.12;
  Count_C=0;
  Velocity_D=Count_D*57.12;
  Count_D=0;
        
  value_A=Incremental_PI_A(Velocity_A,Target_A);  //通过目标值和当前值在这个函数下算出我们需要调整用的PWM值，并赋值给value
  value_B=Incremental_PI_B(Velocity_B,Target_B); 
  value_C=Incremental_PI_C(Velocity_C,Target_C); 
  value_D=Incremental_PI_D(Velocity_D,Target_D); 
        
  Set_PWM_A(value_A);  //将算好的PWM值输出给电机
  Set_PWM_B(value_B);
  Set_PWM_C(value_C);
  Set_PWM_D(value_D);
}
//内部中断函数


//增量式PI控制器
int Incremental_PI_A (float Encoder,float Target) {  
   static float Bias_A,PWM_A,Last_bias_A;  //定义全局静态浮点型变量Bias(本次偏差),PWM,Last_bias(上次偏差)
   static float Last_PWM_A;                //定义全局静态浮点型变量Last_PWM(上次输出的PWM)
   
   Bias_A=Target-Encoder;                                       //计算偏差,目标值减去当前值
   PWM_A+=Velocity_KP*(Bias_A-Last_bias_A)+Velocity_KI*Bias_A;  //增量式PI控制计算
   
   if(PWM_A>PWM_Restrict)
   PWM_A=PWM_Restrict;     //限幅
   
   if(PWM_A<-PWM_Restrict)
   PWM_A=-PWM_Restrict;    //限幅  
   
   Last_bias_A=Bias_A;     //保存上一次偏差 

   PWM_A*=0.7;
   PWM_A+=Last_PWM_A*0.3;  //一阶低通滤波器

   Last_PWM_A=PWM_A;       //保存上一次输出的PWM

   return PWM_A;           //增量输出
}

int Incremental_PI_B (float Encoder,float Target) {  
   static float Bias_B,PWM_B,Last_bias_B;  //定义全局静态浮点型变量Bias(本次偏差),PWM,Last_bias(上次偏差)
   static float Last_PWM_B;                //定义全局静态浮点型变量Last_PWM(上次输出的PWM)
   
   Bias_B=Target-Encoder;                                       //计算偏差,目标值减去当前值
   PWM_B+=Velocity_KP*(Bias_B-Last_bias_B)+Velocity_KI*Bias_B;  //增量式PI控制计算
   
   if(PWM_B>PWM_Restrict)
   PWM_B=PWM_Restrict;      //限幅
   
   if(PWM_B<-PWM_Restrict)
   PWM_B= -PWM_Restrict;    //限幅  
   
   Last_bias_B=Bias_B;      //保存上一次偏差

   PWM_B*=0.7;
   PWM_B+=Last_PWM_B*0.3;   //一阶低通滤波器

   Last_PWM_B=PWM_B;        //保存上一次输出的PWM
   
   return PWM_B;            //增量输出
}

int Incremental_PI_C (float Encoder,float Target) {  
   static float Bias_C,PWM_C,Last_bias_C;  //定义全局静态浮点型变量Bias(本次偏差),PWM,Last_bias(上次偏差)
   static float Last_PWM_C;                //定义全局静态浮点型变量Last_PWM(上次输出的PWM)

   
   Bias_C=Target-Encoder;                                       //计算偏差,目标值减去当前值
   PWM_C+=Velocity_KP*(Bias_C-Last_bias_C)+Velocity_KI*Bias_C;  //增量式PI控制计算
   
   if(PWM_C>PWM_Restrict)
   PWM_C=PWM_Restrict;      //限幅
   
   if(PWM_C<-PWM_Restrict)
   PWM_C=-PWM_Restrict;     //限幅  
   
   Last_bias_C=Bias_C;      //保存上一次偏差 

   PWM_C*=0.7;
   PWM_C+=Last_PWM_C*0.3;   //一阶低通滤波器

   Last_PWM_C=PWM_C;        //保存上一次输出的PWM
   
   return PWM_C;            //增量输出
}

int Incremental_PI_D (float Encoder,float Target) {  
   static float Bias_D,PWM_D,Last_bias_D;  //定义全局静态浮点型变量Bias(本次偏差),PWM,Last_bias(上次偏差)
   static float Last_PWM_D;                //定义全局静态浮点型变量Last_PWM(上次输出的PWM)
   
   Bias_D=Target-Encoder;                                       //计算偏差,目标值减去当前值
   PWM_D+=Velocity_KP*(Bias_D-Last_bias_D)+Velocity_KI*Bias_D;  //增量式PI控制计算
   
   if(PWM_D>PWM_Restrict)
   PWM_D=PWM_Restrict;      //限幅
   
   if(PWM_D<-PWM_Restrict)
   PWM_D=-PWM_Restrict;     //限幅  
   
   Last_bias_D=Bias_D;      //保存上一次偏差 

   PWM_D*=0.7;
   PWM_D+=Last_PWM_D*0.3;   //一阶低通滤波器

   Last_PWM_D=PWM_D;        //保存上一次输出的PWM
   
   return PWM_D;            //增量输出
}
//增量式PI控制器


//设置PWM函数
void Set_PWM_A(int motora) { 
  if (motora < 0)
  {
    analogWrite(PWMA, -motora+startPWM);
    digitalWrite(DIRA1, HIGH);
    digitalWrite(DIRA2, LOW); 
  }
  else if(motora == 0)
  {
    digitalWrite(DIRA1, LOW); 
    digitalWrite(DIRA2, LOW);   
  }
  else if (motora > 0)
  {
    analogWrite(PWMA, motora+startPWM);
    digitalWrite(DIRA1, LOW);
    digitalWrite(DIRA2, HIGH);
  }
}

void Set_PWM_B(int motora) {
  if (motora < 0)
  {
    analogWrite(PWMB, -motora+startPWM);
    digitalWrite(DIRB1, HIGH);
    digitalWrite(DIRB2, LOW);
  }
  else if(motora == 0)
  {
    digitalWrite(DIRB1, LOW);
    digitalWrite(DIRB2, LOW);
  }
  else if (motora > 0)
  {
    analogWrite(PWMB, motora+startPWM);
    digitalWrite(DIRB1, LOW);
    digitalWrite(DIRB2, HIGH);
  }
}

void Set_PWM_C(int motora) { 
  if (motora < 0)
  {
    analogWrite(PWMC, -motora+startPWM);
    digitalWrite(DIRC1, HIGH);
    digitalWrite(DIRC2, LOW);
  }
  else if(motora == 0)
  {
    digitalWrite(DIRC1, LOW);
    digitalWrite(DIRC2, LOW);
  }
  else if (motora > 0)
  {
    analogWrite(PWMC, motora+startPWM);
    digitalWrite(DIRC1, LOW);
    digitalWrite(DIRC2, HIGH);
  }
}

void Set_PWM_D(int motora) { 
  if (motora < 0)
  {
    analogWrite(PWMD, -motora+startPWM);
    digitalWrite(DIRD1, HIGH);
    digitalWrite(DIRD2, LOW);
  }
  else if(motora == 0)
  {
    digitalWrite(DIRD1, LOW);
    digitalWrite(DIRD2, LOW);
  }
  else if (motora > 0)
  {
    analogWrite(PWMD, motora+startPWM);
    digitalWrite(DIRD1, LOW);
    digitalWrite(DIRD2, HIGH);
  }
}
//设置PWM函数

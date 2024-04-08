#define front_D_AD_VALUE 5     //确定左右传感器差值
#define front_LEFT_MAX 680     //左传感器峰值
#define front_RIGHT_MAX 653    //右传感器峰值
#define front_LEFT_THERSH 93 //左传感器阈值
#define front_RIGHT_THERSH 91 //右传感器阈值
#define front_LEFT_SPAN 743    //传感器向左移动跳跃差值   //790
#define front_RIGHT_SPAN -721    //传感器向右移动跳跃差值   //1023

#define after_D_AD_VALUE 10     //确定左右传感器差值
#define after_LEFT_MAX 679     //左传感器峰值
#define after_RIGHT_MAX 725    //右传感器峰值
#define after_LEFT_THERSH 60 //左传感器阈值
#define after_RIGHT_THERSH 93 //右传感器阈值
#define after_LEFT_SPAN 743    //传感器向左移动跳跃差值   //790
#define after_RIGHT_SPAN -792    //传感器向右移动跳跃差值   //1023

#define left_D_AD_VALUE -18     //确定左右传感器差值
#define left_LEFT_MAX 726     //左传感器峰值
#define left_RIGHT_MAX 736    //右传感器峰值
#define left_LEFT_THERSH 51 //左传感器阈值
#define left_RIGHT_THERSH 53 //右传感器阈值
#define left_LEFT_SPAN 854    //传感器向左移动跳跃差值   //790
#define left_RIGHT_SPAN -893    //传感器向右移动跳跃差值   //1023

#define right_D_AD_VALUE 10     //确定左右传感器差值
#define right_LEFT_MAX 712     //左传感器峰值
#define right_RIGHT_MAX 720    //右传感器峰值
#define right_LEFT_THERSH 157 //左传感器阈值
#define right_RIGHT_THERSH 215 //右传感器阈值
#define right_LEFT_SPAN 800    //传感器向左移动跳跃差值   //790
#define right_RIGHT_SPAN -792    //传感器向右移动跳跃差值   //1023

#define front_L A14
#define front_M A13
#define front_R A12

#define after_L A0
#define after_M A2
#define after_R A3

#define left_L A9
#define left_M A10
#define left_R A11

#define right_L A8
#define right_M A7
#define right_R A6

int front_PosFlagValue=(int)((front_LEFT_MAX+front_RIGHT_MAX-front_LEFT_THERSH-front_RIGHT_THERSH)/3.0f);
int after_PosFlagValue=(int)((after_LEFT_MAX+after_RIGHT_MAX-after_LEFT_THERSH-after_RIGHT_THERSH)/3.0f);
int left_PosFlagValue=(int)((left_LEFT_MAX+left_RIGHT_MAX-left_LEFT_THERSH-left_RIGHT_THERSH)/3.0f);
int right_PosFlagValue=(int)((right_LEFT_MAX+right_RIGHT_MAX-right_LEFT_THERSH-right_RIGHT_THERSH)/3.0f);

void XUNJI_init(){
  pinMode(front_L,INPUT);
  pinMode(front_M,INPUT);
  pinMode(front_R,INPUT);

  pinMode(after_L,INPUT);
  pinMode(after_M,INPUT);
  pinMode(after_R,INPUT);

  pinMode(left_L,INPUT);
  pinMode(left_M,INPUT);
  pinMode(left_R,INPUT);

  pinMode(right_L,INPUT);
  pinMode(right_M,INPUT);
  pinMode(right_R,INPUT);
}

//获取循迹传感器输出函数
//返回值：int类型，范围循迹传感器数据，根据此值来调节小车舵机角度
int front_GetTraceDate(void)
{
  int Data_Out;//定义数据输出变量
  int Left_AD,Right_AD,Mid_AD;//定义左右中传感器AD值变量
  static char front_PosFlag=0;//定义传感器位置标志位，0认为传感器在黑线偏左位置，1认为小车在传感器偏右位置
  
  Left_AD=analogRead(front_L);
  Mid_AD=analogRead(front_M);
  Right_AD=analogRead(front_R);
  
  Data_Out=(Left_AD-Right_AD+front_D_AD_VALUE);
  if(Data_Out>front_PosFlagValue)
  {
    front_PosFlag=1;
  }
  else if(Data_Out<-front_PosFlagValue)
  {
    front_PosFlag=0;
  }
  if(Mid_AD<front_LEFT_THERSH)
  { 
    if(Data_Out>front_PosFlagValue)
    {
      Data_Out=(2*front_LEFT_MAX-Left_AD)*2-front_LEFT_SPAN;
    }
    else if((Data_Out<front_PosFlagValue)&&(front_PosFlag==1))
    {
      Data_Out=abs((2*front_LEFT_MAX-Left_AD)*2-front_LEFT_SPAN);
    }
    
  } 
  
  if(Mid_AD<front_RIGHT_THERSH)
  { 
    if(Data_Out<-front_PosFlagValue)
    {
      Data_Out=(Right_AD-2*front_RIGHT_MAX)*2-front_RIGHT_SPAN;
    }
    else if((Data_Out>-front_PosFlagValue)&&(front_PosFlag==0))
    {
      Data_Out=-abs((Right_AD-2*front_RIGHT_MAX)*2-front_RIGHT_SPAN);
    }
  }

  if (Data_Out>=500) Data_Out=500;
  else if (Data_Out<=-500) Data_Out=-500;
  
  return Data_Out;
}

int after_GetTraceDate(void)
{
  int Data_Out;//定义数据输出变量
  int Left_AD,Right_AD,Mid_AD;//定义左右中传感器AD值变量
  static char after_PosFlag=0;//定义传感器位置标志位，0认为传感器在黑线偏左位置，1认为小车在传感器偏右位置
  
  Left_AD=analogRead(after_L);
  Mid_AD=analogRead(after_M);
  Right_AD=analogRead(after_R);
  
  Data_Out=(Left_AD-Right_AD+after_D_AD_VALUE);
  if(Data_Out>after_PosFlagValue)
  {
    after_PosFlag=1;
  }
  else if(Data_Out<-after_PosFlagValue)
  {
    after_PosFlag=0;
  }
  if(Mid_AD<after_LEFT_THERSH)
  { 
    if(Data_Out>after_PosFlagValue)
    {
      Data_Out=(2*after_LEFT_MAX-Left_AD)*2-after_LEFT_SPAN;
    }
    else if((Data_Out<after_PosFlagValue)&&(after_PosFlag==1))
    {
      Data_Out=abs((2*after_LEFT_MAX-Left_AD)*2-after_LEFT_SPAN);
    }
    
  } 
  
  if(Mid_AD<after_RIGHT_THERSH)
  { 
    if(Data_Out<-after_PosFlagValue)
    {
      Data_Out=(Right_AD-2*after_RIGHT_MAX)*2-after_RIGHT_SPAN;
    }
    else if((Data_Out>-after_PosFlagValue)&&(after_PosFlag==0))
    {
      Data_Out=-abs((Right_AD-2*after_RIGHT_MAX)*2-after_RIGHT_SPAN);
    }
  }

  if (Data_Out>=500) Data_Out=500;
  else if (Data_Out<=-500) Data_Out=-500;
  
  return Data_Out;
}

int left_GetTraceDate(void)
{
  int Data_Out;//定义数据输出变量
  int Left_AD,Right_AD,Mid_AD;//定义左右中传感器AD值变量
  static char left_PosFlag=0;//定义传感器位置标志位，0认为传感器在黑线偏左位置，1认为小车在传感器偏右位置
  
  Left_AD=analogRead(left_L);
  Mid_AD=analogRead(left_M);
  Right_AD=analogRead(left_R);
  
  Data_Out=(Left_AD-Right_AD+left_D_AD_VALUE);
  if(Data_Out>left_PosFlagValue)
  {
    left_PosFlag=1;
  }
  else if(Data_Out<-left_PosFlagValue)
  {
    left_PosFlag=0;
  }
  if(Mid_AD<left_LEFT_THERSH)
  { 
    if(Data_Out>left_PosFlagValue)
    {
      Data_Out=(2*left_LEFT_MAX-Left_AD)*2-left_LEFT_SPAN;
    }
    else if((Data_Out<left_PosFlagValue)&&(left_PosFlag==1))
    {
      Data_Out=abs((2*left_LEFT_MAX-Left_AD)*2-left_LEFT_SPAN);
    }
    
  } 
  
  if(Mid_AD<left_RIGHT_THERSH)
  { 
    if(Data_Out<-left_PosFlagValue)
    {
      Data_Out=(Right_AD-2*left_RIGHT_MAX)*2-left_RIGHT_SPAN;
    }
    else if((Data_Out>-left_PosFlagValue)&&(left_PosFlag==0))
    {
      Data_Out=-abs((Right_AD-2*left_RIGHT_MAX)*2-left_RIGHT_SPAN);
    }
  }

  if (Data_Out>=500) Data_Out=500;
  else if (Data_Out<=-500) Data_Out=-500;
  
  return Data_Out;
}

int right_GetTraceDate(void)
{
  int Data_Out;//定义数据输出变量
  int Left_AD,Right_AD,Mid_AD;//定义左右中传感器AD值变量
  static char right_PosFlag=0;//定义传感器位置标志位，0认为传感器在黑线偏左位置，1认为小车在传感器偏右位置
  
  Left_AD=analogRead(right_L);
  Mid_AD=analogRead(right_M);
  Right_AD=analogRead(right_R);
  
  Data_Out=(Left_AD-Right_AD+right_D_AD_VALUE);
  if(Data_Out>right_PosFlagValue)
  {
    right_PosFlag=1;
  }
  else if(Data_Out<-right_PosFlagValue)
  {
    right_PosFlag=0;
  }
  if(Mid_AD<right_LEFT_THERSH)
  { 
    if(Data_Out>right_PosFlagValue)
    {
      Data_Out=(2*right_LEFT_MAX-Left_AD)*2-right_LEFT_SPAN;
    }
    else if((Data_Out<right_PosFlagValue)&&(right_PosFlag==1))
    {
      Data_Out=abs((2*right_LEFT_MAX-Left_AD)*2-right_LEFT_SPAN);
    }
    
  } 
  
  if(Mid_AD<right_RIGHT_THERSH)
  { 
    if(Data_Out<-right_PosFlagValue)
    {
      Data_Out=(Right_AD-2*right_RIGHT_MAX)*2-right_RIGHT_SPAN;
    }
    else if((Data_Out>-right_PosFlagValue)&&(right_PosFlag==0))
    {
      Data_Out=-abs((Right_AD-2*right_RIGHT_MAX)*2-right_RIGHT_SPAN);
    }
  }

  if (Data_Out>=500) Data_Out=500;
  else if (Data_Out<=-500) Data_Out=-500;
  
  return Data_Out;
}

float kp=0.75,ki=0,kd=35;
float front_kp =kp, front_ki =ki, front_kd =kd;
int front_xunji_PID(int Error){
  static float front_allError,front_Error,front_lastError,front_v_turn;
  front_Error=Error;
  front_allError+=front_Error;
  front_v_turn=front_kp*front_Error+front_ki*front_allError+front_kd*(front_Error-front_lastError);
  front_lastError=front_Error;
  return front_v_turn; 
}

float after_kp =kp, after_ki =ki, after_kd =kd;
int after_xunji_PID(int Error){
  static float after_allError,after_Error,after_lastError,after_v_turn;
  after_Error=Error;
  after_allError+=after_Error;
  after_v_turn=after_kp*after_Error+after_ki*after_allError+after_kd*(after_Error-after_lastError);
  after_lastError=after_Error;
  return after_v_turn; 
}

float left_kp =kp, left_ki =ki, left_kd =kd;
int left_xunji_PID(int Error){
  static float left_allError,left_Error,left_lastError,left_v_turn;
  left_Error=Error;
  left_allError+=left_Error;
  left_v_turn=left_kp*left_Error+left_ki*left_allError+left_kd*(left_Error-left_lastError);
  left_lastError=left_Error;
  return left_v_turn; 
}

float right_kp =kp, right_ki =ki, right_kd =kd;
int right_xunji_PID(int Error){
  static float right_allError,right_Error,right_lastError,right_v_turn;
  right_Error=Error;
  right_allError+=right_Error;
  right_v_turn=right_kp*right_Error+right_ki*right_allError+right_kd*(right_Error-right_lastError);
  right_lastError=right_Error;
  return right_v_turn; 
}

//A电机的前进后退
void MOTORA_FORWARD(float Target) {
  if(Target<100) Target=100;
  if(Target>550) Target=550;
  Target_A=-Target;}
  
void MOTORA_STOP() {
  Target_A=0;}
  
void MOTORA_BACK(float Target) {
  if(Target<100) Target=100;
  if(Target>550) Target=550;
  Target_A=Target;}

void MOTORA_RUN(float Target) {
  if(Target<-50) Target=-50;
  if(Target>50) Target=50;
  Target_A=-Target;}

void MOTORA_RUN_(float Target) {
  if(Target<-80) Target=-80;
  if(Target>-10&&Target<10) Target=0;
  if(Target>80) Target=80;
  Target_A=-Target;}
//A电机的前进后退


//B电机的前进后退
void MOTORB_FORWARD(float Target) {
  if(Target<100) Target=100;
  if(Target>550) Target=550;
  Target_B=-Target;}
  
void MOTORB_STOP() {
  Target_B=0;}
  
void MOTORB_BACK(float Target) {
  if(Target<100) Target=100;
  if(Target>550) Target=550;
  Target_B=Target;}

void MOTORB_RUN(float Target) {
  if(Target<-50) Target=-50;
  if(Target>50) Target=50;
  Target_B=-Target;}

void MOTORB_RUN_(float Target) {
  if(Target<-80) Target=-80;
  if(Target>-10&&Target<10) Target=0;
  if(Target>80) Target=80;
  Target_B=-Target;}
//B电机的前进后退


//C电机的前进后退
void MOTORC_FORWARD(float Target) {
  if(Target<100) Target=100;
  if(Target>550) Target=550;
  Target_C=Target;}
  
void MOTORC_STOP() {
  Target_C=0;}
  
void MOTORC_BACK(float Target) {
  if(Target<100) Target=100;
  if(Target>550) Target=550;
  Target_C=-Target;}

void MOTORC_RUN(float Target) {
  if(Target<-50) Target=-50;
  if(Target>50) Target=50;
  Target_C=-Target;}

void MOTORC_RUN_(float Target) {
  if(Target<-80) Target=-80;
  if(Target>-10&&Target<10) Target=0;
  if(Target>80) Target=80;
  Target_C=-Target;}
//C电机的前进后退


//D电机的前进后退
void MOTORD_FORWARD(float Target) {
  if(Target<100) Target=100;
  if(Target>550) Target=550;
  Target_D=Target;}

void MOTORD_STOP() {
  Target_D=0;}
  
void MOTORD_BACK(float Target) {
  if(Target<100) Target=100;
  if(Target>550) Target=550;
  Target_D=-Target;}

void MOTORD_RUN(float Target) {
  if(Target<-50) Target=-50;
  if(Target>50) Target=50;
  Target_D=-Target;}

void MOTORD_RUN_(float Target) {
  if(Target<-80) Target=-80;
  if(Target>-10&&Target<10) Target=0;
  if(Target>80) Target=80;
  Target_D=-Target;}
//D电机的前进后退


//小车停止
void STOP() {
  MOTORA_STOP();MOTORB_STOP();    
  MOTORC_STOP();MOTORD_STOP();}
//小车停止


//小车前进
void ADVANCE(float Target,float Target_Bias_1,float Target_Bias_2) {
  MOTORA_RUN(Target_Bias_1);MOTORB_FORWARD(Target+Target_Bias_1);    
  MOTORC_FORWARD(Target-Target_Bias_1);MOTORD_RUN(Target_Bias_2);}
//小车前进


//小车后退
void BACK(float Target,float Target_Bias_1,float Target_Bias_2) {
  MOTORA_RUN(Target_Bias_2);MOTORB_BACK(Target-Target_Bias_1);    
  MOTORC_BACK(Target+Target_Bias_1);MOTORD_RUN(Target_Bias_1);}
//小车后退


//小车左移
void LEFT(float Target,float Target_Bias_1,float Target_Bias_2) {
  MOTORA_FORWARD(Target+Target_Bias_1);MOTORB_RUN(Target_Bias_2);    
  MOTORC_RUN(Target_Bias_1);MOTORD_FORWARD(Target-Target_Bias_1);}
//小车左移


//小车右移
void RIGHT(float Target,float Target_Bias_1,float Target_Bias_2) {
  MOTORA_BACK(Target-Target_Bias_1);MOTORB_RUN(Target_Bias_1);    
  MOTORC_RUN(Target_Bias_2);MOTORD_BACK(Target+Target_Bias_1);}
//小车右移

//小车摆正
void STRAIGHTEN(float Target_Bias_1,float Target_Bias_2,float Target_Bias_3,float Target_Bias_4) {
  MOTORA_RUN_(Target_Bias_1);MOTORB_RUN_(Target_Bias_2);    
  MOTORC_RUN_(Target_Bias_4);MOTORD_RUN_(Target_Bias_3);}
//小车摆正

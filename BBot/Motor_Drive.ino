
#define   GUARD_GAIN   20.0

#define   InA_R                 6                              // INA right motor pin 
#define   InB_R                 7                              // INB right motor pin
#define   InA_L                 8                              // INA left motor pin
#define   InB_L                 9                              // INB left motor pin

float K = 1.4;
float   Kp =12;                      
float   Ki = 0;                   
float   Kd = 0.8;  
int last_error = 0;
int integrated_error = 0;
float pTerm = 0, iTerm = 0, dTerm = 0;

int updatePid(int targetPosition, int currentPosition)   {
  
  int error = targetPosition - currentPosition; 
  
  Serial.print(error);
  Serial.print("########");
  pTerm = Kp * error;
  integrated_error += error;                                       
  iTerm = Ki * constrain(integrated_error, -GUARD_GAIN, GUARD_GAIN);
  dTerm = Kd * (error - last_error);
  Serial.print("   pterm:");
  Serial.print(pTerm);
  Serial.print(" ---->IE:");
  Serial.print(constrain(integrated_error, -GUARD_GAIN, GUARD_GAIN));
  Serial.print("   iterm:");
  Serial.print(iTerm);
  Serial.print("   dterm:");
  Serial.print(dTerm);
  last_error = error;
  return -constrain(K*(pTerm + iTerm + dTerm), -255, 255);
}


int Drive_Motor(int torque)  {
  
  pinMode(InA_R,OUTPUT);
  pinMode(InA_L,OUTPUT);
  pinMode(InB_R,OUTPUT);
  pinMode(InB_L,OUTPUT);
  
  if (torque > 0)  {                                        // drive motors forward
    digitalWrite(InA_R, LOW);                        
    digitalWrite(InB_R, HIGH);
    digitalWrite(InA_L, LOW);                     
    digitalWrite(InB_L, HIGH);
  }  else if (torque<0){                                                  // drive motors backward
    digitalWrite(InA_R, HIGH);                       
    digitalWrite(InB_R, LOW);
    digitalWrite(InA_L, HIGH);                      
    digitalWrite(InB_L, LOW);
    torque=1.0*torque;
  }  else {
    digitalWrite(InA_R, LOW);                       
    digitalWrite(InB_R, LOW);
    digitalWrite(InA_L, LOW);                      
    digitalWrite(InB_L, LOW);
  }
  torque = abs(torque);
  
   //if(torque>5) map(torque,0,255,30,255);
    Serial.print("   Torque:");
    Serial.print(torque);
    analogWrite(EN_R,0.9*torque);
    analogWrite(EN_L,torque);
  
}






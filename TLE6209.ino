#include<SPI.h>

#define trace true

#define clk LOW
#define aclk HIGH

//Configuration byte
#define motorConf 85

//PWM pins
#define pwm1 9
#define pwm2 10

//Motor Direction pins
#define md1 22
#define md2 24

//Slave Select pins
#define ss1 30
#define ss2 32

//Inhabit
#define inb 42

byte motorStatus=255;

void setup()
{
  //SPI settings
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  //Configuring each IC one at a time
  ConfigMotors();
  //PWM frequency adjustments
  TCCR1B&=248;
  TCCR1B|=2;
  TCCR2B&=248;
  TCCR2B|=2;
  //IO control
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  pinMode(md1,OUTPUT);
  pinMode(md2,OUTPUT);
  pinMode(ss1,OUTPUT);
  pinMode(ss2,OUTPUT);
  pinMode(inb,OUTPUT);
  //active high
  digitalWrite(inb,HIGH);
}

void loop()
{
		//50% duty cycle
        analogWrite(pwm1,127);
        analogWrite(pwm2,127);
        digitalWrite(md1,clk);
        digitalWrite(md2,aclk);
}

void ConfigMotors()
{
  ConfigMotor(ss1);
  ConfigMotor(ss2);
}

void PrintMotor(byte motorStatus)
{
  Serial.print("Motor Status: ");
  Serial.print(motorStatus);
  Serial.print("  ");
  for(int i=7;i>0;i--)
  {
    Serial.print(bitRead(motorStatus,i)); 
  }
  Serial.println(); 
}

void ConfigMotor(int pin)
{
  digitalWrite(pin,LOW);
  motorStatus=SPI.transfer(motorConf);
  digitalWrite(pin,HIGH); 
  if(trace)
  {
    Serial.println(pin);
    PrintMotor(motorStatus);
  }  
}
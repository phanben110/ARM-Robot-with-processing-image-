#include "ARM_ROBOT_motor.h"
#include <Arduino.h>
#include <math.h>

StepMotor::StepMotor(int8_t _pullPin, int8_t _dirPin)
{
  pullPin = _pullPin;
  dirPin  = _dirPin;
}

void StepMotor::setupMotor()
{

  pinMode(pullPin, OUTPUT );
  pinMode(dirPin, OUTPUT );
  valuePosition = 0;
}

void StepMotor::moveWithSpeed( int16_t _speed , int8_t _dir )
{
  digitalWrite( dirPin , _dir );
  digitalWrite( pullPin, 1 );
  delayMicroseconds(_speed);
  digitalWrite( pullPin, 0);
  delayMicroseconds(_speed );
}

void StepMotor::moveToPosition( int16_t _position)
{
  if ( _position >= valuePosition )
  {
    int32_t value = abs((_position - valuePosition)) * 8.88888888888888888888888888888888888888888888888889 ;
    for ( uint16_t i = 0; i < value ; i++ )
    {
      moveWithSpeed( DELAY_SPEED_SET, RIGHT );
    }
  }
  else
  {
    int32_t value = abs((valuePosition - _position)) * 8.88888888888888888888888888888888888888888888888889 ;
    for ( uint16_t i = 0; i < value ; i++ )
    {
      moveWithSpeed( DELAY_SPEED_SET, LEFT );
    }
  }
  valuePosition = _position;
}

void StepMotor::moveWithTime(int16_t _time, int8_t _dir )
{
  unsigned long timeRead = micros();
  while ( (micros() - timeRead)< timeRead + _time*1000 )
  {
    moveWithSpeed(DELAY_SPEED_SET,_dir);
  }
}

void StepMotor::moveWithAgle( int16_t _agle, int8_t _dir)
{
  int32_t value = map ( _agle , 0,360, 0,3200) ;
  for ( int16_t i=0; i < value ; i++) 
  {
   moveWithSpeed(DELAY_SPEED_SET,_dir); 
  }
}


///////////////Driver for LM298N /////////////////////////////


driverL298N::driverL298N( uint8_t dirPin, uint8_t pullPin , uint8_t enable )
{
  _dirPin = dirPin;
  _pullPin = pullPin;
  _enable = enable;
  pinMode(_dirPin , OUTPUT);
  pinMode(_pullPin, OUTPUT);
  pinMode(_enable , OUTPUT);

}

void driverL298N::setSpeed(uint8_t pwmVal)
{
  _pwmVal = pwmVal ;
}

void driverL298N::forWard()
{
  digitalWrite(_dirPin, HIGH);
  digitalWrite(_pullPin, LOW);
  analogWrite(_enable , _pwmVal);
  _isMoving = true ;
}

void driverL298N::backWard()
{
  digitalWrite(_dirPin, HIGH);
  digitalWrite(_pullPin,HIGH);
  analogWrite(_enable, _pwmVal);
  _isMoving = true ;
}

void driverL298N::stop()
{
  digitalWrite(_dirPin ,LOW );
  digitalWrite(_pullPin,LOW );
  analogWrite(_enable , 255) ;
  _isMoving = false;

}

void driverL298N::forWardFor(uint8_t delayVal )
{
  unsigned long timeBegin  = millis () ;
  while (  ( millis () - timeBegin) > delayVal )
  {
    forWard() ;
  }
  stop();
}

void driverL298N::backWardFor(uint8_t delayVal ) 
{
  unsigned long timeBegin = millis () ;
  while (  ( millis () - timeBegin) > delayVal )
  {
    backWard(); 
  }
  stop () ;
}

void driverL298N::reset()
{
  _canMove = true ;

}

bool driverL298N::isMoving()
{
  return _isMoving ;
}

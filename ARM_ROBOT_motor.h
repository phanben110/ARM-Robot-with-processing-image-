#ifndef ARM_ROBOT_motor_h
#define ARM_ROBOT_motor_h
#include <Arduino.h>

#define DELAY_SPEED_MAX 23
#define RESOLUTION_ANGLE 3200
#define DELAY_SPEED_SET 500
#define LEFT  0
#define RIGHT 1

class StepMotor
{
  private:
    int8_t pullPin ;
    int8_t dirPin ;
    int16_t _resolutionAngle;
    int16_t _speed;
    int16_t _position;
    uint16_t valuePosition;

  public:

    StepMotor(int8_t _pullPin, int8_t _dirPin );
    void setupMotor();
    void moveWithSpeed (int16_t _speed, int8_t _dir );
    void moveWithTime (int16_t _time, int8_t _dir);
    void moveToPosition( int16_t _position);
    void moveWithAgle( int16_t _agle, int8_t _dir);
    void resest();

};

class driverL298N
{
private: 
    uint8_t _dirPin ;
    uint8_t _pullPin ;
    uint8_t _pwmPin ;
    uint8_t _enable ;
    uint8_t _pwmVal ;
    bool _canMove;
    bool _isMoving;
public: 
    typedef enum 
    {
        FORWARD =  0,
        BACKWARD = 1  
    } Direction;

    driverL298N( uint8_t dirPin, uint8_t pullPin , uint8_t enable );
    void setSpeed(uint8_t pwmVal );
    void forWard();
    void backWard();
    void forWardFor(uint8_t delayVal );
    void backWardFor(uint8_t delayVal );
    void stop();
    void reset();
    bool isMoving();
};

#endif

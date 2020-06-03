#ifndef ARM_ROBOT_calculator_angle_h
#define ARM_ROBOT_calculator_angle_h 
#include <stdint.h>
#define DEBUG true 
#define PI 3.14159265
const int pointI1[2] = {0,0};

class calculator 
{
private: 
	float   pointInput[2] ;
	float R1;
  float R2;
	float 	 distancePointInput;
	float 	 detal;
	float 	 pointI21[2];
	float 	 pointI22[2];
	float 	 pointI2[2];
	float    coefficientA;
	float    coefficientB;
	float    coefficientC;
	float    coefficientK;
	int8_t  angleR1 ;
	int8_t  angleR2 ;
	int8_t  angle[2];
public: 
	calculator(float _R1, float _R2); 
	~calculator();
	void brainArmRobot(float  _pointInput[2] , int8_t _angle[]);
 	bool checkCondition();
  float calculatorPointI();
 	float calculatorPointI21();
 	float calculatorPointI22();
 	float calCoefficientA ();
 	float calCoefficientB ();
 	float calCoefficientC ();
 	float calCoefficientK ();
 	float Detal();
 	int8_t calculatorAngleR1();
 	int8_t calculatorAngleR2();
 	int8_t calculatorSuportAngleR2();
 	void serial_println(char* payload ) ;
 	void serial_print(char* payload ) ;


};
#endif 

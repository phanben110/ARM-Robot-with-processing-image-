#include "ARM_ROBOT_calculator_angle.h"
#include <Arduino.h>
#include <stdint.h>
#include <math.h>

calculator::calculator( float _R1, float  _R2)
{
  R1 = _R1 ;
  R2 = _R2 ;
}


calculator::~calculator()
{
  for (int i = 0 ; i < 2 ; i++)
  {
    pointI21[i] = 0;
  }
  for (int i = 0 ; i < 2 ; i++)
  {
    pointI22[i] = 0;
  }
}

// hàm này là hàm xử lý chính đó nha
void calculator::brainArmRobot(float _pointInput[2], int8_t _angle[] )
{

  for ( int i = 0 ; i < 2 ; i++ )
  {
    pointInput[i] = _pointInput[i] ;
  }
  calculatorPointI() ;
  // goc R1
  angle[0] = calculatorAngleR1() ;
//  Serial.println(String ( "R1: ") + angle[0]);
  // goc R2
  angle[1] = calculatorAngleR2();
//  Serial.println(String ("R2: " ) + angle[1]);
//  Serial.println( angle[0] ) ;
//  Serial.println( angle[1] ) ;

for ( int i = 0  ; i<2 ; i++ ) 
{
  _angle[i] = angle[i] ; 
}

  return _angle ;
}


// hàm này dùng để xử lý để tìm ra tọa độ điểm tâm I
float calculator::calculatorPointI()
{

  if ( checkCondition() )
  {
    calculatorPointI21();
    calculatorPointI22();
    float I21  = sqrt( pow(pointInput[0] - pointI21[0], 2) + pow(pointInput[1] - pointI21[1], 2));
    float I22  = sqrt( pow(pointInput[0] - pointI22[0], 2) + pow(pointInput[1] - pointI22[1], 2));
//    Serial.println( String ( "I21: ") + I21);
 //   Serial.println( String ( "I22: ") + I22);

    if ( (pointI21[1] <= pointI22[1]) && (I21 <= R2 + 0.2) && (I21 >= R2 - 0.2) )
    {
   //   serial_print("center of c2 is :  x= ");
     // Serial.print( pointI21[0]);
      //serial_print("  y= ") ;
      //Serial.println( pointI21[1]);
      for ( int i = 0 ; i < 2 ; i++ )
      {
        pointI2[i] = pointI21[i] ;
      }
      //      Serial.println( pointI2[0]);
      //      Serial.println( pointI2[1]);
      return pointI2[0], pointI2[1];
    }
    else if ((I22 <= R2 + 0.2) && (I22 >= R2 - 0.2))
    {
     // serial_print("center of c2 isis :  x= ");
     // Serial.print ( pointI22[0]  );
     // serial_print ( "  y= " ) ;
     // Serial.println( pointI22[1] );
      for ( int i = 0 ; i < 2 ; i++ )
      {
        pointI2[i] = pointI22[i] ;
      }
      //Serial.println( pointI2[0]);
      //Serial.println( pointI2[1]);
      return pointI2[0] , pointI2[1];
    }
  }

}

bool calculator::checkCondition()
{
  distancePointInput = sqrt( pointInput[0] * pointInput[0] + pointInput[1] * pointInput[1]);
 // Serial.println( String ("distancePointInput") + distancePointInput) ;
  if ( (distancePointInput >= (R1 - R2) ) && (distancePointInput <= (R1 + R2)) )
  {
   // serial_println(" satisfy the conditions:  ");
    return true;
  }
  else
  {
    //serial_println(" unsatisfy the conditions: ");
    return false;
  }
}

/*
  A = 4a*a + 4b*b
  B = -4a*k
  C = k*k - 4b*b*R1*R1
  K = r1*r1 -  r2*r2 + a*a + b*b
*/



float calculator::calCoefficientK()
{
  coefficientK = R1 * R1 - R2 * R2 + pointInput[0] * pointInput[0] + pointInput[1] * pointInput[1] ;
 // Serial.println(String ("coefficientK") + coefficientK);
  return coefficientK;
}

float calculator::calCoefficientA()
{
  coefficientA = 4 * (pointInput[0] * pointInput[0] + pointInput[1] * pointInput[1]);
 // Serial.println(String ("coefficientA") + coefficientA);
  return coefficientA;
}

float calculator::calCoefficientB()
{
  coefficientB = -4 * calCoefficientK() * pointInput[0];
  //Serial.println(String ("coefficientB") + coefficientB);
  return coefficientB ;
}

float calculator::calCoefficientC()
{
  coefficientC = calCoefficientK() * calCoefficientK() - 4 * pointInput[1] * pointInput[1] * R1 * R1 ;
  //Serial.println(String ("coefficientC") + coefficientC);
  return coefficientC;
}

float calculator::Detal()
{
  detal = pow(abs(calCoefficientB()), 2) - 4 * calCoefficientA() * calCoefficientC();
  //Serial.println(String ("dettal") + detal);
  return detal;
}

float calculator::calculatorPointI21()
{
  pointI21[0] = (-calCoefficientB() + sqrt(Detal())) / (2 * calCoefficientA());
  pointI21[1] = sqrt(R1 * R1 - pointI21[0] * pointI21[0]);
 // Serial.println( pointI21[0]);
  //Serial.println( pointI21[1]);
  return pointI21[0] , pointI21[1] ;
}

float calculator::calculatorPointI22()
{

  pointI22[0] =  (-calCoefficientB() - sqrt(Detal())) / (2 * calCoefficientA()) ;
  pointI22[1] = sqrt(R1 * R1 - pointI22[0] * pointI22[0]);
  //Serial.println( pointI22[0]);
 // Serial.println( pointI22[1]);
  return pointI22[0] , pointI22[1]  ;
}


void calculator::serial_print( char* payload )
{
  if (DEBUG)
  {
   // Serial.print( payload);
  }
}

void calculator::serial_println( char* payload )
{
  if (DEBUG)
  {
    //Serial.println(  payload );
  }
}

// hàm này sẽ tính toán rồi sẽ đưa ra góc quay của R1 ( 0<=R1<=90)
int8_t calculator::calculatorAngleR1()
{
  angleR1 = (acos(float (pointI2[0] / R1)) * 180.0) / PI ;
  return angleR1;
}

// hàm này sẽ tính toán rồi sẽ trả về giá trị là một góc theo đọ R2 sẽ quay theo nó
int8_t calculator::calculatorAngleR2()
{
  //  int8_t AD = pointInput[0];
  //  int8_t CI = pointI2[0];
  //  int8_t AH = pointInput[1];
  //  int8_t CO = pointI2[1];
  //  //quya 0 do
  //  if ( AD < CI && AH == CO)
  //  {
  //    angleR2 = 0;
  //    return angleR2;
  //  }
  //  // quay 90 do
  //  else if ( AD == CI && AH > CO )
  //  {
  //    angleR2 = 90;
  //    return angleR2;
  //  }
  //  //quay 180 do
  //  else if ( AD > CI && AH == CO )
  //  {
  //    angleR2 = 180;
  //    return angleR2;
  //  }
  //  // quay 270 do
  //  else if ( AD == CI && AH < CO)
  //  {
  //    angleR2 = 270;
  //    return angleR2;
  //  }
  //  // quay 360 do
  //  else if (AD > CI && AH == CO )
  //  {
  //    angleR2 = 360;
  //    return angleR2;
  //  }
  //  //goc phan tu so 1
  //  if ( AD > CI && AH > CO )
  //  {
  //    angleR2 = calculatorSuportAngleR2();
  //    return angleR2;
  //  }
  //  // goc phan tu so 2
  //  else if ( AD < CI && AH > CO )
  //  {
  //    angleR2 = calculatorSuportAngleR2();
  //    return angleR2;
  //
  //  }
  //  // goc phan tu so 3
  //  else if ( AD < CI && AH > CO  )
  //  {
  //    angleR2 = 270 + calculatorSuportAngleR2();
  //    return angleR2;
  //
  //  }
  //  // goc phan tu so 4
  //  else if ( AD > CI && AH < CO )
  //  {
  //    angleR2 = 180 + calculatorSuportAngleR2();
  //    return angleR2;
  if ( pointI2[1] >= pointInput[1])
  {
    if ( calculatorSuportAngleR2() > 0)
    {
      return - calculatorSuportAngleR2();
    }
    else
      return calculatorSuportAngleR2();
  }
  return calculatorSuportAngleR2();


  //}


}

// hàm này dùng để tính toán góc giữa 2 vecto của cánh tay R2

int8_t calculator::calculatorSuportAngleR2()
{
  //  int8_t a1 =  pointInput[0] - pointI2[0];
  //  int8_t b1 =  pointInput[1] - pointI2[1];
  //  int8_t a2 =  - pointI2[0] ;
  //  int8_t b2 =  0;
  if ( checkCondition())
  {
    float a = sqrt( pow(pointInput[0], 2) + pow (pointInput[1], 2));
    float b = sqrt( pow( pointI2[0], 2) + pow ( pointI2[1], 2))  ;
    float c = sqrt( pow(pointInput[0] - pointI2[0], 2) + pow(pointInput[1] - pointI2[1], 2));
    float cosA = (pow(c, 2) + pow(b, 2) - pow(a, 2) ) / ( 2 * c * b) ;
    angleR2 =  (acos(cosA) * 180.0) / PI ;
    //Serial.println(String ( "test: "  ) + cosA) ;
    return angleR2 ;
  }

}

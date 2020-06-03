#include <Servo.h>
#include "ARM_ROBOT_motor.h"
#include "ARM_ROBOT_find_center.h"
#include "ARM_ROBOT_calculator_angle.h"
#include <string.h>
#define DELAY_SERVO 1000
#define _dirPin 8
#define _pullPin 7
#define _pwm 11
float _centerPoint[20][2] ;
const bool debug = true ;
String data  ;
int LED = 2 ;
int countPoint = 0 ;
int  pointPriority[20] ;
float input[2] = {20, 30}; // chay den toa do ( x = 10 , y  = 20  )

int  inputPoint[] = {3 , 10 , 2, 5 , 7 } ;




// initialization contructor for library  ARM_ROBOT_motor.h
StepMotor stepMotor1(4, 5) ;
StepMotor stepMotor2(2, 3) ;
driverL298N motor(7, 7, 8);

// initialization contructor for library ARM_ROBOT_calculator_angle.h
calculator Calculator(21, 20)  ; // R1 , R2

// initialization contructor for library ARM_ROBOT_find_center.h
pointCenter pointCenter( 27.5, 35) ;
// initialization contructor for library Servo.h
Servo thisServo ;

int inputData[20];
int8_t angle[2];


void sendData( String _data )
{
  int val_len = _data.length() + 1;
  char charArray[val_len];
  _data.toCharArray(charArray, val_len);
  Serial.write( charArray ) ;

}


void setup()
{

  stepMotor1.setupMotor();
  stepMotor2.setupMotor();

  Serial.begin(9600);
  stepMotor1.moveToPosition(0);
  stepMotor2.moveToPosition(0);
//  delay ( 500) ;
//
//  stepMotor1.moveToPosition(180);
//  stepMotor2.moveToPosition(180);
  delay ( 500) ;

  stepMotor1.moveToPosition(0);
  stepMotor2.moveToPosition(0);
  //readDatafromPython(true) ;

  //  while (data.length() < 2 )
  //  {
  //
  //    if (Serial.available() > 0)
  //    {
  //      data = Serial.readStringUntil('\n');
  //
  //
  //
  //
  //      int str_len = data.length() + 1;
  //      char char_array[str_len];
  //      data.toCharArray(char_array, str_len);
  //      Serial.write( char_array ) ;
  //      // Serial.write( "\r\n") ;
  //
  //      if (data == "on")
  //      {
  //        digitalWrite(LED, HIGH);
  //        Serial.write("My on ");
  //        // Serial.write( "\r\n") ;
  //      }
  //
  //      else if (data == "off")
  //      {
  //        digitalWrite(LED, HIGH);
  //        Serial.write("My off");
  //        // Serial.write( "\r\n") ;
  //
  //      }
  //      //    else
  //      //    {
  //      //      Serial.write("invalid input") ;
  //      //      Serial.write( "\r\n") ;
  //      //    }
  //    }
  //
  //  }
  //
  //  data = " " ;
  //readDatafromPython(true) ;

  thisServo.attach(6);
  thisServo.write(0);

  //
  //
  //  Calculator.brainArmRobot(input , angle ) ; // cai nay su dung ham tra ve mot mang bang cach tao ra mot array roi luu bien no vao do
  //
  pointCenter.processPointCenter ( _centerPoint ) ;
  //  int n = 5 ;// trong mang truyen vao co 5 gia tri


  // pointCenter.ascending ( inputPoint , 5) ;
  //  for ( int i = 0 ; i < 5 ; i++ )
  //  {
  //    Serial.println( inputPoint[i] ) ;
  //  }

  //Serial.println(  _centerPoint[19][0] ) ;
  //Serial.println( _centerPoint[19][1]);



  //  Serial.println( angle[0] ) ;
  //  Serial.println( angle[1] ) ;

  //  data[0] = Calculator.brainArmRobot(input);
  //  data[0] = Calculator.brainArmRobot(input);
  //  Serial.println( angle[0] ) ;

  pinMode( _dirPin , OUTPUT ) ;
  pinMode( _pullPin , OUTPUT );
  pinMode( _pwm , OUTPUT ) ;

}


bool readDatafromPython( bool _debug )
{

  while (data.length() < 2 )
  {

    if (Serial.available() > 0)
    {
      data = Serial.readStringUntil('\n');
      countPoint = 0;




      int str_len = data.length() + 1;
      char char_array[str_len];
      data.toCharArray(char_array, str_len);
      Serial.write( char_array ) ;
      convertStrtoArr( data, inputData ) ;
      for ( int i = 0  ; i < 20 ; i++)
      {
        sendData(String( inputData[i] )) ;
      }

      // Serial.write( "\r\n") ;

      //      if (data == "on")
      //      {
      //        digitalWrite(LED, HIGH);
      //        Serial.write("My on ");
      //        // Serial.write( "\r\n") ;
      //      }
      //
      //      else if (data == "off")
      //      {
      //        digitalWrite(LED, HIGH);
      //        Serial.write("My off");
      //        // Serial.write( "\r\n") ;
      //
      //      }
      //    else
      //    {
      //      Serial.write("invalid input") ;
      //      Serial.write( "\r\n") ;
      //    }
    }

  }

  data = " " ;


  //  while (data.length() < 2 )
  //  {
  //    if (Serial.available() > 0)
  //    {
  //      data = Serial.readStringUntil('\n');
  //      data.length() ;
  //
  //      int str_len = data.length() + 1;
  //      char char_array[str_len];
  //      data.toCharArray(char_array, str_len);
  //      Serial.write( char_array ) ;
  //      //    convertStrtoArr( data, inputData ) ;
  //      //    for ( int i = 0  ; i < 20 ; i++)
  //      //    {
  //      //      Serial.write( inputData[i] ) ;
  //      //    }
  //      //Serial.write( "\r\n") ;
  //
  //
  //      // Serial.write( "\r\n") ;
  //
  //    }
  //    //    else
  //    //    {
  //    //      Serial.write("invalid input") ;
  //    //      Serial.write( "\r\n") ;
  //    //    }
  //
  //    data = " " ;
  //
  for ( int i = 0 ; i < 20 ; i++ )
  {
    if ( inputData[i] != 0 )
    {
      countPoint += 1 ;
    }
  }
  for ( int i = 0 ; i < 20 ; i++)
  {
    if ( inputData[i] != 0 )
    {
      return true ;
    }
    else
      return false ;
  }
  // }
}


void controlServo( uint8_t value )
{
  for ( uint8_t i = 0 ; i < value; i++)
  {
    thisServo.write( value);
    delayMicroseconds( DELAY_SERVO ) ;
  }
  serialPrintln( "Servo being moving" );
}

void Controlmotor(uint8_t _time )
{
  motor.forWardFor( _time ) ;
  serialPrintln( "motor being moving" );
}

void serialPrintln( char* _payload)
{
  if (debug)
  {
    Serial.println( _payload ) ;
  }
}

void serialPrint( char* _payload)
{
  if ( debug)
  {
    Serial.print( _payload ) ;
  }
}

void forWard()
{
  digitalWrite(_dirPin, HIGH);
  digitalWrite(_pullPin, LOW);
  analogWrite(_pwm  , 70);
}

void Stop()
{
  digitalWrite(_dirPin, LOW );
  digitalWrite(_pullPin, LOW ) ;
  analogWrite( _pwm , 255 ) ;
}
void brainRobot (float _output[2])
{

  stepMotor1.moveToPosition(_output[0]);
  stepMotor2.moveToPosition(_output[1]);
  delay(100);
  controlServo(90);
  delay(100);
  Controlmotor ( 3000 ) ;
  delay(100) ;
  positionSetup();

}

bool positionSetup()
{
  controlServo(0);
  delay(100);
  stepMotor1.moveToPosition(0);
  stepMotor2.moveToPosition(0);
  return true;
}

void convertStrtoArr(String _str, int _input[20])
{
  for ( int i = 0; i < 20 ; i++ )
  {
    _input[i] = 0;
  }
  int j = 0, i, sum = 0;
  for ( i = 0 ; _str[i] != '\0' ; i++ )
  {
    if ( _str[i] == ' ')
      continue ;
    if (_str[i] ==  ',')
    {
      j++;
    }
    else
    {
      _input[j] = _input[j] * 10 + (_str[i] - 48);
    }
  }
  // Serial.println(" begin ") ;
  //  for ( int i = 0; i <= 20 ; i++ )
  //  {
  //    Serial.println( _input[i] ) ;
  //  }
  //  Serial.println( " end" ) ;

}

void runArmRobot ()
{

  if ( readDatafromPython(true) )
  {
    pointCenter.processPointPriority ( inputData , pointPriority , countPoint ) ;
    for ( int i = 0 ; i < countPoint ; i++ )
    {

      sendData ( String (NumberPriority[inputData[i]-1]) ) ;
      Serial.write(" ") ;

      pointCenter.pointOutput( NumberPriority[pointPriority[i]] , _centerPoint ) ;
    }
    for ( int j = 0 ; j < countPoint ; j++ )
    {
      //sendData(String( _centerPoint[0][1] ) ) ;
      for ( int i = 0 ; i < 2 ; i++ )
      {
        input[i] = _centerPoint[j][i] ;
      }
      Serial.write(" ") ;
      Calculator.brainArmRobot( input , angle ) ;
      if (angle[0] < 0) {
        angle[0] = - angle[0];
      }
      stepMotor1.moveToPosition(angle[0]*2);
      sendData( String(angle[0])) ;
       Serial.write(" ") ;
      if (angle[1] < 0) {
        angle[1] =  - angle[1];
      }

      stepMotor2.moveToPosition(angle[1]*2);
      sendData( String(angle[1])) ;

      Serial.write("_") ;
     // delay(1000);
      //      thisServo.write(90);
      //      forWard();
      //      delay( 2000);
      //      Stop() ;
      //      delay(500) ;
    }

    //Calculator.brainArmRobot( input , angle ) ;
    
    Stop() ;
    thisServo.write(0);
    stepMotor1.moveToPosition(0);
    stepMotor2.moveToPosition(0);
    sendData( String("ok hihi")) ;
  }


  //  thisServo.write(90);
  //  delay( 500) ;
  //  forWard();
  //  delay( 3000);
  //  Stop() ;
  //  delay(500);
  //  thisServo.write(0);
  //  stepMotor1.moveToPosition(0);
  //  stepMotor2.moveToPosition(0);


}




void loop ()
{

  sendData ( String ( "ben dep trai " ) ) ;
  runArmRobot() ;
  //
  //  if ( readDatafromPython(true) )
  //  {
  //    pointCenter.processPointPriority ( inputData , pointPriority , countPoint ) ;
  //    for ( int i = 0 ; i < countPoint ; i++ )
  //    {
  //
  //      //sendData ( String (NumberPriority[pointPriority[i]]) )  ;
  //      Serial.write(" begin  ") ;
  //      // sendData( String ( NumberPriority[pointPriority[i]])  ) ;
  //
  //
  //      pointCenter.pointOutput( NumberPriority[pointPriority[i]] , _centerPoint ) ;
  //      sendData(String( _centerPoint[i][0]) ) ;
  //      Serial.write(" ") ;
  //    }
  //
  //    for ( int j = 0 ; j < countPoint ; j++ )
  //    {
  //      // sendData(String( _centerPoint[0][1] ) ) ;
  //      for ( int i = 0 ; i < 2 ; i++ )
  //      {
  //        input[i] = _centerPoint[j][i] ;
  //        sendData(String(input[i]) ) ;
  //        Serial.write(" ") ;
  //      }
  //      //        Serial.write(" ") ;
  //      //        Calculator.brainArmRobot( input , angle ) ;
  //      stepMotor1.moveToPosition(angle[0]);
  //      sendData( String(angle[0])) ;
  //      //        Serial.write(" ") ;
  //      //        delay (100) ;
  //      stepMotor2.moveToPosition(angle[1]);
  //      sendData( String(angle[1])) ;
  //      //        Serial.write("_") ;
  //
  //      //  delay(500);
  //    }
  //
  //  }
}






//  stepMotor1.moveToPosition(_centerPoint[19][0]);
//  stepMotor2.moveToPosition(90);
//  delay(100);
//  thisServo.write(90);
//  delay( 500) ;
//  forWard();
//  delay( 3000);
//  Stop() ;
//  delay(500);
//  thisServo.write(0);
//  stepMotor1.moveToPosition(0);
//  stepMotor2.moveToPosition(0);



//  stepMotor1.moveToPosition(180);
//
//  stepMotor2.moveToPosition(180);
//  delay( 500) ;



//  stepMotor1.moveToPosition(90);
//  delay( 1000);
//  stepMotor1.moveToPosition(180);
//  delay (1000);
//  stepMotor1.moveToPosition(90);
//  delay (1000);
//  stepMotor1.moveWithTime(5000, 1);
//  delay (1000);
//  stepMotor2.moveToPosition(90);
//  delay( 1000);
//  stepMotor2.moveToPosition(180);
//  delay (1000);
//  stepMotor2.moveToPosition(90);
//  delay (1000);
//  stepMotor2.moveWithTime(5000, 1);
//  delay (1000);
//  stepMotor1.moveWithAgle(360 * 2, 0);

//  delay(500);
//  stepMotor1.moveWithSpeed(0, 100);
//  delay(500);

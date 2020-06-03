
#include "ARM_ROBOT_find_center.h"
#include <Arduino.h>
float centerPoint[20][2];
int point_Priority[20] ;

pointCenter::pointCenter( float _length , float _height , uint8_t _size[2] )
{
  Length = _length ;
  height = _height ;

//  for ( int i = 0 ; i < 2 ; i++ )
//  {
//    Size[i] = _size[i] ;
//  }

}

pointCenter::pointCenter(float _length , float _height )
{
  Length = _length ;
  height = _height ;
//  Serial.println ( height ) ;
//  Serial.println ( Length ) ;
//  for ( int i = 0 ; i < 2 ; i++ )
//  {
//    Size[i] = SIZE[i] ;
//  }
}

void pointCenter::processPointCenter ( float _centerPoint[20][2] )
{
  /* this line to debug value for contructor */
  //  Serial.println (Length );
  //  delay ( 50 ) ;
  //  Serial.println ( height);
  //  delay ( 50 ) ;
  //  for ( int i = 0 ; i < 2 ; i++  )
  //  {
  //    Serial.println ( Size[i] ) ;
  //    delay (50) ;
  //  }

  //Serial.println (Length);
  int countPoint = Size[0] * Size[1] ;
  for ( int i = 0; i < 2 ; i++ )
  {
    if ( i == 0 )
    {
      int count1 = 0 ;
      int coutUp = 0;
      for ( int j = 0; j < 20 ; j++ )  //  nap bien cho x
      {

        if ( count1 == 5  )
        {
          count1 = 0 ;
          coutUp ++ ;
        }
        _centerPoint[j][i] = Length / 5 + (coutUp ) * (Length / 5) ;
//        Serial.println( _centerPoint[j][i] ) ;
//        delay (50) ; 
        //Serial.println( Length / 5 + (coutUp ) * (Length / 5) ) ;
        //delay ( 50 );
        count1 ++ ;

      }
    }

    if ( i == 1 )
    {
      int count2 = 0 ;

      for ( int j = 0; j < 20 ; j++ )  // nap bien cho y
      {

        if ( count2 == 4 )
        {
          count2 = 0;
        }
        _centerPoint[j][i] = height / 8 + (height / 8) * count2 ;
        
//        delay (50) ;
        count2 ++ ;
      }

    }
 
  }
  //  Serial.println( _centerPoint[3][1] ) ;
  //  delay(50);
  //  Serial.println( _centerPoint[2][1] ) ;
  //  delay(50);
  //  Serial.println( _centerPoint[2][0] ) ;
}


void pointCenter::processPointPriority(int _inputPoint[] , int _pointPriority[] , int n   )
{
  //processPointCenter ( centerPoint ) ;
  ascending(  _inputPoint , n ) ; 
//  for ( int i =0 ; i<5; i++ ) 
//  {
//    Serial.println( _inputPoint[i] ) ;
//  }
 
  int count3 = 0 ;
  for ( int i = 0 ; i < n ; i++ )
  {
    for ( int j = 0 ; j < 20 ; j++)
    {
      if ( _inputPoint[i] == NumberPriority[j] && (count3 < n) )
      {
        _pointPriority[count3] = j ;
        poitnPriority[count3] = j ;
       // Serial.println( j ) ;
        count3 ++ ;
      }
      
    }

  }

  

//  for ( int i = 0 ; i < count ; i++ )
//  {
//   // pointOutput( poitnPriority[i] ) ;
//    Serial.println( pointOutput( _pointPriority[i] ) ) ;
//  }

}


void pointCenter::ascending(int a[], int n)
{
  int i, j, tam;
  for (i = 0; i < n - 1; i++)
    for (j = i + 1; j < n; j++)
      if (a[j] < a[i])
      {
        tam = a[i];
        a[i] = a[j];
        a[j] = tam;
      }
}

float pointCenter::pointOutput( int _pointNumber , float pointCenter[20][2] )
{
  float point_Output[2] ;

  point_Output[0] = pointCenter[_pointNumber][0] ;
  point_Output[1] = pointCenter[_pointNumber][1] ;
 // Serial.println(point_Output[0] ) ;
 // Serial.println(point_Output[1] ) ; 

  //return point_Output ;
  return point_Output[0] , point_Output[1] ;
  
}

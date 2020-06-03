#ifndef ARM_ROBOT_find_center_h
#define ARM_ROBOT_find_center_h
#include <Arduino.h>
const int SIZE[2] = {4, 5} ; 

// khởi tạo vị trí ô được đanh số trên bảng  
const int NumberPriority[20] = {1, 2, 3, 4, 8, 7, 6, 5, 9, 10, 11, 12, 16, 15, 14, 13, 17, 18, 19, 20};
class pointCenter
{
  private:
    // Nhập chiều dài của cái bảng
    float Length ;

    // Nhập chiều cao của cái bảng
    float height ;

    // biến count này có chức năng đếm số điểm input đầu vào từ phần processing image
    int count ;

    // biến này để lưu tọa độ điểm
    float point[20][2];

    // biến này để lưu tạo độ trọng tâm điểm
    float pointCenter[20][2];

    // biến này để lưu các ô sau khi đã sắp xếp xong mức ưu tiên để hệ thống chạy
    int  poitnPriority[20] ;

    // biến này để khởi tạo size vd trong trường hợp này chúng ta khời tạo biến này với giá trị là 3*4
    uint8_t Size[2] ;

  public:
    // hàm này là hàm khởi tạo contructor với các thông số đầu vào của cái bảng
    pointCenter ( float _length , float _height , uint8_t _size[2] ) ;

    // hàm này cũng làm 1 contructor với các thông số đầu vào khởi tạo cái bảng nhưng không có giá trị size
    pointCenter ( float _length , float _height ) ;

    // đây là hàm dùng để xử lý tính toàn rồi trả giá trị tọa độ từng ô lưu vào một đối số đó
    void processPoint ( float _point[20][2] ) ;

    // đây là hàm dùng để xử lý tính tìm ra tọa độ tâm của từng ô
    void processPointCenter ( float _centerPoint[20][2] ) ;

    // đây là hàm dùng để xử lý tính toán để tìm ra điểm input ưu tiên 
    void processPointPriority( int  _inputPoint[] , int  _pointPriority[] , int n ) ;

    // đây là hàm để sắp xếp các giá trị tăng dần 
    void ascending(int a[20] , int n ) ;

    // đây là hàm trả về giá trị một điểm rồi từ điểm đó mình truy xuất đến giá trị 
    float pointOutput( int _pointNumber , float pointCenter[20][2] ) ;

    // float pointCenter( float _pointPriority[20] , int n ) ;


};

#endif

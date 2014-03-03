#include <math.h>


typedef int ObjectID;
class Radian;
class Degree;
class Point;
class Radian
{
public:
	Radian(){
		value_ = 0.f;
	}
	Radian(float value){
		value_ = value;
	}
	Radian(const Radian& radian){
		value_ = radian.value_;
	}

	~Radian() { };

	Radian& operator= (const Radian& radian){
		value_ = radian.value_;
		return *this;
	}

	Radian operator+ (const Radian& radian){
		return Radian( value_ + radian.value_ );
	}

	Radian operator- (const Radian& radian){
		return Radian( value_ - radian.value_ );
	}
	
	Radian operator* (const Radian& radian){
		return Radian( value_ * radian.value_ );
	}
	
	Radian operator/ (const Radian& radian){
		return Radian( value_ / radian.value_ );
	}
	
	Degree toDegree();

	float value_;
};

class Degree
{
public:
	Degree(){
		value_ = 0.f;
	}
	Degree(float value){
		value_ = value;
	}
	Degree(const Degree& degree){
		value_ = degree.value_;
	}

	~Degree() { };

	Degree& operator= (const Degree& degree){
		value_ = degree.value_;
		return *this;
	}

	Degree operator+ (const Degree& degree){
		return Degree( value_ + degree.value_ );
	}

	Degree operator- (const Degree& degree){
		return Degree( value_ - degree.value_ );
	}
	
	Degree operator* (const Degree& degree){
		return Degree( value_ * degree.value_ );
	}
	
	Degree operator/ (const Degree& degree){
		return Degree( value_ / degree.value_ );
	}
	Radian toRadian();

	float value_;

};

class Point{
public:
	Point(){
		x_ = 0;
		y_ = 0.f;
	}
	Point(float x, float y){
		x_ = x;
		y_ = y;
	}
	Point(const Point& point){
		x_ = point.x_;
		y_ = point.y_;
	}

	~Point() { };

	Point& operator= (const Point& point){
		x_ = point.x_;

		y_ = point.y_;
		return *this;
	}

	Point operator+ (const Point& point){
		return Point( x_ + point.x_, y_ + point.y_ );
	}

	Point operator- (const Point& point){
		return Point( x_ - point.y_, y_ + point.y_ );
	}

	Point operator* (const float& factor){
		return Point( x_ * factor, y_ * factor );
	}
	
	Point operator/ (const float& factor){
		return Point( x_ / factor, y_ / factor );
	}

	float Length(){
		return pow( pow( x_, 2.f ) + pow( y_, 2.f ) , 0.5f );
	}

	float Distance (const Point& point){
		return pow( pow( x_ - point.x_, 2.f ) + pow( y_ - point.y_, 2.f ) , 0.5f );
	}

	Point Rotate (const Radian& radian){
		return Point( x_ * cos(radian.value_) - y_ * sin(radian.value_) , x_ * sin(radian.value_) + y_ * cos(radian.value_) );
	}
	
	Point Rotate (Degree& degree){
		return Rotate( degree.toRadian() );
	}

	float x_, y_;

};
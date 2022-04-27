#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>    

using namespace std;

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 
  	Shape(string name) {
		name_ = name;
	}
	
  	string getName() {
		return name_;
	}
	
  	virtual double getArea() const = 0;
  	virtual double getVolume() const = 0;
	
private:
  string name_;


};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape{
public:
  	Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle") {
		width_ = width;
		length_ = length;
	}
	
  	double getArea() const {
		return (double) (width_ * length_);
	}
	
  	double getVolume() const {
		return 0.0;
	}
	
	Rectangle<T> operator + (const Rectangle<T>& rec) {
		Rectangle R3 = Rectangle(0.0, 0.0);
		R3.width_ = width_ + rec.width_;
		R3.length_ = length_ + rec.length_;
		return R3;
	}
	
	Rectangle<T> operator - (const Rectangle<T>& rec) {
		Rectangle R3 = Rectangle(0.0, 0.0);
		R3.width_ = max(0.0, (double) (width_ - rec.width_));
		R3.length_ = max(0.0, (double) (length_ - rec.length_));
		return R3;
	} 
	
	T getWidth() const { 
		return width_;
	}
	
	T getLength() const { 
		return length_;
	}
private:
	T width_;
    T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape{
public:
  	Circle(double radius):Shape("Circle") {
		radius_ = radius;
	}
	
  	double getArea() const{
		return radius_ * radius_ * M_PI;
	}
	
 	double getVolume() const{
		return 0.0;
	}
	
  	Circle operator + (const Circle& cir){
		Circle C3 = Circle(0.0);
		C3.radius_ = radius_ + cir.radius_;
		return C3;
	}
	
	Circle operator - (const Circle& cir){
		Circle C3 = Circle(0.0);
		C3.radius_ = max(0.0, radius_ - cir.radius_);
		return C3;
	} 

	double getRadius() const { 
		return radius_;
	}
	
private:
	double radius_;

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape{
public:
  	Sphere(double radius):Shape("Sphere") {
		radius_ = radius;
	}

  	double getVolume() const {
		return (4.0/3.0) * radius_ * radius_ * radius_ * M_PI; 
	}	
	
  	double getArea() const {
		return 4.0 * radius_ * radius_ * M_PI; 
	}

	Sphere operator + (const Sphere& sph) {
		Sphere S3 = Sphere(0.0);
		S3.radius_ = radius_ + sph.radius_;
		return S3;
	}

	Sphere operator - (const Sphere& sph) {
		Sphere S3 = Sphere(0.0);
		S3.radius_ = max(0.0, radius_ - sph.radius_);
		return S3;		
	} 
	
	double getRadius() const {
		return radius_;
	}

private:
	double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape{
public:
  	RectPrism(double width, double length, double height):Shape("RectPrism") {
		width_ = width;
		length_ = length;
		height_ = height;
	}
	
  	double getVolume() const {
		return width_ * length_ * height_;
	}
  	
	double getArea() const {
		return 2.0 * (length_ * width_ + length_ * height_ + width_ * height_);
	}
	
	RectPrism operator + (const RectPrism& rectp){
		RectPrism R3 = RectPrism(0.0, 0.0, 0.0);
  		R3.width_ = width_ + rectp.width_;
  		R3.length_ = length_ + rectp.length_;
  		R3.height_ = height_ + rectp.height_;
  		return R3;
	}
	
	RectPrism operator - (const RectPrism& rectp){
		RectPrism R3 = RectPrism(0.0, 0.0, 0.0);
  		R3.width_ = max(0.0, width_ - rectp.width_);
  		R3.length_ = max(0.0, length_ - rectp.length_);
  		R3.height_ = max(0.0, height_ - rectp.height_);
  		return R3;
	}	
	
	double getWidth() const { 
		return width_;
	}
	
	double getLength() const { 
		return length_;
	}
	
	double getHeight() const { 
		return height_;
	}
private:
  	double length_;
  	double width_;
  	double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
	//@@Insert your code here
	list<Shape *> shapes;
	int size;
	double in1, in2, in3;
	string type;
	ifstream ifs (file_name, std::ifstream::in);
	ifs >> size;
	while(size != 0){
		Shape * temp;
		ifs >> type;
		if(type == "Rectangle"){
			ifs >> in1 >> in2;
			temp = new Rectangle<double>(in1, in2);
		} else if(type == "Circle"){
			ifs >> in1;
			temp = new Circle(in1);
		} else if(type == "Sphere"){
			ifs >> in1;
			temp = new Sphere(in1);
		} else if(type == "RectPrism"){
			ifs >> in1 >> in2 >> in3;
			temp = new RectPrism(in1, in2, in3);
		}
		shapes.push_back(temp);
		size--;
	}
	ifs.close();
	return shapes;
}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	double value;
	list<Shape*>::iterator it;
	for(it = shapes.begin(); it != shapes.end(); it++){
		if((*it) != NULL){
			value = (*it) -> getArea();
			if(value > max_area){
				max_area = value;
			}
		}
	}
	
	return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
	double value;
	list<Shape*>::iterator it;
	for(it = shapes.begin(); it != shapes.end(); it++){
		if((*it) != NULL){
			value = (*it) -> getVolume();
			if(value > max_volume){
				max_volume = value;
			}
		}
	}
	
	return max_volume;
}
#endif


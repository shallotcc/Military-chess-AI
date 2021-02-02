// Vector.cpp: implementation of the Vector class.
//
//////////////////////////////////////////////////////////////////////

#include "Vector.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Vector::Vector()
{
	this->belongTo = 0;
	this->isRoad = 0;
	this->isSave = 0;
	this->isStuck = 0;
	this->power = 0;
}

Vector::~Vector()
{

}
bool Vector::operator ==(Vector v1)
{
	if((this->belongTo == v1.belongTo)&&(this->col == v1.col)&&(this->isRoad == v1.isRoad)&&(this->isSave == v1.isSave)&&(this->isStuck == v1.isStuck)&&(this->power == v1.power)&&(this->row == v1.row))
	{
      return true;
	}else{
		return false;
	}

}


void Vector::operator =(Vector v1)
{
	this->belongTo = v1.belongTo;
	this->col = v1.col;
	this->isRoad = v1.isRoad;
	this->isSave = v1.isSave;
	this->isStuck = v1.isStuck;
	this->power = v1.power;
	this->row = v1.row;

}

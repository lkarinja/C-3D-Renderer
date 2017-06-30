/*
Copyright © 2015-2017 Leejae Karinja

This file is part of C++ 3D Renderer.

C++ 3D Renderer is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

C++ 3D Renderer is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with C++ 3D Renderer.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Vector.h"

Vector::Vector(void){
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 1;
}
Vector::Vector(double x, double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 1;
}
Vector::Vector(double x, double y, double z, double w){
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
Vector Vector::normalize(void){
	Vector vect;
	vect.x = this->x / this->getLength();
	vect.y = this->y / this->getLength();
	vect.z = this->z / this->getLength();
	return vect;
}
double Vector::getLength(void){
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}


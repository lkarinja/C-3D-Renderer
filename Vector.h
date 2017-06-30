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

#ifndef VECTOR
#define VECTOR

#include <iostream>
#include <math.h>

using namespace std;

class Vector {
	public:
	    Vector(void);
	    Vector(double x, double y, double z);
	    Vector(double x, double y, double z, double w);
	    Vector normalize(void);
        double getLength(void);
        double x;
    	double y;
    	double z;
    	double w;
};

#endif


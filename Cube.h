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

#ifndef CUBE
#define CUBE

#include <iostream>
#include "Renderer.h"
#include "Vector.h"

class Renderer;
class Vector;

using namespace std;

class Cube {
    public:
        Cube(double x, double y, double z, double w);
        void draw(Renderer* r);
        Vector s0;
    	Vector s1;
    	Vector s2;
    	Vector s3;
    	Vector s4;
    	Vector s5;
    	Vector s6;
    	Vector s7;
};

#endif


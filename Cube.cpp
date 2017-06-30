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

#include "Cube.h"

Cube::Cube(double x, double y, double z, double len){
	s0.x = x;
	s0.y = y;
	s0.z = z;

	s1.x = x + len;
	s1.y = y;
	s1.z = z;

	s2.x = x;
	s2.y = y + len;
	s2.z = z;

	s3.x = x;
	s3.y = y;
	s3.z = z + len;

	s4.x = x + len;
	s4.y = y + len;
	s4.z = z;

	s5.x = x;
	s5.y = y + len;
	s5.z = z + len;

	s6.x = x + len;
	s6.y = y;
	s6.z = z + len;

	s7.x = x + len;
	s7.y = y + len;
	s7.z = z + len;
}
void Cube::draw(Renderer* r){
	r->makeLine(s0, s1);
	r->makeLine(s1, s4);
	r->makeLine(s4, s2);
	r->makeLine(s2, s0);
	r->makeLine(s0, s3);
	r->makeLine(s3, s5);
	r->makeLine(s5, s7);
	r->makeLine(s7, s4);
	r->makeLine(s5, s2);
	r->makeLine(s7, s6);
	r->makeLine(s6, s3);
	r->makeLine(s6, s1);
	return;
}


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

#ifndef RENDERER
#define RENDERER

#include <cmath>
#include <math.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "Vector.h"
#include "Cube.h"
#include <string>
#include <stdarg.h>

class Cube;
class Vector;

using namespace std;

class Renderer{
    public:
        const float FOV = (float) (1.0 / (float)(tan(1.0)));
        const int HEIGHT = 20;
        //const float CHAR_HEIGHT = 600;
        const int WIDTH = 30;
        //const float CHAR_WIDTH = 600;

    	double matrix[16];
        double aspectRatio = WIDTH / HEIGHT;
        double _near = 0.0;
        double _far = 40.0;
    	double movement = 1.0;
    	bool flight = true;
    	
    	Vector *viewpoint;
    	Vector *viewangle;

    	Cube *c0;
    	Cube *c1;
    	
    	Renderer(void);
    	void buildMatrix(void);
    	Vector toPerspective(Vector point);
    	void render(void);
        void makeLine(Vector pointA, Vector pointB);
        void drawLine(double x1, double y1, double x2, double y2);
        void set(int x, int y, string s);
};

#endif


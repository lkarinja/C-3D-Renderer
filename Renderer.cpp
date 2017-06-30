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

#include "Renderer.h"

#define PI 3.14159265358979323846264

Renderer::Renderer(void){
    viewpoint = new Vector(0, 0, 0);
    viewangle = new Vector(0, 0, PI);
   	c0 = new Cube(0, 0, 0, 20);
    c1 = new Cube(5, 5, 5, 20);
    buildMatrix();
    
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD NumInputs = 0;
    DWORD InputsRead = 0;

    INPUT_RECORD irInput;

    GetNumberOfConsoleInputEvents(hInput, &NumInputs);

    
    while(true){
        ReadConsoleInput(hInput, &irInput, 1, &InputsRead);
        switch(irInput.Event.KeyEvent.wVirtualKeyCode){
            case 0x57:
            	if(flight){
            		viewpoint->y += sin(viewangle->y) * movement;
            		viewpoint->x += cos(viewangle->x + (PI / 2.0)) * (cos(viewangle->y) * movement);
            		viewpoint->z += sin(viewangle->x + (PI / 2.0)) * (cos(viewangle->y) * movement);
            	}else{
            		viewpoint->x += cos(viewangle->x + (PI / 2.0)) * movement;
            		viewpoint->z += sin(viewangle->x + (PI / 2.0)) * movement;
            	}
            	render();
            	break;
            case 0x41:
            	viewpoint->x += cos(viewangle->x) * movement;
            	viewpoint->z += sin(viewangle->x) * movement;
            	render();
            	break;
            case 0x53:
            	if(flight){
            		viewpoint->y -= sin(viewangle->y) * movement;
            		viewpoint->x += cos(viewangle->x - (PI / 2.0)) * (cos(viewangle->y) * movement);
            		viewpoint->z += sin(viewangle->x - (PI / 2.0)) * (cos(viewangle->y) * movement);
            	}else{
            		viewpoint->x += cos(viewangle->x - (PI / 2.0)) * movement;
            		viewpoint->z += sin(viewangle->x - (PI / 2.0)) * movement;
            	}
            	render();
            	break;
            case 0x44:
            	viewpoint->x -= cos(viewangle->x) * movement;
            	viewpoint->z -= sin(viewangle->x) * movement;
            	render();
            	break;
            case 0x45:
            	viewpoint->y += 1;
            	render();
            	break;
            case 0x51:
            	viewpoint->y -= 1;
            	render();
            	break;
            case VK_LEFT:
            	viewangle->x -= 0.1;
            	viewangle->x = fmod(viewangle->x, 2 * PI);
            	render();
            	break;
            case VK_RIGHT:
            	viewangle->x += 0.1;
            	viewangle->x = fmod(viewangle->x, 2 * PI);
            	render();
            	break;
            case VK_UP:
            	if(viewangle->y < (PI / 2)){
            		viewangle->y += 0.1;
            	}
            	render();
            	break;
            case VK_DOWN:
            	if(viewangle->y > -(PI / 2)){
            		viewangle->y -= 0.1;
            	}
            	render();
            	break;
            case 0x52:
            	viewpoint->x = 0.0;
            	viewpoint->y = 0.0;
            	viewpoint->z = 0.0;
            	viewangle->x=0.0;
            	viewangle->y=0.0;
            	viewangle->z= PI;
            	render();
            	break;
        }
    }
}

void Renderer::buildMatrix(void){
	double frustumDepth =  (_far - _near);
	double oneOverDepth = 1 / frustumDepth;

    matrix[0] = 1 * matrix[5] / aspectRatio;
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = 0;
    matrix[4] = 0;
    matrix[5] = 1 / tan(0.5f * FOV);
    matrix[6] = 0;
    matrix[7] = 0;
    matrix[8] = 0;
    matrix[9] = 0;
	matrix[10] = _far * oneOverDepth;
 	matrix[11] = 1;
 	matrix[12] = 0;
 	matrix[13] = 0;
	matrix[14] = (-_far * _near) * oneOverDepth;
	matrix[15] = 0;

	return;
}

Vector Renderer::toPerspective(Vector point){
	Vector vect;

	double ax = viewangle->x;
	double ay = viewangle->y;
	double az = viewangle->z;

	double ix = point.x - viewpoint->x;
	double iy = point.y - viewpoint->y;
	double iz = point.z - viewpoint->z;
	double iw = point.w - viewpoint->w;

	double x1=iz*sin(ax)+ix*cos(ax);
	double y1=iy;
	double z1=iz*cos(ax)-ix*sin(ax);

	double x11=x1;
	double y11=y1*cos(ay)-z1*sin(ay);
	double z11=y1*sin(ay)+z1*cos(ay);

	double x111=y11*sin(az)+x11*cos(az);
	double y111=y11*cos(az)-x11*sin(az);
	double z111=z11;

	ix = x111;
	iy = y111;
	iz = z111;

	double ox = matrix[0] * ix + matrix[4] * iy + matrix[8] * iz + matrix[12] * iw;
	double oy = matrix[1] * ix + matrix[5] * iy + matrix[9] * iz + matrix[13] * iw;
	double oz = matrix[2] * ix + matrix[6] * iy + matrix[10] * iz + matrix[14] * iw;
	double ow = matrix[3] * ix + matrix[7] * iy + matrix[11] * iz + matrix[15] * iw;

	vect.x = ((ox * WIDTH) / (2.0 * ow) + (WIDTH / 2.0));
	vect.y = ((oy * HEIGHT) / (2.0 * ow) + (HEIGHT / 2.0));
	vect.z = (oz);
	vect.w = (ow);
	
	return vect;
}

void Renderer::render(void){
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            set(x,y, " ");//.c_str());
        }
    }
    
	c0->draw(this);
	c1->draw(this);

	return;
}

void Renderer::makeLine(Vector pointA, Vector pointB){
	Vector pointAProjected = toPerspective(pointA);
	Vector pointBProjected = toPerspective(pointB);
	//if(pointAProjected.z >= this->_near && pointBProjected.z >= this->_near){
		this->drawLine(pointAProjected.x, pointAProjected.y, pointBProjected.x, pointBProjected.y);
	/*}else if(pointAProjected.z >= this->_near && pointBProjected.z < this->_near){
		double n = (pointAProjected.w - this->_near) / (pointAProjected.w - pointBProjected.w);
		double xc = (n * pointAProjected.x) + ((1-n) * pointBProjected.x);
		double yc = (n * pointAProjected.y) + ((1-n) * pointBProjected.y);
		double zc = (n * pointAProjected.z) + ((1-n) * pointBProjected.z);
		pointBProjected.x = xc;
		pointBProjected.y = yc;
		pointBProjected.z = zc;
		this->drawLine(pointAProjected.x, pointAProjected.y, pointBProjected.x, pointBProjected.y);
	}else if(pointAProjected.z < this->_near && pointBProjected.z >= this->_near){
		double n = (pointBProjected.w - this->_near) / (pointBProjected.w - pointAProjected.w);
		double xc = (n * pointBProjected.x) + ((1-n) * pointAProjected.x);
		double yc = (n * pointBProjected.y) + ((1-n) * pointAProjected.y);
		double zc = (n * pointBProjected.z) + ((1-n) * pointAProjected.z);
		pointAProjected.x = xc;
		pointAProjected.y = yc;
		pointAProjected.z = zc;
		this->drawLine(pointAProjected.x, pointAProjected.y, pointBProjected.x, pointBProjected.y);
	}*/
	return;
}

void Renderer::drawLine(double x1, double y1, double x2, double y2){
    // Bresenham's line algorithm
    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    
    if(steep){
        swap(x1, y1);
        swap(x2, y2);
    }

    if(x1 > x2){
        swap(x1, x2);
        swap(y1, y2);
    }

    const float dx = x2 - x1;
    const float dy = fabs(y2 - y1);

    float error = dx / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = (int)y1;

    const int maxX = (int)x2;

    for(int x=(int)x1; x<maxX; x++){
        if(steep){
            set(y,x, "#");//.c_str());
        }else{
            set(x,y, "#");//.c_str());
        }

        error -= dy;
        if(error < 0){
            y += ystep;
            error += dx;
        }
    }
    return;
}

void Renderer::set(int x, int y, string s){
    cout << x << " : " << y << endl;
    if(x < WIDTH && x >= 0 && y < HEIGHT && y >= 0){
    	COORD p;
        p.X = x;
        p.Y = y;
    	if(SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), p) == 0) cout << "Something broke yo!";
    	cout << s;
    }
    return;
}


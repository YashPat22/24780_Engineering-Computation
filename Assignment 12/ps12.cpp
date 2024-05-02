#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "fssimplewindow.h"



/*
Make class hierarchy like:

Primitive
  PrimitiveWithTwoPoints
    Line
    Box
  PrimitiveWithPointAndRadius
    Circle
*/


class Primitive
{
public:
	virtual void Draw(void) const;
    float R,g,b;
};

class PrimitiveWithTwoPoints : public Primitive
{
public:
	double x0,y0,x1,y1;
};

class PrimitiveWithPointAndRadius : public Primitive
{
public:
	double x,y,r;
};

class Line : public PrimitiveWithTwoPoints
{
public:
	virtual void Draw(void) const override;
};

class Box : public PrimitiveWithTwoPoints
{
public:
    virtual void Draw(void) const override;
};

class Circle : public PrimitiveWithPointAndRadius
{
public:
    virtual void Draw(void) const override;
};

void Primitive::Draw(void) const
{
    glBegin(GL_LINES);
    glEnd();
}

void Line::Draw(void) const
{
	glBegin(GL_LINES);
	glVertex2d(x0,y0);
	glVertex2d(x1,y1);
	glEnd();
}

void Box::Draw(void) const
{
	glBegin(GL_QUADS);
	glVertex2d(x0,y0);
	glVertex2d(x1,y0);
	glVertex2d(x1,y1);
	glVertex2d(x0,y1);
	glEnd();
}

void Circle::Draw(void) const
{
	glBegin(GL_LINE_LOOP);
	for(int i=0; i<360; i+=6)
	{
		double a=(double)i*3.1415927/180.0;
		double c=cos(a);
		double s=sin(a);
		glVertex2d(x+c*r,y+s*r);
	}
	glEnd();
}

int main(void)
{
	std::vector <Primitive *> primitives;
	FsOpenWindow(0,0,800,600,1);

	glPointSize(4);

	int nPoints=0;
	double x0,y0,x1,y1;

	for(;;)
	{
		FsPollDevice();
		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}

//        auto prim = new Primitive;

        if(FSKEY_1==key)
        {
//            prim->r = 0;
//            prim->g = 0;
//            prim->b = 1;
//            primitives.push_back(prim);
            glColor3f(0,0,1);
        }
        else if(FSKEY_2==key)
        {
//            prim->r = 1;
//            prim->g = 0;
//            prim->b = 0;
//            primitives.push_back(prim);
            glColor3f(1,0,0);
        }
        else if(FSKEY_3==key)
        {
//            prim->r = 1;
//            prim->g = 0;
//            prim->b = 1;
//            primitives.push_back(prim);
            glColor3f(1,0,1);
        }
        else if(FSKEY_4==key)
        {
//            prim->r = 0;
//            prim->g = 1;
//            prim->b = 0;
//            primitives.push_back(prim);
            glColor3f(0,1,0);
        }
        else if(FSKEY_5==key)
        {
//            prim->r = 0;
//            prim->g = 1;
//            prim->b = 1;
//            primitives.push_back(prim);
            glColor3f(0,1,1);
        }
        else if(FSKEY_6==key)
        {
//            prim->r = 1;
//            prim->g = 1;
//            prim->b = 0;
//            primitives.push_back(prim);
            glColor3f(1,1,0);
        }
        else if(FSKEY_7==key)
        {
//            prim->r = 0;
//            prim->g = 0;
//            prim->b = 0;
//            primitives.push_back(prim);
            glColor3f(0,0,0);
        }

//        glColor3f(prim->r,prim->g,prim->b);
//        primitives.push_back(prim);

		int lb,mb,rb,mx,my;
		auto evt=FsGetMouseEvent(lb,mb,rb,mx,my);
		if(FSMOUSEEVENT_LBUTTONDOWN==evt)
		{
			if(0==nPoints)
			{
				x0=mx;
				y0=my;
				x1=mx;
				y1=my;
			}
			else
			{
				x0=x1;
				y0=y1;
				x1=mx;
				y1=my;
			}
			++nPoints;
		}

		if(2<=nPoints && FSKEY_L==key)
		{
			auto prim=new Line;
			prim->x0=x0;
			prim->y0=y0;
			prim->x1=x1;
			prim->y1=y1;
			primitives.push_back(prim);
		}
		if(2<=nPoints && FSKEY_B==key)
		{
			auto prim=new Box;
			prim->x0=x0;
			prim->y0=y0;
			prim->x1=x1;
			prim->y1=y1;
			primitives.push_back(prim);
		}
		if(2<=nPoints && FSKEY_C==key)
		{
			auto prim=new Circle;
			prim->x=x0;
			prim->y=y0;
			prim->r=sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
			primitives.push_back(prim);
		}


		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		for(auto primPtr : primitives)
		{
			primPtr->Draw();
		}

		glBegin(GL_POINTS);
		if(1==nPoints)
		{
			glVertex2d(x0,y0);
		}
		else if(2<=nPoints)
		{
			glVertex2d(x0,y0);
			glVertex2d(x1,y1);
		}
		glEnd();
		FsSwapBuffers();
	}
	return 0;
}

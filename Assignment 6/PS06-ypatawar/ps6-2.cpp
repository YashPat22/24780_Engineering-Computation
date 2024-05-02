 #include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <ctime>
#include "fssimplewindow.h"

void Draw()
{
	double pi=3.1415927;

	glColor3ub(0,0,0);

	glBegin(GL_LINE_LOOP);
	for(double angle=0.0; angle<360.0; angle+=5.0)
	{
		double radian=angle*pi/180.0;
		double x=400.0+250.0*cos(radian);
		double y=300.0-250.0*sin(radian);
		glVertex2d(x,y);
	}
	glEnd();

	glBegin(GL_LINES);
	for(int tickMark=0; tickMark<60; ++tickMark)
	{
		double radian=(double)tickMark;
		radian=radian*2.0*pi/60.0;

		double l1,l2;
		if(0==tickMark%5)
		{
			l1=200.0;
			l2=240.0;
		}
		else
		{
			l1=230.0;
			l2=240.0;
		}

		double x=400.0+l1*cos(radian);
		double y=300.0-l1*sin(radian);
		glVertex2d(x,y);

		x=400.0+l2*cos(radian);
		y=300.0-l2*sin(radian);
		glVertex2d(x,y);
	}
	glEnd();
}
void hourhand(int &hour,int &min,int &s)
{
    double pi=3.1415927;
    glColor3ub(0,0,0);
    glBegin(GL_LINES);
    double hourPlusMin=(double)hour+(double)min/60.0;
    double radian=pi*2.0*hourPlusMin/12.0;
    double x=400.0+160.0*sin(radian);
    double y=300.0-160.0*cos(radian);
    glVertex2d(x,y);
    glVertex2d(400.0,300.0);
    glEnd();
}

void minhand(int &hour,int &min, int &sec)
{
    double pi=3.1415927;
    glColor3ub(0,0,0);
    double minPlusSec=(double)min+(double)sec/60.0;
    glBegin(GL_LINES);
    double radian=pi*2.0*(double)minPlusSec/60.0;
    double x=400.0+200.0*sin(radian);
    double y=300.0-200.0*cos(radian);
    glVertex2d(x,y);
    glVertex2d(400.0,300.0);
    glEnd();
}

void sechand(int &hour, int &min, int &sec)
{
    double pi=3.1415927;
    glBegin(GL_LINES);
    glColor3ub(255,0,0);
    double radian=pi*2.0*(double)sec/60.0;
    double x=400.0+220.0*sin(radian);
    double y=300.0-220.0*cos(radian);
    glVertex2d(x,y);
    glVertex2d(400.0,300.0);
    glEnd();
}

void GetLocalTimeHourMinSec(int &hour,int &min,int &sec)
{
    struct tm *localTime;
    time_t t=time(NULL);
    localTime=localtime(&t);
    hour=localTime->tm_hour;
    min=localTime->tm_min;
    sec=localTime->tm_sec;
}

int main(void)
{
	int hour,min,sec;
    double pi=3.1415927;
	FsOpenWindow(32,32,800,600,0);
    for(;FSKEY_ESC!=FsInkey();)
    {
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        GetLocalTimeHourMinSec(hour,min,sec);
        Draw();
        hourhand(hour,min,sec);
        minhand(hour,min,sec);
        sechand(hour,min,sec);
        glFlush();
    }
    FsSleep(25);
	FsCloseWindow();

	return 0;
}

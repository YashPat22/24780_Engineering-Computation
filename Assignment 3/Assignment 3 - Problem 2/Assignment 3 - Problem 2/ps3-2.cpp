//
//  ps3-2.cpp
//  Assignment 3 - Problem 2
//
//  Created by Yash Patawari on 9/17/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "fssimplewindow.h"

const double Pi=3.1415927;

void DrawCircle(double x,double y,double r)
{
    glBegin(GL_LINE_STRIP);
    for(int i=0; i<200; ++i)
    {
        double a=Pi*(double)i/30;
        double dx=cos(a)*r;
        double dy=sin(a)*r;
        glVertex2d(x+dx,y+dy);
    }
    glEnd();
    
}

void DrawCLines(double x, double y)
{
    int j=0;
    while(j<60)
    {
        
        double b=j*Pi/30;
        double ddx = cos(b);
        double ddy = sin(b);
        if(j%5 == 0)
        {
            glBegin(GL_LINE_STRIP);
            glVertex2d(x+(200*ddx),y+(200*ddy));
            glVertex2d(x+(240*ddx),y+(240*ddy));
            glEnd();
        }
        else
        {
            glBegin(GL_LINE_STRIP);
            glVertex2d(x+(230*ddx),y+(230*ddy));
            glVertex2d(x+(240*ddx),y+(240*ddy));
            glEnd();
        }
        j++;
    }
    
}

void DrawClock(double h,double m,double s, double x,double y)
{
    double hangle=(((30*h)+(0.5*m))-90) * Pi/180;
    double mangle=(Pi/180)*(((6*m)+(0.1*s)-90));
    double sangle=(Pi*s/30)-(Pi/2);
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2d(x,y);
    glVertex2d(x+(160*cos(hangle)),y+(160*sin(hangle)));
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2d(x,y);
    glVertex2d(x+(200*cos(mangle)),y+(200*sin(mangle)));
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2d(x,y);
    glVertex2d(x+(220*cos(sangle)),y+(220*sin(sangle)));
    glEnd();
    
}
int main(void)
{
    double hrs,mins,sec;
    int hour,min,sec;
    GetLocalTimeHourMinSec(hour,min,sec);
    std::cout<<"Please Enter hours, minutes and seconds separated by a space: ";
    std::cin>>hrs>>mins>>sec;
    FsOpenWindow(0,0,800,600,0);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    for(;;)
    {
        FsPollDevice();
        auto key=FsInkey();
        if(FSKEY_ESC==key)
        {
            break;
        }

        const double x0=400.0;
        const double y0=300.0;
        const double rad=250.0;
        glColor3ub(0,0,0);
        DrawCircle(x0,y0,rad);
        DrawCLines(x0,y0);
        DrawClock(hrs,mins,sec,x0,y0);

        glFlush();

        FsSleep(25);
    }
    return 0;
}

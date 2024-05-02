
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

void DrawCLines(int x, int y)
{
    for(int j=0;j<60;j++)
    {
        double b=j*Pi/30;
        if(j%5 == 0)
        {
            glBegin(GL_LINE_STRIP);
            int ddx = cos(b);
            int ddy = sin(b);
            glVertex2i(x+(200*ddx),y+(200*ddy));
            glVertex2i(x+(240*ddx),y+(240*ddy));
            glEnd();
        }
        else
        {
            glBegin(GL_LINE_STRIP);
            int ddx = cos(b);
            int ddy = sin(b);
            glVertex2i(x+(230*ddx),y+(230*ddy));
            glVertex2i(x+(240*ddx),y+(240*ddy));
            glEnd();
        }
        
    }

}

void DrawClock(int h,int m,int s);

int main(void)
{
    int hrs,mins,sec;
    //std::cout<<"Please Enter hours, minutes and seconds separated by a space: ";
    //std::cin>>hrs>>mins>>sec;
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

        const int x0=400;
        const int y0=300;
        const int rad=250;
        glColor3ub(0,0,0);
        DrawCircle(x0,y0,rad);
        DrawCLines(x0,y0);
        

        glFlush();
        //FsSwapBuffers();

        //FsSleep(25);
    }
    return 0;
}

void DrawClock(int h,int m,int s)
{
    
}

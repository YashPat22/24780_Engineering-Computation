//
//  ps4-2.cpp
//  Assignment 4 - Problem 2
//
//  Created by Yash Patawari on 9/26/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include "fssimplewindow.h"

#define PI 3.14159265


void DrawCircle(double x,double y,double r)
{
    int R = rand()%255;
    int g = rand()%255;
    int b = rand()%255;
    glColor3ub(R,g,b);
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<64; ++i)
    {
        double a=PI*(double)i/32;
        double dx=cos(a)*r;
        double dy=sin(a)*r;
        glVertex2d(x+dx,y+dy);
    }
    glEnd();
}

void Ball_Move(double &x,double &y,double &vx,double &vy,double m,double dt,double &angle)
{
    double fx,fy,ax,ay;
    
    
    x=x+vx*dt;
    y=y+vy*dt;
    
    
    fx=0.0;
    fy=-m*9.8;
    
    
    ax=fx/m;
    ay=fy/m;
    
    
    vx=vx+dt*ax;
    vy=vy-dt*ay;
    
    angle-=PI/180;
}


void DrawCannon(int X,int Y)
{
    glColor3f(0,0,1);
    glBegin(GL_QUADS);
    glVertex2i(X,Y);
    glVertex2i(X,Y-10);
    glVertex2i(X+10,Y-10);
    glVertex2i(X+10,Y);
    glEnd();
}


void DrawCannonArm(int X, int Y, double angle, int rad)
{
    double cang = cos(angle);
    double sing = sin(angle);
    
    glColor3f(0,0,1);
    glBegin(GL_LINES);
    glVertex2d(X+5,Y-5);
    glVertex2d(X+5+rad*cang,Y-5+rad*sing);
    glEnd();
}

void RotAngle(double &angle)
{
    angle -= PI/180;
}

bool CheckCollision(double mx,double my,int tx,int ty,int tw, int th)
{
    int rx = mx-tx;
    int ry = my-ty;
    
    if(0<=rx && rx<=tw && 0<=ry && ry<=th)
    {
        return true;
    }
    return false;
}


void DrawTarget(int x,int y,int w,int h)
{
    glColor3f(1,0,0);
    glBegin(GL_QUADS);
    glVertex2i(x,y);
    glVertex2i(x+w,y);
    glVertex2i(x+w,y+h);
    glVertex2i(x,y+h);
    glEnd();
}

void MoveTarget(int &x, int &y, int sc_size_x, int sc_size_y)
{
    y+=10;
    if(y>sc_size_y)
    {
        y=0;
    }
    
}


void DrawObstacle(int x[],int y[],int w[],int h[],int state[])
{
    for(int i=0;i<5;i++)
    {
    if(state[i]==1)
    {
        glColor3f(0.0,1.0,0.0);
        glBegin(GL_QUADS);
        glVertex2i(x[i],y[i]);
        glVertex2i(x[i],y[i]+h[i]);
        glVertex2i(x[i]+w[i],y[i]+h[i]);
        glVertex2i(x[i]+w[i],y[i]);
        glEnd();
    }
    else if (state[i]==0)
    {
        glColor3f(0.0,0.0,1.0);
        glBegin(GL_LINE_LOOP);
        glVertex2i(x[i],y[i]);
        glVertex2i(x[i]+w[i],y[i]);
        glVertex2i(x[i]+w[i],y[i]+h[i]);
        glVertex2i(x[i],y[i]+h[i]);
        glEnd();
    }
    }
}

int main(void)
{
    srand(time(NULL));
    const int numObs=5;
    int tx[numObs],ty[numObs], tw[numObs], th[numObs];
    int tstate[numObs];
    for(int i = 0;i<numObs;i++)
    {
        int x0 = rand()%(800-150);
        int y0 = rand()%(600-150);
        int x1 = 80+rand()%70;
        int y1 = 80+rand()%70;
        tx[i] = x0;
        ty[i] = y0;
        tw[i] = x1;
        th[i] = y1;
        tstate[i] = 1;
    }
    
    int X_Cannon = 50, Y_Cannon = 550, radius = 30;
    double init_angle = -(PI/6);
    
    int targetX = 700, targetY = 100, targetsize_X = 100, targetsize_Y = 100,ttstate = 1;
    
    double m=1.0,vx,vy,dt=0.025;
    double v =400;
    vx = v * cos(init_angle);
    vy = v * sin(-init_angle);
    double a=0,k=0,q=0,w=0,grav=9.8;
    
    double X_Circle = (double)X_Cannon+5+30*cos(init_angle);
    double Y_Circle = (double)Y_Cannon-5+30*sin(init_angle);
    FsOpenWindow(0,0,800,600,1);
    double mx=X_Circle,my=Y_Circle;
    int mstate=0;
    
    for(;;)
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glFlush();
        FsPollDevice();
        auto key=FsInkey();
        if(FSKEY_ESC==key)
        {
            break;
        }
        else if(FSKEY_SPACE==key)
        {
            if(mstate == 0)
            {
                mstate=1;
                mx=X_Circle;
                my=Y_Circle;
                vx=400*cos(init_angle);
                vy=400*sin(init_angle);
            }
        }
        if(0!=mstate)
        {
            mx +=vx * dt;
            my +=vy * dt;
            vy = vy-dt*grav/m;
            if(my<0 || mx>800 || my>600 || mx<0)
            {
                mstate = 0;
                mx=X_Circle;
                my=Y_Circle;
                vx=400*cos(init_angle);
                vy=400*sin(init_angle);
            }
        }
        
        
        DrawCannon(X_Cannon,Y_Cannon);
        
        DrawCannonArm(X_Cannon,Y_Cannon,init_angle,radius);
        if(init_angle<=0 && init_angle>= -PI/2)
        {
            RotAngle(init_angle);
        }
        else
        {
            init_angle = 0;
        }
    
        
        int on=0;
    
        
        DrawTarget(targetX,targetY,targetsize_X,targetsize_Y);
        
        MoveTarget(targetX, targetY, 800, 600);
        
        DrawObstacle(tx,ty,tw,th,tstate);
        
        
        for(int i=0;i<numObs;i++)
        {
            if(0!=tstate[i])
            {
                on++;
            }
            if(0!=mstate && 0!=tstate[i] && CheckCollision(mx,my,tx[i],ty[i],tw[i],th[i])==true)
            {
                mstate = 0;
                tstate[i] = 0;
                mx=X_Circle;
                my=Y_Circle;
                vx=400*cos(init_angle);
                vy=400*sin(init_angle);

            }
        }
        
        if(0!=mstate)
        {
            //Ball_Move(X_Circle,Y_Circle,vx,vy,m,dt,a);
            glColor3ub(1,1,1);
            glBegin(GL_TRIANGLE_FAN);
            for(int i=0; i<64; ++i)
            {
                double a=PI*(double)i/32;
                double dx=cos(a)*5;
                double dy=sin(a)*5;
                glVertex2d(mx+dx,my+dy);
            }
            glEnd();
        }
        
        if (mstate > 0)
        {
            bool c = CheckCollision(mx, my, targetX, targetY, targetsize_X, targetsize_Y);
            if (true == c )
            {
                break;
            }
        }
        FsSwapBuffers();
        FsSleep(25);
    }
    return 0;
}

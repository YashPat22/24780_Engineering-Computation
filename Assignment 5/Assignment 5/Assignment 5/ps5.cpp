//
//  ps5.cpp
//  Assignment 5
//
//  Created by Yash Patawari on 10/3/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include "fssimplewindow.h"

void DrawCircle(double cx,double cy,double r)
{
    const double PI=3.1415927;
    
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<64; ++i)
    {
        double a=(double)i*PI*2.0/64.0;
        double s=sin(a);
        double c=cos(a);
        glVertex2d(cx+c*r,cy+s*r);
    }
    glEnd();
}

void BounceOnWall(double bx,double by,double &vx,double &vy)
{
    if((by<=0.0 && vy<0.0) || (550<=by && vy<0.0))
    {
        vy=-vy;
    }
    if((bx<=0 && vx<0.0) || (800<=bx && 0.0<vx))
    {
        vx=-vx;
    }
}



int main(void)
{
    srand(time(NULL));
    time_t begin, end;
    int numP,mode,speed;
    std::cout<<"How many people blood do you want to drink? (Max 500) \n";
    std::cin>>numP;
    
    std::cout<<"Enter Game Mode (1-Slow, 2-Normal, 3-Fast) \n";
    std::cout<<"What mode do you want to play (Speed in ft/sec) (Slow-speed 25/Normal-speed 50/Fast-speed 75)? \n";
    std::cin>>mode;
    
    double bx[500],by[500],vx[500],vy[500],dt=0.001;
    int hstate[500];
    for(int i=0; i<numP; ++i)
    {
        bx[i]=(double)(rand()%800);
        by[i]=(double)(rand()%600);
        vx[i]=(double)(rand()%100);
        vy[i]=(double)(rand()%100);
        hstate[i] = 0;
    }
    
    if(mode==1)
    {
        speed = 25;
    }
    else if(mode==3)
    {
        speed = 75;
    }
    else
    {
        speed = 50;
    }
    
    
    double hx=50,hy=50;
    
    int move;

    time(&begin);
    FsOpenWindow(0,0,800,600,1);
    for(;;)
    {
        FsPollDevice();
        auto key=FsInkey();
        if(FSKEY_ESC==key)
        {
            break;
        }
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        for(int i=0; i<numP; ++i)
        {
            bx[i]+=vx[i]*dt;
            by[i]+=vy[i]*dt;
            vx[i]-=rand()%20;
            vy[i]-=rand()%20;
            BounceOnWall(bx[i],by[i],vx[i],vy[i]);
        }
        
        glColor3ub(255,0,0);
        DrawCircle(hx, hy, 10.0);
        if(FSKEY_RIGHT==key)
        {
            move = 0;
            hx+=speed;
            if(hx>800)
            {
                hx = 50;
                std::cout<<"Sorry! you went out of bounds Horizontally into Sunlight \n";
                break;
            }
            //break;
        }
            
        if(FSKEY_LEFT==key)
        {
            move = 1;
            hx-=speed;
            if(hx<0)
            {
                hx = 50;
                std::cout<<"Sorry! you went out of bounds Horizontally into Sunlight \n";
                break;
            }
            //break;
        }
            
        if(FSKEY_UP==key)
        {
            move = 2;
            hy-=speed;
            if(hy>550)
            {
                hy = 550;
                std::cout<<"Sorry! you went out of bounds Vertically into Sunlight \n";
                break;
            }
            //break;
        }
            
        if(FSKEY_DOWN==key)
        {
            move = 3;
            hy+=speed;
            if(hy<10)
            {
                hy = 550;
                std::cout<<"Sorry! you went out of bounds Vertically into Sunlight \n";
                break;
            }
            //break;
        }



        //Define Safe Zone
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1,0b1000100010001000);
        glColor3ub(0,0,0);
        glBegin(GL_LINE_STRIP);
        glVertex2i(350,250);
        glVertex2i(350,350);
        glVertex2i(450,350);
        glVertex2i(450,250);
        glVertex2i(350,250);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
        
        
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1,0b1000100010001000);
        glColor3ub(255,0,0);
        glBegin(GL_LINE_STRIP);
        glVertex2i(2,2);
        glVertex2i(798,2);
        glVertex2i(798,598);
        glVertex2i(2,598);
        glVertex2i(2,2);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
        
        int count=0;
        for(int i=0; i<numP; ++i)
        {
            
            double dx=hx-bx[i];
            double dy=hy-by[i];
            double d=sqrt(dx*dx+dy*dy);
            if(d<30)
            {
                hstate[i] = 1;
                
            }
            
            if(hx>=350.0 && hx<=450.0 && hy>=250.0 && hy<=350.0 && bx[i]>=350.0 && bx[i]<=450.0 && by[i]>=250.0 && by[i]<=350.0)
            {
                hstate[i] = 0;
            }
            
            if(hstate[i]==1)
            {
                count++;
                glColor3ub(0,0,255);
                DrawCircle(bx[i],by[i],10.0);
                
            }
            else if(hstate[i]==0)
            {
                glColor3ub(0,255,0);
                DrawCircle(bx[i],by[i],10.0);
            }
            
        }
        
        
        if(count==numP)
        {
            std::cout<<"You Win! You sucked the blood out of all people! \n";
            std::cout<<"You Win! Total Number of Zombies Created: "<<count<<std::endl;
            
            break;
            
        }
        FsSwapBuffers();
        FsSleep(10);
    }
    time(&end);
    time_t duration = end-begin;
    
    std::cout<<"Game Over! Time you took to play the game (in seconds): "<<duration<<std::endl;;
    return 0;
}

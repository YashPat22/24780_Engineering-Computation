//
//  ps4-1.cpp
//  Assignment 4 - Problem 1
//
//  Created by Yash Patawari on 9/23/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include "fssimplewindow.h"


void DrawRect(int x1,int y1,int x2,int y2)
{
    glBegin(GL_QUADS);
    glVertex2i(x1,y1);
    glVertex2i(x2,y1);
    glVertex2i(x2,y2);
    glVertex2i(x1,y2);
    glEnd();
}

void VisualizeArrayContents(int n,int x[],int movedIndex1,int movedIndex2, int state)
{
    int x1=0,x2,y1,y2,x3=0,x4,y3,y4;
    for(int i=0;i<n;i++)
    {
        glColor3ub(0,0,255);
        x2 = 20 * x[i];
        y1 = 20 * i;
        y2 = (20 * i) + 20;
        DrawRect(x1, y1, x2, y2);
        
        if(state!=0)
        {
            glColor3ub(255,0,0);
            x4 = 20 * x[movedIndex1];
            y3 = 20 * movedIndex1;
            y4 = (20 * movedIndex1) + 20;
            DrawRect(x3, y3, x4, y4);
        
            glColor3ub(255,0,0);
            x4 = 20 * x[movedIndex2];
            y3 = 20 * movedIndex2;
            y4 = (20 * movedIndex2) + 20;
            DrawRect(x3, y3, x4, y4);
        }
    }
      
    // Fill this function.
}

void SwapInt(int &a,int &b)
{
    int c;
    c=b;
    b=a;
    a=c;
}

void Shuffle(int n,int x[])
{
    int i = 0,movedIndex1=-1,movedIndex2=-2,count=0,state=1;
    srand(time(NULL));
    
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
            if(i<n)
            {
                count++;
                int r1=rand()%n;
                if(i==r1)
                {
                    r1 =rand()%n;
                }
                SwapInt(x[i],x[r1]);
                movedIndex1 = i;
                movedIndex2 = r1;
                VisualizeArrayContents(n, x, movedIndex1, movedIndex2,state);
                i++;
                if(count==n)
                {
                    movedIndex1 = -1;
                    movedIndex1 = -2;
                    state = 0;
                }
            }
        }
        else
        {
            VisualizeArrayContents(n, x, movedIndex1, movedIndex2,state);
        }
        
        FsSwapBuffers();
        FsSleep(25);
    }
}

int main(void)
{
    int x[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    FsOpenWindow(16,16,400,400,1);
    Shuffle(20,x);
    return 0;
}


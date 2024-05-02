//
//  ps8-1.cpp
//  Assignment 8 - Problem 1
//
//  Created by Yash Patawari on 11/1/22.
//

#include <stdio.h>
#include "fssimplewindow.h"
#include <stdlib.h>

int main(void)
{
    // Character for the cell (x,y) will be pattern[y*16+x]
    char pattern[]=
    {
        // By the way, if you want to define a long string, you can write like this.
        "...1........1..."
        "...11......11..."
        "...1.1....1.1..."
        "...1..1..1..1..."
        "...1..1111..1..."
        "..1..........1.."
        "..1..11..11..1.."
        "..1..........1.."
        ".1..111..111..1."
        ".1.1.1.11.1.1.1."
        "1..1.1.11.1.1..1"
        "1...111..111...1"
        ".1............1."
        ".1.....11.....1."
        "..111......111.."
        ".....111111....."
    };
    
    FsOpenWindow(16,16,300,300,0);
    while(FSKEY_ESC!=FsInkey())
    {
        int lb,mb,rb,mx,my;
        FsPollDevice();
        
        for(int i=0;i<256;i++)
        {
            if(pattern[i]=='1')
            {
                int l, b;
                l = i%16;
                b = i/16;
                l*=16;
                b*=16;
                glColor3f(0, 0, 0);
                glBegin(GL_QUADS);
                glVertex2i(l, b);
                glVertex2i(l + 16, b);
                glVertex2i(l + 16, b + 16);
                glVertex2i(l, b + 16);
                glEnd();
            }
        }
        
        if(FSMOUSEEVENT_MOVE==FsGetMouseEvent(lb,mb,rb,mx,my))
        {
            int count = 0;
            for(int i=0;i<256;i++)
            {
                int flag = 0;
                
                if(pattern[i]=='1')
                {
                    int l, b;
                    l = i%16;
                    b = i/16;
                    l*=16;
                    b*=16;
                    if (mx >= l && mx <= l+16 && my >= b && my <= b+16)
                    {
                        flag=1;
                        count+=flag;
                        if (flag == 1)
                        {
                            printf("%d %d %d\n",mx,my,flag);
                        }
                    }
                }
            }
            for(int j=0;j<256;j++)
            {
                if(count<1)
                {
                    int l, b;
                    l = j%16;
                    b = j/16;
                    l*=16;
                    b*=16;
                    if (mx >= l && mx <= l+16 && my >= b && my <= b+16)
                    {
                        printf("%d %d .\n",mx,my);
                    }
                }
            }
            
                    
        }
        glFlush();
        FsSleep(10);
    }
    return 0;
}

//
//  ps8-2.cpp
//  Assignment 8 - Problem 2
//
//  Created by Yash Patawari on 11/1/22.
//

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <ctype.h>
#include "fssimplewindow.h"
#include "yspng.h"
#include "yspngenc.h"

char* YsFgets(char str[], int maxn, FILE* fp)
{
    if (nullptr != fgets(str, maxn, fp))
    {
        int i;
        for (i = 0; 0 != str[i]; ++i)
        {
        }
        for (i = i; 0 <= i && 0 == isprint(str[i]); --i)
        {
            str[i] = 0;
        }
        return str;
    }
    return nullptr;
}

int main(void)
{
    char fName[256];
    printf("Enter File Name: ");
    YsFgets(fName, 255, stdin);
    

    YsRawPngDecoder png;
    png.Decode(fName);
    png.Flip();
    if (0 == png.wid || 0 == png.hei)
    {
        printf("Failed to load image.\n");
        return 1;
    }
    
    FsOpenWindow(16, 16, png.wid+10, png.hei+10, 1);

    for (;;)
    {
        FsPollDevice();
        int lb, mb, rb, mx, my;
        
        auto key = FsInkey();
        if (FSKEY_ESC == key)
        {
            break;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int w, h;
        FsGetWindowSize(w, h);

        glRasterPos2i(0, h-10);
        glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
        
        FsGetMouseEvent(lb, mb, rb, mx, my);
        
        
//        if (mx<w && mx>0 && my<h && my>0 )
//        {
//            printf("\nMouse Cursor Coordinate: %d  %d\n", mx, my);
//            printf("Red:  %d ", png.rgba[4 * ((png.hei - my) * png.wid + mx)]);
//            printf("Green:  %d ", png.rgba[4 * ((png.hei - my) * png.wid + mx) + 1]);
//            printf("Blue:  %d ", png.rgba[4 * ((png.hei - my) * png.wid + mx) + 2]);
//        }
        
        if (mx < w-10)
        {
            if (my < h-10)
            {
                if (mx > 0)
                {
                    if (my > 0)
                    {
                        printf("Mouse Cursor Coordinate: %d  %d\n", mx, my);
                        printf("Red:  %d\n", png.rgba[4 * ((png.hei - my) * png.wid + mx)]);
                        printf("Green:  %d\n", png.rgba[4 * ((png.hei - my) * png.wid + mx) + 1]);
                        printf("Blue:  %d\n", png.rgba[4 * ((png.hei - my) * png.wid + mx) + 2]);
                    }
                }
            }
        }
        
        if(lb==1)
        {
            glColor3ub(0,0,255);
            glBegin(GL_QUADS);
            glVertex2i(mx-2.5, my-2.5);
            glVertex2i(mx+2.5, my-2.5);
            glVertex2i(mx+2.5, my+2.5);
            glVertex2i(mx-2.5, my+2.5);
            glEnd();
            png.rgba[4 * ((png.hei - my) * png.wid + mx)] = 0;
            png.rgba[4 * ((png.hei - my) * png.wid + mx) + 1] = 0;
            png.rgba[4 * ((png.hei - my) * png.wid + mx) + 2] = 255;
//            printf("Red:  %d ", png.rgba[4 * ((png.hei - my) * png.wid + mx)]);
//            printf("Green:  %d ", png.rgba[4 * ((png.hei - my) * png.wid + mx) + 1]);
//            printf("Blue:  %d ", png.rgba[4 * ((png.hei - my) * png.wid + mx) + 2]);
            
        }
//        else if(lb==0)
//        {
//            glClearColor(0,0,0,0);
//        }
        FsSwapBuffers();
        FsSleep(10);
    }
    return 0;
}

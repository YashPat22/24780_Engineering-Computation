//
//  ps3-1.cpp
//  Assignment 3 - Problem 1
//
//  Created by Yash Patawari on 9/16/22.
//
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "fssimplewindow.h"


const int head[]=
{
148,307, 148,267, 140,252, 134,238, 114,256, 94,265,  79,268,  84,261,
85,248,  73,262,  63,278,  60,290,  49,264,  41,234,  43,221,  47,213,
46,193,  38,216,  32,179,  34,147,  44,129,  52,121,  54,109,  57,106,
81,105,  91,109,  91,98,   107,110, 147,122, 164,122, 163,116, 153,105,
135,102, 149,98,  165,102, 179,107, 174,97,  187,101, 204,114, 205,105,
199,96,  211,104, 223,116, 228,92,  239,72,  245,63,  257,57,  259,82,
265,98,  281,79,  298,69,  308,70,  303,86,  302,100, 301,131, 294,151,
306,143, 296,157, 289,171, 296,166, 306,164, 295,177, 290,193, 289,222,
};
const int body[]=
{
305,273, 317,286, 348,293, 380,295, 429,293, 471,285, 499,281, 523,278,
525,249, 520,210, 505,153, 509,152, 524,169, 541,198, 551,226, 556,241,
568,228, 562,242, 559,254, 567,245, 561,262, 560,279, 576,289, 612,318,
641,354, 664,397, 670,414, 661,406, 672,442, 664,436, 669,477, 664,515,
653,547, 643,560, 629,567, 599,568, 567,565, 560,559, 558,554, 561,545,
569,538, 576,536, 578,531, 576,523, 569,526, 571,518, 568,507, 559,512,
560,499, 554,488, 507,500, 447,511, 410,517, 390,516, 400,527, 386,528,
366,523, 377,532, 345,533, 309,529, 283,518, 277,538, 268,553, 253,562,
221,566, 192,565, 173,561, 169,551, 173,543, 182,537, 173,537, 186,531,
196,525, 187,524, 197,518, 203,506, 202,480, 194,466, 178,448, 180,459,
170,448, 164,434, 164,446, 157,436, 152,418,
};
const int scarf[]=
{
148,307, 131,332, 121,348, 120,368, 132,388, 142,409, 147,428, 155,415,
190,384, 239,351, 283,315, 299,292, 305,274, 308,248, 305,227, 299,218,
294,214, 290,218, 279,243, 245,283, 205,306, 146,340, 148,307,
};
const int headLen=sizeof(head)/sizeof(head[0]);
const int bodyLen=sizeof(body)/sizeof(body[0]);
const int scarfLen=sizeof(scarf)/sizeof(scarf[0]);

int main(void)
{
    int xhead[headLen/2],yhead[headLen/2];
    int xbody[bodyLen/2],ybody[bodyLen/2];
    int xscarf[scarfLen/2],yscarf[scarfLen/2];
    for(int i=0;i<headLen/2;i++)
    {
        xhead[i] = head[i*2];
        yhead[i] = head[(i*2)+1];
    }
    for(int j=0;j<bodyLen/2;j++)
    {
        xbody[j] = body[j*2];
        ybody[j] = body[(j*2)+1];
    }
    for(int k=0;k<scarfLen/2;k++)
    {
        xscarf[k] = scarf[k*2];
        yscarf[k] = scarf[(k*2)+1];
    }

    FsOpenWindow(16,16,800,600,0);
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    for(;;)
    {
            
        glColor3ub(0,0,0);
        glBegin(GL_LINE_STRIP);
        for(int a=0;a<headLen/2;a++)
        {
            glVertex2i(xhead[a],yhead[a]);
        }
        glEnd();
        glBegin(GL_LINE_STRIP);
        for(int b=0;b<bodyLen/2;b++)
        {
            glVertex2i(xbody[b],ybody[b]);
        }
        glEnd();
        glColor3ub(255,0,0);
        glBegin(GL_LINE_STRIP);
        for(int c=0;c<scarfLen/2;c++)
        {
            glVertex2i(xscarf[c],yscarf[c]);
        }
        glEnd();

        FsPollDevice();
        auto key=FsInkey();
        if(FSKEY_ESC==key)
        {
            break;
        }
            
        glFlush();
        //FsSwapBuffers();

        FsSleep(10);
        }
    return 0;
}

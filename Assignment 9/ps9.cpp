#include <stdio.h>
#include <iostream>
#include "fssimplewindow.h"

const int WindowSize = 256;
class CharBitmap
{
private:
    int wid,hei;
    const char *dat;
protected:
    char *newdat;
    int newwid,newhei;
public:
    CharBitmap();
    CharBitmap(const CharBitmap& bmp);
    CharBitmap& operator=(const CharBitmap& bp) //Assignment Operator
    {
        //std::cout<<"\nAssignment Operator Called\n";
        SetBitmap(bp.newwid, bp.newhei, bp.newdat);
        return *this;
    }
    ~CharBitmap();
    void CleanUp(void);

    int GetWidth(void);
    int GetHeight(void);
    void SetBitmap(int bmpWid,int bmpHei,char bmp[]);
    void SetPixel(int x,int y,char c);

    void Print(void);
    void Draw(void);
    char GetPixel(int x,int y);
};

CharBitmap::CharBitmap()
{
    hei=0;
    wid=0;
//    std::cout<<"\nConstructor Called\n";
    newwid=0;
    newhei=0;
    newdat=new char[WindowSize];
}

CharBitmap::CharBitmap(const CharBitmap& bit) //Copy Constructor
{
//    std::cout<<"\nCopy Constructor Called\n";
    SetBitmap(bit.newwid, bit.newhei, bit.newdat);
//    newwid = 16;
//    newhei = 16;
//    newdat = "pattern";
}

CharBitmap::~CharBitmap()
{
    CleanUp();
}

void CharBitmap::CleanUp(void)
{
    newwid=0;
    newhei=0;
    if(NULL!=newdat)
    {
        //delete[] newdat;
        newdat=NULL;
        delete[] newdat;
//        std::cout<<"\nDestructor Called\n";
    }
}

int CharBitmap::GetWidth(void)
{
    return newwid;
}

int CharBitmap::GetHeight(void)
{
    return newhei;
}

void CharBitmap::SetBitmap(int bmpWid,int bmpHei,char bmp[])
{
    newwid = bmpWid;
    newhei = bmpHei;
    dat = bmp;
    newdat = bmp;
    //strcpy(newdat,dat);
}

void CharBitmap::SetPixel(int x,int y,char c)
{
    if(0<=x && x<newwid && 0<=y && y<newhei)
    {
        newdat[y*newhei+x] = c;
    }
    else
    {
        std::cout<<"\nCannot Set Pixel outside the Bitmap\n";
    }
}

void CharBitmap::Print(void)
{
    int x,y;
    for(y=0; y<newhei; y++)
    {
        for(x=0; x<newwid; x++)
        {
            printf("%c",GetPixel(x,y));
        }
        printf("\n");
    }
}

void CharBitmap::Draw(void)
{
    
    for(int i=0;i<256;i++)
    {
        if(newdat[i]=='1')
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
    for(int j=0;j<256;j++)
    {
        if(newdat[j]=='.')
        {
            int l, b;
            l = j%16;
            b = j/16;
            l*=16;
            b*=16;
            glColor3f(255, 255, 255);
            glBegin(GL_QUADS);
            glVertex2i(l, b);
            glVertex2i(l + 16, b);
            glVertex2i(l + 16, b + 16);
            glVertex2i(l, b + 16);
            glEnd();
        }
    }
}

char CharBitmap::GetPixel(int x,int y)
{
    if(0<=x && x<newwid && 0<=y && y<newhei)
    {
        return newdat[y*newhei+x];
    }
    return 0;
}

int main(void)
{
    char pattern[]=
    {
        "....11....11...."
        "...1..1..1..1..."
        "...1.11..1.11..."
        "...1.11..1.11..."
        "...1.11..1.11..."
        "...1.11..1.11..."
        "...1.11..1.11..."
        "...1.11111.11..."
        "..1..........1.."
        ".1............1."
        "1..............1"
        "1..............1"
        "1..............1"
        "1......11......1"
        ".11..........11."
        "...1111111111..."
    };

    CharBitmap bmp;
//    CharBitmap bmp2;
//    bmp2 = bmp;
//    CharBitmap bmp3 = bmp;
    bmp.SetBitmap(16,16,pattern);
    bmp.SetPixel(4,10,'1');
    bmp.SetPixel(5,10,'1');
    bmp.SetPixel(4,11,'1');
    bmp.SetPixel(5,11,'1');
    bmp.SetPixel(10,10,'1');
    bmp.SetPixel(11,10,'1');
    bmp.SetPixel(10,11,'1');
    bmp.SetPixel(11,11,'1');
//    bmp.SetPixel(17,17,'1');
    bmp.Print();

    FsOpenWindow(16,16,256,256,1);
    while(FSKEY_NULL==FsInkey())
    {
        FsPollDevice();

        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        bmp.Draw();
        FsSwapBuffers();

        FsSleep(10);
    }

    return 0;
}

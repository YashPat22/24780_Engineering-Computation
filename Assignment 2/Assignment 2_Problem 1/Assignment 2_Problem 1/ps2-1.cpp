//
//  ps2-1.cpp
//  Assignment 2_Problem 1
//
//  Created by Yash Patawari on 9/9/22.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

void Hash(int x)
{
    for(int i=0;i<=x;i++)
    {
        printf("#");
        if(i==x)
            {
            printf("\n");
            }
    }
}

int main(void)
{
    int n;
    for(float i=0.0;i<=100.0;i+=0.1)
    {
        n = 40 + (sin(i)*40);
        Hash(n);
    }
    return 0;
}

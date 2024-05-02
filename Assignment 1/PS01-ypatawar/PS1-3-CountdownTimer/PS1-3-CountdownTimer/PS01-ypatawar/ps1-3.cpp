//
//  CountDownTimer_Debug.cpp
//  PS1-3-CountdownTimer
//
//  Created by Yash Patawari on 8/30/22.
//

#include <stdio.h>
#include <time.h>
// If you are more comfortable with std::cout / std::cin,
// you can replace C-standard library functions with std::cin and std::cout.
int main(void)
{
    printf("24-780 Engineering Computation Problem Set 1-3\n");
    printf("Enter how many seconds to count:");
    int t;
    scanf("%d",&t);
    int tEnd=time(NULL)+t;
    int prev=time(NULL);
    while(time(NULL)<tEnd)
    {
        if(prev!=time(NULL))
        {
            printf("%d\n",tEnd-time(NULL));
            prev=time(NULL);
        }
    }
    printf("Time is up.\n");
    
    return 0;
}

//
//  ps2-2.cpp
//  Assignment 2_Problem 2
//
//  Created by Yash Patawari on 9/10/22.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void SwapInt(int &a,int &b)
{
    int c;
    c=b;
    b=a;
    a=c;
}

void SetRandomNumberSeed(void)
{
    srand(time(NULL));
}

int GenerateRandomNumber(void)
{
    return rand()%10;
}

void Generate_Flashcard_Array_Ordered(int ord_array[])
{
    for(int i=0;i<144;i++)
    {
        ord_array[i] = i;
    }
}

void Shuffle(int arr[],int num)
{
    SetRandomNumberSeed();
    for(int i=0;i<num;i++)
    {
        int n=GenerateRandomNumber();
        SwapInt(arr[i],arr[n]);
    }
}

int main(void)
{
    int correct_count=0;
    int wrong_count=0;
    int total_count=0;
    int number_input;
    int answer;
    int percent;
    time_t begin,end;
    for(;;)
    {
        std::cout<<"Enter number of flash cards to work on (between 1-144) \n";
        std::cin>>number_input;
        if(number_input>=1 && number_input<=144)
        {
            break;
        }
        else
        {
            std::cout<<"The number of cards must be between 1 and 144 \n";
            continue;
        }
    }
    int Flashcard_Array[144];
    Generate_Flashcard_Array_Ordered(Flashcard_Array);
    Shuffle(Flashcard_Array,144);
    
    time(&begin);
    for(int i=0;i<number_input;i++)
    {
        total_count++;
        int num1 = int(Flashcard_Array[i]/12)+1;
        int num2 = int(Flashcard_Array[i]%12)+1;
        std::cout<<"\nEnter Answer for "<<num1<<" x "<<num2<<std::endl;
        std::cin>>answer;
        std::cout<<"\n";
        if(answer==(num1*num2))
        {
            correct_count++;
            continue;
        }
        else
        {
            wrong_count++;
            std::cout<<"Wrong! \n";
            std::cout<<"Correct answer is: "<<num1*num2<<std::endl;
            continue;
        }
    }
    time(&end);
    time_t t = end - begin;
    
    percent = ((correct_count*100)/total_count);
  
    std::cout<<"\nResults: \n";
    std::cout<<"You answered "<<total_count<<" problems in "<<t<<" seconds\n";
    std::cout<<"You answered "<<correct_count<<" problems correctly (";
    std::cout<<percent<<"%) \n";
    
    return 0;
    
}


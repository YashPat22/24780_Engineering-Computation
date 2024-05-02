//
//  ps6-1.cpp
//  Assignment 6 - Problem 1
//
//  Created by Yash Patawari on 10/9/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <ctype.h>


int Parse(int wordIndex[],int wordLen[],int maxNumWords,char line[])
{
    int numWords=0;

    int state=0;
    for(int i=0; 0!=line[i]; ++i)
    {
        auto c=line[i];
        switch(state)
        {
        case 0:
            if(' '!=c && '\t'!=c && '\n'!=c)
            {
                if(numWords<maxNumWords)
                {
                    state=1;
                    wordIndex[numWords]=i;
                    wordLen[numWords]=1;
                    ++numWords;
                }
                else
                {
                    goto EXIT;
                }
            }
            break;
        case 1:
            if(' '==c || '\t'==c || '\n'==c)
            {
                state=0;
            }
            else
            {
                ++wordLen[numWords-1];
            }
            break;
        }
    }
EXIT:
    return numWords;
}


void RemoveTailControlCode(char str[])
{
    int i,lng;
    lng=strlen(str);
    for(i=lng-1; i>=0; i--)
    {
        if(isprint(str[i])==0)
        {
            str[i]=0;
            
        }
        else
        {
            break;
        }
    }
}


void SafeStrCpy(char dst[],char src[],int nLetters,int nLimit)
{
    int i,stopper;
    if(nLetters<nLimit)
    {
        stopper=nLetters;
    }
    else
    {
        stopper=nLimit;
    }
    for(i=0; i<stopper; i++)
    {
        dst[i]=src[i];
    }
    dst[stopper]=0;
}

int main(void)
{
    char keyword[256];
    int app=0;
    char fName[256];
    printf("Enter file name>");
    fgets(fName,255,stdin);
    printf("Enter keyword>");
    fgets(keyword,255,stdin);
    for(int i=0; 0!=fName[i]; ++i)
    {
        if(fName[i]<' ')
        {
            fName[i]=0;
            break;
        }
    }
    
    int keylen = strlen(keyword);
    //std::cout<<keylen<<std::endl;
    for(int i=0;i<keylen;i++)
    {
        keyword[i] = tolower(keyword[i]);
    }
    //printf("%s",keyword);
    
    FILE *fp=fopen(fName,"r");
    if(nullptr!=fp)
    {
        char str[256];
        char strcopy[255];
        int wordNum=1;
        int linenum=1;
        while(nullptr!=fgets(str,255,fp))
        {
            int length=0;
            str[255]=0;
            //linenum++;
            RemoveTailControlCode(str);
            int wordIdx[127],wordLen[127];
            int numWords=Parse(wordIdx,wordLen,127,str);
            //printf("%s\n",str);
            for(int j=0;j<255;j++)
            {
                strcopy[j] = tolower(str[j]);
            }
            for(int i=0; i<numWords; ++i)
            {
                char word[256],newword[256];
                int len=wordLen[i];
                if(256<=len)
                {
                    len=255;
                }
                strncpy(word,str+wordIdx[i],len);
                word[len]=0;
                
                for(int j=0;j<len;j++)
                {
                    word[j] = tolower(word[j]);
                }
                
            }
            for(int i=0;i<255-keylen;i++)
            {
                length=0;
                for(int j=0;j<keylen;j++)
                {
                    if(strcopy[i+j]==keyword[j])
                    {
                        length+=1;
                    }
                }
                if(length+1==keylen)
                {
                    app++;
                    printf("%d:%s\n",linenum,str);
                }
            }
            linenum+=1;
        }
        fclose(fp);
    }
    else
    {
        printf("File cannot be opened.\n");
    }
    
    printf("Appeared %d times\n",app);
    return 0;
}

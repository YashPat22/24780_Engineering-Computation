#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "fssimplewindow.h"


void PhysicalCoordToScreenCoord(int &sx,int &sy,double px,double py)
{
	sx=(int)(px*10.0);
	sy=600-(int)(py*10.0);
}

void DrawCircle(int cx,int cy,int rad,int fill)
{
    const double YS_PI=3.1415927;

    if(0!=fill)
    {
        glBegin(GL_POLYGON);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }

    int i;
    for(i=0; i<64; i++)
    {
        double angle=(double)i*YS_PI/32.0;
        double x=(double)cx+cos(angle)*(double)rad;
        double y=(double)cy+sin(angle)*(double)rad;
        glVertex2d(x,y);
    }

    glEnd();
}

void DrawRect(int x1,int y1,int x2,int y2,int fill)
{
    if(0!=fill)
    {
        glBegin(GL_QUADS);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }

    glVertex2i(x1,y1);
    glVertex2i(x2,y1);
    glVertex2i(x2,y2);
    glVertex2i(x1,y2);

    glEnd();
}

void DrawLine(int x1,int y1,int x2,int y2)
{
    glBegin(GL_LINES);

    glVertex2i(x1,y1);
    glVertex2i(x2,y2);

    glEnd();
}

int CheckHitTarget(
    double missileX,double missileY,
    double targetX,double targetY,double targetSizeX,double targetSizeY)
{
    int relativeX,relativeY;
    relativeX=missileX-targetX;
    relativeY=missileY-targetY;
    if(0<=relativeX && relativeX<targetSizeX && 0<=relativeY && relativeY<targetSizeY)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void DrawArtillery(double x,double y,double angle)
{
	int sx,sy;
	PhysicalCoordToScreenCoord(sx,sy,x,y);

    glColor3ub(0,0,255);
    DrawRect(sx-5,sy-5,sx+5,sy+5,1);

	int vx,vy;
	PhysicalCoordToScreenCoord(vx,vy,x+3.0*cos(angle),y+3.0*sin(angle));

    DrawLine(sx,sy,vx,vy);
}

void DrawCannonBall(double x,double y)
{
	int sx,sy;
	PhysicalCoordToScreenCoord(sx,sy,x,y);

    glColor3ub(rand()%256,rand()%256,rand()%256);
    DrawCircle(sx,sy,5,1);
}

void MoveCannon(double &x,double &y,double &vx,double &vy,double m,double dt)
{
    x+=vx*dt;
    y+=vy*dt;

    vy-=9.8*dt;
}

void FireCannon(
    double &cx,double &cy,double &vx,double &vy,
    double artX,double artY,double artAngle,double iniVel)
{
    cx=artX;
    cy=artY;
    vx=iniVel*cos(artAngle);
    vy=iniVel*sin(artAngle);
}

void GenerateObstacle(
    int nObstacle,int obstacleState[],double obstacleX[],double obstacleY[],double obstacleW[],double obstacleH[])
{
    int i;
    for(i=0; i<nObstacle; i++)
    {
        obstacleState[i]=1;
        obstacleX[i]=(double)(10+rand()%70);
        obstacleY[i]=(double)(rand()%60);
        obstacleW[i]=(double)(8+rand()%8);
        obstacleH[i]=(double)(8+rand()%8);

        // The following if-statements forces the effective size of the
        // obstacle to be between 8x8 and 15x15.
        if(80.0<obstacleX[i]+obstacleW[i])
        {
            obstacleX[i]=80.0-obstacleW[i];
        }
        if(60.0<obstacleY[i]+obstacleH[i])
        {
            obstacleY[i]=60.0-obstacleH[i];
        }
    }
}

void DrawObstacle(
    int nObstacle,int obstacleState[],double obstacleX[],double obstacleY[],double obstacleW[],double obstacleH[])
{
    for(int i=0; i<nObstacle; i++)
    {
		int x1,y1,x2,y2;
		PhysicalCoordToScreenCoord(x1,y1,obstacleX[i],obstacleY[i]);
		PhysicalCoordToScreenCoord(x2,y2,obstacleX[i]+obstacleW[i],obstacleY[i]+obstacleH[i]);
		if(0==obstacleState[i])
		{
			glColor3ub(0,0,255);
		}
		else
		{
			glColor3ub(0,255,0);
		}
        DrawRect(x1,y1,x2,y2,obstacleState[i]);
    }
}

void DrawTarget(
    double targetX,double targetY,double targetW,double targetH)
{
	int x1,y1,x2,y2;
	PhysicalCoordToScreenCoord(x1,y1,targetX,targetY);
	PhysicalCoordToScreenCoord(x2,y2,targetX+targetW,targetY+targetH);

    glColor3ub(255,0,0);
    DrawRect(x1,y1,x2,y2,1);
}

void MoveTarget(double &targetX,double &targetY,const double dt)
{
	targetY-=10*dt;
	if(0>targetY)
	{
		targetY=60.0;
	}
}

void DrawTrajectory(int nPnt,const double pnt[])
{
	if(2<=nPnt)
	{
		glColor3ub(0,0,0);
		glBegin(GL_LINE_STRIP);

		int i;
		for(i=0; i<nPnt; i++)
		{
			int sx,sy;
			PhysicalCoordToScreenCoord(sx,sy,pnt[i*2],pnt[i*2+1]);
			glVertex2i(sx,sy);
		}

		glEnd();
	}
}

const int nObstacle=5;

int main(void)
{
    int i,nShot;
    double artX,artY,artAngle;
    const double PI=3.1415927;

	const int maxNumTrj=200;
	int nTrj=0;
	double trj[maxNumTrj*2];

	int explosionCount=0;
	double expX[10],expY[10];
	int expT[10];

    artX=5.0;
    artY=5.0;
    artAngle=PI/6.0;

    srand(time(NULL));

    int cannonState;
    double cannonX,cannonY,cannonVx,cannonVy;
    cannonState=0;

    double targetState=1,targetX,targetY,targetW,targetH;
    targetX=70.0;
    targetY=60.0;
    targetW=10.0;
    targetH=10.0;

    FsOpenWindow(16,16,800,600,1);

    int obstacleState[nObstacle];
    double obstacleX[nObstacle],obstacleY[nObstacle];
    double obstacleW[nObstacle],obstacleH[nObstacle];
    GenerateObstacle(nObstacle,obstacleState,obstacleX,obstacleY,obstacleW,obstacleH);


    FsPollDevice();

    nShot=0;
    while(0!=targetState || 0<explosionCount)
    {
        FsPollDevice();
		auto key=FsInkey();

        switch(key)
        {
        case FSKEY_SPACE:
            if(cannonState==0)
            {
                cannonState=1;
                FireCannon(
                    cannonX,cannonY,cannonVx,cannonVy,
                    artX,artY,artAngle,40.0);
                nShot++;
				nTrj=0;
            }
            break;
        }
		if(FSKEY_ESC==key)
		{
			break;
		}

		artAngle+=PI/90.0;
		if(PI/2.0<artAngle)
		{
			artAngle=0.0;
		}

		MoveTarget(targetX,targetY,0.025);

        if(cannonState==1)
        {
            MoveCannon(cannonX,cannonY,cannonVx,cannonVy,1.0,0.02);
            if(cannonY<0.0 || cannonX<0.0 || 80.0<cannonX)
            {
                cannonState=0;
            }

			if(nTrj<maxNumTrj)
			{
				trj[nTrj*2  ]=cannonX;
				trj[nTrj*2+1]=cannonY;
				nTrj++;
			}

            for(i=0; i<nObstacle; i++)
            {
                if(obstacleState[i]==1 && 
                   CheckHitTarget(cannonX,cannonY,obstacleX[i],obstacleY[i],obstacleW[i],obstacleH[i])==1)
                {
                    printf("Hit Obstacle!\n");
                    obstacleState[i]=0;
                    cannonState=0;
                }
            }

            if(0!=targetState && CheckHitTarget(cannonX,cannonY,targetX,targetY,targetW,targetH)==1)
            {
                printf("Hit Target!\n");
                printf("You fired %d shots.\n",nShot);

                explosionCount=200;
                targetState=0;
                cannonState=0;
                for(int i=0; i<10; ++i)
                {
					expX[i]=targetX+(double)(rand()%50-25)/10.0;
					expY[i]=targetY+(double)(rand()%50-25)/10.0;
					expT[i]=i*5;
				}
            }
        }

		if(0<explosionCount)
		{
			for(int i=0; i<10; ++i)
			{
				expT[i]+=3;
				expT[i]%=50;
			}
			--explosionCount;
		}


        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        DrawArtillery(artX,artY,artAngle);
        DrawObstacle(nObstacle,obstacleState,obstacleX,obstacleY,obstacleW,obstacleH);

		if(0<explosionCount)
		{
			for(int i=0; i<10; ++i)
			{
				int x,y;
				PhysicalCoordToScreenCoord(x,y,expX[i],expY[i]);
				glColor3ub(rand()%256,rand()%256,rand()%256);
				DrawCircle(x,y,expT[i],1);
			}
		}

		if(0!=targetState)
		{
	        DrawTarget(targetX,targetY,targetW,targetH);
		}

        if(cannonState==1)
        {
            DrawCannonBall(cannonX,cannonY);
			DrawTrajectory(nTrj,trj);
        }
        FsSwapBuffers();

        FsSleep(25);
    }

    return 0;
}

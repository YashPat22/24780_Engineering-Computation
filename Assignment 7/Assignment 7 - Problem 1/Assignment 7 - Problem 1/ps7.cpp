//
//  ps7.cpp
//  Assignment 7 - Problem 1
//
//  Created by Yash Patawari on 10/25/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include "fssimplewindow.h"

const double PI = 3.1415927;
const int nObstacle = 5;
const int nBalls = 5;
const int iniVel = 40;
const double dt = 0.025;
const int m = 1;
const int maxNumTrj = 200;

void PhysicalCoordToScreenCoord(int& sx, int& sy, double px, double py)
{
    sx = (int)(px * 10.0);
    sy = 600 - (int)(py * 10.0);
}

void DrawCircle(int cx, int cy, int rad, int fill)
{
    const double YS_PI = 3.1415927;

    if (0 != fill)
    {
        glBegin(GL_POLYGON);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }

    int i;
    for (i = 0; i < 64; i++)
    {
        double angle = (double)i * YS_PI / 32.0;
        double x = (double)cx + cos(angle) * (double)rad;
        double y = (double)cy + sin(angle) * (double)rad;
        glVertex2d(x, y);
    }
    glEnd();
}

void DrawRect(int x1, int y1, int x2, int y2, int fill)
{
    if (0 != fill)
    {
        glBegin(GL_QUADS);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }

    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);

    glEnd();
}

void DrawLine(int x1, int y1, int x2, int y2)
{
    glBegin(GL_LINES);

    glVertex2i(x1, y1);
    glVertex2i(x2, y2);

    glEnd();
}

void DrawTrajectory(int nPnt, const double pnt[])
{
    if (2 <= nPnt)
    {
        glColor3ub(0, 0, 0);
        glBegin(GL_LINE_STRIP);

        int i;
        for (i = 0; i < nPnt; i++)
        {
            int sx, sy;
            PhysicalCoordToScreenCoord(sx, sy, pnt[i * 2], pnt[i * 2 + 1]);
            glVertex2i(sx, sy);
        }

        glEnd();
    }
}

class Artillery
{
public:
    double artX = 5.0, artY = 5.0, artAngle = PI / 6;
    void Draw(void);
};

void Artillery::Draw()
{
    int sx, sy;
    PhysicalCoordToScreenCoord(sx, sy, artX, artY);

    glColor3ub(0, 0, 255);
    DrawRect(sx - 5, sy - 5, sx + 5, sy + 5, 1);

    int vx, vy;
    PhysicalCoordToScreenCoord(vx, vy, artX + 3.0 * cos(artAngle), artY + 3.0 * sin(artAngle));

    DrawLine(sx, sy, vx, vy);
}

class CannonBall
{
public:
    int cannonState = 0;
    double cannonX, cannonY, cannonVx, cannonVy;
    void Fire(double artX, double artY, double artAngle);
    void Move(void);
    void Draw(void);
};

void CannonBall::Fire(double artX, double artY, double artAngle)
{
    cannonX = artX;
    cannonY = artY;
    cannonVx = iniVel * cos(artAngle);
    cannonVy = iniVel * sin(artAngle);
}

void CannonBall::Move(void)
{
    cannonX += cannonVx * dt;
    cannonY += cannonVy * dt;
    cannonVy -= 9.8 * dt;
}

void CannonBall::Draw(void)
{
    int sx, sy;
    PhysicalCoordToScreenCoord(sx, sy, cannonX, cannonY);
    glColor3ub(rand() % 256, rand() % 256, rand() % 256);
    DrawCircle(sx, sy, 5, 1);
}

class Obstacle
{
public:
    int obstacleState[nObstacle];
    double obstacleX[nObstacle], obstacleY[nObstacle];
    double obstacleW[nObstacle], obstacleH[nObstacle];
    void GenerateObstacle(int i);
    void DrawObstacle(int i);
    int CheckHitByCannonBall(double bx, double by);
};

int Obstacle::CheckHitByCannonBall(double bx, double by)
{
    for (int i = 0;i < nObstacle;i++)
    {
        int relativeX, relativeY;
        relativeX = bx - obstacleX[i];
        relativeY = by - obstacleY[i];

        if(0 <= relativeX && relativeX < obstacleW[i] && 0 <= relativeY && relativeY < obstacleH[i] && obstacleState[i] == 1)
        {
            obstacleState[i] = 0;
            return 1;
        }
    }
    return 0;
}

void Obstacle::GenerateObstacle(int i)
{
        obstacleState[i] = 1;
        obstacleX[i] = (double)(10 + rand() % 70);
        obstacleY[i] = (double)(rand() % 60);
        obstacleW[i] = (double)(8 + rand() % 8);
        obstacleH[i] = (double)(8 + rand() % 8);

        // The following if-statements forces the effective size of the
        // obstacle to be between 8x8 and 15x15.
        if (80.0 < obstacleX[i] + obstacleW[i])
        {
            obstacleX[i] = 80.0 - obstacleW[i];
        }
        if (60.0 < obstacleY[i] + obstacleH[i])
        {
            obstacleY[i] = 60.0 - obstacleH[i];
        }
}

void Obstacle::DrawObstacle(int i)
{
        int x1, y1, x2, y2;
        PhysicalCoordToScreenCoord(x1, y1, obstacleX[i], obstacleY[i]);
        PhysicalCoordToScreenCoord(x2, y2, obstacleX[i] + obstacleW[i], obstacleY[i] + obstacleH[i]);
        if (0 == obstacleState[i])
        {
            glColor3ub(0, 0, 255);
        }
        else
        {
            glColor3ub(0, 255, 0);
        }
        DrawRect(x1, y1, x2, y2, obstacleState[i]);
}

class Target
{
public:
    double targetState, targetX, targetY, targetW, targetH;
    void Move(void);
    void Draw(void);
    int CheckHitByCannonBall(double bx, double by);
    void Initialize(void);
};

void Target::Initialize()
{
    targetState = 1;
    targetX = 70.0;
    targetY = 60.0;
    targetW = 10.0;
    targetH = 10.0;
}

int Target::CheckHitByCannonBall(double bx, double by)
{
    int relativeX, relativeY;
    relativeX = bx - targetX;
    relativeY = by - targetY;
    if (0 <= relativeX && relativeX < targetW && 0 <= relativeY && relativeY < targetH)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Target::Move()
{
    targetY -= 10 * dt;
    if (0 > targetY)
    {
        targetY = 60.0;
    }
}

void Target::Draw()
{
    int x1, y1, x2, y2;
    PhysicalCoordToScreenCoord(x1, y1, targetX, targetY);
    PhysicalCoordToScreenCoord(x2, y2, targetX + targetW, targetY + targetH);

    glColor3ub(255, 0, 0);
    DrawRect(x1, y1, x2, y2, 1);
}

int main()
{
    Artillery artillery;
    CannonBall cannonball;
    Obstacle obstacle;
    Target target;

    int nTrj = 0;
    double trj[maxNumTrj * 2];

    srand(time(NULL));

    for (int i = 0;i < nObstacle;i++)
    {
        obstacle.GenerateObstacle(i);
    }
    target.Initialize();
    FsOpenWindow(0, 0, 800, 600, 1);
    for (;;)
    {
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        auto key = FsInkey();
        if (FSKEY_ESC == key)
        {
            break;
        }
        if (FSKEY_SPACE == key)
        {
            if (cannonball.cannonState == 0)
            {
                cannonball.cannonState = 1;
                cannonball.Fire(artillery.artX, artillery.artY, artillery.artAngle);
                nTrj = 0;
            }
        }
        artillery.artAngle += PI / 90.0;
        if (PI / 2.0 < artillery.artAngle)
        {
            artillery.artAngle = 0.0;
        }
        if (cannonball.cannonState == 1)
        {
            cannonball.Move();
            if (cannonball.cannonY < 0.0 || cannonball.cannonX < 0.0 || 80.0 < cannonball.cannonX || 60 < cannonball.cannonY)
            {
                cannonball.cannonState = 0;
            }
            if (obstacle.CheckHitByCannonBall(cannonball.cannonX, cannonball.cannonY)==1)
            {
                printf("Hit Obstacle!\n");
                cannonball.cannonState = 0;
            }
            if (target.CheckHitByCannonBall(cannonball.cannonX, cannonball.cannonY) == 1)
            {
                printf("Hit Target!\n");
                target.targetState == 0;
                cannonball.cannonState == 0;
                break;
            }
            if (nTrj < maxNumTrj)
            {
                trj[nTrj * 2] = cannonball.cannonX;
                trj[nTrj * 2 + 1] = cannonball.cannonY;
                nTrj++;
            }
        }
        if (cannonball.cannonState == 1)
        {
            cannonball.Draw();
            DrawTrajectory(nTrj, trj);
        }
        artillery.Draw();
        for (int i = 0;i < nObstacle;i++)
        {
            obstacle.DrawObstacle(i);
        }
        target.Move();
        target.Draw();
        FsSwapBuffers();
        FsSleep(20);
    }
    return 0;
}

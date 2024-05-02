#include <stdio.h>
#include <math.h>
#include <iostream>
#include "fssimplewindow.h"

const double YsPi=3.1415927;

double MeasureCornerAngle(int nCoord,const double coord[],int index)
{
    if(index < 1 || index>nCoord-2)
    {
        return 0.0;
    }
    double vector1[2] = {coord[2*(index)] - coord[2*(index-1)], coord[2*(index)+1] - coord[2*(index-1)+1]};
    double vector2[2] = {coord[2*(index+1)] - coord[2*(index)], coord[2*(index+1)+1] - coord[2*(index)+1]};
    double dot = vector1[0]*vector2[0] + vector1[1]*vector2[1];
    double len_v1 = sqrt(pow(vector1[0], 2) + pow(vector1[1], 2));
    double len_v2 = sqrt(pow(vector2[0], 2) + pow(vector2[1], 2));
    double angle = acos(dot/(len_v1*len_v2));
    return angle;
}

void DrawLineSegments(int nCoord,const double coord[],int mx,int my,int lb)
{
    int color_ind = 0;
    int r[3] = {255, 0, 0};
    int g[3] = {0, 255, 0};
    int b[3] = {0, 0, 255};

    int x=50;
    for(int i = 0; i < nCoord-1; ++i)
    {
        if(MeasureCornerAngle(nCoord, coord, i)>60*YsPi/180)
        {
            glColor3ub(r[color_ind], g[color_ind], b[color_ind]);
            ++color_ind;
        }
        else
        {
            glColor3ub(0,0,0);
            color_ind = 0;
        }
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2d(coord[2*i], coord[2*i+1]);
        glVertex2d(coord[2*(i+1)], coord[2*(i+1)+1]);
        glEnd();
        double X1 = coord[2*i];
        double X2 = coord[2*(i+1)];
        double Y1 = coord[2*i+1];
        double Y2 = coord[2*(i+1)+1];
        double slope = (Y2-Y1)/(X2-X1);
        
        double dist1 = sqrt(pow((X1-mx),2)+pow((Y1-my),2));
        double dist2 = sqrt(pow((X2-mx),2)+pow((Y2-my),2));
        
        double a=slope;
        double b=-1;
        double c=Y1-(slope*X1);
        double d = ((a*mx)+(b*my)+c)/sqrt(pow(a,2)+pow(b,2));
        
        if(d<0)
        {
            d*=-1;
        }
        
        if(d<=50.0 && (mx>=X1 && mx<=X2 && my>=Y1 && my<=Y2)||(mx<=X1 && mx>=X2 && my<=Y1 && my>=Y2)||(mx<=X1 && mx>=X2 && my>=Y1 && my<=Y2)||(mx>=X1 && mx<=X2 && my<=Y1 && my>=Y2) && lb==1)
        {
            x=i;
        }
    }
    if(x>=0 && x<nCoord*2 && lb==1)
    {
        glLineWidth(5);
        glBegin(GL_LINES);
        glVertex2d(coord[2*x], coord[2*x+1]);
        glVertex2d(coord[2*(x+1)], coord[2*(x+1)+1]);
        glEnd();
//        glLineWidth(1);
    }
}

int main(void)
{
	const int nCoord=16;
	const double coord[nCoord*2]=
	{
		747.000000, 171.000000,
		297.000000, 171.000000,
		279.441871, 172.729325,
		262.558491, 177.850842,
		246.998679, 186.167735,
		233.360390, 197.360390,
		  6.167735, 426.998679,
		 24.875801, 439.499009,
		 69.875801, 394.499009,
		 88.583867, 406.999340,
		265.180195, 229.180195,
		271.999340, 223.583867,
		279.779246, 219.425421,
		288.220936, 216.864662,
		297.000000, 216.000000,
		747.000000, 216.000000
	};

	for(int i=1; i<nCoord-1; i++)
	{
		printf("Corner %d  Angle %lf\n",i,MeasureCornerAngle(nCoord,coord,i)*180.0/YsPi);
	}
    int lb,mb,rb,mx,my;

	FsOpenWindow(16,16,800,600,1);

	int key=FSKEY_NULL;
	while(FSKEY_ESC!=key)
	{
		FsPollDevice();
		key=FsInkey();

		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        
        if(FSMOUSEEVENT_MOVE==FsGetMouseEvent(lb,mb,rb,mx,my))
        {
//            std::cout<<"lb: "<<lb<<"mx: "<<mx<<"my: "<<my<<std::endl;
            
        }
		DrawLineSegments(nCoord,coord,mx,my,lb);
		FsSwapBuffers();

		FsSleep(20);
	}
    

	return 0;
}

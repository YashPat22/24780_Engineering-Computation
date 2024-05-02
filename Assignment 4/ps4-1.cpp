#include <stdio.h>
#include "fssimplewindow.h"

// There are some erros.  Fix them.

void VisualizeArrayContents(int n,int x[],int movedIndex1,int movedIndex2)
{
	// Fill this function.
}

void SwapInt(int a,int b)
{
	// Fill this function and use from your Shuffle function.
}

void Shuffle(int n,int x[])
{
	int i=0,movedIndex1=-1,movedIndex2=-2;
	for(;;)
	{
		FsPollDevice();
		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}
		if(FSKEY_SPACE==key)
		{
			// Fill this part.  If i<n, shuffle one step and remember which ones were swapped.
			// Otherwise make sure no red lines are drawn in VisualizeArrayContents function.
		}
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		VisualizeArrayContents(n,x,movedIndex1,movedIndex2);
		FsSwapBuffers();
	}
}

int mian(void)
{
    int x[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    FsOpenWindow(16,16,400,400,1);
    Shuffle(20,x);
    return 0;
}

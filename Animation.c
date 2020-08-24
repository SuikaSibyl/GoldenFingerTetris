#include "Tetris.h"

void DrawLight()
{
	double x1,y1,x2,y2;
	double wid,hei;
	DefineColor("Light",r,g,b);
	SetPenColor("Light");
	hei=GetWindowHeight();
	Randomize();
	x1=RandomReal(0, 4);
	x2=RandomReal(0,4);
	y1=RandomReal(0,hei);
	y2=RandomReal(0,hei);
	MovePen(x1,y1);
	DrawLine(x2-x1,y2-y1);
}

void ChangeColor()
{
	switch(colorflag)
	{
		case 1:
			if(r) r=r-0.1;else colorflag=2;
			break;
		case 2:
			if(g) g-=0.1;else colorflag=3;
			break;
		case 3:
			if(b) b-=0.1;else colorflag=4;
			break;
		case 4:
			if(r!=1) r+=0.1;else colorflag=5;
			break;
		case 5:
			if(g!=1) g+=0.1;else colorflag=6;
			break;
		case 6:
			if(b!=1) b+=0.1;else colorflag=1;
			break;
	}
}

void TimerAnimationProcess(int timerID)
{
	switch(timerID)
	{
		case 1:
		DrawLight();
		break;
	}
}

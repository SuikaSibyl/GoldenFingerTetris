#include "Tetris.h"
int phf=0;int gdf=0;
void DrawAero(int x,int y) 
{
	SetPenColor("Light Gray"); 
	StartFilledRegion(1);
	DrawBox(width/3+(x-5.5)*BSIZE,height/2+(10.5-y)*BSIZE,BSIZE/4,BSIZE);
	EndFilledRegion();
	StartFilledRegion(1);
	DrawBox(width/3+(x-5.5)*BSIZE,height/2+(10.6-y)*BSIZE,BSIZE,BSIZE/7);
	EndFilledRegion();
	StartFilledRegion(1);
	DrawBox(width/3+(x-5.1)*BSIZE,height/2+(10.5-y)*BSIZE,BSIZE/8,BSIZE/2);
	EndFilledRegion();
	StartFilledRegion(1);
	DrawBox(width/3+(x-5.9)*BSIZE,height/2+(10.5-y)*BSIZE,BSIZE/8,BSIZE/2);
	EndFilledRegion();
}
void Shoot()
{
	By=1;
	Bx=Ax;
	switch(nBullet)
	{
		case 0:SetPenColor("Light Gray");break;
		case 1:SetPenColor("Green");break;
		case 2:SetPenColor("Magenta");break;
	}
	StartFilledRegion(1);
	DrawBox(width/3+(Bx-5.5)*BSIZE,height/2+(10.5-By)*BSIZE,BSIZE/8,BSIZE*0.7);
	EndFilledRegion();
	startTimer(2,100);
}
void ChangeTo2(int x,int y)
{
	Gameboard[x][y]=3;
	phf=1;
}
void ChangeTo4(int x,int y)
{
	Gameboard[x][y]=5;
	gdf=1;
}

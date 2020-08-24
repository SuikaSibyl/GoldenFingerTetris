#include "Tetris.h"

/********************************************************** 
 *  函数原型：void DrawBox(double m,double n,double x,double y)								  			*
 *  传入参数：中点横纵坐标，方框宽与长                       													*
 *  返 回 值：无                            										*
 *  函数功能：画方框	*
 **********************************************************/
void DrawBox(double m,double n,double x,double y)
{
	MovePen(m-x/2,n-y/2);
	DrawLine(x,0);
	DrawLine(0,y);
	DrawLine(-x,0);
	DrawLine(0,-y);
}
/**********************************************************
 *  函数原型：void DrawSquare(int x, int y)								*
 *  传入参数：游戏面板中的横坐标x，纵坐标y                *
 *  返 回 值：无                            							*
 *  函数功能：在坐标（x, y）处绘制方块										*
 **********************************************************/
void DrawSquare(int x, int y)
{
	if(y<1)
		return;
	DrawBox(width/3+(x-4.5)*BSIZE,height/2+(9.5-y)*BSIZE,BSIZE,BSIZE);
}
/********************************************************** 
 *  函数原型：void DrawBlock(int BlockIndex, int sx, int sy,int color)	*
 *  传入参数：形状的索引BlockIndex，绝对横坐标x，绝对纵坐标y，颜色color	*
 *  返 回 值：无                     																		*
 *  函数功能：在坐标（sx, sy）处绘制颜色为color的形状										*
 **********************************************************/
void DrawBlock(int BlockIndex, int sx, int sy,char* color)
{
	int i,c;
	StartFilledRegion(1);
	SetPenColor(color);
	for(i=0;i<7;i+=2)
		DrawSquare(arrayBlock[BlockIndex].arrXY[i]+sx, arrayBlock[BlockIndex].arrXY[i+1]+sy);
}

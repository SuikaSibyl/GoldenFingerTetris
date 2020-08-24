#include "Tetris.h"

/********************************************************** 
 *  ����ԭ�ͣ�void DrawBox(double m,double n,double x,double y)								  			*
 *  ����������е�������꣬������볤                       													*
 *  �� �� ֵ����                            										*
 *  �������ܣ�������	*
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
 *  ����ԭ�ͣ�void DrawSquare(int x, int y)								*
 *  �����������Ϸ����еĺ�����x��������y                *
 *  �� �� ֵ����                            							*
 *  �������ܣ������꣨x, y�������Ʒ���										*
 **********************************************************/
void DrawSquare(int x, int y)
{
	if(y<1)
		return;
	DrawBox(width/3+(x-4.5)*BSIZE,height/2+(9.5-y)*BSIZE,BSIZE,BSIZE);
}
/********************************************************** 
 *  ����ԭ�ͣ�void DrawBlock(int BlockIndex, int sx, int sy,int color)	*
 *  �����������״������BlockIndex�����Ժ�����x������������y����ɫcolor	*
 *  �� �� ֵ����                     																		*
 *  �������ܣ������꣨sx, sy����������ɫΪcolor����״										*
 **********************************************************/
void DrawBlock(int BlockIndex, int sx, int sy,char* color)
{
	int i,c;
	StartFilledRegion(1);
	SetPenColor(color);
	for(i=0;i<7;i+=2)
		DrawSquare(arrayBlock[BlockIndex].arrXY[i]+sx, arrayBlock[BlockIndex].arrXY[i+1]+sy);
}

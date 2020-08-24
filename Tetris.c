#include "Tetris.h"

//定义 
int Gameboard[BOARD_WIDTH+2][BOARD_HEIGHT+2];
int nCurrent_block_index;/* 当前下落的方块的索引号*/
int nNext_block_index ; /*下一个方块的索引号*/
int nSpeed, nScore; /*速度和得分*/
int nSpeedUpScore = 1000; /*第一次要加速需达到的分数*/
int bAccel, bOver;
int nOriginX=5, nOriginY=1;/*某一形状的原点的绝对坐标*/
unsigned int TimerCounter; 
int bottom=0;
FILE *namefp;
FILE *savefp;
char curuser[20];
extern struct info user;
extern struct info savestates[3];
extern char accounts[3][20];
int location=0;
double r,g,b;
int colorflag=1;

BLOCK arrayBlock[19]={
	/*x1,y1,x2,y2,x3,y3,x4,y4, color,   next*/
	{ 0,-2, 0,-1, 0, 0, 1, 0,  "Cyan",    1}, /*        */  
	{-1, 0, 0, 0, 1,-1, 1, 0,  "Cyan",    2}, /*   #    */
	{ 0,-2, 1,-2, 1,-1, 1, 0,  "Cyan",    3}, /*   #    */
	{-1,-1,-1, 0, 0,-1, 1,-1,  "Cyan",    0}, /*   ##   */

	{ 0,-2, 0,-1, 0, 0, 1,-2,"Magenta",   5}, /*        */ 
	{-1,-1,-1, 0, 0, 0, 1, 0,"Magenta",   6}, /*   ##   */
	{ 0, 0, 1,-2, 1,-1, 1, 0,"Magenta",   7}, /*   #    */
	{-1,-1, 0,-1, 1,-1, 1, 0,"Magenta",   4}, /*   #    */

	{-1, 0, 0,-1, 0, 0, 1, 0,"Yellow",    9}, /*        */
	{-1,-1, 0,-2, 0,-1, 0, 0,"Yellow",   10}, /*        */
	{-1,-1, 0,-1, 0, 0, 1,-1,"Yellow",   11}, /*   #    */
	{ 0,-2, 0,-1, 0, 0, 1,-1,"Yellow",    8}, /*  ###   */

	{-1, 0, 0,-1, 0, 0, 1,-1, "Brown",   13}, /*   ##   */
	{ 0,-2, 0,-1, 1,-1, 1, 0, "Brown",   12}, /*  ##    */

	{-1,-1, 0,-1, 0, 0, 1, 0, "Green",   15}, /*   ##    */
	{ 0,-1, 0, 0, 1,-2, 1,-1, "Green",   14}, /*   ##   */

	{ 0,-3, 0,-2, 0,-1, 0, 0,   "Red",   17},/*  #     */
	{-1, 0, 0, 0, 1, 0, 2, 0,   "Red",   16},/*  #     */
					               			 /*  #     */
					               			 /*  #     */
										                     
	{ 0,-1, 0, 0, 1,-1, 1, 0,  "Blue",   18},/*  ##    */
					               			 /*  ##    */
};
//函数申明 
void KeyboardMenuProcess(int key,int event);/*键盘消息回调函数*/

/********************************************************** 
 *  函数原型：void main()																	*
 *  传入参数：无                       										*
 *  返 回 值：无                            							*
 *  函数功能：入口函数，包含俄罗斯方块程序的主流程				*
 **********************************************************/
void Main() /*仅初始化执行一次*/
{
    InitGraphics();
    if((namefp=fopen("curuser.txt","r+"))==NULL) {
	    int i;
		for(i=0;i<=2;i++){
	    	strcpy(accounts[i],"default");
		}
		namefp=fopen("accounts.txt","w");
		for(i=0;i<=2;i++){
		    fprintf(namefp,"%s\n",accounts[i]);
		}
		fclose(namefp);
		Register(); 
	}
    else{
    	fscanf(namefp,"%s",curuser);
    	ExtractSavestates();	
	}
	InitializeMenu();
    SetWindowTitle("Tetris");
    /*else {
	    fscanf("%s",curusername);
	    fclose(namefp);
	    savefp=fopen("savestates1.txt","r+");
	    fread(&user,sizeof(struct info),1,savefp);
	    if
	}*/
    /*struct info savestates[3]={{'\0',-1},{'\0',-1},{'\0',-1}};
	int i=0;
	if((fp=fopen("savestates.txt","r+"))==NULL){
		fp=fopen("savestates.txt","w+");
		Register();
	}
	else{
		while(!feof(fp)){
			fscanf(fp,"%s %d\n",savestates[i].name,&savestates[i].best);
			i++;
		}
	}*/
}


#include "Tetris.h"

//变量定义
char pubstr[256]={'\0'}; //共用字符串 
int count=0; //用于键盘输入函数，代表输入的字符数 
int cap=0; //用于键盘输入函数，代表大小写状态 
//char PenColor[20]; //当前画笔颜色 
extern FILE *namefp; //Tetris.c中定义的文件指针
extern FILE *savefp; //Tetris.c中定义的文件指针
extern char curuser[20]; //Tetris.c中定义的字符串，长度为20（最大用户名19）
int accountsnum; 
int overwrite=0; //overwrite变量用于提示Register(), 当前状态是新建用户还是覆写用户 

/********************************************************** 
 *  函数原型：void DrawBox(double m,double n,double x,double y)								  			*
 *  传入参数：中点横纵坐标，方框宽与长                       													*
 *  返 回 值：无                            										*
 *  函数功能：画方框	*
*  检查情况：【良好】	
 **********************************************************/
void DrawBox(double m,double n,double x,double y)
{
	SetPenSize(0.01);
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
 *  函数功能：在坐标（x, y）处绘制方块
 *  检查情况：【除坐标外工作良好】											*
 **********************************************************/
void DrawSquare(int x, int y)
{
	if(y<1)
		return;
	DrawBox(width/3+(x-5.5)*BSIZE,height/2+(10.5-y)*BSIZE,BSIZE,BSIZE);
}
void DrawSquareforNEXT(int x, int y)
{
	//if(y<1)
	//	return;
	DrawBox(width*2/3+(x)*BSIZE/2,(height+BSIZE*BOARD_HEIGHT)/2-2*BSIZE-(y+1)*BSIZE/2,BSIZE/2,BSIZE/2);
}
/********************************************************** 
 *  函数原型：void DrawBlock(int BlockIndex, int sx, int sy,int color)	*
 *  传入参数：形状的索引BlockIndex，绝对横坐标x，绝对纵坐标y，颜色color	*
 *  返 回 值：无                     																		*
 *  函数功能：在坐标（sx, sy）处绘制颜色为color的形状
 *  检查情况：【除坐标外工作良好】								*
 **********************************************************/
void DrawBlock(int BlockIndex, int sx, int sy,char* color)
{
	int i,c;
	for(i=0;i<4;i+=1)
		{
		SetPenColor(color);
		StartFilledRegion(1);
		DrawSquare(arrayBlock[BlockIndex].arrXY[2*i]+sx, arrayBlock[BlockIndex].arrXY[2*i+1]+sy);
	    EndFilledRegion();
	    SetPenColor("Black");
	    DrawSquare(arrayBlock[BlockIndex].arrXY[2*i]+sx, arrayBlock[BlockIndex].arrXY[2*i+1]+sy);
		}
}
void DrawBlockforNEXT(int BlockIndex,char* color)
{
	int i,c;
	for(i=0;i<4;i+=1)
		{
		SetPenColor(color);
		StartFilledRegion(1);
		DrawSquareforNEXT(arrayBlock[BlockIndex].arrXY[2*i], arrayBlock[BlockIndex].arrXY[2*i+1]);
	    EndFilledRegion();
	    SetPenColor("Black");
	    DrawSquareforNEXT(arrayBlock[BlockIndex].arrXY[2*i], arrayBlock[BlockIndex].arrXY[2*i+1]);
		}
	SetPenColor("Yellow");
	DrawBox(width*2/3,(height+BSIZE*BOARD_HEIGHT)/2-2*BSIZE,4*BSIZE,4*BSIZE);
}
/********************************************************** 
 *  函数原型：int IsConflict(int BlockIndex, int x, int y)			*
 *  传入参数：形状的索引BlockIndex，绝对横坐标x，绝对纵坐标y		*
 *  返 回 值：无冲突返回0，有冲突返回1                        	*
 *  函数功能：判断形状是否能存在于坐标（x, y）处								*
 **********************************************************/
int IsConflict(int BlockIndex, int x, int y)
{
	int i;
	for (i=0;i<=7;i++,i++)
	{
		if (arrayBlock[BlockIndex].arrXY[i]+x<1 || arrayBlock[BlockIndex].arrXY[i]+x>10)
			return TRUE;
		if (arrayBlock[BlockIndex].arrXY[i+1]+y<1)
			continue;
		if (Gameboard[arrayBlock[BlockIndex].arrXY[i]+x][arrayBlock[BlockIndex].arrXY[i+1]+y])
			return TRUE;
	}
	return FALSE;
}
/********************************************************** 
 *  函数原型：int HandleLeft(int BlockIndex,int *x, int *y)						*
 *  传入参数：形状的索引BlockIndex，绝对横坐标的指针*x，绝对纵坐标的	*
 *            指针*y                                                  *
 *  返 回 值：无                        															*
 *  函数功能：按下左方向键时的处理函数																*
 **********************************************************/
void HandleLeft(int BlockIndex,int *x, int *y) /*按下左方向键时的处理函数*/
{
	if(!IsConflict(BlockIndex,*x-1,*y))
	{
		DrawBlock(BlockIndex,*x,*y,"Black"); /*擦除原先的形状*/
		(*x)--;
		DrawBlock(BlockIndex, *x, *y, arrayBlock[BlockIndex].nColor); /*绘制当前形状*/
	}
}
/********************************************************** 
 *  函数原型：int HandleRight(int BlockIndex,int *x, int *y)					*
 *  传入参数：形状的索引BlockIndex，绝对横坐标的指针*x，绝对纵坐标的	*
 *            指针*y                                                  *
 *  返 回 值：无                        															*
 *  函数功能：按下右方向键时的处理函数																*
 **********************************************************/
void HandleRight(int BlockIndex,int *x, int *y)/*按下右方向键时的处理函数*/
{

	if(!IsConflict(BlockIndex,*x+1,*y))
	{
		DrawBlock(BlockIndex,*x,*y,"Black"); /*擦除原先的形状*/
		(*x)++;
		DrawBlock(BlockIndex, *x, *y, arrayBlock[BlockIndex].nColor); /*绘制当前形状*/
	}
}
/********************************************************** 
 *  函数原型：int HandleUp(int BlockIndex,int *x, int *y)							*
 *  传入参数：形状的索引BlockIndex，绝对横坐标的指针*x，绝对纵坐标的	*
 *            指针*y                                                  *
 *  返 回 值：无                        															*
 *  函数功能：按下上方向键（旋转键）时的处理函数											*
 **********************************************************/
void HandleUp(int *BlockIndex,int *x, int *y) /*按下旋转键时的处理函数*/
{
	int NextBlockIndex, i;
	static int arrayOffset[5]={0,-1,1,-2,2};

	NextBlockIndex = arrayBlock[*BlockIndex].nNext;
	//for(i=0;i<5;i++)
	i=0;
		if(!IsConflict(NextBlockIndex, *x+arrayOffset[i],*y))
	{
		DrawBlock(*BlockIndex, *x, *y, "Black"); /*擦除原先的形状*/
		*BlockIndex = arrayBlock[*BlockIndex].nNext;
		(*x) += arrayOffset[i];
		DrawBlock(*BlockIndex, *x, *y, arrayBlock[*BlockIndex].nColor); /*绘制当前形状*/
	}
}
/********************************************************** 
 *  函数原型：int HandleDown(int BlockIndex,int *x, int *y)						*
 *  传入参数：形状的索引BlockIndex，绝对横坐标的指针*x，绝对纵坐标的	*
 *            指针*y                                                  *
 *  返 回 值：仍在自由下落返回0，无法下落了返回1                      *
 *  函数功能：按下向下方向键或自由下落时的处理函数										*
 **********************************************************/
int HandleDown(int BlockIndex,int *x, int *y)/*按下下方向键或自由下落时的处理函数*/
{
	char ScoreBuffer[10]={0},SpeedBuffer[10]={0};
	int i;
	int NumLinesKilled=0;
	/*if(TimerCounter>(20-nSpeed*2))*/
	{
		TimerCounter = 0; /*重置时钟中断*/
		if(!IsConflict(BlockIndex,*x,*y+1)) /*仍在下落*/
		{
			DrawBlock(BlockIndex,*x,*y,"Black"); /*擦除原先的形状*/
			(*y)++;
			DrawBlock(BlockIndex, *x, *y, arrayBlock[BlockIndex].nColor); /*绘制当前形状*/
			return FALSE;/*仍在下落返回FALSE*/
		}
		else /*无法再下落了*/
		{
			DrawBlock(BlockIndex,*x,*y,"White");
			for (i=0;i<=7;i++,i++)
			{
				if ((*y)+arrayBlock[BlockIndex].arrXY[i+1]<1)
					continue;
				Gameboard[(*x)+arrayBlock[BlockIndex].arrXY[i]][(*y)+arrayBlock[BlockIndex].arrXY[i+1]]=1;
			}

			NumLinesKilled = KillLines(*y);
			if(NumLinesKilled>0)
			{
				switch(NumLinesKilled)
				{
					case 1:
						nScore+=100;
					case 2:
						nScore+=300;
					case 3:
						nScore+=500;
					case 4:
						nScore+=800;
				}
				/*重绘计分框*/
					SetPenColor("Black");
					StartFilledRegion(1);
					DrawBox(width*2/3,(height-BSIZE*BOARD_HEIGHT)/2+2*BSIZE,4*BSIZE,4*BSIZE);
					EndFilledRegion();
					SetPenColor("Blue");
					MovePen(width*2/3-2*BSIZE,(height-BSIZE*BOARD_HEIGHT)/2+2*BSIZE+2*BSIZE+BSIZE); 
					DrawTextString("Score");
					SetPenColor("Yellow");
					DrawBox(width*2/3,(height-BSIZE*BOARD_HEIGHT)/2+2*BSIZE,4*BSIZE,4*BSIZE);
					SetPenColor("Red");
					itoa(nScore,ScoreBuffer, 10);
					MovePen(width*2/3-TextStringWidth(ScoreBuffer)/2,(height-BSIZE*BOARD_HEIGHT)/2+2*BSIZE); 
					DrawTextString(ScoreBuffer);

				if(nScore > nSpeedUpScore)
				{
					nSpeed++;
					nSpeedUpScore+= nSpeed*1000;
					/*重绘速度框*/
					SetPenColor("Black");
					StartFilledRegion(1);
					DrawBox(width*2/3,(height)/2,4*BSIZE,4*BSIZE);
					EndFilledRegion();
					SetPenColor("Blue");
					MovePen(width*2/3-2*BSIZE,(height)/2+2*BSIZE+BSIZE);
					DrawTextString("Level");
					SetPenColor("Yellow");
					DrawBox(width*2/3,(height)/2,4*BSIZE,4*BSIZE);
					SetPenColor("Red");
					itoa(nSpeed,SpeedBuffer,10);
					MovePen(width*2/3-TextStringWidth(SpeedBuffer)/2,(height)/2);
					DrawTextString(SpeedBuffer);
				}
			}
			if(IsGameOver())
				bOver = TRUE;
			
	    {
		if(nNext_block_index==-1)
		{
			nCurrent_block_index = RandomInteger(0, 18);
			nNext_block_index = RandomInteger(0, 18);
			/*绘制下一个提示形状*/
			//DrawBlock(nNext_block_index, 21,6,arrayBlock[nNext_block_index].nColor );
			DrawBlockforNEXT(nNext_block_index,arrayBlock[nNext_block_index].nColor);
		}
		else
		{
			nCurrent_block_index = nNext_block_index;
			//DrawBlock(nNext_block_index, 21,6,"Black" );
			DrawBlockforNEXT(nNext_block_index,"Black");
			nNext_block_index = RandomInteger(0, 18);
			//DrawBlock(nNext_block_index, 21,6,arrayBlock[nNext_block_index].nColor ); /*绘制下一个提示形状 */
		    DrawBlockforNEXT(nNext_block_index,arrayBlock[nNext_block_index].nColor);
		    bottom=FALSE;
		}

		nOriginX=5, nOriginY=1;

		//TimerCounter = 0;

		DrawBlock(nCurrent_block_index, nOriginX,nOriginY, arrayBlock[nCurrent_block_index].nColor );/*在面板内绘制当前形状*/
	
	    }
	
	    if(IsGameOver())
	    {
	    	cancelTimer(1);
	    	cancelTimer(2);
	    	GameOver();
		} 
		
			return TRUE; /*下落到底返回TRUE*/
		}
	}
}
/********************************************************** 
 *  函数原型：int IsLineFull(int y)												*
 *  传入参数：纵坐标y                       							*
 *  返 回 值：填满返回1，否则返回0                        *
 *  函数功能：判断第y行是否已被填满												*
 **********************************************************/
int IsLineFull(int y)
{
	int i;
	for(i=1;i<=10;i++)
		if(!Gameboard[i][y])
			return FALSE;
	return TRUE;
}
/********************************************************** 
 *  void KillLine(int y)																	*
 *  传入参数：纵坐标y                       							*
 *  返 回 值：无                            							*
 *  函数功能：消去第y行																		*
 **********************************************************/
void KillLine(int y)
{
	int i,j;
	for(j=y;j>=2;j--)
		for(i=1;i<=10;i++)
		{
			if(Gameboard[i][j]==Gameboard[i][j-1])
				continue;
			if(Gameboard[i][j-1]==FILLED)
			{
				Gameboard[i][j]=FILLED;
				StartFilledRegion(1);
				SetPenColor("White");
				DrawSquare(i,j);
			    EndFilledRegion();
			}
			else /*Gameboard[i][j-1]==EMPTY*/
			{
				Gameboard[i][j] = EMPTY;
				StartFilledRegion(1);
				SetPenColor("Black");
				DrawSquare(i,j);
			    EndFilledRegion();
			}
			SetPenColor("Black");
	        DrawSquare(i,j);
		}
}
/********************************************************** 
 *  函数原型：int KillLines(int y)												*
 *  传入参数：纵坐标y                       							*
 *  返 回 值：消去的行数                            			*
 *  函数功能：消去第y行以及与第y行连续的上面被填满的行		*
 **********************************************************/
int KillLines(int y)
{
	int i, j, LinesKilled=0;
	for(i=0;i<4;i++)
	{
		while(IsLineFull(y))
		{
			KillLine(y);
			LinesKilled++;
			i++;
		}
		y--;
		if(y<1)
			break;
	}
	return LinesKilled;
}
/********************************************************** 
 *  函数原型：int IsGameOver()														*
 *  传入参数：无                       										*
 *  返 回 值：游戏结束返回1，否则返回0                    *
 *  函数功能：判断游戏是否结束														*
 **********************************************************/
int IsGameOver()
{
	int i;
	for(i=1;i<=10;i++){
		if(Gameboard[i][1])
		return TRUE;}
	return FALSE;
}
/********************************************************** 
 *  函数原型：int GameOver()															            		*
 *  传入参数：无                       																		*
 *  返 回 值：退出游戏返回1，否则返回0                    								*
 *  函数功能：在界面上输出游戏结束信息，并根据用户按键选择决定是否退出游戏*
 **********************************************************/
int GameOver()
{
	//int key;
	int i;
	int mark;
	char strlevel[10],strscore[10];
	/* 输出游戏结束信息 */
	/*SetPenColor("Red");
	MovePen(BSIZE*15-TextStringWidth("Game  Over")/2,BSIZE*12);
	DrawTextString("Game  Over");
	SetPenColor("Green");
	MovePen(BSIZE*15-TextStringWidth("Enter : New  Game")/2,BSIZE*14);
	DrawTextString("Enter : New  Game");
	MovePen(BSIZE*15-TextStringWidth("Esc : Exit")/2,BSIZE*15);
	DrawTextString("Esc : Exit");*/
	registerKeyboardEvent(KeyboardEndProcess);
	ExtractRanking();
	mark=RankingSort();
	StartFilledRegion(1);
	SetPenColor("Black");
	DrawBox(width/2,height/2,width,height);
	EndFilledRegion();
	SetPointSize(70);
	SetPenColor("Magenta");
	MovePen(width/2-TextStringWidth("GAME OVER")/2,height*7/8);
	DrawTextString("GAME OVER");
	SetPointSize(24);
	MovePen(width/4-TextStringWidth("Player")/2,height*3/4);
	DrawTextString("Player");
	MovePen(width/2-TextStringWidth("Level")/2,height*3/4);
	DrawTextString("Level");
	MovePen(width*3/4-TextStringWidth("Score")/2,height*3/4);
	DrawTextString("Score");
	SetPointSize(18); 
	SetPenColor("Blue");
	for(i=0;i<=mark-1;i++){
		MovePen(width/4-TextStringWidth(ranking[i].player)/2,height*3/4-height/12-height*i/24);
		DrawTextString(ranking[i].player);
		itoa(ranking[i].level,strlevel,10);
		MovePen(width/2-TextStringWidth(strlevel)/2,height*3/4-height/12-height*i/24);
		DrawTextString(strlevel);
		itoa(ranking[i].score,strscore,10);
		MovePen(width*3/4-TextStringWidth(strscore)/2,height*3/4-height/12-height*i/24);
		DrawTextString(strscore);
	}
	SetPenColor("Cyan");
	MovePen(width/4-TextStringWidth(ranking[mark].player)/2,height*3/4-height/12-height*mark/24);
	DrawTextString(ranking[mark].player);
	itoa(ranking[mark].level,strlevel,10);
	MovePen(width/2-TextStringWidth(strlevel)/2,height*3/4-height/12-height*mark/24);
	DrawTextString(strlevel);
	itoa(ranking[mark].score,strscore,10);
	MovePen(width*3/4-TextStringWidth(strscore)/2,height*3/4-height/12-height*mark/24);
	DrawTextString(strscore);
	SetPenColor("Blue");
	for(i=mark+1;i<=9;i++){
		MovePen(width/4-TextStringWidth(ranking[i].player)/2,height*3/4-height/12-height*i/24);
		DrawTextString(ranking[i].player);
		itoa(ranking[i].level,strlevel,10);
		MovePen(width/2-TextStringWidth(strlevel)/2,height*3/4-height/12-height*i/24);
		DrawTextString(strlevel);
		itoa(ranking[i].score,strscore,10);
		MovePen(width*3/4-TextStringWidth(strscore)/2,height*3/4-height/12-height*i/24);
		DrawTextString(strscore);
	}
	SetPenColor("Light Gray");
	SetPointSize(22);
	MovePen(width/2-TextStringWidth("press ESC to exit")/2,height/12);
	DrawTextString("press ESC to exit");
	MovePen(width/2-TextStringWidth("press ENTER to start a new game")/2,height/6);
	DrawTextString("press ENTER to start a new game");
}

void CharIProcess(char c)
{
	double width = GetWindowWidth();
	double height = GetWindowHeight();
	double l;
	char string[2],user[2];
	//if(flag1){
	//	flag1=0;
	//	DrawTextString("_");
	//}
	//else
	{
		string[0]=c;
		string[1]='\0';
	switch(c){
		
		case VK_RETURN : 
		    location=0;
			break;
		case VK_BACK :
			if(location){
				location--;
				user[0]=pubstr[location];
				user[1]=0;
				pubstr[location]=0;
				SetPenColor("Light Gray");
				StartFilledRegion(1);
				DrawBox(GetCurrentX()-TextStringWidth(user)/2,GetCurrentY(),TextStringWidth(user),GetFontHeight()+0.1);
				EndFilledRegion();
				MovePen(GetCurrentX(),GetCurrentY()+GetFontHeight()/2+0.05);
				//cpx-=TextStringWidth("a")/2;
				SetPenColor("Magenta");
			}
			break;
		default:
			if(location<11)
			{
			DrawTextString(string);
			strcat(pubstr,string);
			count++;
			location++;}
		break;	
	}
	}
}

void CharVoidProcess(char c){} 

void Register(){
	int i;
	//registerKeyboardEvent(KeyboardIProcess);
	SetPenColor("Light Gray");
	StartFilledRegion(1);
	DrawBox(width/2,height/2,width/2,height/4);
	EndFilledRegion();
	SetPenColor("Magenta");
	//strcpy(PenColor,"Magenta");
	SetPointSize(18);
	MovePen(width/2-TextStringWidth("Please Enter Username")/2,5*height/8-height/12);
	DrawTextString("Please Enter Username");
	MovePen(width/4+1,5*height/8-height/6);
	DrawTextString("Account:");
	//MovePen(1.5,3*height/4-height/4);
	//DrawTextString("Password:");
	MovePen(GetCurrentX()+0.1,5*height/8-height/6);
	//registerCharEvent(CharIProcess);
	/*cpx=1.5+TextStringWidth("Account:");
	cpy=3*height/4-height/6;*/
	ExtractAccounts();
	if(accountsnum==3&&overwrite==0){
		/*SetPenColor("Light Gray");
		StartFilledRegion(1);
		DrawBox(width/2,height/2,width/2,height/4);
		EndFilledRegion();
		SetPointSize(22);
		SetPenColor("Magenta");
		MovePen(width/2-TextStringWidth("No more account can be created!")/2,height/2);
		DrawTextString("No more account can be created!");
		registerTimerEvent(TimerEventProcess);
		startTimer(3,1000);*/
		overwrite=1;
	    InitializeOverwrite();
	}
	else if(accountsnum<3) {
	    mark=accountsnum;
	    registerCharEvent(CharIProcess);
	    registerKeyboardEvent(KeyboardIProcess);
	} 
	else if(overwrite==1) {
	    overwrite=0;
		registerCharEvent(CharIProcess);
	    registerKeyboardEvent(KeyboardIProcess);
	}
	for(i=0;i<=255;i++){
		pubstr[i]='\0';
	}
	/*if((savefp=fopen("savestates1.txt","r"))!=NULL){
		fclose(savefp);
		if((savefp=fopen("savestates2.txt","r"))!=NULL){
			fclose(savefp);
			if((savefp=fopen("savestates3.txt","r"))!=NULL){
				SetPenColor("Light Gray");
				StartFilledRegion(1);
				DrawBox(width/2,height/2,width/2,height/4);
				EndFilledRegion();
				SetPointSize(22);
				SetPenColor("Magenta");
				MovePen(width/2-TextStringWidth("No more account can be created!")/2,height/2);
				DrawTextString("No more account can be created!");
				registerTimerEvent(TimerEventProcess);
				startTimer(3,1000);
			}
		}
	}*/
}

void KeyboardIProcess(int key, int event){
	//键盘输入函数 
	SetPenColor("Magenta");
	switch(event){
		case KEY_DOWN:
			switch(key){
				case VK_RETURN:{
					namefp=fopen("curuser.txt","w");
					fprintf(namefp,"%s\n",pubstr);
					fclose(namefp);
					strcpy(curuser,pubstr);
					/*if((savefp=fopen("savestates1.txt","r+")!=NULL){
						fclose(savefp);
						if(savefp=fopen())
					}*/
					strcpy(accounts[mark],pubstr); 
					PrintAccounts();
					Play();
					registerCharEvent(CharVoidProcess);
					break;
				}
			}
		
	}
}

void ExtractSavestates(){
	/*namefp=fopen("curuser.txt","r+");
	fscanf(namefp,"%s\n",curuser);
    fclose(namefp);*/
    if((savefp=fopen("savestates1.txt","r+"))!=NULL){
	    fread(&savestates[0],sizeof(struct info),1,savefp);
        fclose(savefp);
	}
	else {
			strcpy(savestates[0].username,"default");
			savestates[0].nScore=0;
			savestates[0].nSpeed=0;
		}
    if((savefp=fopen("savestates2.txt","r+"))!=NULL){
        fread(&savestates[1],sizeof(struct info),1,savefp);
    	fclose(savefp);
		
	}
	else {
		strcpy(savestates[1].username,"default");
		savestates[1].nScore=0;
		savestates[1].nSpeed=0;
	}
	if((savefp=fopen("savestates3.txt","r+"))!=NULL){
    		fread(&savestates[2],sizeof(struct info),1,savefp);
    	    fclose(savefp);
		}
	else {
			strcpy(savestates[2].username,"default");
			savestates[2].nScore=0;
			savestates[2].nSpeed=0;
	}
}

void ExtractAccounts(){
	int i;
	accountsnum=0;
	namefp=fopen("accounts.txt","r+");
	for(i=0;i<=2;i++){
		fscanf(namefp,"%s\n",accounts[i]);
	}
	fclose(namefp);
	for(i=0;i<=2;i++){
		if(strcmp(accounts[i],"default")) accountsnum++;
	}
}

void PrintAccounts(){
	int i;
	namefp=fopen("accounts.txt","w");
	for(i=0;i<=2;i++){
		fprintf(namefp,"%s\n",accounts[i]);
	}
	fclose(namefp);
}

void ExtractRanking(){
	FILE *rankfp;
	if((rankfp=fopen("ranking list.txt","r+"))==NULL){
		int i;
		for(i=0;i<=10;i++){
			strcpy(ranking[i].player,"defalut");
			ranking[i].level=0;
			ranking[i].score=0;
		}
		rankfp=fopen("ranking list.txt","w");
		fwrite(ranking,sizeof(ranking),1,rankfp);
		fclose(rankfp);
	}
	else {
		fread(ranking,sizeof(ranking),1,rankfp);
		fclose(rankfp);
	}
}

int RankingSort(){
	int i,j;
	for(i=0;i<=10;i++){
		if(ranking[i].score<=nScore){
			for(j=9;j>=i;j--){
				strcpy(ranking[j+1].player,ranking[j].player);
				ranking[j+1].score=ranking[j].score;
				ranking[j+1].level=ranking[j].level;
			}
			strcpy(ranking[i].player,curuser);
			ranking[i].level=nSpeed;
			ranking[i].score=nScore;
			break;
		}
	}
	FILE *rankfp;
	rankfp=fopen("ranking list.txt","w");
	fwrite(ranking,sizeof(ranking),1,rankfp);
	fclose(rankfp);
	return i;
}

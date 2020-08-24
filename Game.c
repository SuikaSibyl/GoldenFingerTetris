#include "Tetris.h"
struct rankinglist ranking[11];
int Ax=6,Bx,By=0;
int worldflag=0;
int Bullet=0;
int Shootflag=1;int nBullet,topflag=0;int gdflag=1;
/********************************************************** 
 *  ����ԭ�ͣ�void InitializeGameboard()								  			*
 *  �����������                       													*
 *  �� �� ֵ����                            										*
 *  �������ܣ���ʼ����Ϸ����Լ���һ��״��ʾ�򡢼Ʒֿ���Ѷȿ�	*
 PASS
 **********************************************************/
void InitializeGameboard()
{
	width=GetWindowWidth();
    height=GetWindowHeight();
    
	/* ������Ϸ��壨����Ϸ����*/
	StartFilledRegion(1);
	SetPenColor("Black");
    DrawBox(width/2,height/2,width,height);
    EndFilledRegion();
    SetPenColor("White");
    DrawBox(width/3-0.001,height/2,BSIZE*BOARD_WIDTH+0.02,BSIZE*BOARD_HEIGHT+0.04);
    
    /*������һ��״��ʾ��*/
    SetPenColor("Blue");
    SetPointSize(5);
    MovePen(width*2/3-2*BSIZE,(height+BSIZE*BOARD_HEIGHT)/2+BSIZE);
    DrawTextString("Next");
	SetPenColor("Yellow");
	DrawBox(width*2/3,(height+BSIZE*BOARD_HEIGHT)/2-2*BSIZE,4*BSIZE,4*BSIZE);
	
	/*�����ٶȿ�*/
	SetPenColor("Blue");
	MovePen(width*2/3-2*BSIZE,(height)/2+2*BSIZE+BSIZE);
	DrawTextString("Level");
	SetPenColor("Yellow");
	DrawBox(width*2/3,(height)/2,4*BSIZE,4*BSIZE);
	SetPenColor("Red");
	MovePen(width*2/3-TextStringWidth("0")/2,(height)/2);
	DrawTextString("0");
	
	/*���ƼƷֿ�*/
	SetPenColor("Blue");
	MovePen(width*2/3-2*BSIZE,(height-BSIZE*BOARD_HEIGHT)/2+2*BSIZE+2*BSIZE+BSIZE); 
	DrawTextString("Score");
	SetPenColor("Yellow");
	DrawBox(width*2/3,(height-BSIZE*BOARD_HEIGHT)/2+2*BSIZE,4*BSIZE,4*BSIZE);
	SetPenColor("Red");
	MovePen(width*2/3-TextStringWidth("0")/2,(height-BSIZE*BOARD_HEIGHT)/2+2*BSIZE); 
	DrawTextString("0");
}

/********************************************************** 
 *  ����ԭ�ͣ�void KeyboardGameProcess(int key,int event)							  			*
 *  �����������                       													*
 *  �� �� ֵ����                            										*
 *  �������ܣ��˵������̿���	*
 PASS
 **********************************************************/
void KeyboardGameProcess(int key,int event)/*ÿ������������Ϣ����Ҫִ��*/
{
	char SpeedBuffer[10]={0};
	int i,j;
     switch (event) {
	 	case KEY_DOWN:
					 switch (key) {
				case VK_LEFT: /* ���� */
					HandleLeft(nCurrent_block_index,&nOriginX,&nOriginY );
					break;
				case VK_RIGHT: /* ���� */
					HandleRight(nCurrent_block_index,&nOriginX,&nOriginY );
					break;
				case VK_UP: /* ��ת */
					HandleUp(&nCurrent_block_index, &nOriginX,&nOriginY);
					break;
				case VK_DOWN: /* ������ټ� */
						//bAccel=TRUE;
					if(!IsConflict(nCurrent_block_index,nOriginX,nOriginY+1)&&!IsConflict(nCurrent_block_index,nOriginX,nOriginY))
					bottom=HandleDown(nCurrent_block_index,&nOriginX,&nOriginY);
					break;
				case VK_ESC: /* �˳���Ϸ */
					cancelTimer(1);
					//cancelTimer(2);
					InitializeSuspend();
					break;
				case 'R':
					Play();
					break;
				case '0':
					cancelTimer(1);
					//cancelTimer(2);
					savefp=fopen("savestates1.txt","w");
					strcpy(user.username,curuser);
					//strcpy(user.password,password);
					user.nNext_block_index=nNext_block_index;
					user.nCurrent_block_index=nCurrent_block_index;
					user.nSpeed=nSpeed;
					user.nScore=nScore;
					for(i=0;i<12;i++)
					for(j=0;j<22;j++)
					user.Gameboard[i][j]=Gameboard[i][j];
					user.nOriginX=nOriginX;
					user.nOriginY=nOriginY;
                 	fwrite(&user,sizeof(struct info),1,savefp);
                 	fclose(savefp);
					break;
				case 'C':
					CountinueGame();
					break;
				case 'Q':
					if(nSpeed) nSpeed--;
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
					break;
				case 'E':
					//if(nSpeed<10) 
					nSpeed++;
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
					break;
				case 'K':
					if(!IsConflict(nCurrent_block_index,nOriginX,nOriginY+1)&&!IsConflict(nCurrent_block_index,nOriginX,nOriginY))
					{
						cancelTimer(1);
					j=20;
					for(i=1;i<=10;i++)
					{
						Gameboard[i][j]=FILLED;
						StartFilledRegion(1);
						SetPenColor("White");
						DrawSquare(i,j);
			    		EndFilledRegion();
			    		SetPenColor("Black");
	        			DrawSquare(i,j);
					 } 
					 KillLines(20);
					 startTimer(1,25);
					}
					break; 
				case '1':
					if(worldflag==0)
					{
						worldflag=1;
						cancelTimer(1);
					} 
					else
					{
						worldflag=0;
						startTimer(1,25);
					}
					break;
				case '2':
				{
					DrawBlock(nCurrent_block_index, nOriginX,nOriginY, "Black" );
						nCurrent_block_index = nNext_block_index;
						//DrawBlock(nNext_block_index, 21,6,"Black" );
						DrawBlockforNEXT(nNext_block_index,"Black");
						nNext_block_index = RandomInteger(0, 18);
						//DrawBlock(nNext_block_index, 21,6,arrayBlock[nNext_block_index].nColor ); /*������һ����ʾ��״ */
		    			DrawBlockforNEXT(nNext_block_index,arrayBlock[nNext_block_index].nColor);
		    			DrawBlock(nCurrent_block_index, nOriginX,nOriginY, arrayBlock[nCurrent_block_index].nColor );
				}break;
				case '3':
				{
					ChangeTo2(3,19);
				}break;
				case '4':
				{
					ChangeTo4(3,19);
				}break;
				case '5':
					DrawAero(Ax,-1);
					break;
				case 'A':
					if(Ax>1){
					StartFilledRegion(1);
					SetPenColor("Black");
					DrawBox(width/3+(Ax-5.5)*BSIZE,height/2+(10.5+1)*BSIZE,BSIZE+0.1,BSIZE+0.1);
					EndFilledRegion();
					DrawAero(--Ax,-1);
					}
					break;
				case 'D':
					if(Ax<10){
					StartFilledRegion(1);
					SetPenColor("Black");
					DrawBox(width/3+(Ax-5.5)*BSIZE,height/2+(10.5+1)*BSIZE,BSIZE+0.1,BSIZE+0.1);
					EndFilledRegion();
					DrawAero(++Ax,-1);
					}
					break;
				case VK_SPACE:
					if(Shootflag==1){
					nBullet=Bullet;
					Shoot(Ax);
					Shootflag=0;
					}
					break;
				case 'B':
						if(Bullet<=1) Bullet++;
						else  Bullet=0;
					break;
			 }
			 break;
		case KEY_UP:
			 break;
	 }	 
}
/********************************************************** 
 *  ����ԭ�ͣ�void StartGame ()																*
 *  �����������                       												*
 *  �� �� ֵ����                            									*
 *  �������ܣ���Ϸ��ʼʱ���õĺ��������л��ƽ�������ú���  	*
 *            InitializeGameboard(), ���������ʼ����Ϸ����	*
 *            ���������һЩȫ�ֱ����ĳ�ֵ                   	*
 PASS
 **********************************************************/
void StartGame()
{
	int i,j;

	/*������Ϸ�����ÿ������ĳ�ʼֵ*/
	for(j=0;j<=BOARD_HEIGHT;j++)
		for(i=0;i<BOARD_WIDTH+2;i++)
	{
		if(i==0 || i==BOARD_WIDTH+1)
			Gameboard[i][j] = FILLED;
		else
			Gameboard[i][j] = EMPTY;
	}
	for(i=0;i<BOARD_WIDTH+2;i++)
	Gameboard[i][BOARD_HEIGHT+1] = FILLED;
		
	InitializeGameboard();
	
	/*������Ϸ�����ĳ�ֵ*/
	//nNext_block_index = -1; /*��Ϸ��ʼ��û����һ����״��������*/
	DrawBlockforNEXT(nNext_block_index,arrayBlock[nNext_block_index].nColor);
	nSpeed = 0;
	nScore = 0;

}
/********************************************************** 
 *  ����ԭ�ͣ�void Play()																	*
 *  �����������                       										*
 *  �� �� ֵ����                            							*
 *  �������ܣ���ں�������������˹��������������		
 PASS		*
 **********************************************************/
void Play()
{
	nCurrent_block_index = RandomInteger(0, 18);
	nNext_block_index = RandomInteger(0, 18);
	registerKeyboardEvent(KeyboardGameProcess);
	registerTimerEvent(TimerEventProcess);/*ע�ᶨʱ����Ϣ�ص�����*/
	startTimer(1,25);
	Randomize();
	StartGame();
	nOriginX=5, nOriginY=1;
} 
/********************************************************** 
 *  ����ԭ�ͣ�void TimerEventProcess(int timerID)																	*
 *  �����������                       										*
 *  �� �� ֵ����                            							*
 *  �������ܣ���ں�������������˹��������������				*
 **********************************************************/
void TimerEventProcess(int timerID)
{
	int i,j;
	switch(timerID){
	case 1:{
		
		TimerCounter+=(1+nSpeed*0.3);
		if(TimerCounter>=15){
			bottom=HandleDown(nCurrent_block_index,&nOriginX,&nOriginY);
			TimerCounter==0;
			if(phf==1)
			{
				for(i=1;i<=10;i++)
				for(j=1;j<=20;j++) if(Gameboard[i][j]==3) Gameboard[i][j]=2;
				for(i=1;i<=10;i++)
				for(j=1;j<=20;j++)
				{
					if(Gameboard[i][j]==2){
						Gameboard[i][j]=EMPTY;
						SetPenColor("Black");
						StartFilledRegion(1);
						DrawSquare(i,j);
						EndFilledRegion();
					if(i-1>=1&&i-1<=10&&Gameboard[i-1][j]==FILLED) {
						Gameboard[i-1][j]=3;
						SetPenColor("Magenta");
						StartFilledRegion(1);
						DrawSquare(i-1,j);
						EndFilledRegion();
						SetPenColor("Black");
						DrawSquare(i-1,j);
					}
					if(i+1>=1&&i+1<=10&&Gameboard[i+1][j]==FILLED) {
						Gameboard[i+1][j]=3;
						SetPenColor("Magenta");
						StartFilledRegion(1);
						DrawSquare(i+1,j);
						EndFilledRegion();
						SetPenColor("Black");
						DrawSquare(i+1,j);
					}
					if(j-1>=1&&j-1<=20&&Gameboard[i][j-1]==FILLED) {
						Gameboard[i][j-1]=3;
						SetPenColor("Magenta");
						StartFilledRegion(1);
						DrawSquare(i,j-1);
						EndFilledRegion();
						SetPenColor("Black");
						DrawSquare(i,j-1);
						
					}
					if(j+1>=1&&j+1<=20&&Gameboard[i][j+1]==FILLED){
						Gameboard[i][j+1]=3;
						SetPenColor("Magenta");
						StartFilledRegion(1);
						DrawSquare(i,j+1);
						EndFilledRegion();
						SetPenColor("Black");
						DrawSquare(i,j+1);
					} }
				}
			}
			if(gdf==1)
			{
				for(i=1;i<=10;i++)
				for(j=1;j<=20;j++) if(Gameboard[i][j]==5) gdflag=0;
					if(gdflag==1) KillLines(20);
				gdflag=1;
				for(i=1;i<=10;i++)
				for(j=1;j<=20;j++) if(Gameboard[i][j]==5) Gameboard[i][j]=4;
				for(i=1;i<=10;i++)
				for(j=2;j<=20;j++)
				{
					if(Gameboard[i][j]==4){
						Gameboard[i][j]=FILLED;
						SetPenColor("White");
						StartFilledRegion(1);
						DrawSquare(i,j);
						EndFilledRegion();
						SetPenColor("Black");
						DrawSquare(i,j);
					if(i-1>=1&&i-1<=10&&Gameboard[i-1][j]==EMPTY) {
						Gameboard[i-1][j]=5;
						SetPenColor("Green");
						StartFilledRegion(1);
						DrawSquare(i-1,j);
						EndFilledRegion();
						SetPenColor("Black");
						DrawSquare(i-1,j);
					}
					if(i+1>=1&&i+1<=10&&Gameboard[i+1][j]==EMPTY) {
						Gameboard[i+1][j]=5;
						SetPenColor("Green");
						StartFilledRegion(1);
						DrawSquare(i+1,j);
						EndFilledRegion();
						SetPenColor("Black");
						DrawSquare(i+1,j);
					}
					if(j-1>1&&j-1<=20&&Gameboard[i][j-1]==EMPTY) {
						Gameboard[i][j-1]=5;
						SetPenColor("Green");
						StartFilledRegion(1);
						DrawSquare(i,j-1);
						EndFilledRegion();
						SetPenColor("Black");
						DrawSquare(i,j-1);
						
					}
					if(j+1>1&&j+1<=20&&Gameboard[i][j+1]==EMPTY){
						Gameboard[i][j+1]=5;
						SetPenColor("Green");
						StartFilledRegion(1);
						DrawSquare(i,j+1);
						EndFilledRegion();
						SetPenColor("Black");
						DrawSquare(i,j+1);
					} }
				}
			}
		}
		break;
	}
	case 2:
		switch(nBullet)
		{
			case 0:
				if(By<20&&Gameboard[Bx][By+1]!=FILLED)
		{
			SetPenColor("Black");
			StartFilledRegion(1);
			DrawSquare(Bx,By++);
			EndFilledRegion();
			switch(nBullet)
			{
				case 0:SetPenColor("Light Gray");break;
				case 1:SetPenColor("Green");break;
				case 2:SetPenColor("Magenta");break;
			}
			StartFilledRegion(1);
			DrawBox(width/3+(Bx-5.5)*BSIZE,height/2+(10.5-By)*BSIZE,BSIZE/8,BSIZE*0.7);
			EndFilledRegion();
		}
		else 
		{
			SetPenColor("Black");
			StartFilledRegion(1);
			DrawSquare(Bx,By);
			EndFilledRegion();
			Shootflag=1;
			cancelTimer(2);
			if(!IsConflict(nCurrent_block_index,nOriginX,nOriginY+1)&&!IsConflict(nCurrent_block_index,nOriginX,nOriginY))
					{
						cancelTimer(1);
					j=20;
					for(i=1;i<=10;i++)
					{
						Gameboard[i][j]=FILLED;
						StartFilledRegion(1);
						SetPenColor("White");
						DrawSquare(i,j);
			    		EndFilledRegion();
			    		SetPenColor("Black");
	        			DrawSquare(i,j);
					 } 
					 KillLines(20);
					 startTimer(1,25);
					}
		}
		break;
		case 1:
			if(By<20&&Gameboard[Bx][By+1]!=FILLED)
		{
			SetPenColor("Black");
			StartFilledRegion(1);
			DrawSquare(Bx,By++);
			EndFilledRegion();
			switch(nBullet)
			{
				case 0:SetPenColor("Light Gray");break;
				case 1:SetPenColor("Green");break;
				case 2:SetPenColor("Magenta");break;
			}
			StartFilledRegion(1);
			DrawBox(width/3+(Bx-5.5)*BSIZE,height/2+(10.5-By)*BSIZE,BSIZE/8,BSIZE*0.7);
			EndFilledRegion();
		}
		else if(By<20&&Gameboard[Bx][By+1]==FILLED)
			{
			SetPenColor("Black");
			StartFilledRegion(1);
			DrawSquare(Bx,By++);
			EndFilledRegion();
			By++;
			}
		else 
		{
			Shootflag=1;
			SetPenColor("Black");
			StartFilledRegion(1);
			DrawSquare(Bx,By);
			EndFilledRegion();
			ChangeTo4(Bx,By);
			cancelTimer(2);
		}
		break;
		case 2:
			if(By<20&&Gameboard[Bx][By+1]!=FILLED)
		{
			SetPenColor("Black");
			StartFilledRegion(1);
			DrawSquare(Bx,By++);
			EndFilledRegion();
			switch(nBullet)
			{
				case 0:SetPenColor("Light Gray");break;
				case 1:SetPenColor("Green");break;
				case 2:SetPenColor("Magenta");break;
			}
			StartFilledRegion(1);
			DrawBox(width/3+(Bx-5.5)*BSIZE,height/2+(10.5-By)*BSIZE,BSIZE/8,BSIZE*0.7);
			EndFilledRegion();
		}
		else 
		{
			SetPenColor("Black");
			StartFilledRegion(1);
			DrawSquare(Bx,By);
			EndFilledRegion();
			Shootflag=1;
			cancelTimer(2);
			ChangeTo2(Bx,By);
		}
		break;
		}
		
}
}
/********************************************************** 
 *  ����ԭ�ͣ�void KeyboardEndProcess(int key,int event)							  			*
 *  �����������                       													*
 *  �� �� ֵ����                            										*
 *  �������ܣ��˵������̿���	*
 **********************************************************/
void KeyboardEndProcess(int key,int event)/*ÿ������������Ϣ����Ҫִ��*/
{
     switch (event) {
	 	case KEY_DOWN:
			 switch (key) {
			 	 case VK_ESC:
                 	{
					 ExitGraphics();
					 break; 
					}
					break;
		         case VK_RETURN:
			        Play();
			        break;
			 }
	 }	 
}

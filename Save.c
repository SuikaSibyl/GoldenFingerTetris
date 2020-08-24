#include "Tetris.h"

int mark;

extern struct info savestates[3];

/********************************************************** 
 *  ����ԭ�ͣ�void InitializeSave()								  			*
 *  �����������                       													*
 *  �� �� ֵ����                            										*
 *  �������ܣ���ʼ����Ϸ����Լ���һ��״��ʾ�򡢼Ʒֿ���Ѷȿ�	*
 **********************************************************/
void Save(int n)
{
    int i,j;
    switch(n)
    {
 	    case 3:
		    savefp=fopen("savestates3.txt","w+");
		    break;
 		case 2:
		    savefp=fopen("savestates2.txt","w+");
		    break;
 		case 1:
		    savefp=fopen("savestates1.txt","w+");
		    break;
	}
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
    InitializeSave();
} 

 void InitializeSave()
 {
 	int i;
 	state=0;
 	//registerKeyboardEvent(KeyboardSaveProcess);
	/* ���ƺ�ɫ����*/
	ExtractSavestates();
	StartFilledRegion(1);
	SetPenColor("Black");
    DrawBox(width/2,height/2,width,height);
    EndFilledRegion();
    
    for(i=1;i<=3;i++)
    	DrawSaveBox(i);
    
    registerKeyboardEvent(KeyboardSaveProcess);
    
    SetPenColor("Magenta");
	SetPointSize(70);
	MovePen(width/2-TextStringWidth("LOAD")/2,5.5*height/7);
	DrawTextString("SAVE");
	
	SetPointSize(1);
	SetPenColor("Magenta");
	MovePen(width/2-TextStringWidth("Choose a Save to Continue")/2,5*height/7);
	DrawTextString("Choose a Save to Continue");
	SetPenColor("Light Gray");
	MovePen(width/2-TextStringWidth("press BACKSPACE going back to Suspend menu")/2,height/20);
	DrawTextString("press BACKSPACE going back to Suspend menu");
 }
/********************************************************** 
 *  ����ԭ�ͣ�void InitializeSuspend()								  			*
 *  �����������                       													*
 *  �� �� ֵ����                            										*
 *  �������ܣ���ʼ����Ϸ����Լ���һ��״��ʾ�򡢼Ʒֿ���Ѷȿ�	*
 **********************************************************/
 void InitializeSuspend()
 {
 	int i;
 	state=0;
 	//registerKeyboardEvent(KeyboardSaveProcess);
	/* ���ƺ�ɫ����*/
	StartFilledRegion(1);
	SetPenColor("Black");
    DrawBox(width/2,height/2,width,height);
    EndFilledRegion();
    
    StartFilledRegion(1);
	SetPenColor("Light Gray");
    DrawBox(width/2,1*height/5,width/4,height/12);
    EndFilledRegion();
    StartFilledRegion(1);
    DrawBox(width/2,1.65*height/5,width/4,height/12);
    EndFilledRegion();
    StartFilledRegion(1);
    DrawBox(width/2,2.3*height/5,width/4,height/12);
    EndFilledRegion();
    StartFilledRegion(1);
    DrawBox(width/2,2.95*height/5,width/4,height/12);
    EndFilledRegion();
    
    SetPenColor("Blue");
    MovePen(width/2-TextStringWidth("Menu")/2,2.95*height/5);
	DrawTextString("Menu");
	MovePen(width/2-TextStringWidth("Save")/2,2.3*height/5);
	DrawTextString("Save");
	MovePen(width/2-TextStringWidth("Load")/2,1.65*height/5);
	DrawTextString("Load");
	MovePen(width/2-TextStringWidth("Restart")/2,1*height/5);
	DrawTextString("Restart");
    
    registerKeyboardEvent(KeyboardSuspendProcess);
    
    SetPenColor("Magenta");
	SetPointSize(70);
	MovePen(width/2-TextStringWidth("SUSPEND")/2,5.5*height/7);
	DrawTextString("SUSPEND");
	
	SetPointSize(1);
	SetPenColor("Magenta");
	MovePen(width/2-TextStringWidth("Choose a button")/2,5*height/7);
	DrawTextString("Choose a button");
	SetPenColor("Light Gray");
	MovePen(width/2-TextStringWidth("press BACKSPACE to continue")/2,height/20);
	DrawTextString("press BACKSPACE to continue");
 }
 /********************************************************** 
 *  ����ԭ�ͣ�void InitializeLoad()								  			*
 *  �����������                       													*
 *  �� �� ֵ����                            										*
 *  �������ܣ���ʼ����Ϸ����Լ���һ��״��ʾ�򡢼Ʒֿ���Ѷȿ�	*
 **********************************************************/
 void InitializeLoad()
 {
 	int i;
 	state=0;
 	ExtractSavestates();
 	//registerKeyboardEvent(KeyboardSaveProcess);
	/* ���ƺ�ɫ����*/
	StartFilledRegion(1);
	SetPenColor("Black");
    DrawBox(width/2,height/2,width,height);
    EndFilledRegion();
    
    for(i=1;i<=3;i++)
    	DrawSaveBox(i);
    
    registerKeyboardEvent(KeyboardLoadProcess);
    
    SetPenColor("Magenta");
	SetPointSize(70);
	MovePen(width/2-TextStringWidth("LOAD")/2,5.5*height/7);
	DrawTextString("LOAD");
	
	SetPointSize(1);
	SetPenColor("Magenta");
	MovePen(width/2-TextStringWidth("Choose a Save to Continue")/2,5*height/7);
	DrawTextString("Choose a Save to Continue");
	SetPenColor("Light Gray");
	MovePen(width/2-TextStringWidth("press BACKSPACE going back to menu")/2,height/20);
	DrawTextString("press BACKSPACE going back to menu");
 }
  /********************************************************** 
 *  ����ԭ�ͣ�void DrawSaveBox(int n)							  			*
 *  �����������                       													*
 *  �� �� ֵ����                            										*
 *  �������ܣ��˵������̿���	*
 **********************************************************/
 void DrawSaveBox(int n)
 {
 	char ScoreBuffer[10]={'\0'},SpeedBuffer[10]={'\0'};
 	SetPointSize(3);
 	
 	StartFilledRegion(1);
	SetPenColor("Light Gray");
    DrawBox(width/2,n*height/5,width/4,height/7);
    EndFilledRegion();
    
    SetPenColor("Blue");
    SetPointSize(5);
    MovePen(width/2-0.7,n*height/5+0.1) ;
    DrawTextString("Player:");
    MovePen(width/2-0.7,n*height/5-0.1) ;
    DrawTextString("Score:");
    MovePen(width/2-0.7,n*height/5-0.3) ;
    DrawTextString("Level:");
    
    /*switch(n){
    	case 1:if((savefp=fopen("savestates1.txt","rb+")!=NULL){
                    rewind(savefp);
                    fread(&user,sizeof(struct info),1,savefp);
                    fclose(savefp);
				}
				else user
                break;
        case 2:savefp=fopen("savestates2.txt","rb+");
                rewind(savefp);
                fread(&user,sizeof(struct info),1,savefp);
                fclose(savefp);
                break;
        case 3:savefp=fopen("savestates3.txt","rb+");
                rewind(savefp);
                fread(&user,sizeof(struct info),1,savefp);
                fclose(savefp);
                break;
	}*/
	
    SetPenColor("Magenta");
    itoa(savestates[3-n].nScore,ScoreBuffer,10);
	MovePen(width/2,n*height/5-0.1) ;
    DrawTextString(ScoreBuffer);
    MovePen(width/2,n*height/5-0.3) ;
    itoa(savestates[3-n].nSpeed,SpeedBuffer,10);
    DrawTextString(SpeedBuffer);
    SetPointSize(10);
    MovePen(width/2,n*height/5+0.1);
    DrawTextString(savestates[3-n].username);
 }
  /********************************************************** 
 *  ����ԭ�ͣ�void KeyboardSuspendProcess(int key,int event)							  			*
 *  �����������                       													*
 *  �� �� ֵ����                            										*
 *  �������ܣ��˵������̿���	*
 **********************************************************/
void KeyboardSuspendProcess(int key,int event)/*ÿ������������Ϣ����Ҫִ��*/
{	
    switch (event) {
	    case KEY_DOWN:
			switch (key) {
			    case VK_DOWN:
			    	if(state<4){
					    state++;
					    if(state!=1)
			            {
						SetPenColor("Light Gray");
			            DrawBox(width/2,(4.25-state*0.65)*height/5,width/4-0.05,height/12-0.05);
			            }
			            SetPenColor("Blue");
			            DrawBox(width/2,(3.6-state*0.65)*height/5,width/4-0.05,height/12-0.05);
                    }
					break;
                case VK_RETURN:
                 	switch(state){
                 		case 1:{
                 			InitializeMenu();
							break;
						case 2:
						    InitializeSave();
							break;
						case 3:
						    InitializeLoad();
							break;
						case 4:Play();
						break;
						}
					}
					break;
				case VK_UP:
			    	if(state>1){
					    state--;
			            SetPenColor("Light Gray");
			            DrawBox(width/2,(2.95-state*0.65)*height/5,width/4-0.05,height/12-0.05);
			            SetPenColor("Blue");
			            DrawBox(width/2,(3.6-state*0.65)*height/5,width/4-0.05,height/12-0.05);
			            
                    }
					break;
				case VK_BACK:
					CountinueGame();
					break;
			break;
        }
	    /*case KEY_UP:
			break;*/
	}	 
}
 /********************************************************** 
 *  ����ԭ�ͣ�void KeyboardSaveProcess(int key,int event)							  			*
 *  �����������                       													*
 *  �� �� ֵ����                            										*
 *  �������ܣ��˵������̿���	*
 **********************************************************/
void KeyboardSaveProcess(int key,int event)/*ÿ������������Ϣ����Ҫִ��*/
{	
    switch (event) {
	    case KEY_DOWN:
			switch (key) {
			    case VK_DOWN:
			    	if(state<3){
					    state++;
					    if(state!=1)
			            {
						SetPenColor("Light Gray");
			            DrawBox(width/2,(5-state)*height/5,width/4-0.05,height/7-0.05);
			            }
			            SetPenColor("Blue");
			            DrawBox(width/2,(4-state)*height/5,width/4-0.05,height/7-0.05);
                    }
					break;
                case VK_RETURN:
                 	Save(state);
					break;
				case VK_UP:
			    	if(state>1){
					    state--;
			            SetPenColor("Light Gray");
			            DrawBox(width/2,(3-state)*height/5,width/4-0.05,height/7-0.05);
			            SetPenColor("Blue");
			            DrawBox(width/2,(4-state)*height/5,width/4-0.05,height/7-0.05);
			            
                    }
					break;
				case VK_BACK:
					InitializeSuspend();
					break;
			break;
        }
	    /*case KEY_UP:
			break;*/
	}	 
}
 /********************************************************** 
 *  ����ԭ�ͣ�void KeyboardLoadProcess(int key,int event)							  			*
 *  �����������                       													*
 *  �� �� ֵ����                            										*
 *  �������ܣ��˵������̿���	*
 **********************************************************/
void KeyboardLoadProcess(int key,int event)/*ÿ������������Ϣ����Ҫִ��*/
{	
    switch (event) {
	    case KEY_DOWN:
			switch (key) {
			    case VK_DOWN:
			    	if(state<3){
					    state++;
					    if(state!=1)
			            {
						SetPenColor("Light Gray");
			            DrawBox(width/2,(5-state)*height/5,width/4-0.05,height/7-0.05);
			            }
			            SetPenColor("Blue");
			            DrawBox(width/2,(4-state)*height/5,width/4-0.05,height/7-0.05);
                    }
					break;
                case VK_RETURN:
                	switch (state){
                		case 1:savefp=fopen("savestates1.txt","ab+");
                 			rewind(savefp);
                 			fread(&user,sizeof(struct info),1,savefp);
                 			fclose(savefp);
                 			LoadGame();
                 			break;
                 		case 2:savefp=fopen("savestates2.txt","ab+");
                 			rewind(savefp);
                 			fread(&user,sizeof(struct info),1,savefp);
                 			fclose(savefp);
                 			LoadGame();
                 			break;
                 		case 3:savefp=fopen("savestates3.txt","ab+");
                 			rewind(savefp);
                 			fread(&user,sizeof(struct info),1,savefp);
                 			fclose(savefp);
                 			LoadGame();
                 			break;
					}
					break;
				case VK_UP:
			    	if(state>1){
					    state--;
			            SetPenColor("Light Gray");
			            DrawBox(width/2,(3-state)*height/5,width/4-0.05,height/7-0.05);
			            SetPenColor("Blue");
			            DrawBox(width/2,(4-state)*height/5,width/4-0.05,height/7-0.05);
                    }
					break;
				case VK_BACK:
					InitializeMenu();
					break;
			break;
        }
	    /*case KEY_UP:
			break;*/
	}	 
}

/*struct save SaveAccount()
{
	account.username=username;
	account.password=password;
	account.nNext_block_index=nNext_block_index;
	account.nCurrent_block_index=nCurrent_block_index;
	//account.Gameboard=Gameboard;
	account.nOriginX=nOriginX;
	account.nOriginY=nOriginY;
	return account;
}*/
 /********************************************************** 
 *  ����ԭ�ͣ�void LoadGame()						  			*
 *  �����������                       													*
 *  �� �� ֵ����                            										*
 *  �������ܣ�������Ϸ�浵	*
 **********************************************************/
 void LoadGame()
 {
 	int i,j;
 	char ScoreBuffer[10]={0},SpeedBuffer[10]={0};
 	registerKeyboardEvent(KeyboardGameProcess);
	registerTimerEvent(TimerEventProcess);/*ע�ᶨʱ����Ϣ�ص�����*/
	//startTimer(2,50);
	startTimer(1,25);
	Randomize();
	InitializeGameboard();
	/*������Ϸ�����ÿ������ĳ�ʼֵ*/
	for(i=0;i<12;i++)
	for(j=0;j<22;j++)
	     Gameboard[i][j]=user.Gameboard[i][j];
	for(i=1;i<11;i++)
	for(j=0;j<21;j++){
		if(Gameboard[i][j]==FILLED){
				StartFilledRegion(1);
				SetPenColor("White");
			    DrawSquare(i,j);
			    EndFilledRegion();
			    SetPenColor("Black");
	            DrawSquare(i,j);}
		}
    strcpy(curuser,user.username);
    nCurrent_block_index = user.nCurrent_block_index;
	nNext_block_index = user.nNext_block_index;
	nOriginX=user.nOriginX;nOriginY=user.nOriginY;
	DrawBlockforNEXT(nNext_block_index,arrayBlock[nNext_block_index].nColor);
	DrawBlock(nCurrent_block_index, nOriginX,nOriginY, arrayBlock[nCurrent_block_index].nColor );
	nSpeed=user.nSpeed;
	nScore=user.nScore;
	            /*�ػ�Ʒֿ�*/
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

					/*�ػ��ٶȿ�*/
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
 /********************************************************** 
 *  ����ԭ�ͣ�void ContinueGame()						  			*
 *  �����������                       													*
 *  �� �� ֵ����                            										*
 *  �������ܣ�������Ϸ�浵	*
 **********************************************************/
 void CountinueGame()
 {
 	int i,j;
 	char ScoreBuffer[10]={0},SpeedBuffer[10]={0};
 	registerKeyboardEvent(KeyboardGameProcess);
	registerTimerEvent(TimerEventProcess);/*ע�ᶨʱ����Ϣ�ص�����*/
	//startTimer(2,50);
	startTimer(1,25);
	Randomize();
	InitializeGameboard();
	/*������Ϸ�����ÿ������ĳ�ʼֵ*/
	for(i=1;i<11;i++)
	for(j=0;j<21;j++){
		if(Gameboard[i][j]==FILLED){
				StartFilledRegion(1);
				SetPenColor("White");
			    DrawSquare(i,j);
			    EndFilledRegion();
			    SetPenColor("Black");
	            DrawSquare(i,j);}
		}
	DrawBlockforNEXT(nNext_block_index,arrayBlock[nNext_block_index].nColor);
	DrawBlock(nCurrent_block_index, nOriginX,nOriginY, arrayBlock[nCurrent_block_index].nColor );
	            /*�ػ�Ʒֿ�*/
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

					/*�ػ��ٶȿ�*/
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

void InitializeAccounts(){
	int i=0;
	StartFilledRegion(1);
	SetPenColor("Black");
	width=GetWindowWidth();
    height=GetWindowHeight();
    DrawBox(width/2,height/2,width,height);
    EndFilledRegion();
    SetPointSize(22);
    SetStyle(1);
    StartFilledRegion(1);
    SetPenColor("Light Gray");
	DrawBox(width/2,height-height/7*2,width/5,height/14); 
    EndFilledRegion();
	StartFilledRegion(1);
	DrawBox(width/2,height-height/7*3,width/5,height/14); 
    EndFilledRegion();
    StartFilledRegion(1);
	DrawBox(width/2,height-height/7*4,width/5,height/14); 
    EndFilledRegion();
    StartFilledRegion(1);
	DrawBox(width/2,height/7*2,width/5,height/14); 
    EndFilledRegion();
    StartFilledRegion(1);
	DrawBox(width/2,height/7,width/5,height/14); 
    EndFilledRegion();
    SetPenColor("Blue");
    DrawBox(width/2,height*5/7,width/5-0.05,height/14-0.05);
    SetPenColor("Magenta");
    SetPointSize(28);
    MovePen(width/2-TextStringWidth("Accounts")/2,height*6/7);
    DrawTextString("Accounts");
    SetPointSize(18);
    SetPenColor("Magenta");
    ExtractAccounts();
    for(i=0;i<=2;i++){
    	if(strcmp(accounts[i],"default")){
    		MovePen(width/2-TextStringWidth(accounts[i])/2,(5-i)*height/7);
    		DrawTextString(accounts[i]);
		}
		else{
			MovePen(width/2-TextStringWidth("NONE")/2,(5-i)*height/7);
    		DrawTextString("NONE");
		}
	}
	SetPenColor("Blue");
	MovePen(width/2-TextStringWidth("Register")/2,height*2/7);
	DrawTextString("Register"); 
	MovePen(width/2-TextStringWidth("Return")/2,height/7);
	DrawTextString("Return");
	registerKeyboardEvent(KeyboardAccountProcess);
	
	state=1;
}

void KeyboardAccountProcess(int key,int event){
	double framew=width/5-0.05;
	double frameh=height/14-0.04;
	switch(event){
		case KEY_DOWN:{
			switch(key) {
				case VK_DOWN:{
					if(state<=4){
						SetPenColor("Light Gray");
						DrawBox(width/2,height*(6-state)/7,framew,frameh);
						SetPenColor("Blue");
						DrawBox(width/2,height*(5-state)/7,framew,frameh);
						state++;
					}
					break;
				}
				case VK_UP:{
					if(state>=2){
						SetPenColor("Light Gray");
						DrawBox(width/2,height*(6-state)/7,framew,frameh);
						SetPenColor("Blue");
						DrawBox(width/2,height*(7-state)/7,framew,frameh);
						state--;
					}
					break;
				}
				case VK_RETURN:{
					switch(state){
						case 1:{
							if (strcmp(accounts[0],"default")){
								strcpy(curuser,accounts[0]);
								InitializeMenu();
							}
							else{
								AccountSelectionError();
							}
							break;
						}
						case 2:{
							if (strcmp(accounts[1],"default")){
								strcpy(curuser,accounts[1]);
								InitializeMenu();
							}
							else{
								AccountSelectionError();
							}
							break;
						}
						case 3:{
							if (strcmp(accounts[2],"default")){
								strcpy(curuser,accounts[2]);
								InitializeMenu();
							}
							else{
								AccountSelectionError();
							}
							break;
						}
						case 4:{
							Register();
							break;
						}
						case 5:{
							InitializeMenu();
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}
}
void InitializeHelp()
{
 	int i;
 	state=0;
 	StartFilledRegion(1);
	SetPenColor("Black");
	DrawBox(width/2,height/2,width,height);
    EndFilledRegion();
	
	SetPenColor("Magenta");
	SetPointSize(70);
	MovePen(width/2-TextStringWidth("HELP")/2,5.5*height/7);
	DrawTextString("HELP");
	
	SetPenColor("Blue");
    SetPointSize(15);
    MovePen(width/30,5*height/7);
	DrawTextString("�������һ���򵥵Ķ���˹��������м��û����浵ϵͳ�����а�ȹ���");
	MovePen(width/30,4.7*height/7);
	DrawTextString("Menu����ͨ�������ϡ���ѡ��ť��Game���������");
	MovePen(width/30,4.4*height/7);
	DrawTextString("1.ʹ�ü��������ƶ����飬ʹ������ת���飬�¼��ٷ�������");
	MovePen(width/30,4.1*height/7);
	DrawTextString("2.Next����ʾ��һ�����ֵķ���");
	MovePen(width/30,3.8*height/7);
	DrawTextString("3.Level����ʾ�ȼ���Ϣ���ȼ�Խ�ߣ���������Խ��");
	MovePen(width/30,3.5*height/7);
	DrawTextString("4.Score��ʾ��ǰ�÷�");
	MovePen(width/30,3.2*height/7);
	DrawTextString("5.Game���水��Esc������ͣ�˵�����backspace������Ϸ");
	MovePen(width/30,2.9*height/7);
	DrawTextString("Load����ͨ������ѡ�񱣴���ĵ�");
	MovePen(width/30,2.6*height/7);
	DrawTextString("Accounts����ͨ������ѡ�����л��û���");
	MovePen(width/30,2.3*height/7);
	DrawTextString("ע�⣺����3���û���Ҫ���ǣ��û�����������10���ַ�");
	MovePen(width/30,2.0*height/7);
	DrawTextString("Menu����ѡ��Exit�˳�����");
	
	SetPenColor("Light Gray");
	SetPointSize(1);
	MovePen(width/2-TextStringWidth("press BACKSPACE going back to menu")/2,height/20);
	DrawTextString("press BACKSPACE going back to menu");
	
	registerKeyboardEvent(KeyboardHelpProcess);
}

void KeyboardHelpProcess(int key,int event)/*ÿ������������Ϣ����Ҫִ��*/
{	
    switch (event) {
	    case KEY_DOWN:
			switch (key) {
			   
				case VK_BACK:
					InitializeMenu();
					break;
		
        }
	    /*case KEY_UP:
			break;*/
	}	 
}

//AccountSelectionError(), ��ѡ����û���֧��ʱ���ã�����������Ϣ��ʾ��Ȼ�󷵻��˻����� 
void AccountSelectionError(){
	StartFilledRegion(1);
	SetPenColor("Light Gray");
	DrawBox(width/2,height/2,width/2,height/4);
	EndFilledRegion();
	MovePen(width/2-TextStringWidth("Account not avaliable!")/2,height/2);
	SetPenColor("Magenta");
	SetPointSize(18);
	DrawTextString("Account not avaliable!");
	registerTimerEvent(TimerEventProcess);
	startTimer(4,1000);
}

void InitializeOverwrite(){
	int i;
	state=1;
	StartFilledRegion(1);
	SetPenColor("Black");
	DrawBox(width/2,height/2,width,height);
	EndFilledRegion();
	for(i=1;i<=3;i++){
		SetPenColor("Light Gray");
		StartFilledRegion(1);
		DrawBox(width/2,height*(4-i)/4,width/5,height/14);
		EndFilledRegion();
		SetPenColor("Magenta");
		SetPointSize(22);
		MovePen(width/2-TextStringWidth(accounts[i-1])/2,height*(4-i)/4);
		DrawTextString(accounts[i-1]);
	}
	SetPenColor("Blue");
	DrawBox(width/2,height*3/4,width/5-0.05,height/14-0.05);
	registerKeyboardEvent(KeyboardOverwriteProcess);
	SetPenColor("Light Gray");
	MovePen(width/2-TextStringWidth("Choose An Account to Overwrite")/2,height/18);
	DrawTextString("Choose An Account to Overwrite");	
}

void KeyboardOverwriteProcess(int key, int event){
	switch(event){
		case KEY_DOWN:{
			switch(key){
				case VK_DOWN:{
					if(state<3){
						state++;
						SetPenColor("Light Gray");
						DrawBox(width/2,height*(5-state)/4,width/5-0.05,height/14-0.05);
						SetPenColor("Blue");
						DrawBox(width/2,height*(4-state)/4,width/5-0.05,height/14-0.05);
					}
					break;
				}
				case VK_UP:{
					if(state>1){
					    state--;
					    SetPenColor("Light Gray");
					    DrawBox(width/2,height*(3-state)/4,width/5-0.05,height/14-0.05);
						SetPenColor("Blue");
						DrawBox(width/2,height*(4-state)/4,width/5-0.05,height/14-0.05);
					    break;
					}
				}
				case VK_RETURN:{
					mark=state-1;
					Register();
					break;
				}
			}
			break;
		}
	}
}

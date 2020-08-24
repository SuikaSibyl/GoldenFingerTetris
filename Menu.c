#include "Tetris.h"

/********************************************************** 
 *  函数原型：void InitializeMenu()								  			*
 *  传入参数：无                       													*
 *  返 回 值：无                            										*
 *  函数功能：初始化游戏面板以及下一形状提示框、计分框和难度框	*
 **********************************************************/
void InitializeMenu()
{
//	registerKeyboardEvent(KeyboardEventProcess);
	/* 绘制黑色底面*/
	StartFilledRegion(1);
	SetPenColor("Black");
	width=GetWindowWidth();
    height=GetWindowHeight();
    DrawBox(width/2,height/2,width,height);
    EndFilledRegion();
    /* 绘制菜单*/
    //SetPenColor("White");
    SetPointSize(22);
    SetStyle(1);
    StartFilledRegion(1);
    SetPenColor("Light Gray");
	DrawBox(width/2,height-height/7*2,width/5,height/14); 
    EndFilledRegion();StartFilledRegion(1);
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
    MovePen(width/2-TextStringWidth("Play")/2,height-height/7*2);
    SetPenColor("Blue");
	DrawTextString("Play");
	MovePen(width/2-TextStringWidth("Load")/2,height-height/7*3);
	DrawTextString("Load");
	MovePen(width/2-TextStringWidth("Accounts")/2,height-height/7*4);
	DrawTextString("Accounts");
	MovePen(width/2-TextStringWidth("Help")/2,height/7*2);
	DrawTextString("Help");
	MovePen(width/2-TextStringWidth("Exit")/2,height/7);
	DrawTextString("Exit");
	SetPenColor("Magenta");
	SetPointSize(70);
	SetPenColor("Blue");
	MovePen(width/2-TextStringWidth("Terris")/2-0.05,6*height/7);
	DrawTextString("Tetris");
	SetPenColor("Magenta");
	MovePen(width/2-TextStringWidth("Terris")/2+0.05,6*height/7);
	DrawTextString("Tetris");
	SetPenColor("White");
	MovePen(width/2-TextStringWidth("Terris")/2,6*height/7);
	DrawTextString("Tetris");
	SetPenColor("Blue");
	DrawBox(width/2,height-height/7*2,width/5-0.05,height/14-0.05); 
	r=1;g=1;b=1;
	SetPenColor("Blue");
	SetPointSize(18);
	MovePen(width*4/10,height*11/14+0.04);
	DrawTextString("Current User:");
	MovePen(width*11/20-TextStringWidth(curuser)/2,height*11/14+0.04);
	SetPenColor("Magenta");
	DrawTextString(curuser);
	//registerTimerEvent(TimerAnimationProcess);
	//MovePen(0,0);
	//startTimer(1,100);
	registerKeyboardEvent(KeyboardMenuProcess);/*注册键盘消息回调函数*/
	
	state=1;
	
}

/********************************************************** 
 *  函数原型：void KeyboardMenuProcess(innt key,int event)							  			*
 *  传入参数：无                       													*
 *  返 回 值：无                            										*
 *  函数功能：菜单栏键盘控制	*
 **********************************************************/
void KeyboardMenuProcess(int key,int event)/*每当产生键盘消息，都要执行*/
{	
	double boxw=width/5;
	double boxh=height/14;
    switch (event) {
	    case KEY_DOWN:
			switch (key) {
			    case VK_DOWN:
			    	if(state<5){
					    state++;
			            SetPenColor("Light Gray");
			            DrawBox(width/2,height*(7-state)/7,boxw-0.05,boxh-0.05);
			            SetPenColor("Blue");
			            DrawBox(width/2,height*(6-state)/7,boxw-0.05,boxh-0.05);   
                    }
					break;
                case VK_RETURN:
                 	switch(state){                 //play game
                 		case 1:{
                 			Play();
							break;
						}
						case 2:{                   //load
                 			InitializeLoad();
							break;
						}
						case 3:{
							/*SetPenColor("Black"); 
							StartFilledRegion(1); 
							DrawBox(width/2,height/2,width,height);
							EndFilledRegion();
							SetPenColor("Light Gray");
							StartFilledRegion(1);
							DrawBox(width/2,height*3/10,width/5,height/10);
							EndFilledRegion();
							StartFilledRegion(1);  
							DrawBox(width/2,height*5/10,width/5,height/10);
							EndFilledRegion();
							StartFilledRegion(1); 
							DrawBox(width/2,height*7/10,width/5,height/10);
							EndFilledRegion();
							StartFilledRegion(1); 
							DrawBox(width/3,height/10,width/5,height/14);
							EndFilledRegion();
							StartFilledRegion(1); 
							DrawBox(width*2/3,height/10,width/5,height/14);
							EndFilledRegion();
							SetPenColor("Magenta");
							SetPointSize(28); 
							MovePen(width/2-TextStringWidth("Accounts")/2,height*9/10);
							DrawTextString("Accounts");
							MovePen(width/2-TextStringWidth(""),height*3/10);*/
							InitializeAccounts();
							break;
						} 
						case 4:{
							InitializeHelp();
							break;
						}
						
						case 5:
						ExitGraphics();
						break;
					}
					break;
				case VK_UP:
			    	if(state>1){
					    state--;
			            SetPenColor("Light Gray");
			            DrawBox(width/2,height*(5-state)/7,boxw-0.05,boxh-0.05);
			            SetPenColor("Blue");
			            DrawBox(width/2,height*(6-state)/7,boxw-0.05,boxh-0.05);   
                    }
					break;
			break;
        }
	    /*case KEY_UP:
			break;*/
	}	 
}

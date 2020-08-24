#ifndef _TETRIS_H_
#define _TETRIS_H_

//include
#include "Tetris.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "graphics.h"
#include "genlib.h"
#include "conio.h"
#include "extgraph.h"
#include "simpio.h"
#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <dos.h>
#include <random.h> 

//���� 
#define FALSE 0
#define TRUE 1
#define EMPTY 0
#define FILLED 1
#define TIMER 0x1c /*����ʱ���жϵ��жϺ�*/
#define BSIZE 0.25 /*����ı߳���16������*/
#define MAX_SHAPE 19 /*�ܹ���19�ָ���̬�ķ���*/
#define BOARD_WIDTH 10 /*��Ϸ���Ŀ�ȣ��Է���Ŀ��Ϊ��λ*/
#define BOARD_HEIGHT 20/*��Ϸ���ĸ߶ȣ��Է���Ŀ��Ϊ��λ*/
#define BOARD_MID_X 2 /*��Ϸ������½ǵĺ�����*/
#define BOARD_MID_Y 0.5 /*��Ϸ������½ǵ�������*/ 
#define BOARD_LEFT_X 10 /*��Ϸ������Ͻǵĺ�����*/
#define BOARD_LEFT_Y 5 /*��Ϸ������Ͻǵ�������*/
#define VK_ESC 27
#define VK_A 'A'
#define VK_B 'B'
#define VK_C 'C'
#define VK_D 'D'
#define VK_E 'E'
#define VK_F 'F'
#define VK_G 'G'
#define VK_H 'H'
#define VK_I 'I'
#define VK_J 'J'
#define VK_K 'K'
#define VK_L 'L'
#define VK_M 'M'
#define VK_N 'N'
#define VK_O 'O'
#define VK_P 'P'
#define VK_Q 'Q'
#define VK_R 'R'
#define VK_S 'S'
#define VK_T 'T'
#define VK_U 'U'
#define VK_V 'V'
#define VK_W 'W'
#define VK_X 'X'
#define VK_Y 'Y'
#define VK_Z 'Z'
#define VK_0 '0'
#define VK_1 '1'
#define VK_2 '2'
#define VK_3 '3'
#define VK_4 '4'
#define VK_5 '5'
#define VK_6 '6'
#define VK_7 '7'
#define VK_8 '8'
#define VK_9 '9'



//�ṹ�� 
struct blocks{
 int arrXY[8];
 char* nColor;
 int nNext;
}; 
typedef struct blocks BLOCK;
extern BLOCK arrayBlock[19];

struct info{
	char username[20];
	int Gameboard[12][22];
	int nOriginX;
	int nOriginY;
	int nCurrent_block_index;
	int nNext_block_index;
	int nSpeed;
	int nScore;
	
};
struct info user;
struct info* infoptr;
struct info savestates[3];

struct rankinglist{
	char player[20];
	int level;
	int score;
};

/*����ȫ�ֱ���*/
extern int Gameboard[BOARD_WIDTH+2][BOARD_HEIGHT+2];
extern int nCurrent_block_index  ; /*��ǰ����ķ����������*/
extern int nNext_block_index ; /*��һ�������������*/
extern int nSpeed, nScore; /*�ٶȺ͵÷�*/
extern int nSpeedUpScore; /*��һ��Ҫ������ﵽ�ķ���*/
extern int bAccel, bOver;
extern int nOriginX, nOriginY;/*ĳһ��״��ԭ��ľ�������*/
extern unsigned int TimerCounter;  /* ��ʱ������ÿ��������18 */
double width,height;
static int state;
extern int bottom;
extern char username[20];
//extern char password[8];
extern FILE *namefp;
extern FILE *savefp;
extern char curuser[20]; //Tetris.c�ж�����ַ���������ָʾ���ڵ��û��� 
char accounts[3][20];
extern int accountsnum; //Functions.c�ж����ȫ�ֱ�����ָʾ��ǰ��ע���û��ĸ���
extern struct rankinglist ranking[11]; 
extern int mark;
extern int overwrite; 
extern int location;
extern double r,g,b;
extern colorflag;
extern double x,y,dx,dy;
extern int phf,gdf;
extern int Bullet;
extern int Ax,Bx,By,nBullet;
//�������� 
void DrawBox(double m,double n,double x,double y);
void DrawBlock(int BlockIndex, int sx, int sy,char* color);
void InitializeGameboard();
void InitializeMenu();
void InitializeSuspend();
void InitializeSave();
void InitializeAccounts();
void InitializeHelp();
void InitializeOverwrite();
void KeyboardMenuProcess(int key,int event);/*�˵�������Ϣ�ص�����*/
void KeyboardGameProcess(int key,int event);
void KeyboardEndProcess(int key,int event);
void KeyboardLoadProcess(int key,int event);
void KeyboardSuspendProcess(int key,int event);
void KeyboardAccountProcess(int key,int event);
void KeyboardIProcess(int key, int event);
void KeyboardHelpProcess(int key,int event);
void KeyboardOverwriteProcess(int key,int event);
void TimerEventProcess(int timerID);
void StartGame();
void Play();
void KeyboardSaveProcess(int key,int event);
void DrawSaveBox(int n);
void LoadGame();
void CountinueGame();
void Save(int n);
void Register();
void AccountSelectionError();
void ExtractSavestates();
void ExtractAccounts();
void PrintAccounts();
void ExtractRanking();
int RankingSort();
void TimerAnimationProcess(int timerID);
void CharIProcess(char c);
void CharVoidProcess(char);
void DrawLines(double x,double y,double dx,double dy);
void ChangeTo2(int x,int y);
//struct save SaveAccount();

#endif

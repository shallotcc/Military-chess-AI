/* ************************************************************************ */
/* 示例代码维护：哈尔滨理工大学 计算机博弈研究组							*/
/* 己方棋子编码约定:														*/
/*	a司令,b军长,c师长,d旅长,e团长,f营长,g连长,h排长,i工兵,j地雷k炸弹,l军旗	*/
/* 对方方棋子编码约定:														*/
/*	A司令,B军长,C师长,D旅长,E团长,F营长,G连长,H排长,I工兵,J地雷K炸弹,L军旗	*/
/*	X未知对方棋子,0空棋位													*/
/* 最后更新：2012-04-10  meixian@hrbust.edu.cn								*/
/* ************************************************************************ */
#include <stdio.h>
//#include <windows.h>
#include <iostream>
#include <string.h>
#include "Probability.h"
#include "SearchEngine.h"
#include "Vector.h"
#include "hessMove.h"
#include "MoveGenertor.h"
#include "Assessment.h"
using namespace std;
Probability pb;
SearchEngine se;
Assessment am;  //估值
int k=0;		//k是什么？
int STARTMOVE=0;
int FIRSTONLYMOVE=2;//1表示己方先移动,0表示对方先移动,2表示发生碰子
int FLAG;
/* ************************************************************************ */
/* 函数功能：i,j位置是否本方棋子											*/
/* 接口参数：																*/
/*     char cMap[12][5] 棋盘局面											*/
/*     int i,j 棋盘位置行列号												*/
/* 返回值：																	*/
/*     1己方棋子，0空棋位或对方棋子											*/
/* ************************************************************************ */
int IsMyChess(char cMap[12][5],int i,int j)
{
	if(cMap[i][j]>='a'&& cMap[i][j]<='l')
		return 1;
	else
		return 0;
}

/* ************************************************************************ */
/* 函数功能：i,j位置是否本方可移动的棋子									*/
/* 接口参数：																*/
/*     char cMap[12][5] 棋盘局面											*/
/*     int i,j 棋盘位置行列号												*/
/* 返回值：																	*/
/*     1己方可移动棋子(司令,军长,...,工兵,炸弹)，0军旗,地雷,对方棋子或空棋位*/
/* ************************************************************************ */
int IsMyMovingChess(char cMap[12][5],int i,int j)
{
	if(cMap[i][j]>='a' && cMap[i][j]<='i' || cMap[i][j]=='k')
		return 1;
	else
		return 0;
}

/* ************************************************************************ */
/* 函数功能：i,j位置是否山界后的兵站										*/
/* 接口参数：																*/
/*     int i,j 棋盘位置行列号												*/
/* 返回值：																	*/
/*     1处于山界后，0不处于山界后											*/
/* ************************************************************************ */
int IsAfterHill(int i,int j)
{
	if(i*5+j==31 || i*5+j==33)
		return 1;
	else
		return 0;
}

/* ************************************************************************ */
/* 函数功能：i,j位置是否行营												*/
/* 接口参数：																*/
/*     int i,j 棋盘位置行列号												*/
/* 返回值：																	*/
/*     1是行营，0不是行营													*/
/* ************************************************************************ */
int IsMoveCamp(int i,int j)
{
	if(i*5+j==11 || i*5+j==13 || i*5+j==17 || i*5+j==21 || i*5+j==23 || i*5+j==36 || i*5+j==38 || i*5+j==42 || i*5+j==46 || i*5+j==48)
		return 1;
	else
		return 0;
}

/* ************************************************************************ */
/* 函数功能：i,j位置是否大本营					     	 					*/
/* 接口参数：																*/
/*     int i,j 棋盘位置行列号												*/
/* 返回值：																	*/
/*     1是大本营，0不是大本营												*/
/* ************************************************************************ */
int IsBaseCamp(int i,int j)
{
	if(i*5+j==1 || i*5+j==3 || i*5+j==56 || i*5+j==58)
		return 1;
	else
		return 0;
}

/* ************************************************************************ */
/* 函数功能：i,j位置是否有棋子占位的行营										*/
/* 接口参数：																*/
/*     char cMap[12][5] 棋盘局面											*/
/*     int i,j 棋盘位置行列号												*/
/* 返回值：																	*/
/*     1有棋子占位的行营,0不是行营或是空行营								*/
/* ************************************************************************ */
int IsFilledCamp(char cMap[12][5],int i,int j)
{
	if(IsMoveCamp(i,j) && cMap[i][j]!='0')
		return 1;
	else
		return 0;
}

/* ************************************************************************ */
/* 函数功能：双方布局后棋局初始化											*/
/* 接口参数：																*/
/*     char cMap[12][5] 棋盘局面											*/
/*     char *cOutMessage 布局字符序列										*/
/* ************************************************************************ */
void InitMap(char cMap[12][5],char *cOutMessage)
{
	int i,j,k;
	for(i=0;i<6;i++)									//标记对方棋子
		for(j=0;j<5;j++)
			if(IsMoveCamp(i,j))
				cMap[i][j]='0';							//行营不能放子，故为0
			else
				cMap[i][j]='X';							//对方棋子未知，以X代替
	k=6;												//回复己方布局消息中，布局数组的偏移量
	for(i=6;i<12;i++)									//标记己方棋子
		for(j=0;j<5;j++)
			if(IsMoveCamp(i,j))
				cMap[i][j]='0';							//行营不能放子
			else
				cMap[i][j]=cOutMessage[k++];			//将cOutMessage中的棋子序列放入棋盘中

}

/* ************************************************************************ */
/* 函数功能：根据裁判反馈刷新棋盘											*/
/* 接口参数：																*/
/*     char cMap[12][5] 棋盘局面											*/
/*     char *cInMessage 来自裁判的GO YXYX R YX命令							*/
/*     char *cOutMessage 发给裁判的BESTMOVE YXYX命令						*/
/* ************************************************************************ */
void FreshMap(char cMap[12][5],char *cInMessage,char *cOutMessage)
{
	char x1,y1;														//起点
	char x2,y2;														//落点
	char result=-1;													//碰子结果
    if(cInMessage[0]=='G')											// GO 指令
	{
		if(cInMessage[3]>='A' && cInMessage[3]<='L')
		{
			y1=cInMessage[3]-'A';									//
			x1=cInMessage[4]-'0';									//取得起点与落点坐标
			y2=cInMessage[5]-'A';									//
			x2=cInMessage[6]-'0';									//
			result=cInMessage[8]-'0';								//碰子结果
			if(cInMessage[10]>='A' && cInMessage[10]<='L')			//对方司令战死后显示军旗位置，若为00表示军旗位置未知
				cMap[(cInMessage[10]-'A')][cInMessage[11]-'0']='L'; //修改棋盘，将对方军旗位置写入棋盘
			switch(result)											//根据不同结果修改棋盘
			{
				case 0:												//对方棋子被己方吃掉
					cMap[y1][x1]='0';								//清空起点位置，由于对方棋子被我方吃掉，所以不更新落点
					break;
				case 1:												//对方吃掉己方棋子
					cMap[y2][x2]=cMap[y1][x1];						//将对方棋子移动到落点位置
					cMap[y1][x1]='0';								//并清空起点
					break;
				case 2:												//双方棋子对死
					cMap[y1][x1]='0';								//清空起点位置
					cMap[y2][x2]='0';								//清空落点位置
					break;
				case 3:												//对方移动棋子
					cMap[y2][x2]=cMap[y1][x1];						//将对方棋子移动到落点
					cMap[y1][x1]='0';								//并清空起点位置
					break;
			}
		}
	}
    if(cInMessage[0]=='R')													// RESULT 指令，裁判返回己方行棋结果
	{
		y1=cOutMessage[9]-'A';												//计算我方
		x1=cOutMessage[10]-'0';												//棋子起点与
		y2=cOutMessage[11]-'A';												//--落点--
		x2=cOutMessage[12]-'0';												//--坐标
		result=cInMessage[7]-'0';											//行棋结果
		if(cInMessage[8]==' ' && cInMessage[9]>='A' && cInMessage[9]<='L')  //对方司令战死后显示军旗位置
			cMap[(cInMessage[9]-'A')][cInMessage[10]-'0']='L';
		switch(result)										//根据不同结果修改棋盘
		{
			case 0:											//己方棋子被对方吃掉
				cMap[y1][x1]='0';
				break;
			case 1:											//己方吃掉对方棋子
				cMap[y2][x2]=cMap[y1][x1];					//移动我方棋子到落点坐标
				cMap[y1][x1]='0';							//清空起点
				break;
			case 2:											//双方棋子对死
				cMap[y1][x1]='0';							//清空起点
				cMap[y2][x2]='0';							//清空落点
				break;
			case 3:											//己方移动棋子
				cMap[y2][x2]=cMap[y1][x1];
				cMap[y1][x1]='0';
				break;
		}
	}
	
}
/* ************************************************************************ */
/* 函数功能：根据INFO指令,返回参赛队名										*/
/* 接口参数：																*/
/*     char *cInMessage 接收的INFO ver指令									*/
/*     char *cOutMessage 参赛队名											*/
/* ************************************************************************ */
void CalInfo(char *cInMessage,char *cVer,char *cOutMessage)
{
	strcpy(cVer,cInMessage+5);
	strcpy(cOutMessage,"NAME GaGaChess");
}

/* ************************************************************************ */
/* 函数功能：根据START指令,返回布局											*/
/* 接口参数：																*/
/*     char *cInMessage 接收的START first time steps指令					*/
/*     int *iFirst 先行权[0先行，1后行]										*/
/*     int *iTime 行棋时间限制(单位秒)[1000,3600]							*/
/*     int *iStep 进攻等待限制(单位步)[10,31]								*/
/*     char *cOutMessage 布局字符序列										*/
/* ************************************************************************ */
void CalArray(char *cInMessage,int *iFirst,int *iTime,int *iStep,char *cOutMessage)
{
	*iFirst=cInMessage[6]-'0';						//通过减法，将char转化为int，取得是否先行
	*iTime=cInMessage[8]-'0';						//取得行棋时间限制最高位数字
	*iTime=*iTime*10+(cInMessage[9]-'0');			
	*iTime=*iTime*10+(cInMessage[10]-'0');
	*iTime=*iTime*10+(cInMessage[11]-'0');
	*iStep=cInMessage[13]-'0';						//取得进攻等待限制最高位数字
	*iStep=*iStep*10+(cInMessage[14]-'0');          //取得进攻等待限制最低位数字
	if(*iFirst == 0)  //先手
	{
		//strcpy(cOutMessage,"ARRAY cigdcegkefkfaibgidjhhhjlj");//改过了的飘香一剑   还是有点克双喜
		//strcpy(cOutMessage,"ARRAY cigcdegkefkfaibgidjhhhjlj");//改过了的飘香一剑   还是有点克双喜
		//strcpy(cOutMessage,"ARRAY cegicdfkkhiebdagijjjghhlf");//改过的双喜临门  攻防有据
		//strcpy(cOutMessage, "ARRAY diahcbgkkfiecfigjhedjljhg");
		//strcpy(cOutMessage,"ARRAY fhbicdieagkcghkedgjfihjlj");//于无声处  
		//strcpy(cOutMessage,"ARRAY fiehgciadgbhgiekdcfjkhjlj");//乌龙摆尾    先手有点克制双喜临门
		//strcpy(cOutMessage,"ARRAY aibheeiggikcdghdkcjffhjlj");//三节阵    防御不错  暂时没测出效果
		//strcpy(cOutMessage,"ARRAY eihigagccffedikkgdjbhhjlj");//雾山重剑
		//strcpy(cOutMessage,"ARRAY ecdiafggkdibkgfejhicjljhh");//改过的布局
		strcpy(cOutMessage, "ARRAY diahcbgkkfiecfigjhedjljhg");//1
		 // strcpy(cOutMessage, "ARRAY cidfckaggkdhgeiifjbhehjlj");
	}else  //后手
	{
		//strcpy(cOutMessage,"ARRAY cebidkhfgdiakgfcjeigjljhh");
		//strcpy(cOutMessage,"ARRAY cigdcegkefkfaibgidjhhhjlj");//改过了的飘香一剑   还是有点克双喜
		//strcpy(cOutMessage,"ARRAY cigcdegkefkfaibgidjhhhjlj");//改过了的飘香一剑   还是有点克双喜
		//strcpy(cOutMessage,"ARRAY cegicdfkkhiebdagijjjghhlf");//改过的双喜临门  攻防有据
		//strcpy(cOutMessage,"ARRAY fhbicdieagkcghkedgjfihjlj");//于无声处  
		//strcpy(cOutMessage,"ARRAY fiehgciadgbhgiekdcfjkhjlj");//乌龙摆尾    先手有点克制双喜临门
		//strcpy(cOutMessage,"ARRAY aibheeiggikcdghdkcjffhjlj");//三节阵    防御不错  暂时没测出效果
		//strcpy(cOutMessage,"ARRAY eihigagccffedikkgdjbhhjlj");//雾山重剑
		//strcpy(cOutMessage, "ARRAY cigdcegkefkfaigbidjhhhjlj");
		//strcpy(cOutMessage, "ARRAY diahcbgkkfiecfigjhedjljhg");1
		strcpy(cOutMessage, "ARRAY cibhfeidckgakhgfjgjedljhi");//2
	}
}

/* ************************************************************************ */
/* 函数功能：计算己方最佳着法(本程序为示例算法,请参赛选手自行改进算法)		*/
/* 接口参数：																*/
/*     char *cMap 棋盘局面													*/
/*     char *cInMessage 来自裁判的 GO 命令									*/
/*     char *cOutMessage 发给裁判的 BESTMOVE 命令							*/
/* ************************************************************************ */
void CalBestmove(char cMap[12][5],char *cInMessage,char *cOutMessage)
{
	strcpy(cOutMessage,"BESTMOVE A0A0");			//定义回复消息模板，通过下面四句代码形成走法
	cOutMessage[9] = se.theBestMove.fx+'A';					//fx==fromX
	cOutMessage[10]= se.theBestMove.fy+'0';				//fy==fromY
	cOutMessage[11]= se.theBestMove.tx+'A';				//tx==toX
	cOutMessage[12]= se.theBestMove.ty+'0';				//ty==toY
}		
//初始化顶点
void initVector(Vector (*vectors)[5]){
	int i,j;
	for (i = 0;i<12;i++)
	{
		for (j = 0;j<5;j++)
	{
		vectors[i][j].row = i;//行坐标
		vectors[i][j].col = j;//列坐标
		if ((i == 0)||(i == 11))
		{
			vectors[i][j].isStuck = 1;
		}
		if (((i == 2)&&(j == 1))||((i == 2)&&(j == 3))||((i == 3)&&(j == 2))||((i == 4)&&(j == 1))||((i == 4)&&(j == 3))||((i == 7)&&(j == 1))||((i == 7)&&(j == 3))||((i == 8)&&(j == 2))||((i == 9)&&(j == 1))||((i == 9)&&(j == 3)))
		{
			vectors[i][j].isSave = 1;//标志行营
		}
	}
	}
	//标志公路
	for ( i = 1; i <= 10; i++) {
		vectors[i][0].isRoad = 1;
		vectors[i][4].isRoad = 1;
	}
	for ( j = 1; j <= 3; j++) {
		vectors[1][j].isRoad = 1;
		vectors[5][j].isRoad = 1;
		vectors[6][j].isRoad = 1;
		vectors[10][j].isRoad = 1;
		}
}

//转化界面传递过来的信息并且更新至顶点数组中
void transformChess(char CMap[12][5],Vector (*vectors)[5]){
	for(int i = 0;i<12;i++)
		for (int j = 0;j<5;j++)
		{
			if (CMap[i][j] == 'A')
			{
				vectors[i][j].power = 10;		//power应该指棋子的权力大小（或者说军衔大小）
				vectors[i][j].belongTo = 0;		//0表示己方，1表示对方
			}else if (CMap[i][j] == 'B')
			{
				vectors[i][j].power = 9;
				vectors[i][j].belongTo = 0;
			}else if (CMap[i][j] == 'C')
			{
				vectors[i][j].power = 8;
				vectors[i][j].belongTo = 0;
			}else if (CMap[i][j] == 'D')
			{
				vectors[i][j].power = 7;
				vectors[i][j].belongTo = 0;
			}else if (CMap[i][j] == 'E')
			{
				vectors[i][j].power = 6;
				vectors[i][j].belongTo = 0;
			}else if (CMap[i][j] == 'F')
			{
				vectors[i][j].power = 5;
				vectors[i][j].belongTo = 0;
			}else if (CMap[i][j] == 'G')
			{
				vectors[i][j].power = 4;
				vectors[i][j].belongTo = 0;
			}else if (CMap[i][j] == 'H')
			{
				vectors[i][j].power = 3;
				vectors[i][j].belongTo = 0;
			}else if (CMap[i][j] == 'I')
			{
				vectors[i][j].power = 2;
				vectors[i][j].belongTo = 0;
			}else if (CMap[i][j]== 'J')
			{
				vectors[i][j].power = 12;
				vectors[i][j].belongTo = 0;
			}else if (CMap[i][j]== 'K')
			{
				vectors[i][j].power = 11;
				vectors[i][j].belongTo = 0;
			}else if (CMap[i][j]== 'L')
			{
				vectors[i][j].power = 1;
				vectors[i][j].belongTo = 0;
			}
		    else if (CMap[i][j]== 'a')
			{
				vectors[i][j].power = 22;
				vectors[i][j].belongTo =1;
			}else if (CMap[i][j]== 'b')
			{
				vectors[i][j].power =21;
				vectors[i][j].belongTo =1;
			}else if (CMap[i][j]== 'c')
			{
				vectors[i][j].power =20 ;
				vectors[i][j].belongTo =1;
			}else if (CMap[i][j]== 'd')
			{
				vectors[i][j].power =19;
				vectors[i][j].belongTo = 1;
			}else if (CMap[i][j]== 'e')
			{
				vectors[i][j].power = 18;
				vectors[i][j].belongTo = 1;
			}else if (CMap[i][j] == 'f')
			{
				vectors[i][j].power = 17;
				vectors[i][j].belongTo = 1;
			}else if (CMap[i][j]== 'g')
			{
				vectors[i][j].power = 16;
				vectors[i][j].belongTo = 1;
			}else if (CMap[i][j]== 'h')
			{
				vectors[i][j].power = 15;
				vectors[i][j].belongTo = 1;
			}else if (CMap[i][j]== 'i')
			{
				vectors[i][j].power = 14;
				vectors[i][j].belongTo = 1;
			}else if (CMap[i][j]== 'j')
			{
				vectors[i][j].power = 24;
				vectors[i][j].belongTo = 1;
			}else if (CMap[i][j]== 'k')
			{
				vectors[i][j].power = 23;
				vectors[i][j].belongTo = 1;
			}else if (CMap[i][j] == 'l')
			{
				vectors[i][j].power = 13;
				vectors[i][j].belongTo = 1;
			}
			else if (CMap[i][j]== '0')
			{
				vectors[i][j].power = 0;	//空旗位对应的Power为0
				vectors[i][j].belongTo = 2;	//不属于哪一方，用2表示
			}
		}
}
void transformcMap(char cMap[12][5],char (*CMap)[5],Chance C[25])
{
	for(int i=0;i<12;i++)
		for(int j=0;j<5;j++)
		{
			if(cMap[i][j]>='a'&&cMap[i][j]<='l')//将我方棋子转换为大写字母
				CMap[i][j]=cMap[i][j]-32;
			else if(cMap[i][j]=='0')
				CMap[i][j]=cMap[i][j];//将空位置0复制给CMap
		}
	pb.FreshAssume(pb.C,CMap);
}
/*
double Step31(char cInMessage[200],char CMap[12][5],Chance C[25],Vector vectors[12][5],ChessMove &bestmove)
{
	MoveGenertor mg;
    SearchEngine se2;
	ChessMove c1;
    Assessment am;					//估值
	double x=0;
	double grapplevalue=0;			//格斗值？？？
	double sadplacevalue=0;			//伤心之地值？？？
	int z=0;
	int CurMapNumber[12][5];
	int count;
	double stepvalue=-100;
	char value='0';
	if(cInMessage[0]=='R')			//Result指令 cInMessage[7]为结果，0为己方行棋后被对方棋子吃掉，1为吃掉对方棋子，2为对死，3为仅移动；
	{
		if(cInMessage[7]!='3')
		{
			//如果发生了碰子
			k=0;					//k为记录行棋k步未碰子，此时碰子了，故将k值归零
			FIRSTONLYMOVE=2;		//发生了碰子
			STARTMOVE=0;			//这个变量的意思搞不懂
		}
		else
		{
			if(STARTMOVE==0)
			{
				FIRSTONLYMOVE=1;	//表示己方先移动
                STARTMOVE=1;
			}
			k++;
            
		}
	}
	else if(cInMessage[0]=='G')		//GO指令  GO move result flag 裁判通知我方对方行棋结果，cInMessage[8]表示行棋结果，result=0为对方行棋后对方棋子被吃掉，1为吃掉己方棋子，2为对死，3为仅移动；
	{
		if(cInMessage[8]!='3')
		{
			k=0;
			FIRSTONLYMOVE=2;		//发生了碰子
			STARTMOVE=0;
		}
		else
		{
			if(STARTMOVE==0)
			{
				FIRSTONLYMOVE=0;	//表示对方先移动
                STARTMOVE=1;
			}
			k++;
		}
	}
	if((k>15)&&FIRSTONLYMOVE==1)   //(猜测)已经行走了25步未碰子，又是我方的先手，所以此时不发起进攻很危险
	{
		se2.CharToInt(CMap,CurMapNumber);//将char转换为int
		count=mg.CreatePossibleMove(CurMapNumber,0,0,vectors);//调用走法生成器
		int count2= mg.CreatePossibleMove(CurMapNumber, 1, 1, vectors);
		int count3 = mg.CreatePossibleMove(CurMapNumber, 2, 0, vectors);
			for(z=0;z<count;z++)
		{
		   grapplevalue=0;
		   sadplacevalue=0;
           c1=mg.GetMove(0,z);
		   if(CMap[c1.tx][c1.ty]!='0')//必须碰子
		   {
			    grapplevalue=am.MyGrappleValue(c1,C,CMap);
			   if(grapplevalue>0&&
				CMap[c1.tx][c1.ty]!='k'&&CMap[c1.tx][c1.ty]!='j'
				&&CMap[c1.fx][c1.fy]!='K')//如果拼杀后我方获胜则可以计算位置域
			   {
				   value=CMap[c1.fx][c1.fy];
				   sadplacevalue=am.MySadPlaceValue(c1,CMap,C,value);
			   }
			   x=grapplevalue+sadplacevalue;
			   if(x>stepvalue)
			   {
				   stepvalue=x;
				   bestmove.fx=c1.fx;
				   bestmove.fy=c1.fy;
				   bestmove.tx=c1.tx;
				   bestmove.ty=c1.ty;
			   }
		   }
		}
			for (z = 0; z<count3; z++)
			{
				grapplevalue = 0;
				sadplacevalue = 0;
				c1 = mg.GetMove(2, z);
				if (CMap[c1.tx][c1.ty] != '0')//必须碰子
				{
					grapplevalue = am.MyGrappleValue(c1, C, CMap);
					if (grapplevalue>0 &&
						CMap[c1.tx][c1.ty] != 'k'&&CMap[c1.tx][c1.ty] != 'j'
						&&CMap[c1.fx][c1.fy] != 'K')//如果拼杀后我方获胜则可以计算位置域
					{
						value = CMap[c1.fx][c1.fy];
						sadplacevalue = am.MySadPlaceValue(c1, CMap, C, value);
					}
					x = grapplevalue + sadplacevalue;
					if (x>stepvalue)
					{
						stepvalue = x;
						bestmove.fx = c1.fx;
						bestmove.fy = c1.fy;
						bestmove.tx = c1.tx;
						bestmove.ty = c1.ty;
					}
				}
			}
			



	}
return stepvalue;
}
*/
void step31(char cInMessage[200], char CMap[12][5], Chance C[25], Vector vectors[12][5]) {
	if (cInMessage[0] == 'R')			//Result指令 cInMessage[7]为结果，0为己方行棋后被对方棋子吃掉，1为吃掉对方棋子，2为对死，3为仅移动；
	{
		if (cInMessage[7] != '3')
		{
			//如果发生了碰子
			k = 0;					//k为记录行棋k步未碰子，此时碰子了，故将k值归零
			FIRSTONLYMOVE = 2;		//发生了碰子
			STARTMOVE = 0;			//我方31步没有危险
		}
		else
		{
			if (STARTMOVE == 0)
			{
				FIRSTONLYMOVE = 1;	//表示己方先移动
				STARTMOVE = 1;
			}
			k++;

		}
	}
	else if (cInMessage[0] == 'G')		//GO指令  GO move result flag 裁判通知我方对方行棋结果，cInMessage[8]表示行棋结果，result=0为对方行棋后对方棋子被吃掉，1为吃掉己方棋子，2为对死，3为仅移动；
	{
		if (cInMessage[8] != '3')
		{
			k = 0;
			FIRSTONLYMOVE = 2;		//发生了碰子
			STARTMOVE = 0;
		}
		else
		{
			if (STARTMOVE == 0)
			{
				FIRSTONLYMOVE = 0;	//表示对方先移动
				STARTMOVE = 1;
			}
			k++;
		}
	}

	if (k > 15 && FIRSTONLYMOVE == 1) //必须为我方先手
	{
		se.theBestMove=se.mg.moveList[0][1];
	}
}

void defence(char CMap[12][5], Chance C[25], Vector vectors[12][5]) {
	ChessMove defencemove;
	int CurMapNumber[12][5];
	char nowrank='L';
	if (CMap[11][1] == 'L')
	{
		if (CMap[10][0] <= 'k'&&CMap[10][0] >= 'a')
		{
			se.CharToInt(CMap, CurMapNumber);//将char转换为int
			int count = se.mg.CreatePossibleMove(CurMapNumber, 0,0,vectors);//产生可能的走法
			for (int i = 0; i < count; i++)
			{
				ChessMove c1 = se.mg.GetMove(0, i);
				if (c1.tx == 10 && c1.ty == 0)
				{
					if (CMap[c1.fx][c1.fy] < nowrank) { nowrank = CMap[c1.fx][c1.fy]; defencemove = c1; }
				}
			}
			se.theBestMove = defencemove;
			FLAG = 0;
		}
		else if (CMap[10][1] <= 'k'&&CMap[10][1] >= 'a')
		{
			se.CharToInt(CMap, CurMapNumber);//将char转换为int
			int count = se.mg.CreatePossibleMove(CurMapNumber, 0, 0, vectors);//产生可能的走法
			for (int i = 0; i < count; i++)
			{
				ChessMove c1 = se.mg.GetMove(0, i);
				if (c1.tx == 10 && c1.ty == 1)
				{
					if (CMap[c1.fx][c1.fy] < nowrank) { nowrank = CMap[c1.fx][c1.fy]; defencemove = c1; }
				}
			}
			se.theBestMove = defencemove;
			FLAG = 0;
		}
		else if (CMap[10][2] <= 'k'&&CMap[10][2] >= 'a')
		{
			se.CharToInt(CMap, CurMapNumber);//将char转换为int
			int count = se.mg.CreatePossibleMove(CurMapNumber, 0, 0, vectors);//产生可能的走法
			for (int i = 0; i < count; i++)
			{
				ChessMove c1 = se.mg.GetMove(0, i);
				if (c1.tx == 10 && c1.ty == 2)
				{
					if (CMap[c1.fx][c1.fy] < nowrank) { nowrank = CMap[c1.fx][c1.fy]; defencemove = c1; }
				}
			}
			se.theBestMove = defencemove;
			FLAG = 0;
		}
	}
	else if (CMap[11][3] == 'L')
	{
		if (CMap[10][2] <= 'k'&&CMap[10][2] >= 'a')
		{
			se.CharToInt(CMap, CurMapNumber);//将char转换为int
			int count = se.mg.CreatePossibleMove(CurMapNumber, 0, 0, vectors);//产生可能的走法
			for (int i = 0; i < count; i++)
			{
				ChessMove c1 = se.mg.GetMove(0, i);
				if (c1.tx == 10 && c1.ty == 2)
				{
					if (CMap[c1.fx][c1.fy] < nowrank) { nowrank = CMap[c1.fx][c1.fy]; defencemove = c1; }
				}
			}
			se.theBestMove = defencemove;
			FLAG = 0;
		}
		else if (CMap[10][3] <= 'k'&&CMap[10][3] >= 'a')
		{
			se.CharToInt(CMap, CurMapNumber);//将char转换为int
			int count = se.mg.CreatePossibleMove(CurMapNumber, 0, 0, vectors);//产生可能的走法
			for (int i = 0; i < count; i++)
			{
				ChessMove c1 = se.mg.GetMove(0, i);
				if (c1.tx == 10 && c1.ty == 3)
				{
					if (CMap[c1.fx][c1.fy] < nowrank) { nowrank = CMap[c1.fx][c1.fy]; defencemove = c1; }
				}
			}
			se.theBestMove = defencemove;
			FLAG = 0;
		}
		else if (CMap[10][4] <= 'k'&&CMap[10][4] >= 'a')
		{
			se.CharToInt(CMap, CurMapNumber);//将char转换为int
			int count = se.mg.CreatePossibleMove(CurMapNumber, 0, 0, vectors);//产生可能的走法
			for (int i = 0; i < count; i++)
			{
				ChessMove c1 = se.mg.GetMove(0, i);
				if (c1.tx == 10 && c1.ty == 4)
				{
					if (CMap[c1.fx][c1.fy] < nowrank) { nowrank = CMap[c1.fx][c1.fy]; defencemove = c1; }
				}
			}
			se.theBestMove = defencemove;
			FLAG = 0;
		}
	}

}

int main()
{
	char cVer[200];			//协议版本
	int iFirst;				//先行权[0先行，1后行]
	int iTime;				//行棋时间限制(单位秒)[1000,3600]
	int iStep;				//进攻等待限制(单位步)[10,31]
	char cInMessage[200];   //输入通信内容
	char cOutMessage[200];  //输出通信内容
    char cMap[12][5];		//棋盘
	char CMap[12][5];
	double Alpha=-999999.0;
	double Beta=10000.0;
	double stepvalue=0;
    Vector vectors[12][5];
	initVector(vectors);	//初始化棋盘顶点
	cin.getline(cInMessage,200);		//获取来自裁判系统的指令 "GO 0000 0 00"
	while(cInMessage[0]>='A')
	{
		switch(cInMessage[0])
		{
			case 'I':								//INFO指令
				CalInfo(cInMessage,cVer,cOutMessage);
				cout<<cOutMessage<<endl;			//将"NAME "指令传递给裁判系统
				break;
			case 'S':								//START 指令 
				CalArray(cInMessage,&iFirst,&iTime,&iStep,cOutMessage);	
				InitMap(cMap,cOutMessage);
				pb.InitProbability(cMap);           //初始化概率表
				transformcMap(cMap,CMap,pb.C);
				transformChess(CMap,vectors);//权值是否设置正确？
				cout<<cOutMessage<<endl;
				break;
			case 'G':								//GO 指令
				if(!(cInMessage[3]=='0'&&cInMessage[4]=='0'&&cInMessage[5]=='0'&&cInMessage[6]=='0'))
				pb.FreshChance(CMap,cInMessage,cOutMessage,pb.C);//对方行棋完毕，刷新概率表
				se.start = clock();
				FreshMap(cMap,cInMessage,cOutMessage);
				transformcMap(cMap,CMap,pb.C);
				transformChess(CMap,vectors);
    			//se.AWT(0,Alpha,Beta,CMap,vectors,pb.C,bestmove,0);
				//stepvalue=Step31(cInMessage,CMap,pb.C,vectors,bestmove);
				//defence(CMap, pb.C, vectors);
				se.MakeDecision(CMap, vectors, pb.C);
				step31(cInMessage, CMap, pb.C, vectors);
				CalBestmove(cMap, cInMessage, cOutMessage);
				cout<<cOutMessage<<endl;
				break;
			case 'R':								//RESULT 指令
				pb.FreshChance(CMap,cInMessage,cOutMessage,pb.C);//我方行棋完毕，刷新概率表
				FreshMap(cMap,cInMessage,cOutMessage);
				transformcMap(cMap,CMap,pb.C);
				transformChess(CMap,vectors);
				step31(cInMessage, CMap, pb.C, vectors);
   				//stepvalue=Step31(cInMessage,CMap,pb.C,vectors,bestmove);
				break;
			case 'E':								//END 指令
				return 0;	
			default:
				return 1;				
		}
		cin.getline(cInMessage,200);	//获取来自裁判系统的指令"START" 或 "RESULT" 或 "GO" 或 "END"
	}
	return 0;
}

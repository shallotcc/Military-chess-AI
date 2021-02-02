// Probability.h: interface for the Probability class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROBABILITY_H__99F86BE6_9DF7_4DE6_BA71_414874A06267__INCLUDED_)
#define AFX_PROBABILITY_H__99F86BE6_9DF7_4DE6_BA71_414874A06267__INCLUDED_

//#include "SearchEngine.h"	// Added by ClassView
#include "hance.h"	// Added by ClassView
#include "hessMove.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Probability  
{
public:
	void ChangeArmyAround(Chance *C,int flagy,int i);
	void KillCommander(Chance *C,int flagy,int i);
	void FreshAssume(Chance *C,char CMap[][5]);									//根据概率表，将对方棋子确定下来，将棋局转换为确定棋局
	void Assume(Chance *C,char CMap[][5]);										//根据概率表，将概率最大者作为该棋子的值
	void CoordinateChange(Chance *C,int result,ChessMove move,int mychess,int i);	//根据裁判信息刷新概率表中棋子行列信息
	//SearchEngine se;
	int SerchChess(Chance C[],int x,int y);											//找到对应位置上的棋子的概率表
	void FreshChance(char CMap[][5],char CInMessage[],char COutMessage[],Chance *C);//刷新概率表
	Chance C[25];																	//概率表，棋子总数为25
	void InitProbability(char CurMap[12][5]);										//概率表初始化
	Probability();
	virtual ~Probability();

};

#endif // !defined(AFX_PROBABILITY_H__99F86BE6_9DF7_4DE6_BA71_414874A06267__INCLUDED_)

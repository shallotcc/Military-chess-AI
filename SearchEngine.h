// SearchEngine.h: interface for the SearchEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEARCHENGINE_H__9A34849F_1C51_4AFD_A9EF_8F7BB22913F6__INCLUDED_)
#define AFX_SEARCHENGINE_H__9A34849F_1C51_4AFD_A9EF_8F7BB22913F6__INCLUDED_
#include "Assessment.h"	// Added by ClassView
#include "Assessment2.h"
#include<algorithm>
#include "Probability.h"	// Added by ClassView
#include "MoveGenertor.h"	// Added by ClassView
#include "math.h"
#include "hance.h"	// Added by ClassView
#include "SearchEngine.h"
#include "windows.h"
#include "hessMove.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class SearchEngine  
{
public:
	int Because;
	void ChangePowerAndBelong(Vector (*CurVector)[5],char  map,int x,int y);
	void ChangeVector(Vector (*CurVector)[5],Vector vectors[12][5],char CurMap[12][5],ChessMove move);
	void FreshMap(int result,Chance *CurC,Chance C[25],ChessMove move,int mychess,char (*CurMap)[5]);
	int total;
    void Thansfor(char(*CurMap)[5],char CMap[12][5],ChessMove move,Chance *CurC,Chance C[25]);
	void Referee(char(*CurMap)[5],ChessMove move,Chance *CurC,Chance C[25],int myChess);
	Assessment am;
	Assessment2 am2;
	void CharToInt(char CurMap[][5],int (*CMap)[5]);
	void CoordinateChange(Chance *CurC,Chance C[25],int result,ChessMove move,int mychess);//改变对于棋子概率表中的坐标
    Probability pb;
	void Total(char (*CurMap)[5]);//计算棋面对方棋子个数
	MoveGenertor mg;
	int maxdepht;
	double  averEntroy0;//第0局棋面信息熵
	double AWT(int depht,double Alpha,double Beta,char CMap[12][5],Vector (*vectors)[5],Chance C[25],ChessMove &bestmove,double upscore);
	double Window(int windowvalue,int s,int total,Chance c[25]);//计算搜索窗口增长倍数
	void MakeDecision( char CMap[12][5], Vector(*vectors)[5], Chance C[25]);
	double DFS(char CurMap[12][5], Vector CurVector[12][5], Chance CurC[25], int depth, int ismine, double Alpha, double Beta);
	double ScoreDifference(char NowMap[12][5], Vector(*NowVector)[5], Chance NowC[25], int ismine);
	double scoremove[12][5][12][5];
	ChessMove theBestMove;
	double Alpha = -999999;
	double Beta = 999999;
	const int Winscore = 88888;
	int flag = 0;
	time_t start, end, dur;
	bool timewarning;
	void denfence(char CurMap[12][5], int count, ChessMove &c1, int &flag);
	void jingyan(char CurMap[12][5], int count, ChessMove &c1, int &flag);
	void attack(char CurMap[12][5], int count, ChessMove &c1, int &flag);
	void armyflag(char CurMap[12][5], int count, ChessMove &c1, int &flag);
	//friend bool CMP(ChessMove m, ChessMove n);
	//double Scoremove(ChessMove m);
	void sort(int depth,int left, int right);
	SearchEngine();
	virtual ~SearchEngine();

protected:
};

#endif // !defined(AFX_SEARCHENGINE_H__9A34849F_1C51_4AFD_A9EF_8F7BB22913F6__INCLUDED_)

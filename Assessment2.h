#pragma once
#include"Probability.h"
#include"hessMove.h"
#include"Vector.h"
#include<iostream>
class Assessment2
{
public:
	double n;
	double m;
	Probability p;//位置域得分
	int z;
	char a[12][5];//用来装位置域
	char c;
	void Place(ChessMove p, char CMap[][5]);
	//double defence(char CMap[][5]);
	double ChessScore(char NowMap[12][5], Vector(*NowVector)[5], Chance NowC[25], int ismine);
	double PlaceScore(char NowMap[12][5], Vector(*NowVector)[5], Chance NowC[25], int ismine);
	double DefenceScore(char NowMap[12][5], Vector(*NowVector)[5], Chance NowC[25], int ismine);
	double Cscore[12] = {45,33,20,12,7,4,2,1,9,8,19,99999};//0司令1军长2师长3旅长4团长5营长6连长7排长8工兵9地雷10炸弹11军旗
	Assessment2();
	~Assessment2();

private:

};

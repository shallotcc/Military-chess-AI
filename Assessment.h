// Assessment.h: interface for the Assessment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASSESSMENT_H__0B70F2C9_A01D_415C_8D9B_72D038266B47__INCLUDED_)
#define AFX_ASSESSMENT_H__0B70F2C9_A01D_415C_8D9B_72D038266B47__INCLUDED_

#include "hance.h"	// Added by ClassView
#include "hessMove.h"	// Added by ClassView
#include "Probability.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Assessment  
{
public:
	double Railway(char CMap[][5]);
	
	double Home(Chance C[],char CMap[][5]);

	double MySadPlaceValue(ChessMove p, char Cmap[][5], Chance C[],char k);

	double MyGrappleValue(ChessMove p,Chance C[],char Cmap[][5]);
	double MyGrappleCount(int z,int k,Chance C[]);

	double GoOrBackValue(ChessMove move,int mymove);

    double SadPlaceValue(ChessMove p,char CMap[][5],Chance C[],int k);

	void Place(ChessMove p,char Cmap[][5]);

	int MyChessLevel(char c);

	double GrappleValue(ChessMove p, Chance C[], char Cmap[12][5]);
	double GrappleCount(int z, int k,Chance C[]);

	double EnemyDefence(char CMap[12][5],int x,int y,int m);
	double EnemyArmyDefence(char CMap[12][5],char CurMap[12][5],Chance C[25],Chance CurC[25],ChessMove move);
	double MyDefence(char CMap[][5],int x,int y,int m);
	double MyArmyFlagDefence(char CMap[12][5],char CurMap[12][5],Chance C[25],Chance CurC[25],ChessMove move);

	double n;
	double m;
	Probability p;//位置域得分
	int z;
	char a[12][5];//用来装位置域
	char c;
};

#endif // !defined(AFX_ASSESSMENT_H__0B70F2C9_A01D_415C_8D9B_72D038266B47__INCLUDED_)

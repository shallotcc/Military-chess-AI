// MoveGenertor.h: interface for the MoveGenertor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVEGENERTOR_H__8AF391F0_CE6D_4CF9_84BD_0719D18D1BE6__INCLUDED_)
#define AFX_MOVEGENERTOR_H__8AF391F0_CE6D_4CF9_84BD_0719D18D1BE6__INCLUDED_

#include "myCObArray.h"
#include "hessMove.h"	// Added by ClassView
#include "Vector.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MoveGenertor
{
public:
	void Screen(int fX, int fY, int tX, int tY, int nPly, int position[12][5]);
	bool judgeInOwnCamp(int row, int col, int belongTo);
	void getNextVector(Vector tempVetor, Vector(*vectors)[5]);
	bool judgeInLine(int oldClickedrow1, int oldClickedcol1, int clickedrow1, int clickedcol1, Vector(*vectors)[5]);
	int judgeBetweenVectors(int(*position)[5], int oldClickedrow1, int oldClickedcol1, int clickedrow1, int clickedcol1, Vector(*vectors)[5]);
	int judgeMoveChess(int(*position)[5], int oldClickedrow1, int oldClickedcol1, int clickedrow1, int clickedcol1, Vector(*vectors)[5]);
	void addMove(int fX, int fY, int tX, int tY, int nPly, int position[][5]);
	bool isRobot(int moveID);
	bool isValidVector(int i, int j);
	void canMove(int(*position)[5], int row1, int col1, int row2, int col2, int nPly, Vector(*vectors)[5]);
	int over12(int moveID);
	int CreatePossibleMove(int(*position)[5], int nPly, int nSide, Vector(*vectors)[5]);
	ChessMove GetMove(int col, int row);

	myCObArray stack;
	myCObArray stack2;
	MoveGenertor();
	virtual ~MoveGenertor();
	ChessMove moveList[10][2000];//用于存储所有可移动棋子的起始坐标和落点坐标
	int moveCount;
private:
	

	myCObArray set;

};

#endif // !defined(AFX_MOVEGENERTOR_H__8AF391F0_CE6D_4CF9_84BD_0719D18D1BE6__INCLUDED_)


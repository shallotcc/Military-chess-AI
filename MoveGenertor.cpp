// MoveGenertor.cpp: implementation of the MoveGenertor class.
//
//////////////////////////////////////////////////////////////////////
#include <afxwin.h>
#include"MoveGenertor.h"
#include "Vector.h"
#include<iostream>
//#include "iostream.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MoveGenertor::MoveGenertor()
{
	//set = new myCObArray();
}

MoveGenertor::  ~MoveGenertor()
{

}




ChessMove MoveGenertor::GetMove(int col, int row)
{
	return moveList[col][row];
}

int MoveGenertor::CreatePossibleMove(int(*position)[5], int nPly, int nside, Vector(*vectors)[5])
{
	moveCount = 0;
	int moveID = 0;

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 5; j++) {

			moveID = position[i][j];//将棋子的价值依次取出
			if ((vectors[i][j].power != 0))//如果当前节点不是空节点
			{
				if ((nside == 0)//min节点
					&& (vectors[i][j].belongTo == 1)) {// 要产生机器人的路径所有可能然而该坐标上的旗子属于玩家，跳出
													   // System.out.println("玩家之旗");
					continue;
				}
				if ((nside == 1)
					&& (vectors[i][j].belongTo == 0)) {// 要产生玩家的路径所有可能然而该坐标上的旗子属于机器人，跳出
					continue;
				}
				if (over12(moveID) == 12) {//如果是地雷，跳出
					continue;
				}
				if (!judgeInOwnCamp(i, j,
					vectors[i][j].belongTo)) {// 判断起点自身是否可以移动
					continue;
				}
				if (vectors[i][j].isRoad == 0) {// 是公路顶点
					if (isValidVector(i - 1, j)) {// 上
						if (judgeMoveChess(position, i, j, i - 1, j, vectors) != 0) {
							addMove(i, j, i - 1, j, nPly, position);
						}
					}
					if (isValidVector(i + 1, j)) {// 下
						if (judgeMoveChess(position, i, j, i + 1, j, vectors) != 0) {
							addMove(i, j, i + 1, j, nPly, position);
						}
					}
					if (isValidVector(i, j - 1)) {// 左
						if (judgeMoveChess(position, i, j, i, j - 1, vectors) != 0) {
							addMove(i, j, i, j - 1, nPly, position);
						}
					}
					if (isValidVector(i, j + 1)) {// 右
						if (judgeMoveChess(position, i, j, i, j + 1, vectors) != 0) {
							addMove(i, j, i, j + 1, nPly, position);
						}
					}
					if (isValidVector(i - 1, j - 1)) {// 左上
						if (judgeMoveChess(position, i, j, i - 1, j - 1, vectors) != 0) {
							addMove(i, j, i - 1, j - 1, nPly, position);
						}
					}
					if (isValidVector(i + 1, j - 1)) {// 左下
						if (judgeMoveChess(position, i, j, i + 1, j - 1, vectors) != 0) {
							addMove(i, j, i + 1, j - 1, nPly, position);
						}
					}
					if (isValidVector(i - 1, j + 1)) {// 右上
						if (judgeMoveChess(position, i, j, i - 1, j + 1, vectors) != 0) {
							addMove(i, j, i - 1, j + 1, nPly, position);
						}
					}
					if (isValidVector(i + 1, j + 1)) {// 右下
						if (judgeMoveChess(position, i, j, i + 1, j + 1, vectors) != 0) {
							addMove(i, j, i + 1, j + 1, nPly, position);
						}
					}

				}
				else {// 铁路顶点
					int flag = 0;
					moveID = over12(moveID);
					if (moveID != 2) {// 不是工兵
						if ((moveID == 12)
							|| (vectors[i][j].isStuck == 1))
							continue;// 不能移动
						else {// 可以移动的旗子
							  // 上
							for (int k = 0; k < i; k++)
								if ((isValidVector(i - k - 1, j))
									&& ((flag = judgeMoveChess(position, i, j, i - k - 1, j, vectors)) != 0))
								{
									if (flag == 1)//空棋位
										addMove(i, j, i - k - 1, j, nPly, position);
									else if (flag == 2)//不是空棋位不用继续循环
									{
										addMove(i, j, i - k - 1, j, nPly, position);
										break;
									}
								}
								else {
									break;
								}
								// 下
								for (int k = 0; k < 11 - i; k++)
									if ((isValidVector(i + k + 1, j))
										&& ((flag = judgeMoveChess(position, i, j,
											i + k + 1, j, vectors)) != 0)) {
										if (flag == 1)//空棋位
											addMove(i, j, i + k + 1, j, nPly, position);
										else if (flag == 2)//不是空棋位不用继续循环
										{
											addMove(i, j, i + k + 1, j, nPly, position);
											break;
										}
									}
									else {
										break;
									}
									// 左
									for (int k = 0; k < j; k++)
										if ((isValidVector(i, j - k - 1))
											&& ((flag = judgeMoveChess(position, i, j, i, j - k - 1, vectors)) != 0)) {
											if (flag == 1)//空棋位
												addMove(i, j, i, j - k - 1, nPly, position);
											else if (flag == 2)//不是空棋位不用继续循环
											{
												addMove(i, j, i, j - k - 1, nPly, position);
												break;
											}
										}
										else {
											break;
										}
										// 右
										for (int k = 0; k < 4 - j; k++)
											if ((isValidVector(i, j + k + 1))
												&& ((flag = judgeMoveChess(position, i, j,
													i, j + k + 1, vectors)) != 0)) {
												if (flag == 1)//空棋位
													addMove(i, j, i, j + k + 1, nPly, position);
												else if (flag == 2)//不是空棋位不用继续循环
												{
													addMove(i, j, i, j + k + 1, nPly, position);
													break;
												}
											}
											else {
												break;
											}
											if (isValidVector(i - 1, j - 1)) {// 左上
												if (judgeMoveChess(position, i, j, i - 1,
													j - 1, vectors) != 0) {
													addMove(i, j, i - 1, j - 1, nPly, position);
												}
											}
											if (isValidVector(i + 1, j - 1)) {// 左下
												if (judgeMoveChess(position, i, j, i + 1,
													j - 1, vectors) != 0) {
													addMove(i, j, i + 1, j - 1, nPly, position);
												}
											}
											if (isValidVector(i - 1, j + 1)) {// 右上
												if (judgeMoveChess(position, i, j, i - 1,
													j + 1, vectors) != 0) {
													addMove(i, j, i - 1, j + 1, nPly, position);
												}
											}
											if (isValidVector(i + 1, j + 1)) {// 右下
												if (judgeMoveChess(position, i, j, i + 1,
													j + 1, vectors) != 0) {
													addMove(i, j, i + 1, j + 1, nPly, position);
												}
											}
						}
					}
					else {// 工兵
						  // 上
						if (set.GetSize() > 0) {
							set.RemoveAll();  //将栈中元素全部删除
						}

						CPoint *point = new CPoint(i, j);//创建坐标点
						set.Add((CObject *)point);//将当前顶点类转换为基类并压入栈
						if (isValidVector(i - 1, j)) {
							canMove(position, i, j, i - 1, j, nPly, vectors);
							set.Add((CObject *)(new CPoint(i - 1, j)));
						}
						if (isValidVector(i + 1, j)) {
							canMove(position, i, j, i + 1, j, nPly, vectors);
							set.Add((CObject *)(new CPoint(i + 1, j)));
						}
						if (isValidVector(i, j - 1)) {
							canMove(position, i, j, i, j - 1, nPly, vectors);
							set.Add((CObject *)(new CPoint(i, j - 1)));
						}
						if (isValidVector(i, j + 1)) {
							canMove(position, i, j, i, j + 1, nPly, vectors);
							set.Add((CObject *)(new CPoint(i, j + 1)));
						}


						//！！！！！！！！！！！！！！！！！
						if (isValidVector(i - 1, j - 1))
						{// 左上
							if (judgeMoveChess(position, i, j, i - 1, j - 1, vectors) != 0)
							{
								addMove(i, j, i - 1, j - 1, nPly, position);
							}
						}
						if (isValidVector(i + 1, j - 1))
						{// 左下
							if (judgeMoveChess(position, i, j, i + 1, j - 1, vectors) != 0)
							{
								addMove(i, j, i + 1, j - 1, nPly, position);
							}
						}
						if (isValidVector(i - 1, j + 1))
						{// 右上
							if (judgeMoveChess(position, i, j, i - 1, j + 1, vectors) != 0)
							{
								addMove(i, j, i - 1, j + 1, nPly, position);
							}
						}
						if (isValidVector(i + 1, j + 1))
						{// 右下
							if (judgeMoveChess(position, i, j, i + 1, j + 1, vectors) != 0)
							{
								addMove(i, j, i + 1, j + 1, nPly, position);
							}
						}
					}
				}
			}
			else {
				continue;
			}
		}
	return moveCount;


}

int MoveGenertor::over12(int moveID)
{
	if (moveID > 12)
		return (moveID - 12);
	else
		return moveID;
}

void MoveGenertor::canMove(int(*position)[5], int row1, int col1, int row2, int col2, int nPly, Vector(*vectors)[5])
{
	if ((vectors[row2][col2].power == 0)//如果该位置为空且是铁路则可以生成走法，并将落地坐标加入栈中
		&& (vectors[row2][col2].isRoad == 1)
		&& !((row1 == 5 && row2 == 6 && col1 % 2 == 1 && col2 % 2 == 1) ||
		(row1 == 6 && row2 == 5 && col1 % 2 == 1 && col2 % 2 == 1)))
	{
		addMove(row1, col1, row2, col2, nPly, position);
		set.Add((CObject *)(new CPoint(row2, col2)));
		if ((row2 == 5 || row2 == 6) && col2 % 2 == 1)
		{
			if (isValidVector(row2, col2 - 1)
				&& (!set.contains((CObject *)(new CPoint(row2, col2 - 1))))
				&& (vectors[row2][col2 - 1].isRoad == 1)) {
				canMove(position, row1, col1, row2, col2 - 1, nPly, vectors);
			}
			if (isValidVector(row2, col2 + 1)
				&& (!set.contains((CObject *)(new CPoint(row2, col2 + 1))))
				&& (vectors[row2][col2 + 1].isRoad == 1)) {
				canMove(position, row1, col1, row2, col2 + 1, nPly, vectors);
			}

		}
		else
		{
			if (isValidVector(row2 - 1, col2)
				&& (!set.contains((CObject *)(new CPoint(row2 - 1, col2))))
				&& (vectors[row2 - 1][col2].isRoad == 1)) {
				canMove(position, row1, col1, row2 - 1, col2, nPly, vectors);
			}
			if (isValidVector(row2 + 1, col2)
				&& (!set.contains((CObject *)(new CPoint(row2 + 1, col2))))
				&& (vectors[row2 + 1][col2].isRoad == 1)) {
				canMove(position, row1, col1, row2 + 1, col2, nPly, vectors);
			}
			if (isValidVector(row2, col2 - 1)
				&& (!set.contains((CObject *)(new CPoint(row2, col2 - 1))))
				&& (vectors[row2][col2 - 1].isRoad == 1)) {
				canMove(position, row1, col1, row2, col2 - 1, nPly, vectors);
			}
			if (isValidVector(row2, col2 + 1)
				&& (!set.contains((CObject *)(new CPoint(row2, col2 + 1))))
				&& (vectors[row2][col2 + 1].isRoad == 1)) {
				canMove(position, row1, col1, row2, col2 + 1, nPly, vectors);
			}
		}
	}
	else {
		if (judgeMoveChess(position, row1, col1, row2, col2, vectors) != 0)
			addMove(row1, col1, row2, col2, nPly, position);
	}

}

bool MoveGenertor::isValidVector(int i, int j)
{
	if ((i >= 0) && (i <= 11) && (j >= 0) && (j <= 4)) {
		return true;
	}
	else {
		return false;
	}
}

bool MoveGenertor::isRobot(int moveID)
{
	if (moveID < 13) {// 机器人
		return true;
	}
	else {// 玩家
		return false;
	}

}

void MoveGenertor::addMove(int fX, int fY, int tX, int tY, int nPly, int position[12][5])
{
	if (!(tX == 11 && tY % 2 == 1))
	{
		if (tX == 0 && tY % 2 == 1)
		{
			if (position[tX][tY] == 13)
				Screen(fX, fY, tX, tY, nPly, position);
			else {};
		}
		else
			Screen(fX, fY, tX, tY, nPly, position);
	}
}

int MoveGenertor::judgeMoveChess(int(*position)[5], int oldClickedrow1, int oldClickedcol1, int clickedrow1, int clickedcol1, Vector(*vectors)[5])
{
	int flag = 0;
	if ((vectors[oldClickedrow1][oldClickedcol1].isRoad == 0)
		&& (vectors[clickedrow1][clickedcol1].isRoad == 0)) {// 公路顶点对公路顶点
															 // 对于（0，0）这个顶点来说，能够移动的位子有右这一个位子
		if ((oldClickedrow1 == 0) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 0) && (clickedcol1 == 1))
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		// 对于（0,1）这个顶点来说，能够移动的位子有左、右这两个位子
		if (((oldClickedrow1 == 0) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 0) && (clickedcol1 == 0))
			|| ((oldClickedrow1 == 0) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 0) && (clickedcol1 == 2)))
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		// 对于（0，2）这个顶点来说，能够移动的位子有左、右这两个位子
		if (((oldClickedrow1 == 0) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 0) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 0) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 0) && (clickedcol1 == 3)))
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		// 对于（0，3）这个顶点来说，能够移动的位子有左、右这两个位子
		if (((oldClickedrow1 == 0) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 0) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 0) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 0) && (clickedcol1 == 4)))
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		// 对于（0，4）这个顶点来说，能够移动的位子有左这两个位子
		if ((oldClickedrow1 == 0) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 0) && (clickedcol1 == 3))
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		// 对于（11，0）这个顶点来说，能够移动的位子有右这一个位子
		if ((oldClickedrow1 == 11) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 11) && (clickedcol1 == 1))
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		// 对于（11,1）这个顶点来说，能够移动的位子有左、右这两个位子
		if ((oldClickedrow1 == 11) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 11) && (clickedcol1 == 0)
			|| (oldClickedrow1 == 11) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 11) && (clickedcol1 == 2))
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		// 对于（11，2）这个顶点来说，能够移动的位子有左、右这两个位子
		if ((oldClickedrow1 == 11) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 11) && (clickedcol1 == 1)
			|| (oldClickedrow1 == 11) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 11) && (clickedcol1 == 3))
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		// 对于（11，3）这个顶点来说，能够移动的位子有左、右这两个位子
		if ((oldClickedrow1 == 11) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 11) && (clickedcol1 == 2)
			|| (oldClickedrow1 == 11) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 11) && (clickedcol1 == 4))
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		// 对于（11，4）这个顶点来说，能够移动的位子有左这两个位子
		if ((oldClickedrow1 == 11) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 11) && (clickedcol1 == 3))
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		// 对于（2，1）这个顶点来说 ，能够移动的位子只有右、下、右下这三个位子
		if (((oldClickedrow1 == 2) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 2) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 2) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 3) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 2) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 3) && (clickedcol1 == 1))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（2，2）这个顶点来说 ，能够移动的位子只有左、下、右这三个位子
		else if (((oldClickedrow1 == 2) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 2) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 2) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 2) && (clickedcol1 == 3))
			|| ((oldClickedrow1 == 2) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 3) && (clickedcol1 == 2))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（2，3）这个顶点来说 ，能够移动的位子只有左、下、左下这三个位子
		else if (((oldClickedrow1 == 2) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 2) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 2) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 3) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 2) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 3) && (clickedcol1 == 3))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（3，1）这个顶点来说 ，能够移动的位子只有上、下、右这三个位子
		else if (((oldClickedrow1 == 3) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 2) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 3) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 4) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 3) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 3) && (clickedcol1 == 2))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（3，2）这个顶点来说 ，能够移动的位子只有左、上、下、右、左上、左下、右下、右上这八个位子
		else if (((oldClickedrow1 == 3) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 3) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 3) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 3) && (clickedcol1 == 3))
			|| ((oldClickedrow1 == 3) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 2) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 3) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 4) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 3) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 2) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 3) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 4) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 3) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 2) && (clickedcol1 == 3))
			|| ((oldClickedrow1 == 3) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 4) && (clickedcol1 == 3))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（3，3）这个顶点来说 ，能够移动的位子只有左、上、下这三个位子
		else if (((oldClickedrow1 == 3) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 2) && (clickedcol1 == 3))
			|| ((oldClickedrow1 == 3) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 4) && (clickedcol1 == 3))
			|| ((oldClickedrow1 == 3) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 3) && (clickedcol1 == 2))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（4，1）这个顶点来说 ，能够移动的位子只有上、右、右上这三个位子
		else if (((oldClickedrow1 == 4) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 3) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 4) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 3) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 4) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 4) && (clickedcol1 == 2))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（4，2）这个顶点来说 ，能够移动的位子只有左、上、右这三个位子
		else if (((oldClickedrow1 == 4) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 4) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 4) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 3) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 4) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 4) && (clickedcol1 == 3))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（4，3）这个顶点来说 ，能够移动的位子只有左、上、左上这三个位子
		else if (((oldClickedrow1 == 4) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 4) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 4) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 3) && (clickedcol1 == 3))
			|| ((oldClickedrow1 == 4) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 3) && (clickedcol1 == 2))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（7，1）这个顶点来说 ，能够移动的位子只有右、下、右下这三个位子
		else if (((oldClickedrow1 == 7) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 7) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 7) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 8) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 7) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 8) && (clickedcol1 == 2))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（7，2）这个顶点来说 ，能够移动的位子只有左、下、右这三个位子
		else if (((oldClickedrow1 == 7) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 7) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 7) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 7) && (clickedcol1 == 3))
			|| ((oldClickedrow1 == 7) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 8) && (clickedcol1 == 2))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（7，3）这个顶点来说 ，能够移动的位子只有左、下、左下这三个位子
		else if (((oldClickedrow1 == 7) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 7) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 7) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 8) && (clickedcol1 == 3))
			|| ((oldClickedrow1 == 7) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 8) && (clickedcol1 == 2))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（8，1）这个顶点来说 ，能够移动的位子只有右、上、下这三个位子
		else if (((oldClickedrow1 == 8) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 7) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 8) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 8) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 8) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 9) && (clickedcol1 == 1))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（8，2）这个顶点来说 ，能够移动的位子只有左、上、下、右、左上、左下、右上、右下这八个位子
		else if (((oldClickedrow1 == 8) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 8) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 8) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 8) && (clickedcol1 == 3))
			|| ((oldClickedrow1 == 8) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 7) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 8) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 9) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 8) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 7) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 8) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 9) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 8) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 7) && (clickedcol1 == 3))
			|| ((oldClickedrow1 == 8) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 9) && (clickedcol1 == 3))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（8，3）这个顶点来说 ，能够移动的位子只有左、上、下这三个位子
		else if (((oldClickedrow1 == 8) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 7) && (clickedcol1 == 3))
			|| ((oldClickedrow1 == 8) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 8) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 8) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 9) && (clickedcol1 == 3))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（9，1）这个顶点来说 ，能够移动的位子只有上、右、右上这三个位子
		else if (((oldClickedrow1 == 9) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 8) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 9) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 9) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 9) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 8) && (clickedcol1 == 2))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（9，2）这个顶点来说 ，能够移动的位子只有左、上、右这三个位子
		else if (((oldClickedrow1 == 9) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 9) && (clickedcol1 == 3))
			|| ((oldClickedrow1 == 9) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 9) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 9) && (oldClickedcol1 == 2)
				&& (clickedrow1 == 8) && (clickedcol1 == 2))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（9，3）这个顶点来说 ，能够移动的位子只有左、上、左上这三个位子
		else if (((oldClickedrow1 == 9) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 9) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 9) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 8) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 9) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 8) && (clickedcol1 == 3))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}
		else {
			// System.out.println("无法到达目标顶点");
			return 0;
		}
	}
	else if ((vectors[oldClickedrow1][oldClickedcol1].isRoad == 0)
		&& (vectors[clickedrow1][clickedcol1].isRoad == 1)) {// 公路对铁路
															 // 对于（0，0）这个顶点来说，能够移动到的位子只有下这一个位子
		if ((oldClickedrow1 == 0) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 1) && (clickedcol1 == 0)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（0，1）这个顶点来说，能够移动到的位子只有下这一个位子
		else if ((oldClickedrow1 == 0) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 1) && (clickedcol1 == 1)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（0，2）这个顶点来说，能够移动到的位子只有下这一个位子
		else if ((oldClickedrow1 == 0) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 1) && (clickedcol1 == 2)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（0，3）这个顶点来说，能够移动到的位子只有下这一个位子
		else if ((oldClickedrow1 == 0) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 1) && (clickedcol1 == 3)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（0，4）这个顶点来说，能够移动到的位子只有下这一个位子
		else if ((oldClickedrow1 == 0) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 1) && (clickedcol1 == 4)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（11，0）这个顶点来说，能够移动到的位子只有上这一个位子
		else if ((oldClickedrow1 == 11) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 10) && (clickedcol1 == 0)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（11，1）这个顶点来说，能够移动到的位子只有上这一个位子
		else if ((oldClickedrow1 == 11) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 10) && (clickedcol1 == 1)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（11，2）这个顶点来说，能够移动到的位子只有上这一个位子
		else if ((oldClickedrow1 == 11) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 10) && (clickedcol1 == 2)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（11，3）这个顶点来说，能够移动到的位子只有上这一个位子
		else if ((oldClickedrow1 == 11) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 10) && (clickedcol1 == 3)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（11，4）这个顶点来说，能够移动到的位子只有上这一个位子
		else if ((oldClickedrow1 == 11) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 10) && (clickedcol1 == 4)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（2，1）这个顶点来说，能够移动到的位子只有上、左、左上、左下、右上这五个位子
		else if (((oldClickedrow1 == 2) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 1) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 2) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 1) && (clickedcol1 == 0))
			|| ((oldClickedrow1 == 2) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 1) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 2) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 2) && (clickedcol1 == 0))
			|| ((oldClickedrow1 == 2) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 3) && (clickedcol1 == 0))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（2，2）这个顶点来说，能够移动到的位子只有上这一个位子
		else if ((oldClickedrow1 == 2) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 1) && (clickedcol1 == 2)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（2，3）这个顶点来说，能够移动到的位子只有上、右、左上、右上、右下这五个位子
		else if (((oldClickedrow1 == 2) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 1) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 2) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 1) && (clickedcol1 == 3))
			|| ((oldClickedrow1 == 2) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 1) && (clickedcol1 == 4))
			|| ((oldClickedrow1 == 2) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 2) && (clickedcol1 == 4))
			|| ((oldClickedrow1 == 2) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 3) && (clickedcol1 == 4))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（3，1）这个顶点来说，能够移动到的位子只有左这一个位子
		else if ((oldClickedrow1 == 3) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 3) && (clickedcol1 == 0)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（3，3）这个顶点来说，能够移动到的位子只有上这一个位子
		else if ((oldClickedrow1 == 3) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 3) && (clickedcol1 == 4)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（4，1）这个顶点来说，能够移动到的位子只有左、下、左上、左下、右下这一个位子
		else if ((oldClickedrow1 == 4) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 5) && (clickedcol1 == 0)
			|| (oldClickedrow1 == 4) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 3) && (clickedcol1 == 0)
			|| (oldClickedrow1 == 4) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 4) && (clickedcol1 == 0)
			|| (oldClickedrow1 == 4) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 5) && (clickedcol1 == 1)
			|| (oldClickedrow1 == 4) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 5) && (clickedcol1 == 2)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（4，2）这个顶点来说，能够移动到的位子只有下这一个位子
		else if ((oldClickedrow1 == 4) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 5) && (clickedcol1 == 2)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（4，3）这个顶点来说，能够移动到的位子只有下、右、左下、右上、右下这一个位子
		else if ((oldClickedrow1 == 4) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 3) && (clickedcol1 == 4)
			|| (oldClickedrow1 == 4) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 4) && (clickedcol1 == 4)
			|| (oldClickedrow1 == 4) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 5) && (clickedcol1 == 4)
			|| (oldClickedrow1 == 4) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 5) && (clickedcol1 == 3)
			|| (oldClickedrow1 == 4) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 5) && (clickedcol1 == 2)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（9，1）这个顶点来说，能够移动到的位子只有下、左、左上、左下、右下这五个位子
		else if (((oldClickedrow1 == 9) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 10) && (clickedcol1 == 1))
			|| ((oldClickedrow1 == 9) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 8) && (clickedcol1 == 0))
			|| ((oldClickedrow1 == 9) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 10) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 9) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 9) && (clickedcol1 == 0))
			|| ((oldClickedrow1 == 9) && (oldClickedcol1 == 1)
				&& (clickedrow1 == 10) && (clickedcol1 == 0))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（9，2）这个顶点来说，能够移动到的位子只有下这一个位子
		else if ((oldClickedrow1 == 9) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 10) && (clickedcol1 == 2)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（9，3）这个顶点来说，能够移动到的位子只有下、右、左下、右上、右下这五个位子
		else if (((oldClickedrow1 == 9) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 10) && (clickedcol1 == 2))
			|| ((oldClickedrow1 == 9) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 10) && (clickedcol1 == 3))
			|| ((oldClickedrow1 == 9) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 8) && (clickedcol1 == 4))
			|| ((oldClickedrow1 == 9) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 9) && (clickedcol1 == 4))
			|| ((oldClickedrow1 == 9) && (oldClickedcol1 == 3)
				&& (clickedrow1 == 10) && (clickedcol1 == 4))) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（8，1）这个顶点来说，能够移动到的位子只有左这一个位子
		else if ((oldClickedrow1 == 8) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 8) && (clickedcol1 == 0)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（8，3）这个顶点来说，能够移动到的位子只有上这一个位子
		else if ((oldClickedrow1 == 8) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 8) && (clickedcol1 == 4)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（7，1）这个顶点来说，能够移动到的位子只有左、上、左下、左上、右上这一个位子
		else if ((oldClickedrow1 == 7) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 6) && (clickedcol1 == 0)
			|| (oldClickedrow1 == 7) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 7) && (clickedcol1 == 0)
			|| (oldClickedrow1 == 7) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 8) && (clickedcol1 == 0)
			|| (oldClickedrow1 == 7) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 6) && (clickedcol1 == 1)
			|| (oldClickedrow1 == 7) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 6) && (clickedcol1 == 2)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（7，2）这个顶点来说，能够移动到的位子只有上这一个位子
		else if ((oldClickedrow1 == 7) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 6) && (clickedcol1 == 2)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（7，3）这个顶点来说，能够移动到的位子只有上、右、左上、右下、右上这一个位子
		else if ((oldClickedrow1 == 7) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 6) && (clickedcol1 == 4)
			|| (oldClickedrow1 == 7) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 7) && (clickedcol1 == 4)
			|| (oldClickedrow1 == 7) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 8) && (clickedcol1 == 4)
			|| (oldClickedrow1 == 7) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 6) && (clickedcol1 == 3)
			|| (oldClickedrow1 == 7) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 6) && (clickedcol1 == 2)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}
		else {
			// System.out.println("无法到达目标顶点");
			return 0;
		}

	}
	else if ((vectors[oldClickedrow1][oldClickedcol1].isRoad == 1)
		&& (vectors[clickedrow1][clickedcol1].isRoad == 1)) {// 铁路对铁路
		int moveID = position[oldClickedrow1][oldClickedcol1];
		moveID = over12(moveID);
		if (moveID == 2) {// 工兵走旗，则利用栈进行搜索路径

			stack.RemoveAll();
			stack2.RemoveAll();
			// System.out.println("工兵走旗");
			Vector *tempVetor = new Vector();// 建立一个顶点类临时对象，用来存放从栈中取出的对象
											 // 将第一次按下顶点周围的满足既在铁路上又是空顶点的压入栈中
			stack.Add((CObject *)&vectors[oldClickedrow1][oldClickedcol1]);
			while (!stack.empty()) {
				// System.out.println(PlayGame.stack.empty());
				*tempVetor = stack.pop();
				stack2.Add((CObject *)&tempVetor);
				if (judgeInLine((*tempVetor).row, (*tempVetor).col, clickedrow1,
					clickedcol1, vectors)) {// 判断是否可以到达目标顶点
					return judgeBetweenVectors(position, oldClickedrow1,
						oldClickedcol1, clickedrow1, clickedcol1, vectors);
				}
				else {
					getNextVector(*tempVetor, vectors);
				}
			}
			// System.out.println("工兵被卡住了，无法移动");
			return 0;
		}
		else {
			// 如果是其他兵种，则判断所选中的两个位子是不是在同一行或则同一列上
			if (judgeInLine(oldClickedrow1, oldClickedcol1, clickedrow1,
				clickedcol1, vectors)) {
				return flag = judgeBetweenVectors(position, oldClickedrow1,
					oldClickedcol1, clickedrow1, clickedcol1, vectors);
			}
		}

	}
	else if ((vectors[oldClickedrow1][oldClickedcol1].isRoad == 1)
		&& (vectors[clickedrow1][clickedcol1].isRoad == 0)) {// 铁路对公路
															 // 对于（1，0）这个顶点来说，能够移动到的位子只有上、右下位子
		if ((oldClickedrow1 == 1) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 2) && (clickedcol1 == 1)
			|| (oldClickedrow1 == 1) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 0) && (clickedcol1 == 0)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（1，1）这个顶点来说，能够移动到的位子上、下位子
		else if ((oldClickedrow1 == 1) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 2) && (clickedcol1 == 1)
			|| (oldClickedrow1 == 1) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 0) && (clickedcol1 == 1)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（1，2）这个顶点来说，能够移动到的位子有上、下、左下、右下位子
		else if ((oldClickedrow1 == 1) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 2) && (clickedcol1 == 1)
			|| (oldClickedrow1 == 1) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 2) && (clickedcol1 == 2)
			|| (oldClickedrow1 == 1) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 2) && (clickedcol1 == 3)
			|| (oldClickedrow1 == 1) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 0) && (clickedcol1 == 2)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（1，3）这个顶点来说，能够移动到的位子上、下位子
		else if ((oldClickedrow1 == 1) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 2) && (clickedcol1 == 3)
			|| (oldClickedrow1 == 1) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 0) && (clickedcol1 == 3)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（1，4）这个顶点来说，能够移动到的位子上、左下位子
		else if ((oldClickedrow1 == 1) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 2) && (clickedcol1 == 3)
			|| (oldClickedrow1 == 1) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 0) && (clickedcol1 == 4)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（2，0）这个顶点来说，能够移动到的位子右位子
		else if ((oldClickedrow1 == 2) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 2) && (clickedcol1 == 1)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（2，4）这个顶点来说，能够移动到的位子右位子
		else if ((oldClickedrow1 == 2) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 2) && (clickedcol1 == 3)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（3，0）这个顶点来说，能够移动到的位子右、右上、右下位子
		else if ((oldClickedrow1 == 3) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 2) && (clickedcol1 == 1)
			|| (oldClickedrow1 == 3) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 3) && (clickedcol1 == 1)
			|| (oldClickedrow1 == 3) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 4) && (clickedcol1 == 1)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（3，4）这个顶点来说，能够移动到的位子左、左上、左下位子
		else if ((oldClickedrow1 == 3) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 2) && (clickedcol1 == 3)
			|| (oldClickedrow1 == 3) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 3) && (clickedcol1 == 3)
			|| (oldClickedrow1 == 3) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 4) && (clickedcol1 == 3)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（4，0）这个顶点来说，能够移动到的位子右位子
		else if ((oldClickedrow1 == 4) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 4) && (clickedcol1 == 1)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（4，4）这个顶点来说，能够移动到的位子左位子
		else if ((oldClickedrow1 == 4) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 4) && (clickedcol1 == 3)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（5，0）这个顶点来说，能够移动到的位子右上位子
		else if ((oldClickedrow1 == 5) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 4) && (clickedcol1 == 1)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（5，1）这个顶点来说，能够移动到的上位子
		else if ((oldClickedrow1 == 5) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 4) && (clickedcol1 == 1)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（5，2）这个顶点来说，能够移动到的上、左上、右上位子
		else if ((oldClickedrow1 == 5) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 4) && (clickedcol1 == 1)
			|| (oldClickedrow1 == 5) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 4) && (clickedcol1 == 2)
			|| (oldClickedrow1 == 5) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 4) && (clickedcol1 == 3)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（5，3）这个顶点来说，能够移动到的上位子
		else if ((oldClickedrow1 == 5) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 4) && (clickedcol1 == 3)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（5，4）这个顶点来说，能够移动到的上位子
		else if ((oldClickedrow1 == 5) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 4) && (clickedcol1 == 3)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（6，0）这个顶点来说，能够移动到的位子右下位子
		else if ((oldClickedrow1 == 6) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 7) && (clickedcol1 == 1)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（6，1）这个顶点来说，能够移动到的下位子
		else if ((oldClickedrow1 == 6) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 7) && (clickedcol1 == 1)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（6，2）这个顶点来说，能够移动到的下、左下、右下位子
		else if ((oldClickedrow1 == 6) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 7) && (clickedcol1 == 1)
			|| (oldClickedrow1 == 6) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 7) && (clickedcol1 == 2)
			|| (oldClickedrow1 == 6) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 7) && (clickedcol1 == 3)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（6，3）这个顶点来说，能够移动到的下位子
		else if ((oldClickedrow1 == 6) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 7) && (clickedcol1 == 3)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（6，4）这个顶点来说，能够移动到的下位子
		else if ((oldClickedrow1 == 6) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 7) && (clickedcol1 == 3)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（7，0）这个顶点来说，能够移动到的位子右位子
		else if ((oldClickedrow1 == 7) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 7) && (clickedcol1 == 1)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（7，4）这个顶点来说，能够移动到的位子左位子
		else if ((oldClickedrow1 == 7) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 7) && (clickedcol1 == 3)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（8，0）这个顶点来说，能够移动到的位子右、右上、右下位子
		else if ((oldClickedrow1 == 8) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 9) && (clickedcol1 == 1)
			|| (oldClickedrow1 == 8) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 8) && (clickedcol1 == 1)
			|| (oldClickedrow1 == 8) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 7) && (clickedcol1 == 1)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（8，4）这个顶点来说，能够移动到的位子左、左上、左下位子
		else if ((oldClickedrow1 == 8) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 9) && (clickedcol1 == 3)
			|| (oldClickedrow1 == 8) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 8) && (clickedcol1 == 3)
			|| (oldClickedrow1 == 8) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 7) && (clickedcol1 == 3)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（9，0）这个顶点来说，能够移动到的位子右位子
		else if ((oldClickedrow1 == 9) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 9) && (clickedcol1 == 1)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（9，4）这个顶点来说，能够移动到的位子右位子
		else if ((oldClickedrow1 == 9) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 9) && (clickedcol1 == 3)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（10，0）这个顶点来说，能够移动到的位子只有上、右下位子
		else if ((oldClickedrow1 == 10) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 9) && (clickedcol1 == 1)
			|| (oldClickedrow1 == 10) && (oldClickedcol1 == 0)
			&& (clickedrow1 == 11) && (clickedcol1 == 0)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（10，1）这个顶点来说，能够移动到的位子上、下位子
		else if ((oldClickedrow1 == 10) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 9) && (clickedcol1 == 1)
			|| (oldClickedrow1 == 10) && (oldClickedcol1 == 1)
			&& (clickedrow1 == 11) && (clickedcol1 == 1)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（10，2）这个顶点来说，能够移动到的位子有上、下、左下、右下位子
		else if ((oldClickedrow1 == 10) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 9) && (clickedcol1 == 1)
			|| (oldClickedrow1 == 10) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 9) && (clickedcol1 == 2)
			|| (oldClickedrow1 == 10) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 9) && (clickedcol1 == 3)
			|| (oldClickedrow1 == 10) && (oldClickedcol1 == 2)
			&& (clickedrow1 == 11) && (clickedcol1 == 2)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（10，3）这个顶点来说，能够移动到的位子上、下位子
		else if ((oldClickedrow1 == 10) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 9) && (clickedcol1 == 3)
			|| (oldClickedrow1 == 10) && (oldClickedcol1 == 3)
			&& (clickedrow1 == 11) && (clickedcol1 == 3)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}// 对于（10，4）这个顶点来说，能够移动到的位子上、左下位子
		else if ((oldClickedrow1 == 10) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 9) && (clickedcol1 == 3)
			|| (oldClickedrow1 == 10) && (oldClickedcol1 == 4)
			&& (clickedrow1 == 11) && (clickedcol1 == 4)) {
			return judgeBetweenVectors(position, oldClickedrow1,
				oldClickedcol1, clickedrow1, clickedcol1, vectors);
		}
		else {
			// System.out.println("无法到达目标顶点");
			return 0;
		}
	}
	return 0;

}

int MoveGenertor::judgeBetweenVectors(int(*position)[5], int oldClickedrow1, int oldClickedcol1, int clickedrow1, int clickedcol1, Vector(*vectors)[5])
{
	//起点为空  
	if (vectors[oldClickedrow1][oldClickedcol1].power == 0)
	{
		return 0;
	}
	// 起点在自己的大本营中||起点是地雷
	if ((!
		judgeInOwnCamp(oldClickedrow1, oldClickedcol1,
			vectors[oldClickedrow1][oldClickedcol1]
			.belongTo)) || (vectors[oldClickedrow1][oldClickedcol1].power == 12)
		|| (vectors[oldClickedrow1][oldClickedcol1].power == 24))
		return 0;
	// 如果第二个选中的顶点为空旗位，则将旗子移动
	if (vectors[clickedrow1][clickedcol1].power == 0)
		return 1;
	else
	{// 如果有旗子
	 // 同一方的旗子，则不做任何移动
		if (vectors[oldClickedrow1][oldClickedcol1].belongTo == vectors[clickedrow1][clickedcol1].belongTo)
			return 0;
		else
		{// 不是同一方的旗子，则继续判断第二次选中的顶点是否是行营，
		 // 是行营，则不做任何移动
			if (vectors[clickedrow1][clickedcol1].isSave == 1)
				return 0;
			else //不是同一方棋子
				return 2;

		}
	}

}

bool MoveGenertor::judgeInLine(int oldClickedrow1, int oldClickedcol1, int clickedrow1, int clickedcol1, Vector(*vectors)[5])
{
	// 两个顶点在同一顶点
	int row1 = oldClickedrow1;
	int col1 = oldClickedcol1;
	int row2 = clickedrow1;
	int col2 = clickedcol1;
	if (((row1 == row2) && (row1 == 1)) || ((row1 == row2) && (row1 == 5))
		|| ((row1 == row2) && (row1 == 6))
		|| ((row1 == row2) && (row1 == 10))) {
		// System.out.print("属于同一行");
		if (col1 <= col2)
		{
			for (int j = col1 + 1; j < col2; j++)
			{
				if (vectors[row1][j].power != 0)
				{
					// System.out.println("然后却无法到达目标顶点");
					return false;
				}
			}
			// System.out.println("并且可以到达目标顶点");
			return true;
		}
		else
		{
			for (int j = col2 + 1; j < col1; j++)
			{
				if (vectors[row1][j].power != 0)
				{
					// System.out.println("无法到达目标顶点");
					return false;
				}
			}
			// System.out.println("并且可以到达目标顶点");
			return true;
		}

	}
	// 两个顶点在同一列上
	else if (((col1 == col2) && (col1 == 0))
		|| ((col1 == col2) && (col1 == 4))
		|| ((col1 == col2) && (col1 == 2))) {
		// System.out.println("属于同一列");
		if (row1 <= row2) {
			for (int i = row1 + 1; i < row2; i++) {
				// System.out.println("铁路对铁路");
				if (vectors[i][col1].power != 0) {
					// System.out.println("然而却无法到达目标顶点");
					return false;
				}
			}
			// System.out.println("并且可以到达目标顶点");
			return true;
		}
		else {
			for (int i = row2 + 1; i < row1; i++) {
				if (vectors[i][col1].power != 0) {
					// System.out.println("然而却无法到达目标顶点");
					return false;
				}
			}
			// System.out.println("并且可以到达目标顶点");
			return true;
		}
	}
	return false;// 不是在同一战线上的旗子

}

void MoveGenertor::getNextVector(Vector tempVetor, Vector(*vectors)[5])
{
	if (((tempVetor.row - 1) >= 0)
		&& (&vectors[tempVetor.row - 1][tempVetor.col] != NULL)
		&& (vectors[tempVetor.row - 1][tempVetor.col]
			.power == 0)
		&& (vectors[tempVetor.row - 1][tempVetor.col].isRoad == 1)
		&& (judgeInLine(tempVetor.row - 1, tempVetor.col,
			tempVetor.row, tempVetor.col, vectors))) {// 如果上顶点存在并且为空，则将其压入栈中
		if ((stack2.GetSize() != 0)
			&& stack2
			.search((CObject *)&vectors[tempVetor.row - 1][tempVetor.col]) == -1) {// 如果这个顶点之前没被测试过
			stack
				.Add((CObject *)&vectors[tempVetor.row - 1][tempVetor.col]);
			// System.out.println("转上");
		}
	}
	if (((tempVetor.row + 1) <= 11)
		&& (&vectors[tempVetor.row + 1][tempVetor.col] != NULL)
		&& (vectors[tempVetor.row + 1][tempVetor.col]
			.power == 0)
		&& (vectors[tempVetor.row + 1][tempVetor.col].isRoad == 1)
		&& (judgeInLine(tempVetor.row + 1, tempVetor.col,
			tempVetor.row, tempVetor.col, vectors))) {// 如果下顶点存在并且为空，则将其压入栈中
		if ((stack2.GetSize() != 0)
			&& stack2
			.search((CObject *)&vectors[tempVetor.row + 1][tempVetor.col]) == -1) {
			stack
				.Add((CObject *)&vectors[tempVetor.row + 1][tempVetor.col]);
			// System.out.println("转下");
		}
	}
	if (((tempVetor.col - 1) >= 0)
		&& (&vectors[tempVetor.row][tempVetor.col - 1] != NULL)
		&& (vectors[tempVetor.row][tempVetor.col - 1]
			.power == 0)
		&& (vectors[tempVetor.row][tempVetor.col - 1].isRoad == 1)
		&& (judgeInLine(tempVetor.row, tempVetor.col - 1,
			tempVetor.row, tempVetor.col, vectors))) {// 如果左顶点存在并且为空，则将其压入栈中
		if ((stack2.GetSize() != 0)
			&& stack2
			.search((CObject *)&vectors[tempVetor.row][tempVetor.col - 1]) == -1) {
			stack
				.Add((CObject *)&vectors[tempVetor.row][tempVetor.col - 1]);
			// System.out.println("转左");
		}
	}
	if ((tempVetor.col + 1 <= 4)
		&& (&vectors[tempVetor.row][tempVetor.col + 1] != NULL)
		&& (vectors[tempVetor.row][tempVetor.col + 1]
			.power == 0)
		&& (vectors[tempVetor.row][tempVetor.col + 1].isRoad == 1)
		&& (judgeInLine(tempVetor.row, tempVetor.col + 1,
			tempVetor.row, tempVetor.col, vectors))) {// 如果右顶点存在并且为空，则将其压入栈中
		if ((stack2.GetSize() != 0)
			&& stack2
			.search((CObject *)&vectors[tempVetor.row][tempVetor.col + 1]) == -1) {
			stack.Add((CObject *)&vectors[tempVetor.row][tempVetor.col + 1]);
			// System.out.println("转右");
		}
	}

}

bool MoveGenertor::judgeInOwnCamp(int row, int col, int belongTo)
{
	if (row == 0 && col % 2 == 1 || row == 11 && col % 2 == 1) {
		return false;// 玩家在自己的大本营中
	}
	else
		return true;// 玩家不再自己的大本营中


}





void MoveGenertor::Screen(int fX, int fY, int tX, int tY, int nPly, int position[][5])
{
	moveList[nPly][moveCount].setFX(fX);
	moveList[nPly][moveCount].setFY(fY);
	moveList[nPly][moveCount].setTX(tX);
	moveList[nPly][moveCount].setTY(tY);
	moveCount++;

	if (position[fX][fY] == 2)//是我方工兵走棋
	{
		if ((fX == 1 || fX == 5 || fX == 6 || fX == 10 || fY == 0 || fY == 4) && (tX == 1 || tX == 5 || tX == 6 || tX == 10 || tY == 0 || tY == 4) && fX != tX && fY != tY)//工兵在铁路上走棋
		{
			if (tY == 0 || tY == 4)
			{
				if (position[tX - 1][tY] == 24 && ((tX - 1) > 0 && (tX - 1) < 11))//向前
				{
					moveList[nPly][moveCount].setFX(fX);
					moveList[nPly][moveCount].setFY(fY);
					moveList[nPly][moveCount].setTX(tX - 1);
					moveList[nPly][moveCount].setTY(tY);
					moveCount++;
				}
			}
			else if (tX == 1)
			{
				if (position[tX][tY + 1] == 24 && ((tY + 1) >= 0 && (tY + 1) <= 4))//向右检测一步
				{
					moveList[nPly][moveCount].setFX(fX);
					moveList[nPly][moveCount].setFY(fY);
					moveList[nPly][moveCount].setTX(tX);
					moveList[nPly][moveCount].setTY(tY + 1);
					moveCount++;
				}
				if (position[tX][tY - 1] == 24 && ((tY - 1) >= 0 && (tY - 1) <= 4))//向左检测一步
				{
					moveList[nPly][moveCount].setFX(fX);
					moveList[nPly][moveCount].setFY(fY);
					moveList[nPly][moveCount].setTX(tX);
					moveList[nPly][moveCount].setTY(tY - 1);
					moveCount++;
				}
			}
		}
	}

	if (position[fX][fY] == 14)//是对方工兵走棋
	{
		if ((fX == 1 || fX == 5 || fX == 6 || fX == 10 || fY == 0 || fY == 4) && (tX == 1 || tX == 5 || tX == 6 || tX == 10 || tY == 0 || tY == 4) && fX != tX && fY != tY)//工兵在铁路上走棋
		{
			if (tY == 0 || tY == 4)
			{
				if (position[tX + 1][tY] == 12 && ((tX + 1) > 0 && (tX + 1) < 11))//向前一步
				{
					moveList[nPly][moveCount].setFX(fX);
					moveList[nPly][moveCount].setFY(fY);
					moveList[nPly][moveCount].setTX(tX + 1);
					moveList[nPly][moveCount].setTY(tY);
					moveCount++;
				}
			}
			else if (tX == 10)
			{
				if (position[tX][tY + 1] == 24 && ((tY + 1) >= 0 && (tY + 1) <= 4))//向右检测一步
				{
					moveList[nPly][moveCount].setFX(fX);
					moveList[nPly][moveCount].setFY(fY);
					moveList[nPly][moveCount].setTX(tX);
					moveList[nPly][moveCount].setTY(tY + 1);
					moveCount++;
				}
				if (position[tX][tY - 1] == 24 && ((tY - 1) >= 0 && (tY - 1) <= 4))//向左检测一步
				{
					moveList[nPly][moveCount].setFX(fX);
					moveList[nPly][moveCount].setFY(fY);
					moveList[nPly][moveCount].setTX(tX);
					moveList[nPly][moveCount].setTY(tY - 1);
					moveCount++;
				}
			}
		}
	}
}

// Probability.cpp: implementation of the Probability class.
//
//////////////////////////////////////////////////////////////////////

#include "Probability.h"
#include <iostream>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Probability::Probability()
{

}

Probability::~Probability()
{

}

void Probability::InitProbability(char CurMap[12][5])
{
	//概率需要重新计算
	int k = 0;
	//0司令, 1军长, 2师长, 3旅长, 4团长, 5营长, 6连长, 7排长, 8工兵, 9地雷,10炸弹, 11军旗
	int g;
	for (int i = 0; i < 6; i++)						//6排
		for (int j = 0; j < 5; j++)					//5列
		{
			if (CurMap[i][j] != '0')				//若不是空位，则对当前位棋子种类的概率进行计算
			{
				C[k].x = i;
				C[k].y = j;
				if (i == 0 && j % 2 == 1)						//大本营
				{
					//这里的概率是迷之概率，乱算的
					for (g = 0; g < 12; g++)
					{
						if (g == 11)						//军旗概率，军旗编号为11（棋种共12个，编号由0开始）
							C[k].P[g] = 1.0 / 2;
						else if (g == 7)					//排长的概率，排长编号为7
							C[k].P[g] = 1.0 / 2;
						else if (g == 6)					//连长的概率，连长编号为6
							C[k].P[g] = 0;
						else
							C[k].P[g] = 0;
					}
				}
				else if (i == 0 && j == 0) {
					for (g = 0; g < 11; g++)
					{
						if (g == 7) C[k].P[g] = 3.0 / 22;
						else if (g == 9) C[k].P[g] = 6.0 / 22;
						else if (g == 8) C[k].P[g] = 3.0 / 22;
						else if (g == 6) C[k].P[g] = 2.0 / 22;
						else if (g == 5) C[k].P[g] = 2.0 / 22;
						else C[k].P[g] = 1.0/22;
					}
				}
				else if (i == 0 && j == 2) {
					for (g = 0; g < 11; g++)
					{
						if (g == 9) C[k].P[g] = 10.0 / 22;
						else if (g == 3) C[k].P[g] = 2.0 / 22;
						else if (g == 5) C[k].P[g] = 2.0 / 22;
						else C[k].P[g] = 1.0/22;
					}
				}
				else if (i == 0 && j == 4) {
					for (g = 0; g < 11; g++)
					{
						if (g == 4) C[k].P[g] = 2.0 / 22;
						else if (g == 9) C[k].P[g] = 6.0 / 22;
						else if (g == 7) C[k].P[g] = 3.0 / 22;
						else if (g == 3) C[k].P[g] = 2.0 / 22;
						else if (g == 8) C[k].P[g] = 2.0 / 22;
						else if (g == 10)C[k].P[g] = 2.0 / 22;
						else C[k].P[g] = 1.0/22;
					}
				}
				else if (i == 1 && j == 0) {
					for (g = 0; g < 11; g++)
					{
						if (g == 7) C[k].P[g] = 3.0 / 22;
						else if (g == 9) C[k].P[g] = 5.0 / 22;
						else if (g == 10) C[k].P[g] = 3.0 / 22;
						else if (g == 6) C[k].P[g] = 2.0 / 22;
						else if (g == 3) C[k].P[g] = 2.0 / 22;
						else if (g == 4) C[k].P[g] = 2.0 / 22;
						else C[k].P[g] = 1.0/22;
					}
				}
				else if (i == 1 && j == 1) {
					for (g = 0; g < 11; g++)
					{
						if (g == 8) C[k].P[g] = 2.0 / 22;
						else if (g == 9) C[k].P[g] = 6.0 / 22;
						else if (g == 2) C[k].P[g] = 2.0 / 22;
						else if (g == 7) C[k].P[g] = 2.0 / 22;
						else if (g == 6) C[k].P[g] = 2.0 / 22;
						else if (g == 5) C[k].P[g] = 2.0 / 22;
						else if (g == 10) C[k].P[g] = 2.0 / 22;
						else C[k].P[g] = 1.0/22;
					}
				}
				else if (i == 1 && j == 2) {
					for (g = 0; g < 11; g++)
					{
						if (g == 2) C[k].P[g] = 3.0 / 22;
						else if (g == 3) C[k].P[g] = 5.0 / 22;
						else if (g == 6) C[k].P[g] = 4.0 / 22;
						else if (g == 5) C[k].P[g] = 2.0 / 22;
						else if (g == 8) C[k].P[g] = 2.0 / 22;
						else C[k].P[g] = 1.0/22;
					}
				}
				else if (i == 1 && j == 3) {
					for (g = 0; g < 11; g++)
					{
						if (g == 8) C[k].P[g] = 4.0 / 22;
						else if (g == 9) C[k].P[g] = 3.0 / 22;
						else if (g == 10) C[k].P[g] = 2.0 / 22;
						else if (g == 7) C[k].P[g] = 2.0 / 22;
						else if (g == 6) C[k].P[g] = 2.0 / 22;
						else if (g == 5) C[k].P[g] = 2.0 / 22;
						else if (g == 3) C[k].P[g] = 3.0 / 22;
						else C[k].P[g] = 1.0/22;
					}
				}
				else if (i == 1 && j == 4) {
					for (g = 0; g < 11; g++)
					{
						if (g == 1) C[k].P[g] = 4.0 / 22;
						else if (g == 0) C[k].P[g] = 2.0 / 22;
						else if (g == 9) C[k].P[g] = 3.0 / 22;
						else if (g == 3) C[k].P[g] = 3.0 / 22;
						else if (g == 5) C[k].P[g] = 3.0 / 22;
						else if (g == 10) C[k].P[g] = 2.0 / 22;
						else C[k].P[g] = 1.0/22;
					}
				}
				else if (i == 2 && j == 0) {
					for (g = 0; g < 11&&g!=9; g++)
					{
						if (g == 4) C[k].P[g] = 4.0 / 21;
						else if (g == 6) C[k].P[g] = 4.0 / 21;
						else if (g == 5) C[k].P[g] = 4.0 / 21;
						else if (g == 3) C[k].P[g] = 3.0 / 21;
						else C[k].P[g] = 1.0/21;
					}
				}
				else if (i == 2 && j == 2) {
					for (g = 0; g < 11 && g != 9; g++)
					{
						if (g == 5) C[k].P[g] = 3.0 / 21;
						else if (g == 8) C[k].P[g] = 5.0 / 21;
						else if (g == 7) C[k].P[g] = 3.0 / 21;
						else if (g == 6) C[k].P[g] = 3.0 / 21;
						else if (g == 10) C[k].P[g] = 2.0 / 21;
						else C[k].P[g] = 1.0/21;
					}
				}
				else if (i == 2 && j == 4) {
					for (g = 0; g < 11 && g != 9; g++)
					{
						if (g == 0) C[k].P[g] = 2.0 / 21;
						else if (g == 1) C[k].P[g] = 2.0 / 21;
						else if (g == 6) C[k].P[g] = 3.0 / 21;
						else if (g == 7) C[k].P[g] = 4.0 / 21;
						else if (g == 10) C[k].P[g] = 3.0 / 21;
						else if (g == 5) C[k].P[g] = 2.0 / 21;
						else if (g == 4) C[k].P[g] = 2.0 / 21;
						else C[k].P[g] = 1.0/21;
					}
				}
				else if (i == 3 && j == 0) {
					for (g = 0; g < 11 && g != 9; g++)
					{
						if (g == 0) C[k].P[g] = 2.0 / 21;
						else if (g == 2) C[k].P[g] = 4.0 / 21;
						else if (g == 4) C[k].P[g] = 2.0 / 21;
						else if (g == 6) C[k].P[g] = 3.0 / 21;
						else if (g == 3) C[k].P[g] = 2.0 / 21;
						else if (g == 8) C[k].P[g] = 2.0 / 21;
						else if (g == 5) C[k].P[g] = 2.0 / 21;
						else if (g == 7) C[k].P[g] = 2.0 / 21;
						else C[k].P[g] = 1.0/21;
					}
				}
				else if (i == 3 && j == 1) {
					for (g = 0; g < 11 && g != 9; g++)
					{
						if (g == 1) C[k].P[g] = 2.0 / 21;
						else if (g == 4) C[k].P[g] = 2.0 / 21;
						else if (g == 5) C[k].P[g] = 2.0 / 21;
						else if (g == 6) C[k].P[g] = 3.0 / 21;
						else if (g == 8) C[k].P[g] = 3.0 / 21;
						else if (g == 10) C[k].P[g] = 5.0 / 21;
						else C[k].P[g] = 1.0/21;
					}
				}
				else if (i == 3 && j == 3) {
					for (g = 0; g < 11 && g != 9; g++)
					{
						if (g == 3) C[k].P[g] = 2.0 / 21;
						else if (g == 5) C[k].P[g] = 4.0 / 21;
						else if (g == 6) C[k].P[g] = 2.0 / 21;
						else if (g == 7) C[k].P[g] = 3.0 / 21;
						else if (g == 8) C[k].P[g] = 2.0 / 21;
						else if (g == 10) C[k].P[g] = 4.0 / 21;
						else C[k].P[g] = 1.0 / 21;
					}
				}
				else if (i == 3 && j == 4) {
					for (g = 0; g < 11 && g != 9; g++)
					{
						if (g == 0) C[k].P[g] = 3.0 / 21;
						else if (g == 2) C[k].P[g] = 4.0 / 21;
						else if (g == 3) C[k].P[g] = 2.0 / 21;
						else if (g == 4) C[k].P[g] = 5.0 / 21;
						else if (g == 10) C[k].P[g] = 2.0 / 21;
						else C[k].P[g] = 1.0/21;
					}
				}
				else if (i == 4 && j == 0) {
					for (g = 0; g < 11 && g != 9; g++)
					{
						if (g == 0) C[k].P[g] = 3.0 / 21;
						else if (g == 1) C[k].P[g] = 3.0 / 21;
						else if (g == 3) C[k].P[g] = 3.0 / 21;
						else if (g == 4) C[k].P[g] = 2.0 / 21;
						else if (g == 7) C[k].P[g] = 2.0 / 21;
						else if (g == 10) C[k].P[g] = 4.0 / 21;
						else C[k].P[g] = 1.0/21;
					}
				}
				else if (i == 4 && j == 2) {
					for (g = 0; g < 11 && g != 9; g++) {
						if (g == 6) C[k].P[g] = 6.0 / 21;
						else if (g == 8) C[k].P[g] = 6.0 / 21;
						else if (g == 10) C[k].P[g] = 2.0 / 21;
						else C[k].P[g] = 1.0/21;
					}
				}
				else if (i == 4 && j == 4) {
					for (g = 0; g < 11 && g != 9; g++)
					{
						if (g == 0) C[k].P[g] = 2.0 / 21;
						else if (g == 2) C[k].P[g] = 5.0 / 21;
						else if (g == 3) C[k].P[g] = 2.0 / 21;
						else if (g == 4) C[k].P[g] = 3.0 / 21;
						else if (g == 5) C[k].P[g] = 2.0 / 21;
						else if (g == 6) C[k].P[g] = 2.0 / 21;
						else if (g == 10) C[k].P[g] = 2.0 /21;
						else C[k].P[g] = 1.0/21;
					}
				}
				else if (i == 5 && j == 0) {
					for (g = 0; g < 11 && g != 9; g++)
					{
						if (g == 0) C[k].P[g] = 2.0 / 21;
						else if (g == 2) C[k].P[g] = 5.0 / 21;
						else if (g == 4) C[k].P[g] = 4.0 / 21;
						else if (g == 5) C[k].P[g] = 2.0 / 21;
						else if (g == 6) C[k].P[g] = 3.0 / 21;
						else C[k].P[g] = 1.0/21;
					}
				}
				else if (i == 5 && j == 1) {
					for (g = 0; g < 11 && g != 9; g++)
					{
						if (g == 2) C[k].P[g] = 2.0 / 21;
						else if (g == 3) C[k].P[g] = 2.0 / 21;
						else if (g == 5) C[k].P[g] = 2.0 / 21;
						else if (g == 7) C[k].P[g] = 5.0 / 21;
						else if (g == 8) C[k].P[g] = 5.0 / 21;
						else C[k].P[g] = 1.0/21;
					}
				}
				else if (i == 5 && j == 2) {
					for (g = 0; g < 11 && g != 9; g++)
					{
						if (g == 0) C[k].P[g] = 2.0 / 21;
						else if (g == 1) C[k].P[g] = 4.0 / 21;
						else if (g == 3) C[k].P[g] = 2.0 / 21;
						else if (g == 4) C[k].P[g] = 3.0 / 21;
						else if (g == 6) C[k].P[g] = 3.0 / 21;
						else if (g == 8) C[k].P[g] = 3.0 / 21;
						else C[k].P[g] = 1.0 / 21;
					}
				}
				else if (i == 5 && j == 3) {
					for (g = 0; g < 11 && g != 9; g++)
					{
						if (g == 0) C[k].P[g] = 2.0 / 21;
						else if (g == 3) C[k].P[g] = 2.0 / 21;
						else if (g == 6) C[k].P[g] = 2.0 / 21;
						else if (g == 7) C[k].P[g] = 3.0 / 21;
						else if (g == 8) C[k].P[g] = 7.0 / 21;
						else C[k].P[g] = 1.0 / 21;
					}
				}
				else if (i == 5 && j == 4) {
					for (g = 0; g < 11 && g != 9; g++)
					{
						if (g == 1) C[k].P[g] = 2.0 / 21;
						else if (g == 2) C[k].P[g] = 5.0 / 21;
						else if (g == 4) C[k].P[g] = 3.0 / 21;
						else if (g == 5) C[k].P[g] = 2.0 / 21;
						else if (g == 6) C[k].P[g] = 4.0 / 21;
						else C[k].P[g] = 1.0/21;
					}
				}
				k++;
			}
		}
		/*
		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 12; j++) {
				std::cout << C[i].P[j] << "  ";
			}
			std::cout << std::endl;
		}
		*/
	Assume(C, CurMap);
}

/*
*刷新概率
*/
void Probability::FreshChance(char CMap[][5], char CInMessage[], char COutMessage[], Chance *C)
{
	int i;
	int m[12];
	double sum = 0;
	int static flag = 0;
	ChessMove move;
	if (CInMessage[0] == 'G')//对方行棋完毕，裁判传来行棋结果
	{

		move.setFX(CInMessage[3] - 'A');
		move.setFY(CInMessage[4] - '0');
		move.setTX(CInMessage[5] - 'A');
		move.setTY(CInMessage[6] - '0');
		i = SerchChess(C, move.fx, move.fy);//获得对方移动棋子的概率表号
		C[i].P[9] = 0;
		if (CInMessage[10] != '0')			//对方司令被杀，军旗位置暴露
		{
			if (flag == 0)
			{
				int flagy = CInMessage[11] - '0';//对方军旗纵坐标位置
				KillCommander(C, flagy, i);
				flag = 1;
			}

		}
		if (CInMessage[8] == '3')					//对方仅行棋没有碰子,则此棋子肯定不是地雷，CInMessage[8]为行棋结果，0为己方行棋后被对方棋子吃掉，1为吃掉对方棋子，2为对死，3为仅移动；
		{
			CoordinateChange(C, 3, move, 0, i);		//刷新概率表中的棋子坐标
			/*
			for (int j = 0; j < 12; j++)
			{
				if (j == 9)							//將地雷概率設為0，其他均分（此处感觉有错，军旗只能放在大本营）
					m[j] = 0;
				else
					m[j] = 1;
				sum += m[j] * C[i].P[j];
			}
			for (int j = 0; j < 12; j++)
				C[i].P[j] = m[j] * C[i].P[j] / sum;	//这里是均分概率？是否有错
		}
		*/
		}
		else if (CInMessage[8] == '1')				//如果发生拼杀对方获胜
		{
			CoordinateChange(C, 1, move, 0, i);		//刷新概率表中的棋子坐标
			if (CMap[move.tx][move.ty] == 'J')		//如果我方是地雷，则对方一定是工兵(如果我方是地雷，说明该位置一定是最后两排，就不用另外判断是否在最后两排)
				for (int j = 0; j < 12; j++)
				{
					if (j == 8) C[i].P[j] = 1.0;
					else C[i].P[j] = 0.0;
				}
			else if (CMap[move.tx][move.ty] == 'B')	//如果我方是军长，则对方一定是司令，而且对方其他棋子一定不是司令
			{
				for (int j = 0; j < 12; j++)
				{
					if (j == 0)
						C[i].P[j] = 1;				//这个棋子一定是对方司令，那么概率设为1
					else
						C[i].P[j] = 0;				//其他棋子概率设为0
				}
				/*
				for (int o = 0; o < 25; o++)			//更新其他概率表的概率
				{
					if (o != i)
					{
						for (int j = 0; j < 12; j++)
						{
							if (j == 0)				//对方司令已经暴露，所以此棋子为对方司令的概率为零
								m[j] = 0;
							else
								m[j] = 1;
							sum += m[j] * C[i].P[j];
						}
						for (int j = 0; j < 12; j++)
							C[i].P[j] = m[j] * C[i].P[j] / sum;//这个这样算有什么意义？
					}
				}*/
				for (int o = 0; o < 25; o++) 
				{
					if (o != i) 
					{
						for (int j = 0; j < 12; j++) 
						{
							if (j == 0) C[o].P[j] = 0;
						}
					}
				}
			}
			
			else
			{
				for (int j = 0; j < 12; j++)
				{
					if (j < (CMap[move.tx][move.ty] - 'A'))//级别比我方大的棋子，级别是由A往后递减
						m[j] = 1;
					else
						m[j] = 0;						//级别比我方小的棋子，概率变成0
					sum += (m[j]^1) * C[i].P[j];
					C[i].P[j] = m[j] * C[i].P[j];
				}
				for (int j = 0; j < 12; j++)
					C[i].P[j]+=  (m[j]*sum/ (CMap[move.tx][move.ty] - 'A'+1));
			}
		}
		else if (CInMessage[8] == '0')//如果发生拼杀时我方获胜
		{
			CoordinateChange(C, 0, move, 0, i);//刷新概率表中的棋子坐标
			if (CMap[move.tx][move.ty] == 'J')//如果我方是地雷则对方一定不可能工兵
			{
				for (int j = 0; j < 8; j++)
				{
					sum += C[i].P[j];
				}
				double item= C[i].P[8];
				C[i].P[8] = 0;
				for (int j = 0; j < 8; j++) {
					C[i].P[j] = C[i].P[j] / sum;
					C[i].P[j] += item / 8;
				}
			}
			else
			{
				for (int j = 0; j < 12; j++)
				{
					if (j > (CMap[move.tx][move.ty] - 'A') && j < 9)//级别比我方小且不是地雷、炸弹、军旗的概率
						m[j] = 1;
					else
						m[j] = 0;
					sum += (m[j] ^ 1) * C[i].P[j];
					C[i].P[j] = m[j] * C[i].P[j];
				}
				for (int j = 0; j < 12; j++)
					C[i].P[j] +=( m[j] * sum / (8-(CMap[move.tx][move.ty] - 'A' )));
			}
		}
		else//同归于尽
		{
			CoordinateChange(C, 2, move, 0, i);//刷新概率表中的棋子坐标
			if (CMap[move.tx][move.ty] != 'K')//如果我方不是炸弹
			{
				for (int j = 0; j < 12; j++)
				{
					if (j == (CMap[move.tx][move.ty] - 'A') || j == 10)//级别与我方相同，或炸弹的概率
						C[i].P[j] = 0.5;
					else
						C[i].P[j] = 0;
				}
			}

		}
		//如果有转弯，则对方棋子一定是工兵
		if ((move.fx == 5 || move.fx == 1 || move.fx == 6 || move.fx == 10 || move.fy == 0 || move.fy == 4) &&
			(move.tx == 5 || move.tx == 1 || move.tx == 6 || move.tx == 10 || move.ty == 0 || move.ty == 4) &&
			move.fx != move.tx&&move.fy != move.ty)
		{
			for (int j = 0; j < 12; j++)
			{
				if (j == 8) C[i].P[j] = 1.0;
				else C[i].P[j] = 0.0;
			}
		}
	}
	else if (CInMessage[0] == 'R')//机器方行棋后得知结果
	{
		move.setFX(COutMessage[9] - 'A');
		move.setFY(COutMessage[10] - '0');
		move.setTX(COutMessage[11] - 'A');
		move.setTY(COutMessage[12] - '0');
		i = SerchChess(C, move.tx, move.ty);//获得对方棋子的概率表号
		if (CInMessage[9] != '0')//我方殺掉對方司令
		{
			if (flag == 0)
			{
				int flagy = CInMessage[10] - '0';//对方军旗纵坐标位置
				KillCommander(C, flagy, i);
				flag = 1;
			}

		}
		if (CInMessage[7] == '1')//机器方获胜
		{
			CoordinateChange(C, 1, move, 1, i);//刷新概率表中的棋子坐标
			if (CMap[move.fx][move.fy] == 'I')//如果我方是工兵，则对方一定是地雷
			{
				if (move.tx == 0 && move.ty % 2 == 1)//大本营
				{
					for (int j = 0; j < 12; j++)
					{
						if (j == 11) C[i].P[j] = 1.0;//军旗概率为1？那是不是该赢了
						else C[i].P[j] = 0.0;
					}
				}
				else
				{
					for (int j = 0; j < 12; j++)
					{
						if (j == 9) C[i].P[j] = 1.0;
						else C[i].P[j] = 0.0;
					}
				}
			}
			else //如果我方不是工兵，则对方级别比我方小且不是地雷、炸弹、军旗
			{
				if (move.tx == 0 && move.ty % 2 == 1)//大本营吃掉可能是军旗的棋子游戏还没有结束，说明该位置棋子一定不是军旗，另一位置一定是军旗
				{
					//改变军旗周围棋子概率及军旗概率
					int flagy = 4 - move.ty;//对方军旗纵坐标位置
					ChangeArmyAround(C, flagy, i);
				}
				else
				{
					for (int j = 0; j < 12; j++)
					{
						if (j > (CMap[move.fx][move.fy] - 'A') && j < 9)//级别比我方小且不是地雷、炸弹、军旗的概率
							m[j] = 1;
						else
							m[j] = 0;
						sum += (m[j] ^ 1) * C[i].P[j];
						C[i].P[j] = m[j] * C[i].P[j];
					}
					for (int j = 0; j < 12; j++)
						C[i].P[j] += (m[j] * sum / (8 - (CMap[move.fx][move.fy] - 'A')));
				}
			}
		}
		else if (CInMessage[7] == '0')//对方获胜
		{
			CoordinateChange(C, 0, move, 1, i);//刷新概率表中的棋子坐标
			if (CMap[move.fx][move.fy] == 'I')//如果我方是工兵，对方棋子级别比我方大
			{
				for (int j = 0; j < 12; j++)
				{
					if (j < CMap[move.fx][move.fy] - 'A')
						m[j] = 1;
					else m[j] = 0;
					sum += m[j] * C[i].P[j];
				}
				for (int j = 0; j < 12; j++)
					C[i].P[j] = m[j] * C[i].P[j] / sum;
			}
			else if (CMap[move.fx][move.fy] == 'A')//如果我方是司令，则对方一定是地雷
			{
				for (int j = 0; j < 12; j++)
				{
					if (j == 9) C[i].P[j] = 1.0;
					else C[i].P[j] = 0.0;
				}
			}
			else if (move.tx < 2)//如果我方不是工兵，且棋子落点在对方兵界的最后两排，则对方棋子级别可能比我方大，也可能是地雷
			{
				for (int j = 0; j < 12; j++)
				{
					if (j < CMap[move.fx][move.fy] - 'A' || j == 9)
						m[j] = 1;
					else m[j] = 0;
					sum += (m[j] ^ 1) * C[i].P[j];
					C[i].P[j] = m[j] * C[i].P[j];
				}
				for (int j = 0; j < 12; j++)
					C[i].P[j] += (m[j] * sum / (CMap[move.fx][move.fy] - 'A' + 2));
			}
			else //如果我方不是士兵，且落点不在对方兵界的最后两排，则对方棋子级别比我方大
			{
				for (int j = 0; j < 12; j++)
				{
					if (j < CMap[move.fx][move.fy] - 'A')
						m[j] = 1;
					else m[j] = 0;
					sum += (m[j] ^ 1) * C[i].P[j];
					C[i].P[j] = m[j] * C[i].P[j];
				}
				for (int j = 0; j < 12; j++)
					C[i].P[j] += (m[j] * sum / (CMap[move.fx][move.fy] - 'A' + 1));
			}

		}
		else if (CInMessage[7] == '2')//如果双方棋子同归于尽
		{
			CoordinateChange(C, 2, move, 1, i);//刷新概率表中的棋子坐标
			if (CMap[move.fx][move.fy] != 'K')//如果我方棋子不是炸弹
			{
				for (int j = 0; j < 12; j++)
				{
					if (j == CMap[move.fx][move.fy] - 'A' || j == 10)//对方是炸弹或者与我方棋子同级别
						C[i].P[j] = 0.5;
					else C[i].P[j] = 0;
				}
			}
		}

	}
	Assume(C, CMap);
}

int Probability::SerchChess(Chance C[], int x, int y)
{
	int m = 12;
	for (int i = 0; i < 25; i++)				//共有25个棋子，遍历所有棋子，取出当前棋子的概率表
		if (C[i].x == x&&C[i].y == y)
		{
			m = i;
			break;
		}
	return m;
}

void Probability::CoordinateChange(Chance *C, int result, ChessMove move, int mychess, int i)
{
	if (mychess == 0)					//如果是对方行棋
	{
		if (result == 2 || result == 0)//如果是我方胜，或者同归于尽
		{
			C[i].x = 13;			//将对方棋子放到棋盘外
			C[i].alive = 0;
			C[i].assume = '0';
		}
		else					//如果是对方胜或者无拼杀
		{
			C[i].x = move.tx;
			C[i].y = move.ty;		//将对方棋子坐标移到落点

		}
	}
	else//如果是我方行棋		
	{
		if (result == 2 || result == 1)//如果是我方胜，或者同归于尽
		{
			C[i].x = 13;			//将对方棋子放到棋盘外
			C[i].alive = 0;
			C[i].assume = '0';
		}
	}


}
/*将抽样值存储在概率表中*/
void Probability::Assume(Chance *C, char CMap[][5])
{
	double max = -1000.0;
	int g = 0;
	for (int i = 0; i < 25; i++)
	{
		if (C[i].alive == 0)
			C[i].assume = '0';
		else
		{
			for (int j = 0; j < 12; j++)
			{
				if (C[i].P[j] >= max)	//寻找概率最大的类型
				{
					max = C[i].P[j];	//将概率存储起来
					g = j;				//将概率最大的类型数值存储起来
				}
			}
			C[i].assume = (char)(g + 'a');//将数字转换为字符，假定值就是当前棋子最有可能的棋种
			max = -1000.0;
			g = 0;
		}
	}
}

/*将概率表中的抽样信息付给棋盘*/
void Probability::FreshAssume(Chance *C, char CMap[][5])
{
	for (int i = 0; i < 25; i++)
		if (C[i].alive == 1)
			CMap[C[i].x][C[i].y] = C[i].assume;

}

void Probability::KillCommander(Chance *C, int flagy, int i)
{
	//改变军旗周围棋子概率及军旗概率
	ChangeArmyAround(C, flagy, i);
	//将对方司令棋子放置到棋盘外，并改变相应棋子概率
	C[i].x = 13;
	C[i].alive = 0;
	C[i].assume = '0';
	for (int t = 0; t < 25; t++)
		for (int j = 0; j < 12; j++)
		{
			if (t == i)//改变司令棋子概率
			{
				if (j == 0)
					C[t].P[j] = 1;
				else
					C[t].P[j] = 0;
			}
			else//改变其他棋子概率
			{
				if (j == 0)
					C[t].P[j] = 0;
				else
					C[t].P[j] += (C[t].P[0]) / 11;
			}

		}
}
/*改变军旗周围棋子概率及军旗概率*/
void Probability::ChangeArmyAround(Chance *C, int flagy, int i)
{
	int i00 = 0;
	int i10 = 0;
	int i11 = 0;
	int i12 = 0;
	int i02 = 0;
	int i04 = 0;
	int i13 = 0;
	int i14 = 0;
	i00 = SerchChess(C, 0, 0);
	i02 = SerchChess(C, 0, 2);
	i04 = SerchChess(C, 0, 4);
	i10 = SerchChess(C, 1, 0);
	i11 = SerchChess(C, 1, 1);
	i12 = SerchChess(C, 1, 2);
	i13 = SerchChess(C, 1, 3);
	i14 = SerchChess(C, 1, 4);

	if (C[1].y == flagy)//如果第一个是军旗，则其军旗概率相应改变，另一个位置的军旗概率相应变为0
	{
		for (int j = 0; j < 12; j++)
		{
			if (j == 11)//该位置军旗概率设置为1，另一位置概率设为0
			{
				C[1].P[j] = 1;
				C[3].P[j] = 0;
				C[3].P[7] = 1;
				C[1].P[7] = 0;
			}
			else if (j == 9)//该位置周围地雷概率增大，另一位置周围地雷概率减小
			{
				C[i00].P[j] = 2 * C[i00].P[j];//*2即增大概率
				C[i02].P[j] = 2 * C[i02].P[j];
				C[i04].P[j] = 0.5*C[i04].P[j];//*0.5即减小概率
				C[i10].P[j] = 2 * C[i10].P[j];
				C[i11].P[j] = 2 * C[i11].P[j];
				C[i12].P[j] = 2 * C[i12].P[j];
				C[i13].P[j] = 0.5*C[i13].P[j];
				C[i14].P[j] = 0.5*C[i14].P[j];

			}
			else//该位置其他棋子概率为1，另一位置其他棋子概率均分
			{
				//军旗周围棋子地雷概率增大，其他棋子地雷概率减小(待修正)
				C[i00].P[j] = 0.5*C[i00].P[j];
				C[i02].P[j] = 0.5*C[i02].P[j];
				C[i04].P[j] = 2 * C[i04].P[j];
				C[i10].P[j] = 0.5*C[i10].P[j];
				C[i11].P[j] = 0.5*C[i11].P[j];
				C[i12].P[j] = 0.5*C[i12].P[j];
				C[i13].P[j] = 2 * C[i13].P[j];
				C[i14].P[j] = 2 * C[i14].P[j];
			}

		}
	}
	else if (C[3].y == flagy)//如果第一个是军旗，则其军旗概率相应改变，另一个位置的军旗概率相应变为0
	{
		for (int j = 0; j < 12; j++)
		{
			if (j == 11)
			{
				C[3].P[j] = 1;//该位置军旗概率设置为1，另一位置概率设为0
				C[1].P[j] = 0;
				C[3].P[7] = 0;
				C[1].P[7] = 1;
			}
			else if (j == 9)//该位置周围地雷概率增大，另一位置周围地雷概率减小
			{
				C[i00].P[j] = 0.5*C[i00].P[j];
				C[i02].P[j] = 2 * C[i02].P[j];
				C[i04].P[j] = 2 * C[i04].P[j];
				C[i10].P[j] = 0.5*C[i10].P[j];
				C[i11].P[j] = 0.5*C[i11].P[j];
				C[i12].P[j] = 2 * C[i12].P[j];
				C[i13].P[j] = 2 * C[i13].P[j];
				C[i14].P[j] = 2 * C[i14].P[j];

			}
			else
			{
				//军旗周围棋子地雷概率增大，其他棋子地雷概率减小
				C[i00].P[j] = 2 * C[i00].P[j];
				C[i02].P[j] = 0.5*C[i02].P[j];
				C[i04].P[j] = 0.5*C[i04].P[j];
				C[i10].P[j] = 2 * C[i10].P[j];
				C[i11].P[j] = 2 * C[i11].P[j];
				C[i12].P[j] = 0.5*C[i12].P[j];
				C[i13].P[j] = 0.5*C[i13].P[j];
				C[i14].P[j] = 0.5*C[i14].P[j];
			}
		}
	}

}

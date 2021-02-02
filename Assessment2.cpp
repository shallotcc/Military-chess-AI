#if !defined(AFX_SEARCHENGINE_H__9A34849F_1C51_4AFD_A9EF_8F7BB22913F6__INCLUDED_)
#define AFX_SEARCHENGINE_H__9A34849F_1C51_4AFD_A9EF_8F7BB22913F6__INCLUDED_


#include"Assessment2.h"



double Assessment2::ChessScore(char CurMap[12][5], Vector(*CurVector)[5], Chance CurC[25], int ismine) {
	double minescore = 0, enemyscore = 0;//双方得分
	int minecount = 0, enemycount = 0;//双方棋子数量
	for (int i=0;i<12;i++)
		for (int j = 0; j < 5; j++)
		{
			if (CurMap[i][j] >= 'a'&&CurMap[i][j] <= 'k') enemycount++;
			else if (CurMap[i][j] >= 'A'&&CurMap[i][j] <= 'K')minecount++;
			if (CurMap[i][j] == 'A')minescore += Cscore[0];
			else if (CurMap[i][j] == 'A')minescore += Cscore[0];
			else if (CurMap[i][j] == 'B')minescore += Cscore[1];
			else if (CurMap[i][j] == 'C')minescore += Cscore[2];
			else if (CurMap[i][j] == 'D')minescore += Cscore[3];
			else if (CurMap[i][j] == 'E')minescore += Cscore[4];
			else if (CurMap[i][j] == 'F')minescore += Cscore[5];
			else if (CurMap[i][j] == 'G')minescore += Cscore[6];
			else if (CurMap[i][j] == 'H')minescore += Cscore[7];
			else if (CurMap[i][j] == 'I')minescore += Cscore[8];
			else if (CurMap[i][j] == 'J')minescore += Cscore[9];
			else if (CurMap[i][j] == 'K')minescore += Cscore[10];
			else if (CurMap[i][j] == 'L')minescore += Cscore[11];
		}
	for (int i = 0; i < 25; i++)
	{
		if (CurC[i].alive == 1)
		for (int j = 0; j < 12; j++)
		{
			enemyscore += Cscore[j] * CurC[i].P[j];
		}
	}
	enemyscore += enemycount * 30;
	minescore += minecount * 30;
	if (ismine) return enemyscore - minescore;
	else return minescore - enemyscore;
}
double Assessment2::PlaceScore(char CurMap[12][5], Vector(*CurVector)[5], Chance CurC[25], int ismine) {

	double minescore = 0, enemyscore = 0;//双方得分
	int myflagdefence1 = 0, myflagdefence2 = 0;
		if (CurMap[11][1] == 'L')//军旗位置
		{
			if (CurMap[9][1] >= 'A'&&CurMap[9][1] <= 'K')minescore += 10;
			else if (CurMap[9][1] >= 'a'&&CurMap[9][1] <= 'k')enemyscore += 10;
			if (CurMap[11][0] >= 'a'&&CurMap[11][0] <= 'k')enemyscore += 98888;
			if (CurMap[0][0] >= 'A'&&CurMap[0][0] <= 'K')minescore += 98888;
			for (int i = 6; i < 11; i++) {
				if (CurMap[i][0] <= 'K'&&CurMap[i][0] >= 'A')myflagdefence1 = 1;
				if (CurMap[i][4] <= 'K'&&CurMap[i][4] >= 'A')myflagdefence2 = 1;
			}
			if (!myflagdefence1) minescore -= 8;
			if (!myflagdefence2) minescore -= 8;
		}
		else if (CurMap[11][3] == 'L')//军旗位置
		{
			if (CurMap[9][3] >= 'A'&&CurMap[9][3] <= 'K')minescore += 10;
			else if (CurMap[9][3] >= 'a'&&CurMap[9][3] <= 'k')enemyscore += 10;
			if (CurMap[11][4] >= 'a'&&CurMap[11][4] <= 'k')enemyscore += 98888;
			for (int i = 6; i < 11; i++) {
				if (CurMap[i][4] <= 'K'&&CurMap[i][4] >= 'A')myflagdefence2 = 1;
				if (CurMap[i][0] <= 'K'&&CurMap[i][0] >= 'A')myflagdefence1 = 1;
			}
			if (!myflagdefence1) minescore -= 8;
			if (!myflagdefence2) minescore -= 8;
		}
		int flagdefence1 = 0, flagdefence2 = 0;
		if (CurC[1].P[11] >0.5)//(0,1)为军旗
		{
			if (CurMap[2][1] >= 'A'&&CurMap[2][1] <= 'K')minescore += 10;
			else if (CurMap[2][1] >= 'a'&&CurMap[2][1] <= 'k')enemyscore += 10;
			if (CurMap[0][0] >= 'A'&&CurMap[0][0] <= 'K')minescore += 98888;
			for (int i = 1; i < 6; i++) {
				if (CurMap[i][0] <= 'k'&&CurMap[i][0] >= 'a')flagdefence1 = 1;
				if (CurMap[i][4] <= 'k'&&CurMap[i][4] >= 'a')flagdefence2 = 1;
			}
			if (!flagdefence1) enemyscore -= 8;
			if (!flagdefence2) enemyscore -= 8;
		}
		else if (CurC[3].P[11] >0.5)//(0,3)为军旗
		{
			if (CurMap[2][3] >= 'A'&&CurMap[2][3] <= 'K')minescore += 10;
			else if (CurMap[2][3] >= 'a'&&CurMap[2][3] <= 'k')enemyscore += 10;
			if (CurMap[0][3] >= 'A'&&CurMap[0][3] <= 'K')minescore += 98888;
			for (int i = 1; i < 6; i++) {
				if (CurMap[i][4] <= 'k'&&CurMap[i][4] >= 'a')flagdefence2 = 1;
				if (CurMap[i][0] <= 'k'&&CurMap[i][0] >= 'a')flagdefence1 = 1;
			}
			if (!flagdefence1) enemyscore -= 8;
			if (!flagdefence2) enemyscore -= 8;
		}
		for(int i=2;i<10;i++)
			for (int j = 1; j < 4; j++)
			{
				if (5 * i + j == 11 || 5 * i + j == 13 || 5 * i + j == 17 || 5 * i + j == 21 ||
					5 * i + j == 23 || 5 * i + j == 36 || 5 * i + j == 38 || 5 * i + j == 42 ||
					5 * i + j == 46 || 5 * i + j == 48)
				{
					if (CurMap[i][j] <= 'L'&&CurMap[i][j] >= 'A')minescore += 5;
					else if (CurMap[i][j] <= 'l'&&CurMap[i][j] >= 'a')enemyscore += 5;
				}
			}
		

		
	if (ismine) return enemyscore - minescore;
	else return minescore - enemyscore;
}
double Assessment2::DefenceScore(char NowMap[12][5], Vector(*NowVector)[5], Chance NowC[25], int ismine) {
	double minescore = 0, enemyscore = 0;//双方得分
	if (ismine) return enemyscore - minescore;
	else return minescore - enemyscore;
}

Assessment2::Assessment2()
{
}

Assessment2::~Assessment2()
{
}







void Assessment2::Place(ChessMove p, char CMap[][5])
{
	int i, j, m, n;
	i = p.tx;
	j = p.ty;
	//坐标原点在左上角,横向为y轴，纵向为x轴
	if (i * 5 + j == 59)//
	{
		a[i][j] = CMap[i][j];
		a[i - 1][j] = CMap[i - 1][j];//上
		a[i][j - 1] = CMap[i][j - 1];//左
	}
	if (i * 5 + j == 55)//
	{
		a[i][j] = CMap[i][j];
		a[i - 1][j] = CMap[i - 1][j];//上
		a[i][j + 1] = CMap[i][j + 1];//右
	}
	if (i * 5 + j == 0)//
	{
		a[i][j] = CMap[i][j];
		a[i + 1][j] = CMap[i + 1][j];//下
		a[i][j - 1] = CMap[i][j - 1];//左
	}
	if (i * 5 + j == 4)//
	{
		a[i][j] = CMap[i][j];
		a[i][j + 1] = CMap[i][j + 1];//下
		a[i + 1][j] = CMap[i + 1][j];//右
	}
	if (i * 5 + j == 1 || i * 5 + j == 56 || i * 5 + j == 3 || i * 5 + j == 58 || i * 5 + j == 2 || i * 5 + j == 57)
	{
		a[i][j] = CMap[i][j];
		a[i - 1][j] = CMap[i - 1][j];//上
		a[i + 1][j] = CMap[i + 1][j];//右
		a[i][j - 1] = CMap[i][j - 1];//左
	}
	if (i * 5 + j == 16 || i * 5 + j == 41 || i * 5 + j == 12 || i * 5 + j == 22 || i * 5 + j == 37 || i * 5 + j == 47 || i * 5 + j == 18 || i * 5 + j == 43)
	{
		a[i][j] = CMap[i][j];
		a[i - 1][j] = CMap[i - 1][j];//上
		a[i + 1][j] = CMap[i + 1][j];//下
		a[i][j + 1] = CMap[i][j + 1];//右
		a[i][j - 1] = CMap[i][j - 1];//左
	}
	if (i * 5 + j == 6 || i * 5 + j == 8 || i * 5 + j == 51 || i * 5 + j == 53)
	{
		a[i][j] = CMap[i][j];
		a[i - 1][j] = CMap[i - 1][j];//上
		a[i + 1][j] = CMap[i + 1][j];//下

									 //左一排铁路
		for (n = j; n > 0; n--)
		{
			if (CMap[i][n - 1] != '0')
			{
				a[i][n - 1] = CMap[i][n - 1];
				break;
			}
		}
		//右一排铁路
		for (n = j; n < 5; n++)
		{
			if (CMap[i][n] != '0')
			{
				a[i][n + 1] = CMap[i][n + 1];
				break;
			}
		}
	}
	if (i * 5 + j == 10 || i * 5 + j == 20 || i * 5 + j == 35 || i * 5 + j == 45)
	{
		a[i][j] = CMap[i][j];
		a[i][j + 1] = CMap[i][j + 1];//右

									 //上一排铁路
		for (m = i; m > 0; m--)
		{
			if (CMap[m - 1][j] != '0')
			{
				a[m - 1][j] = CMap[m - 1][j];
				break;
			}
		}
		//下一排铁路
		for (m = i; m < 12; m++)
		{
			if (CMap[m + 1][j] != '0')
			{
				a[m + 1][j] = CMap[m + 1][j];
				break;
			}
		}
	}
	if (i * 5 + j == 14 || i * 5 + j == 24 || i * 5 + j == 39 || i * 5 + j == 49)
	{
		a[i][j] = CMap[i][j];
		a[i][j - 1] = CMap[i][j - 1];//左

									 //上一排铁路
		for (m = i; m > 0; m--)
		{
			if (CMap[m - 1][j] != '0')
			{
				a[m - 1][j] = CMap[m - 1][j];
				break;
			}
		}
		//下一排铁路
		for (m = i; m < 12; m++)
		{
			if (CMap[m + 1][j] != '0')
			{
				a[m + 1][j] = CMap[m + 1][j];
				break;
			}
		}
	}
	if (i * 5 + j == 15 || i * 5 + j == 40)
	{
		a[i][j] = CMap[i][j];
		a[i][j + 1] = CMap[i][j + 1];//右
		a[i + 1][j + 1] = CMap[i + 1][j + 1];//下右
		a[i - 1][j + 1] = CMap[i - 1][j + 1];//上右

											 //上一排铁路
		for (m = i; m > 0; m--)
		{
			if (CMap[m - 1][j] != '0')
			{
				a[m - 1][j] = CMap[m - 1][j];
				break;
			}
		}
		//下一排铁路
		for (m = i; m < 12; m++)
		{
			if (CMap[m + 1][j] != '0')
			{
				a[m + 1][j] = CMap[m + 1][j];
				break;
			}
		}
	}
	if (i * 5 + j == 19 || i * 5 + j == 44)
	{
		a[i][j] = CMap[i][j];
		a[i][j - 1] = CMap[i][j - 1];//左
		a[i - 1][j - 1] = CMap[i - 1][j - 1];//上左
		a[i + 1][j - 1] = CMap[i + 1][j - 1];//下左

											 //上一排铁路
		for (m = i; m > 0; m--)
		{
			if (CMap[m - 1][j] != '0')
			{
				a[m - 1][j] = CMap[m - 1][j];
				break;
			}
		}
		//下一排铁路
		for (m = i; m < 12; m++)
		{
			if (CMap[m + 1][j] != '0')
			{
				a[m + 1][j] = CMap[m + 1][j];
				break;
			}
		}
	}
	if (i * 5 + j == 5)
	{
		a[i][j] = CMap[i][j];
		a[i + 1][j + 1] = CMap[i + 1][j + 1];//下右

											 //右一排铁路
		for (n = j; n < 5; n++)
		{
			if (CMap[i][n] != '0')
			{
				a[i][n + 1] = CMap[i][n + 1];
				break;
			}
		}
		//下一排铁路
		for (m = i; m < 12; m++)
		{
			if (CMap[m + 1][j] != '0')
			{
				a[m + 1][j] = CMap[m + 1][j];
				break;
			}
		}
	}
	if (i * 5 + j == 50)
	{
		a[i][j] = CMap[i][j];
		a[i + 1][j] = CMap[i + 1][j];//下
		a[i - 1][j + 1] = CMap[i - 1][j + 1];//上右

											 //右一排铁路
		for (n = j; n<5; n++)
		{
			if (CMap[i][n] != '0')
			{
				a[i][n + 1] = CMap[i][n + 1];
				break;
			}
		}
		//上一排铁路
		for (m = i; m>0; m--)
		{
			if (CMap[m - 1][j] != '0')
			{
				a[m - 1][j] = CMap[m - 1][j];
				break;
			}
		}
	}
	if (i * 5 + j == 9)
	{
		a[i][j] = CMap[i][j];
		a[i - 1][j] = CMap[i - 1][j];//上
		a[i + 1][j - 1] = CMap[i + 1][j - 1];//下左

											 //左一排铁路
		for (n = j; n>0; n--)
		{
			if (CMap[i][n - 1] != '0')
			{
				a[i][n - 1] = CMap[i][n - 1];
				break;
			}
		}
		//下一排铁路
		for (m = i; m<12; m++)
		{
			if (CMap[m + 1][j] != '0')
			{
				a[m + 1][j] = CMap[m + 1][j];
				break;
			}
		}
	}
	if (i * 5 + j == 54)
	{
		a[i][j] = CMap[i][j];
		a[i + 1][j] = CMap[i + 1][j];//下
		a[i - 1][j - 1] = CMap[i - 1][j - 1];//上左

											 //左一排铁路
		for (n = j; n>0; n--)
		{
			if (CMap[i][n - 1] != '0')
			{
				a[i][n - 1] = CMap[i][n - 1];
				break;
			}
		}
		//上一排铁路
		for (m = i; m>0; m--)
		{
			if (CMap[m - 1][j] != '0')
			{
				a[m - 1][j] = CMap[m - 1][j];
				break;
			}
		}
	}
	if (i * 5 + j == 25)
	{
		a[i][j] = CMap[i][j];
		a[i - 1][j + 1] = CMap[i - 1][j + 1];//上右

											 //上一排铁路
		for (m = i; m>0; m--)
		{
			if (CMap[m - 1][j] != '0')
			{
				a[m - 1][j] = CMap[m - 1][j];
				break;
			}
		}
		//下一排铁路
		for (m = i; m<12; m++)
		{
			if (CMap[m + 1][j] != '0')
			{
				a[m + 1][j] = CMap[m + 1][j];
				break;
			}
		}
		//右一排铁路
		for (n = j; n<5; n++)
		{
			if (CMap[i][n] != '0')
			{
				a[i][n + 1] = CMap[i][n + 1];
				break;
			}
		}
	}
	if (i * 5 + j == 30)
	{
		a[i][j] = CMap[i][j];
		a[i + 1][j + 1] = CMap[i + 1][j + 1];//下右

											 //上一排铁路
		for (m = i; m>0; m--)
		{
			if (CMap[m - 1][j] != '0')
			{
				a[m - 1][j] = CMap[m - 1][j];
				break;
			}
		}
		//下一排铁路
		for (m = i; m<12; m++)
		{
			if (CMap[m + 1][j] != '0')
			{
				a[m + 1][j] = CMap[m + 1][j];
				break;
			}
		}
		//右一排铁路
		for (n = j; n<5; n++)
		{
			if (CMap[i][n] != '0')
			{
				a[i][n + 1] = CMap[i][n + 1];
				break;
			}
		}
	}
	if (i * 5 + j == 32 || i * 5 + j == 7)
	{
		a[i][j] = CMap[i][j];
		a[i - 1][j] = CMap[i - 1][j];//上
		a[i + 1][j] = CMap[i + 1][j];//下
		a[i + 1][j + 1] = CMap[i + 1][j + 1];//下右
		a[i + 1][j - 1] = CMap[i + 1][j - 1];//下左

											 //左一排铁路
		for (n = j; n>0; n--)
		{
			if (CMap[i][n - 1] != '0')
			{
				a[i][n - 1] = CMap[i][n - 1];
				break;
			}
		}
		//右一排铁路
		for (n = j; n<5; n++)
		{
			if (CMap[i][n] != '0')
			{
				a[i][n + 1] = CMap[i][n + 1];
				break;
			}
		}
	}
	if (i * 5 + j == 27 || i * 5 + j == 52)
	{
		a[i][j] = CMap[i][j];
		a[i - 1][j] = CMap[i - 1][j];//上
		a[i + 1][j] = CMap[i + 1][j];//下
		a[i - 1][j + 1] = CMap[i - 1][j + 1];//上右
		a[i - 1][j - 1] = CMap[i - 1][j - 1];//上左

											 //左一排铁路
		for (n = j; n>0; n--)
		{
			if (CMap[i][n - 1] != '0')
			{
				a[i][n - 1] = CMap[i][n - 1];
				break;
			}
		}
		//右一排铁路
		for (n = j; n<5; n++)
		{
			if (CMap[i][n] != '0')
			{
				a[i][n + 1] = CMap[i][n + 1];
				break;
			}
		}
	}
	if (i * 5 + j == 29)
	{
		a[i][j] = CMap[i][j];
		a[i - 1][j - 1] = CMap[i - 1][j - 1];//上左

											 //上一排铁路
		for (m = i; m>0; m--)
		{
			if (CMap[m - 1][j] != '0')
			{
				a[m - 1][j] = CMap[m - 1][j];
				break;
			}
		}
		//下一排铁路
		for (m = i; m<12; m++)
		{
			if (CMap[m + 1][j] != '0')
			{
				a[m + 1][j] = CMap[m + 1][j];
				break;
			}
		}
		//左一排铁路
		for (n = j; n>0; n--)
		{
			if (CMap[i][n - 1] != '0')
			{
				a[i][n - 1] = CMap[i][n - 1];
				break;
			}
		}
	}
	if (i * 5 + j == 34)
	{
		a[i][j] = CMap[i][j];
		a[i + 1][j - 1] = CMap[i + 1][j - 1];//下左

											 //上一排铁路
		for (m = i; m>0; m--)
		{
			if (CMap[m - 1][j] != '0')
			{
				a[m - 1][j] = CMap[m - 1][j];
				break;
			}
		}
		//下一排铁路
		for (m = i; m<12; m++)
		{
			if (CMap[m + 1][j] != '0')
			{
				a[m + 1][j] = CMap[m + 1][j];
				break;
			}
		}
		//左一排铁路
		for (n = j; n>0; n--)
		{
			if (CMap[i][n - 1] != '0')
			{
				a[i][n - 1] = CMap[i][n - 1];
				break;
			}
		}
	}
	if (i * 5 + j == 26 || i * 5 + j == 28)
	{
		a[i][j] = CMap[i][j];
		a[i - 1][j] = CMap[i - 1][j];//上

									 //左一排铁路
		for (n = j; n>0; n--)
		{
			if (CMap[i][n - 1] != '0')
			{
				a[i][n - 1] = CMap[i][n - 1];
				break;
			}
		}
		//右一排铁路
		for (n = j; n<5; n++)
		{
			if (CMap[i][n] != '0')
			{
				a[i][n + 1] = CMap[i][n + 1];
				break;
			}
		}
	}
	if (i * 5 + j == 31 || i * 5 + j == 33)
	{
		a[i][j] = CMap[i][j];
		a[i + 1][j] = CMap[i + 1][j];//下

									 //左一排铁路
		for (n = j; n>0; n--)
		{
			if (CMap[i][n - 1] != '0')
			{
				a[i][n - 1] = CMap[i][n - 1];
				break;
			}
		}
		//右一排铁路
		for (n = j; n<5; n++)
		{
			if (CMap[i][n] != '0')
			{
				a[i][n + 1] = CMap[i][n + 1];
				break;
			}
		}
	}
	if (i * 5 + j == 27)
	{
		a[i][j] = CMap[i][j];
		a[i - 1][j] = CMap[i - 1][j];//上
		a[i + 1][j] = CMap[i + 1][j];//下
		a[i - 1][j + 1] = CMap[i - 1][j + 1];//上右
		a[i - 1][j - 1] = CMap[i - 1][j - 1];//上左

											 //左一排铁路
		for (n = j; n>0; n--)
		{
			if (CMap[i][n - 1] != '0')
			{
				a[i][n - 1] = CMap[i][n - 1];
				break;
			}
		}
		//右一排铁路
		for (n = j; n<5; n++)
		{
			if (CMap[i][n] != '0')
			{
				a[i][n + 1] = CMap[i][n + 1];
				break;
			}
		}
	}
}



#endif // !defined(AFX_SEARCHENGINE_H__9A34849F_1C51_4AFD_A9EF_8F7BB22913F6__INCLUDED_)

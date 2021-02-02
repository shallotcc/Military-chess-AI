#include "Assessment.h"
#include "math.h"
#include <iostream>



double Dorje[12][12] =  
{
	//	   司令  军长   师长  旅长  团长   营长   连长   排长   工兵   地雷  炸弹   军棋
/*司令*/ { 0.0,  28.6,  16.6, 11.4, 6.7,   3.9,   2.0,   1.0,   10.0,  6.9,  -20.7, 999},
/*军长*/ {-28.6,  0,    15.2, 11.0, 6.5,   3.8,   1.9,   1.0,   9.0,   6.0,  -17.1, 999},
/*师长*/ {-16.6, -15.2,   0,  10.9, 6.4,   3.7,   1.9,   1.0,   9.0,   5.3,  -16.6, 999},
/*旅长*/ {-11.4, -11.0, -10.9,  0,  5.1,   3.0,   1.5,   0.8,   9.0,   5.6,  -15.4, 999},
/*团长*/ {-6.7,  -6.7,  -6.4, -5.1,  0,    2.9,   1.3,   0.7,   9.0,   7.8,   3.3,  999},
/*营长*/ {-3.9,  -3.8,  -3.7, -3.0, -2.9,   0,    1.3,   0.6,   8.8,   7.7,   6.0,  999},
/*连长*/ {-2.0,  -1.9,  -1.9, -1.5, -1.3,  -1.3,   0,    0.6,   8.0,   7.8,   7.0,  999},
/*排长*/ {-1.0,  -1.0,  -1.0, -0.8, -0.7,  -0.6,  -0.6,   0,    6.1,   7.9,   10.0, 999},
/*工兵*/ {-10.0, -9.0,  -9.0, -9.0, -9.0,  -8.0,  -8.0,  -6.1,   0,    8.0,  -10.0, 999},
/*地雷*/ {-6.9,  -6.0,  -5.3, -7.8, -7.8,  -7.8,  -7.8,  -7.9,  -8.0,   0,     0,   999},
/*炸弹*/ {24.7,  12.1,  0.6,  -9.6, -13.7, -15.7, -17.3, -18.1, -10.0, -17.7,  0,   999},
/*军棋*/ {999,   999,    999,  999,  999,   999,   999,   999,  999,   999,   999,  999}
};

double Assessment::MyGrappleValue(ChessMove p,Chance C[],char CMap[][5])
{
	/*上面传来的是产生走法后还没有刷新的概率表和棋面信息，由于主动拼杀的是我方棋子所以对方棋子在落点处*/
	int i, j, m, n, k;
	double payOff = 0;
	Probability h;

	i = p.fx;    //对方将要拼杀棋子的坐标
	j = p.fy;
	m = p.tx;    //己方将要拼杀棋子的坐标
	n = p.ty;

	k = h.SerchChess(C, m, n);  //找到对方棋子序号，知道对方具体为哪个编号的棋子
	c = CMap[i][j];             //c中装的我方棋子
	MyChessLevel(c);            //根据c值找到对应的z值,也就是返回棋子类型
	payOff = MyGrappleCount(z, k, C);

	return payOff ;
}

double Assessment::GrappleValue(ChessMove p, Chance C[], char CMap[12][5])
{
	/*上面传过来的是产生走法，和产生走法之前还没有刷新的概率表和棋面信息，由于是对方主动进攻，
	所以起点才是我们要找的拼杀棋子*/
	int i, j, m, n, k;
	double payOff  = 0;
	Probability h;

	i = p.fx;  //对方将要拼杀棋子的坐标
	j = p.fy;
	m = p.tx;  //己方将要拼杀棋子的坐标
	n = p.ty;

	k = h.SerchChess(C, i, j);  //找到对方棋子序号，知道对方具体为哪个编号的棋子
	c = CMap[m][n];  //落点坐标才是我方棋子，此时对方进攻
	MyChessLevel(c);   //根据c值找到对应的z值,也就是返回棋子类型
	payOff  = GrappleCount(z, k, C);

	return payOff ;
}

double Assessment::MySadPlaceValue(ChessMove p, char CMap[][5], Chance C[], char k)  //我方位置域得分
{
	Probability h;
	int i, j;
	int m = 0;
	int n = 0;
	int t = 0;
	int f[10] = {0};
	double temp = 0;
	double pf1 = 0;
	double pf2 = 0;
	double q[10] = {0};

	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 5; j++)
		{
			a[i][j] = '0';
		}
	}
	Place(p, CMap);
	for (i = 0; i < 12; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			z=MyChessLevel(a[i][j]);
			if (z ==  -1)  //如果是对方的棋子
			{
				f[m] = h.SerchChess(C, i, j);
				m ++;
			}
		}
	}
	z = MyChessLevel(k);  //找出棋子的数字值
	for (j = 0; j < m; j++)
	{
		pf1 = GrappleCount(z, f[j], C);
		q[t] = pf1;
		t ++;
	}
	for (i = 0; i < t; i++)
	{
		for (j = i + 1; j < t; j++)
		{
			if (q[j] > q[i])
			{
				temp = q[j];
				q[j] = q[i];
				q[i] = temp;
			}
		}
	}
	pf2 = q[0];
	if (pf2 < 0)
	{
		pf2 = 0;
	}

	return  -pf2 * 0.8;
}

double Assessment::SadPlaceValue(ChessMove p, char CMap[][5], Chance C[], int k)  //对方位置域
{
	Probability h;
	int i, j;
	int m = 0;  //m为棋子域中对方棋子个数
	int t = 0;
	double temp = 0;
	double q[10] = {0};
	int f[10] = {0};
	double payOff  = 0, payOff2 = 0;
	for (i = 0; i < 12; i++)  //循环找出位置域中的棋子具体标号
	{
		for (j =  0; j < 5; j++)
		{
			z=MyChessLevel(a[i][j]);  //找出位置域中的棋子是哪个级别或者己方还是对方
			if (!(z ==  -1 || z ==  12))  //如果位置域中的棋子是对方棋子
			{
				f[m] =  z;
				m ++;
			}
		}
	}

	for (i = 0; i < m; i++)  //循环计算拼杀结果
	{
		payOff = MyGrappleCount(f[i], k, C);  //此时f[i]为我方棋子的数字值，k为对方在概率表中的位置
		q[t] = payOff ;
		++ t;
	}

	for (i = 0; i < t; i++)  //找出其中最大的payOff ;即为位置域得分payOff2
	{
		for (j = i + 1; j < t; j++)
		{
			if (q[j] > q[i])
			{
				temp = q[i];
				q[i] = q[j];
				q[j] = temp;
			}
		}
	}

	payOff2 = q[0];
	if (payOff2 < 0)  //此时代表走这一步没有危险
	{
		payOff2 = 0;
	}
	
	return -payOff2 * 0.8;
}

double Assessment::GoOrBackValue(ChessMove move, int mymove)
{
	double moveScore =  0;
	if (mymove ==  1)  //如果是我方移动棋子
	{
		if (move.fx - move.tx ==  0)  //棋子没有移动
		{
			moveScore =  11 - move.tx;
		}else  //棋子移动
		{
			moveScore =  (move.fx - move.tx) * (11 - move.tx);
		}
	}else  
	{
		if (move.fx - move.tx ==  0)  //棋子没有移动
		{
			moveScore =  move.tx;
		}else  //棋子移动
		{
			moveScore =  (move.tx - move.fx) * move.tx;
		}
	}

	moveScore =  moveScore / 12.0;

	return moveScore;
}

double Assessment::MyArmyFlagDefence(char CMap[12][5], char CurMap[12][5], Chance C[25], Chance CurC[25], ChessMove move)
{
	double scoreout10_0 =  0;
	double scorein11_0 =  0;
	double scoreout9_1 =  0;
	double scorein10_1 =  0;
	double scoreout10_2 =  0;
	double scorein11_2 =  0;
	double scoreout9_3 =  0;
	double scorein10_3 =  0;
	double scoreout10_4 =  0;
	double scorein11_4 =  0;
    double score[3] =  {0};
	double scoreall =  10000;
	int x =  0;
	int y =  0;
	int k =  0;
	Probability h;

	if (CurMap[11][1] ==  'L')  //如果坐标为（11, 1）位置是我方军旗
	{
		scoreout10_0 =  MyDefence(CurMap, 10, 0, 3);  //调用我方坐标为10,0外防御分数
		if (scoreout10_0 < 0 && scoreout10_0 > -140)  //如果该防御为空
		{
			score[0] = -999;
		}else  //如果坐标为10,0的外防御位置非空
			score[0] =  scoreout10_0 + scorein11_0;

		scoreout9_1 =  MyDefence(CurMap, 9, 1, 4);  //调用我方坐标为9, 1外防御分数
        if(scoreout9_1 < 0 && scoreout9_1 > -140)  //如果该防御为空
	    {
		    scorein10_1 =  MyDefence(CurMap, 10, 1, 5);  //看相对应的内防御位置情况
		    if(scorein10_1 < 0 && scorein10_1 > -250)  //如果相对应的内防御位置也为空
			    score[1] =  -1200;
		    else  //如果内防御非空或者内防御被占用
			    score[1] =  scoreout9_1 + scorein10_1;
	    }
	    else  //如果坐标为9, 1的外防御位置非空
		    score[1] =  scoreout9_1 + scorein10_1;

		scoreout10_2 =  MyDefence(CurMap, 10, 2, 3);//调用我方坐标为10,2外防御分数
        if(scoreout10_2 < 0 && scoreout10_2 > -140)//如果该防御为空
	    {
		    scorein11_2 =  MyDefence(CurMap, 11, 2, 5);//看相对应的内防御位置情况
		    if(scorein11_2 < 0 && scorein11_2 > -250)//如果相对应的内防御位置也为空
			    score[2] =  -120;
		    else//如果内防御非空或者内防御被占用
			    score[2] =  scoreout10_2 + scorein11_2;
	    }
	    else //如果坐标为10, 2的外防御位置非空
		    score[2] =  scoreout10_2 + scorein11_2;
	    for(int i =  0; i < 3; i ++)
	    {
		    if(score[i] < scoreall)
			    scoreall =  score[i];
	    }
	}else if(CurMap[11][3]== 'L')  //如果坐标为（11, 3）位置是我方军旗
	{
       scoreout10_4 =  MyDefence(CurMap, 10, 4, 3);  //调用我方坐标为10, 4外防御分数
	   scorein11_4 =  MyDefence(CurMap, 11, 4, 5);  //看相对应的内防御位置情况
       if(scoreout10_4 < 0 && scoreout10_4 > -140)  //如果该防御为空
	   {
		   score[0] = -999;
	   }
	   else  //如果坐标为10, 4的外防御位置非空
		   score[0] =  scoreout10_4 + scorein11_4;  //总防御分数是第2,3,4列防御分数之和


	   scoreout9_3 =  MyDefence(CurMap, 9, 3, 4);  //调用我方坐标为9, 3外防御分数
	   scorein10_3 =  MyDefence(CurMap, 10, 3, 5);  //看相对应的内防御位置情况
       if(scoreout9_3 < 0 && scoreout9_3 > -140)  //如果该防御为空
	   {  
		   if(scorein10_3 < 0 && scorein10_3 > -250)  //如果相对应的内防御位置也为空
			   score[1] =  -120;
		   else  //如果内防御非空或者内防御被占用
			   score[1] =  scoreout9_3 + scorein10_3;
	   }
	   else  //如果坐标为9, 3的外防御位置非空
		   score[1] =  scoreout9_3 + scorein10_3;

	   scoreout10_2 =  MyDefence(CurMap,10,2,3);  //调用我方坐标为10, 2外防御分数
	   scorein11_2 =  MyDefence(CurMap,11,2,5);  //看相对应的内防御位置情况
       if(scoreout10_2 < 0 && scoreout10_2 > -140)  //如果该防御为空
	   {
		   
		   if(scorein11_2 < 0 && scorein11_2 > -250)  //如果相对应的内防御位置也为空
			   score[2] = -120;
		   else  //如果内防御非空或者内防御被占用
			   score[2] =  scoreout10_2 + scorein11_2;
	   }
	   else  //如果坐标为10, 2的外防御位置非空
		   score[2] =  scoreout10_2 + scorein11_2;
	   for(int i =  0; i < 3; i ++)
	   {
		   if(score[i] < scoreall)
			   scoreall =  score[i];
	   }
	}

	return scoreall;
}

double Assessment::MyDefence(char CMap[][5], int x, int y, int m)
{
   	double score =  0.0;
	int  empty =  0;
	int  danger =  0;
	int  safe =  0;
	if(CMap[x][y] < 'L' && CMap[x][y] >=  'A')//如果该位置被我方棋子占领
		safe =  1;
	else if(CMap[x][y] == '0')
		empty = 1;
	else
		danger = 1;
	//计算防御得分
    if(safe ==  1)
		score =  m;
	//计算危险的分
	else if(empty == 1)
		score = -m;
	else
		score = -50*m;
	if (CMap[11][1] == 'L' && ((x == 11 && y == 0) || (x == 10 && y == 1) || (x == 11 && y == 2))) {//如果军棋周围有敌方棋子
		if (CMap[x][y] < 'l' && CMap[x][y] >= 'a') score = -99999;
	}
	else if (CMap[11][3] == 'L' && ((x == 11 && y == 4) || (x == 10 && y == 3) || (x == 11 && y == 4))) {//如果军棋周围有敌方棋子
		if (CMap[x][y] < 'l' && CMap[x][y] >= 'a') score = -99999;
	}
		return score;
}

double Assessment::EnemyArmyDefence(char CMap[12][5], char CurMap[12][5],Chance C[25],Chance CurC[25],ChessMove move)
{
	//Chance C[]_是否活着  ChessMove move给出棋子移动前后的坐标
	//给出了10个防御位置
	double scoreout1_0 = 0;
	double scorein0_0 = 0;
	double scoreout2_1 = 0;
	double scorein1_1 = 0;
	double scoreout1_2 = 0;
	double scorein0_2 = 0;
	double scoreout2_3 = 0;
	double scorein1_3 = 0;
	double scoreout1_4 = 0;
	double scorein0_4 = 0;
	double score[3] = {0};
	double score0_1 = 10000;
	double score0_3 = 10000;
	double scoreall = 0;
	int x = 0;
	int y = 0;
	int k = 0;
	Probability h;
    if(CurC[1].P[11] != 0)  //如果坐标为（0,1）位置是敌方军旗
	{
       scoreout1_0 =  EnemyDefence(CurMap, 1, 0, 3);  //调用敌方坐标为1,0外防御分数
	   scorein0_0 =  EnemyDefence(CurMap, 0, 0, 5);  //看相对应的内防御位置情况
       if(scoreout1_0 < 0 && scoreout1_0 >- 140)  //如果该防御为空
	   {
		   
		   if(scorein0_0 < 0 && scorein0_0 > -250)  //如果相对应的内防御位置也为空
			   score[0] =  -120;
		   else  //如果内防御非空或者内防御被占用
			   score[0] =  scoreout1_0 + scorein0_0;
	   }
	   else  //如果坐标为1,0的外防御位置非空
		   score[0] =  scoreout1_0 + scorein0_0;


	   scoreout2_1 =  EnemyDefence(CurMap, 2, 1, 4);  //调用敌方坐标为2，1外防御分数
	    scorein1_1 =  EnemyDefence(CurMap, 1, 1, 5);  //看相对应的内防御位置情况
       if(scoreout2_1 < 0 && scoreout2_1> -140)  //如果该防御为空
	   {
		  
		   if(scorein1_1 < 0 && scorein1_1 > -250)  //如果相对应的内防御位置也为空
			   score[1] =  -120;
		   else  //如果内防御非空或者内防御被占用
			   score[1] =  scoreout2_1 + scorein1_1;
	   }
	   else  //如果坐标为2，1的外防御位置非空
		   score[1] =  scoreout2_1 + scorein1_1;

	   scoreout1_2 =  EnemyDefence(CurMap, 1, 2, 3);  //调用敌方坐标为1, 2外防御分数
	   scorein0_2 =  EnemyDefence(CurMap, 0, 2, 5);  //看相对应的内防御位置情况
       if(scoreout1_2 < 0 && scoreout1_2 > -140)  //如果该防御为空
	   {
		   
		   if(scorein0_2 < 0 && scorein0_2 > -250)  //如果相对应的内防御位置也为空
			   score[2] =  -120;
		   else  //如果内防御非空或者内防御被占用
			   score[2] =  scoreout1_2 + scorein0_2;
	   }
	   else  //如果坐标为1, 2的外防御位置非空
		   score[2] =  scoreout1_2 + scorein0_2;
	   for(int i= 0; i<3; i++)
	   {
		   if(score[i] < score0_1)
			   score0_1 =  score[i];
	   }
	   
	}
   if(CurC[3].P[11] !=  0)  //如果坐标为（0, 3）位置是敌方军旗
	{
       scoreout1_4 =  EnemyDefence(CurMap, 1, 4, 3);  //调用敌方坐标为1, 4外防御分数
	   scorein0_4 =  EnemyDefence(CurMap, 0, 4, 5);  //看相对应的内防御位置情况
       if(scoreout1_4 < 0 && scoreout1_4 > -140)  //如果该防御为空
	   {
		   
		   if(scorein0_4 < 0 && scorein0_4 > -250)  //如果相对应的内防御位置也为空
			   score[0] =  -120;
		   else  //如果内防御非空或者内防御被占用
			   score[0] =  scoreout1_4 + scorein0_4;
	   }
	   else  //如果坐标为1, 4的外防御位置非空
		   score[0] =  scoreout1_4 + scorein0_4;  //总防御分数是第2,3,4列防御分数之和

	   scoreout2_3 =  EnemyDefence(CurMap, 2, 3, 4);  //调用敌方坐标为2, 3外防御分数
	   scorein1_3 =  EnemyDefence(CurMap, 1, 3, 5);  //看相对应的内防御位置情况
       if(scoreout2_3 < 0 && scoreout2_3  >-140)  //如果该防御为空
	   {
		   
		   if(scorein1_3 < 0 && scorein1_3 > -250)  //如果相对应的内防御位置也为空
			   score[1] =  -120;
		   else  //如果内防御非空或者内防御被占用
			   score[1] =  scoreout2_3 + scorein1_3;
	   }
	   else  //如果坐标为2, 3的外防御位置非空
		   score[1] =  scoreout2_3 + scorein1_3;

	   scoreout1_2 =  EnemyDefence(CurMap, 1, 2, 3);  //调用敌方坐标为1, 2外防御分数
	   scorein0_2 =  EnemyDefence(CurMap, 0, 2, 5);  //看相对应的内防御位置情况
       if(scoreout1_2 < 0 && scoreout1_2 > -140)  //如果该防御为空
	   {
		   
		   if(scorein0_2 < 0 && scorein0_2 > -250)  //如果相对应的内防御位置也为空
			   score[2] =  -120;
		   else  //如果内防御非空或者内防御被占用
			   score[2] =  scoreout1_2 + scorein0_2;
	   }
	   else  //如果坐标为1, 2的外防御位置非空
		   score[2] =  scoreout1_2 + scorein0_2;
	   for(int i =  0; i<3; i++)
	   {
		   if(score[i] < score0_3)
			   score0_3 =  score[i];
	   }
	   
	}
  
   scoreall= (CurC[1].P[11]/(CurC[1].P[11] + CurC[3].P[11])) * score0_1 +
	   (CurC[3].P[11]/(CurC[1].P[11] + CurC[3].P[11]))  *score0_3;
	
   return scoreall;
}

double Assessment::EnemyDefence(char CMap[12][5], int x, int y, int m)
{
	double score = 0;
	int danger = 0;
	int empty = 0;
	int safe = 0;
	if (CMap[x][y] < 'l' && CMap[x][y] > 'a')  //如果该位置被我方棋子占领
	{
		safe = 1;
	}else if (CMap[x][y] == '0')
	{
		empty = 1;
	}else
	{
		danger = 1;
	}
	//计算防御得分
	if (safe == 1)
	{
		score = m;
	}
	//计算危险得分
	else if (empty == 1)
	{
		score = -m;
	}else
	{
		score = -50 * m;
	}
	if (CMap[0][1] == 'l' && ((x == 0 && y == 0) || (x == 1 && y == 1) || (x == 0 && y == 2))) {//如果军棋周围有敌方棋子
		if (CMap[x][y] < 'L' && CMap[x][y] >= 'A') score = -99999;
	}
	else if (CMap[0][3] == 'l' && ((x == 0 && y == 4) || (x == 1 && y == 3) || (x == 0 && y == 4))) {//如果军棋周围有敌方棋子
		if (CMap[x][y] < 'L' && CMap[x][y] >= 'A') score = -99999;
	}

	return score;
}

int Assessment::MyChessLevel(char c)
{
	switch (c)   //判断我方的具体为什么棋子
	{
	case 'A': z =  0;  break;
	case 'B': z =  1;  break;
	case 'C': z =  2;  break;
	case 'D': z =  3;  break;
	case 'E': z =  4;  break;
	case 'F': z =  5;  break;
	case 'G': z =  6;  break;
	case 'H': z =  7;  break;
	case 'I': z =  8;  break;
	case 'J': z =  9;  break;
	case 'K': z =  10; break;
	case 'L': z =  11; break;
	case '0': z =  12; break;
	default:  z =  -1;
	}

	return z;
}

double Assessment::MyGrappleCount(int z, int k, Chance C[])  //我方主动进攻
{
	double payOff  =  0;
	double worth1 = 0, rank1 = 0, worth2 = 0, rank2 = 0;
	double m =  0;
	int i =  0;

	switch(z)//找到我方棋子的价值及级别
	{
		case 0 :worth1 =  45,  rank1= 10;  break;
		case 1 :worth1 =  33,  rank1= 9;   break;
		case 2 :worth1 =  20,  rank1= 8;   break;
		case 3 :worth1 =  12,  rank1= 6;   break;
		case 4 :worth1 =  7,   rank1= 5;   break;
		case 5 :worth1 =  4,   rank1= 4;   break;
		case 6 :worth1 =  2,   rank1= 3;   break;
		case 7 :worth1 =  1,   rank1= 2;   break;
		case 8 :worth1 =  9,   rank1= 1;   break;
		case 9 :worth1 =  8,   rank1= 6.5; break;
		case 10 :worth1 =  19, rank1= 7;   break;
		case 11 :worth1 =  1000;          break;
	}
	if(z ==  10)//我方是否为炸弹
	{
		for(i =  0; i < 12; i ++)//循环12次累加payOff 
		{
			switch(i)//判断对方棋子类型、价值、级别、序号
			{
				case 0 :worth2 =  45, rank2 =  10; break;
				case 1 :worth2 =  33, rank2 =  9;  break;
				case 2 :worth2 =  20, rank2 =  8;  break;
				case 3 :worth2 =  12, rank2 =  6;  break;
				case 4 :worth2 =  7,  rank2 =  5;  break;
				case 5 :worth2 =  4,  rank2 =  4;  break;
				case 6 :worth2 =  2,  rank2 =  3;  break;
				case 7 :worth2 =  1,  rank2 =  2;  break;
				case 8 :worth2 =  9,  rank2 =  1;  break;
				case 9 :worth2 =  8,  rank2 =  6.5;break;
				case 10 :worth2= 19,  rank2 =  7;  break;
				case 11 :worth2= 1000;            break;	
			}
			if(i ==  11)//我方炸弹与对方军旗对垒
			{
				m =  (float)C[k].P[i] * 99999;//计算
				payOff  +=  m;
			}
			else if(i ==  9)//我方炸弹与对方地雷对垒
			{
				m =  C[k].P[i]*30;
				payOff  +=  m;
			}
			else if(i ==  8)//我方炸弹与对方士兵对垒
			{
				m =  (float)C[k].P[i]*(5);//计算
				payOff  +=  m;
			}
			else if(i ==  10)//炸弹对战炸弹
			{
				m =  0;
				payOff  +=  m;
			}
			else//我方炸弹对战对方出炸弹地雷士兵军旗外其他类型棋子
			{
					switch(i)//判断敌方自己的棋子类型、价值、级别
					{
						case 0 :worth2 =  45;  break;
						case 1 :worth2 =  33;  break;
						case 2 :worth2 =  20;  break;
						case 3 :worth2 =  12;  break;
						case 4 :worth2 =  7;   break;
						case 5 :worth2 =  2;   break;
						case 6 :worth2 =  1.2; break;
						case 7 :worth2 =  1;   break;
					}
			
				  if(i < 2)
				  {
						m =  (float)C[k].P[i] *(worth2+500);
						payOff  += m;
				  }
				  else if(i ==  2)
				  {
					    m =  (float)C[k].P[i]*1.0;
						payOff  += m;
				  }
				  else
				  {
					m =  (float)C[k].P[i]*(-45.0/worth2);
					payOff  += m;
				  }
				 
				
			}
		}

	}
	else if(z ==  8)//我方主动进攻棋子为工兵
	{
		for(i =  0; i < 12; i++)//循环12次累加payOff 
		{
			switch(i)//判断对方棋子类型、价值、级别
			{
				case 0 :worth2 =  45, rank2 =  10; break;
				case 1 :worth2 =  33, rank2 =  9; break;
				case 2 :worth2 =  20, rank2 =  8; break;
				case 3 :worth2 =  12, rank2 =  6; break;
				case 4 :worth2 =  7, rank2 =  5; break;
				case 5 :worth2 =  4, rank2 =  4; break;
				case 6 :worth2 =  2, rank2 =  3; break;
				case 7 :worth2 =  1, rank2 =  2; break;
				case 8 :worth2 =  9, rank2 =  1; break;
				case 9 :worth2 =  8, rank2 =  6.5; break;
				case 10 :worth2 =  19, rank2 =  7; break;
				case 11 :worth2 =  1000; break;
			}
			if(i ==  11)//工兵对战军旗
			{
				m =  (float)C[k].P[i]*99999;//计算
				payOff += m;
			}
			else if(i== 9)//我方工兵撞地雷
			{
				m= (float)C[k].P[i]*2000;
				payOff += m;
			}
			else if(i== 8)//工兵对战工兵
			{
				m= 0;
				payOff += m;
			}
			else if(i== 10)//工兵对战对方炸弹
			{
				m= (float)C[k].P[i]*(-5);
				payOff += m;
			}
			else//工兵对战对方除军旗地雷炸弹工兵外其他类型棋子
			{
				m= (float)C[k].P[i]*(-2000);
				payOff += m;
			}
		}
	}
	else//我方除军旗炸弹地雷工兵外其他类型棋子对战对方棋子
	{
		for(i= 0;i<12;i++)//循环12次累加payOff 
		{
			switch(i)//判断对方棋子类型、价值、级别
			{
				case 0 :worth2= 45,rank2= 10;break;
				case 1 :worth2= 33,rank2= 9;break;
				case 2 :worth2= 20,rank2= 8;break;
				case 3 :worth2= 12,rank2= 6;break;
				case 4 :worth2=  7,rank2= 5;break;
				case 5 :worth2=  4,rank2= 4;break;
				case 6 :worth2=  2,rank2= 3;break;
				case 7 :worth2=  1,rank2= 2;break;
				case 8 :worth2=  9,rank2= 1;break;
				case 9 :worth2=  8,rank2= 6.5;break;
				case 10 :worth2= 19,rank2= 7;break;
				case 11 :worth2= 1000;break;
			}
			if(i== 11)//对方是否为军旗
			{
				m= (float)C[k].P[i]*99999;//计算
				payOff += m;
			}
			else if(i== 9)//对方是地雷，我方得负分，我方价值越大，得分越小
			{
				m= (float)C[k].P[i]*(-worth1+(fabs(worth1-worth2)/exp(fabs(rank1-rank2))));
				payOff += m;
			}
			else if(i== 8)//对方是工兵，我方得正分
			{
				m= (float)C[k].P[i]*20;
				payOff += m;
			}
			else if(i== 10)//对方是炸弹
			{

                 if(z<2)
				 {
						m= (float)C[k].P[i]*(-worth1-500);
						payOff += m;
				 }
				 else if(z== 2)
				 {
					    m= (float)C[k].P[i]*(-1.0);
						payOff += m;
				 }
				 else
				 {
					m= (float)C[k].P[i]*(45.0/worth1);
					payOff += m;
				 }
				
			}
			else//其他情况
			{
				if(i== z)
				{
					m= 0;
					payOff += m;
				}
				else
				{
					if(worth1>worth2)//主动拼杀级别大于对方时,我方得正分，对方价值越大，我方得分越高
					{
				 		m= (float)C[k].P[i]*(worth2-(fabs(worth1-worth2)/exp(fabs(rank1-rank2))));//公式还有待考究
				 		payOff += m;
					}
					else//主动拼杀级别小于对方,我得负分，我方价值越大得分越小
					{
						m= (float)C[k].P[i]*(-worth1+(fabs(worth1-worth2)/exp(fabs(rank1-rank2))));
						payOff += m;
					}
				}
			}
		}				
	}

	return payOff;
}

double Assessment::GrappleCount(int z, int k, Chance C[])  //敌方主动进攻
{
	double payOff  =  0;
	double worth1 = 0, rank1 = 0, worth2 = 0, rank2 = 0;
	double m =  0;
	int i =  0;

	switch(z)//找到我方棋子的价值及级别
		{
			case 0 :worth1= 45,rank1 = 10;break;
			case 1 :worth1= 33,rank1 = 9;break;
			case 2 :worth1= 20,rank1 = 8;break;
			case 3 :worth1= 12,rank1 = 6;break;
			case 4 :worth1=  7,rank1 = 5;break;
			case 5 :worth1=  4,rank1 = 4;break;
			case 6 :worth1=  2,rank1 = 3;break;
			case 7 :worth1=  1,rank1 = 2;break;
			case 8 :worth1=  9,rank1 = 1;break;
			case 9 :worth1=  8,rank1 = 6.5;break;
			case 10 :worth1= 19,rank1 = 7;break;
			case 11 :worth1= 1000;break;
		}
		for(i =  0;i<12;i++)//循环12次累加payOff （悲观算法，将每个棋子类型的概率加进去算了）
		{
			switch(i)//判断敌方自己的棋子类型、价值、级别、序号
			{
				case 0 :worth2 = 45,rank2 = 10;break;
				case 1 :worth2 = 33,rank2 = 9;break;
				case 2 :worth2 = 20,rank2 = 8;break;
				case 3 :worth2 = 12,rank2 = 6;break;
				case 4 :worth2 =  7,rank2 = 5;break;
				case 5 :worth2 =  4,rank2 = 4;break;
				case 6 :worth2 =  2,rank2 = 3;break;
				case 7 :worth2 =  1,rank2 = 2;break;
				case 8 :worth2 =  9,rank2 = 1;break;
				case 9 :worth2 =  8,rank2 = 6.5;break;
				case 10 :worth2 = 19,rank2 = 7;break;
				case 11 :worth2 = 1000;break;	
			}


			if(i== 10)//主动方为炸弹
			{
				if(z== 11)//炸弹与军旗对垒
				{
					m= (float)C[k].P[i]*99999;//扛走地方我方军旗得分  +无穷  ， 被对方扛走军旗得分  -无穷
					payOff += m;
				}
				else if(z== 9)//主动方炸弹与对手地雷对垒
				{
					m= (float)C[k].P[i]*30;
					payOff += m;
				}
				else if(z== 8)//主动方炸弹与对手工兵对垒//有待考证
				{
					m= (float)C[k].P[i]*(5);//计算
					payOff += m;
				}
				else if(z== 10)//炸弹与炸弹
				{
					m= 0;
					payOff += m;
				}
				else//主动方炸弹与其他棋子类型对垒
				{
                    if(z<2)
					{
						m= (float)C[k].P[i]*(worth1+500);
						payOff += m;
					}
					else if(z== 2)
					{
					    m= (float)C[k].P[i]*1.0;
						payOff += m;
					}
					else
					{
						m= (float)C[k].P[i]*(-45.0/worth1);
						payOff += m;
					}
				}
			}
			else if(i== 8)//主动棋子为工兵
			{
				if(z== 11)//工兵与军旗
				{
					m= (float)C[k].P[i]*99999;//计算
					payOff += m;
				}
				else if(z== 10)//主动方工兵和对手炸弹
				{
					m= (float)C[k].P[i]*(-5);//计算
					payOff += m;
				}
				else if(z== 9)//主动方工兵和对手地雷
				{
					m= (float)C[k].P[i]*2000;//计算
					payOff += m;
				}
				else if(z== 8)
				{
					m= 0;
					payOff += m;
				}
				else//主动方工兵与对方出工兵地雷炸弹外其他类型棋子对垒，我方得负分
				{
				 	m= (float)C[k].P[i]*(-2000);
				 	payOff += m;
				}
			}
			else if(i== 9)//对方是地雷，因为不可能是地雷，所以得分为0
			{
				m= 0.0;
				payOff += m;
			}
			else//其他情况
			{
				if(z== 11)//判断己方棋子是否为军旗
				{
					m= (float)C[k].P[i]*99999;
					payOff += m;
				}
				else if(z== 10)//主动方其他类型棋子与对手炸弹对垒
				{
					switch(i)//判断敌方自己的棋子类型、价值、级别、序号
					{
						case 0 :worth2 = 45;break;
						case 1 :worth2 = 33;break;
						case 2 :worth2 = 20;break;
						case 3 :worth2 = 12;break;
						case 4 :worth2 =  7;break;
						case 5 :worth2 =  2;break;
						case 6 :worth2 =  1.2;break;
						case 7 :worth2 =  1;break;
					}
					if(i<2)
					{
						m= (float)C[k].P[i]*(-worth2-500 );
						payOff += m;
					}
					else if(i== 2)
					{
					    m= (float)C[k].P[i]*(-1.0);
						payOff += m;
					}
					else
					{
						m= (float)C[k].P[i]*(45.0/worth2 );
						payOff += m;
					}
				}
				else if(z== 9)// 地雷对主动方除士兵炸弹军旗地雷外的其他类型棋子，主动棋子价值越大，损失越惨重
				{
					m= (float)C[k].P[i]*(-worth2 +fabs(worth1-worth2 )/exp(fabs(rank1 -rank2 )));//计算
					payOff += m;
				}
				else if(z== 8)//对手工兵对主动方除工兵炸弹军旗地雷外其他类型棋子，我方得正分
				{
					m= (float)C[k].P[i]*2000;//计算
					payOff += m;
				}
				else//双方都为其他类型棋子
				{			
					if(i== z)
					{
						m= (float)C[k].P[i]*0;
					 	payOff += m;
					}
					else
					{
						if(worth2 >worth1)//主动方获胜，对手价值越高，得分越高
						{
				 			m= (float)C[k].P[i]*(worth1-(fabs(worth1-worth2 )/exp(fabs(rank1 -rank2 ))));//公式还有待考究
				 			payOff += m;
						}
						else//主动方失败，主动方价值越高，得分越低
						{
							m= (float)C[k].P[i]*(-worth2 +(fabs(worth1-worth2 )/exp(fabs(rank1 -rank2 ))));
							payOff += m;
						}
					}
				}
			}
		}

	return payOff ;
}

void Assessment::Place(ChessMove p, char CMap[][5])
{
	int i, j, m, n;
	i = p.tx;
	j = p.ty;
	//坐标原点在左上角,横向为y轴，纵向为x轴
	if(i*5+j == 59)//
	{
		a[i][j] = CMap[i][j];
		a[i-1][j] = CMap[i-1][j];//上
		a[i][j-1] = CMap[i][j-1];//左
	}
	if(i*5+j == 55)//
	{
		a[i][j] = CMap[i][j];
		a[i-1][j] = CMap[i-1][j];//上
		a[i][j+1] = CMap[i][j+1];//右
	}
	if(i*5+j == 0)//
	{
		a[i][j] = CMap[i][j];
		a[i+1][j] = CMap[i+1][j];//下
		a[i][j-1] = CMap[i][j-1];//左
	}
	if(i*5+j == 4)//
	{
		a[i][j] = CMap[i][j];
		a[i][j+1] = CMap[i][j+1];//下
		a[i+1][j] = CMap[i+1][j];//右
	}
	if(i*5+j == 1 || i*5+j == 56 || i*5+j == 3 || i*5+j == 58 || i*5+j == 2 || i*5+j == 57)
	{
		a[i][j] = CMap[i][j];
		a[i-1][j] = CMap[i-1][j];//上
		a[i+1][j] = CMap[i+1][j];//右
		a[i][j-1] = CMap[i][j-1];//左
	}
	if(i*5+j == 16 || i*5+j == 41 || i*5+j == 12 || i*5+j == 22 || i*5+j == 37 || i*5+j == 47 || i*5+j == 18 || i*5+j == 43)
	{
		a[i][j] = CMap[i][j];
		a[i-1][j] = CMap[i-1][j];//上
		a[i+1][j] = CMap[i+1][j];//下
		a[i][j+1] = CMap[i][j+1];//右
		a[i][j-1] = CMap[i][j-1];//左
	}
	if(i*5+j ==  6 || i*5+j ==  8 || i*5+j ==  51 || i*5+j ==  53)
	{
		a[i][j] = CMap[i][j];
		a[i-1][j] = CMap[i-1][j];//上
		a[i+1][j] = CMap[i+1][j];//下

		//左一排铁路
		for(n = j; n > 0; n--)
		{
			if(CMap[i][n-1] != '0')
			{
				a[i][n-1] = CMap[i][n-1];
				break;
			}
		}
		//右一排铁路
		for(n = j; n < 5; n++)
		{
			if(CMap[i][n] != '0')
			{
				a[i][n+1] = CMap[i][n+1];
				break;
			}
		}
	}
	if(i*5+j ==  10 || i*5+j ==  20 || i*5+j ==  35 || i*5+j ==  45)
	{
		a[i][j] = CMap[i][j];
		a[i][j+1] = CMap[i][j+1];//右

		//上一排铁路
		for(m = i; m > 0; m--)
		{
			if(CMap[m-1][j] != '0')
			{
				a[m-1][j] = CMap[m-1][j];
				break;
			}
		}
		//下一排铁路
		for(m = i; m < 12; m++)
		{
			if(CMap[m+1][j] != '0')
			{
				a[m+1][j] = CMap[m+1][j];
				break;
			}
		}
	}
	if(i*5+j ==  14 || i*5+j ==  24 || i*5+j ==  39 || i*5+j ==  49)
	{
		a[i][j] = CMap[i][j];
		a[i][j-1] = CMap[i][j-1];//左

		//上一排铁路
		for(m = i; m > 0; m--)
		{
			if(CMap[m-1][j] != '0')
			{
				a[m-1][j] = CMap[m-1][j];
				break;
			}
		}
		//下一排铁路
		for(m = i; m < 12; m++)
		{
			if(CMap[m+1][j] != '0')
			{
				a[m+1][j] = CMap[m+1][j];
				break;
			}
		}
	}
	if(i*5+j ==  15 || i*5+j ==  40)
	{
		a[i][j] = CMap[i][j];
		a[i][j+1] = CMap[i][j+1];//右
		a[i+1][j+1] = CMap[i+1][j+1];//下右
		a[i-1][j+1] = CMap[i-1][j+1];//上右

		//上一排铁路
		for(m = i; m > 0; m--)
		{
			if(CMap[m-1][j] != '0')
			{
				a[m-1][j] = CMap[m-1][j];
				break;
			}
		}
		//下一排铁路
		for(m = i;m < 12; m++)
		{
			if(CMap[m+1][j] != '0')
			{
				a[m+1][j] = CMap[m+1][j];
				break;
			}
		}
	}
	if(i*5+j ==  19 || i*5+j ==  44)
	{
		a[i][j] = CMap[i][j];
		a[i][j-1] = CMap[i][j-1];//左
		a[i-1][j-1] = CMap[i-1][j-1];//上左
		a[i+1][j-1] = CMap[i+1][j-1];//下左

		//上一排铁路
		for(m = i; m > 0 ; m--)
		{
			if(CMap[m-1][j] != '0')
			{
				a[m-1][j] = CMap[m-1][j];
				break;
			}
		}
		//下一排铁路
		for(m =  i; m < 12; m++)
		{
			if(CMap[m+1][j] !=  '0')
			{
				a[m+1][j] =  CMap[m+1][j];
				break;
			}
		}
	}
	if(i*5+j ==  5)
	{
		a[i][j] = CMap[i][j];
		a[i+1][j+1] = CMap[i+1][j+1];//下右

		//右一排铁路
		for(n =  j;n < 5; n++)
		{
			if(CMap[i][n] != '0')
			{
				a[i][n+1] = CMap[i][n+1];
				break;
			}
		}
		//下一排铁路
		for(m = i; m < 12; m++)
		{
			if(CMap[m+1][j]!= '0')
			{
				a[m+1][j]= CMap[m+1][j];
				break;
			}
		}
	}
	if(i*5+j== 50)
	{
		a[i][j]= CMap[i][j];
		a[i+1][j]= CMap[i+1][j];//下
		a[i-1][j+1]= CMap[i-1][j+1];//上右

		//右一排铁路
		for(n= j;n<5;n++)
		{
			if(CMap[i][n]!= '0')
			{
				a[i][n+1]= CMap[i][n+1];
				break;
			}
		}
		//上一排铁路
		for(m= i;m>0;m--)
		{
			if(CMap[m-1][j]!= '0')
			{
				a[m-1][j]= CMap[m-1][j];
				break;
			}
		}
	}
	if(i*5+j== 9)
	{
		a[i][j]= CMap[i][j];
		a[i-1][j]= CMap[i-1][j];//上
		a[i+1][j-1]= CMap[i+1][j-1];//下左

		//左一排铁路
		for(n= j;n>0;n--)
		{
			if(CMap[i][n-1]!= '0')
			{
				a[i][n-1]= CMap[i][n-1];
				break;
			}
		}
		//下一排铁路
		for(m= i;m<12;m++)
		{
			if(CMap[m+1][j]!= '0')
			{
				a[m+1][j]= CMap[m+1][j];
				break;
			}
		}
	}
	if(i*5+j== 54)
	{
		a[i][j]= CMap[i][j];
		a[i+1][j]= CMap[i+1][j];//下
		a[i-1][j-1]= CMap[i-1][j-1];//上左

		//左一排铁路
		for(n= j;n>0;n--)
		{
			if(CMap[i][n-1]!= '0')
			{
				a[i][n-1]= CMap[i][n-1];
				break;
			}
		}
		//上一排铁路
		for(m= i;m>0;m--)
		{
			if(CMap[m-1][j]!= '0')
			{
				a[m-1][j]= CMap[m-1][j];
				break;
			}
		}
	}
	if(i*5+j== 25)
	{
		a[i][j]= CMap[i][j];
		a[i-1][j+1]= CMap[i-1][j+1];//上右

		//上一排铁路
		for(m= i;m>0;m--)
		{
			if(CMap[m-1][j]!= '0')
			{
				a[m-1][j]= CMap[m-1][j];
				break;
			}
		}
		//下一排铁路
		for(m= i;m<12;m++)
		{
			if(CMap[m+1][j]!= '0')
			{
				a[m+1][j]= CMap[m+1][j];
				break;
			}
		}
		//右一排铁路
		for(n= j;n<5;n++)
		{
			if(CMap[i][n]!= '0')
			{
				a[i][n+1]= CMap[i][n+1];
				break;
			}
		}
	}
	if(i*5+j== 30)
	{
		a[i][j]= CMap[i][j];
		a[i+1][j+1]= CMap[i+1][j+1];//下右

		//上一排铁路
		for(m= i;m>0;m--)
		{
			if(CMap[m-1][j]!= '0')
			{
				a[m-1][j]= CMap[m-1][j];
				break;
			}
		}
		//下一排铁路
		for(m= i;m<12;m++)
		{
			if(CMap[m+1][j]!= '0')
			{
				a[m+1][j]= CMap[m+1][j];
				break;
			}
		}
		//右一排铁路
		for(n= j;n<5;n++)
		{
			if(CMap[i][n]!= '0')
			{
				a[i][n+1]= CMap[i][n+1];
				break;
			}
		}
	}
	if(i*5+j== 32||i*5+j== 7)
	{
		a[i][j]= CMap[i][j];
		a[i-1][j]= CMap[i-1][j];//上
		a[i+1][j]= CMap[i+1][j];//下
		a[i+1][j+1]= CMap[i+1][j+1];//下右
		a[i+1][j-1]= CMap[i+1][j-1];//下左

		//左一排铁路
		for(n= j;n>0;n--)
		{
			if(CMap[i][n-1]!= '0')
			{
				a[i][n-1]= CMap[i][n-1];
				break;
			}
		}
		//右一排铁路
		for(n= j;n<5;n++)
		{
			if(CMap[i][n]!= '0')
			{
				a[i][n+1]= CMap[i][n+1];
				break;
			}
		}
	}
	if(i*5+j== 27||i*5+j== 52)
	{
		a[i][j]= CMap[i][j];
		a[i-1][j]= CMap[i-1][j];//上
		a[i+1][j]= CMap[i+1][j];//下
		a[i-1][j+1]= CMap[i-1][j+1];//上右
		a[i-1][j-1]= CMap[i-1][j-1];//上左

		//左一排铁路
		for(n= j;n>0;n--)
		{
			if(CMap[i][n-1]!= '0')
			{
				a[i][n-1]= CMap[i][n-1];
				break;
			}
		}
		//右一排铁路
		for(n= j;n<5;n++)
		{
			if(CMap[i][n]!= '0')
			{
				a[i][n+1]= CMap[i][n+1];
				break;
			}
		}
	}
	if(i*5+j== 29)
	{
		a[i][j]= CMap[i][j];
		a[i-1][j-1]= CMap[i-1][j-1];//上左

		//上一排铁路
		for(m= i;m>0;m--)
		{
			if(CMap[m-1][j]!= '0')
			{
				a[m-1][j]= CMap[m-1][j];
				break;
			}
		}
		//下一排铁路
		for(m= i;m<12;m++)
		{
			if(CMap[m+1][j]!= '0')
			{
				a[m+1][j]= CMap[m+1][j];
				break;
			}
		}
		//左一排铁路
		for(n= j;n>0;n--)
		{
			if(CMap[i][n-1]!= '0')
			{
				a[i][n-1]= CMap[i][n-1];
				break;
			}
		}
	}
	if(i*5+j== 34)
	{
		a[i][j]= CMap[i][j];
		a[i+1][j-1]= CMap[i+1][j-1];//下左

		//上一排铁路
		for(m= i;m>0;m--)
		{
			if(CMap[m-1][j]!= '0')
			{
				a[m-1][j]= CMap[m-1][j];
				break;
			}
		}	
		//下一排铁路
		for(m= i;m<12;m++)
		{
			if(CMap[m+1][j]!= '0')
			{
				a[m+1][j]= CMap[m+1][j];
				break;
			}
		}
		//左一排铁路
		for(n= j;n>0;n--)
		{
			if(CMap[i][n-1]!= '0')
			{
				a[i][n-1]= CMap[i][n-1];
				break;
			}
		}
	}
	if(i*5+j== 26||i*5+j== 28)
	{
		a[i][j]= CMap[i][j];
		a[i-1][j]= CMap[i-1][j];//上

		//左一排铁路
		for(n= j;n>0;n--)
		{
			if(CMap[i][n-1]!= '0')
			{
				a[i][n-1]= CMap[i][n-1];
				break;
			}
		}
		//右一排铁路
		for(n= j;n<5;n++)
		{
			if(CMap[i][n]!= '0')
			{
				a[i][n+1]= CMap[i][n+1];
				break;
			}
		}
	}
	if(i*5+j== 31||i*5+j== 33)
	{
		a[i][j]= CMap[i][j];
		a[i+1][j]= CMap[i+1][j];//下

		//左一排铁路
		for(n= j;n>0;n--)
		{
			if(CMap[i][n-1]!= '0')
			{
				a[i][n-1]= CMap[i][n-1];
				break;
			}
		}
		//右一排铁路
		for(n= j;n<5;n++)
		{
			if(CMap[i][n]!= '0')
			{
				a[i][n+1]= CMap[i][n+1];
				break;
			}
		}
	}
	if(i*5+j== 27)
	{
		a[i][j]= CMap[i][j];
		a[i-1][j]= CMap[i-1][j];//上
		a[i+1][j]= CMap[i+1][j];//下
		a[i-1][j+1]= CMap[i-1][j+1];//上右
		a[i-1][j-1]= CMap[i-1][j-1];//上左

		//左一排铁路
		for(n= j;n>0;n--)
		{
			if(CMap[i][n-1]!= '0')
			{
				a[i][n-1]= CMap[i][n-1];
				break;
			}
		}
		//右一排铁路
		for(n= j;n<5;n++)
		{
			if(CMap[i][n]!= '0')
			{
				a[i][n+1]= CMap[i][n+1];
				break;
			}
		}
	}
}

double Assessment::Railway(char CMap[][5])
{
     int firstChessIsMychess= 0;
	 int firstChessIsEnemychess= 0;
	 int firstChessIsMychess0 = 0;
	 int firstChessIsEnemychess0 = 0;

	 double raiwayscore= 0;
	 for(int i= 9;i>0;i--)
	 {
		 if(CMap[i][4]>= 'a'&&CMap[i][4]<'l')
		 {
			 firstChessIsEnemychess= 1;
			 break;
		 }
		 if(CMap[i][4]>= 'A'&&CMap[i][4]<'L')
		 {
			 firstChessIsMychess= 1;
			 break;
		 }
		     
	 }
	 for (int i = 9; i>0; i--)
	 {
		 if (CMap[i][0] >= 'a'&&CMap[i][0]<'l')
		 {
			 firstChessIsEnemychess0 = 1;
			 break;
		 }
		 if (CMap[i][0] >= 'A'&&CMap[i][0]<'L')
		 {
			 firstChessIsMychess0 = 1;
			 break;
		 }

	 }
	 if(firstChessIsEnemychess== 1)
        raiwayscore= -40;
	 else raiwayscore = 40;
	 if (firstChessIsEnemychess0 == 1)
		 raiwayscore -= 40;
	 else raiwayscore += 40;
	 if(CMap[9][2]<'l'&&CMap[9][2]>= 'a')
        raiwayscore+= -40;
	 return raiwayscore;
}

double Assessment::Home(Chance C[], char CMap[][5])
{
	double homeValue  =  0;
	double rate1= 0;//对方第一个大本营中军旗概率在两个大本营中占的比例
	double rate2= 0;//另一大本营占的比例
	rate1= C[1].P[11]/(C[1].P[11]+C[3].P[11]);
	rate2= C[3].P[11]/(C[1].P[11]+C[3].P[11]);
//占据普通行营
	if(CMap[4][3]<'l'&&CMap[4][3]>'a')
		homeValue += -0.5;
	else if(CMap[4][3]== '0')
		homeValue += 0;
	else
		homeValue += 0.5;


    if(CMap[4][1]<'l'&&CMap[4][1]>'a')
		homeValue += -0.5;
	else if(CMap[4][1]== '0')
		homeValue += 0;
	else
		homeValue += 0.5;


    if(CMap[7][1]<'l'&&CMap[7][1]>'a')
		homeValue += -0.5;
	else if(CMap[7][1]== '0')
		homeValue += 0;
	else
		homeValue += 0.5;


	if(CMap[7][3]<'l'&&CMap[7][3]>'a')
		homeValue += -0.5;
	else if(CMap[7][3]== '0')
		homeValue += 0;
	else
		homeValue += 0.5;

//占据大营
	if (CMap[11][1] == 'L') {
		if (CMap[9][1]<'l'&&CMap[9][1]>'a')
			homeValue += -1.2;
		else if (CMap[9][1] == '0')
			homeValue += 0;
		else
			homeValue += 1.2;
	}
	else
	{
		if (CMap[9][1]<'l'&&CMap[9][1]>'a')
			homeValue += -0.5;
		else if (CMap[9][1] == '0')
			homeValue += 0;
		else
			homeValue += 0.5;
	}

	if (CMap[11][3] == 'L') {
		if (CMap[9][3]<'l'&&CMap[9][3]>'a')
			homeValue += -1.2;
		else if (CMap[9][3] == '0')
			homeValue += 0;
		else
			homeValue += 1.2;
	}
	else
	{
		if (CMap[9][3]<'l'&&CMap[9][3]>'a')
			homeValue += -0.5;
		else if (CMap[9][3] == '0')
			homeValue += 0;
		else
			homeValue += 0.5;
	}

//占据中营

  if(CMap[3][2]<'l'&&CMap[3][2]>'a')
		homeValue += -1;
	else if(CMap[3][2]== '0')
		homeValue += 0;
	else
		homeValue += 1;


    if(CMap[8][2]<'l'&&CMap[8][2]>'a')
		homeValue += -1;
	else if(CMap[8][2]== '0')
		homeValue += 0;
	else
		homeValue += 1;


	//占据大营
	if(CMap[2][1]<'l'&&CMap[2][1]>'a')
		homeValue += rate1*(-1.2)+rate2*(-0.5);
	else if(CMap[2][1]== '0')
		homeValue += 0;
	else
		homeValue += rate1*(1.2)+rate2*(0.5);;


	if(CMap[2][3]<'l'&&CMap[2][3]>'a')
		homeValue += rate2*(-1.2)+rate1*(-0.5);
	else if(CMap[2][3]== '0')
		homeValue += 0;
	else
		homeValue += rate2*(1.2)+rate1*(0.5);


	return homeValue ;
}

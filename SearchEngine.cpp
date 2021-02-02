// SearchEngine.cpp: implementation of the SearchEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "SearchEngine.h"
#include <iostream>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SearchEngine::SearchEngine()
{

	//maxdepht = 2;
	Because = 5;
}

SearchEngine::~SearchEngine()
{

}



void SearchEngine::Thansfor(char(*CurMap)[5], char CMap[12][5], ChessMove move, Chance *CurC, Chance C[25])
{
	int result;															 //0表示机器胜，1表示对方胜，2表示同归于尽，3表示无拼杀
  //将当前棋盘信息赋给CurMap
	int mychess = 0;													//0表示敌方走棋，1表示机器方走棋
	if (CMap[move.fx][move.fy] <= 'l'&&CMap[move.fx][move.fy] >= 'a')	//对方走棋
		mychess = 0;
	else
		mychess = 1;
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 5; j++)
			CurMap[i][j] = CMap[i][j];
	if (CurMap[move.tx][move.ty] == '0')								//落点无棋子无拼杀
	{
		CurMap[move.tx][move.ty] = CurMap[move.fx][move.fy];			//将起始位置的值赋给落点位置
		CurMap[move.fx][move.fy] = '0';									//起始位置值设为0
		result = 3;
		if (mychess == 0)												//对方走棋
		{
			CoordinateChange(CurC, C, result, move, mychess);			//调和概率
		}
		else if (mychess == 1)											//我方行棋
		{
			//将概率表复制出来
			for (int i = 0; i < 25; i++)
			{
				CurC[i].x = C[i].x;
				CurC[i].y = C[i].y;
				CurC[i].assume = C[i].assume;
				CurC[i].alive = C[i].alive;
				for (int j = 0; j < 12; j++)
					CurC[i].P[j] = C[i].P[j];
			}
		}
	}
	else
	{
		Referee(CurMap, move, CurC, C, mychess);						 //落点处有拼杀，裁判拼杀结果
	}
}

double SearchEngine::Window(int windowvalue, int s, int total, Chance c[])
{
	double pieceEntroy = 0;												//棋子信息熵总和
	double averEntroy = 0;												//局面信息熵
	double rate;														//窗口增长倍数
	for (int i = 0; i < 25; i++)
		if (c[i].alive == 1)											//如果棋子还活着
		{
			for (int j = 0; j < 12; j++)
				if (c[i].P[j] != 0)
					pieceEntroy += c[i].P[j] * (log(c[i].P[j]));
		}
	averEntroy = pieceEntroy / total;
	if (s == 0) averEntroy0 = averEntroy;
	if (windowvalue == 2)
		rate = 1.0;
	else if (windowvalue == 0)
		if (s == 0) rate = 1.8;
		else rate = averEntroy*1.8 / averEntroy0;
	else
		if (s == 0) rate = 1.1;
		else rate = averEntroy*1.1 / averEntroy0;
		return rate;
}


void SearchEngine::denfence(char CurMap[12][5],int count,ChessMove &c1, int &flag) {
	ChessMove item;
	char minerank='L';
	if(CurMap[11][1]=='L')//己方军棋位置
		for (int n = 0; n < 3; n++) {
			if(CurMap[10][n]<='k'&&CurMap[10][n]>='a')//上三格为对方的棋子
				for (int i = 0; i < count; i++) {
					item = mg.GetMove(0,i);
					if (item.tx == 10 && item.ty == n) {
						if(CurMap[item.fx][item.fy]<minerank)c1 = item;
						flag = 1;
					}
				}
	}
	else if (CurMap[11][3] == 'L')//己方军棋位置
		for (int n = 2; n < 5; n++) {
			if (CurMap[10][n] <= 'k'&&CurMap[10][n] >= 'a')//上三格为对方的棋子
				for (int i = 0; i < count; i++) {
					item = mg.GetMove(0, i);
					if (item.tx == 10 && item.ty == n) {
						if (CurMap[item.fx][item.fy]<minerank)c1 = item;
						flag = 1;
					}
				}
		}
}
void SearchEngine::jingyan(char CurMap[12][5], int count,ChessMove &c1,int &flag) {

}
void SearchEngine::attack(char CurMap[12][5], int count,ChessMove &c1,int &flag) {

}

void SearchEngine::armyflag(char CurMap[12][5], int count, ChessMove &c1, int &flag) {
	ChessMove item;
	for (int i = 0; i < count; i++) {
		item = mg.GetMove(0, i);
		if (CurMap[item.tx][item.ty] == 'l') { c1 = item;	flag = 1; }
	}
}






/*
double SearchEngine::AWT(int depht, double Alpha, double Beta, char CMap[12][5], Vector(*vectors)[5], Chance C[25], ChessMove &bestmove, double upscore)
{
	double g=-999999;					//存储最佳倒推值
	double x;					//存储倒推值
	int count;					//存储当前棋局叶子节点个数
	int k;
	int CurMapNumber[12][5];	//用于存储将字符信息转换为数字信息的棋盘信息
	char CurMap[12][5];			//用于存储由走法生成棋转换过来的棋盘信息
	Chance CurC[25];			//用于存储因为棋面信息变化而改变的概率表信息
	Vector CurVector[12][5];	//用于存储棋盘界面信息
	int windowvalue;
	ChessMove c1;
	//将概率表复制出来
	for (int i = 0; i < 25; i++)
	{
		CurC[i].x = C[i].x;
		CurC[i].y = C[i].y;
		CurC[i].assume = C[i].assume;
		CurC[i].alive = C[i].alive;
		for (int j = 0; j < 12; j++)
			CurC[i].P[j] = C[i].P[j];
	}
	//将当前棋盘信息赋给CurMap
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 5; j++)
			CurMap[i][j] = CMap[i][j];


	//将路面信息复制出来
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 5; j++)
			CurVector[i][j] = vectors[i][j];
	//计算对方棋子总个数
	Total(CMap);
	if (depht == maxdepht)//如果是叶子节点
	{

		double myarmyflagscore = 0, enemyarmyflagscore = 0, grapplevalue = 0,
			sadplacevalue = 0, grapple = 0, goorbackvalue = 0,
			home = 0, army = 0, railwayscore = 0;
		double score = 0;//总得分
		char value = '0';

		k = 0;//刷新k值
		CharToInt(CMap, CurMapNumber);//将char转换为int
		count = mg.CreatePossibleMove(CurMapNumber, depht, depht % 2, vectors);//调用走法生成器
		c1 = mg.GetMove(depht, k++);
		Thansfor(CurMap, CMap, c1, CurC, C);//将走法生成器信息转换为棋盘信息，并刷新概率表
		ChangeVector(CurVector, vectors, CurMap, c1);//刷新棋盘路面信息
		g = -999998;

		while (g <= Beta&&k <= count)
		{
			grapplevalue = 0; sadplacevalue = 0; home = 0; army = 0; railwayscore = 0; goorbackvalue = 0; value = '0';
			myarmyflagscore = 0; enemyarmyflagscore = 0;//每次循环需要将得分全部刷新
			myarmyflagscore = am.MyArmyFlagDefence(CMap, CurMap, C, CurC, c1);//己方军旗防御得分
			enemyarmyflagscore = -am.EnemyArmyDefence(CMap, CurMap, C, CurC, c1);//调用对手军旗防御评估函数
			army = myarmyflagscore + enemyarmyflagscore;
			home = am.Home(CurC, CurMap);
			railwayscore = am.Railway(CurMap);
			if (CMap[c1.tx][c1.ty] == '0')//如果落点坐标为空，即不发生拼杀就只进行位置域评分
			{
				value = CMap[c1.fx][c1.fy];
				sadplacevalue = am.MySadPlaceValue(c1, CurMap, CurC, value);//底层需要位置域得分，因为已经是模拟走棋的底层
				//if (sadplacevalue == 0 && CMap[c1.fx][c1.fy] != 'I')
					//goorbackvalue = am.GoOrBackValue(c1, 1);
			}
			else//否则将进行拼杀，其得分应该是拼杀后的得分+位置域评估得分
			{
				value = CMap[c1.fx][c1.fy];
				grapplevalue = am.MyGrappleValue(c1, C, CMap);//调用拼杀评估函数计算得分
				if (grapplevalue > 0 &&
					CMap[c1.tx][c1.ty] != 'k'&&CMap[c1.tx][c1.ty] != 'j'
					&&CMap[c1.fx][c1.fy] != 'K')//如果拼杀后我方获胜则可以计算位置域
				{
					sadplacevalue = am.MySadPlaceValue(c1, CurMap, CurC, value);
					//if (sadplacevalue == 0 && CMap[c1.fx][c1.fy] != 'I')
					//	goorbackvalue = am.GoOrBackValue(c1, 1);
				}
			}
			score = sadplacevalue + grapplevalue + home + goorbackvalue + army + railwayscore;//四舍五入去掉不重要的分值  
			x = score + upscore;
			if (x > g)
				g = x;
			c1 = mg.GetMove(depht, k++);
			Thansfor(CurMap, CMap, c1, CurC, C);//将走法生成器信息转换为棋盘信息，并刷新概率表
			ChangeVector(CurVector, vectors, CurMap, c1);//刷新棋盘路面信息
		}
	}
	else if (depht % 2 == 1)//如果是min节点
	{
		double grapplevalue = 0, sadplacevalue = 0, goorbackvalue = 0;
		double score = 0;//总得分
		int value = 0;

		k = 0;  //刷新k值
		CharToInt(CMap, CurMapNumber);//将char转换为int
		count = mg.CreatePossibleMove(CurMapNumber, depht, depht % 2, vectors);//调用走法生成器
		c1 = mg.GetMove(depht, k++);//取出第一个孩子
		Thansfor(CurMap, CMap, c1, CurC, C);//将走法生成器信息转换为棋盘信息，并刷新概率表
		ChangeVector(CurVector, vectors, CurMap, c1);//刷新棋盘路面信息
		g = 10000.0;
		while (g > Alpha&&k <= count)
		{
			grapplevalue = 0; sadplacevalue = 0; goorbackvalue = 0; value = 0;
			if (CMap[c1.tx][c1.ty] == '0')//如果落点坐标为空，即不发生拼杀就只进行位置域评分
			{
				value = pb.SerchChess(C, c1.fx, c1.fy);
				sadplacevalue = am.SadPlaceValue(c1, CurMap, CurC, value);
				//if (sadplacevalue == 0)
				//	goorbackvalue = am.GoOrBackValue(c1, 0);
			}
			else//否则将进行拼杀，其得分应该是拼杀后的得分+位置域评估得分
			{
				value = pb.SerchChess(C, c1.fx, c1.fy);
				grapplevalue = am.GrappleValue(c1, C, CMap);//调用拼杀评估函数计算得分
				if (grapplevalue > 0 &&
					CMap[c1.tx][c1.ty] != 'K'&&CMap[c1.tx][c1.ty] != 'J'
					&&CMap[c1.fx][c1.fy] != 'k')//如果拼杀后我方获胜则可以计算位置域
				{
					sadplacevalue = am.SadPlaceValue(c1, CurMap, CurC, value);
					//if (sadplacevalue == 0)
					//	goorbackvalue = am.GoOrBackValue(c1, 0);
				}

			}
			score = grapplevalue + sadplacevalue + goorbackvalue + upscore;//四舍五入去掉不重要的分值
			x = AWT(depht + 1, Alpha, Beta, CurMap, CurVector, CurC, bestmove, -score);
			if (x < g) //g是其中的最小值
				g = x;
			c1 = mg.GetMove(depht, k++);
			Thansfor(CurMap, CMap, c1, CurC, C);//将走法生成器信息转换为棋盘信息，并刷新概率表
			ChangeVector(CurVector, vectors, CurMap, c1);//刷新棋盘路面信息
			Beta = g;//有问题                                                          
		}
	}
	else if (depht % 2 == 0 && depht != maxdepht) //如果是max节点
	{
		double grapplevalue = 0, sadplacevalue = 0, goorbackvalue = 0;
		double score = 0;//总得分
		char value = '0';
		Window(1, depht, total, CurC);
		k = 0;//刷新k值
		SYSTEMTIME sys;
		time_t dwstart;
		int istime;
		CharToInt(CMap, CurMapNumber);//将char转换为int
		count = mg.CreatePossibleMove(CurMapNumber, depht, depht % 2, vectors);//调用走法生成器
		c1 = mg.GetMove(depht, k++);
		if (depht == 0) {
			int flag = 0;
			if (!flag)armyflag(CMap, count, c1, flag);
			if(!flag)denfence(CMap, count, c1,flag);
			if (!flag)attack(CMap, count, c1, flag);
			if (!flag)jingyan(CMap, count, c1, flag);
			if (flag == 1) {
				bestmove.setFX(c1.fx);
				bestmove.setFY(c1.fy);
				bestmove.setTX(c1.tx);
				bestmove.setTY(c1.ty);
				return g;
			}
		}
		bestmove.setFX(c1.fx);
		bestmove.setFY(c1.fy);
		bestmove.setTX(c1.tx);
		bestmove.setTY(c1.ty);
		Thansfor(CurMap, CMap, c1, CurC, C);//将走法生成器信息转换为棋盘信息，并刷新概率表
		ChangeVector(CurVector, vectors, CurMap, c1);//刷新棋盘路面信息
		g = -999998.0;
		while (g < Beta&&k <= count)
		{
			if (CMap[c1.tx][c1.ty] == 'l')//落点是军旗可能存在的位置，则这个走法是最佳走法
			{
				bestmove.setFX(c1.fx);
				bestmove.setFY(c1.fy);
				bestmove.setTX(c1.tx);
				bestmove.setTY(c1.ty);
				break;
			}
			else
			{
				grapplevalue = 0; sadplacevalue = 0; goorbackvalue = 0; value = '0';
				if (CMap[c1.tx][c1.ty] == '0')//如果落点坐标为空，即不发生拼杀就只进行位置域评分
				{
					value = CMap[c1.fx][c1.fy];
					sadplacevalue = am.MySadPlaceValue(c1, CurMap, CurC, value);
					if (sadplacevalue == 0 && CMap[c1.fx][c1.fy] != 'I')
						goorbackvalue = am.GoOrBackValue(c1, 1);
				}
				else//否则将进行拼杀，其得分应该是拼杀后的得分+位置域评估得分
				{
					value = CMap[c1.fx][c1.fy];
					grapplevalue = am.MyGrappleValue(c1, C, CMap);//调用拼杀评估函数计算得分
					if (grapplevalue > 0 &&
						CMap[c1.tx][c1.ty] != 'k'&&CMap[c1.tx][c1.ty] != 'j'
						&&CMap[c1.fx][c1.fy] != 'K')//如果拼杀后我方获胜则可以计算位置域
					{
						sadplacevalue = am.MySadPlaceValue(c1, CurMap, CurC, value);
						if (sadplacevalue == 0 && CMap[c1.fx][c1.fy] != 'I')
							goorbackvalue = am.GoOrBackValue(c1, 1);
					}
				}
				score = grapplevalue + sadplacevalue + goorbackvalue;//四舍五入去掉不重要的分值

				x = AWT(depht + 1, Alpha, Beta, CurMap, CurVector, CurC, bestmove, -score);
				if (x > Alpha)
				{
					g = x;
					bestmove.setFX(c1.fx);
					bestmove.setFY(c1.fy);
					bestmove.setTX(c1.tx);
					bestmove.setTY(c1.ty);
					windowvalue = 0;
					if (g > 0)
						Alpha = g*Window(windowvalue, depht, total, CurC);
					else
						Alpha = g / Window(windowvalue, depht, total, CurC);
					GetLocalTime(&sys);//获取系统时间
					dwstart = sys.wMilliseconds;
					istime = 1;
				}
				/*
				else if (istime == 1)
				{
					GetLocalTime(&sys);
					if (sys.wMilliseconds - dwstart > -1 && windowvalue != 2)
					{
						windowvalue++;
						if (g > 0)
							Alpha = g*Window(windowvalue, depht, total, CurC);
						else
							Alpha = g / Window(windowvalue, depht, total, CurC);
						if (windowvalue != 2)
						{
							GetLocalTime(&sys);
							dwstart = sys.wMilliseconds;
						}
						else istime = 0;
					}
				}
				//
				c1 = mg.GetMove(depht, k++);
				Thansfor(CurMap, CMap, c1, CurC, C);//将走法生成器信息转换为棋盘信息，并刷新概率表
				ChangeVector(CurVector, vectors, CurMap, c1);//刷新棋盘路面信息

			}
		}
	}

	return g;
}
*/



/*
double SearchEngine::Scoremove(ChessMove m) {
	return scoremove[m.fx][m.fy][m.tx][m.ty];
}

bool CMP(ChessMove m, ChessMove n) {
	return Scoremove(m) > Scoremove(n);
}*/

 void SearchEngine::sort(int depth,int left,int right) {
	 ChessMove t;
	 if (left > right)
		 return;
	 ChessMove temp = mg.moveList[depth][left];
	 int i = left;
	 int j = right;
	 int fx1 = mg.moveList[depth][j].fx;
	 int fy1 = mg.moveList[depth][j].fy;
	 int tx1 = mg.moveList[depth][j].tx;
	 int ty1 = mg.moveList[depth][j].ty;
	 int fx2 = mg.moveList[depth][i].fx;
	 int fy2 = mg.moveList[depth][i].fy;
	 int tx2 = mg.moveList[depth][i].tx;
	 int ty2 = mg.moveList[depth][i].ty;
	 while (i != j)
	 {
		 while (scoremove[fx1][fy1][tx1][ty1] <= scoremove[temp.fx][temp.fy][temp.tx][temp.ty] && i < j) j--;
		 while (scoremove[fx2][fy2][tx2][ty2] >= scoremove[temp.fx][temp.fy][temp.tx][temp.ty] && i < j) i++;
		 if (i < j)
		 {
			 t = mg.moveList[depth][j];
			 mg.moveList[depth][j] = mg.moveList[depth][i];
			 mg.moveList[depth][i] = t;
		 }
	 }
	 mg.moveList[depth][left] = mg.moveList[depth][i];
	 mg.moveList[depth][i] = temp;
	 sort(depth, left, i - 1);
	 sort(depth, i + 1, right);
 }

double SearchEngine::DFS(char CurMap[12][5],Vector CurVector[12][5],Chance CurC[25], int depth, int ismine, double Alpha, double Beta) {
	end = clock();
	dur = end-start;
	//if (CurMap[0][0] >= 'A'&&CurMap[0][0] <= 'L')std::cout << "进";
#ifdef DEBUG
	//std::cout << depth << std::endl;
	//std::cout << dur << std::endl;
	//std::cout << CurMap[0][1] << "存活:" << CurC[1].alive <<"概率："<< CurC[1].P[11] << std::endl;
	//std::cout << CurMap[0][3] << "存活:" << CurC[3].alive << "概率：" << CurC[3].P[11] << std::endl;
#endif // DEBUG

	if ((CurC[1].alive==0&&CurC[1].P[11]!=0) || (CurC[3].alive==0&&CurC[3].P[11]!=0)) {
		if(ismine==0)return -99999;
		else return 99999;
	}
	if (CurMap[11][1] != 'L'&&CurMap[11][3] != 'L') {
		if (ismine = 0)return 99999;
		else return -99999;
	}
	if (depth == maxdepht) {
		return am2.PlaceScore(CurMap,CurVector,CurC,ismine)+am2.ChessScore(CurMap, CurVector,CurC, ismine);//返回局面分数
	}
	char NowMap[12][5];
	Vector NowVector[12][5];
	Chance NowC[25];
	int CurMapNumber[12][5];
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 5; j++) {
			NowMap[i][j] = CurMap[i][j];
			NowVector[i][j] = CurVector[i][j];
		}
	}
	for (int i = 0; i < 25; i++) NowC[i] = CurC[i];
	CharToInt(CurMap, CurMapNumber);//将char转换为int
	int count = mg.CreatePossibleMove(CurMapNumber,depth, ismine, CurVector);//产生可能的走法
	sort(depth,0,count-1);//对movelist根据价值排序
	//std::sort(mg.moveList[depth], mg.moveList[depth] + count + 1, CMP);
	double bestscore, nowscore;
	int countBestmove = 0;
	ChessMove bestmove[100];
	if (ismine == 0) bestscore = -999999;
	else bestscore = 999999;
//	std::cout << "此时在" << depth << "层" << std::endl;
	for (int i = 0; i < count; i++)
	{
	//	std::cout << "此时在" << depth << "层**" << std::endl;
		ChessMove c1 = mg.GetMove(depth,i);
		/*
		if (c1.fx == 10 && c1.fy == 3 && c1.tx == 10 && c1.ty == 4) 
		{
			std::cout <<"（10，3）->（10，4）出现在"<< depth << "层" << std::endl;
			std::cout << "***********" << std::endl;
			std::cout << CurMap[10][3] << " " << CurMap[10][4] << std::endl;
			std::cout << "***********" << std::endl;
			std::cout << std::endl;
			}*/
		if(ismine)
		if ((c1.tx == 0 && c1.ty == 1) || (c1.tx == 0 && c1.ty == 3)) {
			flag = 1;
			theBestMove = c1;
			break;
		}
		Thansfor( NowMap,CurMap, c1,NowC, CurC);//将走法生成器信息转换为棋盘信息，并刷新概率表
		ChangeVector( NowVector,CurVector,NowMap, c1);//刷新棋盘路面信息
		nowscore = DFS(NowMap, NowVector, NowC, depth + 1, ismine ^ 1, Alpha, Beta);
		
		if (timewarning) break;
		if (nowscore == bestscore) bestmove[countBestmove++] = mg.moveList[depth][i];
		if (ismine == 0)
		{
			if (nowscore > bestscore)
			{
				bestscore = nowscore;

		//		std::cout <<"我方收益为："<< bestscore <<std::endl;

				countBestmove = 1;
				bestmove[0] = mg.moveList[depth][i];
				Alpha = nowscore;
			}
		}
		else
		{
			if (nowscore < bestscore)
			{
				bestscore = nowscore;

		//		std::cout <<"敌方收益为："<< bestscore << std::endl;

				countBestmove = 1;
				bestmove[0] = mg.moveList[depth][i];
				Beta = nowscore;
			}
		}
		if (Alpha >= Beta)
		{
			scoremove[c1.fx][c1.fy][c1.tx][c1.ty] += pow(maxdepht - depth + 1, 2);
			if (ismine == 0)return 999999;
			else return -999999;
		}
	}
	if (timewarning)return -999999;
	if (flag)return 99999;
	for (int i = 0; i < countBestmove; i++) {
	//	std::cout <<"("<< bestmove[i].fx<<","<<bestmove[i].fy<<")->("<<bestmove[i].tx<<","<<bestmove[i].ty <<")"<< std::endl;
		scoremove[bestmove[i].fx][bestmove[i].fy][bestmove[i].tx][bestmove[i].ty]+= pow(maxdepht - depth + 1, 2);
	}
	if (depth == 0) {
		theBestMove = bestmove[rand() % countBestmove];
		//std::cout << "(" << bestmove[0].fx << "," << bestmove[0].fy << ")->(" << bestmove[0].tx << "," << bestmove[0].ty << ")" << std::endl;
	}

	return bestscore;
}

void SearchEngine::MakeDecision(char CMap[12][5], Vector(*vectors)[5], Chance C[25]) {
	memset(scoremove, 0, sizeof(scoremove));
	timewarning = false;
	double bestscore;
	char CurMap[12][5];
	Vector CurVector[12][5];
	Chance CurC[25];
	flag = 0;
	int ismine = 0;//ismine为0是为我方
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 5; j++) {
			CurMap[i][j] = CMap[i][j];
			CurVector[i][j]=vectors[i][j];
		}
	}
	for (int i = 0; i < 25; i++) CurC[i] = C[i];
	for (int d = 1; d <= 4; d++) {
		maxdepht = d;
		bestscore = DFS(CurMap, CurVector, CurC,0,ismine ,Alpha , Beta);
		if (bestscore > Winscore) break;
		if (timewarning) break;
		if (flag)break;
	}
}






/*
双方碰子，判断碰子结果
*/
void SearchEngine::Referee(char(*CurMap)[5], ChessMove move, Chance *CurC, Chance C[], int myChess)
{
	if (myChess == 1)//如果走棋方是己方棋子
	{
		if (CurMap[move.fx][move.fy] != 'I'&&CurMap[move.fx][move.fy] != 'K'&&CurMap[move.tx][move.ty] != 'k'
			&&CurMap[move.tx][move.ty] != 'l'&&CurMap[move.tx][move.ty] != 'j')	//普通情况
		{
			if (CurMap[move.fx][move.fy] - CurMap[move.tx][move.ty] > -32)		//己方棋子级别小于对方棋子,对方胜
				FreshMap(1, CurC, C, move, myChess, CurMap);						//:FreshMap(int result, Chance *CurC,Chance C[], ChessMove move, int mychess,char (*CurMap)[5])
			else if (CurMap[move.fx][move.fy] - CurMap[move.tx][move.ty] < -32)	//己方棋子级别大于对方棋子，机器胜
				FreshMap(0, CurC, C, move, myChess, CurMap);
			else//同归于尽
				FreshMap(2, CurC, C, move, myChess, CurMap);
		}
		if (CurMap[move.fx][move.fy] == 'K' || CurMap[move.tx][move.ty] == 'k')		//双方有炸弹，同归于尽
			FreshMap(2, CurC, C, move, myChess, CurMap);
		if (CurMap[move.tx][move.ty] == 'l')									//对方棋子为军旗，机器胜
			FreshMap(0, CurC, C, move, myChess, CurMap);
		if (CurMap[move.tx][move.ty] == 'j')										//对方棋子是地雷
		{
			if (CurMap[move.fx][move.fy] == 'I')									//己方棋子是工兵，机器方胜
				FreshMap(0, CurC, C, move, myChess, CurMap);
			else if (CurMap[move.fx][move.fy] == 'K')							//如果己方是炸弹，同归于尽
				FreshMap(2, CurC, C, move, myChess, CurMap);
			else//己方棋子不是工兵，也不是炸弹，对方胜
				FreshMap(1, CurC, C, move, myChess, CurMap);
		}
		if (CurMap[move.fx][move.fy] == 'I')										//如果己方是工兵
		{
			if (CurMap[move.tx][move.ty] == 'j' || CurMap[move.tx][move.ty] == 'l')	//对方是地雷或者军旗己方胜
				FreshMap(0, CurC, C, move, myChess, CurMap);
			else if (CurMap[move.tx][move.ty] == 'k' || CurMap[move.tx][move.ty] == 'i')//对方是炸弹或者士兵，同归于尽
				FreshMap(2, CurC, C, move, myChess, CurMap);
			else//对方不是地雷，军旗，炸弹，士兵
				FreshMap(1, CurC, C, move, myChess, CurMap);
		}
	}

	else if (myChess == 0)//如果走棋方是对方棋子
	{
		//判断，若对方不是工兵，不是炸弹，我方不是炸弹，不是军旗不是地雷
		if (CurMap[move.fx][move.fy] != 'i'&&CurMap[move.fx][move.fy] != 'k'&&CurMap[move.tx][move.ty] != 'K'
			&&CurMap[move.tx][move.ty] != 'L'&&CurMap[move.tx][move.ty] != 'J')
		{
			if (CurMap[move.fx][move.fy] - CurMap[move.tx][move.ty] > 32)			//对方棋子级别小于己方棋子，机器方胜
				FreshMap(0, CurC, C, move, myChess, CurMap);
			else if (CurMap[move.fx][move.fy] - CurMap[move.tx][move.ty] < 32)		//对方棋子级别大于己方棋子，对方胜
				FreshMap(1, CurC, C, move, myChess, CurMap);
			else//同归于尽
				FreshMap(2, CurC, C, move, myChess, CurMap);
		}
		if (CurMap[move.fx][move.fy] == 'k' || CurMap[move.tx][move.ty] == 'K')		//如果双方棋子中有炸弹，同归于尽
			FreshMap(2, CurC, C, move, myChess, CurMap);
		if (CurMap[move.tx][move.ty] == 'L')										//如果己方是军旗，对方胜
			FreshMap(1, CurC, C, move, myChess, CurMap);
		if (CurMap[move.tx][move.ty] == 'J')										//如果己方是地雷
		{
			if (CurMap[move.fx][move.fy] == 'i')									//如果对方是工兵，对方胜
				FreshMap(1, CurC, C, move, myChess, CurMap);
			else if (CurMap[move.fx][move.fy] == 'k')								//如果对方是炸弹
				FreshMap(2, CurC, C, move, myChess, CurMap);
			else//对方不是工兵也不是炸弹，机器方（我方）胜
				FreshMap(0, CurC, C, move, myChess, CurMap);
		}
		if (CurMap[move.fx][move.fy] == 'i')										//对方是工兵
		{
			if (CurMap[move.tx][move.ty] == 'J' || CurMap[move.tx][move.ty] == 'L')	//我方是地雷或军旗，对方胜
				FreshMap(1, CurC, C, move, myChess, CurMap);
			else if (CurMap[move.tx][move.ty] == 'K' || CurMap[move.tx][move.ty] == 'I')//我方是工兵或炸弹，同归于尽
				FreshMap(2, CurC, C, move, myChess, CurMap);
			else//我方不是地雷，军旗，工兵，炸弹，我方胜
				FreshMap(0, CurC, C, move, myChess, CurMap);
		}
	}
	Total(CurMap);//由于发生了拼杀，对方棋子总个数可能会有所改变，重新计算对方棋子个数
}

void SearchEngine::Total(char(*CurMap)[5])
{
	total = 0;
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 5; j++)
			if ('a' <= CurMap[i][j] && CurMap[i][j] <= 'l')
				total++;
}

void SearchEngine::CoordinateChange(Chance *CurC, Chance C[], int result, ChessMove move, int mychess)
{

	int i;
	//将概率表复制出来
	for (i = 0; i < 25; i++)
	{
		CurC[i].x = C[i].x;
		CurC[i].y = C[i].y;
		CurC[i].assume = C[i].assume;
		CurC[i].alive = C[i].alive;
		for (int j = 0; j < 12; j++)
			CurC[i].P[j] = C[i].P[j];
	}
	if (mychess == 0)					//如果是对方行棋
	{
		if (result == 2 || result == 0)	//如果是机器方胜，或者同归于尽
		{
			i = pb.SerchChess(CurC, move.fx, move.fy);
			CurC[i].x = 13;
			CurC[i].alive = 0;
			CurC[i].assume = '0';
		}
		else							//如果是对方胜或者无拼杀
		{
			i = pb.SerchChess(CurC, move.fx, move.fy);
			CurC[i].x = move.tx;
			CurC[i].y = move.ty;
		}//将对方棋子坐标移到落点
	}
	else//如果是机器方行棋		
	{
		if (result == 2 || result == 0)//如果是机器方胜，或者同归于尽
		{
			i = pb.SerchChess(CurC, move.tx, move.ty);
			CurC[i].x = 13;    //将对方棋子放到棋盘外
			CurC[i].alive = 0;
			CurC[i].assume = '0';
		}
	}



}

void SearchEngine::CharToInt(char CurMap[][5], int(*CurMapNumber)[5])
{
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 5; j++)
		{
			switch (CurMap[i][j])
			{
			case 'A':CurMapNumber[i][j] = 10; break;
			case 'B':CurMapNumber[i][j] = 9; break;
			case 'C':CurMapNumber[i][j] = 8; break;
			case 'D':CurMapNumber[i][j] = 7; break;
			case 'E':CurMapNumber[i][j] = 6; break;
			case 'F':CurMapNumber[i][j] = 5; break;
			case 'G':CurMapNumber[i][j] = 4; break;
			case 'H':CurMapNumber[i][j] = 3; break;
			case 'I':CurMapNumber[i][j] = 2; break;
			case 'J':CurMapNumber[i][j] = 12; break;
			case 'K':CurMapNumber[i][j] = 11; break;
			case 'L':CurMapNumber[i][j] = 1; break;
			case 'a':CurMapNumber[i][j] = 22; break;
			case 'b':CurMapNumber[i][j] = 21; break;
			case 'c':CurMapNumber[i][j] = 20; break;
			case 'd':CurMapNumber[i][j] = 19; break;
			case 'e':CurMapNumber[i][j] = 18; break;
			case 'f':CurMapNumber[i][j] = 17; break;
			case 'g':CurMapNumber[i][j] = 16; break;
			case 'h':CurMapNumber[i][j] = 15; break;
			case 'i':CurMapNumber[i][j] = 14; break;
			case 'j':CurMapNumber[i][j] = 24; break;
			case 'k':CurMapNumber[i][j] = 23; break;
			case 'l':CurMapNumber[i][j] = 13; break;
			default:CurMapNumber[i][j] = 0; break;
			}
		}
}


void SearchEngine::FreshMap(int result, Chance *CurC, Chance C[], ChessMove move, int mychess, char(*CurMap)[5])
{
	if (mychess == 1)//机器方行棋
	{
		if (result == 0)//机器方胜
		{
			CurMap[move.tx][move.ty] = CurMap[move.fx][move.fy];
			CurMap[move.fx][move.fy] = '0';
			//调用ID函数
			CoordinateChange(CurC, C, result, move, 1);
		}
		else if (result == 1)//对方获胜
		{
			CurMap[move.fx][move.fy] = '0';
			//调用ID函数
			CoordinateChange(CurC, C, result, move, 1);
		}
		else//同归于尽
		{
			CurMap[move.fx][move.fy] = '0';
			CurMap[move.tx][move.ty] = '0';
			//调用ID函数
			CoordinateChange(CurC, C, result, move, 1);
		}
	}
	else//对方行棋
	{
		if (result == 0)//机器方胜
		{
			CurMap[move.fx][move.fy] = '0';
			//调用ID函数
			CoordinateChange(CurC, C, result, move, 0);
		}
		else if (result == 1)//对方获胜
		{
			CurMap[move.tx][move.ty] = CurMap[move.fx][move.fy];
			CurMap[move.fx][move.fy] = '0';
			//调用ID函数
			CoordinateChange(CurC, C, result, move, 0);
		}
		else//同归于尽
		{
			CurMap[move.fx][move.fy] = '0';
			CurMap[move.tx][move.ty] = '0';
			//调用ID函数
			CoordinateChange(CurC, C, result, move, 0);
		}
	}
}

void SearchEngine::ChangeVector(Vector(*CurVector)[5], Vector vectors[][5], char CurMap[][5], ChessMove move)
{
	int fx, fy, tx, ty;
	fx = move.fx;
	fy = move.fy;
	tx = move.tx;
	ty = move.ty;
	//将路面信息复制出来
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 5; j++)
		{
			CurVector[i][j] = vectors[i][j];
		}
	ChangePowerAndBelong(CurVector, CurMap[fx][fy], fx, fy);
	ChangePowerAndBelong(CurVector, CurMap[tx][ty], tx, ty);
}

void SearchEngine::ChangePowerAndBelong(Vector(*CurVector)[5], char map, int x, int y)
{
	switch (map)
	{
	case 'A':CurVector[x][y].power = 10;
		CurVector[x][y].belongTo = 0;
		break;
	case 'B':CurVector[x][y].power = 9;
		CurVector[x][y].belongTo = 0;
		break;
	case 'C':CurVector[x][y].power = 8;
		CurVector[x][y].belongTo = 0;
		break;
	case 'D':CurVector[x][y].power = 7;
		CurVector[x][y].belongTo = 0;
		break;
	case 'E':CurVector[x][y].power = 6;
		CurVector[x][y].belongTo = 0;
		break;
	case 'F':CurVector[x][y].power = 5;
		CurVector[x][y].belongTo = 0;
		break;
	case 'G':CurVector[x][y].power = 4;
		CurVector[x][y].belongTo = 0;
		break;
	case 'H':CurVector[x][y].power = 3;
		CurVector[x][y].belongTo = 0;
		break;
	case 'I':CurVector[x][y].power = 2;
		CurVector[x][y].belongTo = 0;
		break;
	case 'J':CurVector[x][y].power = 12;
		CurVector[x][y].belongTo = 0;
		break;
	case 'K':CurVector[x][y].power = 11;
		CurVector[x][y].belongTo = 0;
		break;
	case 'L':CurVector[x][y].power = 1;
		CurVector[x][y].belongTo = 0;
		break;
	case 'a':CurVector[x][y].power = 22;
		CurVector[x][y].belongTo = 1;
		break;
	case 'b':CurVector[x][y].power = 21;
		CurVector[x][y].belongTo = 1;
		break;
	case 'c':CurVector[x][y].power = 20;
		CurVector[x][y].belongTo = 1;
		break;
	case 'd':CurVector[x][y].power = 19;
		CurVector[x][y].belongTo = 1;
		break;
	case 'e':CurVector[x][y].power = 18;
		CurVector[x][y].belongTo = 1;
		break;
	case 'f':CurVector[x][y].power = 17;
		CurVector[x][y].belongTo = 1;
		break;
	case 'g':CurVector[x][y].power = 16;
		CurVector[x][y].belongTo = 1;
		break;
	case 'h':CurVector[x][y].power = 15;
		CurVector[x][y].belongTo = 1;
		break;
	case 'i':CurVector[x][y].power = 14;
		CurVector[x][y].belongTo = 1;
		break;
	case 'j':CurVector[x][y].power = 24;
		CurVector[x][y].belongTo = 1;
		break;
	case 'k':CurVector[x][y].power = 23;
		CurVector[x][y].belongTo = 1;
		break;
	case 'l':CurVector[x][y].power = 13;
		CurVector[x][y].belongTo = 1;
		break;
	default:CurVector[x][y].power = 0;
		CurVector[x][y].belongTo = 2;
		break;
	}
}






// hance.h: interface for the Chance class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HANCE_H__F06CF070_6259_414D_AFFF_CEE9415E44E7__INCLUDED_)
#define AFX_HANCE_H__F06CF070_6259_414D_AFFF_CEE9415E44E7__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Chance  
{
public:
	double P[13]; //从司令到军旗的概率,最后一个空间防止溢出
	char assume;  //未知棋子假设值
	int x;
	int y;
	int alive;
	Chance();
	virtual ~Chance();

};

#endif // !defined(AFX_HANCE_H__F06CF070_6259_414D_AFFF_CEE9415E44E7__INCLUDED_)

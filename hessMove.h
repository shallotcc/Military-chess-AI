// hessMove.h: interface for the ChessMove class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HESSMOVE_H__6702D58B_C1A8_4E2A_8E7D_09CDB02949DF__INCLUDED_)
#define AFX_HESSMOVE_H__6702D58B_C1A8_4E2A_8E7D_09CDB02949DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ChessMove  
{
public:
	//成员方法分别设置起始坐标，落点坐标
	void setTY(int tY);
	void setTX(int tX);
	void setFY(int fY);
	void setFX(int fX);
	//用于存储起始坐标与落点坐标
	int fx; 
	int fy; 
	int ty; 
	int tx; 
	ChessMove();  //无参空构造函数
	~ChessMove();

};

#endif // !defined(AFX_HESSMOVE_H__6702D58B_C1A8_4E2A_8E7D_09CDB02949DF__INCLUDED_)

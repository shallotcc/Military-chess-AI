// Vector.h: interface for the Vector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR_H__4350A6AD_4483_41A9_A4D1_D2571F20F869__INCLUDED_)
#define AFX_VECTOR_H__4350A6AD_4483_41A9_A4D1_D2571F20F869__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Vector  
{
public:
	Vector();
	virtual ~Vector();
	bool operator == (Vector v1);
	void operator = (Vector v1);
	int row;
	int col;	
	int power;
	int belongTo;//0表示AI，1表示玩家
	int isRoad;//0表示公路，1表示铁路
    int isStuck;//1代表该顶点可以固定旗子，使其不能动弹
    int isSave;//1表示该位子是安全的（即是行营）
};

#endif // !defined(AFX_VECTOR_H__4350A6AD_4483_41A9_A4D1_D2571F20F869__INCLUDED_)

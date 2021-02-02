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
	int belongTo;//0��ʾAI��1��ʾ���
	int isRoad;//0��ʾ��·��1��ʾ��·
    int isStuck;//1����ö�����Թ̶����ӣ�ʹ�䲻�ܶ���
    int isSave;//1��ʾ��λ���ǰ�ȫ�ģ�������Ӫ��
};

#endif // !defined(AFX_VECTOR_H__4350A6AD_4483_41A9_A4D1_D2571F20F869__INCLUDED_)

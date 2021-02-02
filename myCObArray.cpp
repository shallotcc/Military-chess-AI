// myCObArray.cpp: implementation of the myCObArray class.
//
//////////////////////////////////////////////////////////////////////
#include <afxwin.h>
#include "myCObArray.h"
#include <iostream>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

myCObArray::myCObArray()
{

}

myCObArray::~myCObArray()
{

}

bool myCObArray::empty()
{
	if (this->GetSize() == 0)
	{
		return true;
	}else
		return false;
	

}

Vector myCObArray::pop()
{
	Vector *vector =(Vector*) this->GetAt(this->GetSize()-1);//将栈最后一个棋盘节点取出存入vector
	this->RemoveAt(this->GetSize()-1);//将最末尾棋盘节点从栈中删除
    return *vector;//返回vector

}

int myCObArray::search(CObject *newElement)
{
	int k = 1;//如果栈中没有与当前棋盘节点相等的棋盘节点k=1,否则k=-1;
	for (int i = 0;i<this->GetSize();i++)//将当前棋盘节点依次与栈中个界面比较，如果有相等的k=-1
	{
		if (newElement ==this->GetAt(i))
		{
			k = -1;
			break;
		}
	}
	return k;//返回k值

}


bool myCObArray::contains(CObject *newElement)
{
	int row1=((CPoint *)newElement)->x;
	int col1=((CPoint *)newElement)->y;
	int row2,col2;
	for (int i = 0;i<this->GetSize();i++)
	{
			 row2=((CPoint *)this->GetAt(i))->x;
			 col2=((CPoint *)this->GetAt(i))->y;
		if (row1==row2&&col1==col2)
		{
			return true;
		}
	}
	return false;


}

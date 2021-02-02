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
	Vector *vector =(Vector*) this->GetAt(this->GetSize()-1);//��ջ���һ�����̽ڵ�ȡ������vector
	this->RemoveAt(this->GetSize()-1);//����ĩβ���̽ڵ��ջ��ɾ��
    return *vector;//����vector

}

int myCObArray::search(CObject *newElement)
{
	int k = 1;//���ջ��û���뵱ǰ���̽ڵ���ȵ����̽ڵ�k=1,����k=-1;
	for (int i = 0;i<this->GetSize();i++)//����ǰ���̽ڵ�������ջ�и�����Ƚϣ��������ȵ�k=-1
	{
		if (newElement ==this->GetAt(i))
		{
			k = -1;
			break;
		}
	}
	return k;//����kֵ

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

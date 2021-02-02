// myCObArray.h: interface for the myCObArray class.
//
//////////////////////////////////////////////////////////////////////
#include <afxcoll.h>
#include "Vector.h"	// Added by ClassView
#if !defined(AFX_MYCOBARRAY_H__1324FBE9_EE5D_43E6_82AF_45B0C0D271DC__INCLUDED_)
#define AFX_MYCOBARRAY_H__1324FBE9_EE5D_43E6_82AF_45B0C0D271DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class myCObArray:public CObArray
{
public:
	int col;
	int row;
	bool contains(CObject* newElement);
	int search(CObject *newElement);
	Vector pop();
	bool empty();
	
	myCObArray();
	virtual ~myCObArray();

};

#endif // !defined(AFX_MYCOBARRAY_H__1324FBE9_EE5D_43E6_82AF_45B0C0D271DC__INCLUDED_)

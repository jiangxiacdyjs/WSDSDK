// 3DPositioningWnd.h: interface for the C3DPositioningWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DPOSITIONINGWND_H__366C98CD_BA84_42C3_9EC6_AFDFF220CDE5__INCLUDED_)
#define AFX_3DPOSITIONINGWND_H__366C98CD_BA84_42C3_9EC6_AFDFF220CDE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CustomDrawWnd.h"

class C3DPositioningWnd : public CCustomDrawWnd  
{
public:
	CPoint	m_point;
	COLORREF			m_clrBackgroud;
	CString m_strTip;
	C3DPositioningWnd();
	virtual ~C3DPositioningWnd();

protected:
	void Paint( );
	void PaintBkgnd( );
};

#endif // !defined(AFX_3DPOSITIONINGWND_H__366C98CD_BA84_42C3_9EC6_AFDFF220CDE5__INCLUDED_)

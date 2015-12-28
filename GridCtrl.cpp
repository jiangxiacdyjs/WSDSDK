// GridCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "GridCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////IDC_STATIC_VIDEO//////////////////////
// CGridCtrl

CGridCtrl::CGridCtrl()
{
	m_font.CreatePointFont(120,"宋体");

	for(int i=0; i<GRID_ROW; i++)
	{
		for(int j=0; j<GRID_COL; j++)
		{
			m_arrData[i][j] = 0;
		}
	}	
	
	m_pDlgOwner	= NULL;
	m_bDrag		= FALSE;
}

CGridCtrl::~CGridCtrl()
{
	m_font.DeleteObject();
}

BEGIN_MESSAGE_MAP(CGridCtrl, CWnd)
	//{{AFX_MSG_MAP(CGridCtrl)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGridCtrl message handlers

void CGridCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

    DrawBk(&dc);
	DrawBlock(&dc);
	DrawLine(&dc);
	DrawText(&dc);
}

BOOL CGridCtrl::NotifyChange()
{
	if(m_pDlgOwner)
	{
		m_pDlgOwner->SendMessage(WM_GRID_CHANGE,0,0);
		return TRUE;
	}

	return FALSE;
}

void CGridCtrl::DrawLine(CDC *pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	
	int nItemWidth = rcClient.Width() / (GRID_COL+1);
	int nItemHeight = rcClient.Height() / GRID_ROW;

	int nHeight = 0;
	int i = 0;
	for(i = 0; i < 9; i++)
	{
		pDC->MoveTo(0, nHeight);
		pDC->LineTo(rcClient.right, nHeight);
		nHeight += nItemHeight;
	}

	int nWidth = 0;
	for(i = 0; i < 27; i++)
	{
		if(i != 1)
		{
			pDC->MoveTo(nWidth, rcClient.top);
			pDC->LineTo(nWidth, rcClient.bottom);
		}
		nWidth += nItemWidth;
	}
}

void CGridCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	CRect rcClient;
	GetClientRect(&rcClient);

	int nWndWidth = rcClient.Width() - (rcClient.Width() % (GRID_COL+1));
	int nWndHeight = rcClient.Height() - (rcClient.Height() % GRID_ROW);	
	
	SetWindowPos(NULL, 0, 0, nWndWidth+1, nWndHeight+1, SWP_NOMOVE);
}

void CGridCtrl::DrawText(CDC *pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	int nItemWidth = rcClient.Width() / (GRID_COL+1);
	int nItemHeight = rcClient.Height() / GRID_ROW;

	pDC->SetBkMode(TRANSPARENT);
	CFont *oldfont = pDC->SelectObject(&m_font);

	UINT nFormat = DT_SINGLELINE | DT_VCENTER | DT_CENTER;
	int nHeight = 0;
	int i=0;
	for(i=0; i<m_arrWeekStr.GetSize(); i++)
	{
		CString strText = m_arrWeekStr.GetAt(i);
		pDC->DrawText(strText, CRect(0, nHeight, nItemWidth*2, nHeight+nItemHeight), nFormat);
		nHeight += nItemHeight;
	}

	int nWidth = nItemWidth * 2;
	for(i = 0; i < (GRID_COL-1); i++)
	{
		CString strText;
		strText.Format("%d", i);
		pDC->DrawText(strText, CRect(nWidth, 0, nWidth+nItemWidth, nItemHeight), nFormat);
		nWidth += nItemWidth;
	}

	pDC->SelectObject(oldfont);
}

void CGridCtrl::DrawBlock(CDC *pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	int nItemWidth = rcClient.Width() / (GRID_COL+1);
	int nItemHeight = rcClient.Height() / GRID_ROW;
	
	int y = 0;
	int i=0;
	for(i=0; i<GRID_ROW; i++)
	{
		int x = 0;

		for(int j=0; j<GRID_COL; j++)
		{
			if(j == 0)
			{
				m_arrRct[i][j] = CRect(x, y, x + nItemWidth*2, y + nItemHeight);
				x += nItemWidth*2;
			}
			else
			{
				m_arrRct[i][j] = CRect(x, y, x + nItemWidth, y + nItemHeight);
				x += nItemWidth;
			}
		}

		y += nItemHeight;
	}

	for( i=0; i<GRID_ROW; i++)
	{
		for(int j=0; j<GRID_COL; j++)
		{
			if(m_arrData[i][j] == 0)
				continue;

			if(i == 0 && j != 0)
				continue;

			CRect rcFill = m_arrRct[i][j];
			rcFill.DeflateRect(2,2,1,1);
			if(j == 0)
			{
				pDC->FillSolidRect(rcFill, RGB(207,249,202));
			}
			else
			{
				pDC->FillSolidRect(rcFill, RGB(255,0,0));
			}
		}
	}	
}

void CGridCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_ptStart = m_ptStop = point;
	CWnd::OnLButtonDown(nFlags, point);
}

void CGridCtrl::SelectAll()
{
	NotifyChange();

	if(m_arrData[0][0] == 0)
		m_arrData[0][0] = 1;
	else
		m_arrData[0][0] = 0;
	
	for(int i=0; i<GRID_ROW; i++)
		for(int j=0; j<GRID_COL; j++)
			m_arrData[i][j] = m_arrData[0][0];
		
	Invalidate();
}

void CGridCtrl::Select(CPoint point)
{
	NotifyChange();
	for(int i=0; i<GRID_ROW; i++)
		for(int j=0; j<GRID_COL; j++)
		{
			if(m_arrRct[i][j].PtInRect(point))
			{
				if(m_arrData[i][j] == 0)
					m_arrData[i][j] = 1;
				else
					m_arrData[i][j] = 0;
				
				InvalidateRect(m_arrRct[i][j]);
				
				if(i == 0 && j != 0)
				{
					BOOL bSelect = FALSE;
					int z=1;
					for(z=1; z<GRID_ROW; z++)
					{
						if(m_arrData[z][j] != 0)
						{
							bSelect = TRUE;
							break;
						}
						else
						{
							bSelect = FALSE;
						}
					}
					for(z=1; z<GRID_ROW; z++)
					{
						if(bSelect)
							m_arrData[z][j] = 0;
						else
							m_arrData[z][j] = 1;
						InvalidateRect(m_arrRct[z][j]);
					}
				}
				
				return;
			}
		}
}

void CGridCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{	
	m_ptStart = m_ptStop = point;
	SelectOneRow(point);
	CWnd::OnRButtonDown(nFlags, point);
}

void CGridCtrl::SelectOneRow(CPoint point)
{
	NotifyChange();

	for(int i=0; i<GRID_ROW; i++)
		for(int j=0; j<GRID_COL; j++)
		{
			if(!m_arrRct[i][j].PtInRect(point))
				continue;
			
			if(i != 0 && j == 0)
			{
				BOOL bNoSelect = FALSE;
				int z=1;
				for(z=1; z<GRID_COL; z++)
				{
					if(m_arrData[i][z] == 0)
					{
						bNoSelect = TRUE;
						break;
					}
				}
				
				for(z=1; z<GRID_COL; z++)
				{
					if(bNoSelect)
						m_arrData[i][z] = 1;
					else
						m_arrData[i][z] = 0;
					InvalidateRect(m_arrRct[i][z]);
				}
			}
			
			return;
		}
}

void CGridCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_bDrag)
	{
		ClipCursor(NULL);
		
		CRect rcClient;
		GetClientRect(&rcClient);
		int nItemWidth = rcClient.Width() / (GRID_COL+1);
		int nItemHeight = rcClient.Height() / GRID_ROW;
		
		for(int i=0; i<GRID_ROW; i++)
		{
			for(int j=0; j<GRID_COL; j++)
			{
				CRect rc;
				if(rc.IntersectRect(m_rcSelect,m_arrRct[i][j]))
				{
					m_arrData[i][j] = 1;
				}
				
/*				CPoint ptTopLeft = m_arrRct[i][j].TopLeft( );
				CPoint ptBottomRight = m_arrRct[i][j].BottomRight( );
				CPoint ptTopRight = CPoint(m_arrRct[i][j].right, m_arrRct[i][j].top);
				CPoint ptBottomLeft = CPoint(m_arrRct[i][j].left, m_arrRct[i][j].bottom);
				
				if( m_rcSelect.PtInRect(ptTopLeft)		||
					m_rcSelect.PtInRect(ptBottomRight)	||
					m_rcSelect.PtInRect(ptTopRight)		||
					m_rcSelect.PtInRect(ptBottomLeft) )
				{
					m_arrData[i][j] = 1;
				}
*/  
			}
		}
		
		CRect rcNeedInva = m_rcSelect;
		rcNeedInva.InflateRect(nItemWidth, nItemHeight, nItemWidth, nItemHeight);
		InvalidateRect(&rcNeedInva);
		m_bDrag = FALSE;

		ChangeSelectAllState();
		CWnd::OnLButtonUp(nFlags, point);
		return;
	}	

	if(m_arrRct[0][0].PtInRect(point)) //选择全部或取消全部
	{
		SelectAll();
		CWnd::OnLButtonUp(nFlags, point);
		return;
	}
	
	Select(point); //改变单个的状态

	ChangeSelectAllState();
	CWnd::OnLButtonUp(nFlags, point);
}

void CGridCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{	
	if(nFlags & MK_LBUTTON || nFlags & MK_RBUTTON)
	{
		if(!IsInClient(m_ptStart))
			return;

		CDC *pDC = GetDC();
	
		CRect rcFocus(m_ptStart, m_ptStop);
		rcFocus.NormalizeRect();
		if(rcFocus.Width() != 0 && rcFocus.Height() != 0)
			pDC->DrawFocusRect(rcFocus);

		m_ptStop = point;
		rcFocus = CRect(m_ptStart, m_ptStop);
		rcFocus.NormalizeRect();
		if(rcFocus.Width() != 0 && rcFocus.Height() != 0)
		{
			m_bDrag = TRUE;
			CRect rc = m_rcCursorClient;
			ClientToScreen(&rc);
			ClipCursor(&rc);
			pDC->DrawFocusRect(rcFocus);
		}
		ReleaseDC(pDC);

		m_rcSelect = rcFocus;
		m_rcSelect.DeflateRect(2,2,2,2);
	}
	
	CWnd::OnMouseMove(nFlags, point);
}

void CGridCtrl::DrawBk(CDC *pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	pDC->FillSolidRect(rcClient, RGB(255,255,255));
}

void CGridCtrl::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bDrag)
	{
		ClipCursor(NULL);
		CRect rcClient;
		GetClientRect(&rcClient);
		int nItemWidth = rcClient.Width() / (GRID_COL+1);
		int nItemHeight = rcClient.Height() / GRID_ROW;
		
		for(int i=0; i<GRID_ROW; i++)
		{
			for(int j=0; j<GRID_COL; j++)
			{
				CRect rc;
				if(rc.IntersectRect(m_rcSelect,m_arrRct[i][j]))
				{
					m_arrData[i][j] = 0;
				}

/*				CPoint ptTopLeft = m_arrRct[i][j].TopLeft( );
				CPoint ptBottomRight = m_arrRct[i][j].BottomRight( );
				CPoint ptTopRight = CPoint(m_arrRct[i][j].right, m_arrRct[i][j].top);
				CPoint ptBottomLeft = CPoint(m_arrRct[i][j].left, m_arrRct[i][j].bottom);
				
				if(m_rcSelect.PtInRect(ptTopLeft) ||
					m_rcSelect.PtInRect(ptBottomRight) ||
					m_rcSelect.PtInRect(ptTopRight) ||
					m_rcSelect.PtInRect(ptBottomLeft))
				{
					m_arrData[i][j] = 0;
				}
		*/
			}
		
			CRect rcNeedInva = m_rcSelect;
			rcNeedInva.InflateRect(nItemWidth, nItemHeight, nItemWidth, nItemHeight);
			InvalidateRect(&rcNeedInva);
			m_bDrag = FALSE;
		} 
	}

	ChangeSelectAllState();
	CWnd::OnRButtonUp(nFlags, point);
}

BOOL CGridCtrl::IsInClient(CPoint point)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	int nItemWidth = rcClient.Width() / (GRID_COL+1);
	int nItemHeight = rcClient.Height() / GRID_ROW;
	m_rcCursorClient = rcClient;
	m_rcCursorClient.DeflateRect(nItemWidth*2, nItemHeight, 0, 0); 
	return m_rcCursorClient.PtInRect(point);
}

void CGridCtrl::SetWeekText(const CStringArray& arr)
{
	if(m_arrWeekStr.GetSize() != 0)
		m_arrWeekStr.RemoveAll();
	m_arrWeekStr.Append(arr);
}

void CGridCtrl::SetAllValue(int nVal)
{
	NotifyChange();

	for(int i=0; i<GRID_ROW; i++)
		for(int j=0; j<GRID_COL; j++)
		{
			m_arrData[i][j] = nVal;
		}
}

int CGridCtrl::GetGridItemData(int x, int y)
{
	return m_arrData[x][y];
}

void CGridCtrl::SetGridItemData(int x, int y, int nVal)
{
	NotifyChange();

	m_arrData[x][y] = nVal;
}

void CGridCtrl::PreSubclassWindow() 
{
	CRect rcClient;
	GetClientRect(&rcClient);
	int nWndWidth = rcClient.Width() - (rcClient.Width() % (GRID_COL+1));
	int nWndHeight = rcClient.Height() - (rcClient.Height() % GRID_ROW);
	
	SetWindowPos(NULL, 0, 0, nWndWidth+1, nWndHeight+1, SWP_NOMOVE);
	CWnd::PreSubclassWindow();
}

BOOL CGridCtrl::IsAllSelect()
{
	BOOL bRet = TRUE;
	for(int i=0; i<GRID_ROW; i++)
	{
		if(i==0)
			continue;
		for(int j=0; j<GRID_COL; j++)
		{
			if(m_arrData[i][j] == 0)
			{
				bRet = FALSE;
				break;
			}
		}
		if(!bRet)
			break;
	}

	return bRet;
}

void CGridCtrl::ChangeSelectAllState()
{
	if(!IsAllSelect())
	{
		if(m_arrData[0][0] != 0)
		{
			m_arrData[0][0] = 0;
			InvalidateRect(m_arrRct[0][0]);
		}
	}
	else
	{
		if(m_arrData[0][0] != 1)
		{
			m_arrData[0][0] = 1;
			InvalidateRect(m_arrRct[0][0]);
		}
	}

	NotifyChange();
}

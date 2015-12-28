#include "stdafx.h"
#include "VideoWndBase.h"

CVideoWndBase::CVideoWndBase(void)
{
    m_msgCallback = NULL;
    m_msgUserData = NULL;
    m_rc3D.left		= 0;
    m_rc3D.top		= 0;
    m_rc3D.right	= 0;
    m_rc3D.bottom	= 0;
    m_p3dWnd = NULL;
    m_bPositioning = FALSE;
    m_bTrackLeave = FALSE;
}

CVideoWndBase::~CVideoWndBase(void)
{
}

BEGIN_MESSAGE_MAP(CVideoWndBase, CWnd)
    ON_WM_LBUTTONDBLCLK()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONUP()
    ON_WM_ERASEBKGND()
    ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

BOOL CVideoWndBase::Create(UINT uID, RECT &rect, CWnd *pParentWnd,
               DWORD dwStyle)
{
    if(!CreateEx(0,CLASS_CVideoWndBase,"CVideoWndBase",dwStyle,rect,pParentWnd,uID)){
        ASSERT(FALSE);
        return FALSE;
    }
    return TRUE;
}

void CVideoWndBase::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    if (m_msgCallback)
    {
        VIDEO_WND_LBUTTON_DBL_CLK_POINT_T pt;
        pt.x = point.x;
        pt.y = point.y;

        CRect rc;
        GetClientRect(&rc);
        pt.vw = rc.Width();
        pt.vh = rc.Height();
        m_msgCallback(VIDEO_WND_MSG_LBUTTON_DBL_CLK, &pt, sizeof(VIDEO_WND_LBUTTON_DBL_CLK_POINT_T), m_msgUserData);
    }
    CWnd::OnLButtonDblClk(nFlags, point);
}

BOOL CVideoWndBase::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Add your specialized code here and/or call the base class
    WNDCLASS wc		 = {0};
    wc.style         = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = ::DefWindowProc;
    wc.hInstance     = AfxGetInstanceHandle();
    wc.lpszClassName = CLASS_CVideoWndBase;
    wc.hbrBackground = CreateSolidBrush(COLORREF_BK_OVERLAY);
    wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
    if(!AfxRegisterClass(&wc))
        return FALSE;

    return CWnd::PreCreateWindow(cs);
}

void CVideoWndBase::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    m_rc3D.left		= 0;
    m_rc3D.top		= 0;
    m_rc3D.right	= 0;
    m_rc3D.bottom	= 0;
    m_ptLeftTop = point;
    if (m_p3dWnd == NULL)
    {
        m_p3dWnd = new C3DPositioningWnd;
        BOOL ret = m_p3dWnd->Create(NULL, NULL, WS_CLIPSIBLINGS, CRect(0,0,100,100), this, 0);
        if (ret)
        {
            m_p3dWnd->m_strTip = m_str3D;
            m_p3dWnd->ShowWindow(SW_HIDE);
        }
    }

    CWnd::OnLButtonDown(nFlags, point);
}

void CVideoWndBase::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if((nFlags & MK_LBUTTON) && m_bPositioning)
    {
        if   (!m_bTrackLeave)
        {
            // 鼠标第一次移入窗口时，请求一个WM_MOUSELEAVE消息
            TRACKMOUSEEVENT tme;
            tme.cbSize = sizeof(tme);
            tme.hwndTrack = m_hWnd;
            tme.dwFlags = TME_LEAVE;
            _TrackMouseEvent(&tme);
            m_bTrackLeave = TRUE;
        }

        CRect rc3DOld ;
        m_ptNow = point;
        if ((m_ptNow.x < m_ptLeftTop.x) 
            && (m_ptNow.y < m_ptLeftTop.y))
        {
            //鼠标位于窗口的子窗口上，也会发送WM_MOUSELEAVE
            //+1 是为了防止发送错误的WM_MOUSELEAVE
            CRect rc3D(point.x+1, point.y+1, m_ptLeftTop.x, m_ptLeftTop.y);//3D定位的区域
            rc3D.NormalizeRect();

            rc3DOld = m_rc3D;
            m_rc3D = rc3D;
        }
        else
        {
            CRect rc3D(m_ptLeftTop.x, m_ptLeftTop.y, point.x, point.y);//3D定位的区域
            rc3D.NormalizeRect();

            rc3DOld = m_rc3D;
            m_rc3D = rc3D;
        }

        if (m_p3dWnd)
        {

            m_p3dWnd->ShowWindow(SW_HIDE);
            m_p3dWnd->SetWindowText(m_str3D);
            m_p3dWnd->MoveWindow(&m_rc3D);
            m_p3dWnd->ShowWindow(SW_SHOW);
        }

    }

    CWnd::OnMouseMove(nFlags, point);
}

void CVideoWndBase::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if (m_msgCallback && m_bPositioning)
    {
        VIDEO_WND_REGION_T rgn;
        rgn.x = m_rc3D.left;
        rgn.y = m_rc3D.top;
        rgn.w = m_rc3D.Width();
        rgn.h = m_rc3D.Height();

        CRect rc;
        GetClientRect(&rc);
        rgn.vw = rc.Width();
        rgn.vh = rc.Height();

        rgn.zoom = (point.y > m_ptLeftTop.y);
		if (m_rc3D.Width()>0)
		{
			m_msgCallback(VIDEO_WND_MSG_REGION_SELECT, &rgn, sizeof(VIDEO_WND_REGION_T), m_msgUserData);
		}
    }

    m_rc3D.left		= 0;
    m_rc3D.top		= 0;
    m_rc3D.right	= 0;
    m_rc3D.bottom	= 0;
    if(m_p3dWnd)
    {
        delete m_p3dWnd;
        m_p3dWnd = NULL;
    }

    CWnd::OnLButtonUp(nFlags, point);
}

BOOL CVideoWndBase::OnEraseBkgnd(CDC* pDC)
{
    // TODO: Add your message handler code here and/or call default
    if (m_bPositioning)
    {
        return FALSE;
    }

    return CWnd::OnEraseBkgnd(pDC);
}

LRESULT CVideoWndBase::OnMouseLeave(WPARAM wparam,LPARAM lparam)
{
    // TODO: Add your message handler code here and/or call default
    m_bTrackLeave = FALSE;
    if (m_p3dWnd)
    {
        m_p3dWnd->ShowWindow(SW_HIDE);
    }
    return 0;
}

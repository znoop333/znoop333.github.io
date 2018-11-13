// CPlotView.cpp : implementation of the CCPlotView class
//

#include "stdafx.h"
#include "CPlot.h"

#include <cmath>

#include "Chart.h"
#include "CPlotDoc.h"
#include "PlotSettingsDialog.h"
#include "AxisSettings.h"
#include "ColorControl.h"
#include "DataSettingsDialog.h"
#include "MainFrm.h"
#include "CPlotUtility.h"
#include "CPlotView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define		kNoUpdatePoint		-1000000

/////////////////////////////////////////////////////////////////////////////
// CCPlotView

IMPLEMENT_DYNCREATE(CCPlotView, CView)

BEGIN_MESSAGE_MAP(CCPlotView, CView)
	//{{AFX_MSG_MAP(CCPlotView)
	ON_COMMAND(ID_PLOTSETTINGS_PLOTSETUP, OnPlotsettingsPlotSetup)
	ON_COMMAND(ID_PLOTSETTINGS_AXISSETUP, OnPlotsettingsAxisSetup)
	ON_COMMAND(ID_PLOTSETTINGS_DATASETUP, OnPlotsettingsDataSetup)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND_RANGE( IDS_COLORTABLE_START, IDS_COLORTABLE_END, OnSetColorTable )
	ON_COMMAND_RANGE( ID_CHART_XYCHART, ID_CHART_2DCHART, OnSelectChart )
	ON_UPDATE_COMMAND_UI_RANGE( ID_CHART_XYCHART, ID_CHART_2DCHART, OnUpdateSelectChart )

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCPlotView construction/destruction

CCPlotView::CCPlotView()
{
	// TODO: add construction code here
	m_LastPoint.x = kNoUpdatePoint;
	m_CurDataSet = 1;
}

CCPlotView::~CCPlotView()
{
}

BOOL CCPlotView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCPlotView drawing

void CCPlotView::OnDraw(CDC* pDC)
{
	CCPlotDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect		clientRect, updateRect;
	CSize		ext, org;

	m_LastPoint.x = kNoUpdatePoint;

	GetClientRect( (LPRECT) clientRect );
	pDC->DPtoLP( (LPPOINT) &clientRect, 2); 

	pDC->GetClipBox( updateRect );
	updateRect.NormalizeRect();

	switch( GetDocument()->m_WhichChart )
	{
	case ID_CHART_XYCHART: GetDocument()->xyChart.OnDraw( pDC, clientRect, updateRect ); break;
	case ID_CHART_2DCHART: GetDocument()->imageChart.OnDraw( pDC, clientRect, updateRect ); break;
	default: break;
	}
}

void CCPlotView::OnDrawPrint( CDC *pDC, CRect boundingRect )
{
	// We'll inset the rect by a couple centimeters each side
	boundingRect.InflateRect( -100, 100 );

	switch( GetDocument()->m_WhichChart )
	{
	case ID_CHART_XYCHART: GetDocument()->xyChart.OnDraw( pDC, boundingRect ); break;
	case ID_CHART_2DCHART: GetDocument()->imageChart.OnDraw( pDC, boundingRect ); break;
	default: break;
	}
}
/////////////////////////////////////////////////////////////////////////////
// CCPlotView printing

BOOL CCPlotView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	pInfo->SetMaxPage( 1 );
	return DoPreparePrinting(pInfo);
}

void CCPlotView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCPlotView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCPlotView diagnostics

#ifdef _DEBUG
void CCPlotView::AssertValid() const
{
	CView::AssertValid();
}

void CCPlotView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCPlotDoc* CCPlotView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCPlotDoc)));
	return (CCPlotDoc*)m_pDocument;
}
#endif //_DEBUG

void CCPlotView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	CRect		rect;
	CRect		thisRect;
	float		ratio;

	GetClientRect( thisRect );

	// Get the aspect ratio
	ratio = (float)thisRect.Width() / (float)thisRect.Height();

	rect = pInfo->m_rectDraw;

	if( (float)abs(rect.Width()) / (float)abs(rect.Height()) > ratio )
	{
		// chop off some width
		rect.right = rect.left + (int)(abs(rect.Height()) * ratio);
	}
	else
	{
		// chop some off height
		rect.bottom = rect.top - (int)(abs(rect.Width()) / ratio);
	}

	OnDrawPrint( pDC, rect );
}

void CCPlotView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	CView::OnPrepareDC(pDC, pInfo);

	pDC->SetMapMode(MM_LOMETRIC);
}

/////////////////////////////////////////////////////////////////////////////
// CCPlotView message handlers

void CCPlotView::OnInitialUpdate() 
{

}

void	CCPlotView::OnSetColorTable( UINT id )
{
	GetDocument()->imageChart.SetPaletteMenu( id );

	// Force an update
	Invalidate();
}

void	CCPlotView::OnSelectChart( UINT id )
{
	GetDocument()->m_WhichChart = id;

	Invalidate();
}

 void	CCPlotView::OnUpdateSelectChart( CCmdUI *cmd )
{ 
	 cmd->SetCheck((cmd->m_nID == GetDocument()->m_WhichChart)?1:0);
}


void CCPlotView::OnPlotsettingsPlotSetup() 
{
	if( GetDocument()->m_WhichChart == ID_CHART_XYCHART )
	{
		if( GetDocument()->xyChart.PlotSettings() )
			Invalidate( TRUE );
	}
	else
	{
		if( GetDocument()->imageChart.PlotSettings() )
			Invalidate( TRUE );
	}
}

void CCPlotView::OnPlotsettingsAxisSetup() 
{
	if( GetDocument()->m_WhichChart == ID_CHART_XYCHART )
	{
		if( GetDocument()->xyChart.AxisSettings() )
			Invalidate( TRUE );
	}
	else
	{
		if( GetDocument()->imageChart.AxisSettings() )
			Invalidate( TRUE );
	}
}

void CCPlotView::OnPlotsettingsDataSetup() 
{
	if( GetDocument()->m_WhichChart != ID_CHART_XYCHART ) return;

	if( GetDocument()->xyChart.DataSettings() )
		Invalidate( TRUE );
}

void CCPlotView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CPoint		temp( kNoUpdatePoint,0);
	OnMouseMove( 0, temp );

	ClientToScreen( &point );

	if( GetDocument()->m_WhichChart == ID_CHART_XYCHART )
	{if( GetDocument()->xyChart.ShowPopupMenu( this, nFlags, point ) ) Invalidate();}
	else
	{if( GetDocument()->imageChart.ShowPopupMenu( this, nFlags, point ) ) Invalidate();}
}

void CCPlotView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int		dataSetCount;

	if( GetDocument()->m_WhichChart == ID_CHART_XYCHART )
		dataSetCount = GetDocument()->xyChart.GetDataSetCount();
	else
		dataSetCount = GetDocument()->imageChart.GetDataSetCount();

	m_CurDataSet = (m_CurDataSet + 1) % dataSetCount + 1;

	// call it manually
	OnMouseMove( 0, point );

	// Print the current coordinates
	// Uncomment if you want a dialog box to go up
	// showing results of coordinate conversions
/*	CDC			*pDC = this->GetDC();
	int			oldMode;
	double		data[2], nearestData[2];
	CString		string;
	CPoint		reversePoint, nearestPoint = point;

	oldMode = pDC->SetMapMode( MM_LOMETRIC );

	pDC->DPtoLP( &point );

	if( GetDocument()->m_WhichChart == ID_CHART_XYCHART )
	{
		GetDocument()->xyChart.LPToData( pDC, &point, data );
		GetDocument()->xyChart.DataToLP( pDC, data, &reversePoint );
		GetDocument()->xyChart.LPToNearest( pDC, &point, nearestData );
	}
	else
	{
		GetDocument()->imageChart.LPToData( pDC, &point, data );
		GetDocument()->imageChart.DataToLP( pDC, data, &reversePoint );
		GetDocument()->imageChart.LPToNearest( pDC, &point, nearestData );
	}

	pDC->SetMapMode( oldMode );

	string.Format( "Point clicked: (%d, %d). Data value (LPToData): (%g, %g)\nReverse point (DataToLP): (%d, %d)\nNearest point (LPToNearest): (%g, %g)",
		point.x, point.y, data[0], data[1], reversePoint.x, reversePoint.y,
		nearestData[0], nearestData[1]);

	AfxMessageBox( string );	*/
}

void CCPlotView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CMainFrame			*frame = (CMainFrame*)AfxGetMainWnd();

	if( frame )
	{
		CDC			*pDC = this->GetDC();
		int			oldMode, oldROP, i;
		double		nearestData[2];
		CString		string;
		CPen		pen, *pOldPen;
		CPoint		nearestPoint, otherPoint;
		CRect		arcRect;

		oldMode = pDC->SetMapMode( MM_LOMETRIC );

		if( point.x != kNoUpdatePoint )
		{
			pDC->DPtoLP( &point );
			
			if( GetDocument()->m_WhichChart == ID_CHART_XYCHART )
			{
				GetDocument()->xyChart.LPToNearest( pDC, &point, nearestData, m_CurDataSet );
				GetDocument()->xyChart.DataToLP( pDC, nearestData, &nearestPoint );
			}
			else
			{
				GetDocument()->imageChart.LPToNearest( pDC, &point, nearestData );
				GetDocument()->imageChart.DataToLP( pDC, nearestData, &nearestPoint );
			}
			
			string.Format( "Nearest data point: (%g, %g)", nearestData[0], nearestData[1] );
			
			frame->m_wndStatusBar.SetPaneText( 1, string, TRUE );	
		}

		pen.CreatePen( PS_SOLID, 5, RGB( 0, 255, 255 ) );
		pOldPen = pDC->SelectObject( &pen );

		oldROP = pDC->SetROP2( R2_XORPEN );

		otherPoint = m_LastPoint;
		for( i = 0; i < 2; i++ )
		{
			if( otherPoint.x != kNoUpdatePoint )
			{
				arcRect.SetRect( otherPoint.x-25, otherPoint.y+25, otherPoint.x+25, otherPoint.y-25 );
				pDC->Arc( arcRect, otherPoint, otherPoint );
			}
			otherPoint = nearestPoint;
		}

		pDC->SelectObject( pOldPen );
		pDC->SetROP2( oldROP );
		m_LastPoint = nearestPoint;

		pDC->SetMapMode( oldMode );

	}

	CView::OnMouseMove(nFlags, point);
}

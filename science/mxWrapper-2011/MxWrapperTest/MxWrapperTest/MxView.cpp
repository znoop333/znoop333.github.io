// MxView.cpp : implementation file
//

#include "stdafx.h"
#include "MxWrapperTest.h"
#include "MxView.h"
#include "MxWrapperTestDoc.h"


// CMxView

IMPLEMENT_DYNCREATE(CMxView, CFormView)

CMxView::CMxView()
	: CFormView(CMxView::IDD)
{

}

CMxView::~CMxView()
{
}

void CMxView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mEditFormula1);
	DDX_Control(pDX, IDC_EDIT2, mEditFormula2);
	DDX_Control(pDX, IDC_CPLOT, m_cplot);
	DDX_Control(pDX, IDC_BUTTON_EVAL, m_EvaluateNow);
}

BEGIN_MESSAGE_MAP(CMxView, CFormView)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CMxView::OnEnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CMxView::OnEnKillfocusEdit1)
	ON_BN_CLICKED(IDC_BUTTON_EVAL, &CMxView::OnBnClickedButtonEval)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMxView diagnostics

#ifdef _DEBUG
void CMxView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMxView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CMxView::UpdatePlots()
{	
	CMxWrapperTestDoc* pDoc = (CMxWrapperTestDoc *) GetDocument();
	ASSERT_VALID(pDoc);

// show chart 1, user plot
	m_Chart.DeleteAllData();

	mxWrapper X = pDoc->GetX();
	mxWrapper Y = pDoc->GetY();
	mxWrapper XY = horzcat( X, Y );

	int dims[2];
	dims[0]=2;
	dims[1]=X.Size(2);
	int		dataID = m_Chart.AddData( XY.getPr(), 2, dims );

	m_Chart.SetTitle( "Y=F(X)" );

	CAxis	*axis= m_Chart.AddAxis( kLocationLeft );
	axis->SetTitle( "Parabola Y Value" );
	axis = m_Chart.AddAxis( kLocationBottom );
	axis->SetTitle( "X Value" );

	m_Chart.SetMarkerType( dataID, kXYMarkerSquare );
	m_Chart.SetMarkerFrequency( dataID, 2 );



	Invalidate();
}

// CMxView message handlers

void CMxView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	mEditFormula1.SetWindowText( _T("linspace(0,10,100)") );
	mEditFormula2.SetWindowText( _T("(X-3).*(X-6)") );

	// determine how big the dialog window was before any resizing
	CRect r;
	GetClientRect(&r);
	InitDialogHeight = r.Height();
	InitDialogWidth = r.Width();

	// save the initial x coordinates of every child window in this dialog window so they can be moved in OnSize
	for(CWnd *wnd = GetWindow(GW_CHILD); wnd != NULL; wnd = wnd->GetWindow(GW_HWNDNEXT))
	{
		// save the upper edge of the child windows so they can be moved later
		wnd->GetWindowRect(&r); // get screen coordinates of child windows (static text label, buttons, etc.)
		ScreenToClient(&r);      // change to coordinates of dialog window

		int id = wnd->GetDlgCtrlID();  // ID of child window, e.g., IDC_SSPANEL31 or IDC_EDITPH
		ASSERT( id != 0 );  // 0 means failure

		initCoordX[id]=r.left;  // this is now initialized to the number of pixels from the left of the dialog window to the left of the child window 
		initCoordY[id]=r.top;  // this is now initialized to the number of pixels from the left of the dialog window to the left of the child window 
		initCoordW[id]=r.Width();
		initCoordH[id]=r.Height();
	}

	UpdatePlots();
}

void CMxView::OnEnKillfocusEdit1()
{
	CString str;
	CMxWrapperTestDoc* pDoc = (CMxWrapperTestDoc *) GetDocument();
	ASSERT_VALID(pDoc);

	mEditFormula1.GetWindowText(str);
	pDoc->SetXFormula( str );

	mEditFormula2.GetWindowText(str);
	pDoc->SetYFormula( str );

	pDoc->ComputeSoln();

	UpdatePlots();
}


void CMxView::OnDraw(CDC* pDC)
{
	CFormView::OnDraw(pDC);

	CMxWrapperTestDoc* pDoc = (CMxWrapperTestDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	CRect		clientRect, clientRect2;
	CSize		ext, org;

	m_cplot.GetWindowRect( clientRect );
	ScreenToClient(clientRect);

	int nOldMode = pDC->SetMapMode( MM_LOMETRIC );

	pDC->DPtoLP( (LPPOINT) &clientRect, 2 );

	m_Chart.OnDraw( pDC, clientRect );

	pDC->SetMapMode( nOldMode );
}

void CMxView::OnBnClickedButtonEval()
{
	OnEnKillfocusEdit1();
}

void CMxView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if(m_cplot.GetSafeHwnd() == NULL || ( cy == 0 ) || ( cx == 0 ) )
		return;

	ASSERT(InitDialogWidth > 0);

	float newXscale = (float)cx/(float)InitDialogWidth;  // should not be negative
	float newYscale = (float)cy/(float)InitDialogHeight;  // should not be negative
	//ASSERT(newXscale >= 1.0);
	//ASSERT(newXscale < 10.0);
	//ASSERT(newYscale >= 1.0);
	//ASSERT(newYscale < 10.0);

	CRect r;
	for(CWnd *wnd = GetWindow(GW_CHILD); wnd != NULL; wnd = wnd->GetWindow(GW_HWNDNEXT))
	{
		wnd->GetWindowRect(&r); // get the current screen coordinates of the child window
		ScreenToClient(&r);      // offset to coordinates relative to this dialog window

		int id = wnd->GetDlgCtrlID();  // ID of child window, e.g., IDC_SSPANEL31 or IDC_EDITPH
		ASSERT( id != 0 );  // 0 means failure
		if (id == IDC_STATIC)
			continue;

		int initX = initCoordX[id];
		int initY = initCoordY[id];
		int initW = initCoordW[id];
		int initH = initCoordH[id];

		r.left = (int) ((float)initX*newXscale);  // adjust the top of the child window to a proportional distance 
		r.top = (int) ((float)initY*newYscale);  // adjust the top of the child window to a proportional distance 
		r.right = r.left + (int) ((float)initW*newXscale);  
		r.bottom = r.top + (int) ((float)initH*newYscale); 

		r.NormalizeRect();

		ASSERT( r.Width() <= cx );
		ASSERT( r.Height() <= cy );

		// new position and size; no Z-order change; don't redraw yet
		//wnd->SetWindowPos(NULL, r.left, r.top, r.Width(), r.Height(), SWP_NOZORDER | SWP_NOREDRAW );
	}

	Invalidate(); // now redraw everything at once
}
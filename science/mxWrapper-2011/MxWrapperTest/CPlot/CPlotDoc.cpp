// CPlotDoc.cpp : implementation of the CCPlotDoc class
//

#include "stdafx.h"
#include "CPlot.h"
#include <cmath>
#include "CPlotDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	M_PI		3.141592653589793

/////////////////////////////////////////////////////////////////////////////
// CCPlotDoc

IMPLEMENT_DYNCREATE(CCPlotDoc, CDocument)

BEGIN_MESSAGE_MAP(CCPlotDoc, CDocument)
	//{{AFX_MSG_MAP(CCPlotDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCPlotDoc construction/destruction

CCPlotDoc::CCPlotDoc()
{
	m_WhichChart = ID_CHART_XYCHART;
}

CCPlotDoc::~CCPlotDoc()
{
	ASSERT( 1 );
}

BOOL CCPlotDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CCPlotDoc		*pDoc = this;

	CAxis		*axis;


#define		kDataSize		26
#define		k2DDataSize		1024

	double			data[2*kDataSize];
	int			dims[] = {2, kDataSize};
	int			i;
	int			dataID;

	for( i = 0; i < kDataSize; i++ )
	{
		data[i] = i;
		data[kDataSize+i] = -fabs(1e3*sin( (double)i/(double)(kDataSize) * 2*M_PI )) - 1;
	}

//	chart.m_UseMajorHorizontalGrids = TRUE;
//	chart.m_UseMajorVerticalGrids = TRUE;
//	chart.m_UseMinorHorizontalGrids = TRUE;
//	chart.m_UseMinorVerticalGrids = TRUE;
	
	dataID = pDoc->xyChart.AddData( data, 2, dims );

	pDoc->xyChart.SetTitle( "Chart Title" );

	axis = pDoc->xyChart.AddAxis( kLocationBottom );
	axis->SetTitle( "The value of i" );

	axis = pDoc->xyChart.AddAxis( kLocationLeft );
	axis->SetTitle( "The value of j" );

	axis = pDoc->xyChart.AddAxis( kLocationRight );
	axis->SetTitle( "Righthand axis" );
	axis->SetRange( 0, 1 );

	axis = pDoc->xyChart.AddAxis( kLocationTop );
	axis->SetTitle( "Top axis" );

	pDoc->xyChart.SetMarkerType( dataID, kXYMarkerNone );
	pDoc->xyChart.SetChartType( dataID, kXYChartConnect );

	for( i = 0; i < kDataSize; i++ )
	{
		data[i] = i;
		data[kDataSize+i] = 1e3*cos( (double)i/(double)(kDataSize) * 2*M_PI );
	}

//	dataID = pDoc->xyChart.AddData( data, 2, dims );
	pDoc->xyChart.SetMarkerType( dataID, kXYMarkerSquare );
	pDoc->xyChart.SetChartType( dataID, kXYChartConnect );
	pDoc->xyChart.SetDataColor( dataID, RGB( 255, 0, 0 ) );
	pDoc->xyChart.SetDataTitle( dataID, "My red data" );

	for( i = 0; i < kDataSize; i++ )
	{
		data[i] = i;
		data[kDataSize+i] = 1e3*cos( (double)i/(double)(kDataSize) * 2*M_PI + M_PI/2 );
	}

//	dataID = pDoc->xyChart.AddData( data, 2, dims );
	pDoc->xyChart.SetMarkerType( dataID, kXYMarkerTriangle );
	pDoc->xyChart.SetChartType( dataID, kXYChartHistogram );
	pDoc->xyChart.SetDataColor( dataID, RGB( 0, 0, 255 ) );

	pDoc->xyChart.SetXRange( 0, kDataSize-1 );
	pDoc->xyChart.m_UseMajorHorizontalGrids = TRUE;
	pDoc->xyChart.m_UseMajorVerticalGrids = TRUE;
	pDoc->xyChart.SetYRange( -1000, -1 );
	
	// Some other settings to play with

	//	pDoc->xyChart.m_UseMinorHorizontalGrids = TRUE;
	//	pDoc->xyChart.m_UseMinorVerticalGrids = TRUE;

	/*	axis = chart.AddAxis( kLocationTop );
	axis->SetRange( 5, -5 );
	axis->SetTitle( "Top axis" );

	axis = chart.AddAxis( kLocationRight );
	axis->SetRange( 0, 10 );
	axis->SetTitle( "Right hand axis" );
*/

	{
	double			*data;
	int			dims[] = {k2DDataSize, k2DDataSize};
	int			i;

	data = (double *)VirtualAlloc( NULL, k2DDataSize*k2DDataSize * sizeof( double ),
		MEM_COMMIT, PAGE_READWRITE );

	for( i = 0; i < k2DDataSize*k2DDataSize; i++ )
	{
		data[i] = i / k2DDataSize;
	}

	pDoc->imageChart.m_UseMajorHorizontalGrids = TRUE;
	pDoc->imageChart.m_UseMajorVerticalGrids = TRUE;
	pDoc->imageChart.m_UseMinorHorizontalGrids = TRUE;
	pDoc->imageChart.m_UseMinorVerticalGrids = TRUE;
	
	pDoc->imageChart.AddImage( data, 2, dims, TRUE, FALSE );
//	chart.SetTitle( "Chart Title" );

	axis = pDoc->imageChart.AddAxis( kLocationBottom );
	axis->SetTitle( "The value of i" );
//	axis->SetRange( 0, 10 );

	axis = pDoc->imageChart.AddAxis( kLocationLeft );
	axis->SetTitle( "The value of j" );
	axis->SetRange( 0, 10 );
	}
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCPlotDoc serialization

void CCPlotDoc::Serialize(CArchive& ar)
{
	imageChart.Serialize( ar );
	xyChart.Serialize( ar );

	if (ar.IsStoring())
	{
		ar << m_WhichChart;
	}
	else
	{
		ar >> m_WhichChart;
		UpdateAllViews(NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCPlotDoc diagnostics

#ifdef _DEBUG
void CCPlotDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCPlotDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCPlotDoc commands

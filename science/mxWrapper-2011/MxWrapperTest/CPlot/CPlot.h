// CPlot.h : main header file for the CPLOT application
//

#if !defined(AFX_CPLOT_H__C46367B7_603D_4CB1_96F1_D1E1E6DC3317__INCLUDED_)
#define AFX_CPLOT_H__C46367B7_603D_4CB1_96F1_D1E1E6DC3317__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCPlotApp:
// See CPlot.cpp for the implementation of this class
//

class CCPlotApp : public CWinApp
{
public:
	CCPlotApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCPlotApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCPlotApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPLOT_H__C46367B7_603D_4CB1_96F1_D1E1E6DC3317__INCLUDED_)

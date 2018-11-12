#pragma once
#include "afxwin.h"
#include "DlgAreaPlot.h"

#include "Chart.h"


#include <map>
using std::map;

// CMxView form view

class CMxView : public CFormView
{
	DECLARE_DYNCREATE(CMxView)

protected:
	CMxView();           // protected constructor used by dynamic creation
	virtual ~CMxView();

public:
	enum { IDD = IDD_FORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	virtual void OnDraw(CDC* pDC);  // overridden to draw this view

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CEdit mEditFormula1;
	CEdit mEditFormula2;
	void UpdatePlots();
	int InitDialogHeight, InitDialogWidth;
	map<int,int> initCoordY, initCoordX, initCoordW, initCoordH;

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnEnKillfocusEdit1();
	CStatic m_cplot;
	CXYChart m_Chart;
	CButton m_EvaluateNow;
	afx_msg void OnBnClickedButtonEval();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};



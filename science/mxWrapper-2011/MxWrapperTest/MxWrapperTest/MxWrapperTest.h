// MxWrapperTest.h : main header file for the MxWrapperTest application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMxWrapperTestApp:
// See MxWrapperTest.cpp for the implementation of this class
//

class CMxWrapperTestApp : public CWinApp
{
public:
	CMxWrapperTestApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnUpdateFileStart(CCmdUI *pCmdUI);
};

extern CMxWrapperTestApp theApp;
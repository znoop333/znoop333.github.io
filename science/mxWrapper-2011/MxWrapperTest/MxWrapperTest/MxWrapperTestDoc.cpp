// MxWrapperTestDoc.cpp : implementation of the CMxWrapperTestDoc class
//

#include "stdafx.h"
#include "MxWrapperTest.h"

#include "MxWrapperTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMxWrapperTestDoc

IMPLEMENT_DYNCREATE(CMxWrapperTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CMxWrapperTestDoc, CDocument)
END_MESSAGE_MAP()


// CMxWrapperTestDoc construction/destruction

CMxWrapperTestDoc::CMxWrapperTestDoc()
{
	XFormula = mxWrapper(_T("linspace(0,10,100)"));
	YFormula = mxWrapper(_T("(X-3).*(X-6)"));
	X = linspace(0,10,100);
	Y = (X-3)*(X-6);
}

CMxWrapperTestDoc::~CMxWrapperTestDoc()
{
	CloseEngine();
}

BOOL CMxWrapperTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMxWrapperTestDoc serialization

void CMxWrapperTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CMxWrapperTestDoc diagnostics

#ifdef _DEBUG
void CMxWrapperTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMxWrapperTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMxWrapperTestDoc commands

void CMxWrapperTestDoc::ComputeSoln(void)
{
	Engine *pEng = GetEnginePtr();

	XFormula.put(pEng,"XFormula");
	mxWrapperEngEvalString(pEng, "X = eval(XFormula);" );
	X.get(pEng,"X");

	if(X.IsEmpty())
	{
		X = ramp(1.0,1.0,10.0);
		XFormula = _T("1:10");
		X.put(pEng,"X");
	}

	YFormula.put(pEng,"YFormula");
	mxWrapperEngEvalString(pEng, "Y = eval(YFormula);" );
	Y.get(pEng,"Y");

	if(Y.IsEmpty())
	{
		Y = ramp(1.0,1.0,10.0);
		YFormula = _T("1:10");
		Y.put(pEng,"Y");
	}

#ifndef _DEBUG
	mxWrapperEngEvalString(pEng, "clear X Y XFormula YFormula " );
#endif

}

void CMxWrapperTestDoc::SetXFormula(const CString &MatlabExpression)
{
	XFormula = mxWrapper(MatlabExpression);
}

void CMxWrapperTestDoc::SetYFormula(const CString &MatlabExpression)
{
	YFormula = mxWrapper(MatlabExpression);
}

// MxWrapperTestDoc.h : interface of the CMxWrapperTestDoc class
//


#pragma once

#include "mxWrapper.h"

using namespace mxWrapperNS;

class CMxWrapperTestDoc : public CDocument
{
protected: // create from serialization only
	CMxWrapperTestDoc();
	DECLARE_DYNCREATE(CMxWrapperTestDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CMxWrapperTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	mxWrapper X, Y, XFormula, YFormula;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	void ComputeSoln(void);
	void SetXFormula(const CString &MatlabExpression);
	void SetYFormula(const CString &MatlabExpression);

	mxWrapper GetX() { return X; }
	mxWrapper GetY() { return Y; }
};


